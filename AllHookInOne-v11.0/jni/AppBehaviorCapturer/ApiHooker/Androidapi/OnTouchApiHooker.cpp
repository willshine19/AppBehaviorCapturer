/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "OnTouchApiHooker.h"

OnTouchApiHooker::OnTouchApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/support/v4/widget/AutoScrollHelper",
			"onTouch","(Landroid/view/View;Landroid/view/MotionEvent;)Z",false,NULL,NULL,NULL));
}

OnTouchApiHooker::~OnTouchApiHooker() {
	// TODO Auto-generated destructor stub
}

