//----------- Dictionnaire des numéros des touches blanches --------------//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Fonction renvoyant un tableau contenant les numéros des touches blanches

int* dico_blanc(int N_keys) {

   
	int* T = malloc(N_keys*sizeof(int));
	T [0] = 0; T [1]=2;	T [2]=3;	T [3]=5;	T [4]=7; 	T [5]=8;	T [6]=10;	T [7]=12; T [8]=14; T [9]=15;
	T [10] = 17; T [11]=19;	T [12]=20;	T [13]=21;	T [14]=24; 	T [15]=26;	T [16]=27;	T [17]=29; T [18]=31; T [19]=32;
	T [20] = 34; T [21]=36;	T [23]=38;	T [23]=39;	T [24]=41; 	T [25]=43; T [26]=44; T [27]=46; T [28]=48; T [29]=50;
	T [30] = 51; T [31]=53;	T [32]=55;	T [33]=56;	T [34]=58; 	T [35]=60;	T [36]=62;	T [37]=63; T [38]=65; T [39]=67;
	T [40] = 68; T [41]=70;	T [42]=72;	T [43]=74;	T [44]=75; 	T [45]=77;	T [46]=79;	T [47]=80; T [48]=82; T [49]=84;
	T [50] = 86; T [51]=87;

    return T;
}


