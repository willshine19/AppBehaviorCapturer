/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "showInputMethodPickerApiHooker.h"

showInputMethodPickerApiHooker::showInputMethodPickerApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/view/inputmethod/InputMethodManager",
			"showInputMethodPicker","()V",false,NULL,NULL,NULL));
}

showInputMethodPickerApiHooker::~showInputMethodPickerApiHooker() {
	// TODO Auto-generated destructor stub
}

