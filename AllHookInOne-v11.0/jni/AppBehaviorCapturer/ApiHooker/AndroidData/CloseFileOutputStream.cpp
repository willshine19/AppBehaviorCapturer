/*
 * CloseFileOutputStream.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "CloseFileOutputStream.h"

CloseFileOutputStream::CloseFileOutputStream() {
	this->mApiDeclaration = *(new ApiDeclaration("java/io/FileOutputStream",
			"close","()V",false,NULL,NULL,NULL));

}

CloseFileOutputStream::~CloseFileOutputStream() {
	// TODO Auto-generated destructor stub
}

