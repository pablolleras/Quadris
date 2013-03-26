#ifndef __SBLOCK_H__
#define __SBLOCK_H__
#include "block.h"

class Sblock: public Block
{
  public:
   Sblock(Board *board);
   ~Sblock();
   void redraw();
   void erase(int row, int col);
   void left();
   void right();
   void down();
   void drop();
   void rotateCW();
   void rotateCC();
};


#endif
