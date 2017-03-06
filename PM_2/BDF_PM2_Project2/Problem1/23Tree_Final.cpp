/*
Brian Faure
RUID:150003563
NetID:bdf39
Prog. Methodology II
Project #2
Problem #1
December 2015
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <time.h>

/*

--> Implementation of 2-3 Balanced Search Tree
--> **See written report for more detail**

PROGRAM CONTENTS:
--> #1.) TriNode Class
--> #2.) TriNode Class member function definitions
--> #3.) twothreeTree Class
--> #4.) twothreeTree Class member function definitions
         along with assorted global functions
--> #5.) Main Function

     The user should only interact with the 2-3 Tree through the twothreeTree class.
This is not to say it is not possible to manipulate the TriNodes themselves but no quality
can be assured when it comes to the structure of the Balanced Search Tree if the TriNodes are
directly altered by the user.  The list of available functions is shortened to include...

--> twothreeTree default constructor
--> twothreeTree insert function (tempTree.insert(ItemType anItem))
--> inorder global function (inorder(tempTree))
--> int getHeight();
--> int getNodeCount();
--> bool findItem(twothreeTree<ItemType> inputTree, ItemType target){
--> void removeItem(twothreeTree<ItemType> &inputTree, ItemType target){
--> void outputNode(TriNode<ItemType> temp, std::string which){

Be aware the the removeItem function works in most cases.
*/

//--------------------------------------------------------------------------------------
//----------------------------------TriNode Class---------------------------------------
//--------------------------------------------------------------------------------------
template<typename ItemType>
class TriNode{
private:
  TriNode<ItemType>* parentPtr;
  TriNode<ItemType>* leftChildPtr;
  TriNode<ItemType>* midChildPtr;
  TriNode<ItemType>* rightChildPtr;
  TriNode<ItemType>* extraChildPtr;
public:
  ItemType smallItem;
  ItemType largeItem;
  ItemType extraItem;
  
  TriNode();
  TriNode(ItemType anItem);
  TriNode(TriNode<ItemType>* parentptr);
  TriNode(const ItemType& anItem, TriNode<ItemType>* leftPtr,
	  TriNode<ItemType>* midPtr, TriNode<ItemType>* rightPtr);
  
  bool isLeaf();
  bool isTwoNode();
  bool isThreeNode();
  bool isRoot();

  ItemType getSmallItem();
  ItemType getLargeItem();
  ItemType getExtraItem();
  
  bool isLargeItem;
  bool isExtraItem;
  bool isSmallItem;

  bool hasMidChild;
  bool hasLeftChild;
  bool hasRightChild;
  bool hasParent;
  bool hasExtraChild;

  bool hasSmallItem();
  bool hasLargeItem();
  bool hasExtraItem();
  
  void removeLargeItem();
  void removeSmallItem();
  void removeExtraItem();
  
  void setExtraItem(ItemType anItem);
  void setSmallItem(ItemType anItem);
  void setLargeItem(ItemType anItem);

  TriNode<ItemType>* getLeftChildPtr();
  TriNode<ItemType>* getMidChildPtr();
  TriNode<ItemType>* getRightChildPtr();
  TriNode<ItemType>* getParentPtr();
  TriNode<ItemType>* getExtraChildPtr();

  void setLeftChildPtr(TriNode<ItemType>* leftptr);
  void setMidChildPtr(TriNode<ItemType>* midptr);
  void setRightChildPtr(TriNode<ItemType>* rightptr);
  void setParentPtr(TriNode<ItemType>* parentptr);
  void setExtraChildPtr(TriNode<ItemType>* extraptr);

  void removeLeftChildPtr();
  void removeRightChildPtr();
  void removeMidChildPtr();
  void removeParentPtr();
  void removeExtraChildPtr();

