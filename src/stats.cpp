/*
 *  stats.cpp
 *  Tetris
 *
 *  Created by Brandon Croft on 11/15/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include "stats.h"

Stats::Stats() : _lines(0), _score(0), _totalPieces(-1), _level(0), _highscore(DEFAULT_HIGH_SCORE)
{
	std::ifstream scores(".highscore", std::ios::in);
	if(scores.is_open()) {
		scores >> _highscore;
		scores.close();
	}
}

void Stats::reset() {
	this->_lines = 0;
	this->_score = 0;
	this->_totalPieces = -1;
	this->_level = 0;
}

void Stats::incrementTotalPieces() {
	this->_totalPieces++;
}

void Stats::addLines(int num) {
	switch(num) {
		case 1:
			_score += SCORE_1 * (_level + 1);
			break;
		case 2:
			_score += SCORE_2 * (_level + 1);
			break;
		case 3:
			_score += SCORE_3 * (_level + 1);
			break;
		case 4:
			_score += SCORE_4 * (_level + 1);
			break;
	}
	
	_lines += num;
	if(10 - num + _lines - (_level * 10) >= 10) {
		_level++;
	}

	if(_score > _highscore) {
		_highscore = _score;
	}
}

void Stats::saveHighScores() {
	if(_score == _highscore) {
		std::ofstream defaultScores(".highscore", std::ios::out | std::ios::trunc);
		if(defaultScores.is_open()) {
			defaultScores << _highscore;
		}
		defaultScores.close();
	}
}
