//�Զ����� by lh
#include  "setData0APIHOOKER.h"
setData0ApiHooker::setData0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
"setData","(Landroid/net/Uri;)Landroid/content/Intent;",false,NULL,NULL,NULL));}
setData0ApiHooker::~setData0ApiHooker() {}
