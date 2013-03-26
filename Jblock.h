#ifndef __JBLOCK_H__
#define __JBLOCK_H__
#include "block.h"

class Jblock: public Block
{
  public:
   Jblock(Board *board);
   ~Jblock();
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
