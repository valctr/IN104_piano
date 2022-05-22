/*
//----------- Recherche séquentielle (ne sert plus à rien) --------------//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

bool find_word_naive (float* tab, float value, int size_tab) {
  
  for(int i=0;i<size_tab;++i){
    
    if(tab[i]==value) {  return 1;   }
  }
    return 0;

}

*/

//----------- Recherche par dichotomie --------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




bool find_dicho (int* tab, int value, int left, int right)
{
  int mid ;
  //int left=0;
  //int right = size_tab;

  if (left > right) return (false) ;
  mid = (left + right) / 2 ;

  if (value == tab [mid]) { return (true); }     /* word == words[mid] */

  if (value < tab [mid]) return (find_dicho (tab, value, left, mid - 1)) ;

  return (find_dicho (tab, value, mid + 1, right)) ;
}

/*
int main() {
  if(find_dicho(dico_blanc(52),57,0,52)) { printf("%s \n", "trouvé");}
  else { printf("%s \n", "non trouvé");}
  return 1;

}
*/
/*
int main (int argc, char *argv[])
{
  char buffer[256] ;
  char **words ;






  printf ("Number of words: %d.\n", num_words) ;

  while (gets (buffer)) {
    if (find_word_dicho (words, buffer, 0, num_words)) printf ("Found :)\n") ;
    else printf ("Not found :(\n") ;
  }

  return (0) ;
}
*/
