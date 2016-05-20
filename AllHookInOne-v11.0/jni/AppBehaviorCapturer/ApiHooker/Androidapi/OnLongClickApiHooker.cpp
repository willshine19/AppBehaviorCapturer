/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "OnLongClickApiHooker.h"

OnLongClickApiHooker::OnLongClickApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/widget/ZoomButton",
			"onLongClick", "(Landroid/view/View;)Z", false, NULL, NULL, NULL));
}

OnLongClickApiHooker::~OnLongClickApiHooker() {
	// TODO Auto-generated destructor stub
}

