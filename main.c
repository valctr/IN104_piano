#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wav.h"
#include "tools.h"
#include "window.h"
#include "framing.h"
#include "fundamentals.h"
#include "fft.h"
#define FFT_SIZE 8192
#define WIN_LEN 0.25
#define WIN_HOP 0.1
#define ALPHA 0.025
#define NB_HARMONICS 2


int main(){

/*Récupération du nom du fichier traité*/
char fichieraudio[100];
printf("Entrez le nom du fichier (fichier wav mono) : ");
scanf("%s", fichieraudio);

/*Récupération du nom de la fenêtre à utiliser*/
char window_name[100];
printf("Entrez la fenêtre à utiliser (hann ou hamming) : ");
scanf("%s", window_name);
if ((!strcmp(window_name,"hann")) && (!strcmp(window_name,"hamming"))){
	printf("Erreur : fenêtre inexistante. Veuillez choisir hann ou hamming");
	exit(EXIT_FAILURE);
}

int taille=0;
int num_samples=0;
int samplingfreq, num_frames,frame_length,frame_step;

/*Ouverture du fichier wav et création d'un tableau contenant les données*/
double *data = open_wav(fichieraudio,"data.dat",&taille,&num_samples,&samplingfreq);

/*Découpage du signal en image*/
double **frames_data = framing(data,samplingfreq,WIN_LEN,WIN_HOP,taille,&frame_length,&num_frames,&frame_step,FFT_SIZE);
if ((int) frame_length<FFT_SIZE) {
	printf("\nErreur : frame_length doit être supérieur à fft_size -> diminuer fft_size ou augmenter WIN_LEN");
	exit(EXIT_FAILURE);
}

num_frames =(int) (num_samples/frame_step);

/*Application du fenêtrage*/
double **frames_window = window(frames_data,num_frames,frame_length,window_name);

/*Calcul de la FFT*/
double **frames_fft = fft(frames_window,num_frames,frame_length,FFT_SIZE);

/*Calcul des fréquences des notes jouées*/
int **frames_fundamentals = fundamentals(frames_fft,num_frames,FFT_SIZE,NB_HARMONICS, samplingfreq,ALPHA);

/*Correction du tableau*/
correct(frames_fundamentals,num_frames,frame_length, ALPHA);

/*On écrit le résultat dans un fichier nommé fundamentals.dat*/
FILE *fft=fopen("fundamentals.dat","wb");
for (int i=0;i<num_frames;i++)
{
	fprintf(fft,"%d %fs : ",i,i*(double)(frame_step)/samplingfreq);
	if ((frames_fundamentals[i]!=NULL)&&(frames_fundamentals[i][0]>0)){
		for (int j = 1; j < frames_fundamentals[i][0]+1; ++j)
		{
			fprintf (fft,"%d ", frames_fundamentals[i][j]);
		}
	}
	else fprintf(fft,"No notes");
	fprintf(fft,"\n");
}
fclose(fft);

/*On libère la mémoire allouée*/
for (int i = 0; i < num_frames; ++i)
{
	free(frames_data[i]);
	free(frames_window[i]);
	if (!frames_fft[i]) free(frames_fft[i]);
	if (!frames_fundamentals[i]) free(frames_fundamentals[i]);

}
free(frames_data);
free(frames_window);
free(frames_fft);
free(frames_fundamentals);
free(data);

return 0;
}