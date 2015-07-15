package com.lwl.service;

import java.io.IOException;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;


public class JsonService extends Service{
    
    private int count;
    //用于service与activity交互
    private JsonBinder binder = new JsonBinder();
    
    public class JsonBinder extends Binder{
        public int getCount(){
            return count;
        }
    }

    @Override
    public void onCreate() {
        // TODO Auto-generated method stub
        super.onCreate();
        System.out.println("create socket_thread");
        new Thread(){
            @Override
            public void run() {
                try {
                    System.out.println("socket_thread bagins running");
                    MultiThreadJsonReceiveThread jsonThread= new MultiThreadJsonReceiveThread();
                    jsonThread.service();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }.start();
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO Auto-generated method stub
        return binder;
    }

}
