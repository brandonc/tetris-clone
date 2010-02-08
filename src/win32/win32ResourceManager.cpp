/*
 *  win32ResourceManager.cpp
 *  Tetris
 *
 *  Created by Brandon Croft on 12/3/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */


#include "win32ResourceManager.h"

void Win32ResourceManager::populate() {
	WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((LPCSTR)(resourcePath + "/*").c_str(), &findFileData);
   
    if(hFind  == INVALID_HANDLE_VALUE) {
        return;
	}
   
    while(FindNextFile(hFind, &findFileData)) {
        std::string filename(findFileData.cFileName);
		if(filename == "." || filename == "..") continue;
		files.insert(std::pair<std::string, SDL_RWops*>(
			filename,
			createFileOps(resourcePath + "/" + filename)
		));
    }
 
    FindClose(hFind);
}
