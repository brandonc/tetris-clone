/*
 *  tetromino.h
 *  Tetris
 *
 *  Created by Brandon Croft on 11/8/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#ifndef __TETROMINO_H_
#define __TETROMINO_H_

#include "game.h"

class Game;

enum TETROMINO_TYPE {
	TETRO_I = 1,
	TETRO_L,
	TETRO_T,
	TETRO_S,
	TETRO_Z,
	TETRO_O,
	TETRO_J
};

class Tetromino
{
public:
	Tetromino(int type);
	int tiles[4][4];
	bool rotate(Game const *game);
	int type() { return _type; }
	int x() { return _x; }
	int y() { return _y; }
	int size() { return _size; }
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
private:
	int _type;
	int _x;
	int _y;
	int _size;
	static void resetTiles(int* matrix);
};

#endif