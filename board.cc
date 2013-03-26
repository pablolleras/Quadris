#include "board.h"
#include "zero.h"
#include "one.h"
#include "two.h"
#include "three.h"

Board::Board()
{}
//constructor, default seed
Board::Board(Xwindow *window)
{   
   theBoard = new Cell **[NUMROWS];//creates the board
   //initializes basic values
   Board::hiScore = 0;
   Board::currentScore = 0;
   Board::currentLevel = 1;
   this->window = window;
   this->random = new PRNG();
   //iterates through board to set each one to point to a cell
   //basic 2d array instantiation
   for (int row = 0; row < NUMROWS; row++)
   {
      theBoard[row] = new Cell*[NUMCOLS];
      for (int col = 0; col < NUMCOLS; col++)
      {      
         Cell *temp = new Cell (row, col);
         theBoard[row][col] = temp;
      }
   }
   //gives board default level 1
   Board::level = new One(this);
   char blockType = (*level).nextBlock();//finds next block for preview
   //creates the next block according to above function call
   if (blockType == 'I') Board::current = new Iblock(this);
   else if (blockType == 'J') Board::current = new Jblock(this);
   else if (blockType == 'L') Board::current = new Lblock(this);
   else if (blockType == 'T') Board::current = new Tblock(this);
   else if (blockType == 'O') Board::current = new Oblock(this);
   else if (blockType == 'S') Board::current = new Sblock(this);
   else if (blockType == 'Z') Board::current = new Zblock(this);     
   Board::next = (*level).nextBlock();//finds next block for preview
}
//constructor, user defined seed
Board::Board(Xwindow *window, int seed)
{   
   theBoard = new Cell **[NUMROWS];
   Board::hiScore = 0;
   Board::currentScore = 0;
   Board::currentLevel = 1;
   this->window = window;
   this->random = new PRNG(seed);//feeds PRNG a new starting seed
   
   for (int row = 0; row < NUMROWS; row++)
   {
      theBoard[row] = new Cell*[NUMCOLS];
      for (int col = 0; col < NUMCOLS; col++)
      {      
         Cell *temp = new Cell (row, col);
         theBoard[row][col] = temp;
      }
   }

   Board::level = new One(this, random);//feeds seed to level
   char blockType = (*level).nextBlock();
   
   if (blockType == 'I') Board::current = new Iblock(this);
   else if (blockType == 'J') Board::current = new Jblock(this);
   else if (blockType == 'L') Board::current = new Lblock(this);
   else if (blockType == 'T') Board::current = new Tblock(this);
   else if (blockType == 'O') Board::current = new Oblock(this);
   else if (blockType == 'S') Board::current = new Sblock(this);
   else if (blockType == 'Z') Board::current = new Zblock(this);     
   Board::next = (*level).nextBlock();
}

