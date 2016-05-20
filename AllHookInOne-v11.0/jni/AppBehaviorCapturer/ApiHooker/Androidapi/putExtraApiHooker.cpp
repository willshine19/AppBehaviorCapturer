/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "putExtraApiHooker.h"

putExtraApiHooker::putExtraApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
			"putExtra","(Ljava/lang/String;D)Landroid/content/Intent;",false,NULL,NULL,NULL));
}

putExtraApiHooker::~putExtraApiHooker() {
	// TODO Auto-generated destructor stub
}

