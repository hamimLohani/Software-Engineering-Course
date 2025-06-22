#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
  int n;
  printf("Enter number : ");
  scanf("%d",&n);
int bi,dec=0,sum=0;
  for (int i = n; i > 0; i--)
  {
     bi = rand()%2;
     sum = sum*10 + bi;
     dec = dec + bi*pow(2,i-1);
     
  }
    printf("%d-%d\n",dec,sum);

int hex,num=0;
  for (int i = 0; dec!=0; i++)
  {
    hex=dec%16;
    dec=dec/16;
    //printf("-%d-",dec);
    if(hex<10) printf("%d",hex);
    else printf("%c",hex+55);
  }

  for (int i = 0; ; i++)
  {
    /* code */
  }
  
  
}