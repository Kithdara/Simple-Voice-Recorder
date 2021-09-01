[y_in,fs] = audioread('D:\Group\shift_final\male.WAV');
[y_out,fs2] = audioread('D:\Group\shift_final\male_out.WAV');
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
figure;
F_out=fs*(1:(len_out))/len_out; %frequency vector
plot(F_out,abs(fft(y_out)));
