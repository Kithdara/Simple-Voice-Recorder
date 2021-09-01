
%**************************SELECTIVE ENHANCING*****************************

%{
This programme aims to modify an audio signal by selectively enhancing its frequency components in amplitude.

Here we have divided the voice audio spectrum into two frequency ranges as Low Frequency range;
[0Hz < f < 2500Hz] and as the High Frequency range; [f > 2500Hz].

In this case, we enhance the High frequency range by increasing its
amplitude by a factor of 8, and reducing the amplitude of Low Frequency range
by a factor of 1/8.
%}

%-------------------Analyzing the Original Audio Clip----------------------

% 'voice.wav' is a pre-prepared wav. file with 8-bit resoultion and 16kHz sampling rate. 
[y,fs] = audioread('D:\Group\ard_downAA\male.wav');
y = y';

L=length(y);
t=[1:L]*1/fs;

figure;
subplot(2,1,1);
plot(t, y); xlabel('Time (seconds)'); ylabel('Amplitude'); title('Original Signal');

f1=(1:L)*fs/L;
Y=fft(y);

subplot(2,1,2);
plot(f1(1,1:length(f1)/2),abs(Y(1,1:length(y)/2)/L)); xlabel('Frequency (Hz)'); ylabel('Amplitude'); title('Frequency Spectrum');

%sound(y',fs);
%pause


%----------------Creating the Selectively Enhanced Audio-------------------

cut_off=1500/fs*2;
cut_off2=3000/fs*2; % cut-off frequency = 2500Hz
order=8;
order2=16;

h_low=[0 0 0 0 0 0 0 0 fir1(order,cut_off,'low')]; % creating the Low-Pass filter
h_high=fir1(order2,cut_off2,'high') ; % creating the High-Pass filter
h = h_low + h_high*8         % degrading Low frequencies and enhancing High frequencies

%{
h =
  Columns 1 through 19
   -0.0000    0.0061   -0.0053   -0.0033    0.0103   -0.0048   -0.0108    0.0171   -0.0000   -0.0250    0.0229    0.0148   -0.0457    0.0205    0.0444   -0.0675   -0.0000    0.0904   -0.0798

  Columns 20 through 38
   -0.0498    0.1497   -0.0661   -0.1412    0.2143   -0.0000   -0.2966    0.2728    0.1816   -0.6054    0.3138    0.8794   -2.3134    3.0816   -2.3134    0.8794    0.3138   -0.6054    0.1816

  Columns 39 through 57
    0.2728   -0.2966   -0.0000    0.2143   -0.1412   -0.0661    0.1497   -0.0498   -0.0798    0.0904   -0.0000   -0.0675    0.0444    0.0205   -0.0457    0.0148    0.0229   -0.0250   -0.0000

  Columns 58 through 65
    0.0171   -0.0108   -0.0048    0.0103   -0.0033   -0.0053    0.0061   -0.0000

These impulse values can be directly used in AVR-C++ coding to implement the corresponding filter.
Therefore, no need to do a manual calculation for creating a filter in the integrated code. 
%}



figure;
freqz(h,1,512);                     % displaying the compound filter characteristics
%pause

audio=conv(h,y);                    % convolving the original audio and filter 
outlength = length(y) + length(h) - 1; 

f_=fs*(0:outlength-1)/outlength;
f2=f_(1,1:length(f_)/2);
spectrum=fft(audio);

figure;
subplot(2,1,1);
plot(f1(1,1:length(f1)/2),abs(Y(1,1:length(y)/2)/L)); xlabel('Frequency (Hz)'); ylabel('Amplitude'); title('Original Audio Spectrum');
subplot(2,1,2);
plot(f2,abs(spectrum(1,1:length(spectrum)/2))/outlength); xlabel('Frequency (Hz)'); ylabel('Amplitude'); title('Selectively Enhanced Audio Spectrum');
sound(audio,fs);


