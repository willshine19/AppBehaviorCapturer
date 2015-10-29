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
//#include "../System/ApiHookerManager.h"
//class ApiHookerManager;

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
		bool collectBaseInfo();
		bool saveToQueue();
		bool main(const u4* args);
		ApiDeclaration getApiDeclaration();
		virtual bool parseParameter(const u4* args){
			return true;
		}
		virtual bool simpleProcess(){
			return true;
		}
		string toString();

};

#endif /* APIHOOKER_H_ */
