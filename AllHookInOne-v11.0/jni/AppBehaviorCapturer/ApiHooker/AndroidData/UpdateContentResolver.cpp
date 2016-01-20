/*
 * UpdateContentResolver.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "UpdateContentResolver.h"

UpdateContentResolver::UpdateContentResolver() {
	this->mApiDeclaration = *(new ApiDeclaration("android/content/ContentResolver",
			"update","(Landroid/net/Uri;Landroid/content/ContentValues;Ljava/lang/String;[Ljava/lang/String;)I",false,NULL,NULL,NULL));


}

UpdateContentResolver::~UpdateContentResolver() {
	// TODO Auto-generated destructor stub
}

bool UpdateContentResolver::parseResult(Object* obj) {
	char* resultString;
//	sprintf(resultString, "%d", (int*)obj);
//	LOGD("[返回值解析] -> %s", resultString);
	LOGD("[返回值解析] -> %d", (int*)obj);
	return true;
}

