package com.syh.pubjson;

import java.util.HashMap;

public class JSONAdapter {

	private static HashMap<Long, Integer> mMap = new HashMap<Long, Integer>();
	private static int mThreadNumber = 0;

	public JSONAdapter() {
		// TODO Auto-generated constructor stub
	}
	
	/**
	 * 静态方法，返回一个字符串，表示int类型的线程编号，
	 * 从0 开始，因为第一条json是start，要求线程编号为0
	 * 
	 * @param threadID 表示一个long类型的线程号
	 */
	public static String convertThreadID(String threadID) {
		// 将threadIDofAPI改成1234...
		long tempThreadID = Long.parseLong(threadID);
		if (!mMap.containsKey(tempThreadID)) {
			mMap.put(tempThreadID, mThreadNumber++);
		}
		return mMap.get(tempThreadID).toString();
	}

}
