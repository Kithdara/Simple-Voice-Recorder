[y_in,fs] = audioread('D:\Group\1\shift_final - Copy (3)\male.WAV');
[y_out,fs2] = audioread('D:\Group\1\shift_final - Copy (3)\male_out.WAV');
sound(y_out,fs2);
len_in=length(y_in);
len_out=length(y_out);
F_in=fs*(1:(len_in/2-1))/len_in; %frequency vector
F_out=fs*(1:(len_out/2-1))/len_out; %frequency vector
figure;
shift=2000;
subplot(2,1,1);
a=fft(y_in);
plot(F_in,abs(a(2:len_in/2,1)));
title('Input signal (Arduino)')
subplot(2,1,2);
a=fft(y_out);

plot(F_out,abs(a(2:len_out/2,1)));
title('output signal (Arduino)')
figure;
a=fft(y_out);
a(1)=0;
y_out=ifft(a);
F_out=(fs+shift)*(-(len_out-1)/2:(len_out-1)/2)/len_out; %frequency vector
plot(F_out,abs(fftshift(fft(y_out))));
title('Output signal (Arduino)')
