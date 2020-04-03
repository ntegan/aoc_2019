#include <stdio.h>
#include <stdlib.h>

int massToFuel(int mass) {
  int a =  (mass / 3) - 2;
  return  a> 0 ? a : 0;
}

void calculateTotalFuel (int* pSum, FILE* file) {
  char buf[512];
  int temp;

  // loop through file lines
  while (fgets(buf, sizeof(buf), file)) {
    // mass
    temp = atoi(buf);

    // recurse fuel amounts
    do {
      temp = massToFuel(temp);
      *pSum += temp;
    } while (temp > 0);

  }

}

int main (int argc, char **argv) {
  int sum = 0;

  // check for filename
  if (argc != 2) {
    printf("Provide input filename as arg, please\n");
    return 1;
  }

  // open file
  FILE* f = fopen(argv[1], "r");
  if (!f) { printf("Error opening file %s\n", argv[1]); return 2; }

  // calculate
  calculateTotalFuel(&sum, f);

  // print total sum
  printf("%d\n", sum);

  // close file
  fclose(f);
	
  return 0;
}
