package com.lwl.service;


import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import com.lwl.time.AppTimeTestUtils;
import com.lwl.time.AppToHookerTimeTestUtils;
import com.lwl.time.HookerTimeTestUtils;
import com.lwl.time.ServerToHookerTimeTestUtils;
import com.lwl.time.TimeTestUtils;

import android.content.Context;
import android.util.Log;

public class WriteTimeToFileThread extends Thread{
    
    private Context context;
    private FileOutputStream fo;
    private FileInputStream  fi;
    
    private AppTimeTestUtils appTimeTest = AppTimeTestUtils.getInstance();
    private HookerTimeTestUtils hookerTimeTest = HookerTimeTestUtils.getInstance();
    private AppToHookerTimeTestUtils appToHookerTimeTest = AppToHookerTimeTestUtils.getInstance();
    private ServerToHookerTimeTestUtils serverToHookerTimeTest = ServerToHookerTimeTestUtils.getInstance();
    
    public static boolean writeFlags = false;
    public static final String FILE_NAME = "/data/inj-allhookinone/time-test.txt";
    private static final String TAG = "WriteIntoFile";
    
    
    /**  
     * 构造函数
     */ 
    public WriteTimeToFileThread(Context context) {
        super();
        this.context = context;
    }
    
    @Override
    public void run() {
		// TODO Auto-generated method stub
		// 等待写标志位置true
		while (!writeFlags) {
		}
		writeToFile(context, FILE_NAME);
		Log.i(TAG, "写入文件已结束");
    }
    
    /**  
     * 将数组内容写入文件
     * @param context
     * @param filename
     * @return
     */
    public int writeToFile(Context context,String filename){
        try {
            //写入前先清空文件的内容
            //此地方也可以不清空，写入几个换行符，然后记录测试的次数
            fo = context.openFileOutput(filename, Context.MODE_MULTI_PROCESS);
            fo.write("".getBytes());
            fo.flush();
            
            fo = context.openFileOutput(filename, Context.MODE_MULTI_PROCESS + Context.MODE_APPEND);
            
            writeT1T2ToFile();
            writeT3T2SubtractToFile();
            writeT3T4ToFile();
            writeNetWorkDelayToFile();
            
            fi = context.openFileInput(filename);
            int length = fi.available();
            byte[] buffer = new byte[length];
            fi.read(buffer);
            String ss = new String(buffer,"GB2312");
            //输出文件中的内容
            System.out.println(ss);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } finally {
            if (fo != null) {
                try {
                    fo.close();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
            if (fi != null) {
                try {
                    fi.close();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }

        }
        return 0;
    } 
    
    private int writeT1T2ToFile(){
        
        try {
            //写t1
            byte[] byte1 = TimeTestUtils.stringAry2String("t1_start_handle_time",appTimeTest.t1_start_handle_time).getBytes();
            fo.write(byte1);
            fo.flush();
            //写入换行符用于区分
            fo.write('\n');
            fo.flush();
            
            //写t2
            byte[] byte2 = TimeTestUtils.stringAry2String("t2_end_handle_time",appTimeTest.t2_end_handle_time).getBytes();
            fo.write(byte2);
            fo.flush();
            fo.write('\n');
            fo.flush();
            
            //写t2-t1
            byte[] byte3 = TimeTestUtils.stringAry2String("t2_t1_subtract",appTimeTest.t2_t1_subtract).getBytes();
            fo.write(byte3);
            fo.flush();
            fo.write('\n');
            fo.flush();
            
            //写avg(t2-t1)
            byte[] byte4 = TimeTestUtils.string2String("avg_t2_t1_subtract", appTimeTest.t2t1DiffAvgStr).getBytes();
            fo.write(byte4);
            fo.flush();
            fo.write('\n');
            fo.flush();
            
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return 0;
    }
    
    private int writeT3T2SubtractToFile(){
        
        try {
            //写t3-t2
            byte[] byte1 = TimeTestUtils.stringAry2String("t3_t2_subtract",appToHookerTimeTest.t3_t2_subtract).getBytes();
            fo.write(byte1);
            fo.flush();
            //写入换行符用于区分
            fo.write('\n');
            fo.flush();
            
            //写avg(t3-t2)
            System.out.println("avg_t3_t2_subtract" + appToHookerTimeTest.t3t2DiffAvgStr);
            byte[] byte2 = TimeTestUtils.string2String("avg_t3_t2_subtract",appToHookerTimeTest.t3t2DiffAvgStr).getBytes();
            fo.write(byte2);
            fo.flush();
            fo.write('\n');
            fo.flush();
            
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return 0;
    }
    
    private int writeT3T4ToFile(){
        
        try {
            //写t3
            byte[] byte1 = TimeTestUtils.stringAry2String("t3_receive_time",hookerTimeTest.t3_receive_time).getBytes();
            fo.write(byte1);
            fo.flush();
            //写入换行符用于区分
            fo.write('\n');
            fo.flush();
            
            //写t4
            byte[] byte2 = TimeTestUtils.stringAry2String("t4_send_time",hookerTimeTest.t4_send_time).getBytes();
            fo.write(byte2);
            fo.flush();
            fo.write('\n');
            fo.flush();
            
            //写t4-t3
            byte[] byte3 = TimeTestUtils.stringAry2String("t4_t3_time_subtract",hookerTimeTest.t4t3DiffStr).getBytes();
            fo.write(byte3);
            fo.flush();
            fo.write('\n');
            fo.flush();
            
            //写avg(t4-t3)
            byte[] byte4 = TimeTestUtils.string2String("avg_t4_t3_subtract",hookerTimeTest.t4t3DiffAvgStr).getBytes();
            fo.write(byte4);
            fo.flush();
            fo.write('\n');
            fo.flush();
            
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return 0;
    }
    private int writeNetWorkDelayToFile(){
        
        try {
            //t7
            byte[] byte1 = TimeTestUtils.stringAry2String("t7_receive_time_str",serverToHookerTimeTest.t7TimestampDateStr).getBytes();
            fo.write(byte1);
            fo.flush();
            //写入换行符用于区分
            fo.write('\n');
            fo.flush();
            
            //写网络时延
            byte[] byte3 = TimeTestUtils.stringAry2String("network_delay_str",serverToHookerTimeTest.network_delay_str).getBytes();
            fo.write(byte3);
            fo.flush();
            //写入换行符用于区分
            fo.write('\n');
            fo.flush();
            
            //写平均网络时延
            byte[] byte2 = TimeTestUtils.string2String("avg_network_delay_str",serverToHookerTimeTest.avg_network_delay_str).getBytes();
            fo.write(byte2);
            fo.flush();
            fo.write('\n');
            fo.flush();
            
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return 0;
    }

}
