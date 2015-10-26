/*
 * OnRestartActivityApiHooker.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "OnRestartActivityApiHooker.h"

OnRestartActivityApiHooker::OnRestartActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onRestart","()V", false, NULL, NULL, NULL));

}

OnRestartActivityApiHooker::~OnRestartActivityApiHooker() {
	// TODO Auto-generated destructor stub
}

