package com.syh.pubjson;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.lwl.utils.ServerToHookerTimeTestUtils;

import android.content.Context;
import android.os.Environment;
import android.util.Log;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintStream;
import java.util.HashMap;

public class JsonSender {
	
	private static final String USER_ID = "GraphValueTest1";
	private static final String USER_CODE = "1234567890";
	private static final String PUB_SPACE_ID = "56518805f39693a4088fbfa6";
	private static final String PUB_THEME_ID = "56518931f39693a4088fbfa9";
	private static final String SUB_SPACE_ID = "5651c957f39693a4088fbfc4";
	private static final String SUB_THEME_ID = "5651c986f39693a4088fbfc5";
	private static final String TAG1 = "JsonSender";
	private static final String TAG2 = "Callback";
	
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
					Log.v(TAG2, "从server端收到一条消息，开始解析");
					// 将从服务器端接受到的时间，保存到mServerToHooker对象中
					JSONObject msg = (JSONObject) message;
					mServerToHooker.parseTimeFromJson(msg);
					mCount++;
					//设置t7时间
					mServerToHooker.setT7ReceiveTime();
					Log.v(TAG2, "value时间差：" + mServerToHooker.mValueCost.get(mCount - 1));
					Log.v(TAG2, "value时间差str：" + mServerToHooker.mValueCostStr.get(mCount - 1));
					Log.v(TAG2, "list时间差：" + mServerToHooker.mListCost.get(mCount - 1));
					Log.v(TAG2, "list时间差str：" + mServerToHooker.mListCostStr.get(mCount - 1));
					Log.i(TAG2, "[+] 成功从【服务器端】接收到第" + mCount + "组数据");
//						mScore = scoreData.getString("value");
//						Log.v(TAG2, "分数为：" + mScore);
				}
			});
			while (!mSuccessFlag) {
				Log.v(TAG1, "JsonSender等待longin成功的标志...");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			mSuccessFlag = false;
		Log.i(TAG1, "****结束login****");
	}
	
	
	/**
	 * pub一个JSON对象
	 * @param jo 即将被发送的JSON对象
	 */
	public void publish(JSONObject jo) {
//		Log.v(TAG1, "****开始publish****");
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
		Log.d("what's in json [No.2]", "" + nameofAPI + numberofAPI+ threadIDofAPI +timeofAPI +processID+IMEI);
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
//						Log.v(TAG2, "publish成功" );
						mSuccessFlag = true;
					};

					@Override
					public void errorCallback(Object message) {
						Log.e(TAG2, "publish失败: " + message);
					};
				});
		// 等待发送成功
		Log.v(TAG1, "进入while循环");
		while (!mSuccessFlag) {
			Log.v(TAG1, "JsonSender等待发送成功的标志...");
			try {
				Thread.sleep(5000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		Log.v(TAG1, "离开while循环");
		mSuccessFlag = false;
		Log.i(TAG1, "完成pubJSON数据");

//		try {
//			Thread.sleep(1000);// 等待服务器计算
//		} catch (InterruptedException e) {
//			e.printStackTrace();
//		}
//		Log.v(TAG1, "****结束publish****");
	}
	
	/**
	 * 订阅一个space空间的theme，以接受该theme中的信息
	 */
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
	
	/**  
	 * 发送第一条JSON数据，指定内容
	 * @param deviceId 设备识别码
	 */
	public void pubFirstData(String deviceId) {
		JSONObject firstData = new JSONObject();
        try {
			firstData.put("name", "start");// 待检测数据---对应r=0
			firstData.put("number", "0");
			firstData.put("threadID", "0");
			firstData.put("processID", "0");
			firstData.put("IMEI", deviceId);
			firstData.put("time", "0000-00-00 00:00:00:000:000");
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        Log.d("what's in json", "" + firstData);
        publish(firstData);
	}
	
	/**
	 * 将json对象转为字符串写到一个文本中，并将文件保存到sd卡中，即/storage/emulated/0/json.txt
	 * 需要申请权限<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE"/>
	 * 和<uses-permission android:name="android.permission.MOUNT_UNMOUNT_FILESYSTEMS"/>
	 * @throws FileNotFoundException 
	 * @Description:
	 */
	public void saveToFile(JSONObject jo) {
		FileOutputStream fos = null	;
		PrintStream ps = null;
		try {
			String fileName = getSDPath() + "/SyhJson.txt";
//			fos = context.openFileOutput(fileName, Context.MODE_APPEND);
			fos = new FileOutputStream(fileName, true);
			ps = new PrintStream(fos);
			ps.println(jo.toString());
			Log.d(TAG1, "成功保存到文件/storage/emulated/0/json.txt");
		} catch (IOException e) {
			// TODO: handle exception
			e.printStackTrace();
		} finally {
			try {
				if (ps != null) {
					ps.close();
				}
				if (fos != null) {
					fos.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * 获取SD卡的路径
	 * @Description:
	 * @return
	 */
	private String getSDPath() {
        File sdDir = null;
        boolean sdCardExist = Environment.getExternalStorageState().equals(
                android.os.Environment.MEDIA_MOUNTED); // 判断sd卡是否存在
        if (sdCardExist) {
            sdDir = Environment.getExternalStorageDirectory();// 获取跟目录
        }
        return sdDir.toString();
    }
}