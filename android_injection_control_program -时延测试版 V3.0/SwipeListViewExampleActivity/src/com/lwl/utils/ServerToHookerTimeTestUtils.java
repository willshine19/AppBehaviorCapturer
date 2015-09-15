package com.lwl.utils;

import android.annotation.SuppressLint;
import android.util.Log;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

@SuppressLint("SimpleDateFormat")
public class ServerToHookerTimeTestUtils extends TimeTestUtils{
    
    int t7_count = 0;
    
    // 设置输出时间的格式 年-月-日 小时：分钟：秒：毫秒
    private SimpleDateFormat s;
    private HookerTimeTestUtils hooker = HookerTimeTestUtils.getInstance();
    
    //由server传过来的t5-t4'
    public ArrayList<Long> mListCost;
    public ArrayList<String> mListCostStr;
    public long mListCostAvg;
    
    //由server传过来的t6-t5
    public ArrayList<Long> mValueCost; // 单位毫秒
    public ArrayList<String> mValueCostStr;
    public long mValueCostAvg;
    
    //接受到server端测评结果的时间
    public ArrayList<Long> t7_receive_time_long;
    public ArrayList<String> t7_receive_time_str;
    
    //t7与t4的时间差，便于计算网络时延
    public ArrayList<Long> t7_t4_subtract_long;
    public ArrayList<String> t7_t4_subtract_str;
    public long avg_t7_t4_subtract;
    
    //网络时延计算，公式为((t7-t4)-(t5-t4')-(t6-t5))/2
    public ArrayList<Long> network_delay_long;
    public ArrayList<String> network_delay_str;
    
    //平均网络时延计算
    public long avg_network_delay_long;
    public String avg_network_delay_str;

    private static final String TAG = "TimeTest";
    
    // 单例模式
    private static ServerToHookerTimeTestUtils single = null;
    
    /**  
     * 私有构造函数  
     */ 
    private ServerToHookerTimeTestUtils() {
        mValueCost = new ArrayList<Long>();
        mValueCostStr = new ArrayList<String>();
        mListCost = new ArrayList<Long>();
        mListCostStr = new ArrayList<String>();
        
        t7_receive_time_long = new ArrayList<Long>();
        t7_receive_time_str = new ArrayList<String>();
        t7_t4_subtract_long = new ArrayList<Long>();
        t7_t4_subtract_str = new ArrayList<String>();
        network_delay_long = new ArrayList<Long>();
        network_delay_str = new ArrayList<String>();
        s = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SS");
    }
    
    /**  
     * 返回单例
     */
    public static ServerToHookerTimeTestUtils getInstance() {
        if (single ==  null) {
            single = new ServerToHookerTimeTestUtils();
        }
        return single;
    }
    
    
    /**  
     * 获取当前时间，并将时间存储到t7数组
     * 填充t7_receive_time_long数组，t7_receive_time_str数组
     * @return 时间的字符串
     */
    public  String setT7ReceiveTime() {
        //获取当前时间（纳秒单位）,保存至long数组中
        t7_receive_time_long.add(System.nanoTime());
        // 格式化时间，返回字符串类型
        String temp = s.format(new Date());
        t7_receive_time_str.add(temp);
        t7_count++;
        return temp;
    }
    
