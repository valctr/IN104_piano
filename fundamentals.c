#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

int argmax(double *modules, int frame_length,int harmonic_nb, int samplingfreq, double *max_amp,double df){
	
	int argmax_f;
	double res = 1.0;
	double max_res = 0.0;


	for (int i=1; i<frame_length; i++){
		res = 0.0;
		int j = 1;

		if(modules[i]>0.1){
			while ((j<harmonic_nb+1)&&(j*i<frame_length)) {
			if(modules[j*i]>0.1) res+= log10(modules[j*i]);
			j++;}

			if (res>max_res) {
				max_res = res;
				argmax_f = i;
			}
		}
	}
	*max_amp = max_res;
	argmax_f =(int) (argmax_f*df);
	return(argmax_f);
}


void removefreq(double *modules, int f, double df, int frame_length, bool remove_harmonics, double alpha){


	int min, max;
	if (remove_harmonics){
		int i=1;
		while (i*f<frame_length){
			min = (int)(i*f*(1-alpha))/df;
			max = (int)(i*f*(1+alpha))/df;
			if (max>frame_length-1) max = frame_length-1;
			for (int j=min;j<max+1;j++) modules[j]=0.0;
			i++;
		}
	}

	else {
		min = (int)(f*(1-alpha))/df;
		max = (int)(f*(1+alpha))/df;
		if (max>frame_length-1) max = frame_length-1;
		for (int j=min;j<max+1;j++) modules[j]=0.0;
	}
}


int** fundamentals(double **frames, int num_frames, int frame_length,int harmonic_nb, int samplingfreq, double alpha){
	
	int **frames_fundamentals = malloc(num_frames*sizeof(int*));
	if (frames_fundamentals==NULL){
		free(frames_fundamentals);
		exit(EXIT_FAILURE);
	}

	for (int i=0; i<num_frames; i++){
		frames_fundamentals[i] = malloc(sizeof(int)*89);
		if (frames_fundamentals[i]==NULL){
			for(int j=0;j<i;j++){
				free(frames_fundamentals[j]);
				free(frames_fundamentals);
				exit(EXIT_FAILURE);
			}
		}
	} 

	for (int i=0; i<num_frames; i++){
		int f;
		double max_amp;

		double df = 2.0*samplingfreq/frame_length;

		if (frames[i]!=NULL){
			double *modules=malloc(sizeof(double)*frame_length/2);
			for (int k=0; k<frame_length/2; k++) modules[k] = square_module(frames[i],k);
			int j=1;
			f = argmax(modules,frame_length/2,harmonic_nb,samplingfreq,&max_amp,df);
			double min = max_amp-3.0;

			while ((max_amp>min) && (f>20) && (f<4500) && (j<89) && (modules[(int)(f/df)]>0.1)){
				if ((f>20) && (f<4500) && (max_amp>min)) {
					frames_fundamentals[i][j] = f;
					removefreq(modules,f,df,frame_length/2,1,alpha);
					j++;
				}
				else removefreq(modules,f,df,frame_length/2,0,alpha);
				f = argmax(modules,frame_length/2,harmonic_nb,samplingfreq,&max_amp,df);
			}
			frames_fundamentals[i][0]=j-1;
			free(modules);
		}

		else frames_fundamentals[i] = NULL;
	}


	return(frames_fundamentals);
}

void correct(int **frames_fundamentals,int num_frames, int frame_length, double alpha){

	for (int i=0;i<num_frames;i++){

		if ((frames_fundamentals[i]!=NULL)&&(frames_fundamentals[i][0]>1)){
			int length = frames_fundamentals[i][0]-1;
			int tmp[88];
			int count=0;
			int length_tmp = length-count;
			for (int j=0;j<length;j++) tmp[j]=frames_fundamentals[i][j+2];

			for (int j=0;j<length;j++){
				bool c = false;
				int f=frames_fundamentals[i][j+2];
				length_tmp = length-count;
				if (i>0){ 
					if (frames_fundamentals[i-1]!=NULL) c = element_found(f,frames_fundamentals,i,j+2,-1,alpha);
				}
				if (i<num_frames-1){ 
					if (frames_fundamentals[i+1]!=NULL) c = element_found(f,frames_fundamentals,i,j+2,1,alpha);
				}
				if (!c) {
					for (int k=j; k<length_tmp-1;k++) {
						tmp[k]=tmp[k+1];
					}
					frames_fundamentals[i][0]-=1;
					count+=1;
				}
			}

			if (length_tmp>0){
				for (int j=0;j<length_tmp;j++) frames_fundamentals[i][j+2]=tmp[j];
			}

		}
	}
}
