//sum of array without loop

#include<stdio.h>

int func(int arr[],int size);
int fun(int arr[],int size);

int main(){
  int arr[]={1,2,3,4,5,6,7,0};
  int size = sizeof arr / sizeof arr[0];

  printf("%d\n",fun(arr,size));

}
int func(int arr[],int size){
  static int i=0,sum=0;
  if(i!=size-1){
    sum = sum + arr[i];
    i++;
    func(arr,size);
  }
  return sum;
}
int fun(int arr[],int size){
  if(size == 0){
    return 0;
  }else{
    return arr[size-1]+fun(arr,size-1);
  }
}