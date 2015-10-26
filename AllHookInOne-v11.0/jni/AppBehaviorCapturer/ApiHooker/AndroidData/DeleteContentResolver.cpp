/*
 * DeleteContentResolver.cpp
 *
 *  Created on: 2015-6-3
 *      Author: sang
 */

#include "DeleteContentResolver.h"

DeleteContentResolver::DeleteContentResolver() {
	this->mApiDeclaration = *(new ApiDeclaration("android/content/ContentResolver",
			"delete","(Landroid/net/Uri;Ljava/lang/String;[Ljava/lang/String;)I",false,NULL,NULL,NULL));

}

DeleteContentResolver::~DeleteContentResolver() {
	// TODO Auto-generated destructor stub
}

