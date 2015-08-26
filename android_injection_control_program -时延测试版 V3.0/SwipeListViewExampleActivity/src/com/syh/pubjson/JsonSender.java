package com.syh.pubjson;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.lwl.utils.ServerToHookerTimeTestUtils;

import android.util.Log;
import java.util.HashMap;

public class JsonSender {
	
	private final String USER_ID = "55a3682dfd4d877911da1658";
	private final String USER_CODE = "1234567890";
	private final String PUB_SPACE_ID = "55d3e0c7fbab7cd126c37163";
	private final String PUB_THEME_ID = "55d3e11afbab7cd126c37164";
	private final String SUB_SPACE_ID = "55d3e156fbab7cd126c37165";
	private final String SUB_THEME_ID = "55d3e1d5fbab7cd126c37166";
	private final String TAG1 = "JsonSender";
	private final String TAG2 = "Callback";
	
	private String mScore = null;
	private MimoNodeAPI mMimoNode = null;
	private boolean mSuccessFlag = false; //成功发送标志位
	private ServerToHookerTimeTestUtils mServerToHooker; //保存从服务器收到的时间差的对象
	private int mCount = 0;
	
	public JsonSender() {
		mMimoNode = new MimoNodeAPI();
		mServerToHooker = ServerToHookerTimeTestUtils.getInstance();
	}
	
	/**
	 * 登陆
	 */
	public void login() {
		Log.i(TAG1, "****开始login****");
			mMimoNode.login(USER_ID, USER_CODE, new Callback() {
				@Override
				public void successCallback(Object message) {
					Log.v(TAG2, "成功login服务器: " + message);
					mSuccessFlag = true;
				}

				@Override
				public void errorCallback(Object message) {
					Log.e(TAG2, "authFailed: " + message);
				}

				@Override
				public void connectCallback() {
					Log.v(TAG2, "建立链接");
				}

				@Override
				public void disconnectCallback() {
					Log.v(TAG2, "断开链接");
				}

				@Override
				public void socketErrorCallback(Object error) {
					Log.e(TAG2, "socketError: " + error);
				}

				@Override
				public void newMessageCallback(Object message) {
					Log.v(TAG2, "newMessage: " + message);
					// 下载并解析json
					try {
						JSONObject msg = (JSONObject) message;
						JSONArray descriptions = msg
								.optJSONArray("descriptions");
						JSONObject scoreData = (JSONObject) descriptions.opt(4);
						JSONObject valueCostData = (JSONObject) descriptions.opt(5);
						JSONObject listCostData = (JSONObject) descriptions.opt(6);
						if (mCount < mServerToHooker.ARRAY_SIZE) {
							mServerToHooker.mValueCost[mCount] = Long.parseLong((String) valueCostData.opt("value"));
							mServerToHooker.mValueCostStr[mCount] = Long.toString(mServerToHooker.mValueCost[mCount] / 1000)
									+ ":" + Long.toString(mServerToHooker.mValueCost[mCount] % 1000);
							mServerToHooker.mListCost[mCount] = Long.parseLong((String) listCostData.opt("value"));
							mServerToHooker.mListCostStr[mCount] = Long.toString(mServerToHooker.mListCost[mCount] / 1000)
									+ ":" + Long.toString(mServerToHooker.mListCost[mCount] % 1000);
							mCount++;
							//设置t7时间
							mServerToHooker.setT7ReceiveTime();
                            Log.i(TAG2, "【+】从服务器端接收到时间差，数组中已有" + mCount + "个数据");
                            Log.i(TAG2, "value时间差：" + mServerToHooker.mValueCost[mCount - 1]);
                            Log.i(TAG2, "value时间差str：" + mServerToHooker.mValueCostStr[mCount - 1]);
                            Log.i(TAG2, "list时间差：" + mServerToHooker.mListCost[mCount - 1]);
                            Log.i(TAG2, "list时间差str：" + mServerToHooker.mListCostStr[mCount - 1]);
						}
						mScore = scoreData.getString("value");
						Log.v(TAG2, "分数为：" + mScore);
					} catch (JSONException e) {
						e.printStackTrace();
					}
				}
			});
			while (!mSuccessFlag) {}
			mSuccessFlag = false;
		Log.i(TAG1, "****结束login****");
	}
	
	
	/**
	 * pub一个JSON对象
	 * @param jo 即将被发送的JSON对象
	 */
	public void publish(JSONObject jo) {
		Log.i(TAG1, "****开始publish****");
		String nameofAPI = null;
		String numberofAPI = null;
		String threadIDofAPI = null;
		String timeofAPI = null;
		String processID = null;
		String IMEI = null;

		try {
			nameofAPI = jo.getString("name");
			numberofAPI = jo.getString("number");
			threadIDofAPI = jo.getString("threadID");
			timeofAPI = jo.getString("time");
			processID = jo.getString("processID");
			IMEI = jo.getString("IMEI");
		} catch (JSONException e) {
			e.printStackTrace();
		}
		// 上传json
		Log.i(TAG1, "正在pubJSON数据");
		mMimoNode.publishOnTheme(USER_ID,
				PUB_SPACE_ID, PUB_THEME_ID, "4", "string",
				"Sent!zdszdzsdzsdzsdzs", 
				"Name", nameofAPI,
				"Number", numberofAPI, 
				"threadID", threadIDofAPI,
				"time", timeofAPI, 
				"score", "score",
				"processID", processID,
				"IMEI", IMEI,
				new Callback() {
					@Override
					public void successCallback(Object message) {
						Log.i(TAG2, "publish成功: " + message);
						mSuccessFlag = true;
					};

					@Override
					public void errorCallback(Object message) {
						Log.e(TAG2, "publish失败: " + message);
					};
				});
		// 等待发送成功
		Log.v(TAG1, "进入while循环");
		while (!mSuccessFlag) {}
		Log.v(TAG1, "离开while循环");
		mSuccessFlag = false;
		Log.i(TAG1, "完成pubJSON数据");

		try {
			Thread.sleep(1000);// 等待服务器计算
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		Log.i(TAG1, "****结束publish****");
	}
	
	// sub
	public void subscribe() {
		Log.i(TAG1, "****开始subscribe****");
		mMimoNode.subscribeOnTheme(USER_ID,
				SUB_SPACE_ID, SUB_THEME_ID,
				"0", "0", "0", "1", "1", "1", "2", "2", "2",
				new Callback() {
			@Override
			public void successCallback(Object message) {
				Log.v(TAG2, "subscribe成功: "+ message);
				
			};
			@Override
			public void errorCallback(Object message) {
				Log.e(TAG2, "subscribe失败: "+ message);
			};
		});
		Log.i(TAG1, "****结束subscribe****");
	}

	/**
	 * 断开链接
	 */
	public void logout() {
		mScore = null;
		mMimoNode.logout();
	}
	
	public String getScore() {
		return mScore;
	}
}
