/*
Brian Faure
RUID:150003563
NetID:bdf39
Prog. Methodology II
Project #2
Problem #3
December 2015
*/

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <time.h>

/*

--> Implementation of 2-3-4 Balanced Search Tree
--> **See written report for more detail**

PROGRAM CONTENTS:
--> #1.) QuadNode Class
--> #2.) QuadNode Class member function definitions
--> #3.) QuadTree Class
--> #4.) QuadTree Class member function definitions
--> #5.) Main function

     The main interface with the 2-3-4 tree is through the QuadTree<ItemType> class. This
class prescribes the following user-available functions: void setRootPtr(QuadNode Pointer),
int getTreeHeight(), void traverseInOrder(), void insertItem(ItemType newItem), void
printTree(), and bool searchTree(ItemType target).  Along with its member functions, the
QuadTree class has the following constructors: QuadTree(), QuadTree(QuadNode Pointer) as 
well as the default destructor.  

     To implement the 2-3-4 Tree, the QuadTree class relies heavily on the QuadNode<ItemType>
class.  The QuadNode class stores the nodes of the tree as well as the pointers from node to
node among the branches of the tree.  The QuadNode class also stores a large amount of the 
information about the nodes that makes the 2-3-4 Tree implementation possible.
*/

//--------------------------------------------------------------------------------------
//---------------------------------QuadNode Class---------------------------------------
//--------------------------------------------------------------------------------------
template<class ItemType>
class QuadNode{
private:
  QuadNode<ItemType>* parentPtr;
  QuadNode<ItemType>* firstChildPtr;
  QuadNode<ItemType>* secondChildPtr;
  QuadNode<ItemType>* thirdChildPtr;
  QuadNode<ItemType>* fourthChildPtr;
  
  bool hasParentPtr;
  bool firstchild;
  bool secondchild;
  bool thirdchild;
  bool fourthchild;
  int numChildren;
  bool numChildrenAccurate;
  
  ItemType smallItem;
  ItemType middleItem;
  ItemType largeItem;
  bool hassmall;
  bool hasmiddle;
  bool haslarge;
  bool numItemsAccurate;
  int numItems;
 
public:
  QuadNode();
  ~QuadNode();
  QuadNode(ItemType small);
  QuadNode(ItemType small, ItemType large);
  QuadNode(ItemType small, ItemType middle, ItemType large);

  int getNumItems();
  int getNumChildren();
  bool hasParent();
  bool isLeaf();
  bool isRoot();
  bool isLeafRoot();
  void details();
  bool isFourNode();
  bool isThreeNode();
  std::string kindOfChild();

  QuadNode<ItemType>* getParentPtr();
  QuadNode<ItemType>* getFirstChildPtr();
  QuadNode<ItemType>* getSecondChildPtr();
  QuadNode<ItemType>* getThirdChildPtr();
  QuadNode<ItemType>* getFourthChildPtr();

  void setParentPtr(QuadNode<ItemType>* newParent);
  void setFirstChildPtr(QuadNode<ItemType>* newchild);
  void setSecondChildPtr(QuadNode<ItemType>* newchild);
  void setThirdChildPtr(QuadNode<ItemType>* newchild);  
  void setFourthChildPtr(QuadNode<ItemType>* newchild);
  void resetChildren();
  void resetItems();

  void setSmallItem(ItemType small);
  void setMiddleItem(ItemType mid);
  void setLargeItem(ItemType large);

  ItemType getSmallItem();
  ItemType getLargeItem();
  ItemType getMiddleItem();

  void removeSmallItem();
  void removeLargeItem();
  void removeMiddleItem();

  void removeFirstChild();
  void removeSecondChild();
  void removeThirdChild();
  void removeFourthChild();
  void removeParentPtr();

