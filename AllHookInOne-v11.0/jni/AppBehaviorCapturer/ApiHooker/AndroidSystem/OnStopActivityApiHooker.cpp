/*
 * OnStopActivityApiHooker.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "OnStopActivityApiHooker.h"

OnStopActivityApiHooker::OnStopActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onStop","()V", false, NULL, NULL, NULL));

}

OnStopActivityApiHooker::~OnStopActivityApiHooker() {
	// TODO Auto-generated destructor stub
}

