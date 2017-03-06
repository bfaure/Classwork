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


void read_file(std::string filename, std::vector<int> &array){
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
}
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
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
  bool isSmallItem;

  bool hasMidChild;
  bool hasLeftChild;
  bool hasRightChild;
  bool hasParent;

  bool hasSmallItem() const;
  bool hasLargeItem() const;
  bool hasExtraItem() const;
  
  void removeLargeItem();
  void removeSmallItem();
  
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

  void removeLeftChildPtr();
  void removeRightChildPtr();
  void removeMidChildPtr();
  void removeParentPtr();
};
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
bool TriNode<ItemType>::hasSmallItem() const{
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
  hasParent=true;
  isLargeItem=false;
  leftChildPtr=NULL;
  midChildPtr=NULL;
  rightChildPtr=NULL;
  extraChildPtr=NULL;
  isExtraItem=false;
  isSmallItem=false;
  hasMidChild=false;
  hasRightChild=false;
  hasLeftChild=false;
}
template<typename ItemType>
TriNode<ItemType>::TriNode(){
  hasParent=false;
  isSmallItem=false;
  isLargeItem=false;
  parentPtr=NULL;
  leftChildPtr=NULL;
  midChildPtr=NULL;
  rightChildPtr=NULL;
  isExtraItem=false;
  extraChildPtr=NULL;
  hasMidChild=false;
  hasRightChild=false;
  hasLeftChild=false;
}
template<typename ItemType>
void TriNode<ItemType>::setParentPtr(TriNode<ItemType>* parentptr){
  hasParent=true;
  parentPtr=parentptr;
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getParentPtr() const{
  if(!hasParent){
    //std::cout<<"WARNING: THERE IS NO PARENT POINTER!\n";
  }
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
  //std::cout<<"setLeftChildPtr() has been called.\n";
  hasLeftChild=true;
  leftChildPtr=leftptr;
  (*leftptr).setParentPtr(this);
}
template<typename ItemType>
void TriNode<ItemType>::setMidChildPtr(TriNode<ItemType>* midptr){
  //std::cout<<"setMidChildPtr() has been called.\n";
  hasMidChild=true;
  midChildPtr=midptr;
  (*midptr).setParentPtr(this);
}
template<typename ItemType>
void TriNode<ItemType>::setRightChildPtr(TriNode<ItemType>* rightptr){
  //std::cout<<"setRightChildPtr() has been called.\n";
  hasRightChild=true;
  rightChildPtr=rightptr;
  (*rightptr).setParentPtr(this);
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getRightChildPtr() const{
  //std::cout<<"getRightChildPtr() has been called.\n";
  if(!hasRightChild){
    //std::cout<<"WARNING: THERE IS NO RIGHT CHILD!\n";
  }
  return rightChildPtr;
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getMidChildPtr() const{
  //std::cout<<"getMidChildPtr() has been called.\n";
  if(!hasMidChild){
    //std::cout<<"WARNING: THERE IS NO MID CHILD!\n";
  }
  return midChildPtr;
}
template<typename ItemType>
TriNode<ItemType>* TriNode<ItemType>::getLeftChildPtr() const{
  //std::cout<<"getLeftChildPtr() has been called.\n";
  if(!hasLeftChild){
    //std::cout<<"WARNING: THERE IS NO LEFT CHILD!\n";
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
  isSmallItem = true;
  //std::cout<<"Small Item has been set to: "<<smallItem<<"\n";
}
template<typename ItemType>
ItemType TriNode<ItemType>::getLargeItem() const{
  //std::cout<<"getLargeItem() has been called.\n";
  //std::cout<<"The Larger Item is: "<<largeItem<<"\n";
  if(!isLargeItem){
    //std::cout<<"WARNING: THERE IS NO LARGE ITEM!\n";
  }
  return largeItem;
}
template<typename ItemType>
ItemType TriNode<ItemType>::getSmallItem() const{
  //std::cout<<"getSmallItem() has been called.\n";
  //std::cout<<"The Smaller Item is: "<<smallItem<<"\n";
  if(!isSmallItem){
    //std::cout<<"WARNING: THERE IS NO SMALL ITEM!\n";
  }
  return smallItem;
}
template<typename ItemType>
TriNode<ItemType>::TriNode(const ItemType& anItem){
  //std::cout<<"The Single-Input Constructor has been called.\n";
  smallItem = anItem;
  isSmallItem = true;
  isLargeItem = false;
  leftChildPtr = NULL;
  midChildPtr = NULL;
  rightChildPtr = NULL;
  parentPtr = NULL;
  isExtraItem=false;
  extraChildPtr=NULL;
  hasMidChild=false;
  hasLeftChild=false;
  hasRightChild=false;
  hasParent=false;
}
template<typename ItemType>
bool TriNode<ItemType>::isLeaf() const{
  //std::cout<<"isLeaf() has been called.\n";
  if(hasMidChild==true or hasRightChild==true or hasLeftChild==true){
    //std::cout<<"The node is a leaf.\n";
    return false;
  }
  else{
    return true;
  }
}
template<typename ItemType>
bool TriNode<ItemType>::isTwoNode() const{
  //std::cout<<"isTwoNode() has been calld.\n";
  int temp=0;
  if(hasMidChild){
    temp++;
  }
  if(hasLeftChild){
    temp++;
  }
  if(hasRightChild){
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
  if(hasLeftChild){
    temp++;
  }
  if(hasMidChild){
    temp++;
  }
  if(hasRightChild){
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
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
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
  int getHeight();
};
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
  //std::cout<<"FIND LOCATION\n";
  if((*currentNode).getSmallItem()==target or (*currentNode).getLargeItem()==target){
    //std::cout<<"DISREGARD WARNING HERE\n";
    location=currentNode;
    //outputNode(*location, "ALL");
    if((*currentNode).hasSmallItem()){
      if((*currentNode).getSmallItem()==target){
	//std::cout<<"HERE A\n";
	return false;
      }
    }
    if((*currentNode).hasLargeItem()){
      if((*currentNode).getLargeItem()==target){
	//std::cout<<"HERE B\n";
	return false;
      }
    }
  }
  //std::cout<<"INSIDE ELSE STATEMENT\n";
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
	    //std::cout<<"JUST CALLED IT\n";
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
    
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
int main(){
  twothreeTree<int> a;
  insertItem(a, 1);
  for(int i=15; i<4000000; i++){
    insertItem(a,i);
  }
  std::cout<<"Tree Height is: "<<a.getHeight()<<"\n";
    
}
/*
int main(){
  TriNode<int> Node_A(1);
  TriNode<int> Node_B(3);
  Node_A.setLargeItem(2);
  Node_B.setLargeItem(4);
  Node_A.setLeftChildPtr(&Node_B);
  TriNode<int> Node_C = *Node_A.getLeftChildPtr();
  Node_C.getLargeItem();
}
*/

  /*
template<typename K> class 23Tree{
protected:
  TriNode<K>* root;
  bool 
}
  */
/*
int main(){
  std::cout<<"\n\n|--------------------------------------------------|\n";
  std::cout<<"|--------------Sorting with mergeSort()------------|\n";
  std::cout<<"|----------FILE----------|----------STEPS----------|\n";
  std::string filePrefix = "dus-";
  std::string fileExtension = ".txt";
  std::vector<std::string> fileName = {"2","4","6","8","10","12","16","20","24"};
  int num_files = fileName.size();
  for(int i=0; i<num_files; i++){
    counter = 0;
    std::string file = filePrefix+fileName[i]+fileExtension;
    std::vector<int> theArray;
    read_file(file, theArray);
    int first = 0;
    int last = theArray.size()-1;
    SIZE = theArray.size();
    mergeSort(theArray, first, last);
    std::cout<<file<<"                     "<<counter<<"\n";
    //std::string to_write = "./"+filePrefix+fileName[i]+"_SORTED"+fileExtension;  //Save vector to its own file
    //std::ofstream output_file(to_write);
    //std::ostream_iterator<int> output_iterator(output_file, "\n");
    //std::copy(theArray.begin(), theArray.end(), output_iterator);
  }
}
*/
