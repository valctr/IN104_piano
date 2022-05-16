#ifndef _FRAMING_H
#define _FRAMING_H

double** framing(double *data, int fs, double win_len, double win_hop, int signal_length, int *outframe_length, int *outnum_frames, int *outframe_step);

#endif