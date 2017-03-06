/*
Brian Faure
RUID:150003563
NetID:bdf39
Prog. Methodology II
Project #2
*/


#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iterator>
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
void read_file(std::string filename, std::vector<int> &array){
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
}
//--------------------------------------------------------------------
//------------------------TriNode Class-------------------------------
//--------------------------------------------------------------------
template<typename ItemType>
class TriNode{
private:
  ItemType smallItem;
  ItemType largeItem;
  ItemType extraItem;

  TriNode<ItemType>* parentPtr;
  TriNode<ItemType>* leftChildPtr;
  TriNode<ItemType>* midChildPtr;
  TriNode<ItemType>* rightChildPtr;
  TriNode<ItemType>* extraChildPtr;
public:
  TriNode();
  TriNode(const ItemType& anItem);
  TriNode(TriNode<ItemType>* parentptr);
  TriNode(const ItemType& anItem, TriNode<ItemType>* leftPtr,
	  TriNode<ItemType>* midPtr, TriNode<ItemType>* rightPtr);
  friend void swap(TriNode<ItemType>& first, TriNode<ItemType>& second){
    using std::swap;
    swap(first.smallItem, second.smallItem);
    swap(first.largeItem, second.largeItem);
    swap(first.extraItem, second.extraItem);
    swap(first.parentPtr, second.parentPtr);
    swap(first.leftChildPtr, second.leftChildPtr);
    swap(first.midChildPtr, second.midChildPtr);
    swap(first.rightChildPtr, second.rightChildPtr);
    swap(first.extraChildPtr, second.extraChildPtr);
    swap(first.isLargeItem, second.isLargeItem);
    swap(first.isExtraItem, second.isExtraItem);
  }
  bool isLeaf() const;
  bool isTwoNode() const;
  bool isThreeNode() const;

  ItemType getSmallItem() const;
  ItemType getLargeItem() const;
  ItemType getExtraItem() const;
  
  bool isLargeItem;
  bool isExtraItem;
  bool hasLargeItem() const;
  bool hasExtraItem() const;
  
  void setExtraItem(const ItemType& anItem);
  void setSmallItem(const ItemType& anItem);
  void setLargeItem(const ItemType& anItem);

  TriNode<ItemType>* getLeftChildPtr() const;
  TriNode<ItemType>* getMidChildPtr() const;
  TriNode<ItemType>* getRightChildPtr() const;
  TriNode<ItemType>* getParentPtr() const;
  TriNode<ItemType>* getExtraChildPtr() const;

