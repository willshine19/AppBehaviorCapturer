/*
 * ReadFileInputStream.cpp
 *
 *  Created on: 2015-6-18
 *      Author: sang
 */

#include "ReadFileInputStream.h"

ReadFileInputStream::ReadFileInputStream() {
	this->mApiDeclaration = *(new ApiDeclaration("java/io/FileInputStream",
			"read","([BII)I",false,NULL,NULL,NULL));

}

ReadFileInputStream::~ReadFileInputStream() {
	// TODO Auto-generated destructor stub
}
