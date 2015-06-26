/*
 * OnStartActivityApiHooker.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "OnStartActivityApiHooker.h"

OnStartActivityApiHooker::OnStartActivityApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/app/Activity","onStart","()V",
			false,NULL,NULL,NULL));

}

OnStartActivityApiHooker::~OnStartActivityApiHooker() {
	// TODO Auto-generated destructor stub
}

