Fs = 44100;
Fn = Fs/2; 
data(isnan(data))=[];             % Eliminate ‘NaN’ Values First
LF = size(data,1);   
T = linspace(0,1,size(data,1))*(1/Fs); 
figure(3)                   % Plot Data 
plot(T, data)
grid
FF = fft(data)/LF;             % Fourier Series of Data, Freq Vector
Fv = linspace(0,1,fix(LF/2)+1)*Fn;
Iv = 1:length(Fv);          % Index Vector
figure(2)                   % Plot FFT
semilogy(Fv, abs(FF(Iv)))
grid
xlabel('Frequency (Hz)')
ylabel('Amplitude')
axis([0  1500    ylim])

% Fs = 44100;
% Fn = Fs/2;
% fft = sqrt(datafft(:,1).^2+datafft(:,2).^2);
% fft(isnan(fft))=[];             % Eliminate ‘NaN’ Values First
% LF = size(fft,1);   
% T = linspace(0,1,size(fft,1))*(1/Fs); 
% figure(1)                   % Plot Data 
% plot(T, data)
% grid
% FF = fft/LF;             % Fourier Series of Data, Freq Vector
% Fv = linspace(0,1,fix(LF/2)+1)*Fn;
% Iv = 1:length(Fv);          % Index Vector
% figure(2)                   % Plot FFT
% semilogy(Fv, abs(FF(Iv)))
% grid
% xlabel('Frequency (Hz)')
% ylabel('Amplitude')
% axis([0  1500    ylim])