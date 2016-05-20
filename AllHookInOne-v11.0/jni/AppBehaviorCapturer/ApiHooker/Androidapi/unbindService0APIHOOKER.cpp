//�Զ����� by lh
#include  "unbindService0APIHOOKER.h"
unbindService0ApiHooker::unbindService0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"unbindService","(Landroid/content/ServiceConnection;)V",false,NULL,NULL,NULL));}
unbindService0ApiHooker::~unbindService0ApiHooker() {}
