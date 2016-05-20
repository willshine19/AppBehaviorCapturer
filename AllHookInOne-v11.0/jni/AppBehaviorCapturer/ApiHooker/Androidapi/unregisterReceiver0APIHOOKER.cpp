//�Զ����� by lh
#include  "unregisterReceiver0APIHOOKER.h"
unregisterReceiver0ApiHooker::unregisterReceiver0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"unregisterReceiver","(Landroid/content/BroadcastReceiver;)V",false,NULL,NULL,NULL));}
unregisterReceiver0ApiHooker::~unregisterReceiver0ApiHooker() {}
