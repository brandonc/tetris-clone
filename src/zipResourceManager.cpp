/*
 *  zipResourceManager.cpp
 *  Tetris
 *
 *  Created by Brandon Croft on 12/3/08.
 *  Copyright 2008 Brandon Croft. All rights reserved.
 *
 */

#include "zipResourceManager.h"

ZipResourceManager::~ZipResourceManager() {
}

void ZipResourceManager::populate() {
	zzip_error_t zzipError;
    ZZIP_DIR* zzipDir = zzip_dir_open(resourcePath.c_str(), &zzipError);
    checkZzipError(zzipError);

    ZZIP_DIRENT zzipEntry;
    while (zzip_dir_read(zzipDir, &zzipEntry))
    {
        int compressedSize = zzipEntry.d_csize;
        int uncompressedSize = zzipEntry.st_size;

		std::string name = std::string(zzipEntry.d_name);
		files[name] = SDL_RWFromZZIP((resourcePath + "/" + name).c_str(), "rb");
    }

	zzip_dir_close(zzipDir);
}

Mix_Music* ZipResourceManager::getMusic(std::string name) {
	return Mix_LoadMUS(name.c_str());
}

void ZipResourceManager::checkZzipError(int zzipError) const
{
    if (zzipError != ZZIP_NO_ERROR)
    {
        exit(-1);
    }
}