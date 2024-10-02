#ifndef PROCESS_H
#define PROCESS_H

using namespace std; 

//Data Methods
void freeProcInfo();
void children(string pid, int depth);
void sortProcess();
void exploreDir(char *dir_name);
void checkOrigin(const std::vector<std::string>& firstVector, char* option);

//Data Members
extern std::vector<std::string> readFile(string path);
extern vector<vector<string>>* procInfo;
extern vector<vector<string>> info; 
extern vector<int> pidInfo;

#endif