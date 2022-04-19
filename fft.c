#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "wav.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])



int main(){
char fichieraudio[100];
printf ("entrer le nom du fichier audio a analyser :\n");
scanf("%s", fichieraudio);
printf ("nom du fichier : %s\n", fichieraudio);

int taille=0;
double *data = open_wav(fichieraudio,"data.dat",&taille);
printf("tailleres : %d\n",taille);

gsl_complex_packed_array data_fft = data;
gsl_fft_complex_radix2_forward(data_fft, 1, taille);
printf("test: %lf\n",IMAG(data_fft,1023));

FILE *fft=fopen("data_fft.dat","w");
for (int i = 0; i < taille; i++)
{
fprintf(fft,"%lf %lf\n", REAL(data_fft,i), IMAG(data_fft,i));
}
fclose(fft);
free(data);
free(data_fft);
return 0;
}

