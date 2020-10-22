#include<stdio.h>
#include<stdlib.h>


long long int sumAndProduct(int a,int b,int* sum,int* prod){
  *sum= a + b;
  *prod= a * b;
}

int main(int argc,char *argv[]){
  //int x = 5,y=12,sum,prod;
  //
  int sum,prod
  int val1 = atoi(argv[1]);
  int val2=atoi(argv[2]);

  //sumAndProduct(x,y,&sum,&prod);
  printf("la suma es %d y el producto es %d",sum,prod,sumAndProduct(val1,val2,&sum,&prod)); 
  return 0;
}
