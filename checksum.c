/********************************/
/* Program Name:                */
/* Author:                      */
/* Date:                        */
/********************************/
/* Description:                 */
/* Validation Checks:           */
/* Enhancements:                */
/********************************/

#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>

#define max_int (255)
#define byte unsigned char

int main (int argc, char * argv[], char ** envp) {

  int count = 10;
  int sum = 0;   
  byte checksum; 
  byte complement;
  int quotient;
  int remainder;
  int carryForward = 0;
  int runningChecksum = 0;


  byte header[10];
  /* Ok, so far so good, lns 36-39 are producing the right
  output given the 156.txt file; now I just need to make
  the rest of the algorithm*/
  read(STDIN_FILENO, &header, count);
  carryForward = (carryForward + header[0] + header[1])/(max_int+1);
  runningChecksum = (carryForward + header[0] + header[1])%(max_int+1);
 /*  printf("%d\n", carryForward);
  printf("%d\n", runningChecksum); */
  for(int c =2; c<=count-1; c++) {
      if(c==5) {
        runningChecksum = (carryForward + runningChecksum + 0)%(max_int + 1);
        checksum = header[5];
      } else {
        runningChecksum = (carryForward + runningChecksum + header[c])%(max_int + 1);
        carryForward = (runningChecksum + header[c])/max_int;
      }
    }
    complement = max_int - runningChecksum;
    /* printf("%d\n", complement); */

  fprintf(stdout, "Stored Checksum: %d, Computed Checksum: %d\n", checksum, complement);
  if (checksum != complement ) {
    fprintf(stderr, "Error Detected!\n"); 
    return 1;
  }
  
  return 0;
}
