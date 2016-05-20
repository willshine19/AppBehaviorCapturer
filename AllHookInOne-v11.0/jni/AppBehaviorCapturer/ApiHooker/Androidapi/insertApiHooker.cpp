/*
 * CallTelephonnyApiHooker.cpp
 *
 *  Created on: 2015-6-4
 *      Author: long
 */

#include "insertApiHooker.h"

insertApiHooker::insertApiHooker() {
	// modified by lwl
	this->mApiDeclaration = *(new ApiDeclaration("android/database/sqlite/SQLiteDatabase",
			"insert","(Ljava/lang/String;Ljava/lang/String;Landroid/content/ContentValues;)J",false,NULL,NULL,NULL));
}

insertApiHooker::~insertApiHooker() {
	// TODO Auto-generated destructor stub
}

