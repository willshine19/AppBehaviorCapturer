package com.example.ratest;

import java.io.IOException;
import java.lang.reflect.Method;
import java.net.MalformedURLException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;

import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;

import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.net.wifi.WifiManager;
import android.telephony.SmsManager;
import android.telephony.TelephonyManager;
import android.util.Log;

import com.android.internal.telephony.ITelephony;


public class Communication {//手机通信
	
	public static void doSmsMessager(){
		try {
			String phone = "13120329802";
			String context = "ce shi ji";
			SmsManager manager = SmsManager.getDefault();
			manager.sendTextMessage(phone, null, context, null, null);
			Log.i("TEST APP", "[38] android.telephony.gsm.SmsManager sendTextMessage");
			manager.sendDataMessage(phone, null, (short) 6000,
					context.getBytes(), null, null);
			Log.i("TEST APP", "[36] android.telephony.gsm.SmsManager sendDataMessage");
			ArrayList<String> parts = manager.divideMessage(context);
			manager.sendMultipartTextMessage(phone, null, parts, null, null);
			Log.i("TEST APP", "[37] android.telephony.gsm.SmsManager sendMultipartTextMessage");
		} catch (Exception e) {
			Log.v("SmsMessager", "SmsMessager is wrong");
			e.printStackTrace();
		}
	}
	
	public static void doItelephony(Context context){
		
		TelephonyManager mTelephonyManager = (TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);
		
		  Class<TelephonyManager> c = TelephonyManager.class;
		  Method getITelephonyMethod = null;
		  try {
			// 获取所有public/private/protected/默认
			// 方法的函数，如果只需要获取public方法，则可以调用getMethod.
			getITelephonyMethod = c.getDeclaredMethod("getITelephony", (Class[]) null);
			// 将要执行的方法对象设置是否进行访问检查，也就是说对于public/private/protected/默认
			// 我们是否能够访问。值为 true 则指示反射的对象在使用时应该取消 Java 语言访问检查。值为 false
			// 则指示反射的对象应该实施 Java 语言访问检查。
			getITelephonyMethod.setAccessible(true);
			ITelephony iTelephony = (ITelephony) getITelephonyMethod.invoke(mTelephonyManager, (Object[]) null);
			iTelephony.call("13120329802");
			Log.i("TEST APP", "[39] Itelephony call");
			iTelephony.endCall();
			Log.i("TEST APP", "[40] Itelephony endCall");
		  } catch (Exception e) {
		  } 
	}

	public static void doBluetoothAdapter(){
		try{
					BluetoothAdapter mBluetoothAdapter; // 本机蓝牙适配器对象
					mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter(); // 获得本机蓝牙适配器对象引用
					mBluetoothAdapter.enable();
					Log.i("TEST APP", "[42] android.bluetooth.BluetoothAdapter enable");
					mBluetoothAdapter.disable();
					Log.i("TEST APP", "[41] android.bluetooth.BluetoothAdapter disable");
		}catch (Exception e) {
			// TODO Auto-generated catch block
			Log.v("BluetoothAdapter", "BluetoothAdapter is wrong");
			e.printStackTrace();
		}	
		

	}

	public static void dosocket() {
		//http://www.cnblogs.com/harrisonpc/archive/2011/03/31/2001565.html
		Socket client;
		try {
			client = new Socket("127.0.0.1", 12345);
			Log.i("TEST APP", "[43] java.net.Socket Socket");
			client.close();
			Log.i("TEST APP", "[44] java.net.Socket close");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.v("Socket", "Socket is wrong");
		}
	}
	public static void doURL(){
		//http://vinny-w.iteye.com/blog/1327743
		URL myURL;
		try {
			myURL = new URL("HTTP://www.baidu.com/hello.txt&quot");
			URLConnection ucon = myURL.openConnection(); // 打开URL链接  
			Log.i("TEST APP", "[45] java.net.URL openConnection");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.v("URL", "URL is wrong");
		} 
	}
	
	public static void doHttp(){
		try{
					String url = "http://10.3.8.211/";  
					HttpGet httpGet = new HttpGet(url); 
					Log.i("TEST APP", "[46] org.apache.http.client.methods.HttpGet HttpGet");
					HttpPost httpPost = new HttpPost(url);
					Log.i("TEST APP", "[47] org.apache.http.client.methods.HttpPost HttpPost");
		}catch (Exception e) {
			// TODO Auto-generated catch block
			Log.v("Http", "Http is wrong");
			e.printStackTrace();
		}	
		

	}
	
	public static void dowifi(Context context){
		try{
			WifiManager mWifiManager; 
			mWifiManager=(WifiManager) context.getSystemService(Context.WIFI_SERVICE);
			mWifiManager.setWifiEnabled(true);
			Log.i("TEST APP", "[50] android.net.wifi.WifiManager setWifiEnabled");
			mWifiManager.enableNetwork(0, true);
			Log.i("TEST APP", "[49] android.net.wifi.WifiManager enableNetwork");
		}catch (Exception e) {
			// TODO Auto-generated catch block
			Log.v("wifi", "wifi is wrong");
			e.printStackTrace();
		}	

	}
	
	
	
	
	
	
	
	
	
	
}
