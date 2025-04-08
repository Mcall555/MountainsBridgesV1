 /* 
   Hello Teamate, all I did as of 4/7/2025 was clean up the code, rearranged some stuff, and fixed indentation.
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
#include "Color.h"
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

ColorGrid getImage(const ElevationData& elevData) {
  // TODO

  /*
    access elevation with elev_data.getVal(row, col)
    compute the intensity by linear interpolation between elev_data.getMinVal(); and elev_data.getMaxVal();
    create ColorGrid with ColorGrid(nbrows, nbcols)
    fill ColorGrid with .set(row, col, color) 

    💫 return a Color Grid that represents the elevation as gray scale

  */
  	
    cout << "\tWidth: " << elevData.getCols() << endl;
	cout << "\tHeight: " << elevData.getRows() << endl;
	cout << "\tCell Size: " << elevData.getCellSize() << endl;
	cout << "\tLower Left Corner: " << elevData.getxll() << ", " << elevData.getyll() << endl;

	cout << "The first 10 elevation values: " << endl;
    
	for (int k = 0; k < 10; k++){
       cout << "\t" << elevData.getVal(0,k) << endl;
    }
	
	cout << endl;
	
	
  //cout << elevData.getVal(row,col) << endl;
   	
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
	 int rows = elev_data.getRows();
	 int cols = elev_data.getCols();
	 int row = startRow;

	 for (int col = 0; col < cols - 1; col++) {
		int currentElev = elev_data.getVal(row, col);
		//Possible next steps and their elevation changes
		int bestRow = row;
		int minChange = numeric_limits<int>::max();
	
		 //Check up-right (diagonal)
		if (row > 0) {
			int change = abs(currentElev - elev_data.getVal(row - 1, col + 1));
		if (change < minChange) {
			minChange = change;
			bestRow = row - 1;
			 }
		 }
		//Check right (straight)
		{
		int change = abs(currentElev - elev_data.getVal(row, col + 1));
			if (change < minChange) {
				minChange = change;
				bestRow = row;
		}
	 }
		//Check down-right (diagonal)
		 if (row < rows - 1) {
			int change = abs(currentElev - elev_data.getVal(row + 1, col + 1));
		if (change < minChange) {
			minChange = change;
			bestRow = row + 1;
			 }
		 }
		//Draw red at (col,row)
		bridges::Color red(255,0,0);
		cg.set(row,col,red);

		//Moves to next position
		row = bestRow;
}   
		//Draw red at the final column
		bridges::Color red(255,0,0);
		cg.set(row, cols - 1, red);
}

int main(int argc, char **argv) {
	  /*
	    bridges object initialization
	    initialize Bridges
	   💫 How to use our function:
	    bridges(saveSlot,userId,API_Key);
	  */

	      //Make sure all of the paramaters are strings
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
	      startRow = elev_data.getRows()/2; //The middle. (middle of the left side I think.)
	      findPath (elev_data, startRow, cg);
	
	      // visualize
	      bridges.setDataStructure(cg);
	      bridges.visualize();

  return 0; // end of program. Yippeeee!

}


