#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
#include "tools.h"
#include "window.h"
#include "framing.h"
#include "fundamentals.h"
#include "fft.h"
#define FFT_SIZE 8192
#define WIN_LEN 0.2
#define WIN_HOP 0.05
#define ALPHA 0.025


int main(){
char fichieraudio[100];
printf("Entrez le nom du fichier : ");
scanf("%s", fichieraudio);

int taille=0;
int num_samples=0;
int samplingfreq, num_frames,frame_length,frame_step;

double *data = open_wav(fichieraudio,"data.dat",&taille,&num_samples,&samplingfreq);

printf("fft size %d\n",FFT_SIZE);

double **frames_data = framing(data,samplingfreq,WIN_LEN,WIN_HOP,taille,&frame_length,&num_frames,&frame_step);
if ((int) frame_length<FFT_SIZE) {
	printf("\nErreur : frame_length doit être supérieur à fft_size -> diminuer fft_size ou augmenter WIN_LEN");
	exit(EXIT_FAILURE);
}

num_frames =(int) (num_samples/frame_step);

double **frames_window = window(frames_data,num_frames,frame_length);

double **frames_fft = fft(frames_window,num_frames,frame_length,FFT_SIZE);

/*char buf3[14];
for (int i = 0; i < num_frames; ++i)
{
	if(frames_fft[i]!=NULL){
		snprintf(buf3, 14, "%dfft.dat", i);
		printtextdouble(buf3,frames_fft[i],FFT_SIZE);
	}
}


char buf4[14];
for (int i=0; i<num_frames; i++) {
	if (frames_fft[i]!=NULL){
		double modules[FFT_SIZE];
		for (int j=0;j<FFT_SIZE;j++){
			modules[j] = square_module(frames_fft[i],j);
		}
		snprintf(buf4, 14, "%dmod.dat", i);
		FILE *fft=fopen(buf4,"wb"); 
		for (int k = 0; k < FFT_SIZE; k++)
		{
			fprintf (fft,"%lf\n", modules[k]);
		}
		fclose(fft);
	}
}*/

int **frames_fundamentals = fundamentals(frames_fft,num_frames,FFT_SIZE,2, samplingfreq,ALPHA);
correct(frames_fundamentals,num_frames,frame_length, ALPHA);

FILE *fft=fopen("fun.dat","wb");
	for (int i=0;i<num_frames;i++)
	{
		fprintf(fft,"%d %fs : ",i,i*(double)(frame_step)/samplingfreq);
		if ((frames_fundamentals[i]!=NULL)&&(frames_fundamentals[i][0]>0)){
			for (int j = 1; j < frames_fundamentals[i][0]+1; ++j)
			{
				fprintf (fft,"%d ", frames_fundamentals[i][j]);
			}
		}
		fprintf(fft,"\n");
	}
fclose(fft);


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