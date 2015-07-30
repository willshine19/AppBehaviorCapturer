/*
 * OnResumeActivityApiHooker.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "OnResumeActivityApiHooker.h"

OnResumeActivityApiHooker::OnResumeActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity",
			"onResume","()V", false, NULL, NULL, NULL));

}

OnResumeActivityApiHooker::~OnResumeActivityApiHooker() {
	// TODO Auto-generated destructor stub
}

