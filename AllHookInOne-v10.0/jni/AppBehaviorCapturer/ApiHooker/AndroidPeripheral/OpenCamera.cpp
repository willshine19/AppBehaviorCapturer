/*
 * OpenCamera.cpp
 *
 *  Created on: 2015-6-17
 *      Author: sang
 */

#include "OpenCamera.h"

OpenCamera::OpenCamera() {
	this->mApiDeclaration = *(new ApiDeclaration("android/hardware/Camera",
			"open","()V",true,NULL,NULL,NULL));

}

OpenCamera::~OpenCamera() {
	// TODO Auto-generated destructor stub
}

