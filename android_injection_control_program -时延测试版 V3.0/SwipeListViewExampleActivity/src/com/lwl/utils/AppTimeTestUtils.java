package com.lwl.utils;

import org.json.JSONException;
import org.json.JSONObject;


public class AppTimeTestUtils extends TimeTestUtils{
    
    int receive_count = 0;
    // t1时间存储
    public String t1_start_handle_time[];
    // t2时间存储
    public String t2_end_handle_time[];
    
    //时间间隔存储
    public String t2_t1_subtract[];
    //平均时间间隔存储
    public String avg_t2_t1_subtract;
    //单例
    private static AppTimeTestUtils single = null;
    // 私有的默认构造，初始化数组与时间输出格式
    
    private AppTimeTestUtils() {
        t1_start_handle_time = new String[ARRAY_SIZE];
        t2_end_handle_time = new String[ARRAY_SIZE];
        t2_t1_subtract = new String[ARRAY_SIZE];
    }
    //单例，保证类只有一个，这样才能保证数据的准确度
    public static AppTimeTestUtils getInstance() {
        if (single == null) {
            single = new AppTimeTestUtils();
        }
        return single;
    }

    public int parseTimeFromJson(JSONObject json){
        //输出一切正常
        if(json == null){
            return -1;
        }

        try {
            if(receive_count == 1){
                avg_t2_t1_subtract = (String) json.get("avg_t2_t1");
            }
            t1_start_handle_time[receive_count] = (String) json.get("t1_time");
            t2_end_handle_time[receive_count] = (String) json.get("t2_time");
            t2_t1_subtract[receive_count] =  (String) json.get("t2_t1_subtract_time");
            
            receive_count ++;
            
        } catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
       /* try {
            // 解析t1数据，装载到数组
            String t1_time;
            t1_time = (String) json.get("t1_time");
            t1_start_handle_time = t1_time.split(";");
//            for (int i = 0; i < t1_start_handle_time.length; i++) {
//                System.out.println("t1_start_handle_time" + t1_start_handle_time[i]);
//            }
            // 解析t2数据，装载到数组
            String t2_time;
            t2_time = (String) json.get("t2_time");
            t2_end_handle_time = t2_time.split(";");
//            for (int i = 0; i < t2_end_handle_time.length; i++) {
//                System.out.println("t2_end_handle_time" + t2_end_handle_time[i]);
//            }
            // 解析t2-t1数组，装载到数组
            String t2_t1_time;
            t2_t1_time = (String) json.get("t2_t1_subtract_time");
            t2_t1_subtract = t2_t1_time.split(";");
//            for (int i = 0; i < t2_t1_subtract.length; i++) {
//                System.out.println("t2_t1_subtract" + t2_t1_subtract[i]);
//            }
            // 解析avg(t2-t1)
            avg_t2_t1_subtract = (String) json.get("avg_t2_t1");
//            System.out.println("avg_time_subtract" + avg_time_subtract);
        } catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
*/
        return 0;
    }
}
