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

class ApiHooker{
	protected:
//		CollectedApiInfo mCollectedApiInfo;
		ApiDeclaration mApiDeclaration;
		pthread_mutex_t lock;
		int mQueuePosition;
	public:
		HookInfo save;
		ApiHooker();
		virtual ~ApiHooker();
		//成员函数
		bool collectBaseInfo(Thread* self);
		bool saveToQueue();
		bool main(Thread* self);
		ApiDeclaration getApiDeclaration();
		virtual bool parseParameter(){
			LOGD("parseParamter method has called in ApiHooker");
			return true;
		}
		virtual bool simpleProcess(){
			LOGD("simpleProcess method has called in ApiHooker");
			return true;
		}
		string toString();

};

#endif /* APIHOOKER_H_ */
