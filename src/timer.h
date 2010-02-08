/*
 *  timer.h
 *  Tetris
 *
 *  Created by Brandon Croft on 11/8/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#include "SDL.h"

class Timer {
public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	int getTicks();
	bool isStarted() { return started; }
	bool isPaused() { return paused; }
	bool hasElapsed(int duration) { return (getTicks() > duration); }
	static int getSystemTime();
	
private:
	int startTicks;
	int pausedTicks;
	bool paused;
	bool started;
};

#endif