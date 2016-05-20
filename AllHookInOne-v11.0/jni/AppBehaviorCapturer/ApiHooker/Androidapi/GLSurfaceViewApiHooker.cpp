/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "GLSurfaceViewApiHooker.h"

GLSurfaceViewApiHooker::GLSurfaceViewApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/opengl/GLSurfaceView",
			"<init>","(Landroid/content/Context;)V",false,NULL,NULL,NULL));
}

GLSurfaceViewApiHooker::~GLSurfaceViewApiHooker() {
	// TODO Auto-generated destructor stub
}

