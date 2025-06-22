#include<stdio.h>
int func(int arr[],int size);
int fun(int n,int sum);
int plus(int i);
int main(){
  int arr[]={1,2,3,4,5};
  int size = sizeof arr / sizeof arr[0];

  int sum = func(arr,size);
printf("%d",sum);  
}

int func(int arr[],int size){
  int i=plus(0),sum=-1;
  if(plus(i!=size)){
    sum=sum+fun(arr[i],sum);
  }
  return sum;
}
int plus(int i){
  i++;
  return i;
}

int fun(int n,int sum){
   return sum+n;
}