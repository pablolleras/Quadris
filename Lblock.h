#ifndef __LBLOCK_H__
#define __LBLOCK_H__
#include "block.h"

class Lblock: public Block
{
  public:
   Lblock(Board *board);
   ~Lblock();
   void erase(int row, int col);
   void redraw();
   void left();
   void right();
   void down();
   void drop();
   void rotateCW();
   void rotateCC();
};


#endif
