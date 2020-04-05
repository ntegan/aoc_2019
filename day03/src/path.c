#include "includes.h"


// Global variables are gud
//
void path_intersect_closest_origin (path_t* p1, path_t* p2) {

	// bounds
	//u, down, left, right (max from origin)
	int b1[4], b2[4];
	path_get_bounds(p1, b1);
	path_get_bounds(p2, b2);


	printf ("Got paths: %d %d\n", p1->numMoves, p2->numMoves);

	// Find max mu,mdm,ml,mr
	int mmu, mmd, mml, mmr;		int i;
	i = 0;
	mmu = (b1[i] > b2[i]) ? b1[i] : b2[i]; i++;
	mmd = (b1[i] < b2[i]) ? b1[i] : b2[i]; i++;
	mml = (b1[i] < b2[i]) ? b1[i] : b2[i]; i++;
	mmr = (b1[i] > b2[i]) ? b1[i] : b2[i];
	//printf ("%d %d %d %d", mmu, mmd, mml, mmr);

	//
	// subtract from coordinates, so goes from 0,0 bottom left to height and width
	//
	// make array of 0,1,2 intersect

}
void path_get_bounds      (path_t* pPath, int* fourInts) {
	// count max distance traveled in each of 4 directions, relative to starting point
	// 	// max up, down, left, right
	int mu = 0, md = 0, ml = 0, mr = 0;
	//	current horizontal position, current vertical position
	int hPos = 0, vPos = 0;
	int i;

	// walk through the path
	for (i = 0; i < pPath->numMoves; i++) {
		// update current vertical / horizontal position
		switch (pPath->pMoves[i].direction) {
			case 'U':
				vPos += pPath->pMoves[i].count;
			break;
			case 'D':
				vPos -= pPath->pMoves[i].count;
			break;
			case 'L':
				hPos -= pPath->pMoves[i].count;
			break;
			case 'R':
				hPos += pPath->pMoves[i].count;
			break;
			default:
			printf("HUH!!?\n");
			break;
		}

		// update maximums
		if (vPos > mu) mu = vPos;
		if (vPos < md) md = vPos;
		if (hPos > mr) mr = hPos;
		if (hPos < ml) ml = hPos;

	}
	//printf ("%d %d %d %d\n", mu, md, ml, mr);
	fourInts[0] = mu;
	fourInts[1] = md;
	fourInts[2] = ml;
	fourInts[3] = mr;
}

void path_print           (path_t* pPath) {
	printf ("Path has %d moves!\n", pPath->numMoves);
	int i;
	for (i = 0; i < pPath->numMoves; i++) {
		printf ("%c%03d\t", pPath->pMoves[i].direction, pPath->pMoves[i].count);
		if (i % 10 == 0) printf ("\n");
	}
	printf ("\n\n");


}
void path_free_moves      (path_t* pPath) {
	if (pPath->pMoves) free (pPath->pMoves);
}
void move_from_string     (move_t *pMove, char* string) {
	char *alias = string;
	pMove->direction = alias[0];
	alias = alias + 1;
	pMove->count = atoi(alias);
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
		// add a new move to the path
		pPath->numMoves++;
		pPath->pMoves = (move_t*) realloc (pPath->pMoves, pPath->numMoves * sizeof (move_t));
		move_from_string (&(pPath->pMoves[pPath->numMoves - 1]), token);

		// get next token
		token = strtok(NULL, delim);

	}


}
