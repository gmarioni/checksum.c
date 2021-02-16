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

#define max_int (255)
#define byte (char)

int main (int argc, char * argv[], char ** envp) {

  int count = 10;
  int sum = 0;   
/*   byte checksum; 
  byte complement; */
  int retval;
  int fd;
  fd = open(STDIN_FILENO);
  char buffer[10];
  int *p = (int) &buffer;
  retval = (int) read(fd, (void *) &buffer, count);
  printf("%d", retval);
  /* the following is the prototype for the read system call */
  /* int read(int fildes, void *buf, size_t nbyte);  */

 /*  fprintf(stdout, "Stored Checksum: %d, Computed Checksum: %d\n", checksum, complement);
  if (checksum != complement ) {
    fprintf(stderr, "Error Detected!\n"); 
    return 1;
  }
  return 0;
} */
}