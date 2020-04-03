#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// buffer of this size will hold
// hopefully input file isn't bigger than this
#define BUFFER_SIZE 16384

int countCommas(char* buf, int numBytes) {
  int i = 0;
  int count = 0;

  for (i = 0; i < numBytes; i++) {
    if (buf[i] == ',') count++;
  }

  return count;
}

void printProgram (int* opcodes, int numInts) {
  // print resulting program
  for (int i = 0; i < numInts; i++) {
    printf ("%d", opcodes[i]);
    if (i < numInts - 1) printf(",");
  }
  printf ("\n");
}

void loadOpcodes (int** pArray, int* numInts, FILE* file) {
  char *buf = (char*) malloc (BUFFER_SIZE);
  int numBytesRead = 0;
  int numCommas = 0;

  if (!buf) { printf("Couldn't alloc buf\n"); exit (2); }

  // read file into buf
  memset (buf, 0, BUFFER_SIZE);
  numBytesRead = fread (buf, sizeof (char), BUFFER_SIZE, file);
  if (numBytesRead > BUFFER_SIZE - 1) { 
    printf("Need bigger buf\n"); exit(3); 
  }

  // count commas
  numCommas = countCommas(buf, numBytesRead);
  //printf ("%d commas\n", numCommas);

  // allocate int array
  //    numCommas + 1 ints long
  *numInts = numCommas + 1;
  *pArray = (int*) malloc (*numInts * sizeof(int));
  if (!*pArray) { printf("Couldn't alloc number buf\n"); exit (4); }

  // load ints into int array
  char *pch; int i = 0;
  pch = strtok (buf, ",");
  while (pch) {
    (*pArray)[i++] = atoi(pch);
    pch = strtok(NULL, ",");
  }

  if (buf) free (buf);
}

void runProgram (int** pOpcodes, int numInts) {
  int *opcodes = *pOpcodes;
  int pc; // program counter

  for (pc = 0; pc < numInts; pc += 4) {
    // DO ADDITION
    if (opcodes[pc] == 1) {
      // add opcodes[pc + 1] and [pc + 2] 
      int sum = opcodes[opcodes[pc + 1]] 
              + opcodes[opcodes[pc + 2]];

      // store in [pc + 3]
      int resultPosition = opcodes[pc + 3];
      opcodes[resultPosition] = sum;
    }
    // DO MULTIPLICATION
    else if (opcodes[pc] == 2) {
      opcodes[opcodes[pc + 3]] =
          opcodes[opcodes[pc + 1]] *
          opcodes[opcodes[pc + 2]];
    }
    // HALT PROGRAM
    else if (opcodes[pc] == 99) {
      break;
    }
    // INVALID OPCODE
    else {
      printf("invalid opcodde\n");
    }
  }

}

int main (int argc, char **argv) {
  // array of integers
  int *opcodes = NULL;
  // number of ints separated by commas
  int numInts;

  // check for filename
  if (argc != 4) {
    printf("usage: %s <input file> <noun> <verb>\n", argv[0]);
    return 1;
  }

  // open file
  FILE* f = fopen(argv[1], "r");
  if (!f) { printf("Error opening file %s\n", argv[1]); return 2; }

  // load input into opcodes array
  loadOpcodes(&opcodes, &numInts, f);

  // before run program, restore to 1202 program alarm state
  opcodes[1] = atoi(argv[2]); opcodes[2] = atoi(argv[3]);

  // pos1 is noun, pos2 is verb
  // each between 0 and 99 (inclusive)

  // run program
  runProgram (&opcodes, numInts);

  //print result
  printf("output: %d\n", opcodes[0]);

  // print 100 * noun + verb
  printf("answer: %d\n", opcodes[1] * 100 + opcodes[2]);

  // close file
  fclose(f);

  // free array
  if (opcodes) free (opcodes);
	
  return 0;
}
