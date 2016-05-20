//�Զ����� by lh
#include  "startActivity0APIHOOKER.h"
startActivity0ApiHooker::startActivity0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"startActivity","(Landroid/content/Intent;Landroid/os/Bundle;)V",false,NULL,NULL,NULL));}
startActivity0ApiHooker::~startActivity0ApiHooker() {}
