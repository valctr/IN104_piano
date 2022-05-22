#include <math.h>
#include "tools.h"
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])


double hann(int i, int N){
	return(0.5 * (1.0 - cos(2.0*M_PI*(double)i / N )));
}

double** window(double **frames,int num_frames, int frame_length){
	double **frames_out = create_frames_tab(num_frames,frame_length);

	for(int i=0; i<num_frames; i++){
		for (int j=0; j<frame_length; j++)
		{
			REAL(frames_out[i],j) = hann(j,frame_length)*REAL(frames[i],j);
			IMAG(frames_out[i],j) = hann(j,frame_length)*IMAG(frames[i],j);
		}
 	}

 	return(frames_out);
}