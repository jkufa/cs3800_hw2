/*
 * Written by: Jack Kufa
 */
#include "processor.h"
#include <iostream>
#include <thread>

Computer::Processor::Processor(const std::string & filename)
{
  inputfile = filename;
  seed = 0;

}

Computer::Processor::Processor(const Computer:: Processor & copy)
{
  inputfile = copy.inputfile;
  seed = copy.seed;
}

Computer::Processor & Computer::Processor::operator=(const Computer:: Processor & copy)
{
  inputfile = copy.inputfile;
  seed = copy.seed;
  return *this;
}

Computer::Processor Start()
{
  
}


