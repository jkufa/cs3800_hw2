/*
 * Written by: Jack Kufa
 */
#include "processor.h"
#include <iostream>
#include <thread>
#include <fstream>

Computer::Processor::Processor(const std::string & filename)
{
  std::ifstream source;
  source.open(filename);
  std::vector<std::string> lines;
  std::string line;
  while(std::getline(source, line)) 
  {
    lines.push_back(line);
  }
  int index = 2; // skip first two lines of input
  seed = std::stoi(lines[0]);
  processNum = std::stoi(lines[1]);
  for(long unsigned int i = 0; i < processNum; i++) 
  {
    std::vector<int> processVect; // Empty vector to act as index #
    // Insert processNum size empty vector
    processesInstructions.push_back(processVect); 
    instructionNum = std::stoi(lines[index+i]);
    for(unsigned int j = 0; j < instructionNum; j++) 
    {
      index++;
      // Create vector of instructionTimes
      processesInstructions[i].push_back(std::stoi(lines[i+index]));
    }
  }
}

Computer::Processor::Processor(const Computer:: Processor & copy)
{
  inputfile = copy.inputfile;
  seed = copy.seed;
  processNum = copy.processNum;
  instructionNum = copy.instructionNum;
  processesInstructions = copy.processesInstructions;
}

Computer::Processor & Computer::Processor::operator=(const Computer:: Processor & copy)
{
  inputfile = copy.inputfile;
  seed = copy.seed;
  processNum = copy.processNum;
  instructionNum = copy.instructionNum;
  processesInstructions = copy.processesInstructions;
  return *this;
}

void Computer::Processor::Start()
{
  unsigned int processCounter = 0; // Keep track of how many process are left
  // int currentProcesses[3] = {}; // Only 3 processes at a time
  std::vector<std::vector<int>> currentProcesses; // Only 3 processes at a time
  int processUnits = rand() % 100 + 1;
  Computer::Process process; //Construct process

  std::cout << "----- " << processUnits << " Pus ------ " << std::endl;
  if(processCounter <  processesInstructions.size()) 
  {
    while(currentProcesses.size() < 3) 
    {
      for(int i = 0; i < 3; i++) 
      {
        currentProcesses.push_back(processesInstructions[processCounter]);
        processCounter++;
      }
    }
    for(int i = 0; i < 3; i++) {
      /*Process Shit*/
      process.
    }

  }
    std::cout << process;
}