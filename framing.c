#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

double** framing(double *data, int fs, double win_len, double win_hop, int signal_length, int *outframe_length, int *outnum_frames, int *outframe_step){

	double frame_length = win_len * (double)fs;
	double frame_step = win_hop * (double)fs;
	double frames_overlap = frame_length - frame_step;
	printf("frame_length %f\n",frame_length);
	printf("frame_step %f\n",frame_step);
	printf("frames_overlap %f\n",frames_overlap);

	int num_frames = (int)(abs(signal_length - frames_overlap) / abs(frame_length - frames_overlap));
	int rest_samples = (int)(abs(signal_length - frames_overlap) % abs(frame_length - frames_overlap));

	double **frames;
	if (!rest_samples) {
		frames = create_frames_tab(num_frames,frame_length);

		for (int i=0; i<num_frames; i++){

			for (int j=0; j<(int)frame_length; j++){

				REAL(frames[i],j) = REAL(data,j+i*(int)frame_step);
				IMAG(frames[i],j) = IMAG(data,j+i*(int)frame_step);
				
			}
		} 
	}

	//We modify num_frames if necessary to avoid truncating samples from the signal
	else {
		num_frames++;
		frames = create_frames_tab(num_frames,frame_length);

		for (int i=0; i<num_frames; i++){

			for (int j=0; j<(int)frame_length; j++){
				
				if(i==num_frames-1){
					if (j<rest_samples) {
						REAL(frames[i],j) = REAL(data,j+i*(int)frame_step);
						IMAG(frames[i],j) = IMAG(data,j+i*(int)frame_step);
					}
					else {
						REAL(frames[i],j) = 0.0;
						IMAG(frames[i],j) = 0.0;
					}
				}
				else{
					REAL(frames[i],j) = REAL(data,j+i*(int)frame_step);
					IMAG(frames[i],j) = IMAG(data,j+i*(int)frame_step);
				}
				
			}
		}
	}
	*outframe_step =(int)frame_step;
	*outnum_frames = (int)num_frames;
	*outframe_length = (int)frame_length;
	printf("num_frames %d\n",num_frames);
	return (frames);
}