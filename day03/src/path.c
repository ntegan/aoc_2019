#include "includes.h"


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
	
/*
Example map
 asciiflow.com

                                 Array dimmensions
e.g. mmu=7         Height: 13          13     (0->12)
     mmd=-5                            x
     mml=-4        Width:  11          11     (0->10)
     mmr=6
   +
   |
12 |               Origin 'o' at
11 |               4 horizontal, 5 vertical
10 |
 9 |
 8 |
 7 |
 6 |
 5 |    o
 4 |
 3 |
 2 |
 1 |
 0 |
   +------------+

    01234567891
              0
*/

	// width and height
	int w = mmr - mml + 1, h = mmu-mmd + 1;
	int **map;

	// Allocate array for map
	map = (int**) malloc (sizeof(int*) * w);
	for (i = 0; i < w; i++) { map[i] = (int*) malloc (sizeof(int) * h); 
				  memset (map[i], 0, h * sizeof(int)); }

	// add paths to map
	int PATH_ONE_MARKER    = (1 << 0),
	    PATH_TWO_MARKER    = (1 << 1),
	    PATH_ORIGIN_MARKER = (1 << 2);

	// starting position (i.e. origin)
	// 	Also going to use this as the current position as walk through path
	int sx = ABS(mml), sy = ABS(mmd);

	// starting marker
	map[sx][sy] |= PATH_ORIGIN_MARKER;

	path_t* curPath; int j, k;
	int curMarker;

	for (j = 0; j < 2; j++) {
		// reset starting position
		sx = ABS(mml); sy = ABS(mmd);

		// pick path to add to map
		// 	add it to origin
		if (j == 0) { curMarker = PATH_ONE_MARKER; curPath = p1; map[sx][sy] |= PATH_ONE_MARKER; } 
		else        { curMarker = PATH_TWO_MARKER; curPath = p2; map[sx][sy] |= PATH_TWO_MARKER; }

		// walk through path's moves
		for (i = 0; i < curPath->numMoves; i++) {
			// 
			switch (curPath->pMoves[i].direction) {
				case 'U':
					for (k = 0; k < curPath->pMoves[i].count; k++) {
						if (sy >= (h - 1)) printf ("UHOH Y HIGH\n");
						sy ++; map[sx][sy] |= curMarker;
					}
				break;
				case 'D':
					for (k = 0; k < curPath->pMoves[i].count; k++) {
						if (sy <= 0) printf ("UHOH y low\n");
						sy --; map[sx][sy] |= curMarker;
					}
				break;
				case 'L':
					for (k = 0; k < curPath->pMoves[i].count; k++) {
						if (sx <= 0) printf ("UHOH x low\n");
						sx --; map[sx][sy] |= curMarker;
					}
				break;
				case 'R':
					for (k = 0; k < curPath->pMoves[i].count; k++) {
						if (sx >= (w - 1)) { printf ("UHOH X HIGH\n"); printf ("%d\n", sx); }
						sx ++; map[sx][sy] |= curMarker;
					}
				break;
				default:
					printf("UH OH\n");
				break;

			}
		}

	}

	// closest x, closest y, closest distance, temporary distance
	int cx = w, cy = h, cd = w + h, tDist;

	// reset starting position
	// 	To act as origin
	sx = ABS(mml); sy = ABS(mmd);

	// find intersection closest
	int test = PATH_ONE_MARKER | PATH_TWO_MARKER;

	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			// if current spot on grid is an intersection
			if ((map[i][j] == test)) {
				printf ("Intersect: (%d,%d)\n", i + mml, j + mmd); 
				tDist = ABS(i - sx) + ABS(j - sy);
				
				// if closer
				if (tDist < cd) { cd = tDist; cx = i; cy = j; }	
			}
		}

	}

	printf ("Closest distance: %d at (%d,%d) from 0,0\n", cd, cx, cy);
	

	// free map
	if (map) { for (i = 0; i < w; i++) 
		   if (map[i]) free (map[i]); free (map); }

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

