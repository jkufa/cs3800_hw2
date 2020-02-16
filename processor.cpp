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
    std::vector<Instruction> processVect; // Empty vector to act as index #
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
  unsigned int processCounter = 0; // Track of how many process are left
  unsigned int processRemainder = processesInstructions.size(); // Track how many processes are left
  unsigned int currentProcessSize;
  int processUnits = rand() % 100 + 1;
  std::vector<Computer::Process> currentProcesses; // Only 3 processes at a time
  std::vector<Computer::Process> processes; //Construct process

  std::cout << "----- " << processUnits << " Pus ------ " << std::endl;

  // Create list of processes with values
  for(unsigned int i = 0; i < processesInstructions.size(); i++) 
  {
    processes.push_back(processesInstructions[i]);
    std::cout << processes[i];  // Output all processes
  }
  std::cout << std::endl;

  /* PROCESSING */
  while(processCounter <  processesInstructions.size() && processUnits > 0) 
  {
    while(currentProcesses.size() < 3 && processRemainder != 0) 
    {
      if(processRemainder > 3) {
        for(int i = 0; i < 3; i++) 
        {
          // Only add 3 processes
          currentProcesses.push_back(processesInstructions[processCounter]);
        }
        /*Run ProcessUnit */
        for(int i = 0; i < currentProcesses.size(); i++) 
        {
          currentProcesses[i].StartProcessing();
          bool test = currentProcesses[i].ProcessUnit(processUnits);
          std::cout << "Process - " << processes[processCounter].Id() << " processing..." <<std::endl;
          processCounter++;
        }
        processRemainder--;
      }
      else 
      {
        for(unsigned int i = 0; i < processRemainder; i++) 
        {
          currentProcesses.push_back(processesInstructions[processCounter]);
        }
        /*Run ProcessUnit */
        for(int i = 0; i < currentProcesses.size(); i++) 
        {
          currentProcesses[i].StartProcessing();
          bool test = currentProcesses[i].ProcessUnit(processUnits);
          std::cout << "Process - " << processes[processCounter].Id() << " processing..." <<std::endl;
          processCounter++;
        }
        processRemainder--;
      }
      // /*Run ProcessUnit */
      // for(int i = 0; i < currentProcesses.size(); i++) {
      //   while(currentProcesses[i].ProcessUnit(processUnits)) {
      //   }
      // }

      /* Erase current processes once they're finished */
      currentProcessSize = currentProcesses.size();
      for(unsigned int i = 0; i < currentProcessSize; i++) {
      currentProcesses.erase(currentProcesses.begin());
      }
    }

    // for(unsigned int i = 0; i < currentProcessSize; i++) {
    //   std::cout << "Process - " << processes[i].Id() << " processing..." <<std::endl;
    // }
  }
}