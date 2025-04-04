/* 
   Hello Teamate, all I did as of 4/3/2025 @ 1:36 AM was clean up the code, rearranged some stuff, and fixed indentation.
   I plan on doing more soon, ttyl. -Gurshan

    How to run the code
    --> https://imgur.com/a/iCZkUe7 <--
   
*/




// imported from Bridges

#include "Bridges.h"
#include "ColorGrid.h"
#include "DataSource.h"
#include "data_src/ElevationData.h"
#include "/public/read.h"

// imported from C++

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

// namespaces for ease of access 

using namespace std;
using namespace bridges;

  /*
    This program implements the mountain paths assignment in C++. See the README.md for a
    detailed description this code takes in the processed elevation data and returns a color grid for
    visualization using BRIDGES 
  */

ColorGrid getImage(const ElevationData& elev_data) {
  // TODO

  /*
    access elevation with elev_data.getVal(row, col)
    compute the intensity by linear interpolation between elev_data.getMinVal(); and elev_data.getMaxVal();
    create ColorGrid with ColorGrid(nbrows, nbcols)
    fill ColorGrid with .set(row, col, color) 

    💫 return a Color Grid that represents the elevation as gray scale

  */

  ColorGrid cg (1,1); //stub
  
  return cg;

}

 
// determines the least effort path through the mountain starting a point on the left edge of the image
    
void findPath(const ElevationData&  elev_data, int startRow, ColorGrid& cg) {
    
  // TODO
    
  /*
    Run the greedy path from (0, startRow) to the right of the image
    always move right, but select the right cell, the top right cell, or bottom right cell
    by minimizing the difference of elevation.
    
    💫 Write path to the colorgrid 
    
  */
    
}   

int main(int argc, char **argv) {

	cout << endl;

    int userChoice = read("Pick either Option 1 or Option 2: ");

	cout << endl;

	if (userChoice == 1) {

      /*
        bridges object initialization
        initialize Bridges
    
        💫 How to use our function:
        bridges(saveSlot,userId,API_Key);

      */

      Bridges bridges(1, "Mcall555", "1301845300906");

      // defaults for row number and data file
      int startRow = 50;
  
      // set title
      bridges.setTitle("Avoid Hillbilly Hell");

      bridges.setDescription("Your goal is to find the path with least elevation change from one side to the other");

      // get elevation data
      DataSource ds;
      ElevationData elev_data = ds.getElevationData(6.02, 44.10, 9.70, 47.77, 0.02);

      // color grid for visualization
      ColorGrid cg = getImage(elev_data);

      // find path by applying a greedy algorithm (the function we wrote above)
      startRow = elev_data.getRows()/2;
      findPath (elev_data, startRow, cg);

      // visualize
      bridges.setDataStructure(cg);
      bridges.visualize();


	} else if (userChoice == 2){

	}


  return 0; // end of program. Yippeeee!

}


