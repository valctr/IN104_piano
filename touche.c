#include <stdio.h>
#include <math.h>



// fonction renvoyant le numero de la touche jouee à partir de la freq jouee

unsigned int num_touche(float f) { 
    double x=1.0/12;
    printf( " x = %f\n", x);
    float r = pow(2.00,x); // rapport entre les freq
    printf( "r = %f\n", r);
    //float epsilon = r/2 ; // tolerance entre la freq detectee et celle de la touche
    float f0 = 27.5 ; // note de reference, premiere touche du clavier

    for(int i=0 ; i<88 ; ++i) {
    	if (f-f0*pow(r,i)<pow(r,i)) {
    		return i;
    	}
    }
    return -1 ;
}

int main (){
    float f = 58;
    printf("%d \n", num_touche(f));

}