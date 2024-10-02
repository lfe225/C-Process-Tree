#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 

#include "process.h"

//Main Method & Command line input 
int main(int argc, char *avrp[]) {

  //Exploring directory depending on -u
  if(avrp[1] == "-u"){
    cout << "avrp" << avrp[1];
    exploreDir(avrp[2]);
  }else{
    //Saving the file information and the pid information
    exploreDir(avrp[1]);  //Parameter: userinput from the command line 
  }

  //Sorting the process information
  sortProcess(); 

 //Retreiving the first process
  const std::vector<std::string>& firstVector = info[0];
  std::string pid = firstVector[2];

 //Checking to see if there is an origin and origin with a parent id of 0
  checkOrigin(firstVector, avrp[1]);

  //Printing out the children of the first process recursivly 
  std::cout << firstVector[1] << " (" << firstVector[2] << "," << firstVector[3] << ")\n";
  children(pid, 0); //0 specifies it is a the root of the processes

  //Freeing memory 
  freeProcInfo();

  return 0;
}