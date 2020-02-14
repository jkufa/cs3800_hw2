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
    processes.push_back(std::stoi(lines[i+index]));
    processesToInstructions.push_back(processes);
    instructionNum = std::stoi(lines[index+i]);
    for(unsigned int j = 0; j < instructionNum; j++) 
    {
      index++;
      // Create vector of instructionTimes
      processesToInstructions[i].push_back(std::stoi(lines[i+index]));
      std::cout << "at: " << processesToInstructions[i][j] << std::endl;
      std::cout << "adding: " << std::stoi(lines[i+index]) << " to vector" << std::endl;
      instructionTimes.push_back(std::stoi(lines[i+index]));
    }
  }
  for(long unsigned int i = 0; i < processes.size(); i++) 
  {
      // std::cout << "vector " << i << " has " << processesToInstructions[i].size() << " instructions" << std::endl;
      // std::cout << "vector " << i << " instructions: " << std::endl;
      // for(int j = 0; j < processesToInstructions[i].size(); j++) {
      //   std::cout << processesToInstructions[i][j] << std::endl;
      // }
    //std::cout << processes[i] << std::endl;
    
  }
  // for(int i = 0; i < instructionTimes.size(); i++) {
  //   std::cout << instructionTimes[i] <<std::endl;
  // }
}

Computer::Processor::Processor(const Computer:: Processor & copy)
{
  inputfile = copy.inputfile;
  seed = copy.seed;
  processNum = copy.processNum;
  instructionNum = copy.instructionNum;
  instructionTimes = copy.instructionTimes;
}

Computer::Processor & Computer::Processor::operator=(const Computer:: Processor & copy)
{
  inputfile = copy.inputfile;
  seed = copy.seed;
  processNum = copy.processNum;
  instructionNum = copy.instructionNum;
  instructionTimes = copy.instructionTimes;
  return *this;
}

void Computer::Processor::Start()
{
  
}