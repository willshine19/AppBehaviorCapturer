//�Զ����� by lh
#include  "checkPermission0APIHOOKER.h"
checkPermission0ApiHooker::checkPermission0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"checkPermission","(Ljava/lang/String;II)I",false,NULL,NULL,NULL));}
checkPermission0ApiHooker::~checkPermission0ApiHooker() {}
