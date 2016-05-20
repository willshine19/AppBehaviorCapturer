/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "OnClick2ApiHooker.h"

OnClick2ApiHooker::OnClick2ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/preference/Preference",
			"onClick","()V",false,NULL,NULL,NULL));
}

OnClick2ApiHooker::~OnClick2ApiHooker() {
	// TODO Auto-generated destructor stub
}

