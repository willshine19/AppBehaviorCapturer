package com.lwl.utils;

import android.annotation.SuppressLint;
import android.content.Context;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;


@SuppressLint("SimpleDateFormat")
public class HookerTimeTestUtils  extends TimeTestUtils{

    // 设置输出时间的格式 年-月-日 小时：分钟：秒：毫秒
    private SimpleDateFormat s;
    private FileOutputStream fo;
    private FileInputStream  fi;

    public int t3_count = 0;
    public int t4_count = 0;
    // t3时间存储
    public String t3_receive_time[];
    // t4时间存储
    public String t4_send_time[];
    // t3纳秒级时间存储
    public long t3_receive_long_format[];
    // t4纳秒级存储
    public long t4_send_long_format[];
    //时间间隔存储
    public String t4_t3_time_subtract[];
    // 纳秒时间 间隔
    public long time_subtract_long_format[];
    

    private static HookerTimeTestUtils single = null;

    // 私有的默认构造，初始化数组与时间输出格式
    private HookerTimeTestUtils() {
        t3_receive_time = new String[ARRAY_SIZE];
        t3_receive_long_format = new long[ARRAY_SIZE];
        t4_send_time = new String[ARRAY_SIZE];
        t4_send_long_format = new long[ARRAY_SIZE];
        t4_t3_time_subtract = new String[ARRAY_SIZE];
        time_subtract_long_format = new long[ARRAY_SIZE];
        s = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SS");
    }
    
    //单例，保证类只有一个，这样才能保证数据的准确度
    public static HookerTimeTestUtils getInstance() {
        if (single == null) {
            single = new HookerTimeTestUtils();
        }
        return single;
    }
    
    // 获取当前时间，并将时间存储到t3数组，返回时间的字符串
    //设置数组t3_receive_long_format，t3_receive_time
    public  String setT3ReceiveTime() {
        //获取当前时间（纳秒单位）,保存至long数组中
        t3_receive_long_format[t3_count] = System.nanoTime();
        //输出正常
//        System.out.println("[time test]" + t3_receive_long_format[t3_count]);
        // 格式化时间，返回字符串类型
        String temp = s.format(new Date());
        t3_receive_time[t3_count] = temp;
        System.out.println("[time test]" + temp);
        t3_count++;
        return temp;
    }
    
    // 获取当前时间，并将时间存储到t4数组，返回时间的字符串
    //设置数组t4_send_long_format，t4_send_time
    public  String setT4SendTime() {
        //获取当前时间（纳秒单位）,保存至long数组中
        //System.nanoTime()，此方法只能用于测量已过的时间，与系统或钟表时间的其他任何时间概念无关
        t4_send_long_format[t4_count] = System.nanoTime();
        //输出正常
//        System.out.println("[time test]" + t4_send_long_format[t4_count]);
        // 格式化时间，返回字符串类型
        String temp = s.format(new Date());
        t4_send_time[t4_count] = temp;
        System.out.println("[time test]" + temp);
        t4_count++;
        return temp;
    }
    
    //计算时间间隔，并保存至time_subtract数组
    //设置数组time_subtract，time_subtract_long_format
    public  int timeSubtract(long stop,long start){
        if(t3_count != t4_count){
            System.out.println("执行过程出错");
            return -1;
        }
        if(stop < start){
            System.out.println("计算时间间隔传参出错");
            return -1;
        }
        long subtract = stop - start;
        //将long类型时间差存入数组
        time_subtract_long_format[t4_count-1] = subtract;
        //设置时间差值的格式
        String temp = subtract/1000000000 + ":" + subtract%1000000000/1000000 + ":" + subtract%1000000/1000;
        //将String类型时间差值存入数组
        t4_t3_time_subtract[t4_count-1] = temp;
        return 0;
    }
    
    //将数组内容写入文件
    public int writeToFile(Context context,String filename){
        
        try {
            //写入前先清空文件的内容
            //此地方也可以不清空，写入几个换行符，然后记录测试的次数
            fo = context.openFileOutput(filename, Context.MODE_MULTI_PROCESS);
            fo.write("".getBytes());
            fo.flush();
            
            fo = context.openFileOutput(filename, Context.MODE_MULTI_PROCESS + Context.MODE_APPEND);
            //将long数组t3_receive_long_format转换为String，写入文件
            byte[] bytes1 = longAry2String("t3_receive_long_format",t3_receive_long_format).getBytes();
            fo.write(bytes1);
            fo.flush();
            //写入换行符用于区分
            fo.write('\n');
            fo.flush();
            //将String数组t3_receive_time转换为String格式，写入文件
            byte[] byte2 = StringAry2String("t3_receive_time",t3_receive_time).getBytes();
            fo.write(byte2);
            fo.flush();

            
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
    

}
