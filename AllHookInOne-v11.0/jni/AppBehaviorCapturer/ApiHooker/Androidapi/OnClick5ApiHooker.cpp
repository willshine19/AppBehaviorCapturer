/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "OnClick5ApiHooker.h"

OnClick5ApiHooker::OnClick5ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/text/method/CharacterPickerDialog",
			"onClick","(Landroid/view/View;)V",false,NULL,NULL,NULL));
}

OnClick5ApiHooker::~OnClick5ApiHooker() {
	// TODO Auto-generated destructor stub
}

