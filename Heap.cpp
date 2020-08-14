#include "Heap.h"
#include <iostream>

//Author: Thomas Wang

Heap::Heap(){
  numItems = 0;
}

void Heap::enqueue(PrintJob *pJ){
  if(!this->isFull()){
    if(this->isEmpty()){
      this->arr[numItems] = pJ;
      numItems++;
    } else {

    int percUp = numItems;
    // checks if the parent node is less than the current node
    // if so, it violates the max-heap property
    
    while ((percUp > 0) && (this->arr[(percUp - 1) / 2]->getPriority() < pJ->getPriority())){
      this->arr[percUp] = this->arr[(percUp - 1) / 2];
      percUp = (percUp - 1) / 2;
    }
    this->arr[percUp] = pJ;
    numItems++;
    }
  }
}

void Heap::dequeue(){
  if(!isEmpty()) { 
    if(this->numItems == 1){
      this->arr[0] = 0;
    } else{
      this->arr[0] = this->arr[numItems - 1];
      trickleDown(0);
    }
    this->numItems--;
  }
}

PrintJob* Heap::highest(){
  if(!this->isEmpty()){
    return this->arr[0];
  } else {
    return 0;
  }
}

void Heap::print(){
  if(numItems != 0){
    cout << "Priority: " << this->arr[0]->getPriority() << ", ";
    cout << "Job Number: " << this->arr[0]->getJobNumber() << ", ";
    cout << "Number of Pages: " << this->arr[0]->getPages() << endl;
  } 
}

void Heap::trickleDown(int index){
  int childIndex = 2 * index + 1;
  PrintJob *temp = this->arr[index];
  while(childIndex < this->numItems){
    // find max among node and it's children
    PrintJob *max = temp;
    int maxIndex = -1;

    // i + childIndex makes sure we're only checking the 2 children of a parent node
    // then make sure that the indices are not out of bound 
    for(int i = 0; i < 2 && i + childIndex < numItems; i++){
      if(this->arr[i + childIndex] > max){
        max = this->arr[i + childIndex];
        maxIndex = i + childIndex;
      }
    }
    
    if(max == temp){
      return;
    } else {
      this->arr[maxIndex] = this->arr[index];
      this->arr[index] = max;
      index = maxIndex;
      childIndex = 2 * index + 1;
    }
  }
}