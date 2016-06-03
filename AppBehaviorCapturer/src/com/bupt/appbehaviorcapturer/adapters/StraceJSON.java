package com.bupt.appbehaviorcapturer.adapters;

import org.json.JSONObject;

public class StraceJSON{
	public String number;//public String mNum;
	public String name;//public String mName;
	public String time;//public String mTime;
	public String FatherThreadIdofAPI;//public String mPTID;
	public String threadID;//public String mTID;
	public String processID;//public String mPID;
	public String context;//public String mPara;
	public String result;//public String mRes;

	public StraceJSON() {
		number = null;
		name = null;
		time = null;
		FatherThreadIdofAPI = null;
		threadID = null;
		processID = null;
		context = null;
		result = null;
	}

	public StraceJSON(String n, String na, String tim, String pti, String cti, String ti,
			String pi, String pa, String r) {
		number = n;
		name = na;
		time = tim;
		FatherThreadIdofAPI = pti;
		threadID = ti;
		processID = pi;
		context = pa;
		result = r;
	}
	public void reset(){
		number = "";
		name = "";
		time = "";
		FatherThreadIdofAPI = "";
		threadID = "";
		processID = "";
		context = "";
		result = "";
	}
	public void show(){
		System.out.println("*****mNum = " + number + "*****");
//		System.out.println("*****mName = " + name + "*****");
//		System.out.println("*****mTime = " + time + "*****");
//		System.out.println("*****mPTID = " + FatherThreadIdofAPI + "*****");
//		System.out.println("*****mTID = " + threadID + "*****");
//		System.out.println("*****mPID = " + processID + "*****");
//		System.out.println("*****mPara = " + context + "*****");
//		System.out.println("*****mRes = " + result + "*****");
	}
//	  public JSONObject toJSON() throws JSONException {
//	        JSONObject json = new JSONObject();
//	        json.put(JSON_ID, mId.toString());
//	        json.put(JSON_TITLE, mTitle);
//	        json.put(JSON_SOLVED, mSolved);
//	        json.put(JSON_DATE, mDate.getTime());
//	        return json;
//	    }
}
