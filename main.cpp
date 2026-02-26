#include <iostream>
#include <fstream>
#include "node.h"

using namespace std;

// Tree building
void insert(node* current, node*& root, int value);
void print(int depth, node* current);
void search(int s, node* current, bool& found);
void deletion(int d, node* current, node* parent);
node* find(node* current, int d);

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

    if(command == "delete" || command == "DELETE"){
      cout<<"What number are you looking to delete?"<<endl;
      int d = 0;
      cin>>d;

      deletion(d, root, root);
    }

  }
  
}

void deletion(int d, node* current, node* parent){

  if(current->right != NULL){
    deletion(d, current->right, current);
  }

  if(current != NULL){
    if(d == current->value){
      //delete
      if(current->left == NULL &&  current->right == NULL){ // NO CHILD CASE
	if(parent->value > current->value){
	  parent->left = NULL;
	  delete current;
	}else{
	  parent->right = NULL;
	  delete current;
	}
      }

      // 1 Child case
      if(current -> left == NULL && current->right != NULL){ //set right to current
	node* replace = current->right;

	if(parent->right == current){
	  parent->right = replace;
	  delete current;
	}

	if(parent->left == current){
	  parent->left = replace;
	  delete current;
	}
      }

      if(current->right == NULL && current ->left != NULL){ //set left to current
	node* replace = current->left;

	if(parent->right == current){
	  parent->right = replace;
	  delete current;
	}

	if(parent->left == current){
	  parent->left = replace;
	  delete current;
	}
      }

      // 2 child case

      if(current->right != NULL && current->left != NULL){
	cout<<current->value<<endl;
	node* successor = find(current, d);
	cout<< successor->value<<endl;
	
      }

      
    }
  }

  // move all way to the left side of the tree
  if(current->left != NULL){
    deletion(d, current->left, current);
  }

}

node* find(node* current, int d){
  // go the left
  cout<<"RUNNING FIND, current: "<<current->value<<endl;
  // On first call ONLY
  Node* temp;
  if(current->value == d){
    temp = find(current->left, d);
  }

  // go as far to the right
  if(current->right != NULL){
    temp = find(current->right, d);
  }
  else{
    cout<<"about to return: "<<current->value<<endl;
    return temp;

  }

  cout<<"umm failure!!"<<endl;
  return NULL;
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