  void swapItemSpots(std::string arg1, std::string arg2);
  void outputNode(std::string code);
  bool splitFourNode(bool &location);
  bool insert(ItemType newItem);
  void swapChildrenSpots(std::string arg1, std::string arg2);
  void printNode();
  bool searchNode(ItemType target, std::string &direction);
};
//--------------------------------------------------------------------------------------
//----------------------QuadNode Member Function Definitions----------------------------
//--------------------------------------------------------------------------------------
template<class ItemType>
bool QuadNode<ItemType>::searchNode(ItemType target, std::string &direction){
  direction = "NULL";
  int numtoCheck=getNumItems();
  ItemType smallest = getSmallItem();
  ItemType middle = getMiddleItem();
  ItemType largest = getLargeItem();
  if(numtoCheck==1){
    if(smallest==target){
      return true;
    }
    else{
      if(target<smallest){
	direction = "FIRST";
      }
      if(target>smallest){
        direction = "FOURTH";
      }
      return false;
    }
  }
  if(numtoCheck==2){
    if(smallest==target){
      return true;
    }
    if(largest==target){
      return true;
    }
    if(target<smallest){
      direction = "FIRST";
    }
    if(target>largest){
      direction = "FOURTH";
    }
    if(target>smallest and target<largest){
      direction = "SECOND";
    }
  }
  if(numtoCheck==3){
    if(smallest==target){
      return true;
    }
    if(middle==target){
      return true;
    }
    if(largest==target){
      return true;
    }
    if(target<smallest){
      direction = "FIRST";
    }
    if(target>largest){
      direction = "FOURTH";
    }
    if(target>smallest and target<middle){
      direction = "SECOND";
    }
    if(target>middle and target<largest){
      direction = "THIRD";
    }
  }
  return false;
}
template<class ItemType>
void QuadNode<ItemType>::printNode(){
  int number = getNumItems();
  int first = getSmallItem();
  int second = getMiddleItem();
  int third = getLargeItem();
  if(number==1){
    std::cout<<"("<<first<<")";
    return;
  }
  if(number==2){
    std::cout<<"("<<first<<","<<third<<")";
    return;
  }
  if(number==3){
    std::cout<<"("<<first<<","<<second<<","<<third<<")";
    return;
  }
}
template<class ItemType>
void QuadNode<ItemType>::swapChildrenSpots(std::string arg1, std::string arg2){
  if(arg1=="SECOND" and arg2=="THIRD"){
    QuadNode<ItemType> temp = *getThirdChildPtr();
    QuadNode<ItemType>* oldSecondPtr = getSecondChildPtr();
    setThirdChildPtr(oldSecondPtr);
    setSecondChildPtr(&temp);
    return;
  }
  if(arg1=="THIRD" and arg2=="SECOND"){
    QuadNode<ItemType>* tempLeft = new QuadNode<ItemType>;
    QuadNode<ItemType>* tempRight = new QuadNode<ItemType>;
    tempLeft = getSecondChildPtr();
    tempRight = getThirdChildPtr();
    setThirdChildPtr(tempLeft);
    setSecondChildPtr(tempRight);
    return;
  }
}
template<class ItemType>
std::string QuadNode<ItemType>::kindOfChild(){
  QuadNode<ItemType>* temp = parentPtr;
  int numChildren = (*temp).getNumChildren();
  if(numChildren==2){
    if((*temp).getFirstChildPtr()==this){
      return "FIRST";
    }
    if((*temp).getFourthChildPtr()==this){
      return "FOURTH";
    }
  }
  if(numChildren==3){
    if((*temp).getFirstChildPtr()==this){
      return "FIRST";
    }
    if((*temp).getSecondChildPtr()==this){
      return "SECOND";
    }
    if((*temp).getFourthChildPtr()==this){
      return "FOURTH";
    }
  }
  if(numChildren==4){  
    if((*temp).getFirstChildPtr()==this){
      return "FIRST";
    }
    if((*temp).getSecondChildPtr()==this){
      return "SECOND";
    }
    if((*temp).getThirdChildPtr()==this){
      return "THIRD";
    }
    if((*temp).getFourthChildPtr()==this){
      return "FOURTH";
    }
  }
  return "NULL";
}
template<class ItemType>
bool QuadNode<ItemType>::insert(ItemType newItem){
  numItemsAccurate=false;
  int tempNum=getNumItems();
  if(tempNum==3){
    ItemType oldsmallItem = getSmallItem();
    ItemType oldmiddleItem = getMiddleItem();
    ItemType oldlargeItem = getLargeItem();
    if(newItem==oldsmallItem){
      return false;
    }
    if(newItem==oldmiddleItem){
      return false;
    }
    if(newItem==oldlargeItem){
      return false;
    }
    return true;
  }
  if(tempNum==0){
    setSmallItem(newItem);
    return true;
  }
  if(tempNum==1){
    ItemType oldSmallItem = getSmallItem();
    if(newItem==oldSmallItem){
      return false;
    }
    setLargeItem(newItem);
    if(newItem<oldSmallItem){
      swapItemSpots("SMALL","LARGE");
    }
    return true;
  }
  if(tempNum==2){
    ItemType oldSmallItem = getSmallItem();
    ItemType oldLargeItem = getLargeItem();
    if(newItem==oldSmallItem){
      return false;
    }
    if(newItem==oldLargeItem){
      return false;
    }
    setMiddleItem(newItem);
    if(newItem<oldSmallItem){
      swapItemSpots("SMALL","MIDDLE");
      return true;
    }
    if(newItem>oldLargeItem){
      swapItemSpots("MIDDLE","LARGE");
      return true;
    }
    return true;
  }
  return true;
}
template<class ItemType>
bool QuadNode<ItemType>::splitFourNode(bool &location){
  //std::cout<<"Enered splitFourNode\n";
  ItemType tempLeft=getSmallItem();
  ItemType tempMiddle=getMiddleItem();
  ItemType tempRight=getLargeItem();
  if(isLeafRoot()){
    //std::cout<<"Splitting a Leaf Root.\n";
    //outputNode("ALL");
    resetItems();
    setSmallItem(tempMiddle);
    QuadNode<ItemType>* leftNode = new QuadNode<ItemType>;
    (*leftNode).setSmallItem(tempLeft);
    QuadNode<ItemType>* rightNode = new QuadNode<ItemType>;
    (*rightNode).setSmallItem(tempRight);
    setFirstChildPtr(leftNode);
    setFourthChildPtr(rightNode);
    return true;
  }
  else{
    //std::cout<<"Skipped leafRoot if statement in splitFourNode\n";
    if(isLeaf()){
      //std::cout<<"Entered isLeaf if statement in splitFourNode\n";
      QuadNode<ItemType>* parent = getParentPtr();
      std::string relation = kindOfChild();
      int siblings = (*parent).getNumChildren();
      if(siblings==2){
	//std::cout<<"CASE 1\n";
	//std::cout<<relation<<"\n";
	(*parent).insert(tempMiddle);
	removeMiddleItem();
	if(relation=="FIRST"){
	  //std::cout<<"CASE 1A\n";
	  QuadNode<ItemType>* midChild = new QuadNode<ItemType>;
	  (*midChild).setSmallItem(tempRight);
	  removeLargeItem();
	  (*parent).setSecondChildPtr(midChild);
	  return false;
	}
	if(relation=="FOURTH"){
	  //std::cout<<"CASE 1B\n";
	  resetItems();
	  setSmallItem(tempRight);
	  QuadNode<ItemType>* midChild = new QuadNode<ItemType>;
	  (*midChild).setSmallItem(tempLeft);
	  (*parent).setSecondChildPtr(midChild);
	  return false; //here
	}
	std::cout<<"ERROR in CASE 1\n";
      }
      if(siblings==3){
	//std::cout<<"CASE 2\n";
	QuadNode<ItemType>* parent = getParentPtr();
	std::string relation = kindOfChild();
	(*parent).insert(tempMiddle);
	removeMiddleItem();
	if(relation=="FIRST"){
	  //std::cout<<"CASE 2A\n";
	  //std::cout<<"HERE\n";
	  removeLargeItem();
	  QuadNode<ItemType>* newmid = new QuadNode<ItemType>;
	  (*newmid).setSmallItem(tempRight);
	  (*parent).setThirdChildPtr(newmid);
	  (*parent).swapChildrenSpots("THIRD","SECOND");
	  return false;  //here
	}
	if(relation=="FOURTH"){
	  //std::cout<<"CASE 2B\n";
	  removeLargeItem();
	  setSmallItem(tempRight);
	  QuadNode<ItemType>* newmid = new QuadNode<ItemType>;
	  (*newmid).setSmallItem(tempLeft);
	  (*parent).setThirdChildPtr(newmid);
	  location=false;
	  return false; //here
	}
	if(relation=="SECOND"){
	  //std::cout<<"CASE 2C\n";
	  removeLargeItem();
	  QuadNode<ItemType>* newmid = new QuadNode<ItemType>;
	  (*newmid).setSmallItem(tempRight);
	  (*parent).setThirdChildPtr(newmid);
	  return false;
	}
      }
    }
    else{
      //std::cout<<"CASE 3\n";
      QuadNode<ItemType>* tempFirst = getFirstChildPtr();
      QuadNode<ItemType>* tempSecond = getSecondChildPtr();
      QuadNode<ItemType>* tempThird = getThirdChildPtr();
      QuadNode<ItemType>* tempFourth = getFourthChildPtr();
      if(isRoot()){
	//std::cout<<"CASE 3A\n";
	//std::cout<<"Splitting a root\n";
	resetItems();
	resetChildren();
	setSmallItem(tempMiddle);
	QuadNode<ItemType>* leftNode = new QuadNode<ItemType>;
	(*leftNode).setSmallItem(tempLeft);
	(*leftNode).setFirstChildPtr(tempFirst);
	(*leftNode).setFourthChildPtr(tempSecond);
	QuadNode<ItemType>* rightNode = new QuadNode<ItemType>;
	(*rightNode).setSmallItem(tempRight);
	(*rightNode).setFirstChildPtr(tempThird);
	(*rightNode).setFourthChildPtr(tempFourth);
	setFirstChildPtr(leftNode);
	setFourthChildPtr(rightNode);
	return true;
	location=false;
      }
      else{
	//std::cout<<"CASE 4\n";
	QuadNode<ItemType>* parent = getParentPtr();
	std::string relation = kindOfChild();
	int siblings = (*parent).getNumChildren();
	if(siblings==2){
	  (*parent).insert(tempMiddle);
	  removeMiddleItem();
	  if(relation=="FOURTH"){
	    //std::cout<<"CASE 4A\n";
	    setSmallItem(tempRight);
	    removeLargeItem();
	    resetChildren();
	    QuadNode<ItemType>* newMid = new QuadNode<ItemType>;
	    (*newMid).setSmallItem(tempLeft);
	    (*parent).setSecondChildPtr(newMid);
	    (*newMid).setFirstChildPtr(tempFirst);
	    (*newMid).setFourthChildPtr(tempSecond);
	    setFirstChildPtr(tempThird);
	    setFourthChildPtr(tempFourth);
	    return false;
	  }
	  else{
	    if(relation=="FIRST"){
	      //std::cout<<"CASE 4B\n";
	      resetChildren();
	      removeLargeItem();
	      setFirstChildPtr(tempFirst);
	      setFourthChildPtr(tempSecond);
	      QuadNode<ItemType>* newMid = new QuadNode<ItemType>;
	      (*newMid).setSmallItem(tempRight);
	      (*newMid).setFirstChildPtr(tempThird);
	      (*newMid).setFourthChildPtr(tempFourth);
	      (*parent).setSecondChildPtr(newMid);
	      return false;
	    }
	  }
	  //std::cout<<"CASE 4 ERROR\n";
	}
	else{
	  //std::cout<<"CASE 5";
	  if(siblings==3){
	    (*parent).insert(tempMiddle);
	    removeMiddleItem();
	    if(relation=="FIRST"){
	      //std::cout<<"A\n";
	      resetChildren();
	      removeLargeItem();
	      setFirstChildPtr(tempFirst);
	      setFourthChildPtr(tempSecond);
	      QuadNode<ItemType>* newMid = new QuadNode<ItemType>;
	      (*newMid).setSmallItem(tempRight);
	      (*newMid).setFirstChildPtr(tempThird);
	      (*newMid).setFourthChildPtr(tempFourth);
	      (*parent).setThirdChildPtr(newMid);
	      (*parent).swapChildrenSpots("THIRD","SECOND");
	      return false;
	    }
	    if(relation=="FOURTH"){
	      //std::cout<<"B\n";
	      resetChildren();
	      setSmallItem(tempRight);
	      removeLargeItem();
	      setFirstChildPtr(tempThird);
	      setFourthChildPtr(tempFourth);
	      QuadNode<ItemType>* newMid = new QuadNode<ItemType>;
	      (*newMid).setSmallItem(tempLeft);
	      (*newMid).setFirstChildPtr(tempFirst);
	      (*newMid).setFourthChildPtr(tempSecond);
	      (*parent).setThirdChildPtr(newMid);
	      return false;
	    }
	    if(relation=="SECOND"){
	      //std::cout<<"C\n";
	      resetChildren();
	      removeLargeItem();
	      setFirstChildPtr(tempFirst);
	      setFourthChildPtr(tempSecond);
	      QuadNode<ItemType>* newMid = new QuadNode<ItemType>;
	      (*newMid).setSmallItem(tempRight);
	      (*newMid).setFirstChildPtr(tempThird);
	      (*newMid).setFourthChildPtr(tempFourth);
	      (*parent).setThirdChildPtr(newMid);
	      return false;
	    }
	  }
	}
      }
    }
  }
  std::cout<<"CASE 6\n";
  return true;
}	         
template<class ItemType>
bool QuadNode<ItemType>::isLeafRoot(){
  if(isLeaf() and isRoot()){
    return true;
  }
  else{
    return false;
  }
}  
template<class ItemType>
bool QuadNode<ItemType>::isFourNode(){
  int n=getNumItems();
  if(n==3){
    return true;
  }
  else{
    return false;
  }
}
template<class ItemType>
bool QuadNode<ItemType>::isThreeNode(){
  int n=getNumItems();
  if(n==2){
    return true;
  }
  else{
    return false;
  }
}
template<class ItemType>
ItemType QuadNode<ItemType>::getSmallItem(){
  return smallItem;
}
template<class ItemType>
ItemType QuadNode<ItemType>::getMiddleItem(){
  return middleItem;
}
template<class ItemType>
ItemType QuadNode<ItemType>::getLargeItem(){
  return largeItem;
}
template<class ItemType>
void QuadNode<ItemType>::outputNode(std::string code){
  int number = getNumItems();
  int temp1 = getSmallItem();
  int temp2 = getMiddleItem();
  int temp3 = getLargeItem();
  if(code=="ALL"){
    std::cout<<temp1<<"\n";
    if(number==2){
      std::cout<<temp3<<"\n";
    }
    if(number==3){
      std::cout<<temp2<<"\n"<<temp3<<"\n";
    }
    return;
  }
  if(code=="LEFT"){
    std::cout<<temp1<<"\n";
    return;
  }
  if(code=="MIDDLE"){
    std::cout<<temp2<<"\n";
    return;
  }
  if(code=="RIGHT"){
    std::cout<<temp3<<"\n";
    return;
  }
  if(code=="OUTSIDE"){
    std::cout<<temp1<<"\n"<<temp3<<"\n";
    return;
  }
}
template<class ItemType>
void QuadNode<ItemType>::swapItemSpots(std::string arg1, std::string arg2){
  if(arg1=="SMALL" and arg2=="LARGE"){
    ItemType A = getSmallItem();
    ItemType B = getLargeItem();
    setSmallItem(B);
    setLargeItem(A);
    return;
  }
  if(arg1=="LARGE" and arg2=="SMALL"){
    ItemType A = getLargeItem();
    ItemType B = getSmallItem();
    setLargeItem(B);
    setSmallItem(A);
    return;
  }
  if(arg1=="SMALL" and arg2=="MIDDLE"){
    ItemType A = getSmallItem();
    ItemType B = getMiddleItem();
    setSmallItem(B);
    setMiddleItem(A);
    return;
  }
  if(arg1=="MIDDLE" and arg2=="SMALL"){
    ItemType A = getMiddleItem();
    ItemType B = getSmallItem();
    setMiddleItem(B);
    setSmallItem(A);
    return;
  }
  if(arg1=="LARGE" and arg2=="MIDDLE"){
    ItemType A = getLargeItem();
    ItemType B = getMiddleItem();
    setLargeItem(B);
    setMiddleItem(A);
    return;
  }
  if(arg1=="MIDDLE" and arg2=="LARGE"){
    ItemType A = getMiddleItem();
    ItemType B = getLargeItem();
    setMiddleItem(B);
    setLargeItem(A);
    return;
  }
}
template<class ItemType>
void QuadNode<ItemType>::details(){
  int tempchildren = getNumChildren();
  int tempitems = getNumItems();
  std::cout<<"------------------------------\n";
  std::cout<<"This Node...\n";
  std::cout<<"-->Has "<<tempitems<<" items and "<<tempchildren<<" children.\n";
  if(isRoot()){
    std::cout<<"-->Is the root node.\n";
  }
  else{
    std::cout<<"-->Is not the root node.\n";
  }
  std::cout<<"------------------------------\n";
}
template<class ItemType>
bool QuadNode<ItemType>::isRoot(){
  if(hasParent()){
    return false;
  }
  else{
    return true;
  }
}
template<class ItemType>
bool QuadNode<ItemType>::isLeaf(){
  int n = getNumChildren();
  if(n==0){
    return true;
  }
  else{
    return false;
  }
}
template<class ItemType>
void QuadNode<ItemType>::removeParentPtr(){
  hasParentPtr=false;
}
template<class ItemType>
void QuadNode<ItemType>::removeThirdChild(){
  if(thirdchild){
    (*thirdChildPtr).removeParentPtr();
    numChildren--;
  }
  thirdchild=false;
}
template<class ItemType>
void QuadNode<ItemType>::removeFourthChild(){
  if(fourthchild){
    (*fourthChildPtr).removeParentPtr();
    numChildren--;
  }
  fourthchild=false;
}
template<class ItemType>
void QuadNode<ItemType>::removeSecondChild(){
  if(secondchild){
    (*secondChildPtr).removeParentPtr();
    numChildren--;
  }
  secondchild=false;
}
template<class ItemType>
void QuadNode<ItemType>::removeFirstChild(){
  if(firstchild){
    (*firstChildPtr).removeParentPtr();
    numChildren--;
  }
  firstchild=false;
}
template<class ItemType>
void QuadNode<ItemType>::removeSmallItem(){
  if(hassmall){
    numItems--;
  }
  hassmall=false;
}
template<class ItemType>
void QuadNode<ItemType>::removeLargeItem(){
  if(haslarge){
    numItems--;
  }
  haslarge=false;
}
template<class ItemType>
void QuadNode<ItemType>::removeMiddleItem(){
  if(hasmiddle){
    numItems--;
  }
  hasmiddle=false;
}
template<class ItemType>
void QuadNode<ItemType>::resetItems(){
  hassmall=false;
  hasmiddle=false;
  haslarge=false;
  numItems=0;
  numItemsAccurate=true;
}
template<class ItemType>
void QuadNode<ItemType>::resetChildren(){
  firstchild=false;
  secondchild=false;
  thirdchild=false;
  fourthchild=false;
  numChildren=0;
  numChildrenAccurate=true;
}
template<class ItemType>
void QuadNode<ItemType>::setSmallItem(ItemType small){
  smallItem=small;
  hassmall=true;
  numItemsAccurate=false;
}
template<class ItemType>
void QuadNode<ItemType>::setMiddleItem(ItemType mid){
  middleItem=mid;
  hasmiddle=true;
  numItemsAccurate=false;
}
template<class ItemType>
void QuadNode<ItemType>::setLargeItem(ItemType large){
  largeItem=large;
  haslarge=true;
  numItemsAccurate=false;
} 
template<class ItemType>
void QuadNode<ItemType>::setFourthChildPtr(QuadNode<ItemType>* newchild){
  fourthChildPtr=newchild;
  (*newchild).setParentPtr(this);
  fourthchild=true;
  numChildrenAccurate=false;
}
template<class ItemType>
void QuadNode<ItemType>::setThirdChildPtr(QuadNode<ItemType>* newchild){
  thirdChildPtr=newchild;
  (*newchild).setParentPtr(this);
  thirdchild=true;
  numChildrenAccurate=false;
}

