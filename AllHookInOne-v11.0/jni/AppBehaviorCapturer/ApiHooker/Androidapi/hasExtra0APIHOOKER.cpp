//�Զ����� by lh
#include  "hasExtra0APIHOOKER.h"
hasExtra0ApiHooker::hasExtra0ApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
			"hasExtra", "(Ljava/lang/String;)Z", false, NULL, NULL, NULL));
}
hasExtra0ApiHooker::~hasExtra0ApiHooker() {
}
