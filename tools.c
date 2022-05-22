#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

double** create_frames_tab(int num_frames,int frame_length){

	double **frames = malloc(sizeof(double*)*num_frames);
	if (frames==NULL){
		free(frames);
		exit(EXIT_FAILURE);
	}

	for (int i=0; i<num_frames; i++){
		
		frames[i] = malloc(2*sizeof(double)*frame_length);
		if (frames[i]==NULL){
			for(int j=0;j<i;j++){
				free(frames[j]);
				free(frames);
				exit(EXIT_FAILURE);
			}
		}
	} 
	return(frames);
}

bool test_zero(double *frame, int frame_length){
	for (int i = 0; i < frame_length; ++i)
	{
			if( (abs(REAL(frame,i))>0.0000001) || (abs(IMAG(frame,i))>0.0000001) ) return(true);
	}
	return(false);
}

double square_module(double *data, int ind){
	return pow(REAL(data,ind),2) + pow(IMAG(data,ind),2);;
}

bool element_found(int elem,int **frames,int ind1,int ind2,int dir, double alpha){
	int k = ind1+dir;
	int length = frames[k][0];
	for (int i=1;i<length+1;i++){
		if (abs(elem-frames[k][i])<(int)(alpha*elem)) return(true);
	}
	return(false);
}

void printtextdouble(char* fname, double *frame, int frame_length){
	FILE *fft=fopen(fname,"wb"); 
	for (int i = 0; i < frame_length; i++) fprintf (fft,"%lf %lf\n", REAL(frame,i), IMAG(frame,i));
	fclose(fft);
}

void printtextint(char* fname, int *frame, int frame_length){
	FILE *fft=fopen(fname,"wb");
	for (int i = 1; i < frame_length+1; i++) fprintf (fft,"%d\n", frame[i]);
	fclose(fft);
}

