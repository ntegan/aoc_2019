#include "includes.h"


/*
struct move {             // e.g. "U7"
  char      direction;    //    "U"
  int       count;        //    "7"
};

// A path is made of multiple moves
//  e.g. "U7,R6,D4"
struct path {
  move_t*   pMoves;
  int       numMoves;
};
*/
void path_print           (path_t* pPath) {

}
void move_from_string     (move_t *pMove, char* string) {
	char *alias = string;
	pMove->direction = alias[0];
	alias = alias + 1;
	pMove->count = atoi(alias);
	printf (" %c %d", pMove->direction, pMove->count);


	printf("\n");
}
void path_from_string     (path_t* pPath, char* string) {
	// setup path
	pPath->numMoves = 0;
	pPath->pMoves = 0;

	// tokenize string by ","
	char *token = NULL;
	char *delim  = ",";
	token = strtok (string, delim);
	while (token != NULL) {
		token = strtok(NULL, delim);
		if (!token) continue;

		// add a new move to the path
		pPath->numMoves++;
		pPath->pMoves = (move_t*) realloc (pPath->pMoves, pPath->numMoves * sizeof (move_t));
		move_from_string (&(pPath->pMoves[pPath->numMoves - 1]), token);
	}


}
