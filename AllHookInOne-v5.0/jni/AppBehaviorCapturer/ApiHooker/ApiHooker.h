/*
 * ApiHooker.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef APIHOOKER_H_
#define APIHOOKER_H_

#include "common.h"
#include "../ApiInfo/ApiDeclaration.h"
#include "../ApiInfo/CollectedApiInfo.h"

class ApiHooker{
	protected:
		CollectedApiInfo mCollectedApiInfo;
		ApiDeclaration mApiDeclaration;
	public:

		HookInfo save;

		ApiHooker();
		virtual ~ApiHooker();
		//成员函数
		bool collectBaseInfo();
		bool saveToQueue();
		bool main();
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
