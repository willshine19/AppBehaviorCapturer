
package com.fortysevendeg.android.swipelistview.sample.activities;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.widget.TextView;
import com.fortysevendeg.android.swipelistview.sample.activities.SwipeListViewExampleActivity;
import com.fortysevendeg.android.swipelistview.sample.activities.SplashScreen;
import com.fortysevendeg.android.swipelistview.sample.adapters.PackageItem;
import com.fortysevendeg.android.swipelistview.R;

public class SplashScreen extends Activity {// 引导页，检测较耗时，在此运行

    private ArrayList<Integer> JudgeSet = new ArrayList<Integer>();// 检测结果
    
    private String[] running_process = new String[300];

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.splash);

        try {
            TextView versionNumber = (TextView) findViewById(R.id.versionNumber);
            versionNumber.setText("Version " + 1.0);
        } catch (Exception e) {// NameNotFoundException
            e.printStackTrace();
        }

        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                setData();
            }
        }, 100);

        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent();
                intent.setClass(SplashScreen.this, SwipeListViewExampleActivity.class);

                // //可传自定义的item，不过不能传图片
                intent.putIntegerArrayListExtra("Judge", JudgeSet);
                startActivity(intent);
                SplashScreen.this.finish();
            }
        }, 11500);

    }

   

    public void setData() {
        PackageManager appInfo = getPackageManager();
        // Return a List of all application packages that are installed on the device.
        List<ApplicationInfo> listInfo = appInfo.getInstalledApplications(0);
        Collections.sort(listInfo, new ApplicationInfo.DisplayNameComparator(appInfo));
        // 通过调用ps终端指令，获取正在运行的进程信息，填充sline数组
        getRunningProcess();

        for (int index = 0; index < listInfo.size(); index++) {// 找到了，建立list
            try {
                ApplicationInfo content = listInfo.get(index);
                if ((content.flags != ApplicationInfo.FLAG_SYSTEM) && content.enabled) {
                    if (content.icon != 0) {
                        PackageItem item = new PackageItem();
                        // set Application Name
                        item.setName(getPackageManager().getApplicationLabel(content).toString());
                        // set package name
                        item.setPackageName(content.packageName);
                        // 判断item对应app是否运行
                        Integer i = setRunningStatus(item);
                        // 将item对应app运行状态装填至JudgeSet中
                        JudgeSet.add(i);// index,
                        Log.v("index", "" + index);
                    }
                }
            } catch (Exception e) {

            }
        }

    }

    public void getRunningProcess() {
        Process process = null;
        DataOutputStream os = null;
        DataInputStream is = null;

        try {
            process = Runtime.getRuntime().exec("su");
            os = new DataOutputStream(process.getOutputStream());
            is = new DataInputStream(process.getInputStream());
            BufferedReader bfr = new BufferedReader(new InputStreamReader(is));

            os.writeBytes("ps\n");
            os.flush();
            os.writeBytes("exit\n");
            os.flush();

            for (int i = 0; i < 300; i++) {
                running_process[i] = bfr.readLine();
//                Log.v("line", sline[i]);
            }

        } catch (Exception e) {
            // TODO Auto-generated catch block
            Log.e("Error", e.getMessage());
            e.printStackTrace();
        }

    }

    public String findPid(PackageItem item) {
        String pid = "";

        try {
            String pName = item.getPackageName();
            Log.v("pid", "packageName :" + pName);

            for (int i = 0; i < 300; i++) {

                if ((running_process[i]) != null) { // 读取输出 line = bfr.readLine()
                    if (running_process[i].contains(pName)) {
                        String[] splitline = running_process[i].split("\\s+");
                        pid = splitline[1];
//                        Log.v("line", pid);
                    }
                }
            }
        } catch (Exception e) {
            // TODO Auto-generated catch block
            Log.e("Error", e.getMessage());
            e.printStackTrace();
        }
        return pid;
    }

    public int setRunningStatus(PackageItem item) {// , View convertView
        Process process = null;
        DataOutputStream os = null;
        DataInputStream is = null;

        String pid;
        pid = findPid(item);
        if (pid == "") {
            return 0;// 未运行
        }
        try {

            process = Runtime.getRuntime().exec("su");
            os = new DataOutputStream(process.getOutputStream());
            is = new DataInputStream(process.getInputStream());
            BufferedReader bfr = new BufferedReader(new InputStreamReader(is));

            String pName = item.getPackageName();
            Log.v("Injector", "packageName :" + pName);

            String line = null;

            os.writeBytes("cat /proc/" + pid + "/maps | grep libgetJNIEnv.so\n");
            os.flush();
            os.writeBytes("exit\n");
            os.flush();

            Log.v("Injector", "Not been injected");

            while ((line = bfr.readLine()) != null) { // 读取输出
                if (line.contains("liballhookinone.so")) {
                    Log.v("Injector", "Has been injected");
                    return 1;// 已注入
                }
            }
            process.waitFor();

        } catch (Exception e) {
            // TODO Auto-generated catch block
            Log.e("Error", e.getMessage());
            e.printStackTrace();
        }
        return 2;// 未注入
    }

}
