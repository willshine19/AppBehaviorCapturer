/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "putExtra1ApiHooker.h"

putExtra1ApiHooker::putExtra1ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
			"putExtra","(Ljava/lang/String;I)Landroid/content/Intent;",false,NULL,NULL,NULL));
}

putExtra1ApiHooker::~putExtra1ApiHooker() {
	// TODO Auto-generated destructor stub
}

