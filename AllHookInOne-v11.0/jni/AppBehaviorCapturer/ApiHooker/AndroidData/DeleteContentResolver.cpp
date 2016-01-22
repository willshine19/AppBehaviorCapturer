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
	char rs[20];
	int* ma ;
	int i = 0;
	ma = (int*) obj;
	i = reinterpret_cast<int>(&ma[0]);
	sprintf(rs, "%d", i);
	LOGD("[返回值解析] -> %s", rs);
	return true;
}
