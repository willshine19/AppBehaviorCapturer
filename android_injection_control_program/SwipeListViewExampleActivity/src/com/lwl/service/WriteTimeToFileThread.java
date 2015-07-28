package com.lwl.service;


import com.lwl.utils.HookerTimeTestUtils;

import android.content.Context;

public class WriteTimeToFileThread extends Thread{
    
    private Context context;
    private HookerTimeTestUtils timeUtils;
    
    
    public static boolean writeFlags = false;
    public static final String FILE_NAME = "time-test.txt";
    
    
    public WriteTimeToFileThread(Context context, HookerTimeTestUtils timeUtils) {
        super();
        this.context = context;
        this.timeUtils = timeUtils;
    }
    @Override
    public void run() {
        // TODO Auto-generated method stub
        //等待写标志位置true
//        while(true){
            while(!writeFlags){}
            timeUtils.writeToFile(context, FILE_NAME);
//        }

        
    }


}
