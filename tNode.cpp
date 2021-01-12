#include "tNode.h"
#include <iostream>
#include <cstring>

using namespace std;

tNode::tNode(){
  lChild = NULL;
  rChild = NULL;
}

tNode::~tNode(){
 
  lChild = NULL;
  rChild = NULL;
}

void tNode::setRChild(tNode* newnode){
  rChild = newnode;
}

void tNode::setLChild(tNode* newnode){
  lChild = newnode;
}

tNode* tNode::getLChild(){
  return lChild;
}

tNode* tNode::getRChild(){
  return rChild;
}

void tNode::setData(int expression){
  data = expression;
}

int tNode::getData(){
  return data;
}
