
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

/**  
 *   app的入口
 *   引导页，检测较耗时，在此运行
 */  
public class SplashScreen extends Activity {

    /**  所有安装在终端的app的状态，三个状态：0未运行， 1已注入， 2未注入  */  
    private ArrayList<Integer> JudgeSet = new ArrayList<Integer>();// 检测结果
    /**  正在执行的进程信息  */  
    private String[] runningProcess = new String[300];

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.splash);

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

   

    /**  
     * 在新的线程中执行
     */
    public void setData() {
        PackageManager appInfo = getPackageManager();
        // Return a List of all application packages that are installed on the device.
        List<ApplicationInfo> listInfo = appInfo.getInstalledApplications(0);
        Collections.sort(listInfo, new ApplicationInfo.DisplayNameComparator(appInfo));
        
        getRunningProcess();

        for (int i = 0; i < listInfo.size(); i++) {// 找到了，建立list
            try {
                ApplicationInfo info = listInfo.get(i);
                // FLAG_SYSTEM: if set, this application is installed in the device's system image.
                
                if ((info.flags != ApplicationInfo.FLAG_SYSTEM) && info.enabled) {
                    if (info.icon != 0) {
                        PackageItem item = new PackageItem();
                        // set Application Name
                        item.setName(getPackageManager().getApplicationLabel(info).toString());
                        // set package name
                        item.setPackageName(info.packageName);
                        // 返回item对应app的状态
                        Integer status = setRunningStatus(item);
                        // 将item对应app运行状态装填至JudgeSet中
                        JudgeSet.add(status);// index,
                        Log.v("index", "" + i);
                    }
                }
            } catch (Exception e) {

            }
        }

    }

    
    /**  
     * 开启新进程，运行 ps，将所有正在运行的进程信息保存在runningProcess数组中
     */
    public void getRunningProcess() {
        Process process = null;
        DataOutputStream os = null;
        DataInputStream is = null;

        try {
            // 开启新进程
        	process = Runtime.getRuntime().exec("su");
            os = new DataOutputStream(process.getOutputStream());
            is = new DataInputStream(process.getInputStream());
            BufferedReader bfr = new BufferedReader(new InputStreamReader(is));

            os.writeBytes("ps\n");
            os.flush();
            os.writeBytes("exit\n");
            os.flush();

			for (int i = 0; i < 300; i++) {
				runningProcess[i] = bfr.readLine();
//				Log.v("getRunningProcess", runningProcess[i]);
			}
        } catch (Exception e) {
            // TODO Auto-generated catch block
            Log.e("Error", e.getMessage());
            e.printStackTrace();
        }
    }

    
    /**  
     * 返回目标进程的pid，通过包名
     * @param item 包信息
     * @return 目标进程pid
     */
    public String findPid(PackageItem item) {
        String pid = "";

        try {
            String pName = item.getPackageName();
//            Log.v("pid", "packageName :" + pName);

            for (int i = 0; i < 300; i++) {
                if ((runningProcess[i]) != null) { // 读取输出 line = bfr.readLine()
                    if (runningProcess[i].contains(pName)) {
                        String[] splitline = runningProcess[i].split("\\s+");
                        pid = splitline[1];
                        Log.v("findPid", pid);
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

    
    /**  
     * 返回应用的状态
     * @param item
     * @return 0未运行， 1已注入， 2未注入
     */
    public int setRunningStatus(PackageItem item) {// , View convertView
        Process process = null;
        DataOutputStream os = null;
        DataInputStream is = null;

        String pid = findPid(item);
        if (pid == "") {
            return 0;// 未运行
        }
        
        try {
            process = Runtime.getRuntime().exec("su");
            os = new DataOutputStream(process.getOutputStream());
            is = new DataInputStream(process.getInputStream());
            BufferedReader bfr = new BufferedReader(new InputStreamReader(is));

            String pName = item.getPackageName();
//            Log.v("Injector", "packageName :" + pName);

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
