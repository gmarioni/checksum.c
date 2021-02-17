/********************************/
/* Program Name: Checksum        */
/* Author:   Gerardo Marioni     */
/* Date:    2-16-2021            */
/********************************/
/* Description:  Checksum program written in C */
/* Validation Checks:   none  */
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
  int carryForward = 0;
  int runningChecksum = 0;


  byte header[10];
  //the program reads the file allocating the buffer space
  read(STDIN_FILENO, &header, count);
  runningChecksum = (carryForward + header[0] + header[1])%(max_int+1);
  carryForward = (carryForward + header[0] + header[1])/(max_int+1);
  //this for loop calculates the running checksum calculation (one's complement) 
  for(int c =2; c<=count-1; c++) {
      if(c==5) {
        carryForward = (runningChecksum + 0)/(max_int + 1);
        runningChecksum = (carryForward + runningChecksum + 0)%(max_int + 1);
        checksum = header[c];
      } else {
        carryForward = (runningChecksum + header[c])/(max_int + 1);
        runningChecksum = (carryForward + runningChecksum + header[c])%(max_int + 1);
      }
    }
    //complement is determined from the one's complement calculation
    complement = max_int - runningChecksum;

  /* result is printed out and error message is displayed if stored and 
  calculated checksum don't match */
  fprintf(stdout, "Stored Checksum: %d, Computed Checksum: %d\n", checksum, complement);
  if (checksum != complement ) {
    fprintf(stderr, "Error Detected!\n"); 
    return 1;
  }
  
  return 0;
}
