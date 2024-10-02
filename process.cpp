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

using namespace std; 

//Data Members
vector<int> pidInfo;
vector<vector<string>>* procInfo;
vector<vector<string>> info; 

//Exploring the directories and files 
//Saving the file information 
void exploreDir(char *dir_name){  
    //Data Members 
    DIR *dir;
    struct dirent *entry; 
    struct stat info;

    //Opening the directory
    dir = opendir(dir_name); //dir_name is the name of the path

    //Error handing: Directory not found 
    if(!dir){
        cout << "Directory was not found\n" << endl;
        exit(0); 
    }

    //Reading the files in each directory 
    while( (entry = readdir(dir))  != NULL ){
        //Checking if in current directory 
        if(entry->d_name[0] != '.'){ 
            //Creating path to files 
            string path = string(dir_name) + "/" + string(entry->d_name);            
            stat(path.c_str(),&info);

            //Recursive call for opening directories within directories 
            if(S_ISDIR(info.st_mode)){
                exploreDir((char*)path.c_str()); //Changing the path 
            }

            //Stopping at the status file 
            if(string(entry->d_name).compare("status") == 0){
                //Saving the essential data from the status file 
                vector<string> fileData = readFile(path); 
                //Saving the pid 
                int pid = std::stoi(fileData[2]);

                //Error handing: null pointer to procInfo
                if (procInfo == nullptr) {
                        procInfo = new vector<vector<string>>();
                }

                //Adding data to two vectors 
                procInfo->push_back(fileData); //Vector that contains file essential data
                pidInfo.push_back(pid); //Vector that contains only pids
            }
        }
    }
}
//Reading the status file 
std::vector<std::string> readFile(string path) {
    //Data members 
    std::vector<std::string> pInfo = std::vector<std::string>(4); //Vector for the essential process information 
    std::ifstream file; //File
    std::string line; //Line

    //Opening the file 
    file.open(path); 

    //Error checking the file 
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
    }

    while (std::getline(file, line)) { //Parsing through each line of the file 
        if (line.substr(0, 5) == "Name:") { //Saving the name information when the line starts with "Name:"
            pInfo[1] = line.substr(6);
        } else if (line.substr(0, 4) == "Pid:") {  //Saving the pid information when the line starts with "Pid:"
            pInfo[2] = line.substr(5);
        } else if (line.substr(0, 5) == "PPid:") { //Saving the ppid information when the line starts with "PPid:"
            pInfo[0] = line.substr(6);
        } else if (line.substr(0, 6) == "State:") { //Saving the state information when the line starts with "State:"
            int start = line.find_first_of('(') + 1;
            int end = line.find_first_of(')') - start;
            pInfo[3] = line.substr(start, end); //Removing the parenthesies 
        }
    }

    //Closing the file 
    file.close();

  //Returning essential file information
    return pInfo; 
}
//Sorting the process data sequentially 
void sortProcess(){
    //Sorting the vector with pid numbers 
    std::sort(pidInfo.begin(), pidInfo.end());

    //Data Members 
    std::vector<std::string> stringVector;

    //Parsing through the sorted pids
    for (const auto& pid : pidInfo) {
        //Paring through the innerVectors of the process info vector
        for (const auto& innerVector : *procInfo){
            stringVector = innerVector; //Saving the vector at each index 
            int num = std::stoi(innerVector[2]); //Saving the pid at each vector
            
            if(pid == num){ //Testing if they are equal to one another 
                //Adding data to a new vector of vector strings in sequential order 
                info.push_back(innerVector);             
            }
        }
    }
}
void checkOrigin(const std::vector<std::string>& firstVector, char* option){

    if(*option != '-u'){
        if(firstVector[2] != "1"){
        std::cerr << "An error occurred. Exiting with return code 98." << std::endl;
        std::exit(98);
    }
    if(firstVector[0] != "0"){
        std::cerr << "An error occurred. Exiting with return code 99." << std::endl;
        std::exit(99);
    }
    }
}
//Recursive method for finding the process children 
void children(string pid, int depth = 0){ //pid: the current pid, depth: how far into the directory 
    for (const auto& innerVector : info) {//Parsing through all the sorted vector of string vectors
        if(innerVector[0] == pid){ //If the parent of the vector is equal to the pid 
            for (int i = 0; i < depth + 1; ++i) { //Formatting output for depth 
                    std::cout << "----";
            }
            //Process formatting 
            std::cout << innerVector[1] << " (" << innerVector[2] << "," << innerVector[3] << ")";
            std::cout << "\n";
            //Calling the children method again for the next process 
            children(innerVector[2], depth + 1); //adding depth
        }
    }
}
//Freeing the process information
void freeProcInfo() {
    if (procInfo != nullptr) {
        for (auto& innerVector : *procInfo) {
            //Clearing each vector
            innerVector.clear();
        }
        //Clearing the whole vector
        procInfo->clear();
        delete procInfo;
        procInfo = nullptr;
    }
}