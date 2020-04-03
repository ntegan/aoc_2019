


/*    Problem Statement 
 *        
 *        Fuel management system not completely installed
 *
 *        Two wires leave a central port and extend outward on a grid.
 *        (1 wire per line of input)
 *
 *        Wires twist and turn, occasionally crossing.
 *        FIND THE INTERSECTION CLOSEST TO CENTRAL PORT
 *        =============================================
 *
 *        Use "Manhattan Distance", i.e. Taxicab Geometry
 *        https://en.wikipedia.org/wiki/Taxicab_geometry
 *
 *        
 *
 *
 *
 *
 *
 *
 *
 */


#include "includes.h"

void checkArgs(int argc, char **argv);
int pathsFromFile(path_t** ppPaths, int* numPaths, char* fName);


int main (int argc, char **argv) {
  // variables
  path_t* pPaths = NULL;
  int numPaths = 0;

  // make sure have input file
  checkArgs(argc, argv);

  // load paths from file
  if (pathsFromFile(&pPaths, &numPaths, argv[1])) {
    printf("Error: Invalid input file\n");
    exit (2);
  }
  
  

  return 0;
}

int pathsFromFile(path_t** ppPaths, int* numPaths, char* fName) {
  FILE* f = NULL;

  // check if file exists
  f = fopen(fName, "r");
  if (!f) return 1;

  // split file into strings based on number of lines

  // set *numPaths = number of lines

  // make a path from each line/string

  fclose (f);
}

void checkArgs(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <path_input_file>\n", argv[0]);
    exit(1);
  }
}
