#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "wav.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])


double* open_wav(char* fichieraudio, char* fnameout, int *size, int *num_samples,int *samplingfreq)
{
int i=0;
int taille=1; //variable qui correspondra par la suite a la longueur du tableau(puissance de 2)
int nbech=0; //nombre d echantillons extraits du fichier audio
FILE *wav = fopen(fichieraudio,"rb"); //ouverture du fichier wave
struct wavfile header; //creation du header
if ( wav == NULL )
{
printf("\nne peut pas ouvrir le fichier demande, verifier le nom\n");
printf("ne pas oublier l'extention .wav\n");
exit(1);
}
//initialise le header par l'entete du fichier wave
//verifie que le fichier possÈde un entete compatible
if ( fread(&header,sizeof(header),1,wav) < 1 )
{
printf("\nne peut pas lire le header\n");
exit(1);
}
if ( header.id[0] != 'R'
|| header.id[1] != 'I'
|| header.id[2] != 'F'
|| header.id[3] != 'F' )
{
printf("\nerreur le fichier n'est pas un format wave valide\n");
exit(1);
}
if (header.channels!=1)
{
printf("\nerreur : le fichier n'est pas mono\n");
exit(1);
}
nbech=(header.bytes_in_data/header.bytes_by_capture);
printf ("\nle fichier audio contient %d echantillons\n",nbech);
while (nbech>taille)
{
taille=taille*2;
}
*num_samples = nbech;
*size = taille;

double *tab=malloc(2*(taille) * sizeof(double) );
if (tab==NULL){
	printf("Error when allocating memory\n");
	exit(0);
}

tab[taille]=(double)taille;


i=0;
short value=0;
FILE *dat=fopen(fnameout,"w"); //fichier data des echantillons
while( fread(&value,(header.bits_per_sample)/8,1,wav) )
{ //lecture des echantillons et enregistrement dans le tableau
REAL(tab,i)=value;
IMAG(tab,i)=0.0;
i++;
}

*samplingfreq = header.frequency;
printf("fréquence d'échantillonage : %d\n",header.frequency);
printf("taille : %d\n", taille);
printf("\nnombre d'echantillons lus : %d\n",i);
printf("nombre de valeurs sauvegardees %d\n",i);

fprintf(dat,"taille = %d\n",taille);
for (int i=0;i<(taille);i++)
{
fprintf(dat,"%d : %lf %lf\n",i, REAL(tab,i), REAL(tab,i));
}


fclose(wav);
fclose(dat);

return(tab);
}