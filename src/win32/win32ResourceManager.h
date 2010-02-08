/*
 *  win32ResourceManager.h
 *  Tetris
 *
 *  Created by Brandon Croft on 12/3/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#ifndef __WIN32RESOURCEMANAGER_H_
#define __WIN32RESOURCEMANAGER_H_

#include <windows.h>
#include <sstream>
#include "../resourceManager.h"

class Win32ResourceManager : public ResourceManager {
protected:
	void populate();
public:
	Win32ResourceManager(std::string path) : ResourceManager(path) {}
};

#endif