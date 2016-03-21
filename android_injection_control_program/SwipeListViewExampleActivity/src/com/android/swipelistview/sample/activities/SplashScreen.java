
package com.android.swipelistview.sample.activities;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;

import com.android.swipelistview.sample.adapters.PackageItem;
import com.android.swipelistview.sample.adapters.PackageItemModel;
import com.fortysevendeg.android.swipelistview.R;

/**  
 *   app的入口
 *   引导页，显示一个大针头
 */  
public class SplashScreen extends Activity {

    private static final String TAG = "SplashScreen";
    private static final int STATUS_NOT_RUNNING = 0;
    private static final int STATUS_INJECTED = 1;
    private static final int STATUS_NOT_INJECTED = 2;
    /**  正在执行的进程信息  */  
    private ArrayList<String> runningProcessList;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.splash);
        // 启动新线程 
        new InitingTask().execute();
    }

    /**  
     * 将手机上已安装的app的信息（封装在PackageItem）保存在PackageItemModel类（单例）中，这样别的Activity也可以访问
     */
    public void initAppInfoList() {
    	PackageManager pm = getPackageManager();
        // Return a List of all application packages that are installed on the device.
    	List<ApplicationInfo> installedAppList = pm.getInstalledApplications(0);
        Collections.sort(installedAppList, new ApplicationInfo.DisplayNameComparator(pm)); // 为什么要排序？
        PackageItemModel packageItems = PackageItemModel.getInstance();
    	
        // 遍历
        for (ApplicationInfo each : installedAppList) {
            // FLAG_SYSTEM: if set, this application is installed in the device's system image.
            if ((each.flags != ApplicationInfo.FLAG_SYSTEM) && each.enabled && each.icon != 0) {
                PackageItem item = new PackageItem();
                item.setName(pm.getApplicationLabel(each).toString());
                item.setPackageName(each.packageName);
                item.setIcon(pm.getDrawable(each.packageName, each.icon, each));
                item.setRunningStatus(getAppStatus(item));
                packageItems.add(item);
            }
        }
    }
    
    /**  
     * 用linux命令行运行 ps，将所有正在运行的进程信息保存在runningProcess数组中
     */
    public void initRunningProcessList() {
    	runningProcessList = new ArrayList<String>();
        Process process = null;
        DataOutputStream os = null;
        BufferedReader reader = null;

        try {
        	process = Runtime.getRuntime().exec("su");
            os = new DataOutputStream(process.getOutputStream());
            reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            os.writeBytes("ps\n");
            os.flush();
            String line = null;
            os.writeBytes("exit\n");
            os.flush();
            while ((line = reader.readLine()) != null) {
            	runningProcessList.add(line);
            }
        } catch (Exception e) {
            Log.e(TAG, e.getMessage());
            e.printStackTrace();
        } finally {
        	try {
        		if (os != null) {
        			os.close();
        		}
        		if (reader != null) {
        			reader.close();
        		}
        	} catch (IOException ex) {
        		Log.e(TAG,	"关闭流失败");
        	}
        }
    }
    
    /**  
     * 返回目标进程的pid，通过包名
     * 遍历runningProcesses,如果有这个app就返回他的进程号，如果没有就null
     * @param item 代表已安装到手机上的一个app
     * @return 进程号
     */
    public int findPid(PackageItem item) {
        int pid = -1;

        String pName = item.getPackageName();

        for (String each : runningProcessList) {
        	if(each.contains(pName)) {
        		String[] splitFactors = each.split("\\s+");
        		pid = Integer.parseInt(splitFactors[1]);
//        		Log.v("findPid", "" + pid);
        	}
        }
        return pid;
    }

    /**  
     * 返回应用的状态（未运行 已注入 未注入）
     * @param appInfo 代表一个已安装的app
     * @return 0未运行， 1已注入， 2未注入
     */
    public int getAppStatus(PackageItem appInfo) {
        Process process = null;
        DataOutputStream os = null;
        BufferedReader reader = null;

        int pid = findPid(appInfo);
        if (pid == -1) {
            return STATUS_NOT_RUNNING;
        }
        
        try {
            process = Runtime.getRuntime().exec("su");
            os = new DataOutputStream(process.getOutputStream());
            reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            os.writeBytes("cat /proc/" + pid + "/maps | grep libgetJNIEnv.so\n");
            os.flush();
            os.writeBytes("exit\n");
            os.flush();
            String line = null;
            while ((line = reader.readLine()) != null) {
            	if (line.contains("liballhookinone.so")) {
            		return STATUS_INJECTED;
            	}
            }
            process.waitFor();// 阻塞当前线程直到这个进程结束
        } catch (Exception e) {
            Log.e(TAG, e.getMessage());
            e.printStackTrace();
        } finally {
        	try {
        		if (os != null) {
        			os.close();
        		}
        		if (reader != null) {
        			reader.close();
        		}
        	} catch (IOException ex) {
        		Log.e(TAG, "关闭流失败");
        	}
        }
        return STATUS_NOT_INJECTED;// 未注入
    }
    
    /**
     * @author sang
     * 启动一个新的线程，这部分工作比较耗时，放在主线程中会影响ui更新。
     * doInBackground表示子线程中执行的任务，执行完后通知主线程
     * 子线程结束后，执行onPostExecute，这部分在主线程中执行
     */
    private class InitingTask extends AsyncTask<Void, Void, Void> {

    	@Override
    	protected Void doInBackground(Void... params) {
    		initRunningProcessList(); 
    		initAppInfoList();
    		return null;
    	}

    	@Override
		protected void onPostExecute(Void result) {
    		Intent intent = new Intent();
			intent.setClass(SplashScreen.this, SwipeListViewExampleActivity.class);
			startActivity(intent);
			SplashScreen.this.finish();
			super.onPostExecute(result);
		}
    }
}
