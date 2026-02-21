#include <iostream>

using namespace std;

class node{
 public:
  // Constructer
  node(node* r, node* l, int v);

  ~node(); // Destrcucter

  // Next nodes
  node* right;
  node* left;

  // Value storage
  int value;

};
