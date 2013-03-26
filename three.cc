#include "three.h"

//constructor, default seed
Three::Three(Board *board)
{
   //sets fields
   this->board = board;
   this->random = random;
}
//constructor, custom seed
Three::Three(Board *board, PRNG *random)
{
   //sets fields
   this->board = board;
   this->random = random; 
   (*random)();//generates random number
}
Three::~Three()
{
}
char Three::nextBlock()
{   
   //generates a new random number, from 0-11
   PRNG *r = this->board->random;
   int number = (*r)()%9;
   //calls for creation of blocks with different odds
   switch(number)
   {
      case 0: return 'I';//new Iblock(this->board);
                break;
      case 1: return 'J';//new Jblock(this->board);
                break;
      case 2: return 'L';//new Lblock(this->board);
                break;
      case 3: return 'T';//new Tblock(this->board);
                break;                
      case 4: return 'O';//new Oblock(this->board);
                break;
      case 5: 
        case 6: return 'S';//new Sblock(this->board);
                  break;
      case 7:
        case 8: return 'Z';//new Zblock(this->board);
                  break;
   }
}
