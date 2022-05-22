#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//----------- Fonction de tri --------------//


void fct_tricroitableau(float tableau[], int tailletableau)
{
     float valeurtemporaire;
     for (int i=0; i<tailletableau; i++)
     {
        for(int j=i; j<tailletableau; j++)
        {
            if(tableau[j]<tableau[i])  /* si on inverse le signe d'inégalité
                                          on aura le tri décroissant */
            {
                valeurtemporaire = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = valeurtemporaire;
            }
        }
     }
}

//----------- Dictionnaire des fréquences et des abscisses --------------//

float* dico_freq_pos(int N_keys, int w_key, int h_key) {

    double x=1.0/12;
    float r = pow(2.00,x);
    float f0 = 27.5;
	float* abscisse = malloc((2*N_keys+1)*sizeof(float));
    float* abscisse_sans0 = malloc(88*sizeof(float));
	float* dico = malloc(2*88*sizeof(float)); // tableau avec en pair la frequence, impair l'abscisse de touche)

    for(int i=0 ; i<N_keys ; ++i) {
    	abscisse[i]=1 + i * (w_key + 1); } // touches blanches 

        // Touche noire unique

        abscisse[N_keys] = 1 + 1 * (w_key + 1) - 2*w_key/5;

    int i=3;

    while (i < N_keys-1) {

        // Paires
        
        abscisse[N_keys+i-2] = 1 + (i) * (w_key + 1) - 2*w_key/5;
        abscisse[N_keys+i-1] = 1 + (i + 1) * (w_key + 1) - 3*w_key/10;

        
        // Triplets
        
        abscisse[N_keys+i] = 1 + (i + 3) * (w_key + 1) - w_key/2;
        abscisse[N_keys+i+1] = 1 + (i + 4) * (w_key + 1) - w_key/3;
        abscisse[N_keys+i+2] = 1 + (i + 5) * (w_key + 1) - w_key/4;
        //printf("%f\n %f\n  %f\n",abscisse[N_keys+i],abscisse[N_keys+i+1],abscisse[N_keys+i+2]);
   
        i = i + 7;
        
    }
    int k=0;
    for(int i=0 ; i<2*N_keys+2 ; ++i) {
        if (abscisse[i]!=0.0) { 
            abscisse_sans0 [k]=abscisse[i] ; 
            //printf("%f\n", abscisse_sans0[k]);
             ++k;
        }   
    }
    
    fct_tricroitableau(abscisse_sans0, 88); // on trie le tableau
    for(int i=0 ; i<88 ; ++i) {
       //printf("%f \n" , abscisse_sans0[i]);
    }

    // on insère les positions dans le dico, aux cases correspondant au fréquences

    for(int i=0 ; i<88 ; ++i) {
        dico[2*i] = f0*pow(r,i);
        dico[2*i+1] = abscisse_sans0[i];
        //printf("%f \n , %f \n", dico[2*i], dico[2*i+1]);
        }
    free(abscisse);
    free(abscisse_sans0);
    free(dico);
    return dico;
}
/*
int main() {
    int N_keys = 52;
    int w_key = 18;
    int h_key = 100;

    float* dico = dico_freq_pos( N_keys, w_key, h_key);
    
  //  for(int i=0 ; i<2*N_keys+12 ; ++i) {
    //    printf("%f \n , %f \n", dico[2*i], dico[2*i+1]);
      //  }

    return 1;
}


*/
