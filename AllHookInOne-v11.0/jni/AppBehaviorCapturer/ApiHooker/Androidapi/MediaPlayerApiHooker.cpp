/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "MediaPlayerApiHooker.h"

MediaPlayerApiHooker::MediaPlayerApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/media/MediaPlayer",
			"<init>","()V",false,NULL,NULL,NULL));
}

MediaPlayerApiHooker::~MediaPlayerApiHooker() {
	// TODO Auto-generated destructor stub
}

