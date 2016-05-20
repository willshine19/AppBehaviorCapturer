//�Զ����� by lh
#include  "getData0APIHOOKER.h"
getData0ApiHooker::getData0ApiHooker() {
this->mApiDeclaration = *(new ApiDeclaration("android/content/Intent",
"getData","()Landroid/net/Uri;",false,NULL,NULL,NULL));}
getData0ApiHooker::~getData0ApiHooker() {}
