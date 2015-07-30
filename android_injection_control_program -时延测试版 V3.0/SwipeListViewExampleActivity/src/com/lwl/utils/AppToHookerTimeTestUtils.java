package com.lwl.utils;


public class AppToHookerTimeTestUtils extends TimeTestUtils{
    
    //t3-t2时间存储,秒,毫秒
    public long t3_t2_long[];
    // t3-2时间存储(String)
    public String t3_t2_subtract[];
    //t3-t2平均值
    public String avg_t3_t2_subtract;
    
    //单例
    private static AppToHookerTimeTestUtils single = null;
    // 私有的默认构造，初始化数组与时间输出格式
    
    private AppToHookerTimeTestUtils() {
        t3_t2_long = new long[ARRAY_SIZE];
        t3_t2_subtract = new String[ARRAY_SIZE];
    }
    //单例，保证类只有一个，这样才能保证数据的准确度
    public static AppToHookerTimeTestUtils getInstance() {
        if (single == null) {
            single = new AppToHookerTimeTestUtils();
        }
        return single;
    }

    // 通过解析获得t3-t2的数值,填充数组
    public int setT3T2Subtract() {
        AppTimeTestUtils app = AppTimeTestUtils.getInstance();
        HookerTimeTestUtils hooker = HookerTimeTestUtils.getInstance();
        String[] t2_temp;
        String[] t3_temp;
        for (int i = 0; i < CESHI_NUMBER; i++) {

            // 从t2_end_handle_time数组的字符串中解析出秒，毫秒
            t2_temp = app.t2_end_handle_time[i].split(":");
            // for (int j = 0; j < t2_temp.length; j++) {
            // System.out.println(t2_temp[j]);
            // }
            long t2_long = Long.parseLong(t2_temp[2]) * 1000 + Long.parseLong(t2_temp[3]);

            // 从t3_receive_time数组中解析出秒，毫秒
            t3_temp = hooker.t3_receive_time[i].split(":");
            // for (int j = 0; j < t3_temp.length; j++) {
            // System.out.println(t3_temp[j]);
            // }
            long t3_long = Long.parseLong(t3_temp[2]) * 1000 + Long.parseLong(t3_temp[3]);
            // 计算网络时延(t3-t2)，装填至
            t3_t2_long[i] = t3_long - t2_long;
            // System.out.println("t3-t2-long " + t3_t2_long[i]);
            t3_t2_subtract[i] = Long.toString(t3_t2_long[i] / 1000) + ":"
                    + Long.toString(t3_t2_long[i] % 1000);
            // System.out.println(t3_t2__subtract[i]);
        }
        return 0;
    }

    // 计算t3-t2的平均时间差，精确到毫秒
    public int calculateAvgT3T2Subtract() {
        long sum = 0;
        for (int i = 0; i < CESHI_NUMBER; i++) {
            sum += t3_t2_long[i];
        }
        long avg = sum / CESHI_NUMBER;
        avg_t3_t2_subtract = Long.toString(avg / 1000) + ":" + Long.toString(avg % 1000);
//        System.out.println("avg_t3_t2" + avg_t3_t2_subtract);
        return 0;
    }
}
