#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int args, char *argv[])  {
  int c;
  int counterRemainingSpace=0;
  // char cmd[] = argv[1]; -> error: array initializer
  //from errormsg use strcmp to compare argv[1] and '-d'
  int numberOfSpaces = atoi(argv[2]);
  while((c=getchar())!=EOF) {
    if(args > 0){
      if(strcmp(argv[1],"-d")==0){
        if(c=='\t'){
          for(int i=0;i<numberOfSpaces;++i){
            printf("%c", ' ');
          }
        } else {
          printf("%c", c);
        }
      }
      else{
        if(c==' '){
          counterRemainingSpace++;
          if(counterRemainingSpace==numberOfSpaces){
            printf("%c", '\t');
            counterRemainingSpace=0;
          }
        } else {
          for(int i=0;i<counterRemainingSpace;i++) {
            printf("%c",' ');
          }
          printf("%c", c);
          counterRemainingSpace=0;
        }
      }
    }
  }
}
