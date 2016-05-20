/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "OnClick4ApiHooker.h"

OnClick4ApiHooker::OnClick4ApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/app/DatePickerDialog",
			"onClick","(Landroid/content/DialogInterface;I)V",false,NULL,NULL,NULL));
}

OnClick4ApiHooker::~OnClick4ApiHooker() {
	// TODO Auto-generated destructor stub
}

