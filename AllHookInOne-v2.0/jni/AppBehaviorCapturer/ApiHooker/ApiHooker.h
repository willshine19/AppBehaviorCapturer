/*
 * ApiHooker.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef APIHOOKER_H_
#define APIHOOKER_H_

#include "../ApiInfo/ApiDeclaration.h"
#include "../ApiInfo/CollectedApiInfo.h"

class ApiHooker{
	protected:
		CollectedApiInfo mCollectedApiInfo;
		ApiDeclaration mApiDeclaration;
	public:

		ApiHooker();
		ApiHooker(ApiDeclaration* apiDeclaration,CollectedApiInfo* collectedApiInfo);
		virtual ~ApiHooker();
		//成员函数
		bool collectBaseInfo();
		bool saveToQueue();
		bool methodHandler();
		ApiDeclaration getApiDeclaration();

		virtual bool parseParameter(){
			return true;
		}
		virtual bool simpleProcess(){
			return true;
		}
		string toString();

};

#endif /* APIHOOKER_H_ */
