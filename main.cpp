/* Ella MacPherson
   3/4/2026 Binary search tree
   a tree that searchs binarily!!!!!! :DDD
 */


#include <iostream>
#include <fstream>
#include "node.h"

using namespace std;

// Func decleration
void insert(node* current, node*& root, int value);
void print(int depth, node* current);
void search(int s, node* current, bool& found);
void deletion(int d, node* current, node* parent, node*& root);
node* find(node* current, int d, node*& parent);

int main(){

  int input = 0; // Number to be added currently

  string command = ""; // What the user wants to do
  node* root = NULL; // Root of the tree

  while(true){

    // Clear for new input
    command.clear();
    
    cout<<"Enter ADD, FILE ADD, PRINT, SEARCH"<<endl;

    getline(cin, command);

    // Check the command..
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
      // Run insert func
      insert(root, root, input);
    }
    
    if(command == "print" || command == "PRINT"){
      print(0, root);
    }

    if(command == "search" || command == "SEARCH"){
      cout<<"What number are you searching for?"<<endl;
      int s = 0;
      cin>>s;
      cin.ignore();
      bool found = false; // keep track
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
      cin.ignore();
      
      deletion(d, root, root, root);
    }

  }
  
}

// big fat delete function
void deletion(int d, node* current, node* parent, node*& root){
  // iterate through.. yes its a copy of print
  if(current->right != NULL){
    deletion(d, current->right, current, root);
  }

  // As long as there is somthing in the list
  if(current != NULL){
    // current is now = to one we wanna delete
    if(d == current->value){
      // NO CHILD CASE
	if(current->left == NULL &&  current->right == NULL){ // NO CHILD CASE

	  // We are NOT deleting root
	  if(current != root){
	    if(parent->value > current->value){
	      parent->left = NULL;
	      delete current;
	      return;
	    }else{
	      parent->right = NULL;
	      delete current;
	      return;
	    }
	  }
	  else{ // We are deleting the root with NO children
	    delete current;
	    root = NULL;
	    return;
	  }
	}
      

      // 1 Child case with a right child
      if(current -> left == NULL && current->right != NULL){ //set right to current
	node* replace = current->right;
	//we are not deleting root
	if(current != root){
	  if(parent->right == current){
	    parent->right = replace;
	    delete current;
	    return;
	  }
	  
	  if(parent->left == current){
	    parent->left = replace;
	    delete current;
	    return;
	  }
	}
	// We are deleting root with a right value
	else{
	  root = current->right;
	  delete current;
	  return;
	}
      }
	  
      // 1 child case with a left child
      if(current->right == NULL && current ->left != NULL){ //set left to current
	node* replace = current->left;
	// We are deleting not root
	if(current != root){
	  if(parent->right == current){
	    parent->right = replace;
	    delete current;
	    return;
	  }
	  
	  if(parent->left == current){
	    parent->left = replace;
	    delete current;
	    return;
	  }
	}
	// We are deleting root with a left child
	else{
	  root = current->left;
	  delete current;
	  return;
	}
      }
      
      // 2 child case
      
      if(current->right != NULL && current->left != NULL){
	
	node* successorParent = NULL;
	node* successor = find(current, d, successorParent);

	//	cout<<"deleting: " << current->value<<endl;
	
	//	cout<<"successor parent: "<< successorParent->value<<endl;
	//	cout<<"successor: "<< successor->value<<endl;
	//	cout<<"parent of current: "<<parent->value<<endl;

	// We are 2 child deleting the root
	if(current == root){
	  
	//Do 1 child delete for successor if it has a left
	  if(successor->left != NULL){
	    
	    // Put the successor left into the right of the parent of the successor
	    if(successorParent != root){
	      successorParent->right = successor->left;
	    }else{
	      successorParent->left = successor->left;
	    }
	   
	  }
	  
	  //Do NO child delete if it has no left
	  if(successor->left == NULL){
	    
	    if(successorParent != root){
	      successorParent->right = NULL;
	    }
	    else{
	      successorParent->left = NULL;
	    }
	    
	  }

	  
	  //Then like sub it in
	  successor->left = current->left;
	  successor->right = current->right;
	  
	  // Replace root if that is what is happening hereee!
	  if(current->value == root->value){
	    root = successor;
	  }
	  
	  delete current;
	  return;
	}
	
	// We are 2 child deleting a random number in our beautiful scheme
	else{
	  cout<<"running 2 child NOT root delete"<<endl;
	  // patch successor things
	  //Do 1 child delete for successor if it has a left
	  if(successor->left != NULL){
	    // Put the successor left into the right of the parent of the successor
	    successorParent->left = successor->left;
	  }
	  
	  //Do NO child delete if it has no left
	  if(successor->left == NULL){
	    // Set the successor parent left to null
	    successorParent->left = NULL;
	    
	  }

	  // replace currents L and R with successor
	  successor->left = current->left;
	  successor->right = current->right;

	  // Patch it to the old parent
	  if(current->value > parent->value){
	    parent->right = successor;
	  }
	  else{
	    parent->left = successor;
	  }

	  // Then we can finalyl delete the current
	  delete current;
	  return;
	  
	  
	}
	
	
      }

    }
  }

  // move all way to the left side of the tree
  if(current->left != NULL){
    deletion(d, current->left, current, root);
  }

}

node* find(node* current, int d, node*& parent){
  // go the left
  cout<<"RUNNING FIND, current: "<<current->value<<endl;
  // On first call ONLY
  if(current->value == d){
    parent = current;
    return find(current->left, d, parent);
  }

  // go as far to the right
  if(current->right != NULL){
    parent = current;
    return find(current->right, d, parent);
  }
  else{
    cout<<"about to return: "<<current->value<<"with parent: "<<parent->value<<endl;
    return current;

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
