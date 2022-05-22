#include <math.h>
#include <string.h>
#include "tools.h"
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

/*Fenêtre de Hann*/
double hann(int i, int N){
	return(0.5 * (1.0 - cos(2.0*M_PI*(double)i / N )));
}

/*Fenêtre de Hamming*/
double hamming(int i, int N){
	return(0.54 - 0.46 * cos(2.0*M_PI*(double)i / N ));
}

/*Fonction pour appliquer la fenêtre au signal*/
double** window(double **frames,int num_frames, int frame_length, char *window_name){
	double **frames_out = create_frames_tab(num_frames,frame_length);

	if (!strcmp(window_name,"hann")){
		for(int i=0; i<num_frames; i++){
			for (int j=0; j<frame_length; j++)
			{
				REAL(frames_out[i],j) = hann(j,frame_length)*REAL(frames[i],j);
				IMAG(frames_out[i],j) = hann(j,frame_length)*IMAG(frames[i],j);
			}
	 	}
 	}

 	else if (!strcmp(window_name,"hamming")){
		for(int i=0; i<num_frames; i++){
			for (int j=0; j<frame_length; j++)
			{
				REAL(frames_out[i],j) = hamming(j,frame_length)*REAL(frames[i],j);
				IMAG(frames_out[i],j) = hamming(j,frame_length)*IMAG(frames[i],j);
			}
	 	}
 	}

 	return(frames_out);
}