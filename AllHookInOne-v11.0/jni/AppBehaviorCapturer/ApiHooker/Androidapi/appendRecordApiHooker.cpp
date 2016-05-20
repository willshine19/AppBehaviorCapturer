/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "appendRecordApiHooker.h"

appendRecordApiHooker::appendRecordApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/accessibility/AccessibilityEvent",
			"appendRecord","(Landroid/view/accessibility/AccessibilityRecord;)V",false,NULL,NULL,NULL));
}

appendRecordApiHooker::~appendRecordApiHooker() {
	// TODO Auto-generated destructor stub
}

