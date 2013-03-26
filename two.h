#ifndef __TWO_H__
#define __TWO_H__
#include "level.h"

class Two: public Level
{
   PRNG *random;
   
  public:
   Two(Board *board);
   Two(Board *board, PRNG *random);
   ~Two();
   char nextBlock();
};


#endif