template<class ItemType>
void QuadNode<ItemType>::setSecondChildPtr(QuadNode<ItemType>* newchild){
  secondChildPtr=newchild;
  (*newchild).setParentPtr(this);
  secondchild=true;
  numChildrenAccurate=false;
}
template<class ItemType>
void QuadNode<ItemType>::setFirstChildPtr(QuadNode<ItemType>* newchild){
  firstChildPtr=newchild;
  (*newchild).setParentPtr(this);
  firstchild=true;
  numChildrenAccurate=false;
}
template<class ItemType>
void QuadNode<ItemType>::setParentPtr(QuadNode<ItemType>* newParent){
  parentPtr=newParent;
  hasParentPtr=true;
}
template<class ItemType>
QuadNode<ItemType>* QuadNode<ItemType>::getSecondChildPtr(){
  return secondChildPtr;
}
template<class ItemType>
QuadNode<ItemType>* QuadNode<ItemType>::getThirdChildPtr(){
  return thirdChildPtr;
}

template<class ItemType>
QuadNode<ItemType>* QuadNode<ItemType>::getFourthChildPtr(){
  return fourthChildPtr;
}
template<class ItemType>
QuadNode<ItemType>* QuadNode<ItemType>::getFirstChildPtr(){
  return firstChildPtr;
} 
template<class ItemType>
QuadNode<ItemType>* QuadNode<ItemType>::getParentPtr(){
  return parentPtr;
}
template<class ItemType>
bool QuadNode<ItemType>::hasParent(){
  if(hasParentPtr){
    return true;
  }
  else{
    return false;
  }
}
template<class ItemType>
int QuadNode<ItemType>::getNumChildren(){
  int temp=0;
  if(numChildrenAccurate){
    return numChildren;
  }
  else{
    if(firstchild){
      temp++;
    }
    if(secondchild){
      temp++;
    }
    if(thirdchild){
      temp++;
    }
    if(fourthchild){
      temp++;
    }
    numChildren=temp;
    numChildrenAccurate=true;
    return temp;
  }
}
template<class ItemType>
int QuadNode<ItemType>::getNumItems(){
  int temp=0;
  if(numItemsAccurate){
    return numItems;
  }
  else{
    if(hassmall){
      temp++;
    }
    if(hasmiddle){
      temp++;
    }
    if(haslarge){
      temp++;
    }
    numItems=temp;
    numItemsAccurate=true;
    return temp;
  }
}
template<class ItemType>
QuadNode<ItemType>::QuadNode(ItemType small){
  resetChildren();
  resetItems();
  hasParentPtr=false;
  smallItem=small;
  numItems=1;
};
template<class ItemType>
QuadNode<ItemType>::QuadNode(ItemType small, ItemType large){
  resetChildren();
  resetItems();
  hasParentPtr=false;
  smallItem=small;
  hassmall=true;
  largeItem=large;
  haslarge=true;
  numItems=2;
}
template<class ItemType>
QuadNode<ItemType>::QuadNode(ItemType small, ItemType middle, ItemType large){
  resetChildren();
  resetItems();
  hasParentPtr=false;
  smallItem=small;
  hassmall=true;
  middleItem=middle;
  hasmiddle=true;
  largeItem=large;
  haslarge=true;
  numItems=3;
}
template<class ItemType>
QuadNode<ItemType>::QuadNode(){
  hasParentPtr=false;
  resetChildren();
  resetItems();
}
template<class ItemType>
QuadNode<ItemType>::~QuadNode(){
  //std::cout<<"A QuadNode was destroyed.\n";
}
//--------------------------------------------------------------------------------------
//---------------------------------QuadTree Class---------------------------------------
//--------------------------------------------------------------------------------------
template<class ItemType>
class QuadTree{
private:
  QuadNode<ItemType>* rootptr;
  int treeHeight;
  bool heightValidated;
  void traverseHelper(QuadNode<ItemType>* tempPtr);
  bool findLocation(ItemType target, QuadNode<ItemType> *&currentNode, bool &location);
  void offsetHelper(int offset);
  void printHelper(QuadNode<ItemType>* current, int offset, bool &newRow);
  bool searchHelper(QuadNode<ItemType>* vessel, ItemType target);
  QuadNode<ItemType>* getRootPtr();
  int countHelper(QuadNode<ItemType>* vesselNode);
  int count;
  
public:
  QuadTree();
  QuadTree(QuadNode<ItemType>* root);
  ~QuadTree();
 
