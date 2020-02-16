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
  // Track of how many processes are left. Need 2 seperate counters, one
  // for the current pushing the current processes onto the queue and 
  // the other for printing the current process number
  unsigned int processCounter[2] = {0,0}; 
  unsigned int processRemainder = processesInstructions.size(); // Track how many processes are left
  unsigned int currentProcessSize;
  int processUnits = rand() % 100 + 1;
  // Only 3 processes at a time
  std::vector<Computer::Process> currentProcesses; 
  // When processes don't get finished they go here
  std::vector<Computer::Process> priorityQueue; 
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
  while(processCounter[0] <  processesInstructions.size() && processUnits > 0) 
  {
    if(priorityQueue.size() != 0) 
    {
      int currentQueueSize = priorityQueue.size();
      for(int i = 0; i < currentQueueSize; i++) 
      {
        currentProcesses.push_back(priorityQueue.front());
        priorityQueue.erase(priorityQueue.begin());
      }
    }
    while(currentProcesses.size() < 3 && processRemainder != 0) 
    {
      // Check for process carried over from priorty queue
      int availableThreads = 3 - currentProcesses.size();
      if(processRemainder > 3) 
      {
        for(int i = 0; i < availableThreads; i++) 
        {
          // Add the next 3 current processes to queue
          currentProcesses.push_back(processesInstructions[processCounter[0]]);
          processCounter[0]++;
          processRemainder--;
        }
      }
      else
      {
        for(int i = 0; i < processRemainder; i++) 
        {
          // Add remaining processes to queue
          currentProcesses.push_back(processesInstructions[processCounter[0]]);
          processCounter[0]++;
          processRemainder--;
        }
      }
    }

    /*Run ProcessUnit */
    bool doneProcessing = false;
    for(int i = 0; i < currentProcesses.size(); i++) 
    {
        currentProcesses[i].StartProcessing();
        std::cout << "Process - " << processes[processCounter[1]].Id() << " processing..." <<std::endl;
        doneProcessing = currentProcesses[i].ProcessUnit(processUnits);
        if(!doneProcessing) 
        {
          // Keep process in queue and update remianing instructions
          priorityQueue.push_back(currentProcesses[i]);
          priorityQueue[i].StopProcessing();
        }
        currentProcesses[i].StopProcessing();
        processCounter[1]++;
    }
    // Decrement counter by the number of unfinished processes
    processCounter[1] = processCounter[1] - priorityQueue.size();
    

    /* Erase current processes once they're finished */
    currentProcesses.clear();
  }
}