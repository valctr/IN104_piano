#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>
#include "tools.h"
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

/*Calcul de la FFT des images avec GSL*/
double** fft(double **frames, int num_frames, int frame_length, int size){

	double **frames_fft = create_frames_tab(num_frames,size);

	for (int i=0; i<num_frames; i++){
		/*Mise en forme des données*/
		double tmp[2*frame_length];
		for (int j=0; j<frame_length; j++) {
			REAL(tmp,j) = REAL(frames[i],j);
			IMAG(tmp,j) = IMAG(frames[i],j);
		}


		if (test_zero(frames[i],frame_length)){						//On vérifie que les échantillons de l'image ne soient pas tous nuls
			gsl_complex_packed_array frame_fft = tmp;
			gsl_fft_complex_radix2_forward(frame_fft, 1, size); 	//frame_fft devient un tableau complexe de longueur size
			for(int j=0;j<size;j++) frames_fft[i][j] = frame_fft[j];
		}
		else frames_fft[i]=NULL;

	}

	return(frames_fft);
}