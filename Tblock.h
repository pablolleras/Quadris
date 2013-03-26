#ifndef __TBLOCK_H__
#define __TBLOCK_H__
#include "block.h"

class Tblock: public Block
{
  public:
   Tblock(Board *board);
   ~Tblock();
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
