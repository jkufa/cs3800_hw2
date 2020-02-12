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
  int index = 2;
  seed = std::stoi(lines[0]);
  processNum = std::stoi(lines[1]);
  
  for(int i = 0; i < processNum; i++) 
  {
    processes.push_back(std::stoi(lines[i+index]));
    instructionNum = std::stoi(lines[index+i]);
    for(int j = 0; j < instructionNum; j++) 
    {
      index++;
      instructionTimes.push_back(std::stoi(lines[i+index]));
    }
  }
  for(int i = 0; i < processes.size(); i++) {

    std::cout << processes[i] << std::endl;
    
  }
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


