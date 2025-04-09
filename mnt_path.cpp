
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
   	
	Color grey(128,128,128);
    ColorGrid cg (elevData.getRows(),elevData.getCols(), grey);

	int minVal = elevData.getMinVal();
	int maxVal = elevData.getMaxVal();

	for(int row = 0; row < elevData.getRows(); row++){
      for(int col = 0; col < elevData.getCols(); col++){
        int val = elevData.getVal(row,col);

		int newShade = 255 * (val - minVal) / (maxVal - minVal);
		Color newColor(newShade,newShade,newShade);

		cg.set(row,col,newColor);

      }
	}

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

	 bridges::Color red(255, 0, 0);

	 cg.set(row, 0, red);//draw the starting point

	 for (int col = 0; col < cols - 1; col++) {
		int currentVal = elev_data.getVal(row, col);
		int nextCol = col + 1;

		//Greedy choice
		int bestRow = row;
		int minChange = numeric_limits<int>::max();
	
		//Check up-right (diagonal)
		if (row > 0) {
			int change = abs(currentVal - elev_data.getVal(row - 1, nextCol));
		    if (change < minChange){
			  minChange = change;
			  bestRow = row - 1;
			}
		 }
		//Check right (straight)

		{
		int change = abs(currentVal - elev_data.getVal(row, nextCol));
			if (change < minChange){
			  minChange = change;
			  bestRow = row;
		   }
	     }
		//Check down-right (diagonal)
		 if (row < rows - 1) {
			int change = abs(currentVal - elev_data.getVal(row + 1, nextCol));
		     if (change < minChange){
		       minChange = change;
		       bestRow = row + 1;
			}
		 }

		//Moves to next position
		row = bestRow; 

		//Draw red at the final column
		cg.set(row, col, red); 
		
}

 }

int main(int argc, char **argv) {
	  /*
	    bridges object initialization
	    initialize Bridges
	   💫 How to use our function:
	    bridges(saveSlot,userId,API_Key);
	  */
        try {
	     	 //Make sure all of the paramaters are strings
	      	 Bridges bridges(1, "Mcall555", "1301845300906");
	
	     	 // defaults for row number and data file
	     	 //int startRow = 50;

	  		 int startRow = 50;
			 
	     	 // set title
	     	 bridges.setTitle("Least Altitude Change Path.");
	
	     	 bridges.setDescription("Your goal is to find the path with least elevation change from one side to the other");
	
	    	 // get elevation data
	     	 DataSource ds;
		
	     	 ElevationData elev_data = ds.getElevationData(40.03133177632377, -98.02593749997456, 42.508577297430456, -96.94531249997696, 0.0166);

	    	  // color grid for visualization

	         ColorGrid cg = getImage(elev_data);
	
	    	 // find path by applying a greedy algorithm (the function we wrote above)

	         startRow = elev_data.getRows() / 2; //The middle. (middle of the left side I think.)

	    	 findPath(elev_data, startRow, cg);
	
	    	 // visualize
	    	 bridges.setDataStructure(cg);
	    	 bridges.visualize();

        	 return 0;

	        } catch (const char* msg) {
			  cerr << "Exception caught: " << msg << endl;
	 		}
}	