  void setLeftChildPtr(TriNode<ItemType>* leftptr);
  void setMidChildPtr(TriNode<ItemType>* midptr);
  void setRightChildPtr(TriNode<ItemType>* rightptr);
  void setParentPtr(TriNode<ItemType>* parentptr);
  void setExtraChildPtr(TriNode<ItemType>* extraptr);
};
//--------------------------------------------------------------------
//--------------------TriNode Function Definitions--------------------
//--------------------------------------------------------------------
template<typename ItemType>
void TriNode<ItemType>::setExtraChildPtr(TriNode<ItemType>* extraptr){
  extraChildPtr=extraptr;
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getExtraChildPtr() const{
  return extraChildPtr;
}
template<typename ItemType>
bool TriNode<ItemType>::hasExtraItem() const{
  if(isExtraItem){
    return true;
  }
  else{
    return false;
  }
}
template<typename ItemType>
void TriNode<ItemType>::setExtraItem(const ItemType& anItem){
  isExtraItem=true;
  extraItem=anItem;
}
template<typename ItemType>
ItemType TriNode<ItemType>::getExtraItem() const{
  return extraItem;
}
template<typename ItemType>
TriNode<ItemType>::TriNode(TriNode<ItemType>* parentptr){
  parentPtr=parentptr;
  isLargeItem=false;
  leftChildPtr=NULL;
  midChildPtr=NULL;
  rightChildPtr=NULL;
  extraChildPtr=NULL;
  isExtraItem=false;
}
template<typename ItemType>
TriNode<ItemType>::TriNode(){
  isLargeItem=false;
  parentPtr=NULL;
  leftChildPtr=NULL;
  midChildPtr=NULL;
  rightChildPtr=NULL;
  isExtraItem=false;
  extraChildPtr=NULL;
}
template<typename ItemType>
void TriNode<ItemType>::setParentPtr(TriNode<ItemType>* parentptr){
  parentPtr=parentptr;
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getParentPtr() const{
  return parentPtr;
}
template<typename ItemType>
bool TriNode<ItemType>::hasLargeItem() const{
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
  //std::cout<<"Constructor with 4 inputs has been called.\n";
  smallItem=anItem;
  leftChildPtr=leftPtr;
  midChildPtr=midPtr;
  rightChildPtr=rightPtr;
  parentPtr=NULL;
  isLargeItem=false;
  isExtraItem=false;
  extraChildPtr=NULL;
}
template<typename ItemType>
void TriNode<ItemType>::setLeftChildPtr(TriNode<ItemType>* leftptr){
  //std::cout<<"setLeftChildPtr() has been called.\n";
  leftChildPtr=leftptr;
  (*leftptr).setParentPtr(this);
}
template<typename ItemType>
void TriNode<ItemType>::setMidChildPtr(TriNode<ItemType>* midptr){
  //std::cout<<"setMidChildPtr() has been called.\n";
  midChildPtr=midptr;
  (*midptr).setParentPtr(this);
}
template<typename ItemType>
void TriNode<ItemType>::setRightChildPtr(TriNode<ItemType>* rightptr){
  //std::cout<<"setRightChildPtr() has been called.\n";
  rightChildPtr=rightptr;
  (*rightptr).setParentPtr(this);
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getRightChildPtr() const{
  //std::cout<<"getRightChildPtr() has been called.\n";
  if(rightChildPtr==NULL){
    //std::cout<<"There is no Right Child!\n";
  }
  return rightChildPtr;
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getMidChildPtr() const{
  //std::cout<<"getMidChildPtr() has been called.\n";
  if(midChildPtr==NULL){
    //std::cout<<"There is no Middle Child!\n";
  }
  return midChildPtr;
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getLeftChildPtr() const{
  //std::cout<<"getLeftChildPtr() has been called.\n";
  if(leftChildPtr==NULL){
    //std::cout<<"There is no Left Child!\n";
  }
  return leftChildPtr;
}
template<typename ItemType>
void TriNode<ItemType>::setLargeItem(const ItemType& anItem){
  //std::cout<<"setLargeItem() has been called.\n";
  largeItem = anItem;
  isLargeItem=true;
  //std::cout<<"Large Item has been set to: "<<largeItem<<"\n";
}
template<typename ItemType>
void TriNode<ItemType>::setSmallItem(const ItemType& anItem){
  //std::cout<<"setSmallItem() has been called.\n";
  smallItem = anItem;
  //std::cout<<"Small Item has been set to: "<<smallItem<<"\n";
}
template<typename ItemType>
ItemType TriNode<ItemType>::getLargeItem() const{
  //std::cout<<"getLargeItem() has been called.\n";
  //std::cout<<"The Larger Item is: "<<largeItem<<"\n";
  return largeItem;
}
template<typename ItemType>
ItemType TriNode<ItemType>::getSmallItem() const{
  //std::cout<<"getSmallItem() has been called.\n";
  //std::cout<<"The Smaller Item is: "<<smallItem<<"\n";
  return smallItem;
}
template<typename ItemType>
TriNode<ItemType>::TriNode(const ItemType& anItem){
  //std::cout<<"The Single-Input Constructor has been called.\n";
  smallItem = anItem;
  isLargeItem = false;
  leftChildPtr = NULL;
  midChildPtr = NULL;
  rightChildPtr = NULL;
  parentPtr = NULL;
  isExtraItem=false;
  extraChildPtr=NULL;
}
template<typename ItemType>
bool TriNode<ItemType>::isLeaf() const{
  //std::cout<<"isLeaf() has been called.\n";
  if(leftChildPtr==NULL && midChildPtr==NULL && rightChildPtr==NULL){
    //std::cout<<"The node is a leaf.\n";
    return true;
  }
  else{
    //std::cout<<"The node is not a leaf.\n";
    return false;
  }
}
template<typename ItemType>
bool TriNode<ItemType>::isTwoNode() const{
  //std::cout<<"isTwoNode() has been calld.\n";
  int temp=0;
  if(leftChildPtr != NULL){
    temp++;
  }
  if(midChildPtr != NULL){
    temp++;
  }
  if(rightChildPtr != NULL){
    temp++;
  }
  if(temp==2){
    //std::cout<<"The node is a 2-Node.\n";
    return true;
  }
  else{
    //std::cout<<"The node is not a 2-Node.\n";
    return false;
  }
}
template<typename ItemType>
bool TriNode<ItemType>::isThreeNode() const{
  //std::cout<<"isThreeNode() has been called.\n";
  int temp=0;
  if(leftChildPtr != NULL){
    temp++;
  }
  if(midChildPtr != NULL){
    temp++;
  }
  if(rightChildPtr != NULL){
    temp++;
  }
  if(temp==3){
    //std::cout<<"The node is a 3-Node.\n";
    return true;
  }
  else{
    //std::cout<<"The node is not a 3-Node.\n";
    return false;
  }
}
//--------------------------------------------------------------------
//----------------------twothreeTree Class----------------------------
//--------------------------------------------------------------------
template<typename ItemType>
class twothreeTree{
private:
  TriNode<ItemType>* rootPtr;
public:
  twothreeTree();
  twothreeTree(TriNode<ItemType>* inputRootPtr);
  void setRootPtr(TriNode<ItemType>* inputRootPtr);
  TriNode<ItemType>* getRootPtr();
  bool findLocation(ItemType target, TriNode<ItemType>* currentNode, TriNode<ItemType> *&location);
};
//--------------------------------------------------------------------
//---------------twothreeTree Function Definitions--------------------
//--------------------------------------------------------------------
template<typename ItemType>
twothreeTree<ItemType>::twothreeTree(){
  rootPtr=NULL;
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
template<typename ItemType>
bool twothreeTree<ItemType>::findLocation(ItemType target, TriNode<ItemType>* currentNode, TriNode<ItemType> *&location){
  if((*currentNode).getSmallItem()==target or (*currentNode).getLargeItem()==target){
    location=currentNode;
    return false;
  }
  else{
    if((*currentNode).isLeaf()){
      //std::cout<<"The item was not found.\n";
      location=currentNode;
      return true;
    }
    else{
      if((*currentNode).hasLargeItem()){
	if(target<(*currentNode).getSmallItem()){
	  return findLocation(target, (*currentNode).getLeftChildPtr(), location);
	}
	else{
	  if(target<(*currentNode).getLargeItem()){
	    return findLocation(target, (*currentNode).getMidChildPtr(), location);
	  }
	  else{
	    return findLocation(target, (*currentNode).getRightChildPtr(), location);
	  }
	}
      }
      else{
	if(target<(*currentNode).getSmallItem()){
	  return findLocation(target, (*currentNode).getLeftChildPtr(), location);
	}
	else{
	  return findLocation(target, (*currentNode).getRightChildPtr(), location);
	}
      }
    }
  }
}
//--------------------------------------------------------------------
//------------------------split Function------------------------------
//--------------------------------------------------------------------
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
  if((*n).getParentPtr()==NULL){
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
    //inorder(obj);
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
//--------------------------------------------------------------------
//---------------------outputNode Function----------------------------
//--------------------------------------------------------------------
template<typename ItemType>
void outputNode(TriNode<ItemType> temp, std::string which){
  //std::cout<<"Output Node has been called.\n";
  if(which=="ALL"){
    std::cout<<"The Smaller Item is: "<<temp.getSmallItem()<<"\n";
    if(temp.isLargeItem){
      std::cout<<"The Larger Item is "<<temp.getLargeItem()<<"\n";
    }
  }
  if(which=="LEFT"){
    std::cout<<"The Smaller Item is: "<<temp.getSmallItem()<<"\n";
  }
  if(which=="RIGHT"){
    if(temp.isLargeItem){
      std::cout<<"The Larger Item is: "<<temp.getLargeItem()<<"\n";
    }
  }
}
//--------------------------------------------------------------------
//----------------------findItem Function-----------------------------
//--------------------------------------------------------------------
template<typename ItemType>
bool findItem(twothreeTree<ItemType> inputTree, ItemType target){
  TriNode<ItemType> temp = *inputTree.getRootPtr();
  if(temp.getSmallItem()==target or temp.getLargeItem()==target){
    std::cout<<"The item has been found.\n";
    return true;
  }
  else{
    if(temp.isLeaf()){
      std::cout<<"The item was not found.\n";
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
//--------------------------------------------------------------------
//-----------------------inorder Function-----------------------------
//--------------------------------------------------------------------
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
//--------------------------------------------------------------------
//---------------------insertItem Function----------------------------
//--------------------------------------------------------------------
template<typename ItemType>
void insertItem(twothreeTree<ItemType> &inputTree, ItemType newItem){
  TriNode<ItemType>(*tempNode) = inputTree.getRootPtr();
  TriNode<ItemType>(*location);
  inputTree.findLocation(newItem, tempNode, location);
  if((*location).hasLargeItem()){
    //std::cout<<"Need to split node.\n";
    (*location).setExtraItem(newItem);
    twothreeTree<ItemType> obj;
    TriNode<ItemType>* test = new TriNode<ItemType>;
    bool condition = false;
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
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
int main(){
  std::cout<<"--------------------------------\n";
  TriNode<int> Node_A(10);
  Node_A.setLargeItem(20);
  twothreeTree<int> test(&Node_A);
  insertItem(test, 15);
  insertItem(test, 5);
  insertItem(test, 30);
  insertItem(test, 40);
  insertItem(test, 25);
  insertItem(test, 50);
  insertItem(test, 100);
  insertItem(test, 150);
  insertItem(test, 200);
  inorder(test);
  std::cout<<"--------------------------------\n";
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
