[y_in,fs] = audioread('D:\Group\1\f_scaling\male.WAV');
[y_out,fs2] = audioread('D:\Group\1\f_scaling\male_out.WAV');
len_in=length(y_in);
len_out=length(y_out);
F_in=fs*(1:(len_in/2-1))/len_in; %frequency vector
F_out=fs*(1:(len_out/2-1))/len_out; %frequency vector
figure;
subplot(2,1,1);
a=fft(y_in);
plot(F_in,abs(a(2:len_in/2,1)));
title('Input signal')
subplot(2,1,2);
a=fft(y_out);

plot(F_out,abs(a(2:len_out/2,1)));
title('output signal')
T1=1/fs;%sampling period 
T2=1/fs2;
t_in=(0:len_in-1)*T1;
t_out=(0:len_out-1)*T2;
figure;
subplot(2,1,1);
plot(t_in,y_in);
subplot(2,1,2);
plot(t_out,y_out);