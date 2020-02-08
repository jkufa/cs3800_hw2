/*
 * Written by: Jack Kufa
 */
#include "process.h"

Computer::Process::Process()
{
  instructions;
  processIds = 0;
  id = 0;
  processState = NotRunning;
  currInstruction = 0;
}

Computer::Process::Process(const std::vector<Instruction> & inst)
{
  instructions = inst;
  processIds = 0;
  id = 0;
  processState = NotRunning;
  currInstruction = 0;
}

Computer::Process::Process(const Computer::Process & copy)
{
  instructions = copy.instructions;
  processIds = copy.processIds;
  id = copy.id;
  processState = copy.processState;
  currInstruction = copy.currInstruction;
}

Computer::Process & Computer::Process::operator=(const Computer::Process & copy)
{
  instructions = copy.instructions;
  processIds = copy.processIds;
  id = copy.id;
  processState = copy.processState;
  currInstruction = copy.currInstruction;
  return *this
}

// Ostream
//Computer::Process & std::ostream::operator<<(std::ostream & out, const Computer::Process & p)

Computer::Process StartProcessing()
{

}

Computer::Process StopProcessing() 
{

}

Computer::Process ProcessUnit()
{

}

Computer::Process RemainingInstructionTIme() 
{

}

Computer::Process TotalInstructionTime() 
{

}

