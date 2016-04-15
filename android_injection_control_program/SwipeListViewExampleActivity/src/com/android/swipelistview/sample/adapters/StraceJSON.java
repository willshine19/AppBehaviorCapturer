package com.android.swipelistview.sample.adapters;

import org.json.JSONObject;

public class StraceJSON {
	public String mNum;
	public String mName;
	public String mTime;
	public String mPTID;
	public String mTID;
	public String mPID;
	public String mPara;
	public String mRes;

	public StraceJSON() {
		mNum = null;
		mName = null;
		mTime = null;
		mPTID = null;
		mTID = null;
		mPID = null;
		mPara = null;
		mRes = null;
	}

	public StraceJSON(String n, String na, String tim, String pti, String cti, String ti,
			String pi, String pa, String r) {
		mNum = n;
		mName = na;
		mTime = tim;
		mPTID = pti;
		mTID = ti;
		mPID = pi;
		mPara = pa;
		mRes = r;
	}
	public void reset(){
		mNum = "";
		mName = "";
		mTime = "";
		mPTID = "";
		mTID = "";
		mPID = "";
		mPara = "";
		mRes = "";
	}
	public void show(){
		System.out.println("*****mNum = " + mNum + "*****");
		System.out.println("*****mName = " + mName + "*****");
		System.out.println("*****mTime = " + mTime + "*****");
		System.out.println("*****mPTID = " + mPTID + "*****");
		System.out.println("*****mTID = " + mTID + "*****");
		System.out.println("*****mPID = " + mPID + "*****");
		System.out.println("*****mPara = " + mPara + "*****");
		System.out.println("*****mRes = " + mRes + "*****");
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
