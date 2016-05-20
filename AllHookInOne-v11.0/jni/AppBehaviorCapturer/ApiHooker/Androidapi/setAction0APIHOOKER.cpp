//�Զ����� by lh
#include  "setAction0APIHOOKER.h"
setAction0ApiHooker::setAction0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
"setAction","(Ljava/lang/String;)Landroid/content/Intent;",false,NULL,NULL,NULL));}
setAction0ApiHooker::~setAction0ApiHooker() {}
