/*
 * DeleteContentResolver.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "DeleteContentResolver.h"

DeleteContentResolver::DeleteContentResolver() {
	this->mApiDeclaration = *(new ApiDeclaration("android/content/ContentResolver",
			"delete","(Landroid/net/Uri;Ljava/lang/String;[Ljava/lang/String;)I",false,NULL,NULL,NULL));

}

DeleteContentResolver::~DeleteContentResolver() {
	// TODO Auto-generated destructor stub
}

bool DeleteContentResolver::parseResult(Object* obj) {
//	const char* className = "java/io/FileDescriptor";
	char* resultString;
	sprintf(resultString, "%d", (int*)obj);
	// parseObjectToString(obj, className);
//	LOGD("[返回值解析] -> %s", resultString);
	LOGD("[返回值解析] -> %d", (int*)obj);
	return true;
}
