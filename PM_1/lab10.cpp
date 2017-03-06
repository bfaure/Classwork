/*
Brian Faure
Programming Methodology Lab
Lab #10
*/

#include <fstream>
#include <stdio.h>
#include <string>
#include <map>
#include <iostream>


using namespace std;

int main(){
	
	
	ifstream ifs_definitions("definitions.txt");
	ifstream ifs_keys("dictionary_keys.txt");
	string def;
	string key;
	map<string,string> dictionary;
	while(getline(ifs_definitions,def) && getline(ifs_keys,key)){\
		dictionary[key] = def;
	}
	while(1){
		cout<<"Please enter the word you would like to search in the dictionary (enter exit to quit): ";
		cin>>key;
		if(key == "exit"){
			return 0;
		}
		if(dictionary.find(key) == dictionary.end()){
			std::cout<<"No match found in the dictionary\n";
		}
		else{
			string resp = dictionary[key];
			cout<<resp<<endl;
		}
	}
}	
		
