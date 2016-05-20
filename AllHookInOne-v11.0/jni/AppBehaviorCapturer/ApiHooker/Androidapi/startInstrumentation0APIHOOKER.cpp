//�Զ����� by lh
#include  "startInstrumentation0APIHOOKER.h"
startInstrumentation0ApiHooker::startInstrumentation0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"startInstrumentation","(Landroid/content/ComponentName;Ljava/lang/String;Landroid/os/Bundle;)Z",false,NULL,NULL,NULL));}
startInstrumentation0ApiHooker::~startInstrumentation0ApiHooker() {}
