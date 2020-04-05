


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
  
  
  // do stuff with paths

  // free paths

  return 0;
}

int pathsFromFile(path_t** ppPaths, int* numPaths, char* fName) {
  FILE* f = NULL;

  // check if file exists
  f = fopen(fName, "r");
  if (!f) return 1;

  // READ FILE INTO LINES
  // 		Assume 2 lines
  int numLines = 2; int bufSize = 16384;	// HOPEFULLY LINES < 16384 chars
  // just set numPaths = numLines = assumed 2
  *numPaths = numLines;
  char **pStrings = (char**) malloc (numLines * sizeof (char*));
  // might as well init ppPathsa while we at it
  *ppPaths = (path_t*) malloc (numLines * sizeof (path_t));
  //{
	  int i;
	  for (i = 0; i < numLines; i++) {
		  // Read lines into string
		  pStrings[i] = (char*) malloc (bufSize * sizeof (char));
		  memset (pStrings[i], 0, bufSize * sizeof (char));
		  if (!fgets (pStrings[i], bufSize, f)) {
			printf(" UH OH! EOF?\n"); exit (4);
		  }

		  // read  strings into paths
		  path_from_string (&(*ppPaths)[i], pStrings[i]);
	  }
  //}

  // free strings in pStrings
  //{
//	  int i;
	  for (i = 0; i < numLines; i++) {
		  if (pStrings[i]) free (pStrings[i]);
	  }
  //}
  if (pStrings) free (pStrings);
  fclose (f);
  // success
  return 0;
}

void checkArgs(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <path_input_file>\n", argv[0]);
    exit(1);
  }
}
