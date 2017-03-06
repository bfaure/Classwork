#include <iostream>
#include <string>

int main(int argc, char ** argv) {
  if (7 != argc) {
    std::cout<<"You must include exactly six numerical inputs\n";
    return 0;
  }
  int columns = std::stoi(std::string(argv[1]));
  int rows = std::stoi(std::string(argv[2]));
  int col_off = std::stoi(std::string(argv[3]));
  int row_off = std::stoi(std::string(argv[4]));
  int width = std::stoi(std::string(argv[5]));
  int height = std::stoi(std::string(argv[6]));

  //Relating all of the inputs to variables
 

  if(columns > width){
     columns = width;
      }
   
  if(rows > height) {
     rows = height;
  }
    


  //Row Offset...

  for(int a=1; a<=row_off; a++) {
    std::cout<<'\n';
  }

  for(int row_count=1; row_count<=rows; row_count++) {

    //Column Offset Each time through Column Operator

    for(int b=1; b<=col_off; b++) {
      std::cout<<' ';
    }

    if (row_count==1) {
      std::cout<<'X';
      for(int c=3; c<=columns; c++) {
	std::cout<<'-';
      }
      if(width>columns) {
	std::cout<<"\n";
      }
      else {
      std::cout<<"X\n";
      }
    }
    else if (row_count==height) {
      std::cout<<'X';
      for(int d=3; d<=columns; d++) {
	std::cout<<'-';
      }
      if(width>columns) {
	std::cout<<"\n";
      }
      else {
      std::cout<<"X\n";
      }
    }
    //Last two were for top and bottom rows

    else {std::cout<<'-';
      for(int e=3;e<=columns; e++) {
	std::cout<<' ';
      }
      if(width>columns) {
	std::cout<<"\n";
      }
      else{
      std::cout<<"-\n";
      }
     
    }
  }
return 0;
}


    
