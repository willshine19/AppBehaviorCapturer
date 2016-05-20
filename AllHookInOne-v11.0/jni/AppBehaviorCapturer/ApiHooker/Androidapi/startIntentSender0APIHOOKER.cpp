//�Զ����� by lh
#include  "startIntentSender0APIHOOKER.h"
startIntentSender0ApiHooker::startIntentSender0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"startIntentSender","(Landroid/content/IntentSender;Landroid/content/Intent;IIILandroid/os/Bundle;)V",false,NULL,NULL,NULL));}
startIntentSender0ApiHooker::~startIntentSender0ApiHooker() {}
