#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
#include "tools.h"
#include "window.h"
#include "fundamentals.h"
#include "fft.h"


#include "wav.c"
#include "tools.c"
#include "window.c"
#include "fundamentals.c"
#include "fft.c"


#define FFT_SIZE 8192
#define ALPHA 0.025
#define num_frames 1


float main1(){
char fichieraudio[100];
printf("Entrez le nom du fichier : ");
scanf("%s", fichieraudio);

int size_data=0;
int num_samples=0;
int samplingfreq, frame_length;

double **frames_data = malloc(sizeof(double *));
if (frames_data==NULL){
	printf("Error when allocating memory\n");
	exit(EXIT_FAILURE);
}
frames_data[0] = open_wav(fichieraudio,"data.dat",&size_data,&num_samples,&samplingfreq);
frame_length = size_data;



if ((int) frame_length<FFT_SIZE) {
	printf("\nErreur : frame_length doit être supérieur à fft_size -> diminuer fft_size ou augmenter WIN_LEN");
	exit(EXIT_FAILURE);
}

double **frames_window = window(frames_data,num_frames,frame_length);

double **frames_fft = fft(frames_window,num_frames,frame_length,FFT_SIZE);

int **frames_fundamentals = fundamentals(frames_fft,num_frames,FFT_SIZE,2, samplingfreq,ALPHA);

float fundamental = (float)frames_fundamentals[0][1];
printf("La fréquence de la note jouée est %fHz\n",fundamental);

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

return fundamental;
}