  void setRootPtr(QuadNode<ItemType>* newRoot);
  int getTreeHeight();
  void traverseInOrder();
  bool insertItem(ItemType newItem);
  void printTree();
  bool searchTree(ItemType target);
  int getNodeCount();
};
//--------------------------------------------------------------------------------------
//----------------------QuadTree Member Function Definitions----------------------------
//--------------------------------------------------------------------------------------
template<class ItemType>
int QuadTree<ItemType>::getNodeCount(){
  QuadNode<ItemType>* vessel = rootptr;
  count=1;
  int nodeCount = countHelper(vessel);
  return count;
}
template<class ItemType>
int QuadTree<ItemType>::countHelper(QuadNode<ItemType>* vesselNode){
  if((*vesselNode).isLeaf()){
    return count;
  }
  else{
    int numChildren = (*vesselNode).getNumChildren();
    if(numChildren==2){
      count+=2;
      QuadNode<ItemType>* leftPtr = (*vesselNode).getFirstChildPtr();
      QuadNode<ItemType>* rightPtr = (*vesselNode).getFourthChildPtr();
      return (count+countHelper(leftPtr)+countHelper(rightPtr));
    }
    else{
      if(numChildren==3){
	count+=3;
	QuadNode<ItemType>* leftPtr = (*vesselNode).getFirstChildPtr();
	QuadNode<ItemType>* middlePtr = (*vesselNode).getSecondChildPtr();
	QuadNode<ItemType>* rightPtr = (*vesselNode).getFourthChildPtr();
	return (count+countHelper(leftPtr)+countHelper(middlePtr)+countHelper(rightPtr));
      }
      else{
	if(numChildren==4){
	  count+=4;
	  QuadNode<ItemType>* leftPtr = (*vesselNode).getFirstChildPtr();
	  QuadNode<ItemType>* middleLeftPtr = (*vesselNode).getSecondChildPtr();
	  QuadNode<ItemType>* middleRightPtr = (*vesselNode).getThirdChildPtr();
	  QuadNode<ItemType>* rightPtr = (*vesselNode).getFourthChildPtr();
	  return (count+countHelper(leftPtr)+countHelper(middleLeftPtr)+countHelper(middleRightPtr)+countHelper(rightPtr));
	}
      }
    }
  }
  return 0;
}
template<class ItemType>
bool QuadTree<ItemType>::searchHelper(QuadNode<ItemType>* vessel, ItemType target){
  std::string nextDirection;
  bool inNode = (*vessel).searchNode(target, nextDirection);
  if(inNode){
    return true;
  }
  if((*vessel).isLeaf()){
      return false;
  }
  else{
    if(nextDirection == "FIRST"){
      QuadNode<ItemType>* tempVessel = (*vessel).getFirstChildPtr();
      return searchHelper(tempVessel, target);
    }
    if(nextDirection == "SECOND"){
      QuadNode<ItemType>* tempVessel = (*vessel).getSecondChildPtr();
      return searchHelper(tempVessel, target);
    }
    if(nextDirection == "THIRD"){
      QuadNode<ItemType>* tempVessel = (*vessel).getThirdChildPtr();
      return searchHelper(tempVessel, target);
    }
    if(nextDirection == "FOURTH"){
      QuadNode<ItemType>* tempVessel = (*vessel).getFourthChildPtr();
      return searchHelper(tempVessel, target);
    }
    if(nextDirection == "NULL"){
      std::cout<<"NULL Direction ERROR when searching for "<<target<<"\n";
      return false;
    }
  }
  return false;
}
template<class ItemType>  
bool QuadTree<ItemType>::searchTree(ItemType target){
  QuadNode<ItemType>* vesselNode = getRootPtr();
  bool found = searchHelper(vesselNode, target);
  return found;
}
template<class ItemType>
void QuadTree<ItemType>::printHelper(QuadNode<ItemType>* current, int offset, bool &newRow){
  //std::cout<<"\n called \n";
  if((*current).isLeaf()){
    return;
  }
  int numChildren = (*current).getNumChildren();
  if(numChildren==2){
    if(newRow){
      std::cout<<"\n";
      offsetHelper(offset);
      std::cout<<" /   \\"<<"\n";
      offsetHelper(offset-2);
      std::cout<<"   ";
    }
    else{
      offsetHelper(2);
      std::cout<<" /      \\"<<"\n";
      offsetHelper(offset+2);
    }
    int addOffset=3;
    QuadNode<ItemType>* tempPtrLeft = (*current).getFirstChildPtr();
    int leftItems = (*tempPtrLeft).getNumItems();
    (*tempPtrLeft).printNode();
    if(leftItems==3){
      addOffset=1;
    }
    if(leftItems==2){
      addOffset=2;
    }
    for(int i=0; i<addOffset; i++){
      std::cout<<" ";
    }
    offsetHelper(1);
    QuadNode<ItemType>* tempPtrRight = (*current).getFourthChildPtr();
    (*tempPtrRight).printNode();
    newRow=true;
    printHelper(tempPtrLeft, offset-1, newRow);
    newRow=false;
    printHelper(tempPtrRight, offset+1, newRow);
    return;
  }
  else{
    if(numChildren==3){
      if(newRow){
	std::cout<<"\n";
	offsetHelper(offset);
	std::cout<<"/    |    \\"<<"\n";
	offsetHelper(offset-2);
      }
      else{
	offsetHelper(1);
	std::cout<<"  /       |      \\"<<"\n";
	offsetHelper(offset+2);
      }
  
      int addOffsetMid;
      int addOffsetRight;
      QuadNode<ItemType>* tempPtrLeft = (*current).getFirstChildPtr();
      int leftItems = (*tempPtrLeft).getNumItems();
      QuadNode<ItemType>* tempPtrMid = (*current).getSecondChildPtr();
      int midItems = (*tempPtrMid).getNumItems();
      QuadNode<ItemType>* tempPtrRight = (*current).getFourthChildPtr();
      (*tempPtrLeft).printNode();
      offsetHelper(1);
      if(leftItems==1){
	addOffsetMid=3;
      }
      if(leftItems==2){
	addOffsetMid=2;
      }
      if(leftItems==3){
	addOffsetMid=1;
      }
      if(midItems==3){
	addOffsetMid=1;
      }
      for(int i=0; i<addOffsetMid; i++){
	std::cout<<" ";
      }
      (*tempPtrMid).printNode();
      offsetHelper(1);
      if(midItems==3){
	addOffsetRight=1;
      }
      if(midItems==2){
	addOffsetRight=2;
      }
      if(midItems==1){
	addOffsetRight=3;
      }
      if((*tempPtrRight).getNumItems()==3){
	addOffsetRight=1;
      }
      for(int i=0; i<addOffsetRight; i++){
	std::cout<<" ";
      }
      (*tempPtrRight).printNode();
      newRow=true;
      printHelper(tempPtrLeft, offset-2, newRow);
      newRow=false;
      printHelper(tempPtrMid, offset, newRow);
      printHelper(tempPtrRight, offset+1, newRow);
      return;
    }
    else{
      if(numChildren==4){
	if(newRow){
	  std::cout<<"\n";
	  offsetHelper(offset-2);
	  std::cout<<" /      /     \\           \\"<<"\n";
	}
	else{
	  std::cout<<" /      /     \\           \\"<<"\n";
	}
	QuadNode<ItemType>* tempPtrLeft = (*current).getFirstChildPtr();
	QuadNode<ItemType>* tempPtrMidLeft = (*current).getSecondChildPtr();
	QuadNode<ItemType>* tempPtrMidRight = (*current).getThirdChildPtr();
	QuadNode<ItemType>* tempPtrRight = (*current).getFourthChildPtr();
	offsetHelper(offset-3);
	std::cout<<" ";
	(*tempPtrLeft).printNode();
	offsetHelper(2);
	(*tempPtrMidLeft).printNode();
	offsetHelper(1);
	(*tempPtrMidRight).printNode();
	offsetHelper(2);
	(*tempPtrRight).printNode();
	newRow=true;
	printHelper(tempPtrLeft,offset-3,newRow);
	newRow=false;
	printHelper(tempPtrMidLeft,offset-1,newRow);
	printHelper(tempPtrMidRight,offset+1,newRow);
	printHelper(tempPtrRight, offset+3, newRow);
	return;
      }
    }
  }
  return;
}
 
