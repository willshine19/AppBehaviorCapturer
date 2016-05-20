//�Զ����� by lh
#include  "getIntent0APIHOOKER.h"
getIntent0ApiHooker::getIntent0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
"getIntent","(Ljava/lang/String;)Landroid/content/Intent;",true,NULL,NULL,NULL));}
getIntent0ApiHooker::~getIntent0ApiHooker() {}
