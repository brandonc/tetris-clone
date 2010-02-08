/*
 *  game.cpp
 *  Tetris
 *
 *  Created by Brandon Croft on 11/15/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include "game.h"

Game::Game() {
	this->platform = new Platform(this);
	
	initGame();
}

void Game::initGame() {
	srand(Timer::getSystemTime());
	this->paused = false;
	this->over = false;
	this->isCollapsingLines = false;
	this->fallingBlock = createTetromino();
	this->nextBlock = createTetromino();
	this->fallDelay = INIT_DELAY;
	this->fallTimer.start();
	this->stats.reset();
	
	memset(lineCollapsingFlags, 0, sizeof(bool) * NUMBER_ROWS);

	for(int col = 0; col < NUMBER_COLUMNS; col++) {
		for(int row = 0; row < NUMBER_ROWS; row++) {
			this->field[col][row] = NO_TILE;
		}
	}
}

Game::~Game() {
	getStats()->saveHighScores();
	delete platform;
	if(fallingBlock) {
		delete fallingBlock;
	}
}

bool Game::updateGame() {	
	events = platform->getInput();
	
	if(events & EVENT_QUIT) {
		return true;
	}
	
	if(isOver()) {
		if(events & EVENT_RESTART) {
			if(fallingBlock) {
				delete fallingBlock;
			}
			delete nextBlock;
			platform->resumeMusic();
			initGame();
		}
		this->platform->renderGame();
		return false;
	}
	
	if(isPaused()) {
		if(events & EVENT_PAUSE) {
			paused = false;
			platform->resumeMusic();
			fallTimer.unpause();
		} else {
			this->platform->renderGame();
			return false;
		}
	} else {
		if(events & EVENT_PAUSE) {
			paused = true;
			platform->pauseMusic();
			fallTimer.pause();
			return false;
		}
	}
	
	if(newBlockTimer.isStarted() && newBlockTimer.hasElapsed(NEW_BLOCK_DELAY)) {
		newBlockTimer.stop();
		fallingBlock = nextBlock;
		nextBlock = createTetromino();
	}
	
	fallDelay = INIT_DELAY - (stats.level() * DELAY_STEP);
	if(fallDelay < 100) { fallDelay = 100; }
	
	bool movedDown = false;
	
	if(events != EVENT_NONE) {
		if(fallingBlock) {
			if(events & EVENT_ROTATE) {
				if(fallingBlock->rotate(this)) {
					platform->playSound(SOUND_CLICK);
				}
			}
			if(events & EVENT_MOVE_LEFT) {
				moveFallingBlock(-1, 0);
			}
			if(events & EVENT_MOVE_RIGHT) {
				moveFallingBlock(1, 0);
			}
			if(events & EVENT_MOVE_DOWN) {
				moveFallingBlock(0, 1);
				movedDown = true;
			}
			if(events & EVENT_DROP) {
				dropBlock();
			}
		}
		events = EVENT_NONE;
	}
	
	// Collapsing lines are held for a duration while they are animated
	if(isCollapsingLines) {
		if(lineCollapseTimer.hasElapsed(COLLAPSE_LINE_DELAY)) {
			collapseLines();
			isCollapsingLines = false;
			lineCollapseTimer.stop();
		}
	}
	
	// Hard drop test
	if(fallingBlock && !movedDown && fallTimer.hasElapsed(fallDelay)) {
		moveFallingBlock(0, 1);
		fallTimer.start();
	}
	
	platform->renderGame();
	return false;
}

void Game::moveFallingBlock(int x, int y) {
	int new_x = fallingBlock->x() + x;
	int new_y = fallingBlock->y() + y;
	
	if(!checkCollisions(new_x, new_y)) {
		fallingBlock->setX(new_x);
		fallingBlock->setY(new_y);
	} else {		
		if(y > 0) {
			placeFallingBlock();
		}
	}
}

void Game::placeFallingBlock() {
	// Block has fallen into place
	for(int col = 0; col < fallingBlock->size(); col++) {
		for(int row = 0; row < fallingBlock->size(); row++) {
			if(fallingBlock->tiles[col][row]) {
				field[fallingBlock->x() + col][fallingBlock->y() + row] = fallingBlock->type();
			}
		}
	}
	
	if(fallingBlock->y() <= 2) {
		getStats()->saveHighScores();
		over = true;
		platform->pauseMusic();
	} else {
		checkLines();
	}
	
	delete fallingBlock;
	fallingBlock = NULL;
	newBlockTimer.start();
}

void Game::dropBlock() {
	int x = fallingBlock->x();
	int y = fallingBlock->y();
	
	int dy = 0;
	while(!checkCollisions(x, y)) {
		y++;
		dy++;
	}
	
	moveFallingBlock(0, dy - 1);
	placeFallingBlock();
}

bool Game::isCollapsing(int line) {
	return lineCollapsingFlags[line];
}

void Game::collapseLines() {
	int count = 0;
	for(int row = 1; row < NUMBER_ROWS; row++) {
		if(isCollapsing(row)) {
			count++;
		}
	}
	stats.addLines(count);
	
	if(count == 4) {
		platform->playSound(SOUND_TETRIS);
	} else {
		platform->playSound(SOUND_LINE);
	}
	
	for(int row = NUMBER_ROWS - 1; row >= 1; row--) {
		if(isCollapsing(row)) {
			for(int moveRow = row - 1; moveRow >= 1; moveRow--) {
				for(int moveCol = 0; moveCol < NUMBER_COLUMNS; moveCol++) {
					field[moveCol][moveRow + 1] = field[moveCol][moveRow];
				}
			}
			checkLines();
			row++;
		}
	}
}

bool Game::checkCollisions(int new_x, int new_y) {
	for(int col = 0; col < fallingBlock->size(); col++) {
		for(int row = 0; row < fallingBlock->size(); row++) {
			if(fallingBlock->tiles[col][row]) {
				if((new_x + col < 0) || (new_x + col >= NUMBER_COLUMNS)) {
					return true;
				}
				if((new_y + row >= NUMBER_ROWS) || (field[new_x + col][new_y + row] != NO_TILE)) {
					return true;
				}
			}
		}
	}
	return false;
}

void Game::checkLines() {
	bool noline = false;
	// Scan field for lines
	for(int y = 1; y < NUMBER_ROWS; y++) {
		for(int x = 0; x < NUMBER_COLUMNS; x++) {
			if(field[x][y] == NO_TILE) {
				noline = true;
				break;
			}
		}
		if(noline) {
			lineCollapsingFlags[y] = false;
		} else {
			lineCollapseTimer.start();
			lineCollapsingFlags[y] = true;
			isCollapsingLines = true;
		}
		noline = false;
	}	
}

Tetromino* Game::createTetromino() {
	stats.incrementTotalPieces();
	return new Tetromino(rand() % 7 + 1);
}



