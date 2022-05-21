#ifndef _FUNDAMENTALS_H
#define _FUNDAMENTALS_H

int argmax(double *frame, int frame_length,int harmonic_nb, int samplingfreq, double *max_amp,double df);
void removefreq(double *frame,int f, double df, int frame_length, bool remove_harmonics, double alpha);
int** fundamentals(double **frames, int num_frames, int frame_length,int harmonic_nb, int samplingfreq, double alpha);
void correct(int **frames_fundamentals,int num_frames, int frame_length,double alpha);

#endif