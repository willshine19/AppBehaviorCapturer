/*
 * QueryContentResolverApiHooker.cpp
 *
 *  Created on: 2015-6-16
 *      Author: long
 */

#include "QueryContentResolverApiHooker.h"

QueryContentResolverApiHooker::QueryContentResolverApiHooker() {
	// TODO Auto-generated constructor stub
	this->mApiDeclaration =
			*(new ApiDeclaration("android/content/ContentResolver", "query",
					"(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;Landroid/os/CancellationSignal;)Landroid/database/Cursor;",
					false, NULL, NULL, NULL));
}

QueryContentResolverApiHooker::~QueryContentResolverApiHooker() {
	// TODO Auto-generated destructor stub
}

bool QueryContentResolverApiHooker::parseResult(Object* obj) {
	const char* className = "java/lang/Object";//java/long/object!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	char* resultString = parseObjectToString(obj, className);
	LOGD("[返回值解析] -> %s", resultString);
	InfoSender::mCycledBlockingQueue->queue[this->mQueuePosition].setResult(
			resultString);
	return true;
}
