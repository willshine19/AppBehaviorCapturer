/*
 * ApiHooker.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef APIHOOKER_H_
#define APIHOOKER_H_
#include <pthread.h>
#include <stdio.h>
#include "common.h"
#include "../InfoSender/InfoSender.h"
#include "../ApiInfo/ApiDeclaration.h"
#include "../ApiInfo/CollectedApiInfo.h"
#include "../System/ThreadMap.h"

class ApiHooker{
	protected:
		ApiDeclaration mApiDeclaration;
		pthread_mutex_t lock;
		int mQueuePosition;
		char* parseObjectToString(Object* obj, const char* className);
	public:
		HookInfo save;
		ApiHooker();
		virtual ~ApiHooker();
		//成员函数
		bool collectBaseInfo();
		bool saveToQueue();
		long getFatherId();
		bool main(const u4* args);
		ApiDeclaration getApiDeclaration();
		virtual bool parseParameter(const u4* args){
			return true;
		}
		virtual bool parseResult(Object* obj) {
			return true;
		}
		virtual bool simpleProcess(){
			return true;
		}
		string toString();

};

#endif /* APIHOOKER_H_ */
