
#include "includes.h"

void checkArgs(int argc, char **argv);
typedef struct {int low; int high;} range_t;
void range_from_file_name (range_t* r, char *name);
int count_passwords (range_t* r);

int main (int argc, char **argv) {
  range_t range; int numCombinations;

  // make sure have input file
  checkArgs(argc, argv);

  // get range from input
  range_from_file_name (&range, argv[1]);
  printf ("Got range: %d to %d\n", range.low, range.high);

  // solve
  numCombinations = count_passwords (&range);

  // print num possible passwords
  printf ("Possible passwords: %d\n", numCombinations);

  return 0;
}

int count_passwords (range_t* r) {
	// assume it's a six digit range

	int num = 0; int i; int j;
	char passBuf[128];
	int hasMatch, decreases;

	for (i = r->low; i <= r->high; i++) {
		// reset bools
		hasMatch = 0; decreases = 0;

		sprintf(passBuf, "%d", i);	
		for (j = 1; passBuf[j] != '\0'; j++) {
			// check if pass has a pair of 2 consecutive digits (same digits)
			//
			// TODO what the heck
			if (!hasMatch) {
				// test for match
				if ((passBuf[j] == passBuf[j-1]) 
						&& (passBuf[j] != passBuf[j + 1])
						&& (passBuf[j+1] != '\0')) 
					if (j > 1)
						hasMatch = (passBuf[j-2] == passBuf[j-1]) ? 0 : 1;
					else
						hasMatch = 1;
			}

			// check if decreases
			if (passBuf[j] < passBuf[j - 1]) decreases = 1;
		}
		if (hasMatch && !decreases) num++;
	}


	return num;
}

void range_from_file_name (range_t* r, char *name) {
	char buf[512]; char *token;

	// open file
	FILE* f = fopen(name, "r");
	fgets (buf, 512, f);

	// seperate into numbers, fill range struct
	token = strtok (buf, "-");
	r->low = atoi(token);
	token = strtok(NULL, "-");
	r->high = atoi(token);

	fclose (f);

}

void checkArgs(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <input_file>\n", argv[0]);
    exit(1);
  }
}