template<class ItemType>
void QuadTree<ItemType>::offsetHelper(int offset){
  int index=0;
  bool condition=false;
  if(index<offset){
    condition=true;
  }
  while(condition){
    std::cout<<"   ";
    index++;
    if(index>=offset){
      condition=false;
    }
  }
}
template<class ItemType>
void QuadTree<ItemType>::printTree(){
  QuadNode<ItemType>* rootPtr = rootptr;
  int num = (*rootPtr).getNumItems();
  int offset=0;
  bool row = true;
  int height = getTreeHeight();
  height = pow(4,height-1);
  height++;
  offsetHelper(height);
  std::cout<<"---ROOT---\n";
  offsetHelper(height);
  if(num==1){
    std::cout<<"   ";
  }
  if(num==2){
    std::cout<<"  ";
  }
  (*rootPtr).printNode();
  printHelper(rootPtr, height, row);
  std::cout<<"\n\n";
}
template<class ItemType>
bool QuadTree<ItemType>::insertItem(ItemType newItem){
  QuadNode<ItemType>* tempNode=rootptr;
  bool location = true;
  heightValidated=false;
  bool inserted = findLocation(newItem, tempNode, location);
  return inserted;
}
template<class ItemType>
bool QuadTree<ItemType>::findLocation(ItemType newItem, QuadNode<ItemType> *&currentNode, bool &location){
  if((*currentNode).isFourNode() and location==true){
    //std::cout<<"Entered first if statement in findLocation\n";
    bool possible = (*currentNode).insert(newItem);
    if(!possible){
      return false;
    }
    //std::cout<<"Right before splitFourNode\n";
    bool goUp = (*currentNode).splitFourNode(location);
    //std::cout<<"Right after splitFourNode\n";
    //goUp=false; //here
    if(!goUp){
      QuadNode<ItemType>* temp = (*currentNode).getParentPtr();
      location=false; 
      findLocation(newItem, temp, location);
    }
    else{
      findLocation(newItem, currentNode, location);
    }
  }
  
  else{
    //std::cout<<"Skipped first if statement in findLocation\n";
    if((*currentNode).isLeaf()){
      bool possible = (*currentNode).insert(newItem);
      if(possible){
	return true;
      }
      else{
	return false;
      }
    }
    else{
      int numItems = (*currentNode).getNumItems();
      if(numItems==1){
	//std::cout<<"NUM ITEMS = 1\n";
	ItemType tempItem = (*currentNode).getSmallItem();
	if(newItem>tempItem){
	  QuadNode<ItemType>* newNode = (*currentNode).getFourthChildPtr();
	  location=true;
	  findLocation(newItem, newNode, location);
	}
	else{
	  if(newItem<=tempItem){
	    if(newItem==tempItem){
	      return false;
	    }
	    QuadNode<ItemType>* newNode = (*currentNode).getFirstChildPtr();
	    location=true;
	    findLocation(newItem, newNode, location);
	  }
	}
      }
      else{
	if(numItems==2){
	  //std::cout<<"NUM ITEMS = 2\n";
	  ItemType smallerItem = (*currentNode).getSmallItem();
	  ItemType largerItem = (*currentNode).getLargeItem();
	  if(newItem<=smallerItem){
	    if(newItem==smallerItem){
	      return false;
	    }
	    QuadNode<ItemType>* newNode = (*currentNode).getFirstChildPtr();
	    location=true;
	    //std::cout<<"FL CODE 1\n";
	    findLocation(newItem, newNode, location);
	  }
	  else{
	    if(newItem>=largerItem){
	      if(newItem==largerItem){
		return false;
	      }
	      QuadNode<ItemType>* newNode = (*currentNode).getFourthChildPtr();
	      location=true;
	      findLocation(newItem, newNode, location);
	    }
	    else{
	      QuadNode<ItemType>* newNode = (*currentNode).getSecondChildPtr();
	      location=true;
	      findLocation(newItem, newNode, location);
	    }
	  }
	}
	else{
	  //std::cout<<"NUM ITEMS = 3\n";
	  ItemType small = (*currentNode).getSmallItem();
	  ItemType mid = (*currentNode).getMiddleItem();
	  ItemType large = (*currentNode).getLargeItem();
	  if(newItem<=small){
	    if(newItem==small){
	      return false;
	    }
	    QuadNode<ItemType>* newNode = (*currentNode).getFirstChildPtr();
	    location=true;
	    findLocation(newItem, newNode, location);
	  }
	  else{
	    if(newItem>=large){
	      if(newItem==large){
		return false;
	      }
	      QuadNode<ItemType>* newNode = (*currentNode).getFourthChildPtr();
	      location=true;
	      findLocation(newItem, newNode, location);
	    }
	    else{
	      if(newItem>small and newItem<=mid){
		if(newItem==mid){
		  return false;
		}
		QuadNode<ItemType>* newNode = (*currentNode).getSecondChildPtr();
		location=true;
		findLocation(newItem, newNode, location);
	      }
	      else{
		if(newItem==mid){
		  return false;
		}
		QuadNode<ItemType>* newNode = (*currentNode).getThirdChildPtr();
		location=true;
		findLocation(newItem, newNode, location);
	      }
	    }
	  }
	}
      }
    }
  }
  return true;
}	 
template<class ItemType>
void QuadTree<ItemType>::traverseHelper(QuadNode<ItemType>* tempPtr){
  if((*tempPtr).isLeaf()){
    (*tempPtr).outputNode("ALL");
  }
  else{
    int numchildren = (*tempPtr).getNumChildren();
    if(numchildren==2){
      QuadNode<ItemType>* tempPtrLeft=(*tempPtr).getFirstChildPtr();
      traverseHelper(tempPtrLeft);
      (*tempPtr).outputNode("LEFT");
      QuadNode<ItemType>* tempPtrRight=(*tempPtr).getFourthChildPtr();
      traverseHelper(tempPtrRight);
    }
    else{
       if(numchildren==3){
	 QuadNode<ItemType>* tempPtrLeft=(*tempPtr).getFirstChildPtr();
	 traverseHelper(tempPtrLeft);
	 (*tempPtr).outputNode("LEFT");
	 QuadNode<ItemType>* tempPtrMiddle=(*tempPtr).getSecondChildPtr();
	 traverseHelper(tempPtrMiddle);
	 (*tempPtr).outputNode("RIGHT");
	 QuadNode<ItemType>* tempPtrRight=(*tempPtr).getFourthChildPtr();
	 traverseHelper(tempPtrRight);
       }
       else{
	 if(numchildren==4){
	   QuadNode<ItemType>* tempPtrLeft=(*tempPtr).getFirstChildPtr();
	   traverseHelper(tempPtrLeft);
	   (*tempPtr).outputNode("LEFT");
	   QuadNode<ItemType>* tempPtrMiddleLeft=(*tempPtr).getSecondChildPtr();
	   traverseHelper(tempPtrMiddleLeft);
	   (*tempPtr).outputNode("MIDDLE");
	   QuadNode<ItemType>* tempPtrMiddleRight=(*tempPtr).getThirdChildPtr();
	   traverseHelper(tempPtrMiddleRight);
	   (*tempPtr).outputNode("RIGHT");
	   QuadNode<ItemType>* tempPtrRight=(*tempPtr).getFourthChildPtr();
	   traverseHelper(tempPtrRight);
	 }
       }
    }
  }
}
template<class ItemType>
void QuadTree<ItemType>::traverseInOrder(){
  QuadNode<ItemType>* temp = rootptr;
  traverseHelper(temp);
}
template<class ItemType>
int QuadTree<ItemType>::getTreeHeight(){
  if(heightValidated){
    return treeHeight;
  }
  else{
    int height=1;
    QuadNode<ItemType>* vessel=rootptr;
    bool condition=true;
    while(condition){
      if((*vessel).isLeaf()){
	condition=false;
      }
      else{
	height++;
	vessel=(*vessel).getFirstChildPtr();
      }
    }
    treeHeight=height;
    heightValidated=true;
    return height;
  }
}
template<class ItemType>
QuadNode<ItemType>* QuadTree<ItemType>::getRootPtr(){
  return rootptr;
}
template<class ItemType>
QuadTree<ItemType>::QuadTree(){
  QuadNode<ItemType>* temp = new QuadNode<ItemType>;
  heightValidated=false;
  rootptr=temp;
}
template<class ItemType>
QuadTree<ItemType>::QuadTree(QuadNode<ItemType>* root){
  heightValidated=false;
  rootptr=root;
}
template<class ItemType>
QuadTree<ItemType>::~QuadTree(){
  //std::cout<<"A QuadTree was destroyed.\n";
}
template<class ItemType>
void QuadTree<ItemType>::setRootPtr(QuadNode<ItemType>* newRoot){
  heightValidated=false;
  rootptr=newRoot;
}
//--------------------------------------------------------------------------------------
//---------------------------------MAIN FUNCTION----------------------------------------
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
      QuadTree<int> tempTree;
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
      int currentTreeHeight = tempTree.getTreeHeight();
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
