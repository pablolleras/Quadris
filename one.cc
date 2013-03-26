#include "one.h"

//constructor, default seed
One::One(Board *board)
{  
   //sets fields
   this->board = board;
   this->random = random; 
}
//constructor, custom seed
One::One(Board *board, PRNG *random)
{
   //sets fields
   this->board = board;  
   this->random = random; 
   (*random)();//generates random number
}
One::~One()
{
}
char One::nextBlock()
{
   //generates a new random number, from 0-11
   PRNG *r = this->board->random;
   int number = (*r)()%12;
   
   //calls for creation of blocks with different odds
   switch(number)
   {
      case 0:
        case 1: return 'I';// new Iblock(this->board);
                break;
      case 2:
        case 3: return 'J';// new Jblock(this->board);
                break;
      case 4:
        case 5: return 'L';// new Lblock(this->board);
                break;
      case 6:
        case 7: return 'O';//new Oblock(this->board);
                break;
      case 8:
        case 9: return 'T';//new Tblock(this->board);
                break;
      case 10:  return 'S';//new Sblock(this->board);
                break;
      case 11:  return 'Z';//new Zblock(this->board);
                break;
   }
}
