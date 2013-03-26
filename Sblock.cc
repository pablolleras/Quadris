#include "Sblock.h"
//refer to Iblock for comments, all functionality is identical in terms of algorithms
Sblock::Sblock(Board *board)
{
   this->board = board;
   Sblock::pieces = new Cell*[SIZE];
   lost = false;
   position=0;
   for (int count = 0; count < SIZE; count++)
   {
      if(count < 2)
      {
         pieces[count] = this->board->theBoard[BUFFERROWS + 1][count];
      }
      else
      {
         pieces[count] = this->board->theBoard[BUFFERROWS][count - 1];
      }
      
      if(pieces[count]->occupied) lost = true;
      
   } 
   if (!lost) 
      for (int count = 0; count < SIZE; count++)
      {
         pieces[count]->occupied = true;
         pieces[count]->type = 'S';
      }
}

Sblock::~Sblock()
{
   for (int i = 0; i < SIZE; i++)
   {
      pieces[i]->occupied = false;
      pieces[i]->type = ' ';
   }
}
void Sblock::redraw()
{
   for(int count = 0; count < SIZE; count++)
   {
      pieces[count]->occupied = true;
      pieces[count]->type = 'S';
   }
}
void Sblock::erase(int row, int col)
{
   int graphicsMultiplier = 25;
   int yBuffer = 50;
   this->board->window->fillRectangle(col*graphicsMultiplier + 1 , row*graphicsMultiplier + yBuffer + 1 , graphicsMultiplier - 3 , graphicsMultiplier- 3, 1);
}
void Sblock::left()
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
void Sblock::right()
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

void Sblock::down()
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

void Sblock::drop()
{  
 
   for(int count = 0; count <= NUMROWS; count++)
   {
      this->down();
   }
   if(!lost) this->redraw();
   (*Sblock::board).endTurn();
}
void Sblock::rotateCW()
{
   bool possible = true;
   Cell *temp;
   for (int i = 0; i < SIZE; i++)
   {
      pieces[i]->occupied=false;
      pieces[i]->type = ' ';
   }
   if (position == 0)
   {
      temp = pieces[2];
      if (this->board->theBoard[temp->row][temp->col-1]->occupied)
         possible = false;
      
      temp = pieces[3];
      if (temp->row-1 < 0 || this->board->theBoard[temp->row-1][temp->col-2]->occupied)
         possible = false;
      
      if (possible)
      {
         position++;
         erase(pieces[0]->row, pieces[0]->col);
         erase(pieces[3]->row, pieces[3]->col);
         pieces[0]=pieces[1];
         pieces[1]=pieces[2];
         pieces[2]=this->board->theBoard[pieces[2]->row][pieces[2]->col-1];
         pieces[3]=this->board->theBoard[pieces[3]->row-1][pieces[3]->col-2];
      }
   }
   else if (position == 1)
   {
      temp = pieces[0];
      if (this->board->theBoard[temp->row][temp->col-1]->occupied)
         possible=false;
      
      temp = pieces[3];
      if (temp->col+2>=NUMCOLS || this->board->theBoard[temp->row+1][temp->col+2]->occupied)
         possible=false;
      
         
      if(possible)
      {
         position=0;
         erase(pieces[2]->row, pieces[2]->col);
         erase(pieces[3]->row, pieces[3]->col);
         pieces[2]=pieces[1];
         pieces[1]=pieces[0];
         pieces[0]=this->board->theBoard[pieces[0]->row][pieces[0]->col-1];
         pieces[3]=this->board->theBoard[pieces[3]->row+1][pieces[3]->col+2];
      }
         
   }
   this->redraw();

}
void Sblock::rotateCC()
{
   rotateCW();
}
