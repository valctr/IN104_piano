#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

/*Calcul de la fréquence maximisant le produit harmonique spectral (retourne également cette valeur maximale dans max_amp)*/
int argmax(double *modules, int frame_length,int harmonic_nb, int samplingfreq, double *max_amp,double df){
	
	int argmax_f;
	double res;
	double max_res = 0.0;

	/*On parcourt toutes les fréquences pour effectuer le calcul*/
	for (int i=1; i<frame_length; i++){
		res = 0.0;
		int j = 1;

		if(modules[i]>0.1){
			/*Cette boucle while constitue le calcul à proprement parler*/
			while ((j<harmonic_nb+1)&&(j*i<frame_length)) {
				if(modules[j*i]>0.1) res+= log10(modules[j*i]);
				j++;
			}

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

/*Suppression des fréquences autour d'une fréquence désignée (le booléen remove_harmonics communique au programme s'il doit également supprimer les harmoniques)*/
void removefreq(double *modules, int f, double df, int frame_length, bool remove_harmonics, double alpha){

	int min, max;

	/*Cas où l'on supprime aussi les harmoniques*/
	if (remove_harmonics){

		int i=1;
		while (i*f<frame_length){
			/*Calcul des bornes de l'intervalle*/
			min = (int)(i*f*(1-alpha))/df;
			max = (int)(i*f*(1+alpha))/df;

			if (max>frame_length-1) max = frame_length-1; //cas particulier où la borne supérieure dépasse le cadre de l'image
			for (int j=min;j<max+1;j++) modules[j]=0.0;
			i++;
		}
	}

	/*Cas où l'on ne supprime qu'autour de la fréquence désignée*/
	else {
		min = (int)(f*(1-alpha))/df;
		max = (int)(f*(1+alpha))/df;
		if (max>frame_length-1) max = frame_length-1;
		for (int j=min;j<max+1;j++) modules[j]=0.0;
	}
}

/*Calcul des fréquences de toutes les notes jouées pour chacune des images*/
int** fundamentals(double **frames, int num_frames, int frame_length,int harmonic_nb, int samplingfreq, double alpha){
	
	/*Creation du tableau de résultat et allocation de mémoire*/
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


	double df = ((double)samplingfreq)/((double)frame_length); //Calcul du pas de fréquence df

	/*Boucle parcourant les images*/
	for (int i=0; i<num_frames; i++){
		int f;
		double max_amp;

		/*Si l'image n'est pas vide*/
		if (frames[i]!=NULL){
			/*Création d'un tableau contenant les modules de la FFT de l'image*/
			double *modules=malloc(sizeof(double)*frame_length);
			for (int k=0; k<frame_length; k++) modules[k] = square_module(frames[i],k);

			f = argmax(modules,frame_length,harmonic_nb,samplingfreq,&max_amp,df);				//Calcul du fondamental f0max de la note prépondérante, de plus forte intensité
			
			/*On définit ici la limite d'amplitude pour les fréquences : si la perte d'intensité est supérieure à 3dB par rapport à f0max, on ne garde pas la fréquence*/
			double min = max_amp-3.0;															
			
			/*On récupère des fréquences tant que l'on a assez de places pour les accueillir, tant que les fréquences sont issues du piano et tant que la condition décrite ci-dessus est respectée*/ 
			int j=1;
			while ((max_amp>min) && (f>20) && (f<4500) && (j<89) && (modules[(int)(f/df)]>0.1)){

				/*Si la fréquence semble effectivement être jouée par le piano*/
				if ((f>20) && (f<4500) && (max_amp>min)) {
					frames_fundamentals[i][j] = f;												//On conserve la fréquence
					removefreq(modules,f,df,frame_length,1,alpha);								//On supprimer la fréquence et toutes ses harmoniques 
					j++;
				}
				/*Sinon on retire cette fréquence pour qu'elle ne vienne pas parasiter la suite des calculs*/
				else removefreq(modules,f,df,frame_length,0,alpha);
				f = argmax(modules,frame_length,harmonic_nb,samplingfreq,&max_amp,df);			//Nouveau calcul de la fréquence de la nouvelle note de plus forte intensité
			}

			frames_fundamentals[i][0]=j-1;														//On conserve le nombre de fréquences par images pour la suite
			free(modules);
		}
		/*Si l'image est vide, la réponse l'est également*/
		else frames_fundamentals[i] = NULL;
	}


	return(frames_fundamentals);
}

/*Correction du tableau de fréquences*/
void correct(int **frames_fundamentals,int num_frames, int frame_length, double alpha){

	for (int i=0;i<num_frames;i++){

		/*Si l'image n'est pas vide et qu'il y a au moins une fréquence pour l'image*/
		if ((frames_fundamentals[i]!=NULL)&&(frames_fundamentals[i][0]>1)){
			int length = frames_fundamentals[i][0]-1;
			int count=0;

			/*tmp est un tableau qu'on va modifier au fur et à mesure que l'on détermine si chaque fréquence est seule dans son voisinage*/ 
			int tmp[88];
			int length_tmp = length-count;
			for (int j=0;j<length;j++) tmp[j]=frames_fundamentals[i][j+2];

			/*Pour chaque fréquence, on détermine s'il est seule dans le voisinage ou non*/
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
				/*Si on ne trouve pas la fréquence dans le voisinage, on la retire*/
				if (!c) {
					for (int k=j; k<length_tmp-1;k++) {
						tmp[k]=tmp[k+1];
					}
					frames_fundamentals[i][0]-=1;
					count+=1;
				}
			}

			/*On réassigne le nouveau tableau*/ 
			if (length_tmp>0){
				for (int j=0;j<length_tmp;j++) frames_fundamentals[i][j+2]=tmp[j];
			}

		}
	}
}
