package com.example.allhookinone;

import java.text.SimpleDateFormat;

import android.location.Location;
import android.location.LocationManager;
import android.net.wifi.WifiInfo;
import android.util.Log;


public class Runner extends Thread {

	private int ThreadNumber = 0;

	public void setNum(int num){
		this.ThreadNumber=num;
	}

    public String getCurrentTime(){
        long t=System.currentTimeMillis();
        SimpleDateFormat sdFormat = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss:SSS");
        return sdFormat.format(t);
    }

	public void fun1(){
	   Location location = MainActivity.location.getLastKnownLocation(LocationManager.GPS_PROVIDER);
       if(location != null){
           Log.i("Thread", location.toString());
       }
       Log.i("Thread","getLastKnownLcoation failed");
       
	}

	public void fun2(){
        WifiInfo info = MainActivity.wifi.getConnectionInfo();
        info.getMacAddress();
        Log.i("Thread", "MacAddress is"+info.getMacAddress());
	}

	public void fun3(){
	    String deviceId = MainActivity.telephony.getDeviceId();
	    if(deviceId != null){
	        Log.i("Thread","deviceId is "+deviceId);
	    }
	}
    
	public void run() {
//	    while(true){
	        System.out.println("[T]"+getCurrentTime() + " fun "+ this.ThreadNumber +".1 started!!!"); 
            fun1();
            System.out.println("[T]"+getCurrentTime() + " fun "+ this.ThreadNumber +".1 ended "+ this.ThreadNumber+".2 started!!!");    
            fun2();
            System.out.println("[T]"+getCurrentTime() + " fun "+ this.ThreadNumber +".2 ended "+ this.ThreadNumber+".3 started!!!");    
            fun3();
            System.out.println("[T]"+getCurrentTime() + " fun "+ this.ThreadNumber +".3 ended!!!");
//	    }


               
}
}
