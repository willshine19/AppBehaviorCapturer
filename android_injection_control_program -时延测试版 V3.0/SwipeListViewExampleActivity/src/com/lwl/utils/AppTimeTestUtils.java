package com.lwl.utils;

import java.util.ArrayList;

import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;


/**  
 *   对应App中的时延测试（jni层），内部存放t1,t2,t2-t1以及t2-t1的平均值
 */  
public class AppTimeTestUtils extends TimeTestUtils{
    
    int receive_count = 0;
    // t1时间存储
    public ArrayList<String> t1_start_handle_time;
    // t2时间存储
    public ArrayList<String> t2_end_handle_time;
    
    //时间间隔存储
    public ArrayList<String> t2_t1_subtract;
    //平均时间间隔存储
    public String avg_t2_t1_subtract;
    
    private static final String TAG = "TimeTest";
    //单例
    private static AppTimeTestUtils single = null;
    
    /**  
     * 私有的默认构造，初始化数组与时间输出格式
     */ 
    private AppTimeTestUtils() {
        t1_start_handle_time = new ArrayList<String>();
        t2_end_handle_time = new ArrayList<String>();
        t2_t1_subtract = new ArrayList<String>();
    }
  
    /**  
     * 返回单例，确保实例只有一个，这样才能保证数据的准确度
     */
    public static AppTimeTestUtils getInstance() {
        if (single == null) {
            single = new AppTimeTestUtils();
        }
        return single;
    }

    
    /**  
     * 解析从jni层发来的json字符串，
     * 填充t1_start_handle_time, t2_end_handle_time, t2_t1_subtracts 数组
     * @param json 从jni层接受到的json字符串
     * @return
     */
    public void parseTimeFromJson(JSONObject json){

        try {
			if (receive_count == 1) {
                avg_t2_t1_subtract = (String) json.get("avg_t2_t1");
            }
            t1_start_handle_time.add((String) json.get("t1_time"));
            t2_end_handle_time.add((String) json.get("t2_time"));
            t2_t1_subtract.add((String) json.get("t2_t1_subtract_time"));
            
            receive_count ++;
            
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
    
    /**  
	 * 将采集到的数据打印到logcat
	 */
	public void print() {
		
		Log.d(TAG, "t1_start_handle_time: ");
		for (int i = 0; i < t1_start_handle_time.size(); i++) {
			Log.v(TAG, t1_start_handle_time.get(i));
		}
		
		Log.d(TAG, "t2_end_handle_time:");
		for (int i = 0; i < t2_end_handle_time.size(); i++) {
			Log.v(TAG, t2_end_handle_time.get(i));
		} 
		
		Log.d(TAG, "t2_t1_subtract:");
		for (int i = 0; i < t2_t1_subtract.size(); i++) {
			Log.v(TAG, t2_t1_subtract.get(i));
		} 
		Log.d(TAG, "avg_t2_t1_subtract: " + avg_t2_t1_subtract);
	}
}
