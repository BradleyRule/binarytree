#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "tNode.h"


using namespace std;

//method prototypes
void addNode(tNode*&, int);
void printWrapper(tNode*);
void print(tNode*);
bool searchWrapper(tNode*, int);
bool search(tNode*, int);
void printTWrapper(tNode*);
void printT(tNode*, int);
void deleteWrapper(tNode*&, int);
bool deleteNode(tNode*, tNode*, tNode*&, int);
void repair(tNode*, tNode*, int);
void repairRoot(tNode*&);

int main(){
  //char array to store input
  char input[500];
  //integer to store numeric inputs
  int numInput = 0;
  //table is used to store data to setup the tree
  int table[200];
  //used for iteration
  int count = 0;
  //root of the binary tree
  tNode* root = NULL;
  bool running = true;

  
  cout << "Would you like to start your binary tree with a file input or manul input? (enter: 'manual' or 'file')" << endl;

  //get user input
  cin.get(input, 500);
  cin.get();

  
  if(strcmp(input, "manual") == 0){//if user chooses manual input
    cout << "How many numbers would you like to enter?" << endl;
    //get number of integers the user wants to input
    cin >> count;

    for (int i = 0; i < count; i++){
      //get the next number
      cout << "Enter a number (1-999)" << endl;
      cin >> numInput;
      
      //put the entered number int the table
      table[i] = numInput;
      cout << endl;
    }
  }
  else if(strcmp(input, "file") == 0){//if input via file
    for(int i = 0; i < 500; i++){
      input[i] = '\0';
    }

    //get the name of the file
    cout << "Enter name of file (example.txt)" << endl;
    cin.get(input, 500);
    cin.get();

    //create file object.
    ifstream file(input);

    if (file.is_open()){//open the file
      while(!file.eof()){//while not end of file
	//read in the next number from the file and store it in the table
	file >> table[count];
	//increment count
	count++;
      }
      //close file
      file.close();
    }
  }
  

  for(int i = 0; i < count; i++){
    //call addNode on each number entered to create the tree
    addNode(root, table[i]);
  }

  cout << "Your tree has been created!" << endl;
  
  cin.get();
  while(running){//while the user is running the program
    for(int i = 0; i < 500; i++){
      input[i] = '\0';
    }

    
    cout << "What would you like to do? (add, print, delete, search, quit)" << endl;

    //ask user what action they want to perform
    cin.get(input, 500);
    cin.get();

    if(strcmp(input, "add") == 0){//if input is add
      cout << "What number would you like to add to the tree?" << endl;
      //get number input
      cin >> numInput;
      cin.get();
      //add new node to the tree
      addNode(root, numInput);
    }
    else if(strcmp(input, "print") == 0){//if input is print
      //print the tree
      cout << "Data tree:" << endl;
      printTWrapper(root);
      //print all values from least to greatest
      cout << "Data in order of least to greatest:" << endl;
      printWrapper(root);
    }
    else if(strcmp(input, "search") == 0){//if input is search
      cout << "Enter the number you would like to search for:" << endl;
      //get number to search for
      cin >> numInput;
      cin.get();
      //if search method finds the number
      if(searchWrapper(root, numInput)){
	//tell the user that the number is in the tree
	cout << numInput << " is in the tree!" << endl;
      }
      else{//if the searcher did not find the number, tell the user
	cout << numInput << " is not in the tree!" << endl;
      }
    }
    else if(strcmp(input, "delete") == 0){//if input is delete
      cout << "Enter the number you would like to delete: " << endl;
      //get the number to delete
      cin >> numInput;
      cin.get();
      //call function to delete the number
      deleteWrapper(root, numInput);
    }
    else if(strcmp(input, "quit") == 0){//if input is quit
      //set running to false
      running = false;
    }

    cout << endl;
    
  }
  

  return 0;
}

//function adds node to tree
void addNode(tNode*& root, int data){
  if(root == NULL){//if there is no root
    //add the data to a new node made at the root
    root = new tNode();
    root->setData(data);
  }
  else{//if there is already a root
    //create a temp pointer
    tNode* temp = root;
    while(temp != NULL){//find the spot where the node goes
      if(data < temp->getData()){//if the data is smaller than the current node's data, it goes to the left
	if(temp->getLChild() == NULL){//if the next position is null, add the data to a new node at that position
	  tNode* newnode = new tNode();
	  newnode->setData(data);
	  temp->setLChild(newnode);
	  temp = NULL;
	}
	else{
	  //go left
	  temp = temp->getLChild();
	}
      }
      else if(data >= temp->getData()){//same as if the data is smaller but goes to the right
	if(temp->getRChild() == NULL){
	  tNode* newnode = new tNode();
	  newnode->setData(data);
	  temp->setRChild(newnode);
	  temp = NULL;
	}
	else{
	  //go right
	  temp = temp->getRChild();
	}
      }
    }
  }
}


void printWrapper(tNode* root){//print wrapper function
  print(root);
  cout << endl;
}

