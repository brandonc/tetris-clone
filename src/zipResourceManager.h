/*
 *  zipResourceManager.h
 *  Tetris
 *
 *  Created by Brandon Croft on 12/3/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#ifndef __ZIPRESOURCEMANAGER_H_
#define __ZIPRESOURCEMANAGER_H_

#include "resourceManager.h"
#include "SDL_rwops_zzip.h"
#include "zzip/zzip.h"
#include "SDL_mixer/SDL_mixer.h"

class ZipResourceManager : public ResourceManager {
protected:
	void populate();

public:
	ZipResourceManager(std::string packfile) : ResourceManager(packfile) {}
	~ZipResourceManager();
	Mix_Music* getMusic(std::string name);
private:
	void checkZzipError(int zzipError) const;
};

#endif