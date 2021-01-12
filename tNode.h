#ifndef TNODE
#define TNODE

#include <iostream>
#include <cstring>

using namespace std;

class tNode{
 public:
  tNode();
  ~tNode();
  void setRChild(tNode*);
  void setLChild(tNode*);
  tNode* getLChild();
  tNode* getRChild();
  void setData(int);
  int getData();
  
 private:
  tNode* lChild;
  tNode* rChild;
  int data;
  
};
#endif
