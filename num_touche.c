//----------- Determination du numéro de la touche jouée --------------//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>



// fonction renvoyant le numero de la touche jouee à partir de la freq jouee

unsigned int num_touche(float f) {

    double x=1.0/12;
    float r = pow(2.00,x); // rapport entre les freq
    float f0 = 27.5 ; // note de reference, premiere touche du clavier (note la plus grave)

    for(int i=0 ; i<88 ; ++i) {
        if (abs(f-f0*pow(r,i))<pow(r,i)) {
            return i;
        }
    }
    return -1 ;
    // on retourne -1 si la fréquence ne correspond pas à une fréquence jouée par un piano
}
