#ifndef _MON_MODULE_H
#define _MON_MODULE_H

struct wavfile //définit la structure de l entete d un wave
{
char id[4]; // doit contenir "RIFF"
int totallength; // taille totale du fichier moins 8 octets
char wavefmt[8]; // doit etre "WAVEfmt "
int format; // 16 pour le format PCM
short pcm; // 1 for PCM format
short channels; // nombre de channels
int frequency; // frequence d echantillonage
int bytes_per_second; // nombre de octets par secondes
short bytes_by_capture; // nombre de bytes par echantillon
short bits_per_sample; // nombre de bit par echantillon
char data[4]; // doit contenir "data"
int bytes_in_data; // nombre de bytes de la partie data
};


double** open_wav();
#endif