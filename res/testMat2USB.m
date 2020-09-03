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

pt_gh = 1;
xLen = 992;
isPoint1st = 1;
frm_len = 240*1024/64;
fft_len = 128/4/4;
fft_cnt =   0;
fft_dat = zeros(1,frm_len / 4 * fft_len);

x  = 1:xLen;
y11 = zeros(1,xLen);
y12 = zeros(1,xLen);

subplot(2,1,1); gh11 = plot(y11);
subplot(2,1,2); gh12 = plot(y12); title(sprintf('Point Number %d',frm_len / 4 * fft_len));

 a = actxserver('USB2Mat.USB');
 registerevent(a,{'DataReady', @USBReady});
 a.saveFilename='c:\a.bin';
 a.readyThreshold = frm_len;
 a.Start();
 % tic
 pause
 % a.Stop();
 delete(a)
 % r=a.ReadSync(240*1024);