    /**  
     * 解析从server端发来的json字符串，
     * 填充mValueCost, mValueCostStr, mListCost, mListCostStr 数组
     * @param json 从jni层接受到的json字符串
     * @return
     */
    public void parseTimeFromJson(JSONObject json){

        JSONArray descriptions = json.optJSONArray("descriptions");
		JSONObject scoreData = (JSONObject) descriptions.opt(4);
		JSONObject valueCostData = (JSONObject) descriptions.opt(5);
		JSONObject listCostData = (JSONObject) descriptions.opt(6);
		long temp = Long.parseLong((String) valueCostData.opt("value"));
		mValueCost.add(temp);
		mValueCostStr.add(Long.toString(temp / 1000)
				+ ":" + Long.toString(temp % 1000));
		temp = Long.parseLong((String) listCostData.opt("value"));
		mListCost.add(temp);
		mListCostStr.add(Long.toString(temp / 1000)
				+ ":" + Long.toString(temp % 1000));
    }
    
    
	/**  
	 * 计算网络时延
	 * 填充t7_t4_subtract，network_delay_long，network_delay_str
	 * @return 0
	 */
	public int setNetworkDelay() {
		for (int i = 0; i < (CESHI_NUMBER - 2); i++) {
			// 纳秒精度
			long subtract = t7_receive_time_long.get(i)
					- hooker.t4_send_long_format.get(i + 2);
			// 将long类型时间差存入数组
			t7_t4_subtract_long.add(subtract);
			t7_t4_subtract_str.add(Long.toString(subtract / 1000000000)
					+ ":" + Long.toString(subtract % 1000000000));
			
			// 转换为毫秒精度，与server端传过来的精度保持一致
			long avg_t7_t4 = t7_t4_subtract_long.get(i) / 1000000;
			// 计算每一次的网路时延,并0保存至数组
			network_delay_long.add((avg_t7_t4 - mListCost.get(i) - mValueCost.get(i)) / 2);
//			System.out.println("network_delay_long[i]" + network_delay_long.get(i));
			
			// 转换为String
			network_delay_str.add(Long.toString(network_delay_long.get(i) / 1000)
					+ ":" + Long.toString(network_delay_long.get(i) % 1000));
//			System.out.println("network_delay_str[i]" + network_delay_str.get(i));
		}
		return 0;
	}
      
	
      /**  
     * 计算平均网络时延
     * 填充avg_network_delay_long，avg_network_delay_str
     * @return 0
     */
    public int calculateAVGNetworkDelay(){
          //计算各自的平均时间
          calculateAVGListCost();
          caculateAVGValueCost();
          calculateAVGT7T4Subtract();
         
          //计算平均时延
          avg_network_delay_long = (avg_t7_t4_subtract/1000000 - mListCostAvg - mValueCostAvg)/2;
          System.out.println("avg_network_delay_long" + avg_network_delay_long);
          
          //将平均时延保存至string
          avg_network_delay_str = Long.toString(avg_network_delay_long / 1000) + ":"
                  + Long.toString(avg_network_delay_long % 1000);
          return 0;
      }
    
	/**
	 * 计算t5-t4'的平均cost 填充mListCostAvg
	 * @return 0
	 */
	private int calculateAVGListCost() {
		long sum = 0;
		for (int i = 0; i < (CESHI_NUMBER - 2); i++) {
			sum += mListCost.get(i);
		}
		mListCostAvg = sum / (CESHI_NUMBER - 2);
		return 0;
	}

	/**
	 * 计算t6-t5的平均cost 填充mValueCostAvg
	 * @return 0
	 */
	private int caculateAVGValueCost() {
		long sum = 0;
		for (int i = 0; i < (CESHI_NUMBER - 2); i++) {
			sum += mValueCost.get(i);
		}
		mValueCostAvg = sum / (CESHI_NUMBER - 2);
		return 0;
	}

	/**
	 * 计算t7-t4的平均时延 填充avg_t7_t4_subtract
	 * @return
	 */
	private int calculateAVGT7T4Subtract() {
		long sum = 0;
		for (int i = 0; i < (CESHI_NUMBER - 2); i++) {
			sum += t7_t4_subtract_long.get(i);
		}
		avg_t7_t4_subtract = sum / (CESHI_NUMBER - 2);
		return 0;
	}
	
	/**  
	 * 将采集到的数据打印到logcat
	 */
	public void print() {
		
		Log.d(TAG, "mListCostStr: ");
		for (int i = 0; i < mListCostStr.size(); i++) {
			Log.v(TAG, mListCostStr.get(i));
		}
		Log.d(TAG, "mListCostAvg: " + mListCostAvg);
		
		Log.d(TAG, "mValueCostStr:");
		for (int i = 0; i < mValueCostStr.size(); i++) {
			Log.v(TAG, mValueCostStr.get(i));
		} 
		
		Log.d(TAG, "t7_receive_time_str:");
		for (int i = 0; i < t7_receive_time_str.size(); i++) {
			Log.v(TAG, t7_receive_time_str.get(i));
		} 
		
		Log.d(TAG, "t7_t4_subtract_str:");
		for (int i = 0; i < t7_t4_subtract_str.size(); i++) {
			Log.v(TAG, t7_t4_subtract_str.get(i));
		} 
		Log.d(TAG, "network_delay_str:");
		for (int i = 0; i < network_delay_str.size(); i++) {
			Log.v(TAG, network_delay_str.get(i));
		} 
		Log.d(TAG, "avg_network_delay_str: " + avg_network_delay_str);
	}
	
}
    