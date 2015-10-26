/*
 * CloseFileInputStream.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "CloseFileInputStream.h"

CloseFileInputStream::CloseFileInputStream() {
	this->mApiDeclaration = *(new ApiDeclaration("java/io/FileInputStream",
			"close","()V",false,NULL,NULL,NULL));

}

CloseFileInputStream::~CloseFileInputStream() {
	// TODO Auto-generated destructor stub
}

