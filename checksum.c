/********************************/
/* Program Name: Checksum        */
/* Author:   Gerardo Marioni     */
/* Date:    2-16-2021            */
/********************************/
/* Description:  Checksum program written in C */
/* Validation Checks:   ensure that input values are within 0...(2^8)-1  */
/* Enhancements:       none     */
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
  /* The loop works, just need to now add input validation for the read
  part just before the loop*/
  read(STDIN_FILENO, &header, count);
  if(header[0]<0 || header[1]>max_int || header[1]<0 || header[1]<max_int) {
    fprintf(stdout, "Error, invalid input. Ensure that values are within range of 0..(2^8)-1 \n");

  }
  runningChecksum = (carryForward + header[0] + header[1])%(max_int+1);
  carryForward = (carryForward + header[0] + header[1])/(max_int+1);
    
  for(int c =2; c<=count-1; c++) {
      if(c==5) {
        carryForward = (runningChecksum + 0)/(max_int + 1);
        runningChecksum = (carryForward + runningChecksum + 0)%(max_int + 1);
        checksum = header[c];

      } else if (header[c] < 0 || header[c] > max_int) {
        fprintf(stdout, "Error, invalid input. Ensure that values are within range of 0..(2^8)-1 \n");
      } else {
        carryForward = (runningChecksum + header[c])/(max_int + 1);
        runningChecksum = (carryForward + runningChecksum + header[c])%(max_int + 1);

      }
    }
    complement = max_int - runningChecksum;


  fprintf(stdout, "Stored Checksum: %d, Computed Checksum: %d\n", checksum, complement);
  if (checksum != complement ) {
    fprintf(stderr, "Error Detected!\n"); 
    return 1;
  }
  
  return 0;
}
