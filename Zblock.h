#ifndef __ZBLOCK_H__
#define __ZBLOCK_H__
#include "block.h"

class Zblock: public Block
{
  public:
   Zblock(Board *board);
   ~Zblock();
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