Board::~Board()
{
   
}
//assigns a color to each block type
int Board::blockColor(char blockType)
{   
   if (blockType == 'I') return 2; 
   else if (blockType == 'J') return 3;
   else if (blockType == 'L') return 4;
   else if (blockType == 'T') return 5;
   else if (blockType == 'O') return 6;
   else if (blockType == 'S') return 7;
   else if (blockType == 'Z') return 8;
   else return 1;
}
//erases currently selected block in the grid
void Board::erase(int row, int col)
{
   int graphicsMultiplier = 25;
   int yBuffer = 50;
   //constants are for aesthetics
   this->window->fillRectangle(col*graphicsMultiplier + 1 , row*graphicsMultiplier + yBuffer + 1 , graphicsMultiplier - 3 , graphicsMultiplier- 3, 1);
}
//redraws blocks in board, called when line is cleared
void Board::redrawBoard(int row, int col, char blockType)
{
   int graphicsMultiplier = 25;
   int yBuffer = 50;
   int color = this->blockColor(blockType);//gets color for block type
   //constants are for aesthetics
   this->window->fillRectangle(col*graphicsMultiplier + 1 , row*graphicsMultiplier + yBuffer + 1 , graphicsMultiplier - 3 , graphicsMultiplier- 3, color);
}
//drops all rows above the one which has been cleared
void Board::dropRows(int rowsCleared, int emptyRow)
{ 
   //iterates bottom up starting at cleared row    
   for (int row = emptyRow - 1; row >= 0; row--)
   {
      for (int col = 0; col < NUMCOLS; col++)
      {
        //if a cell is occupied, it copies its contents into the block directly below it, and erases the current cell
        if(theBoard[row][col]->occupied)   
        {
          //copy cell
          theBoard[row+1][col]->type = theBoard[row][col]->type;
          theBoard[row+1][col]->occupied = true;
          //redraw
          this->erase(row,col);
          this->redrawBoard(row+1,col,theBoard[row][col]->type);
          //erase contents of old cell location
          theBoard[row][col]->type = ' ';
          theBoard[row][col]->occupied = false;
        }     
          
      }
   }  
}
//recalculates score, checks if any row is cleared
void Board::calculateScore()
{
   int numberFilled = 0;//tracks cells occupied in a single row
   int rowsCleared = 0;//tracks rows cleared
   //stringstreams for casting int to string
   std::stringstream score;
   std::stringstream hiScore;
   
   //iterates through entire board to see if any row is filled
   for (int row = 0; row < NUMROWS; row++)
   {
      numberFilled = 0;//resets counter
      for (int col = 0; col < NUMCOLS; col++)
      {
         //increases counter when it finds an occupied cell
         if( theBoard[row][col]->occupied )
            numberFilled++;
      }
      //if an entire row is occupied, it clears the row and adjusts board accordingly
      if (numberFilled == NUMCOLS)
      {  
         rowsCleared++;
         //iterates through row to erase its contents
         for (int col = 0; col < NUMCOLS; col++)
         {
              this->erase(row,col);
              theBoard[row][col]->occupied = false;
              theBoard[row][col]->type = ' ';
         }
         
         dropRows(rowsCleared, row);//drops all rows above the one(s) cleared
      }      
   }   
   //if any rows are cleared, score is recalculated
   if(rowsCleared > 0)
   {
      //scoring formula
      this->currentScore += (rowsCleared + this->currentLevel)*(rowsCleared + this->currentLevel);
      //update score and score graphics
      score << this->currentScore;
      this->window->fillRectangle(55, 20, 100, 10, 1);
      this->window->drawString(60, 30, score.str(),0);
      
      //if hiscore is surpassed, updates it as well
      if(this->currentScore >= this->hiScore)
      {
         //update score and graphics
         this->hiScore = this->currentScore;
         hiScore << this->hiScore;
         this->window->fillRectangle(60, 35, 100, 10, 1);
         this->window->drawString(80, 45, hiScore.str(),0);
      }
   }
}

//resets the board to a new game
void Board::reset()
{
   delete this->level;//clears memory of current level object
   
   //resets current score, corresponding graphics
   Board::currentScore = 0;
   this->window->fillRectangle(55, 20, 100, 10, 1);
   this->window->drawString(60, 30, "0",0);
   
   //iterates through board to erase the contents of all cells
   for (int row = 0; row < NUMROWS; row++)
   {
      for (int col = 0; col < NUMCOLS; col++)
      {   
         //erases graphics and content
         this->erase(row,col);           
         theBoard[row][col]->occupied = false;
         theBoard[row][col]->type = ' ';
         
      }
   }
   //creates a new level object depending on what level was previously being played
   if (currentLevel == 0) Board::level = new Zero(this);
   else if (currentLevel == 1) Board::level = new One(this);
   else if (currentLevel == 2) Board::level = new Two(this);
   else if (currentLevel == 3) Board::level = new Three(this);   
   
   //creates the current block
   char blockType = (*level).nextBlock();
   
   if (blockType == 'I') Board::current = new Iblock(this);
   else if (blockType == 'J') Board::current = new Jblock(this);
   else if (blockType == 'L') Board::current = new Lblock(this);
   else if (blockType == 'T') Board::current = new Tblock(this);
   else if (blockType == 'O') Board::current = new Oblock(this);
   else if (blockType == 'S') Board::current = new Sblock(this);
   else if (blockType == 'Z') Board::current = new Zblock(this);
   //creates the next block
   Board::next = (*level).nextBlock();
   Board::currentScore = 0;
   std::cout<<"Game Over"<<std::endl;
}

