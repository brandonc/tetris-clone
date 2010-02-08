/*
 *  game.h
 *  Tetris
 *
 *  Created by Brandon Croft on 11/15/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#ifndef __GAME_H_
#define __GAME_H_

#include "stats.h"
#include "tetromino.h"
#include "platform.h"
#include "timer.h"
#include <time.h>

class Tetromino;
class Platform;

enum TILES {
	NO_TILE = 0,
	TILE1,
	TILE2,
	TILE3,
	TILE4,
	TILE5,
	TILE6,
	TILE7
};

enum MOVE_DIRECTION {
	DIR_NONE = 0,
	DIR_LEFT = 1,
	DIR_RIGHT,
	DIR_DOWN
};

class Game {
public:
	static const int NUMBER_COLUMNS = 10;
	static const int NUMBER_ROWS = 22;
	static const int COLLAPSE_LINE_DELAY = 600;
	static const int NEW_BLOCK_DELAY = 250;
	static const int INIT_DELAY = 950;
	static const int DELAY_STEP = 60;

	Game();
	~Game();
	
	bool updateGame();
	
	bool isPaused() { return paused; }
	bool isOver() { return over; }
	bool isCollapsing(int line);

	Tetromino* getFallingBlock() { return fallingBlock; }
	Tetromino* getNextBlock() { return nextBlock; }
	Stats* getStats() { return &stats; }
	
	int field[NUMBER_COLUMNS][NUMBER_ROWS];
private:
	bool checkCollisions(int new_x, int new_y);
	void collapseLines();
	void checkLines();
	Tetromino* createTetromino();
	void moveFallingBlock(int x, int y);
	void placeFallingBlock();
	void dropBlock();
	void initGame();

	Tetromino* fallingBlock;
	Tetromino* nextBlock;
	Stats stats;
	bool paused;
	bool over;
	bool lineCollapsingFlags[NUMBER_ROWS];
	bool isCollapsingLines;
	int fallDelay;
	Timer fallTimer;
	Timer newBlockTimer;
	int events;
	Timer lineCollapseTimer;
	Platform* platform;
};

#endif