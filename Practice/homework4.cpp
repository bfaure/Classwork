/*
Brian Faure
Programming Methodology
Homework #4
Sudoku Solver
RUID: 150003563
NetID: bdf39
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <stack>

// checks if the new value 'i', placed at (x,y), will satisfy
// the rules of sudoku, if so, return true, false o.w.
bool checker(int x, int y, int i, std::vector<std::vector<int>> values){
  int size = values.size(); //creating function to check if the number matching sudoku rules
  for(int j=0; j<size; j++)
  {
    if(i == values[x][j])
    { //checking the column for identical number
      return false;
    }
    if(i ==values[j][y])
    {//checking the row for identical number
      return false;
    }
  }

  //next test is to check the box the value lies inside
  int num = sqrt(size); //solving for the dimensions of the sudoku
  int x_off = x%num;//x coordinate offset inside box
  int y_off = y%num;//y coordinate offset inside box
  int xbox = (x-x_off)/num;//did not end up using xbox & ybox
  int ybox = (y-y_off)/num;
  int xstart = x-x_off;//where to start the box to check inside (x coor)
  int ystart = y-y_off;// " " (y coor)
  for(int v = 0; v<num; v++)
  { //loops through all values in the box
    int xx = xstart+v;
    for(int z = 0; z<num; z++)
    {
      int yy = ystart+z;
      if(i == values[xx][yy])
      { //if the desired value is already in the box..
        return false;//...the function returns false and triggers a checking of the...
      } //...next number unless it was the last one in the done-for loop
    }
  }
  return true; //returns true if the input is valid and follows sudoku rules
}

bool find(int &a, int &b,std::vector<std::vector<int>> puzzle)
{ //because it calls by reference..
  bool condition = false;//...the find function can return x and y coordinates as well as bool
  int size = puzzle.size(); //loading in the size of the current sudoku
  for(int j=0; j<size; j++)
  {
    for(int k=0; k<size; k++)
    {
      if(puzzle[k][j]==0)
      { //searches entire puzzle for first zero 
        a=k;
        b=j;//loads in the values of the found zero coordinate
        return true; //returns true
      }
    }
  }
  return false;//if there are no zeros left in the 2d vector, returns false
}

bool done(std::vector<std::vector<int>> &values)
{ //function to start backtracking
  int x; //x coordinate
  int y; //y coordinate (both coordinates will be loaded into in find function)
  int size = values.size();
  if(find(x,y,values)==false){  return true;  }
  for(int p=1; p<=size; p++)
  {
    if(checker(x,y,p,values))
    { //calls the checker function to see if the input follows... 
      values[x][y]=p; //...the rules of sudoku

      if(done(values)==true){  return true;  }
      values[x][y]=0; //if the checker could not find a solution with any of the inputs...
    }//...it uses a placeholder to let the find function know its not done yet
  }
  return false; //returns false basically if sudoku is not possible to solve
}      

int main(int argc,char ** argv)
{
  if(argc<2){  return 1;  } // if wrong number of inputs

  int size = std::stoi(argv[1]); //converting size input to integer
  float root = sqrt(size); //attempting to take root of size input

  if(fmod(root,1) != 0){  return 2;  } // if input size not a square

  int num_inits = 0;//initializing the num_inits variable at zero
  if(argc > 2)
  { //checking for any initial conditions
    int count = argc-2; //subtracting the size input and terminal call input
    int check = count%3; //should be sets of three's
    if(check != 0){  return 1;  } // if inputs are illegal
    num_inits = count/3; //setting num_inits to findings to be used later
  }

  std::vector<int> temp (size,0); //temporary vector, length of sudoku dimension, zeroes
  std::vector<std::vector<int>> values(size,temp); //2d vector to hold values
  if(num_inits != 0)
  { //adding in the initial conditions if they exist
    for(int p=0; p<num_inits; p++)
    {
      int x_coor = std::stoi(argv[2+(p*3)]); //identifying from the input what...
      int y_coor = std::stoi(argv[3+(p*3)]);//the intended coordinates and values are
      int value = std::stoi(argv[4+(p*3)]);
      values[x_coor][y_coor]=value; //loading the input into the 2d vector
    }
  }   
  if(done(values)==true) //starting the done function to solve the puzzle
  { 
    std::string row_separator = "";
    for (int i=0; i<3.6*size; i++){  row_separator = row_separator+"=";  }
    row_separator = row_separator + "\n";

    for(int j=0; j<size; j++)
    { //input is the 2d vector loaded with the initial values
      if ( (int)(j) % (int)(std::sqrt(size)) == 0 ){  std::cout<<row_separator;  }
      std::cout<<"‖ ";

      for(int k=0; k<size; k++)
      { //(if there are any)
        std::string cur = std::to_string(values[k][j]);
        if ( cur.size()<3 )
        {
          int cur_size = cur.size();
          for (int i=0; i<(3-cur_size); i++ ){  cur = cur+" ";  }
        }
        if ( (int)(k+1) % (int)(std::sqrt(size)) == 0 ){  cur = cur+"‖ ";  }
        else {  cur = cur+"";  }
	       std::cout<<cur;
      }
      std::cout<<std::endl; //once the done function has finished output the result ^^
    }
    std::cout<<row_separator;
  }//did not address if done returns false because could not think of a reason to...
}//...and the assignment did not require it
	      

	      




	      




	      

	 
    
  
