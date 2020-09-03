function USBReady(~,~,src,~)
    global din;
    global dt;
    global datary;

    global    x;
    global  y11;
    global  y12;
    global gh11;
    global gh12;

    global pt_gh;
    global xLen;
    global isPoint1st;
    global frm_len;
    global fft_len;
    global fft_cnt;
    global fft_dat;

    while src.Source.Avial() > (frm_len)
        % r=src.Source.ReadSync(frm_len);
        din = double(src.Source.Read(frm_len));
        dt  = reshape(din,4,[]);
        datary = dt(2,:).*256.*256 + dt(3,:).*256 + dt(4,:);
        datary = datary - (datary >= (2^23))*(2^24);

        if isPoint1st == 1
            isPoint1st = 0;
            y11(:) = mean(datary);
        else
            y11(1:frm_len/4) = datary;
            y11(frm_len/4+1:xLen) = mean(datary);
            % y11(pt_gh) = mean(datary);
        end
        set(gh11,'XData',x,'YData',y11);
        
        fft_dat((1 + fft_cnt * frm_len/4):((fft_cnt+1)*frm_len/4)) = datary;
        fft_cnt = fft_cnt + 1;
        if fft_cnt == fft_len
            Fs = 120e6/128/16;
            NFFT = length(fft_dat);
            Y = fft((fft_dat(1:NFFT))/(2^23),NFFT)/NFFT;
            X = Fs/2*linspace(0,1,NFFT/2);
            y12 = 20*log10(2*abs(Y(1:NFFT/2)));
            fft_cnt = 0;
            set(gh12,'XData',X,'YData',y12);
        end
        
        pt_gh = pt_gh + 1;
        if pt_gh == (xLen + 1)
            pt_gh = 1;
        end
    end

    drawnow limitrate nocallbacks
end