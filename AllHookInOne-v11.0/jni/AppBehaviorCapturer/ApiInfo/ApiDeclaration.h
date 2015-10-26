/*
 * ApiDeclaration.h
 *
 *  Created on: 2015-4-1
 *      Author: long
 */

#ifndef ApiDeclaration_H_
#define ApiDeclaration_H_

#include <string>
using namespace std;

class ApiDeclaration {
	//成员变量
	string mClassName;
	string mMethodName;
	string mMethodSignature;
	bool mIsStaticMethod;
	void *mOriginalMethod;
	void *mReturnType;
	void *mParamTypes;
public:
	ApiDeclaration();
	ApiDeclaration(string mClassName,string mMethodName,string mMethodSignature,bool isStaticMethod,void *originalMethod,void *returnType,
	void *paramType);
	virtual ~ApiDeclaration();

	//成员函数
	string getClassName();
	string getApiName();
	string getApiSignature();
	bool isStaticMethod();
	void* getOriginalMethod();
	void* getReturnType();
	void* getParamTapes();

};


#endif /* ApiDeclaration_H_ */
