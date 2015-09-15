package com.lwl.utils;

import java.util.ArrayList;

public class TimeTestUtils {
    //设置数组的大小
    public static final int ARRAY_SIZE = 100;
    public static final int CESHI_NUMBER = 6;
    
    /**  
     * 将long数组转换为String
     * @param aryName 数组名
     * @param ary long型数组
     */
	public static String longAry2String(String aryName, ArrayList<Long> ary) {
		StringBuilder sb = new StringBuilder();
		// 将数组名放到开头，用于标识
		sb.append(aryName);
		sb.append('\n');
		for (int i = 0; i < CESHI_NUMBER; i++) {
			sb.append(Long.toString(ary.get(i))).append(",");
			// 一行输出10个数
			if ((i + 1) % 10 == 0) {
				sb.append('\n');
			}
		}
		sb.deleteCharAt(sb.length() - 1);
		return sb.toString();
	}

    /**  
     * 将string数组转换为String，用数组名来区分不同的数据
     * @param aryName 数组名
     * @param ary String型数组
     */
    public static  String stringAry2String(String aryName,ArrayList<String> ary) {
        StringBuilder sb = new StringBuilder();
        //将数组名放到开头
        sb.append(aryName);
        sb.append('\n');
        for (int i = 0; i < CESHI_NUMBER; i++) {
            sb.append(ary.get(i)).append(",");
            //一行输出10个数
			if ((i + 1) % 10 == 0) {
				sb.append('\n');
			}
        }
        //把最后一个,删除
        sb.deleteCharAt(sb.length() - 1);
        return sb.toString();
    }
 
    /**  
     * 将两个String连接在一起，用\n隔开，主要用于输出时间间隔的平均值，用于区分数据
     * @param name
     * @param data
     * @return
     */
    public static String string2String(String name,String data){
        StringBuilder sb = new StringBuilder();
        //将数组名放到开头
        sb.append(name);
        sb.append('\n');
        sb.append(data);
//        sb.deleteCharAt(sb.length() - 1);
        return sb.toString();
    }
}
