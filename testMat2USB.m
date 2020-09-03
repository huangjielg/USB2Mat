 a=actxserver('USB2Mat.USB')
 registerevent(a,{'DataReady', @USBReady})
 a.saveFilename='d:\bin';
 a.readyThreshold = 10240;
 a.Start();
 
 
 % a.Stop
 % delete(a)
 
 

 