#include <stdio.h>
#include <stdlib.h>

int feed_into_system(char *line);
void solve_system();
int main(int argc, char **argv)
{
  //Check how many arguments the user supplied, complain if they didn't give exactly 1 argument
  if(argc != 2)
  {
    printf("You should have given exactly 1 argument, being the filename of the logic puzzle.\n");
    exit(-1);
  }

  //If we got to here it means the user gave exactly one argument, arguments in argv start with 1 ([0] is just the name of the file being executed)
  char *filename = argv[1];

  //Open the file with read ("r") privileges
  FILE *f = fopen(filename, "r");

  //fopen returns null if the file could not be opened
  if(f == null)
  {
    //File could not be opened, do something now
    printf("File could not be opened, check that it is not used by another process or that it even exists on the system.\n");
    exit(-2);
  }

  //If we got here the file has been opened successfully and everything is cool, now read from the file line by line
  //The following loop is a specific construct of the libc and is weird

  size_t max_line_size = 300; //size_t is basically an unsigned int (a positive integer, N from 0 to whatever the range allows)
  char line[max_line_size]; //We are assuming a line is never over 300 chars (stupid assumption in all contexts but the most dumb)
  int line_no = 1; //Just to keep track of line number, gets incremented (added 1) every loop
  while (fgets(line, max_line_size, f) != NULL)  {
      int code = feed_into_system(line);

      if(code == 0)
      {
        //All good
      }
      else if(code == 1)
      {
        //Paradox encountered
        printf("Paradox encountered in line no. %d!\n", line_no);

        //Clean up resources before we go and exit
        fclose(f);
        exit(-3);
      }

      line_no++; //Increment line number counter
  }

  //Once we have fed all the lines into the system we solve the system, the solve_system function will do all reporting of results
  solve_system();

  //Be a nice boy and close the file
  fclose(f);
  return 0;
}

//Possible lines
//A=1 (A is a truth teller)
//A=0 (A is a liar)
//A:B=1 (A says B is a truth teller)
//A:A=0 (Liar's paradox)
//A:A=0|B=0 (A says that A is a liar or B is a liar)
//A:A=0^B=0 (A says that one of A or B is a liar (but not both or neither))
//A:A=0&B=0 (A says that both A and B are liars)
//Max supported characters: A, B and C
//Basic idea: Assume different starting conditions until one is found which doesn't result in a contradiction

//The three characters and their liar/truthteller status
bool A = false;
bool B = false;
bool C = false;

char *lines[10];
size_t lines_no = 0;

int feed_into_system(char *line)
{
  lines[lines_no] = line;
  lines_no++;
}
void solve_system()
{
  //We have lines at our disposal
  //Algorithmic idea: Try all possible values of A, B and C and see everytime if the system results in a contradiction (if the value of A, B or C changes during execution of the lines)
  //THIS IS WHERE THE STUFF HAPPENS!
}
