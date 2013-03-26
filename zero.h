#ifndef __ZERO_H__
#define __ZERO_H__
#include "level.h"
#include <fstream>

class Zero: public Level
{
   int streamCount;   //stream to read from "sequence.txt"
  public:

   Zero(Board *board);
   ~Zero();
   char nextBlock();
};


#endif
