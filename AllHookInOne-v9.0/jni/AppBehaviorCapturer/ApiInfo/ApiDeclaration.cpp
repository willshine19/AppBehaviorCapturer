/*
 * ApiDeclaration.cpp
 *
 *  Created on: 2015-4-1
 *      Author: long
 */
#include <iostream>
#include "ApiDeclaration.h"

using namespace std;

ApiDeclaration::ApiDeclaration(){
	// TODO Auto-generated constructor stub
}
ApiDeclaration::ApiDeclaration(string ClassName,string MethodName,string MethodSignature,bool isStaticMethod,void* originalMethod,void* returnType,void* paramType) {
	this->mClassName = ClassName;
	this->mMethodName = MethodName;
	this->mMethodSignature = MethodSignature;
	this->mIsStaticMethod = isStaticMethod;
	this->mOriginalMethod = originalMethod;
	this->mParamTypes = paramType;
	this->mReturnType = returnType;
}

ApiDeclaration::~ApiDeclaration() {
	// TODO Auto-generated destructor stub
}

string ApiDeclaration::getClassName(){
	return this->mClassName;
}
string ApiDeclaration::getApiName(){
	return this->mMethodName;
}
string ApiDeclaration::getApiSignature(){
	return this->mMethodSignature;
}
bool ApiDeclaration::isStaticMethod(){
	return this->mIsStaticMethod;
}
void* ApiDeclaration::getOriginalMethod(){
	return this->mOriginalMethod;
}
void* ApiDeclaration::getReturnType(){
	return this->mReturnType;
}
void* ApiDeclaration::getParamTapes(){
	return this->mParamTypes;
}
