/*
 * OpenCamera.cpp
 *
 *  Created on: 2015-6-17
 *      Author: sang
 */

#include "OpenCamera.h"

OpenCamera::OpenCamera() {
	this->mApiDeclaration = *(new ApiDeclaration("android/hardware/Camera",
			"open","(I)Landroid/hardware/Camera;",true,NULL,NULL,NULL));
}

OpenCamera::~OpenCamera() {
	// TODO Auto-generated destructor stub
}

bool OpenCamera::parseResult(Object* obj) {
	const char* className = "android/hardware/Camera";
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	return true;
}
