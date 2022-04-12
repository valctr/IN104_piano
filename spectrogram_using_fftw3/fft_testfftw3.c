#include <stdio.h>
#include <math.h>
#include "wav_testfftw3.h"
#include <fftw3.h>

int main(){

char fichieraudio[100];
printf ("entrer le nom du fichier audio a analyser :\n");
scanf("%s", fichieraudio);
printf ("nom du fichier : %s\n", fichieraudio);

double **data = open_wav(fichieraudio,"data.dat");
unsigned int N = 128;

fftw_complex *in, *out;
fftw_plan p;

in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

for (int i=0; i<N; i++){
	in[i][0] = data[i][0];
	in[i][1] = data[i][1];
}

fftw_execute(p); /* repeat as needed */

FILE *fft=fopen("data_fft.dat","w");
for (int i = 0; i < 128; i++)
{
fprintf (fft,"%lf %lf\n", out[i][0], out[i][1]);
}
return 0;

fftw_destroy_plan(p);
fftw_free(in); fftw_free(out);
}
