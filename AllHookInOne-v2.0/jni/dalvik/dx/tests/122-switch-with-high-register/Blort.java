class Blort {

    public static int switchWithHighRegister(
            int param1, int param2, int param3, int param4, int param5, int param6, int param7, int param8, int param9, int param10, int param11, int param12, int param13, int param14, int param15, int param16, int param17, int param18, int param19, int param20, int param21, int param22, int param23, int param24, int param25, int param26, int param27, int param28, int param29, int param30, int param31, int param32, int param33, int param34, int param35, int param36, int param37, int param38, int param39, int param40, int param41, int param42, int param43, int param44, int param45, int param46, int param47, int param48, int param49, int param50, int param51, int param52, int param53, int param54, int param55, int param56, int param57, int param58, int param59, int param60, int param61, int param62, int param63, int param64, int param65, int param66, int param67, int param68, int param69, int param70, int param71, int param72, int param73, int param74, int param75, int param76, int param77, int param78, int param79, int param80, int param81, int param82, int param83, int param84, int param85, int param86, int param87, int param88, int param89, int param90, int param91, int param92, int param93, int param94, int param95, int param96, int param97, int param98, int param99, int param100, int param101, int param102, int param103, int param104, int param105, int param106, int param107, int param108, int param109, int param110, int param111, int param112, int param113, int param114, int param115, int param116, int param117, int param118, int param119, int param120, int param121, int param122, int param123, int param124, int param125, int param126, int param127, int param128, int param129, int param130, int param131, int param132, int param133, int param134, int param135, int param136, int param137, int param138, int param139, int param140, int param141, int param142, int param143, int param144, int param145, int param146, int param147, int param148, int param149, int param150, int param151, int param152, int param153, int param154, int param155, int param156, int param157, int param158, int param159, int param160, int param161, int param162, int param163, int param164, int param165, int param166, int param167, int param168, int param169, int param170, int param171, int param172, int param173, int param174, int param175, int param176, int param177, int param178, int param179, int param180, int param181, int param182, int param183, int param184, int param185, int param186, int param187, int param188, int param189, int param190, int param191, int param192, int param193, int param194, int param195, int param196, int param197, int param198, int param199, int param200, int param201, int param202, int param203, int param204, int param205, int param206, int param207, int param208, int param209, int param210, int param211, int param212, int param213, int param214, int param215, int param216, int param217, int param218, int param219, int param220, int param221, int param222, int param223, int param224, int param225, int param226, int param227, int param228, int param229, int param230, int param231, int param232, int param233, int param234, int param235, int param236, int param237, int param238, int param239, int param240, int param241, int param242, int param243, int param244, int param245, int param246, int param247, int param248, int param249, int param250, int param251, int param252, int param253, int param254,
            int param255) {

        // this should add a new non-parameter register, and force the register
        // for param255 over v255
        int i=1;

        // make sure that it can't re-use one of the parameter registers for i
        System.out.println(Integer.toString(i+param1+param2+param3+param4+param5+param6+param7+param8+param9+param10+param11+param12+param13+param14+param15+param16+param17+param18+param19+param20+param21+param22+param23+param24+param25+param26+param27+param28+param29+param30+param31+param32+param33+param34+param35+param36+param37+param38+param39+param40+param41+param42+param43+param44+param45+param46+param47+param48+param49+param50+param51+param52+param53+param54+param55+param56+param57+param58+param59+param60+param61+param62+param63+param64+param65+param66+param67+param68+param69+param70+param71+param72+param73+param74+param75+param76+param77+param78+param79+param80+param81+param82+param83+param84+param85+param86+param87+param88+param89+param90+param91+param92+param93+param94+param95+param96+param97+param98+param99+param100+param101+param102+param103+param104+param105+param106+param107+param108+param109+param110+param111+param112+param113+param114+param115+param116+param117+param118+param119+param120+param121+param122+param123+param124+param125+param126+param127+param128+param129+param130+param131+param132+param133+param134+param135+param136+param137+param138+param139+param140+param141+param142+param143+param144+param145+param146+param147+param148+param149+param150+param151+param152+param153+param154+param155+param156+param157+param158+param159+param160+param161+param162+param163+param164+param165+param166+param167+param168+param169+param170+param171+param172+param173+param174+param175+param176+param177+param178+param179+param180+param181+param182+param183+param184+param185+param186+param187+param188+param189+param190+param191+param192+param193+param194+param195+param196+param197+param198+param199+param200+param201+param202+param203+param204+param205+param206+param207+param208+param209+param210+param211+param212+param213+param214+param215+param216+param217+param218+param219+param220+param221+param222+param223+param224+param225+param226+param227+param228+param229+param230+param231+param232+param233+param234+param235+param236+param237+param238+param239+param240+param241+param242+param243+param244+param245+param246+param247+param248+param249+param250+param251+param252+param253+param254));

        // the register for param255 should be greater than v255, forcing dx
        // to generate a move instruction to move it to a lower register
        switch (param255) {
            case 0:
                return 0;
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return 3;
            case 4:
                return 4;
        }
        return -1;
    }
}
