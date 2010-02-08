/*
 *  tetromino.cpp
 *  Tetris
 *
 *  Created by Brandon Croft on 11/8/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include "tetromino.h"

Tetromino::Tetromino(int type) : _x(3), _y(2), _size(3), _type(type) {
	resetTiles(&this->tiles[0][0]);
	
	switch(type) {
		case TETRO_I:
			tiles[0][1] = 1;
			tiles[1][1] = 1;
			tiles[2][1] = 1;
			tiles[3][1] = 1;
			_size = 4;
			_y = 1;
			break;
		case TETRO_O:
			tiles[0][0] = 1;
			tiles[0][1] = 1;
			tiles[1][0] = 1;
			tiles[1][1] = 1;
			_size = 2;
			break;
		case TETRO_T:
			tiles[0][1] = 1;
			tiles[1][0] = 1;
			tiles[1][1] = 1;
			tiles[2][1] = 1;
			break;
		case TETRO_S:
			tiles[0][1] = 1;
			tiles[1][0] = 1;
			tiles[1][1] = 1;
			tiles[2][0] = 1;
			break;
		case TETRO_Z:
			tiles[0][0] = 1;
			tiles[1][0] = 1;
			tiles[1][1] = 1;
			tiles[2][1] = 1;
			break;
		case TETRO_L:
			tiles[0][1] = 1;
			tiles[1][1] = 1;
			tiles[2][0] = 1;
			tiles[2][1] = 1;
			break;
		case TETRO_J:
			tiles[0][0] = 1;
			tiles[0][1] = 1;
			tiles[1][1] = 1;
			tiles[2][1] = 1;
			break;
	}
}

void Tetromino::resetTiles(int* matrix) {
	for(int col = 0; col < 4; col++) {
		for(int row = 0; row < 4; row++) {
			*(matrix + col + (row * 4)) = 0;
		}
	}
}

bool Tetromino::rotate(Game const *game) {
	int copy[4][4];
	resetTiles(&copy[0][0]);
	
	for(int col = 0; col < size(); col++) {
		for(int row = 0; row < size(); row++) {
			if(x() + (size() - row - 1) < 0 || x() + (size() - row - 1) >= Game::NUMBER_COLUMNS || y() + col >= Game::NUMBER_ROWS) {
				// Rotate not allowed due to field proximity
				return false;
			}
			if(game->field[x() + (size() - row - 1)][y() + col]) {
				// Rotate not allowed due to tile proximity
				return false;
			}
			copy[size() - row - 1][col] = tiles[col][row];
		}
	}
	
	for(int col = 0; col < 4; col++) {
		for(int row = 0; row < 4; row++) {
			tiles[col][row] = copy[col][row];
		}
	}
	return true;
}