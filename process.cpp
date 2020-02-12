/*
 * Written by: Jack Kufa
 */
#include "process.h"
#include "instruction.h"

Computer::Process::Process()
{
  instructions; // fix
  //processIds = 0;
  id = 0;
  processState = NotRunning;
  currInstruction = 0;
}

Computer::Process::Process(const std::vector<Instruction> & inst)
{
  instructions = inst;
  //processIds = 0;
  id = 0;
  processState = NotRunning;
  currInstruction = 0;
}

Computer::Process::Process(const Computer::Process & copy)
{
  instructions = copy.instructions;
  //processIds = copy.processIds;
  id = copy.id;
  processState = copy.processState;
  currInstruction = copy.currInstruction;
}

Computer::Process & Computer::Process::operator=(const Computer::Process & copy)
{
  instructions = copy.instructions;
  //processIds = copy.processIds;
  id = copy.id;
  processState = copy.processState;
  currInstruction = copy.currInstruction;
  return *this;
}

// Ostream
std::ostream & Computer::operator<<(std::ostream & out, const Computer::Process & p)
{
  for(int i = 0; i < p.instructions.size(), i++;) 
  {
    // fix
    // out << "Process " << p.id << ": " << p.NumInstructions << " " 
    //     << p.RemainingInstructionTime << "/" + p.TotalInstructionTime ; 
  }
}

void Computer::Process::StartProcessing()
{
  
}

void Computer::Process::StopProcessing() 
{

}

bool Computer::Process::ProcessUnit(unsigned long pu)
{
  return (pu > 0) ? false : true;
}

unsigned long Computer::Process::RemainingInstructionTime() const
{
}

unsigned long Computer::Process::TotalInstructionTime() const
{

}