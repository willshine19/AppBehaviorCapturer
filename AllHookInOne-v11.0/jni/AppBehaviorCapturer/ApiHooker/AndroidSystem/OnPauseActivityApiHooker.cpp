/*
 * OnPauseActivityApiHooker.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "OnPauseActivityApiHooker.h"

OnPauseActivityApiHooker::OnPauseActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onPause","()V", false, NULL, NULL, NULL));

}

OnPauseActivityApiHooker::~OnPauseActivityApiHooker() {
	// TODO Auto-generated destructor stub
}

