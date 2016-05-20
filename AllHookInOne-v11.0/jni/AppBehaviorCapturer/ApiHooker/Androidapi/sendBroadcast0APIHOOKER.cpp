//�Զ����� by lh
#include  "sendBroadcast0APIHOOKER.h"
sendBroadcast0ApiHooker::sendBroadcast0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"sendBroadcast","(Landroid/content/Intent;Ljava/lang/String;)V",false,NULL,NULL,NULL));}
sendBroadcast0ApiHooker::~sendBroadcast0ApiHooker() {}
