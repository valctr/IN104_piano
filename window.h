#ifndef _WINDOW_H
#define _WINDOW_H

double hann(int i, int N);
double hamming(int i, int N);
double** window(double **frames,int num_frames, int frame_length, char *window_name);

#endif