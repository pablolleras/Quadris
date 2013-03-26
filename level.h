#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "PRNG.h"
#include "Iblock.h"
#include "Sblock.h"
#include "Tblock.h"
#include "Lblock.h"
#include "Jblock.h"
#include "Zblock.h"
#include "Oblock.h"
#include <string>



class Level
{
   
  public:
   Board *board;
   Level();
   ~Level();
   virtual char nextBlock();
};


#endif
