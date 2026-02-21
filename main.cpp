#include <iostream>
#include "node.h"

using namespace std;

// Tree building
void insert(node* current, node*& root, int value);

int main(){

  int input = 0;
  node* root = NULL; // Root of the tree

  cout<<"Enter a number you'd like to add to the tree"<<endl;
  cin>>input;

  // Add it to the tree
  insert(root, root, input);

  cout<<root->value<<endl;
  
}

void insert(node* current, node*& root, int value){

  // On first call
  if(root == NULL){
    // Create a root node
    root = new node(NULL, NULL, value);
  }
}
