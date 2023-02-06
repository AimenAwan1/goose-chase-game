//START: gooseEscapeGamePlay.hpp

#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActor.hpp"
#include "gooseEscapeConsole.hpp"

const int EMPTY = 0;
const int SHALL_NOT_PASS = 1;
const int WINNER = 2;
const int row = 21;
const int columns = 80;
const int JUMP_TILE = 3;
const int GOOSE_POOP = 4;
const int POWER_UP = 5;
const int CORNER = 6;
const int oneLife = 33;
const int jumpTile = 5;

//display characters
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WIN_CHAR = int('%'); 
const int JUMP_CHAR = int('*');
const int POOP_CHAR = int('#');
const int POWERUP_CHAR = int('!');

//function prototypes	
void initializeBoard(char map[row][columns]);

void printBoard(char map[row][columns]);

bool captured(Actor const & player, Actor const & monster);

void movePlayer(int key, Actor & player, char map[row][columns]);

void moveGoose(Actor & monster, Actor & player, char map[row][columns]);

bool changeHealth(Actor & player, char map[row][columns]);

void blowGoose(Actor & player, Actor & monster, char map[row][columns], 
			   int keyEntered);

void randLocation(int & playerX, int & playerY, int & gooseX, int & gooseY);

void instructions(int keyEntered, Actor & player);

#endif

//END: gooseEscapeGamePlay.hpp
