#include <stdbool.h>
#ifndef _TOOLS_H
#define _TOOLS_H

double** create_frames_tab(int num_frames,int frame_length);
bool test_zero(double *frame, int frame_length);
double square_module(double *data, int ind);
bool element_found(int elem,int **frames,int ind1,int ind2,int dir,double alpha);
void printtextdouble(char* fname, double *frame, int frame_length);
void printtextint(char* fname, int *frame, int frame_length);

#endif