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
  ItemType smallItem;
  ItemType largeItem;

  TriNode<ItemType>* leftChildPtr;
  TriNode<ItemType>* midChildPtr;
  TriNode<ItemType>* rightChildPtr;
public:
  TriNode();
  TriNode(const ItemType& anItem);
  TriNode(const ItemType& anItem, TriNode<ItemType>* leftPtr,
	  TriNode<ItemType>* midPtr, TriNode<ItemType>* rightPtr);
  bool isLeaf() const;
  bool isTwoNode() const;
  bool isThreeNode() const;

  ItemType getSmallItem() const;
  ItemType getLargeItem() const;

  void setSmallItem(const ItemType& anItem);
  void setLargeItem(const ItemType& anItem);

  TriNode<ItemType>* getLeftChildPtr() const;
  TriNode<ItemType>* getMidChildPtr() const;
  TriNode<ItemType>* getRightChildPtr() const;

  void setLeftChildPtr(TriNode<ItemType>* leftptr);
  void setMidChildPtr(TriNode<ItemType>* midptr);
  void setRightChildPtr(TriNode<ItemType>* rightptr);
};
template<typename ItemType>
TriNode<ItemType>::TriNode(const ItemType& anItem, TriNode<ItemType>* leftPtr,
			   TriNode<ItemType>* midPtr, TriNode<ItemType>* rightPtr){
  //std::cout<<"Constructor with 4 inputs has been called.\n";
  smallItem=anItem;
  leftChildPtr=leftPtr;
  midChildPtr=midPtr;
  rightChildPtr=rightPtr;
  largeItem=0;
}
template<typename ItemType>
void TriNode<ItemType>::setLeftChildPtr(TriNode<ItemType>* leftptr){
  //std::cout<<"setLeftChildPtr() has been called.\n";
  leftChildPtr=leftptr;
}
template<typename ItemType>
void TriNode<ItemType>::setMidChildPtr(TriNode<ItemType>* midptr){
  //std::cout<<"setMidChildPtr() has been called.\n";
  midChildPtr=midptr;
}
template<typename ItemType>
void TriNode<ItemType>::setRightChildPtr(TriNode<ItemType>* rightptr){
  //std::cout<<"setRightChildPtr() has been called.\n";
  rightChildPtr=rightptr;
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
  largeItem = 0;
  leftChildPtr = NULL;
  midChildPtr = NULL;
  rightChildPtr = NULL;
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
};
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
  if(which=="ALL"){
    if(temp.getSmallItem()!=0){
      std::cout<<"The Smaller Item is: "<<temp.getSmallItem()<<"\n";
    }
    if(temp.getLargeItem()!=0){
      std::cout<<"The Larger Item is "<<temp.getLargeItem()<<"\n";
    }
  }
  if(which=="LEFT"){
    if(temp.getSmallItem()!=0){
      std::cout<<"The Smaller Item is: "<<temp.getSmallItem()<<"\n";
    }
  }
  if(which=="RIGHT"){
    if(temp.getLargeItem()!=0){
      std::cout<<"The Larger Item is: "<<temp.getLargeItem()<<"\n";
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
    std::cout<<"The item has been found.\n";
    return true;
  }
  else{
    if(temp.isLeaf()){
      std::cout<<"The item was not found.\n";
      return false;
    }
    else{
      if(temp.getSmallItem()!=0 && temp.getLargeItem()!=0){
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
    if(temp.isThreeNode()){
      //std::cout<<"The Current Node has 3 Children.\n";
      twothreeTree<ItemType> temptreeleft(temp.getLeftChildPtr());
      inorder(temptreeleft);
      outputNode(temp,"LEFT");
      twothreeTree<ItemType> temptreemid(temp.getMidChildPtr());
      inorder(temptreemid);
      //std::cout<<"Outputting Mid Child of 3-Node.\n";
      outputNode(temp,"RIGHT");
      twothreeTree<ItemType> temptreeright(temp.getRightChildPtr());
      inorder(temptreeright);
      //std::cout<<"Outputting Right Child of 3-Node.\n";
    }
    else{
      if(temp.isTwoNode()){
	twothreeTree<ItemType> temptreeleft(temp.getLeftChildPtr());
        inorder(temptreeleft);
	outputNode(temp,"ALL");
        twothreeTree<ItemType> temptreeright(temp.getRightChildPtr());
        inorder(temptreeright);
	//outputNode(temp);
	/*
      }
      else{
	if(temp.getLeftChildPtr()!=NULL){
	  twothreeTree<ItemType> temptreeleft(temp.getLeftChildPtr());
	  inorder(temptreeleft);
	  outputNode(temp);
	}
	if(temp.getMidChildPtr()!=NULL){
	  twothreeTree<ItemType> temptreemid(temp.getMidChildPtr());
	  inorder(temptreemid);
	  outputNode(temp);
	}
	if(temp.getRightChildPtr()!=NULL){
	  twothreeTree<ItemType> temptreeright(temp.getRightChildPtr());
	  inorder(temptreeright);
	  outputNode(temp);
	}
      }
    }
  }
}
	*/
      }
    }
  }
}
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
int main(){
  std::cout<<"--------------------------------\n";
  TriNode<int> Node_A(50);
  TriNode<int> Node_B(30);
  TriNode<int> Node_C(70);
  Node_C.setLargeItem(90);
  TriNode<int> Node_D(10);
  Node_D.setLargeItem(20);
  TriNode<int> Node_E(40);
  TriNode<int> Node_F(60);
  TriNode<int> Node_G(80);
  TriNode<int> Node_H(100);
  Node_A.setLeftChildPtr(&Node_B);
  Node_A.setRightChildPtr(&Node_C);
  Node_B.setLeftChildPtr(&Node_D);
  Node_B.setRightChildPtr(&Node_E);
  Node_C.setLeftChildPtr(&Node_F);
  Node_C.setMidChildPtr(&Node_G);
  Node_C.setRightChildPtr(&Node_H);
  twothreeTree<int> test(&Node_A);
  findItem(test,50);
  inorder(test);
  std::cout<<"--------------------------------\n";
}





 










