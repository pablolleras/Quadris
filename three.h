#ifndef __THREE_H__
#define __THREE_H__
#include "level.h"

class Three: public Level
{
   PRNG *random;
   
  public:
   Three(Board *board);
   Three(Board *board, PRNG *random);
   ~Three();
   char nextBlock();
};


#endif
