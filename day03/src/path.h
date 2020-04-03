#ifndef _PATH_H_
#define _PATH_H_
#include "includes.h"

////
//  Types and Such
////

typedef struct move move_t;
typedef struct path path_t;

// an example move is "U7" or "R6" 
//      for up 7 and right 6, respectively
//      
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




////
//  Functions
////

void path_print           (path_t* pPath);
void path_from_string     (char* string);

#endif
