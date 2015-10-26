package com.lwl.utils;

import android.annotation.SuppressLint;
import java.text.SimpleDateFormat;
import java.util.Date;

@SuppressLint("SimpleDateFormat")
public class ServerToHookerTimeTestUtils extends TimeTestUtils{
    
    int t7_count = 0;
    
    // 设置输出时间的格式 年-月-日 小时：分钟：秒：毫秒
    private SimpleDateFormat s;
    private HookerTimeTestUtils hooker = HookerTimeTestUtils.getInstance();
    
    ////由server传过来的t5-t4'
    public long[] mListCost;
    public String[] mListCostStr;
    public long mListCostAvg;
    
    //由server传过来的t6-t5
    public long[] mValueCost; // 单位毫秒
    public String[] mValueCostStr;
    public long mValueCostAvg;
    
    //接受到server端测评结果的时间
    public long[] t7_receive_time_long;
    public String[] t7_receive_time_str;
    
    //t7与t4的时间差，便于计算网络时延
    public long[] t7_t4_subtract;
    public long avg_t7_t4_subtract;
    
    //网络时延计算，公式为((t7-t4)-(t5-t4')-(t6-t5))/2
    public long[] network_delay_long;
    public String[] network_delay_str;
    
    //平均网络时延计算
    public long avg_network_delay_long;
    public String avg_network_delay_str;

    // 单例模式
    private static ServerToHookerTimeTestUtils single = null;
    
    // 私有构造器
    private ServerToHookerTimeTestUtils() {
        mValueCost = new long[ARRAY_SIZE];
        mValueCostStr = new String[ARRAY_SIZE];
        mListCost = new long[ARRAY_SIZE];
        mListCostStr = new String[ARRAY_SIZE];
        
        t7_receive_time_long = new long[ARRAY_SIZE];
        t7_receive_time_str = new String[ARRAY_SIZE];
        t7_t4_subtract = new long[ARRAY_SIZE];
        network_delay_long = new long[ARRAY_SIZE];
        network_delay_str = new String[ARRAY_SIZE];
        s = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SS");
    }
    
    public static ServerToHookerTimeTestUtils getInstance() {
        if (single ==  null) {
            single = new ServerToHookerTimeTestUtils();
        }
        return single;
    }
    // 获取当前时间，并将时间存储到t3数组，返回时间的字符串
    //设置数组t3_receive_long_format，t3_receive_time
    public  String setT7ReceiveTime() {
        //获取当前时间（纳秒单位）,保存至long数组中
        t7_receive_time_long[t7_count] = System.nanoTime();
        //输出正常
        System.out.println("[time test] t7_receive_time_long[t7_count]" + t7_receive_time_long[t7_count]);
        // 格式化时间，返回字符串类型
        String temp = s.format(new Date());
        t7_receive_time_str[t7_count] = temp;
        System.out.println("[time test] t7_receive_time_str" + temp);
        t7_count++;
        return temp;
    }
    
    //计算网络时延，并保存
      public int setNetworkDelay(){
          
          for(int i=0;i<(CESHI_NUMBER-1);i++){
              //纳秒精度
              long subtract = t7_receive_time_long[i] - hooker.t4_send_long_format[i+1];
              //将long类型时间差存入数组
              t7_t4_subtract[i] = subtract;
              System.out.println("t7_t4_subtract[i]"+t7_t4_subtract[i]);
              //转换为毫秒精度，与server端传过来的精度保持一致
              long avg_t7_t4 = t7_t4_subtract[i] /1000000;
              //计算每一次的网路时延,并保存至数组
              network_delay_long[i] = (avg_t7_t4 - mListCost[i] - mValueCost[i])/2;
              System.out.println("network_delay_long[i]" + network_delay_long[i]);
              //转换为String
              network_delay_str[i] = Long.toString(network_delay_long[i] / 1000) + ":"
                      + Long.toString(network_delay_long[i] % 1000);
               System.out.println("network_delay_str[i]" + network_delay_str[i]);
              
          }
          return 0;
      }
      
      //计算平均网络时延
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
      //计算t5-t4'的平均cost
      private int calculateAVGListCost(){
          long sum = 0;
          for(int i=0;i<(CESHI_NUMBER-1);i++){
              sum+= mListCost[i];
          }
          mListCostAvg = sum / (CESHI_NUMBER-1);
          return 0;
      }
      //计算t6-t5的平均cost
      private int caculateAVGValueCost(){
          long sum = 0;
          for(int i=0;i<(CESHI_NUMBER-1);i++){
              sum+= mValueCost[i];
          }
          mValueCostAvg = sum / (CESHI_NUMBER-1);
          return 0;
      }
      //计算t7-t4的平均时延
      private int calculateAVGT7T4Subtract(){
          long sum = 0;
          for(int i=0;i<(CESHI_NUMBER-1);i++){
              sum+= t7_t4_subtract[i];
          }
          avg_t7_t4_subtract = sum / (CESHI_NUMBER-1);
          return 0;
      }

    
}
    