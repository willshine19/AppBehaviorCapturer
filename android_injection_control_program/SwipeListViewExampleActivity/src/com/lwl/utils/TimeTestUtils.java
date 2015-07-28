package com.lwl.utils;

public class TimeTestUtils {
    //设置数组的大小
    public static final int ARRAY_SIZE = 100;
    public static final int CESHI_NUMBER = 6;
    
    
    //将long数组转换为String
    public  String longAry2String(String aryName,long[] ary) {
        StringBuilder sb = new StringBuilder();
      //将数组名放到开头，用于标识
        sb.append(aryName);
        sb.append('\n');
        for (int i = 0; i < ary.length; i++) {
            sb.append(Long.toString(ary[i])).append(",");
            //一行输出10个数
            if((i+1)%10 == 0){
                sb.append('\n');
            }
        }
        sb.deleteCharAt(sb.length() - 1);
        return sb.toString();
    }
    
    //将string数组转换为String
    public  String StringAry2String(String aryName,String[] ary) {
        StringBuilder sb = new StringBuilder();
        //将数组名放到开头
        sb.append(aryName);
        sb.append('\n');
        for (int i = 0; i < ary.length; i++) {
            sb.append(ary[i]).append(",");
            //一行输出10个数
            if((i+1)%10 == 0){
                sb.append('\n');
            }
        }
        sb.deleteCharAt(sb.length() - 1);
        return sb.toString();
    }
}
