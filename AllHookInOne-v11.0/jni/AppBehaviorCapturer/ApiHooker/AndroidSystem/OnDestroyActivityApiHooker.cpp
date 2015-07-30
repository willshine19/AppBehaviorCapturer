/*
 * OnDestroyActivityApiHooker.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "OnDestroyActivityApiHooker.h"

OnDestroyActivityApiHooker::OnDestroyActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onDestroy","()V", false, NULL, NULL, NULL));
}

OnDestroyActivityApiHooker::~OnDestroyActivityApiHooker() {
	// TODO Auto-generated destructor stub
}

