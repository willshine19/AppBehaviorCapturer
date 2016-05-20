//�Զ����� by lh
#include  "bindService0APIHOOKER.h"
bindService0ApiHooker::bindService0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"bindService","(Landroid/content/Intent;Landroid/content/ServiceConnection;I)Z",false,NULL,NULL,NULL));}
bindService0ApiHooker::~bindService0ApiHooker() {}
