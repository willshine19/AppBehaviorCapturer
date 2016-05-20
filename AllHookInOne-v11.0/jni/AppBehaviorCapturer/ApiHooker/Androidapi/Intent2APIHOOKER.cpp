//�Զ����� by lh
#include  "Intent2APIHOOKER.h"
Intent2ApiHooker::Intent2ApiHooker() {
	this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
			"<init>", "(Ljava/lang/String;Landroid/net/Uri;)V", false, NULL,NULL, NULL));
}
Intent2ApiHooker::~Intent2ApiHooker() {
}
