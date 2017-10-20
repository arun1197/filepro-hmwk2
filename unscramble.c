#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(char*)a - *(char*)b );
}

int main(int argc, char* argv[]) {
  char jumbles[21];
  char dictionary[21];
  char dToSort[21];

  int flag=1;

  FILE* dict=fopen(argv[1],"r");;
  FILE* jumble=fopen(argv[2],"r");;

  if(argc > 1){
    while(fgets(jumbles,20,(FILE*)jumble)!=NULL){
      jumbles[strlen(jumbles)-1]='\0';
      printf("%s:",jumbles);
      qsort(jumbles,strlen(jumbles),sizeof(char),cmpfunc);
      while(fgets(dictionary,20,(FILE*)dict)!=NULL){
        dictionary[strlen(dictionary)-1]='\0';
        if(strlen(dictionary)==strlen(jumbles)){//this line saved my life . From 3.2 to 0.5 woahhahah
          memcpy(dToSort,dictionary,sizeof(dictionary));
          qsort(dToSort,strlen(dToSort),sizeof(char),cmpfunc);
          if(strcmp(dToSort,jumbles)==0){
            flag=0;
            printf(" %s", dictionary);
          }
        }
        //memset(dToSort, '\0', 21); save some much time if i dont use memset
        //memset(dictionary, '\0',21);
      }
      if(flag==1){
        printf(" %s", "NO MATCHES");
      }
      flag=1;
      // Move the file pointer to the start.
      fseek(dict,0,SEEK_SET);
      putchar('\n');
      // memset(jumbles,'\0',21);
    }
    fclose(dict);
    fclose(jumble);
  }
}
