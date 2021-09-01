[y,fs] = audioread('D:\Group\shift2 - Copy - Copy\male.WAV');


y = y';                     % getting the transpose of y
shift=5000;

figure;
subplot(1,2,1);
len = length(y);
F=(fs+shift)*(-(len-1)/2:(len-1)/2)/len;
plot(F,abs(fftshift(fft(y))));
title('Modulating Signal')
i=1;

while(i<length(y))
    
    y(i)=y(i)*cos(2*2*pi*shift*i/len);
    i=i+1;
end

len = length(y) + length(h_high) - 1; 
F=fs*(-(len-1)/2:(len-1)/2)/len; %frequency vector
h = [0.0217 ,  -0.0023 ,  -0.0358 ,  -0.0842 ,  -0.1276 ,   0.4567 ,  -0.1276 ,  -0.0842 ,  -0.0358 ,  -0.0023   , 0.0217];


y=conv(h,y);
len = length(y) + length(h) - 1; 
F=fs*(-(len-1)/2:(len-1)/2)/len; %frequency vector



mx=max(y);
mi=min(y);
j=0;
while(j<length(y))
    j=j+1;
    y(j)=(y(j)-mi)/(mx-mi);
    %y(j)=round(y(i)+125);
end

len=length(y);
F=(fs+shift)*(-(len-1)/2:(len-1)/2); %frequency vector
subplot(1,2,2);
a=fft(y);
a(1)=0;
y=ifft(a);
sound(y,fs);
plot(F,abs(fftshift(a)));
title('Frequency shifted signal')