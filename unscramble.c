#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(char*)a - *(char*)b );
}

int main(int argc, char* argv[]) {
  char dictionary[20];
  char jumbles[20];

  char jToSort[20];
  char dToSort[20];

  int flag=1;

  FILE *dict=fopen(argv[1],"r");
  FILE *jumble=fopen(argv[2],"r");

  while(fgets(jumbles,20,jumble)!=NULL){
    strncpy(jToSort,jumbles,sizeof(jumbles));
    for(int i=0;i<20;++i){
			if(jumbles[i]!='\n'){
				putchar(jumbles[i]);
			}
    }
    printf(": ");
    qsort(jToSort,strlen(jToSort),sizeof(char),cmpfunc);
    while(fgets(dictionary,20,dict)!=NULL){
      strncpy(dToSort,dictionary,sizeof(dictionary));
      qsort(dToSort,strlen(dToSort),sizeof(char),cmpfunc);
      if(strcmp(dToSort,jToSort)==0){
        flag=0;
        for(int i=0;i<20;++i){
          if(dictionary[i]!='\n'){
            putchar(dictionary[i]);
          }
        }
        putchar(' ');
      }
      memset(dToSort, '\0', 20);
      memset(dictionary, '\0',20);
    }
    if(flag==1){
      printf("%s", "NO MATCHES");
    }
    flag=1;
    // Move the file pointer to the start.
    fseek(dict,0,SEEK_SET);
    putchar('\n');
  }
  fclose(dict);
  fclose(jumble);
}
