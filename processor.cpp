/*
 * Written by: Jack Kufa
 */
#include "processor.h"
#include <iostream>
#include <fstream>
#include <thread>

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
  // for pushing the current processes onto the queue and the other for 
  // printing the current process number
  unsigned int processCounter[2] = {0,0}; 
  unsigned int processRemainder = processesInstructions.size(); // Track how many processes are left
  int processUnits;
  bool allProcessesDone = false;
  // Only 3 processes at a time
  std::vector<int> currentProcesses;
  // When processes don't get finished their index goes here
  std::vector<int> priorityQueue;
  //Construct process
  std::vector<Computer::Process> processes; 
  std::vector<std::thread> threads;

  for(int i = 0; i < processesInstructions.size(); i++) 
  {
    // Create list of processes
    processes.push_back(processesInstructions[i]);
  }
  while(!allProcessesDone) 
  {
    // Seed PUs
    processUnits = rand() % 100 + 1;
    std::cout << "----- " << processUnits << " Pus ------ " << std::endl;

    // Create list of processes with values
    for(unsigned int i = 0; i < processesInstructions.size(); i++) 
    {
      std::cout << processes[i];  // Output all processes
    }
    std::cout << std::endl;

    /* PROCESSING */
    // Grab current proccesses for processing
    while(processUnits > 0) 
    {
      // Make sure there aren't any processes waiting in the queue
      if(priorityQueue.size() != 0) 
      {
        int currentQueueSize = priorityQueue.size();
        for(int i = 0; i < currentQueueSize; i++) 
        {
          currentProcesses.push_back(priorityQueue.front());
          priorityQueue.erase(priorityQueue.begin());
        }
      }
      // Get 3 processes running
      while(currentProcesses.size() < 3 && processRemainder != 0) 
      {
        // Check for process carried over from priorty queue
        int availableThreads = 3 - currentProcesses.size();
        if(processRemainder > 3) 
        {
          for(int i = 0; i < availableThreads; i++) 
          {
            // Add the next 3 current processes to queue
            currentProcesses.push_back(processCounter[0]); // get index of current processes

            processCounter[0]++;
            processRemainder--;
          }
        }
        // If there are less than 3 processes left, go here
        else
        {
          for(unsigned int i = 0; i < processRemainder; i++) 
          {
            // Add remaining processes to queue
            currentProcesses.push_back(processCounter[0]); // get index of current processes

            processCounter[0]++;
            processRemainder--;
          }
        }
      }

      /*Run ProcessUnit */
      bool doneProcessing = false;
      for(unsigned int i = 0; i < currentProcesses.size(); i++) 
      {
        processes[currentProcesses[i]].StartProcessing();
        std::cout << "Process - " << processes[currentProcesses[i]].Id() << " processing..." <<std::endl;
        // doneProcessing = processes[currentProcesses[i]].ProcessUnit(processUnits);
        threads.push_back(std::thread (&Process::ProcessUnit, std::ref(currentProcesses[i]), std::ref(processUnits)));
        if(!doneProcessing) 
        {
          // Keep process in queue and update remianing instructions
          priorityQueue.push_back(currentProcesses[i]);
          processes[currentProcesses[i]].StopProcessing();
        }
        processes[currentProcesses[i]].StopProcessing();

        processCounter[1]++;
      }
      // Decrement counter by the number of unfinished processes
      // ERROR: counter doesnt account for unsequential indexes
      processCounter[1] = processCounter[1] - priorityQueue.size(); 
      // Clear current processes & threads once they're finished
      currentProcesses.clear();
      threads.clear();
      // Reset PUs
      processUnits = 0;
      // Join threads
      for (int j=0; j < currentProcesses.size(); j++)
        {
            threads[j].join();            
        }
      // Check to see if all processes have been completed
      if(processCounter[1] == processesInstructions.size()) 
      {
        allProcessesDone = true;
      }
    }
  }
}