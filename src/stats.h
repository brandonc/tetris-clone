/*
 *  stats.h
 *  Tetris
 *
 *  Created by Brandon Croft on 11/15/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>

class Stats {
public:
	void addLines(int lines);
	void incrementTotalPieces();
	void reset();
	void saveHighScores();
	Stats();
	
	int level() { return _level; }
	int lines() { return _lines; }
	int score() { return _score; }
	int totalPieces() { return _totalPieces; }
	int highscore() { return _highscore; }
	
private:
	int _level;
	int _lines;
	int _score;
	int _totalPieces;
	int _highscore;

	static const int SCORE_1 = 40;
	static const int SCORE_2 = 100;
	static const int SCORE_3 = 300;
	static const int SCORE_4 = 1200;

	static const int DEFAULT_HIGH_SCORE = 10000;
};