void print(tNode* root){
  if(root){//recursivly walks dwn the left, then prints and walks down the right side
    print(root->getLChild());
    cout << root->getData() << " ";
    print(root->getRChild());
  }
}

bool searchWrapper(tNode* root, int data){//search wrapper function
  return search(root, data);
}

bool search(tNode* root, int data){//search function
  if(!root){//if end of tree is reached, nothing matches in the tree
    return false;
  }
  else{
    if(data == root->getData()){//if the data is found, return true
      return true;
    }
    else if(data < root->getData()){//if data is less than the current nodes data, walk down the left side
      return search(root->getLChild(), data);
    }
    else if(data > root->getData()){//if the data is less than the current nodes data, walk down the right side
      return search(root->getRChild(), data);
    }
  }
}


void printTWrapper(tNode* root){//wrapper function for printT method
  printT(root, 0);
  cout << endl;
}

void printT(tNode* root, int count){
  if(root){//if the current node exists
    //call printT incrementing the counter
    printT(root->getRChild(), count+1);
    for(int i = 0; i < count; i++){//add a tab for every level down the tree 
      cout << "\t";
    }
    //print out the value in the node
    cout << root->getData() << endl;
    //call printT on the left child
    printT(root->getLChild(), count+1);
  }
}

void deleteWrapper(tNode* &root, int data){//calls delete and if something was found and deleted, it returns true
  if(deleteNode(root, root, root, data)){//tell user it was successfully deleted
    cout << data << " was successfully deleted" << endl;
  }
  else{//tell user that the data wasn't found
    cout << data << " was not found" << endl;
  }
}

bool deleteNode(tNode* parent, tNode* child, tNode* &root, int data){
  if(!child){//if current is null
    //there is no matching data, return false
    return false;
  }
  else{
    if(data == child->getData()){//if there is matching data 
      if(parent == child){//if the data is at the root
	repairRoot(root);
      }
      else{//if the data is not at the root
	//call repair to delete the data and repair the tree
	repair(parent, child, data);
      }
      //return true afterdeleting
      return true;
    }
    //otherwise, search down the tree for matching data
    else if(data < child->getData()){
      return deleteNode(child, child->getLChild(), root, data);
    }
    else if(data > child->getData()){
      return deleteNode(child, child->getRChild(), root, data);
    }
  }
}
		   
void repair(tNode* parent, tNode* child, int data){
  tNode* temp;
  tNode* previous;
  char whichChild = '\0';


  //determine if the child is the left or right child of parent
  if (parent->getLChild()){
    if(parent->getLChild()->getData() == data){
      whichChild = 'L';
    }
  }
  if (parent->getRChild()){
    if(parent->getRChild()->getData() == data){
      whichChild = 'R';
    }
  }

  if(child->getLChild() == NULL && child->getRChild() == NULL){//if there are no children of the child,
    //delete the node
    if(whichChild == 'L'){
      delete child;
      parent->setLChild(NULL);
    }
    else if(whichChild == 'R'){
      delete child;
      parent->setRChild(NULL);
    }
  }
  else if(child->getRChild() == NULL){//if there is only a left child
    //make parent point to child of the current child then delete current child
    if(whichChild == 'L'){
      parent->setLChild(child->getLChild());
      delete child;
    }
    else if(whichChild == 'R'){
      parent->setRChild(child->getLChild());
      delete child;
    }
  }
  else if(child->getRChild() != NULL){//if there is a right child of child
    //set pointers
    temp = child->getRChild();
    previous = child;
    if(temp->getLChild()){//if there is a left child of temp
      while(temp->getLChild()){//walk down to the farthest left child 
	previous = temp;
	temp = temp->getLChild();
      }
      //put the data in temp into child (temp now has the data of child that we will delete and the child has the in order successor keeping the integrity of the binary tree
      child->setData(temp->getData());

      //delete temp
      previous->setLChild(temp->getRChild());
      delete temp;
    }
    else if(!temp->getLChild()){//if original temp had no left child,
      //set child's child to temp's right child.
      child->setData(temp->getData());
      child->setRChild(temp->getRChild());
      //delete temp
      delete temp;
    }
  }
  
}

void repairRoot(tNode* &root){//same as repair but makes small adjustments to reistablish the root
  tNode* head = root;
  tNode* temp;
  tNode* previous;

  
  if(head->getRChild() == NULL && head->getLChild() == NULL){
    delete head;
    root = NULL;
  }
  else if(!head->getRChild()){
    root = head->getLChild();
    delete head;
  }
  else if(head->getRChild()){
    temp = head->getRChild();
    previous = head;
    if(temp->getLChild()){
      while(temp->getLChild()){
	previous = temp;
	temp = temp->getLChild();
      }
      
      head->setData(temp->getData());
      
      previous->setLChild(temp->getRChild());
      delete temp;
    }
    else if(!temp->getLChild()){
      head->setData(temp->getData());
      head->setRChild(temp->getRChild());
      delete temp;
    }
  }
}
