#include "Oblock.h"
//refer to Iblock for comments, all functionality is identical in terms of algorithms
Oblock::Oblock(Board *board)
{
   this->board = board;
   Oblock::pieces = new Cell*[SIZE];
   lost = false;
   for (int count = 0; count < SIZE; count++)
   {
      if(count < 2)
      {
         pieces[count] = this->board->theBoard[BUFFERROWS][count];
      }
      else
      {
         pieces[count] = this->board->theBoard[BUFFERROWS + 1][count - 2];
      }
      if (pieces[count]->occupied) lost = true;
   }
   if (!lost)
      for (int count = 0; count < SIZE; count++)
      {      
         pieces[count]->occupied = true;
         pieces[count]->type = 'O';
      } 
}
Oblock::~Oblock()
{
   for (int i = 0; i < SIZE; i++)
   {
      pieces[i]->occupied = false;
      pieces[i]->type = ' ';
   }
}
void Oblock::redraw()
{
   for(int count = 0; count < SIZE; count++)
   {
      pieces[count]->occupied = true;
      pieces[count]->type = 'O';
   }
}
void Oblock::erase(int row, int col)
{
   int graphicsMultiplier = 25;
   int yBuffer = 50;
   this->board->window->fillRectangle(col*graphicsMultiplier + 1 , row*graphicsMultiplier + yBuffer + 1 , graphicsMultiplier - 3 , graphicsMultiplier- 3, 1);
}
void Oblock::left()
{
   int row;
   int col;
   for(int count = 0; count < SIZE; count++)
   {
      pieces[count]->occupied = false;
   }
   
   for(int count = 0; count < SIZE; count++)
   {
      col = pieces[count]->col;
      if (col - 1 < 0)
      {
         for (int count = 0; count < SIZE; count++)
         {
            pieces[count]->occupied = true;
            return;
         }
      }
   }
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;
      Cell *temp = this->board->theBoard[row][col-1];
      if (temp->occupied) return;

   }

   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;      
      this->erase(row,col);
      pieces[count]->type = ' ';
      pieces[count] = this->board->theBoard[row][col - 1];      
   }  
   this->redraw();
}
void Oblock::right()
{
   int row;
   int col;
   for(int count = 0; count < SIZE; count++)
   {
      pieces[count]->occupied = false;
   }
   
   for(int count = 0; count < SIZE; count++)
   {
      col = pieces[count]->col;
      if (col + 1 >= NUMCOLS)
      {
         for (int count = 0; count < SIZE; count++)
         {
            pieces[count]->occupied = true;
            return;
         }
      }
   }
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;
      Cell *temp = this->board->theBoard[row][col+1];
      if (temp->occupied) return;

   }

   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;      
      this->erase(row,col);
      pieces[count]->type = ' ';
      pieces[count] = this->board->theBoard[row][col + 1];      
   }  
   this->redraw();
}
void Oblock::down()
{
   int row;
   int col;
   for(int count = 0; count < SIZE; count++)
   {
      pieces[count]->occupied = false;
   }
   
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      if (row + 1 >= NUMROWS)
      {
         for (int count = 0; count < SIZE; count++)
         {
            pieces[count]->occupied = true;
            return;
         }
      }
   }
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;
      Cell *temp = this->board->theBoard[row + 1][col];
      if (temp->occupied) return;

   }

   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;      
      this->erase(row,col);
      pieces[count]->type = ' ';
      pieces[count] = this->board->theBoard[row + 1][col];      
   }  
   this->redraw();
}
void Oblock::drop()
{

   for(int count = 0; count <= NUMROWS; count++)
   {
      this->down();
   }
   if (!lost) this->redraw();
   (*Oblock::board).endTurn();
}
void Oblock::rotateCW()
{
}
void Oblock::rotateCC()
{
}
