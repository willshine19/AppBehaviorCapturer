/*
 * CloseSocket.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "CloseSocket.h"

CloseSocket::CloseSocket() {
	this->mApiDeclaration = *(new ApiDeclaration("java/net/Socket", "close",
			"()V", false, NULL, NULL, NULL));

}

CloseSocket::~CloseSocket() {
	// TODO Auto-generated destructor stub
}

