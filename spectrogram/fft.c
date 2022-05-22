#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wav.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])
#define FFT_SIZE 8192


int main(){
char fichieraudio[100];
printf ("entrer le nom du fichier audio a analyser :\n");
scanf("%s", fichieraudio);
printf ("nom du fichier : %s\n", fichieraudio);

int length;
double *data = open_wav(fichieraudio,"data.dat", &length);

/*double tmp[length]; 
for (int i=0;i<length;i++) {
	REAL(tmp,i) = REAL(data,i);
	IMAG(tmp,i) = IMAG(data,j);
}*/
gsl_complex_packed_array data_fft = data;
gsl_fft_complex_radix2_forward(data_fft, 1, FFT_SIZE); //calcul de la fft

FILE *fft=fopen("data_fft.dat","w"); //réécriture des résultats dans un fichier .dat
for (int i = 0; i < FFT_SIZE; i++)
{
fprintf (fft,"%lf %lf\n", REAL(data_fft,i), IMAG(data_fft,i));
}

free(data);
return 0;
}

