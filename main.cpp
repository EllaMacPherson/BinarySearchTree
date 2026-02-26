#include <iostream>
#include <fstream>
#include "node.h"

using namespace std;

// Tree building
void insert(node* current, node*& root, int value);
void print(int depth, node* current);
void search(int s, node* current, bool& found);

int main(){

  int input = 0; // Number to be added currently

  string command = ""; // What the user wants to do
  node* root = NULL; // Root of the tree

  while(true){

    command.clear();
    
    cout<<"Enter ADD, FILE ADD, PRINT, SEARCH"<<endl;

    getline(cin, command);
    
    if(command == "FILE ADD" || command == "file add"){
      string filename = ""; // Stores file name

      cout<<"Please enter name of file: "<<endl;
      getline(cin, filename);
    
      ifstream inputFile;
      inputFile.open(filename);
    
      if(!inputFile.is_open()){
	cout<<"file doesnt exist"<<endl;
      }
      else{
	while(inputFile >> input){
	  // Add it to the tree
	  insert(root, root, input);
	}
      }
    }
    
    if(command == "add" || command == "ADD"){
      cout<<"Enter number to add"<<endl;
      cin>>input;
      cin.ignore();
      insert(root, root, input);
    }
    
    if(command == "print" || command == "PRINT"){
      /*cout<<"ROOT: "<< root->value<<endl;
      if(root->right != NULL){
	cout<<"ROOT RIGHT: " <<root->right->value<<endl;
      }
      if(root->left != NULL){
	cout<<"ROOT LEFT: " <<root->left->value<<endl;
      }*/

      print(0, root);
    }

    if(command == "search" || command == "SEARCH"){
      cout<<"What number are you searching for?"<<endl;
      int s = 0;
      cin>>s;
      cin.ignore();
      bool found = false;
      if(root != NULL){
	search(s, root, found);
	if(found == false){
	  cout<<"Your number is not in the tree.."<<endl;
	}
      }
      else{
	cout<<"Tree is empty"<<endl;
      }
    }

  }
  
}

void search(int s, node* current, bool& found){
  if(current->right != NULL){
    search(s, current->right, found);
  }

  if(current != NULL){
    if(current->value == s){
      cout<<"Your number is in the tree"<<endl;
      found = true;
      return;
    }
  }

  // move all way to the left side of the tree
  if(current->left != NULL){
    search(s, current->left, found);
  }
}

void print(int depth, node* current){
  //  cout<<"running real pring func"<<endl;
  //move all the way to the right of the tree

  if(current->right != NULL){
    print((depth + 1), current->right);
  }

  //tab over depth times!
  for(int i = 0; i < depth; i++){
    cout<<"\t";
  }

  if(current != NULL){
    cout<<current->value<<endl;
  }

  // move all way to the left side of the tree
  if(current->left != NULL){
    print((depth + 1), current->left);
  }
}

void insert(node* current, node*& root, int value){

  // On first call
  if(root == NULL){
    // Create a root node
    root = new node(NULL, NULL, value);
    return;
  }

  /*  // If the current node has no left or right
  if(current->right == NULL && current->left == NULL){
    // Check if value is greater than current value
    if(current->value < value){
     
    }
    // If value is less than current value
    else{ 
      current->left = new node(NULL,NULL,value);
    }
  }*/

  if(current->value < value){
    // recursive down to right till NULL
    if(current->right != NULL){
      insert(current->right, root, value);
    }
    else{
      current->right = new node(NULL, NULL, value);
    }
  }

  if(current->value >  value){
    //recursive down to left till NULL
    if(current->left != NULL){
      insert(current->left, root, value);
    }
    else{
      current->left = new node(NULL, NULL, value);
    }
  }
  
}
