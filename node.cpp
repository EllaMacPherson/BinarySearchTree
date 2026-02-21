#include "node.h"

node::node(node* r, node* l, int v){

  // Set input values to node values
  right = r;
  left = l;
  value = v;
  
}

node::~node(){

  right = NULL;
  left = NULL;

  delete right;
  delete left;

}
