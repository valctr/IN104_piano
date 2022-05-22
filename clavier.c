#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include "dico_freq_pos.c"
#include "dico_freq_pos.h"
#include "num_touche.c"
#include "num_touche.h"
#include "dico_blanc.c"
#include "dico_blanc.h"
#include "find_dicho.c"
#include "find_dicho.h"
#include "main.c"
#include "main.h"

#define SCREENWIDTH 990
#define SCREENHEIGHT 800

// gcc -Wall -Wfatal-errors clavier.c $(sdl2-config --cflags --libs)
void SDL_ExitWithError1(const char* message);
void SDL_ExitWithError2(const char* message, SDL_Window* window);
void SDL_ExitWithError3(const char* message, SDL_Window* window, SDL_Renderer* renderer);



int  main() {

//----------- Gestion de l'affichage du clavier --------------//

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
      
//Lancement SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
        SDL_ExitWithError1("Erreur lancement SDL");  

//Création fenêtre 
    int largeur=990;
    window = SDL_CreateWindow("Clavier", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largeur, 800, 0);
    if (window == NULL) 
        SDL_ExitWithError1("Echec ouverture fenêtre");
    
    
// Création rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) 
        SDL_ExitWithError2("Echec rendu", window);
       
    int i; 
    SDL_Rect rectangle;    
    
    // Touches Blanches
    
    int N_keys = 52;
    int w_key = 18;
    int h_key = 100;
    i = 0;

    if (SDL_SetRenderDrawColor(renderer, 245, 245, 245, SDL_ALPHA_OPAQUE) != 0) 
        SDL_ExitWithError3("Chargement couleur impossible", window, renderer);
        
    for (i = 0; i < N_keys; i++) {
    
        rectangle.x = 1 + i * (w_key + 1);
        rectangle.y = 450;
        rectangle.w = w_key;
        rectangle.h = h_key;
        
    
        if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
            SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);     
    }
      
    // Touches Noires
    
    int w_keyp = 12;
    int h_keyp = 65;
    i = 3;
    
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) {
        SDL_ExitWithError3("Chargement couleur rendu impossible", window, renderer);}

        // Unique
        rectangle.x = 1 + 1 * (w_key + 1) - 2*w_key/5;
        rectangle.y = 450;
        rectangle.w = w_keyp;
        rectangle.h = h_keyp;
        if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
            SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);
    
    while (i < N_keys-1) {

        // Paires
        rectangle.x = 1 + (i) * (w_key + 1) - 2*w_key/5;
        rectangle.y = 450;
        rectangle.w = w_keyp;
        rectangle.h = h_keyp;
        
    
        if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
            SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);
        
        rectangle.x = 1 + (i + 1) * (w_key + 1) - 3*w_key/10;
        rectangle.y = 450;
        rectangle.w = w_keyp;
        rectangle.h = h_keyp;
        
        if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
            SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);
        
        // Triplets
        rectangle.x = 1 + (i + 3) * (w_key + 1) - w_key/2;
        rectangle.y = 450;
        rectangle.w = w_keyp;
        rectangle.h = h_keyp;
        
        if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
            SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);
        
        rectangle.x = 1 + (i + 4) * (w_key + 1) - w_key/3;
        rectangle.y = 450;
        rectangle.w = w_keyp;
        rectangle.h = h_keyp;
        
        if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
            SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);
        
        rectangle.x = 1 + (i + 5) * (w_key + 1) - w_key/4;
        rectangle.y = 450;
        rectangle.w = w_keyp;
        rectangle.h = h_keyp;
        
        if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
            SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);
        
        i = i + 7;    
    }
    
    // Liseret Blanc
     
    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)         
        SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);
    
    rectangle.x = 1;
    rectangle.y = 449;
    rectangle.w = largeur;
    rectangle.h = 1;
    
    if (SDL_RenderFillRect(renderer, &rectangle) != 0) 
        SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);
    
   
    // Liseret Noir 50 50 50
    
    if (SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError3("Chargement couleur rendu impossible", window, renderer);
        
    rectangle.x = 1;
    rectangle.y = 447;
    rectangle.w = largeur;
    rectangle.h = 2;
    
    if (SDL_RenderFillRect(renderer, &rectangle) != 0)
        SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);
      


//----------- Coloration de la touche jouée --------------//


    if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE) != 0) {
        SDL_ExitWithError3("Chargement couleur rendu impossible", window, renderer);}

    float f=main1();

    unsigned int numero_de_touche = num_touche(f);
    //printf("%d\n",numero_de_touche);
    if (numero_de_touche==-1) { printf("Cette note ne peut pas être jouée par un piano !\n"); exit(EXIT_FAILURE);}

    float* tab_clavier = dico_freq_pos(N_keys, w_key, h_key); // liste des abscisses


    rectangle.x = tab_clavier[numero_de_touche*2+1]; // abscisse de la touche
    //printf("%d\n" , rectangle.x);

    // Liste des abscisses blancs

    int* tab_blanc=dico_blanc(N_keys);


    // On teste si la touche est noire ou blanche et on dessine le rectangle en conséquence

    if (find_dicho (tab_blanc,  numero_de_touche, 0, N_keys)) {
        rectangle.y = 450;
        rectangle.w = w_key;
        rectangle.h = h_key;
        if (SDL_RenderFillRect(renderer, &rectangle) != 0) {
            SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);

        }

    }
    else {
        rectangle.y = 450;
        rectangle.w = w_keyp;
        rectangle.h = h_keyp;
        if (SDL_RenderFillRect(renderer, &rectangle) != 0) {
            SDL_ExitWithError3("Dessin rectangle impossible", window, renderer);
        }
    }

    //Temps d'affichage

    SDL_RenderPresent(renderer);
    SDL_Delay(8000);

    // Libérations
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();  
    return(EXIT_SUCCESS);
}


//----------- Fonctions secondaires --------------//


void SDL_ExitWithError1(const char* message) {
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();         
    exit(EXIT_FAILURE);  
}

void SDL_ExitWithError2(const char* message, SDL_Window* window) {
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();         
    exit(EXIT_FAILURE);
}

void SDL_ExitWithError3(const char* message, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();         
    exit(EXIT_FAILURE);   
}