//levels the game up
void Board::levelUp()
{
   //maximum level
   if (this->currentLevel == 3) return;
   //clears old level object
   delete this->level;
   //increases level, redraws indicator
   this->currentLevel++;
   std::stringstream level;
   level << this->currentLevel;
   this->window->fillRectangle(55, 5, 100, 10, 1);
   this->window->drawString(60, 15, level.str(),0);
   //creates a new level object
   switch (currentLevel)
   {
      case 1: Board::level = new One(this);
              break;
      case 2: Board::level = new Two(this);
              break;
      case 3: Board::level = new Three(this);
              break;
   }
   
}
//levels the game up
void Board::levelDown()
{
   //minimum level
   if (this->currentLevel == 0) return;
   //clears old level object
   delete this->level;
   //decreases level, redraws indicator
   this->currentLevel--;
   std::stringstream level;
   level << this->currentLevel;
   this->window->fillRectangle(55, 5, 100, 10, 1);
   this->window->drawString(60, 15, level.str(),0);
   //creates a new level object
   switch (currentLevel)
   {
      case 0: Board::level = new Zero(this);
              break;
      case 1: Board::level = new One(this);
              break;
      case 2: Board::level = new Two(this);
              break;
    }
}
//drops the current block
void Board::dropCurrent()
{      
   current->drop();
}
//ends a turn (one piece play), recalculates game
void Board::endTurn()
{
   int graphicsMultiplier = 25;
   int yBuffer = 50;
   //iterates through currently played block to redraw its position
   for (int count = 0; count < SIZE; count++)
   {
     int row = current->pieces[count]->row * graphicsMultiplier + yBuffer;
     int col = current->pieces[count]->col * graphicsMultiplier;
     char blockType = current->pieces[count]->type;
     int bevel = 1;          
     int color = blockColor(blockType);
     
     window->fillRectangle(col + bevel , row + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);     
   }
   //calculates score change, if any
   this->calculateScore();
   //sets new values for next block
   char blockType = this->next;
   next = this->level->nextBlock();
   //creates the next block to be played
   if (blockType == 'I') Board::current = new Iblock(this);
   else if (blockType == 'J') Board::current = new Jblock(this);
   else if (blockType == 'L') Board::current = new Lblock(this);
   else if (blockType == 'T') Board::current = new Tblock(this);
   else if (blockType == 'O') Board::current = new Oblock(this);
   else if (blockType == 'S') Board::current = new Sblock(this);
   else if (blockType == 'Z') Board::current = new Zblock(this);
   //if piece can't be placed on board, game is lost and reset
   if(current->lost) reset();
}
//overloaded ostream operator to draw board
std::ostream& operator<<(std::ostream &out, const Board &b)
{
   //basic board output
   out << "Level: " << b.currentLevel << std::endl;
   out << "Score: " << b.currentScore << std::endl;
   out << "Hi Score: " << b.hiScore << std::endl;
   for (int i = 0; i < NUMCOLS; i++) out << "-";
      out << std::endl;
   //iterates through board and outputs each cell's content
   for (int row = 0; row < NUMROWS; row++)
   {
      for (int col = 0; col < NUMCOLS; col++)
      {
         out << b.theBoard[row][col]->type;
      }
      out << std::endl;
   }
   for (int i = 0; i < NUMCOLS; i++) out << "-";
      out << std::endl << "Next:" << std::endl;
   //draws upcoming block
   switch (b.next)
   {
      case 'I': out << std::endl << "IIII";
         break;
      case 'J': out << "J" << std::endl << "JJJ";
         break;
      case 'L': out << " L" << std::endl << "LLL";
         break;
      case 'O': out << "OO" << std::endl << "OO";
         break;
      case 'S': out << " SS" << std::endl << "SS";
         break;
      case 'T': out << "TTT" << std::endl << " T ";
         break;
      case 'Z': out << "ZZ" <<std::endl << " ZZ";
         break;
   }

   return out;
}
