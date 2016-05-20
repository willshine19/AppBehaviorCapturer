//�Զ����� by lh
#include  "sendBroadcastAsUser0APIHOOKER.h"
sendBroadcastAsUser0ApiHooker::sendBroadcastAsUser0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"sendBroadcastAsUser","(Landroid/content/Intent;Landroid/os/UserHandle;Ljava/lang/String;)V",false,NULL,NULL,NULL));}
sendBroadcastAsUser0ApiHooker::~sendBroadcastAsUser0ApiHooker() {}
