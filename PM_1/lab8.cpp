/*
Brian Faure
Programming Meth. Lab
Lab #8
*/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using std::cout;
using std::vector;
using std::list;
using std::endl;
using std::iterator;
template <typename input>
void BinarySort(input& A){
	typedef typename input::iterator iterator;
	iterator begin = A.begin();
	iterator end = A.end();
	for(iterator pivot=begin; pivot!=end; std::advance(pivot,1)){
		iterator low=begin;
		iterator high=pivot;
       		while(low != high){
            		iterator middle = low;
            		std::advance(middle,(std::distance(low,high))/2);
            		if(*pivot>=*middle){
                		low = middle;
				std::advance(low,1);
            		}
            		else {
                		high = middle;
            		}
		}
		
		for(iterator J = pivot; J!=low; std::advance(J,-1)){
		  iterator J_ = J;
		  std::advance(J_,-1);
		  std::swap(*J,*J_);
		}
		
	}
}
int main(){
    // vector
    vector<int> v= {13, 2, 3, 7, 1, 4, 22, 5};
    //list
    list<int> l = {13, 2, 3, 7, 1, 4, 22, 5};
    //sorting vector
    BinarySort(v);
    //sorting list
    BinarySort(l);
    cout<<"----------------------------------------------"<<endl;
    cout<< "After Binary Sort..."<<endl<<"Vector:"<<endl;
    // output result
    for(auto x:v){
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<"List:"<<endl;
    for(auto x:l){
    	cout<<x<<" ";
    }
    cout<<endl;
    cout<<"----------------------------------------------"<<endl;
    return 0;
}
