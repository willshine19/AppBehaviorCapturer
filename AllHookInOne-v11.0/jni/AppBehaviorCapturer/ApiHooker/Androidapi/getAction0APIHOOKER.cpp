//�Զ����� by lh
#include  "getAction0APIHOOKER.h"
getAction0ApiHooker::getAction0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
"getAction","()Ljava/lang/String;",false,NULL,NULL,NULL));}
getAction0ApiHooker::~getAction0ApiHooker() {}