  void resetChildren();
  void resetItems();
  int getNumItems();
  int getNumChildren();
  bool insert(ItemType anItem);
  void swapSmallAndLarge();
  bool searchNode(ItemType anItem);
  std::string getRelation();
  TriNode<ItemType>* findRoot();
};
//--------------------------------------------------------------------------------------
//---------------------TriNode Class Member Function Definitions------------------------
//--------------------------------------------------------------------------------------
template<typename ItemType>
std::string TriNode<ItemType>::getRelation(){
  if(!hasParent){
    return "ROOT";
  }
  TriNode<ItemType>* parent = getParentPtr();
  int children = (*parent).getNumChildren();
  if(children==2){
    if((*parent).getLeftChildPtr()==this){
      return "LEFT";
    }
    if((*parent).getRightChildPtr()==this){
      return "RIGHT";
    }
  }
  if(children==3){
    if((*parent).getLeftChildPtr()==this){
      return "LEFT";
    }
    if((*parent).getRightChildPtr()==this){
      return "RIGHT";
    }
    if((*parent).getMidChildPtr()==this){
      return "MIDDLE";
    }
  }
  return "NULL";
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::findRoot(){
  if(isRoot()){
    return this;
  }
  else{
    bool condition = true;
    TriNode<ItemType>* vessel = getParentPtr();
    while(condition){
      if((*vessel).isRoot()){
	condition = false;
	return vessel;
      }
      else{
	vessel = (*vessel).getParentPtr();
      }
    }
  }
  return this;
}
template<typename ItemType>
bool splitThreeNode(bool &internal, std::string &code, TriNode<ItemType> *&vessel){
  int numItems = (*vessel).getNumItems();
  if(numItems==2){
    return true;
  }
  bool wasLeaf = (*vessel).isLeaf();
  TriNode<ItemType>* firstChild = (*vessel).getLeftChildPtr();
  TriNode<ItemType>* secondChild = (*vessel).getMidChildPtr();
  TriNode<ItemType>* thirdChild = (*vessel).getRightChildPtr();
  TriNode<ItemType>* fourthChild = (*vessel).getExtraChildPtr();
  ItemType oldSmall = (*vessel).getSmallItem();
  ItemType oldLarge = (*vessel).getLargeItem();
  ItemType oldExtra = (*vessel).getExtraItem();
  if((*vessel).isRoot()){
    TriNode<ItemType>* newLeft = new TriNode<ItemType>;
    TriNode<ItemType>* newRight = new TriNode<ItemType>;
    (*newLeft).setSmallItem(oldSmall);
    (*newRight).setSmallItem(oldLarge);
    (*vessel).resetChildren();
    (*vessel).resetItems();
    (*vessel).setSmallItem(oldExtra);
    (*vessel).setLeftChildPtr(newLeft);
    (*vessel).setRightChildPtr(newRight);
    if(!wasLeaf){
      (*newLeft).setLeftChildPtr(firstChild);
      (*newLeft).setRightChildPtr(secondChild);
      (*newRight).setLeftChildPtr(thirdChild);
      (*newRight).setRightChildPtr(fourthChild);
    }
    return true;
  }
  std::string relation = (*vessel).getRelation();
  TriNode<ItemType>* parent = (*vessel).getParentPtr();
  int siblings = (*parent).getNumChildren();
  (*vessel).resetItems();
  (*vessel).resetChildren();
  if(siblings==2){
    (*parent).insert(oldExtra);
    if(relation=="RIGHT"){
      (*vessel).setSmallItem(oldLarge);
      TriNode<ItemType>* newMid = new TriNode<ItemType>;
      (*newMid).setSmallItem(oldSmall);
      (*parent).setMidChildPtr(newMid);
      if(!wasLeaf){
	(*newMid).setLeftChildPtr(firstChild);
	(*newMid).setRightChildPtr(secondChild);
	(*vessel).setLeftChildPtr(thirdChild);
	(*vessel).setRightChildPtr(fourthChild);
      }
      return true;
    }
    if(relation=="LEFT"){
      (*vessel).setSmallItem(oldSmall);
      TriNode<ItemType>* newMid = new TriNode<ItemType>;
      (*newMid).setSmallItem(oldLarge);
      (*parent).setMidChildPtr(newMid);
      if(!wasLeaf){
	(*vessel).setLeftChildPtr(firstChild);
	(*vessel).setRightChildPtr(secondChild);
	(*newMid).setLeftChildPtr(thirdChild);
	(*newMid).setRightChildPtr(fourthChild);
      }
      return true;
    }
  }
  if(siblings==3){
    (*parent).insert(oldExtra);
    if(relation=="RIGHT"){
      (*vessel).setSmallItem(oldSmall);
      TriNode<ItemType>* newFourth = new TriNode<ItemType>;
      (*newFourth).setSmallItem(oldLarge);
      (*parent).setExtraChildPtr(newFourth);
      if(!wasLeaf){
	(*vessel).setLeftChildPtr(firstChild);
	(*vessel).setRightChildPtr(secondChild);
	(*newFourth).setLeftChildPtr(thirdChild);
	(*newFourth).setRightChildPtr(fourthChild);
      }
      return splitThreeNode(internal, code, parent);
    }
    if(relation=="LEFT"){
      (*vessel).setSmallItem(oldSmall);
      TriNode<ItemType>* newSecond = new TriNode<ItemType>;
      (*newSecond).setSmallItem(oldLarge);
      TriNode<ItemType>* newThird = (*parent).getMidChildPtr();
      TriNode<ItemType>* newFourth = (*parent).getRightChildPtr();
      (*parent).setLeftChildPtr(vessel);
      (*parent).setMidChildPtr(newSecond);
      (*parent).setRightChildPtr(newThird);
      (*parent).setExtraChildPtr(newFourth);
      if(!wasLeaf){
	(*vessel).setLeftChildPtr(firstChild);
	(*vessel).setRightChildPtr(secondChild);
	(*newSecond).setLeftChildPtr(thirdChild);
	(*newSecond).setRightChildPtr(fourthChild);
      }
      return splitThreeNode(internal, code, parent);
    }
    if(relation=="MIDDLE"){
      (*vessel).setSmallItem(oldSmall);
      TriNode<ItemType>* newThird = new TriNode<ItemType>;
      (*newThird).setSmallItem(oldLarge);
      TriNode<ItemType>* newFourth = (*parent).getRightChildPtr();
      (*parent).setExtraChildPtr(newFourth);
      (*parent).setRightChildPtr(newThird);
      if(!wasLeaf){
	(*vessel).setLeftChildPtr(firstChild);
	(*vessel).setRightChildPtr(secondChild);
	(*newThird).setLeftChildPtr(thirdChild);
	(*newThird).setRightChildPtr(fourthChild);
      }
      return splitThreeNode(internal, code, parent);
    }
  }
  return false;
}  
template<typename ItemType>
bool TriNode<ItemType>::searchNode(ItemType anItem){
  int numItems = getNumItems();
  if(numItems==1){
    if(getSmallItem()==anItem){
      return true;
    }
  }
  if(numItems==2){
    if(getSmallItem()==anItem){
      return true;
    }
    if(getLargeItem()==anItem){
      return true;
    }
  }
  return false;
}
template<typename ItemType>
bool TriNode<ItemType>::isRoot(){
  if(!hasParent){
    return true;
  }
  else{
    return false;
  }
}
template<typename ItemType>
void TriNode<ItemType>::swapSmallAndLarge(){
  ItemType currentSmall = getSmallItem();
  ItemType currentLarge = getLargeItem();
  setSmallItem(currentLarge);
  setLargeItem(currentSmall);
  return;
}
template<typename ItemType>
bool TriNode<ItemType>::insert(ItemType anItem){
  int numItems = getNumItems();
  if(numItems==2){
    int oldSmall = getSmallItem();
    int oldLarge = getLargeItem();
    if(anItem<oldSmall){
      setSmallItem(anItem);
      setLargeItem(oldLarge);
      setExtraItem(oldSmall);
      return false;
    }
    if(anItem>oldLarge){
      setSmallItem(oldSmall);
      setLargeItem(anItem);
      setExtraItem(oldLarge);
      return false;
    }
    else{
      setExtraItem(anItem);
      return false;
    }
  }
  if(numItems==1){
    int currentItem = getSmallItem();
    setLargeItem(anItem);
    if(anItem<currentItem){
      swapSmallAndLarge();
    }
    return true;
  }
  if(numItems==0){
    setSmallItem(anItem);
    return true;
  }
  return true;
}
template<typename ItemType>
void TriNode<ItemType>::removeExtraChildPtr(){
  hasExtraChild=false;
}
template<typename ItemType>
void TriNode<ItemType>::removeExtraItem(){
  isExtraItem=false;
}
template<typename ItemType>
int TriNode<ItemType>::getNumChildren(){
  int count=0;
  if(hasMidChild){
    count++;
  }
  if(hasLeftChild){
    count++;
  }
  if(hasRightChild){
    count++;
  }
  if(hasExtraChild){
    count++;
  }
  return count;
}
template<typename ItemType>
int TriNode<ItemType>::getNumItems(){
  int count=0;
  if(isLargeItem){
    count++;
  }
  if(isSmallItem){
    count++;
  }
  if(isExtraItem){
    count++;
  }
  return count;
}
template<typename ItemType>
void TriNode<ItemType>::resetChildren(){
  hasExtraChild=false;
  hasLeftChild=false;
  hasRightChild=false;
  hasMidChild=false;
}
template<typename ItemType>
void TriNode<ItemType>::resetItems(){
  isLargeItem=false;
  isSmallItem=false;
  isExtraItem=false;
}
template<typename ItemType>
void TriNode<ItemType>::removeParentPtr(){
  hasParent=false;
}
template<typename ItemType>
void TriNode<ItemType>::removeLeftChildPtr(){
  hasLeftChild=false;
}
template<typename ItemType>
void TriNode<ItemType>::removeRightChildPtr(){
  hasRightChild=false;
}
template<typename ItemType>
void TriNode<ItemType>::removeMidChildPtr(){
  hasMidChild=false;
}
template<typename ItemType>
bool TriNode<ItemType>::hasSmallItem(){
  if(isSmallItem){
    return true;
  }
  else{
    return false;
  }
}
template<typename ItemType>
void TriNode<ItemType>::removeSmallItem(){
  isSmallItem=false;
}
template<typename ItemType>
void TriNode<ItemType>::removeLargeItem(){
  isLargeItem=false;
}
template<typename ItemType>
void TriNode<ItemType>::setExtraChildPtr(TriNode<ItemType>* extraptr){
  extraChildPtr=extraptr;
  hasExtraChild=true;
  (*extraptr).setParentPtr(this);
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getExtraChildPtr(){
  return extraChildPtr;
}
template<typename ItemType>
bool TriNode<ItemType>::hasExtraItem(){
  if(isExtraItem){
    return true;
  }
  else{
    return false;
  }
}
template<typename ItemType>
void TriNode<ItemType>::setExtraItem(ItemType anItem){
  isExtraItem=true;
  extraItem=anItem;
}
template<typename ItemType>
ItemType TriNode<ItemType>::getExtraItem(){
  return extraItem;
}

template<typename ItemType>
TriNode<ItemType>::TriNode(TriNode<ItemType>* parentptr){
  resetChildren();
  resetItems();
  parentPtr=parentptr;
  hasParent=true;
  leftChildPtr=NULL;
  midChildPtr=NULL;
  rightChildPtr=NULL;
  extraChildPtr=NULL;
}
template<typename ItemType>
TriNode<ItemType>::TriNode(){
  resetChildren();
  resetItems();
  hasParent=false;
  parentPtr=NULL;
  leftChildPtr=NULL;
  midChildPtr=NULL;
  rightChildPtr=NULL;
  extraChildPtr=NULL;
}

template<typename ItemType>
void TriNode<ItemType>::setParentPtr(TriNode<ItemType>* parentptr){
  hasParent=true;
  parentPtr=parentptr;
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getParentPtr(){
  return parentPtr;
}
template<typename ItemType>
bool TriNode<ItemType>::hasLargeItem(){
  if(isLargeItem){
    return true;
  }
  else{
    return false;
  }
}
template<typename ItemType>
TriNode<ItemType>::TriNode(const ItemType& anItem, TriNode<ItemType>* leftPtr,
			   TriNode<ItemType>* midPtr, TriNode<ItemType>* rightPtr){
  smallItem=anItem;
  isSmallItem=true;
  leftChildPtr=leftPtr;
  midChildPtr=midPtr;
  rightChildPtr=rightPtr;
  parentPtr=NULL;
  isLargeItem=false;
  isExtraItem=false;
  extraChildPtr=NULL;
  hasMidChild=true;
  hasLeftChild=true;
  hasRightChild=true;
  hasParent=false;
}
template<typename ItemType>
void TriNode<ItemType>::setLeftChildPtr(TriNode<ItemType>* leftptr){
  hasLeftChild=true;
  leftChildPtr=leftptr;
  (*leftptr).setParentPtr(this);
}
template<typename ItemType>
void TriNode<ItemType>::setMidChildPtr(TriNode<ItemType>* midptr){
  hasMidChild=true;
  midChildPtr=midptr;
  (*midptr).setParentPtr(this);
}
template<typename ItemType>
void TriNode<ItemType>::setRightChildPtr(TriNode<ItemType>* rightptr){
  hasRightChild=true;
  rightChildPtr=rightptr;
  (*rightptr).setParentPtr(this);
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getRightChildPtr(){
  if(!hasRightChild){
  }
  return rightChildPtr;
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getMidChildPtr(){
  return midChildPtr;
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getLeftChildPtr(){
  return leftChildPtr;
}
template<typename ItemType>
void TriNode<ItemType>::setLargeItem(ItemType anItem){
  largeItem = anItem;
  isLargeItem=true;
}
template<typename ItemType>
void TriNode<ItemType>::setSmallItem(ItemType anItem){
  smallItem = anItem;
  isSmallItem = true;
}
template<typename ItemType>
ItemType TriNode<ItemType>::getLargeItem(){
  return largeItem;
}
template<typename ItemType>
ItemType TriNode<ItemType>::getSmallItem(){
  return smallItem;
}
template<typename ItemType>
TriNode<ItemType>::TriNode(ItemType anItem){
  resetChildren();
  resetItems();
  smallItem = anItem;
  isSmallItem = true;
  leftChildPtr = NULL;
  midChildPtr = NULL;
  rightChildPtr = NULL;
  parentPtr = NULL;
  extraChildPtr=NULL;
}
template<typename ItemType>
bool TriNode<ItemType>::isLeaf(){
  if(getNumChildren()==0){
    return true;
  }
  else{
    return false;
  }
}
template<typename ItemType>
bool TriNode<ItemType>::isTwoNode(){
  if(getNumChildren()==2){
    return true;
  }
  else{
    return false;
  }
}
template<typename ItemType>
bool TriNode<ItemType>::isThreeNode(){
  if(getNumChildren()==3){
    return true;
  }
  else{
    return false;
  }
}
//--------------------------------------------------------------------------------------
//-------------------------------twothreeTree Class-------------------------------------
//--------------------------------------------------------------------------------------
template<typename ItemType>
class twothreeTree{
private:
  TriNode<ItemType>* rootPtr;
  int count;
  int countHelper(TriNode<ItemType>* vesselNode);
  bool insertionHelper(TriNode<ItemType> *&root, ItemType newItem);
  bool tempBool;
  
public:
  twothreeTree();
  twothreeTree(TriNode<ItemType>* inputRootPtr);
  void setRootPtr(TriNode<ItemType>* inputRootPtr);
  TriNode<ItemType>* getRootPtr();
  bool findLocation(ItemType target, TriNode<ItemType>* currentNode, TriNode<ItemType> *&location);
  int getHeight();
  int getNodeCount();
  bool insertItem(ItemType newItem);
};
template<typename ItemType>
bool twothreeTree<ItemType>::findLocation(ItemType target, TriNode<ItemType>* currentNode, TriNode<ItemType> *&location){
  if((*currentNode).searchNode(target)){
    return false;
  }
  if((*currentNode).isLeaf()){
    location=currentNode;
    return true;
    }
    else{
      int numItems = (*currentNode).getNumItems();
      int smallItem = (*currentNode).getSmallItem();
      int largeItem = (*currentNode).getLargeItem();
      if(numItems==1){
	if(target<smallItem){
	  return findLocation(target, (*currentNode).getLeftChildPtr(), location);
	}
	else{
	  return findLocation(target, (*currentNode).getRightChildPtr(), location);
	}
      }
      else{
	if(numItems==2){
	  if(target<smallItem){
	    return findLocation(target, (*currentNode).getLeftChildPtr(), location);
	  }
	  if(target>largeItem){
	    return findLocation(target, (*currentNode).getRightChildPtr(), location);
	  }
	  else{
	    return findLocation(target, (*currentNode).getMidChildPtr(), location);
	  }
	}
      }
    }
  return true;
}
template<typename ItemType>
bool twothreeTree<ItemType>::insertionHelper(TriNode<ItemType> *&root, ItemType newItem){
  TriNode<ItemType>* nodePtr = rootPtr;
  bool possible = findLocation(newItem, rootPtr, root);
  if(!possible){
    return false;
  }
  bool insertion = (*root).insert(newItem);
  if(insertion){
    return true;
  }
  else{
    bool internal = false;
    std::string code = "NULL";
    TriNode<ItemType>* tempNode = root;
    bool doneSplitting = splitThreeNode(internal,code,tempNode);
    root = tempNode;
    return true;
  }
}
template<typename ItemType>
bool twothreeTree<ItemType>::insertItem(ItemType newItem){
  TriNode<ItemType>* tempRoot = rootPtr;
  tempBool = false;
  bool inserted = insertionHelper(tempRoot, newItem);
  if(inserted){ 
    TriNode<ItemType>* newRoot = (*tempRoot).findRoot();
    rootPtr = newRoot;
  }
  return inserted;
}
template<typename ItemType>
int twothreeTree<ItemType>::getNodeCount(){
  TriNode<ItemType>* vessel = rootPtr;
  count=1;
  countHelper(vessel);
  return count;
}
template<typename ItemType>
int twothreeTree<ItemType>::countHelper(TriNode<ItemType>* vesselNode){
  if((*vesselNode).isLeaf()){
    //std::cout<<"In leaf\n";
    return count;
  }
  else{
    if((*vesselNode).isTwoNode()){
      //std::cout<<"In two node\n";
      count+=2;
      TriNode<ItemType>* leftPtr = (*vesselNode).getLeftChildPtr();
      TriNode<ItemType>* rightPtr = (*vesselNode).getRightChildPtr();
      return (count+countHelper(leftPtr)+countHelper(rightPtr));
    }
    else{
      if((*vesselNode).isThreeNode()){
	//std::cout<<"In three node\n";
	count+=3;
	TriNode<ItemType>* leftPtr = (*vesselNode).getLeftChildPtr();
	TriNode<ItemType>* midPtr = (*vesselNode).getMidChildPtr();
	TriNode<ItemType>* rightPtr = (*vesselNode).getRightChildPtr();
	return (count+countHelper(leftPtr)+countHelper(midPtr)+countHelper(rightPtr));
      }
    }
  }
  return 0;
}
template<typename ItemType>
int twothreeTree<ItemType>::getHeight(){
  int height = 1;
  TriNode<ItemType>* vessel = rootPtr;
  bool condition = true;
  while(condition){
    if((*vessel).hasRightChild){
      height++;
      vessel = (*vessel).getRightChildPtr();
    }
    else{
      condition=false;
    }
  }
  return height;
}
template<typename ItemType>
twothreeTree<ItemType>::twothreeTree(){
  TriNode<ItemType>* temp = new TriNode<ItemType>;
  rootPtr=temp;
}
std::string identify;
template<typename ItemType>
void split(TriNode<ItemType> *n, twothreeTree<ItemType> &obj, TriNode<ItemType> *&tempNode, bool &condition){
  //std::cout<<"Entered the split() function.\n";
  bool fourChildren=false;
  TriNode<ItemType>* leftChild = new TriNode<ItemType>;
  TriNode<ItemType>* middleLeftChild = new TriNode<ItemType>;
  TriNode<ItemType>* middleRightChild = new TriNode<ItemType>;
  TriNode<ItemType>* rightChild = new TriNode<ItemType>; 
  if(identify=="LEFT"){
    //std::cout<<"Entered the identify LEFT statement.\n";
    fourChildren=true;
    leftChild = (*n).getExtraChildPtr();
    middleLeftChild = (*n).getLeftChildPtr();
    middleRightChild = (*n).getMidChildPtr();
    rightChild = (*n).getRightChildPtr();
  }
  if(identify=="RIGHT"){
    //std::cout<<"Entered the identify RIGHT statement.\n";
    fourChildren=true;
    leftChild = (*n).getLeftChildPtr();
    middleLeftChild = (*n).getMidChildPtr();
    middleRightChild = (*n).getRightChildPtr();
    rightChild = (*n).getExtraChildPtr();
  }
  identify="NULL";
  ItemType largeItem = (*n).getLargeItem();
  //std::cout<<"The largeItem in n: "<<largeItem<<"\n";
  ItemType smallItem = (*n).getSmallItem();
  //std::cout<<"The smallItem in n: "<<smallItem<<"\n";
  ItemType extraItem = (*n).getExtraItem();
  //std::cout<<"The extraItem in n: "<<extraItem<<"\n";
  ItemType smallest;
  ItemType middle;
  ItemType largest;
  if(largeItem<smallItem and largeItem<extraItem){
    smallest = largeItem;
    if(largeItem<extraItem){
      largest = extraItem;
      middle = largeItem;
    }
    else{
      largest=largeItem;
      middle=extraItem;
    }
  }
  if(smallItem<largeItem and smallItem<extraItem){
    smallest = smallItem;
    if(largeItem<extraItem){
      largest = extraItem;
      middle = largeItem;
    }
    else{
      largest=largeItem;
      middle=extraItem;
    }
  }
  if(extraItem<smallItem and extraItem<largeItem){
    smallest = extraItem;
    if(smallItem<largeItem){
      largest=largeItem;
      middle=smallItem;
    }
    else{
      largest=smallItem;
      middle=largeItem;
    }
  }
  bool hasThree=false;
  bool placeLeft=false;
  //std::cout<<"SMALLEST: "<<smallest<<"\n";
  //std::cout<<"MIDDLE: "<<middle<<"\n";
  //std::cout<<"LARGEST: "<<largest<<"\n";
  if(!(*n).hasParent){
    //std::cout<<"Has entered the NULL statement.\n";
    TriNode<ItemType>* temp1 = new TriNode<ItemType>;
    TriNode<ItemType>* left = new TriNode<ItemType>;
    TriNode<ItemType>* right = new TriNode<ItemType>;
    (*temp1).setSmallItem(middle);
    //outputNode(*temp1, "ALL");
    (*left).setSmallItem(smallest);
    //outputNode(*left, "ALL");
    (*right).setSmallItem(largest);
    //outputNode(*right, "ALL");
    (*temp1).setLeftChildPtr(left);
    (*temp1).setRightChildPtr(right);
    if(fourChildren){
      //std::cout<<"Has entered the fourChildren inside NULL statement.\n";
      (*left).setLeftChildPtr(leftChild);
      (*left).setRightChildPtr(middleLeftChild);
      (*right).setLeftChildPtr(middleRightChild);
      (*right).setRightChildPtr(rightChild);
    }
    tempNode=temp1;
    obj.setRootPtr(temp1);
    condition=true;
    //std::cout<<"///////////////////Ending Split function////////////////////\n";
    return;
  }
  else{
    ItemType parentSmall;
    ItemType parentLarge;
    TriNode<ItemType>* temp = new TriNode<ItemType>;
    temp = (*n).getParentPtr();
    TriNode<ItemType>* left = new TriNode<ItemType>;
    (*left).setSmallItem(smallest);
    TriNode<ItemType>* right = new TriNode<ItemType>;
    (*right).setSmallItem(largest);
    if(fourChildren){
      //std::cout<<"Entered fourChildren hash.\n";
      (*left).setLeftChildPtr(leftChild);
      (*left).setRightChildPtr(middleLeftChild);
      (*right).setLeftChildPtr(middleRightChild);
      (*right).setRightChildPtr(rightChild);
    }
    if((*temp).hasLargeItem()){
      (*temp).setExtraItem(middle);
      hasThree=true;
    }
    else{
      parentSmall=(*temp).getSmallItem();
      if(parentSmall>middle){
	placeLeft=true;
	(*temp).setSmallItem(middle);
	(*temp).setLargeItem(parentSmall);
      }
      else{
	(*temp).setLargeItem(middle);
      }
    }
    if(hasThree){
      //std::cout<<"-->Entered hasThree statement.\n";
      if(placeLeft){
	//std::cout<<"-->Entered the placeLeft statement.\n";
	identify = "LEFT";
	(*temp).setLeftChildPtr(right);
	(*temp).setExtraChildPtr(left);
      }
      else{
	//std::cout<<"-->Skipped the placeLeft statement (placeRight).\n";
	identify = "RIGHT";
	(*temp).setRightChildPtr(left);
	(*temp).setExtraChildPtr(right);
      }
      //std::cout<<"-->Calling split() again.\n";
      split(temp, obj, tempNode, condition);
    }
    else{
      //std::cout<<"-->Skipped the hasThree statement.\n";
      if(placeLeft){
        (*temp).setLeftChildPtr(left);
        (*temp).setMidChildPtr(right);
      }
      else{
        (*temp).setRightChildPtr(right);
        (*temp).setMidChildPtr(left);
      }
      if(fourChildren){
	//std::cout<<"Entered the bottom fourChildren statement.\n";
	(*left).setLeftChildPtr(leftChild);
	(*left).setRightChildPtr(middleLeftChild);
	(*right).setLeftChildPtr(middleRightChild);
	(*right).setRightChildPtr(rightChild);
      }
      obj.setRootPtr(temp);
      TriNode<ItemType>* root;
      if((*temp).getParentPtr()!=NULL){
	root=temp;
	bool loop = false;
	while(!loop){
	  root = (*root).getParentPtr();
	  if((*root).getParentPtr()==NULL){
	    obj.setRootPtr(root);
	    loop = true;
	    return;
	  }
	}
      }
    }
  }
}
template<typename ItemType>
twothreeTree<ItemType>::twothreeTree(TriNode<ItemType>* inputRootPtr){
  //std::cout<<"twothreeTree constructor has been called.\n";
  rootPtr=inputRootPtr;
}
template<typename ItemType>
void twothreeTree<ItemType>::setRootPtr(TriNode<ItemType>* inputRootPtr){
  //std::cout<<"setRootPtr() has been called.\n";
  rootPtr=inputRootPtr;
}
template<typename ItemType>
TriNode<ItemType>* twothreeTree<ItemType>::getRootPtr(){
  //std::cout<<"getRootPtr() has been called.\n";
  return rootPtr;
}

//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
template<typename ItemType>
void outputNode(TriNode<ItemType> temp, std::string which){
  //std::cout<<"Output Node has been called.\n";
  if(which=="ALL"){
    if(temp.isSmallItem){
      //std::cout<<"The Smaller Item is: "<<temp.getSmallItem()<<"\n";
      std::cout<<temp.getSmallItem()<<"\n";
    }
    if(temp.isLargeItem){
      //std::cout<<"The Larger Item is "<<temp.getLargeItem()<<"\n";
      std::cout<<temp.getLargeItem()<<"\n";
    }
  }
  if(which=="LEFT"){
    if(temp.isSmallItem){
      //std::cout<<"The Smaller Item is: "<<temp.getSmallItem()<<"\n";
       std::cout<<temp.getSmallItem()<<"\n";
    }
  }
  if(which=="RIGHT"){
    if(temp.isLargeItem){
      //std::cout<<"The Larger Item is: "<<temp.getLargeItem()<<"\n";
      std::cout<<temp.getLargeItem()<<"\n";
    }
  }
}
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
template<typename ItemType>
bool findItem(twothreeTree<ItemType> inputTree, ItemType target){
  TriNode<ItemType> temp = *inputTree.getRootPtr();
  if(temp.getSmallItem()==target or temp.getLargeItem()==target){
    //std::cout<<"The item has been found.\n";
    return true;
  }
  else{
    if(temp.isLeaf()){
      //std::cout<<"The item was not found.\n";
      return false;
    }
    else{
      if(temp.isLargeItem){
	if(target<temp.getSmallItem()){
	  twothreeTree<ItemType> temptreeleft(temp.getLeftChildPtr());
	  return findItem(temptreeleft, target);
	}
	else{
	  if(target<temp.getLargeItem()){
	    twothreeTree<ItemType> temptreemid(temp.getMidChildPtr());
	    return findItem(temptreemid, target);
	  }
	  else{
	    twothreeTree<ItemType> temptreeright(temp.getRightChildPtr());
	    return findItem(temptreeright, target);
	  }
	}
      }
      else{
	if(target<temp.getSmallItem()){
	  twothreeTree<ItemType> temptreeleft(temp.getLeftChildPtr());
	  return findItem(temptreeleft, target);
	}
	else{
	  twothreeTree<ItemType> temptreeright(temp.getRightChildPtr());
	  return findItem(temptreeright, target);
	}
      }
    }
  }
}
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
template<typename ItemType>
void inorder(twothreeTree<ItemType> inputTree){
  //std::cout<<"inorder() has been called.\n";
  TriNode<ItemType> temp = *inputTree.getRootPtr();
  if(temp.isLeaf()){
    //std::cout<<"The Current Node is a leaf.\n";
    outputNode(temp,"ALL");
  }
  else{
    //std::cout<<"The Current Node is NOT a leaf.\n";
    if(temp.isThreeNode()){
      //std::cout<<"The Current Node has 3 Children.\n";
      twothreeTree<ItemType> temptreeleft(temp.getLeftChildPtr());
      inorder(temptreeleft);
      //std::cout<<"Outputting the Smaller part of parent.\n";
      outputNode(temp,"LEFT");
      twothreeTree<ItemType> temptreemid(temp.getMidChildPtr());
      //std::cout<<"Outputting Mid Child of 3-Node.\n";
      inorder(temptreemid);
      //std::cout<<"Outputting the Larger Part of parent.\n";
      outputNode(temp,"RIGHT");
      twothreeTree<ItemType> temptreeright(temp.getRightChildPtr());
      //std::cout<<"Outputting Right Child of 3-Node.\n";
      inorder(temptreeright);
    }
    else{
      if(temp.isTwoNode()){
	//std::cout<<"The Current Node has 2 Children.\n";
	twothreeTree<ItemType> temptreeleft(temp.getLeftChildPtr());
	//std::cout<<"Outputting Left Child of 2-Node.\n";
        inorder(temptreeleft);
	//std::cout<<"Outputting 2-Node Parent.\n";
	outputNode(temp,"ALL");
        twothreeTree<ItemType> temptreeright(temp.getRightChildPtr());
	//std::cout<<"Outputting Right Child of 2-Node.\n";
        inorder(temptreeright);
      }
    }
  }
}
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
template<typename ItemType>
void insertItem(twothreeTree<ItemType> &inputTree, ItemType newItem){
  TriNode<ItemType>(*tempNode) = inputTree.getRootPtr();
  TriNode<ItemType>(*location);
  //std::cout<<"Right before find location\n";
  bool possible = inputTree.findLocation(newItem, tempNode, location);
  //std::cout<<"BACK FROM FIND LOCATION\n";
  if(!possible){
    //std::cout<<"THE ITEM IS ALREADY IN THE TREE!\n";
    return;
  }
  if((*location).hasLargeItem()){
    //std::cout<<"Need to split node.\n";
    (*location).setExtraItem(newItem);
    twothreeTree<ItemType> obj;
    TriNode<ItemType>* test = new TriNode<ItemType>;
    bool condition = false;
    identify="NULL";
    split(location, obj, test, condition);
    inputTree=obj;
    if(condition==true){
      inputTree.setRootPtr(test);
    }
  }
  else{
    //std::cout<<"Did not need to split any nodes.\n";
    ItemType temp = (*location).getSmallItem();
    if(newItem>temp){
      (*location).setLargeItem(newItem);
    }
    else{
      (*location).setLargeItem(temp);
      (*location).setSmallItem(newItem);
    }
  }
}

//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
template<typename ItemType>
void removeItem(twothreeTree<ItemType> &inputTree, ItemType target){
  TriNode<ItemType>* tempNode = inputTree.getRootPtr();
  TriNode<ItemType>* location;
  TriNode<ItemType>* temp;
  bool notpossible = inputTree.findLocation(target, tempNode, location);
  temp=location;
  if(notpossible){
    std::cout<<"THE REQUESTED ITEM WAS NOT FOUND!\n";
    return;
  }
  if(!(*location).isLeaf()){
    std::cout<<"NEED TO SWAP WITH INORDER SUCCESSOR\n";
    bool condition = true;
    if((*temp).hasLargeItem()){
	if((*temp).getLargeItem()==target){
	  temp = (*temp).getRightChildPtr();
	  std::cout<<"DOWN RIGHT\n";
	}
	else{
	  temp = (*temp).getMidChildPtr();
	  std::cout<<"DOWN MIDDLE\n";
	}
      }
    else{
      temp = (*temp).getRightChildPtr();
      std::cout<<"DOWN RIGHT\n";
    }	  
    while(condition){
      if((*temp).isLeaf()){
	std::cout<<"FOUND INORDER SUCCESSOR\n";
	ItemType tempItem = (*temp).getSmallItem();
	std::cout<<"SWAPPING WITH "<<tempItem<<"\n";
	(*temp).setSmallItem(target);
	if((*location).hasLargeItem()){
	  if((*location).getLargeItem()==target){
	    (*location).setLargeItem(tempItem);
	    location=temp;
	    std::cout<<"SUCCESSFUL SWAP\n";
	    condition=false;
	  }
	  else{
	    (*location).setSmallItem(tempItem);
	    location=temp;
	    std::cout<<"SUCCESSFUL SWAP\n";
	    condition=false;
	  }
	}
	else{
	  (*location).setSmallItem(tempItem);
	  location=temp;
	  std::cout<<"SUCCESSFUL SWAP\n";
	  condition=false;
	}
      }
      temp = (*temp).getLeftChildPtr();
    }
  }
  if((*location).hasLargeItem()){
    std::cout<<"THE TARGET ITEM IS IN A NODE WITH 2 ITEMS\n";
    if((*location).getLargeItem()==target){
      (*location).removeLargeItem();
      std::cout<<"REMOVED THE LARGE ITEM\n";
      return;
    }
    else{
      ItemType temp = (*location).getLargeItem();
      (*location).setSmallItem(temp);
      (*location).removeLargeItem();
      std::cout<<"REMOVED THE SMALL ITEM AND SWAPPED WITH LARGE\n";
      return;
    }
  }
  std::cout<<"THE TARGET ITEM IS IN ITS OWN NODE\n";
  (*location).removeSmallItem();
  bool internal = false;
  fixTree(location, internal, inputTree);
}
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
template<typename ItemType>
void fixTree(TriNode<ItemType> *&node, bool &internal, twothreeTree<ItemType> &inputTree){
  if(internal){
    std::cout<<"FIXTREE - INTERNAL\n";
  }
  else{
    std::cout<<"FIXTREE - LEAF\n";
  }
  TriNode<ItemType>* temp;
  
  if(!(*node).hasParent){
    std::cout<<"CASE NULL\n";
    node = (*node).getLeftChildPtr();
    inputTree.setRootPtr(node);
    return;
  }
  //(*node).removeSmallItem();
  temp = (*node).getParentPtr();
  if((*temp).hasLargeItem()){ //Parent is a 3-Node
    if((*temp).getRightChildPtr()==node){
      //CASE 1
      TriNode<ItemType>* middlechild = (*temp).getMidChildPtr();
      TriNode<ItemType>* leftchild = (*temp).getLeftChildPtr();
      if((*middlechild).hasLargeItem()){
	std::cout<<"CASE 1A & 1C\n";
	//CASE 1A & 1C
	ItemType temp1 = (*middlechild).getLargeItem();
	(*middlechild).removeLargeItem();
	ItemType temp2 = (*temp).getLargeItem();
	(*temp).setLargeItem(temp1);
	(*node).setSmallItem(temp2);
	return;
      }
      if((*leftchild).hasLargeItem()){
	std::cout<<"CASE 1B\n";
	//CASE 1B
	ItemType leftLarge = (*leftchild).getLargeItem();
	(*leftchild).removeLargeItem();
	ItemType parentSmall = (*temp).getSmallItem();
	(*temp).setSmallItem(leftLarge);
	ItemType middle = (*middlechild).getSmallItem();
	(*middlechild).setSmallItem(parentSmall);
	ItemType parentLarge = (*temp).getLargeItem();
	(*temp).setLargeItem(middle);
	(*node).setSmallItem(parentLarge);
	return;
      }
      std::cout<<"CASE 1D\n";
      //CASE 1D
      ItemType middle = (*middlechild).getSmallItem();
      (*middlechild).removeSmallItem();
      ItemType parentLarge = (*temp).getLargeItem();
      (*temp).setLargeItem(middle);
      (*temp).removeLargeItem();
      (*node).removeLeftChildPtr();
      (*node).removeRightChildPtr();
      (*node).setSmallItem(middle);
      (*node).setLargeItem(parentLarge);
      (*temp).removeMidChildPtr();
      return;
    }
    if((*temp).getLeftChildPtr()==node){
      //CASE 2
      TriNode<ItemType>* middlechild = (*temp).getMidChildPtr();
      TriNode<ItemType>* rightchild = (*temp).getRightChildPtr();
      if((*middlechild).hasLargeItem()){
	std::cout<<"CASE 2A & 2C\n";
	//CASE 2A & 2C
	ItemType middlesmall = (*middlechild).getSmallItem();
	ItemType middlelarge = (*middlechild).getLargeItem();
	(*middlechild).setSmallItem(middlelarge);
	(*middlechild).removeLargeItem();
	ItemType parentsmall = (*temp).getSmallItem();
	(*temp).setSmallItem(middlesmall);
	(*node).setSmallItem(parentsmall);
	return;
      }
      if((*rightchild).hasLargeItem()){
	std::cout<<"CASE 2B\n";
	//CASE 2B
	ItemType parentsmall = (*temp).getSmallItem();
	ItemType parentlarge = (*temp).getLargeItem();
	ItemType middle = (*middlechild).getSmallItem();
	ItemType rightsmall = (*rightchild).getSmallItem();
	ItemType rightlarge = (*rightchild).getLargeItem();
	(*rightchild).removeLargeItem();
	(*rightchild).setSmallItem(rightlarge);
	(*temp).setLargeItem(rightsmall);
	(*middlechild).setSmallItem(parentlarge);
	(*temp).setSmallItem(middle);
	(*node).setSmallItem(parentsmall);
	return;
      }
      std::cout<<"CASE 2D\n";
      //CASE 2D
      ItemType middle = (*middlechild).getSmallItem();
      (*middlechild).removeSmallItem();
      ItemType parentlarge = (*temp).getLargeItem();
      ItemType parentsmall = (*temp).getSmallItem();
      (*temp).removeLargeItem();
      (*temp).setSmallItem(parentlarge);
      (*node).setSmallItem(parentsmall);
      (*node).setLargeItem(middle);
      (*temp).removeMidChildPtr();
      return;
    }
    if((*temp).getMidChildPtr()==node){
      //CASE 3
      TriNode<ItemType>* leftchild = (*temp).getLeftChildPtr();
      TriNode<ItemType>* rightchild = (*temp).getRightChildPtr();
      if((*leftchild).hasLargeItem()){
	std::cout<<"CASE 3A & 3B\n";
	//CASE 3A & 3B
	ItemType leftlarge = (*leftchild).getLargeItem();
	(*leftchild).removeLargeItem();
	ItemType parentsmall = (*temp).getSmallItem();
	(*node).setSmallItem(parentsmall);
	(*temp).setSmallItem(leftlarge);
	return;
      }
      if((*rightchild).hasLargeItem()){
	std::cout<<"CASE 3C\n";
	//CASE 3C
	ItemType parentlarge = (*temp).getLargeItem();
	(*node).setSmallItem(parentlarge);
	ItemType rightsmall = (*rightchild).getSmallItem();
	ItemType rightlarge = (*rightchild).getLargeItem();
	(*rightchild).removeLargeItem();
	(*rightchild).setSmallItem(rightlarge);
	(*temp).setLargeItem(rightsmall);
	return;
      }
      std::cout<<"CASE 3D\n";
      //CASE 3D
      ItemType parentlarge = (*temp).getLargeItem();
      (*temp).removeLargeItem();
      ItemType rightsmall = (*rightchild).getSmallItem();
      (*rightchild).setSmallItem(parentlarge);
      (*rightchild).setLargeItem(rightsmall);
      (*temp).removeMidChildPtr();
      return;
    }
  }
  if((*temp).getRightChildPtr()==node){
    //CASE 4
    TriNode<ItemType>* leftchild = (*temp).getLeftChildPtr();
    if((*leftchild).hasLargeItem()){
      std::cout<<"CASE 4A\n";
      ItemType leftlarge = (*leftchild).getLargeItem();
      ItemType parent = (*temp).getSmallItem();
      (*leftchild).removeLargeItem();
      (*temp).setSmallItem(leftlarge);
      (*node).setSmallItem(parent);
      if(internal){
	std::cout<<"CAUGHT 1 CASE OF INTERNAL\n";      
	TriNode<ItemType>* leftmiddle = (*leftchild).getMidChildPtr();
	TriNode<ItemType>* leftright = (*leftchild).getRightChildPtr();
	TriNode<ItemType>* oldchild = (*node).getLeftChildPtr();
	(*node).setRightChildPtr(oldchild);
	(*node).setLeftChildPtr(leftright);
	(*leftchild).setRightChildPtr(leftmiddle);
	(*leftchild).removeMidChildPtr();
      }      
      return;
    }
    std::cout<<"INTERNAL 1\n";
    //ItemType leftChildValue = (*leftchild).getSmallValue();
    //ItemType parentValue = (*temp).getSmallValue();
    
    
    /*
    TriNode<ItemType>* tempNode = new TriNode<ItemType>;
    ItemType parent = (*temp).getSmallItem();
    ItemType left = (*leftchild).getSmallItem();
    TriNode<ItemType>* old = (*node).getLeftChildPtr();
    TriNode<ItemType>* leftNode = (*leftchild).getLeftChildPtr();
    TriNode<ItemType>* rightNode = (*leftchild).getRightChildPtr();
    (*temp).removeSmallItem();
    (*temp).removeLargeItem();
    (*temp).removeRightChildPtr();
    (*temp).removeMidChildPtr();
    (*leftchild).setLargeItem(parent);
    tempNode = leftchild;
    (*temp).setLeftChildPtr(tempNode);
    node = temp;
    if(internal){
      (*node).setLeftChildPtr(leftNode);
      (*node).setMidChildPtr(rightNode);
      (*node).setRightChildPtr(old);
    }  
    internal=true;
    fixTree(node, internal, inputTree);
    return;
    */
  }
  if((*temp).getLeftChildPtr()==node){
    //CASE 5
    TriNode<ItemType>* rightchild = (*temp).getRightChildPtr();
    if((*rightchild).hasLargeItem()){
      std::cout<<"CASE 5A\n";
      //CASE 5A
      ItemType rightsmall = (*rightchild).getSmallItem();
      ItemType rightlarge = (*rightchild).getLargeItem();
      (*rightchild).removeLargeItem();
      (*rightchild).setSmallItem(rightlarge);
      ItemType parent = (*temp).getSmallItem();
      (*temp).setSmallItem(rightsmall);
      (*node).setSmallItem(parent);
      if(internal){
	std::cout<<"CAUGHT 1 CASE OF INTERNAL\n";
	TriNode<ItemType>* rightmiddle = (*rightchild).getMidChildPtr();
	TriNode<ItemType>* rightleft = (*rightchild).getLeftChildPtr();
	(*rightchild).setLeftChildPtr(rightmiddle);
	(*rightchild).removeMidChildPtr();
	(*node).setRightChildPtr(rightleft);
      }	
      return;
    }
    /*
    std::cout<<"INTERNAL 2\n";
    TriNode<ItemType>* tempNode = new TriNode<ItemType>;
    ItemType parent = (*temp).getSmallItem();
    ItemType rightsmall = (*rightchild).getSmallItem();
    (*rightchild).removeSmallItem();
    (*temp).removeSmallItem();
    (*temp).removeRightChildPtr();
    (*temp).removeMidChildPtr();
    (*node).setSmallItem(parent);
    (*node).setLargeItem(rightsmall);
    tempNode = node;
    (*temp).setLeftChildPtr(tempNode);
    node=temp;
    internal=true;
    fixTree(node, internal, inputTree);
    return;
    */
  }
}
//--------------------------------------------------------------------------------------
//----------------------------------Main Function---------------------------------------
//--------------------------------------------------------------------------------------
int main(){
 std::vector<int> treeSize{64,128,256,512,1024,2048,4096,8192};
 int numSizes=treeSize.size();
 for(int i=0; i<numSizes; i++){
   int currentTreeSize = treeSize[i];
   int insertionCount=0;
   double totalInsertionTime=0;
   int totalTreeHeights=0;
   for(int i=0; i<100; i++){
     twothreeTree<int> tempTree;
     while(tempTree.getNodeCount()<currentTreeSize){
       srand(clock());
       int randomInput = rand() % 100000 + 1;
       time_t beforeInsertion = clock();
       bool inserted = tempTree.insertItem(randomInput);
       time_t afterInsertion = clock();
       double seconds = double(afterInsertion-beforeInsertion)/CLOCKS_PER_SEC;
	if(inserted){
	  insertionCount++;
	  totalInsertionTime+=seconds;
	}
      }
      int currentTreeHeight = tempTree.getHeight();
      totalTreeHeights+=currentTreeHeight;
    }
    double averageTreeHeight = totalTreeHeights/100;
    double averageInsertionTime = totalInsertionTime/insertionCount;
    double averageInsertionCount = insertionCount/100;
    std::cout<<"-----------Node Count = "<<currentTreeSize<<"-----------\n";
    std::cout<<"--> Average Tree Height: "<<averageTreeHeight<<"\n";
    std::cout<<"--> Average Insertion Time: "<<averageInsertionTime<<"\n";
    std::cout<<"--> Average Insertion Count: "<<averageInsertionCount<<"\n";
  }
}
//--------------------------------------------------------------------------------------
//----------------------------------End of Code-----------------------------------------
//--------------------------------------------------------------------------------------
