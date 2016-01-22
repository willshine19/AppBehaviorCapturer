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
	char rs[20];
	int* ma ;
	int i = 0;
	ma = (int*) obj;
	i = reinterpret_cast<int>(&ma[0]);
	sprintf(rs, "%d", i);
	LOGD("[返回值解析] -> %s", rs);
	StringObject* stringObjId = dvmCreateStringFromCstr(rs);
	char* resultString = dvmCreateCstrFromString(stringObjId);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(resultString);
	return true;
}

