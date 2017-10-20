#include <stdio.h>
#include <ctype.h>
#include <string.h>

int generateHistogram() {
 int c,max;
 int alphabets[26];

 for(int i=0;i<26;++i) alphabets[i]=0;

 while((c=getchar())!=EOF) {
    if(isalpha(c)) ++alphabets[tolower(c)-97];
 }

 max=0;
 for(int i=0;i<26;++i) {
   if(alphabets[i]>max) max=alphabets[i];
 }
 for(int i=max;i>0;--i){
   for(int j=0;j<26;++j){
     if(alphabets[j]==i){
       putchar('*');
       alphabets[j]=i-1;
     }else{
       putchar(' ');
     }
   }
   printf("\n");
 }
 printf("abcdefghijklmnopqrstuvwxyz\n");
 return 0;
}

int main() {
  generateHistogram();
}
