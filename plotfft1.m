%%Time specifications:
Fs = 44100;                      % samples per second
dt = 1/Fs;                     % seconds per sample
StopTime = 1;                  % seconds
t = (0:dt:StopTime-dt)';
N = size(datafft,1);

tmp = datafft;
X = fftshift(tmp);
X = sqrt(X(:,1).^2+X(:,2).^2);

%%Frequency specifications:
dF = Fs/N;                      % hertz
%f = -Fs/2+dF:dF:Fs/2;           % hertz
f = -Fs/2+dF:dF:Fs/2;   
%%Plot the spectrum:
figure;
semilogy(f,abs(X)/N);
xlabel('Frequency (in hertz)');
title('Magnitude Response');