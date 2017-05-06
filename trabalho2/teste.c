#include <stdio.h>

int leftChild(int proc){
    return proc * 2 + 1;
}

int rightChild(int proc){
    return proc * 2 + 2;
}

void main(){
  int leftProc = leftChild(0);
  int rightProc = rightChild(0);
  printf("%d \n",leftProc);
  printf("%d \n",rightProc);
}