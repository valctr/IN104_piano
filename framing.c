#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

/*Fonction de découpage su signal en images*/
double** framing(double *data, int fs, double win_len, double win_hop, int signal_length, int *outframe_length, int *outnum_frames, int *outframe_step, int fft_size){

	/*Initialisation du nombre d'échantillons par image (frame_length), du pas pour passer d'une image à la suivante (frame_step), du recouvrement d'échantillons entre image*/
	double frame_length = win_len * (double)fs;
	double frame_step = win_hop * (double)fs;
	double frames_overlap = frame_length - frame_step;
	printf("frame_length %f\n",frame_length);
	printf("frame_step %f\n",frame_step);
	printf("frames_overlap %f\n",frames_overlap);
	printf("\ntaille de la FFT : %d\n",fft_size);

	/*Calcul du nombre d'images nécessaire, et du nombre d'échantillons restant suite au découpage*/
	int num_frames = (int)(abs(signal_length - frames_overlap) / abs(frame_length - frames_overlap));
	int rest_samples = (int)(abs(signal_length - frames_overlap) % abs(frame_length - frames_overlap));

	/*Dnas le cas où le reste est nul, on crée le tableau contenant les images et on assigne pour chacune d'entre elles les données des échantillons*/
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

	/* S'il reste des échantillons, on rajoute une image contenant ces échantillons, puis on complète aved des zéros (zero paddling)*/
	else {
		num_frames++;
		frames = create_frames_tab(num_frames,frame_length);

		for (int i=0; i<num_frames; i++){

			for (int j=0; j<(int)frame_length; j++){
				
				//Image ajoutée
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

				//Autres images
				else{
					REAL(frames[i],j) = REAL(data,j+i*(int)frame_step);
					IMAG(frames[i],j) = IMAG(data,j+i*(int)frame_step);
				}
				
			}
		}
	}

	/*Retour des variables utiles à la suite du programme*/
	*outframe_step =(int)frame_step;
	*outnum_frames = (int)num_frames;
	*outframe_length = (int)frame_length;

	printf("Nombre d'images : %d\n",num_frames);

	return (frames);
}