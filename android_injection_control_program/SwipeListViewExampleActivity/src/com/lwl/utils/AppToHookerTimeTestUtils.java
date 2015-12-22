package com.lwl.utils;

import java.util.ArrayList;

import android.util.Log;


/**  
 *   内部存放t3-t2以及t3-t2的平均值
 */  
public class AppToHookerTimeTestUtils extends TimeTestUtils{
    
    //t3-t2时间存储,秒,毫秒
    public ArrayList<Long> t3_t2_long;
    // t3-2时间存储(String)
    public ArrayList<String>t3_t2_subtract;
    //t3-t2平均值 单位 s:ms
    public String t3t2DiffAvgStr;
    
    private static final String TAG = "TimeTest";

    //单例
    private static AppToHookerTimeTestUtils single = null;
    // 私有的默认构造，初始化数组与时间输出格式
    
    /**  
     * 构造函数  
     */ 
    private AppToHookerTimeTestUtils() {
        t3_t2_long = new ArrayList<Long>();
        t3_t2_subtract = new ArrayList<String>();
    }
    
    /**  
     * 返回单例，保证类只有一个，这样才能保证数据的准确度
     */
    public static AppToHookerTimeTestUtils getInstance() {
        if (single == null) {
            single = new AppToHookerTimeTestUtils();
        }
        return single;
    }

    
    /**  
     * 计算t3-t2的数值
     * 填充t3_t2_subtract， t3_t2_long
     */
    public int setT3T2Subtract() {
        AppTimeTestUtils app = AppTimeTestUtils.getInstance();
        HookerTimeTestUtils hooker = HookerTimeTestUtils.getInstance();
        String[] t2_temp;
        String[] t3_temp;
        for (int i = 0; i < CESHI_NUMBER; i++) {

            // 从t2_end_handle_time数组的字符串中解析出秒，毫秒
            t2_temp = app.t2_end_handle_time.get(i).split(":");
            long t2_long = Long.parseLong(t2_temp[2]) * 1000 + Long.parseLong(t2_temp[3]);

            // 从t3_receive_time数组中解析出秒，毫秒
            t3_temp = hooker.t3_receive_time.get(i).split(":");
            long t3_long = Long.parseLong(t3_temp[2]) * 1000 + Long.parseLong(t3_temp[3]);
            
            // 计算网络时延(t3-t2)，装填至
            t3_t2_long.add(t3_long - t2_long);
			String temp = Long.toString(t3_t2_long.get(i) / 1000) + ":"
					+ Long.toString(t3_t2_long.get(i) % 1000);
			t3_t2_subtract.add(temp);
        }
        return 0;
    }

 
    /**  
     * 计算t3-t2的平均时间差，精确到毫秒
     * 填充avg_t3_t2_subtract
     * @return
     */
    public int calculateAvgT3T2Subtract() {
        long sum = 0;
        for (int i = 0; i < CESHI_NUMBER; i++) {
            sum += t3_t2_long.get(i);
        }
        long avg = sum / CESHI_NUMBER;
        t3t2DiffAvgStr = Long.toString(avg / 1000) + ":" + Long.toString(avg % 1000);
//        System.out.println("avg_t3_t2" + avg_t3_t2_subtract);
        return 0;
    }
    
	/**  
	 * 将采集到的数据打印到logcat
	 */
	public void print() {
		
		Log.d(TAG, "t3_t2_subtract:");
		for (int i = 0; i < CESHI_NUMBER; i++) {
			Log.v(TAG, t3_t2_subtract.get(i));
		} 
		Log.d(TAG, "avg_t3_t2_subtract (s:ms):  " + t3t2DiffAvgStr);
	}
}
