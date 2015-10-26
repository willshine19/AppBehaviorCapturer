package com.lwl.utils;

import android.annotation.SuppressLint;
import android.content.Context;
import android.util.Log;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;


/**  
 *   t4-t3:Manager转发时延
 *   内部存放t3、t4、t4-t3以及t4-t3的平均值
 */  
@SuppressLint("SimpleDateFormat")
public class HookerTimeTestUtils  extends TimeTestUtils{

    // 设置输出时间的格式 年-月-日 小时：分钟：秒：毫秒
    private SimpleDateFormat s;

    public int t3_count = 0;
    public int t4_count = 0;
    // t3时间存储
    public ArrayList<String> t3_receive_time;
    // t3纳秒级时间存储
    public ArrayList<Long> t3TimeStampNanosecond;
    
    // t4时间存储
    public ArrayList<String> t4_send_time;
    // t4纳秒级存储
    public ArrayList<Long> t4TimeStampNanosecond;
    
    //时间间隔存储
    public ArrayList<String> t4t3DiffStr;
    // 纳秒时间 间隔
    public ArrayList<Long> t4t3DiffNanosecond;
    
    //平均时间间隔
    public String t4t3DiffAvgStr; // 单位 s:ma:us
    
    private static final String TAG = "TimeTest";
    private static HookerTimeTestUtils single = null;

    /**  
     * 私有的默认构造，初始化数组与时间输出格式
     */ 
    private HookerTimeTestUtils() {
        t3_receive_time = new ArrayList<String>();
        t3TimeStampNanosecond = new ArrayList<Long>();
        t4_send_time = new ArrayList<String>();
        t4TimeStampNanosecond = new ArrayList<Long>();
        t4t3DiffStr = new ArrayList<String>();
        t4t3DiffNanosecond = new ArrayList<Long>();
        s = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SS");
    }
    
    /**  
     * 返回单例
     */
    public static HookerTimeTestUtils getInstance() {
        if (single == null) {
            single = new HookerTimeTestUtils();
        }
        return single;
    }
    
    /**  
     * 获取当前时间，并将时间存储到t3数组，返回时间的字符串
     * 设置数组t3_receive_long_format，t3_receive_time
     */
    public  String setT3ReceiveTime() {
        //获取当前时间（纳秒单位）,保存至long数组中
        t3TimeStampNanosecond.add(System.nanoTime());
        //输出正常
        // 格式化时间，返回字符串类型
        String temp = s.format(new Date());
        t3_receive_time.add(temp);
        t3_count++;
        return temp;
    }
    
    /**  
     * 获取当前时间，并将时间存储到t4数组，返回时间的字符串
     * 设置数组t4_send_long_format，t4_send_time
     */
    public  String setT4SendTime() {
        //获取当前时间（纳秒单位）,保存至long数组中
        //System.nanoTime()，此方法只能用于测量已过的时间，与系统或钟表时间的其他任何时间概念无关
        t4TimeStampNanosecond.add(System.nanoTime());
        // 格式化时间，返回字符串类型
        String temp = s.format(new Date());
        t4_send_time.add(temp);
        t4_count++;
        return temp;
    }
    
    /**  
     * 计算时间间隔，并保存
     * 设置数组time_subtract，time_subtract_long_format
     */
    public int setT4T3Subtract(){
        
        //通过判断t3_count与t4_count是否相等，t3_receive_long_format，t4_send_long_format是否是配对的
        if(t3_count != t4_count){
            System.out.println("执行过程出错");
            return -1;
        }
        
		for (int i = 0; i < CESHI_NUMBER; i++) {
            long subtract = t4TimeStampNanosecond.get(i) - t3TimeStampNanosecond.get(i);
            //将long类型时间差存入数组
            t4t3DiffNanosecond.add(subtract);
            //设置时间差值的格式
            String temp = subtract/1000000000 + ":" + subtract%1000000000/1000000 + ":" + subtract%1000000/1000;
            //将String类型时间差值存入数组
            t4t3DiffStr.add(temp);
        }
        return 0;
    }
    
    /**  
     * 计算平均时间间隔并保存
     */
	public int calculateAvgT4T3Subtract() {
		long sum = 0;

		for (int i = 0; i < CESHI_NUMBER; i++) {
			sum += t4t3DiffNanosecond.get(i);
		}
		long avg = sum / CESHI_NUMBER;
        
        t4t3DiffAvgStr = avg/1000000000 + ":" + avg%1000000000/1000000 + ":" + avg%1000000/1000;
        return 0;
    }
	
	/**  
	 * 将采集到的数据打印到logcat
	 */
	public void print() {
		
//		Log.d(TAG, "t3_receive_time: ");
//		for (int i = 0; i < CESHI_NUMBER; i++) {
//			Log.v(TAG, t3_receive_time.get(i));
//		} 
//		Log.d(TAG, "t4_send_time:");
//		for (int i = 0; i < CESHI_NUMBER; i++) {
//			Log.v(TAG, t4_send_time.get(i));
//		} 
		
		Log.d(TAG, "t4_t3_time_subtract:");
		for (int i = 0; i < CESHI_NUMBER; i++) {
			Log.v(TAG, t4t3DiffStr.get(i));
		} 
		Log.d(TAG, "t4t3DiffAvgStr (s:ms:um): " + t4t3DiffAvgStr);
	}
}
