/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "isTouchExplorationEnabledApiHooker.h"

isTouchExplorationEnabledApiHooker::isTouchExplorationEnabledApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/accessibility/AccessibilityManager",
			"isTouchExplorationEnabled","()Z",false,NULL,NULL,NULL));
}

isTouchExplorationEnabledApiHooker::~isTouchExplorationEnabledApiHooker() {
	// TODO Auto-generated destructor stub
}

