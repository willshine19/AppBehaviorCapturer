/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "OnClick1ApiHooker.h"

OnClick1ApiHooker::OnClick1ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/preference/PreferenceScreen",
			"onClick","()V",false,NULL,NULL,NULL));
}

OnClick1ApiHooker::~OnClick1ApiHooker() {
	// TODO Auto-generated destructor stub
}

