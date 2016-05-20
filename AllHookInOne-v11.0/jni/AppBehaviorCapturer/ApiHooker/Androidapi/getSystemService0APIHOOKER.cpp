//�Զ����� by lh
#include  "getSystemService0APIHOOKER.h"
getSystemService0ApiHooker::getSystemService0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/ContextWrapper",
"getSystemService","(Ljava/lang/String;)Ljava/lang/Object;",false,NULL,NULL,NULL));}
getSystemService0ApiHooker::~getSystemService0ApiHooker() {}
