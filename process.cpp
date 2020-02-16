/*
 * Written by: Jack Kufa
 */
#include "process.h"
#include <iostream>

unsigned long Computer::Process::processIds = 0;

Computer::Process::Process()
{
  id = Process::processIds++;
  processState = NotRunning;
  currInstruction = 0;
}

Computer::Process::Process(const std::vector<Instruction> & inst)
{
    instructions = inst;
    id = Process::processIds++;
    processState = NotRunning;
    currInstruction = 0;
}

Computer::Process::Process(const Computer::Process & copy)
{
  instructions = copy.instructions;
  id = copy.id;
  processState = copy.processState;
  currInstruction = copy.currInstruction;
}

Computer::Process & Computer::Process::operator=(const Computer::Process & copy)
{
  instructions = copy.instructions;
  id = copy.id;
  processState = copy.processState;
  currInstruction = copy.currInstruction;
  return *this;
}

// Ostream
std::ostream & Computer::operator<<(std::ostream & out, const Computer::Process & p)
{
  std::cout << "Process - " << p.id << ": " << p.NumInstructionsLeft() << " " 
    << p.RemainingInstructionTime() << "/" << p.TotalInstructionTime() << std::endl;
  return out;
}

void Computer::Process::StartProcessing()
{
  processState = Running; 
}

void Computer::Process::StopProcessing() 
{
  processState = NotRunning;
}

bool Computer::Process::ProcessUnit(unsigned long pu)
{
  unsigned long pu_remainder = pu;
  bool isFinished = Finished();
  currInstruction = 0; // Track # of instructions 
  while(pu_remainder > 0 && !isFinished) 
  {
    pu_remainder = instructions[currInstruction].Process(pu_remainder);
    currInstruction++;
    isFinished = Finished();
  }
  return (isFinished);
}

unsigned long Computer::Process::RemainingInstructionTime() const
{
  long currentInstruction = 0;
  for(long unsigned int i = 0; i < instructions.size(); i++) {
    currentInstruction += instructions[i].TimeLeft();
  }
  return currentInstruction;
}

unsigned long Computer::Process::TotalInstructionTime() const
{
  long totalInstructionTime = 0;
  for(long unsigned int i = 0; i < instructions.size(); i++) {
     totalInstructionTime += instructions[i].ProcessTime();
  }
  return totalInstructionTime;
}