/*
 * OnCreateActivityApiHooker.cpp
 *
 *  Created on: 2015-5-12
 *      Author: long
 */

#include "OnCreateActivityApiHooker.h"

OnCreateActivityApiHooker::OnCreateActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onCreate","(Landroid/os/Bundle;)V", false, NULL, NULL, NULL));
	this->mCollectedApiInfo = *(new CollectedApiInfo());
}
OnCreateActivityApiHooker::~OnCreateActivityApiHooker() {
	// TODO Auto-generated destructor stub
}


