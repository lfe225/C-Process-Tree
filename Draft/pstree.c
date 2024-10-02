#include <stdio.h>
#include <unistd.h>     /* for chdir */
#include <dirent.h>     /* for opendir, readdir, and closedir */
#include <string.h>     /* for strcmp */
#include <stdlib.h>     /* for exit */

/* prototypes and dirent structure; references to help in code development 
  int chdir(const char *path);
  DIR *opendir(const char *name);
  struct dirent *readdir(DIR *dirp);
  int closedir(DIR *dirp);
  int strcmp(const char *s1, const char *s2);
  struct dirent {
    ino_t          d_ino;       // Inode number 
    off_t          d_off;       // Not an offset; see below 
    unsigned short d_reclen;    // Length of this record/
    unsigned char  d_type;      // Type of file; not supported by all filesystem types 
    char           d_name[256]; // Null-terminated filename 
  };
*/

//Declaring Protocols
int readdirectory(DIR *directory);
int printResults(int results);
int isInteger(const char *str);

//Main Method & User Input
int main(int argc, char *avrp[]) {

  printf("is this printing anything\n");
  //Data Members
  DIR *directory; 

  //Open
  directory = opendir(avrp[1]); 

  //change 
  chdir(avrp[1]);
  
  //Results
  readdirectory(directory); 
 
  //Closing Directory
  closedir(directory); 

  return 0;
}


int readdirectory(DIR *directory){
  //Data Members
  struct dirent *entry;
  int count = 0;  

  //Success
  while((entry = readdir(directory)) != NULL){

    //if entry->name is a nbumber 
    //if isProcess(entry->d_name);
    if (isInteger(entry->d_name)) {


      printf("\n\nPROCESS: %s\n", entry->d_name);

      char expectedString[256];  // Adjust the size according to your needs
      snprintf(expectedString, sizeof(expectedString), "Pid:	%s", entry->d_name);

      char path[256];
      snprintf(path, sizeof(path), "%s/status", entry->d_name);
      FILE *statusFile = fopen(path, "r");

      char buffer[1024];  // Adjust the size according to your needs
      size_t bytesRead;

      while ((bytesRead = fread(buffer, 1, sizeof(buffer), statusFile)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
        
        
        int pidValue = -1; 
        if (sscanf(buffer, "Pid:\t%d", &pidValue) == 1) {
          // Successfully extracted Pid value
          printf("Process %s has Pid: %d\n", entry->d_name, pidValue);
          break;  // Stop reading after finding the Pid
        }
      }


      
    } else {
      printf("OTHER: %s\n", entry->d_name);
    }

    // if(entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){

    //   printf("%s directory\n", entry->d_name);

      
    //   DIR *subdirectory; 
    //   subdirectory = opendir(entry->d_name); 
    //   chdir(entry->d_name);
    //   readdirectory(subdirectory);

    //   closedir(subdirectory);
    // }
    // if(entry->d_type == DT_REG){
    //   printf("\t\t%s is a text file\n", entry->d_name);

    // }
    count++; 
  }

return count; 
}
int printResults(int results){
  printf("\nThe number of occurances is %d\n.", results); 
  return 0; 
}
int isInteger(const char *str) {
    int value;
    return (sscanf(str, "%d", &value) == 1);
}