//�Զ����� by lh
#include  "stopService0APIHOOKER.h"
stopService0ApiHooker::stopService0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"stopService","(Landroid/content/Intent;)Z",false,NULL,NULL,NULL));}
stopService0ApiHooker::~stopService0ApiHooker() {}
