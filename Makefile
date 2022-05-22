#Makefile

projet : main.c wav.c tools.c window.c framing.c fundamentals.c
	gcc -Wall main.c wav.c tools.c window.c framing.c fundamentals.c fft.c -lgsl
