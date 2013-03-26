#ifndef __ONE_H__
#define __ONE_H__
#include "level.h"

class One: public Level
{
   PRNG *random;
   
  public:
   One(Board *board);
   One(Board *board, PRNG *random);
   ~One();
   char nextBlock();
};


#endif
