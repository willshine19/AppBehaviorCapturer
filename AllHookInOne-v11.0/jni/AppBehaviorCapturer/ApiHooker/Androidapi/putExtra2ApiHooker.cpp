/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "putExtra2ApiHooker.h"

putExtra2ApiHooker::putExtra2ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
			"putExtra","(Ljava/lang/String;C)Landroid/content/Intent;",false,NULL,NULL,NULL));
}

putExtra2ApiHooker::~putExtra2ApiHooker() {
	// TODO Auto-generated destructor stub
}

