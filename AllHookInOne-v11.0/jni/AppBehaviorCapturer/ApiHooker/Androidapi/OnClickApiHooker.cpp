/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "OnClickApiHooker.h"

OnClickApiHooker::OnClickApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/QuickContactBadge",
			"onClick","(Landroid/view/View;)V",false,NULL,NULL,NULL));
}

OnClickApiHooker::~OnClickApiHooker() {
	// TODO Auto-generated destructor stub
}

