/*
 * OpenConnectionURL.cpp
 *
 *  Created on: 2015-6-4
 *      Author: sang
 */

#include "OpenConnectionURL.h"

OpenConnectionURL::OpenConnectionURL() {
	this->mApiDeclaration = *(new ApiDeclaration("java/net/URL",
				"openConnection","()Ljava/net/URLConnection;",false,NULL,NULL,NULL));

}

OpenConnectionURL::~OpenConnectionURL() {
	// TODO Auto-generated destructor stub
}

