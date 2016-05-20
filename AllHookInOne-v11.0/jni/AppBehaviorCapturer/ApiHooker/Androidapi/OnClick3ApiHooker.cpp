/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "OnClick3ApiHooker.h"

OnClick3ApiHooker::OnClick3ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/Spinner",
			"onClick","(Landroid/content/DialogInterface;I)V",false,NULL,NULL,NULL));
}

OnClick3ApiHooker::~OnClick3ApiHooker() {
	// TODO Auto-generated destructor stub
}

