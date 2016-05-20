//�Զ����� by lh
#include  "getExtras0APIHOOKER.h"
getExtras0ApiHooker::getExtras0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
"getExtras","()Landroid/os/Bundle;",false,NULL,NULL,NULL));}
getExtras0ApiHooker::~getExtras0ApiHooker() {}
