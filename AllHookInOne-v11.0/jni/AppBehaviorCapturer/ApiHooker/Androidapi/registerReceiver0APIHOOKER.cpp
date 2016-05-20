//�Զ����� by lh
#include  "registerReceiver0APIHOOKER.h"
registerReceiver0ApiHooker::registerReceiver0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"registerReceiver","(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;Ljava/lang/String;Landroid/os/Handler;)Landroid/content/Intent;",false,NULL,NULL,NULL));}
registerReceiver0ApiHooker::~registerReceiver0ApiHooker() {}
