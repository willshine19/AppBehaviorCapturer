package com.example.ratest;

import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import android.location.GpsSatellite;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.location.GpsStatus;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.provider.Contacts.People;
import android.telephony.SmsMessage;
import android.telephony.TelephonyManager;
import android.util.Log;

public class data {// 手机数据
    public static int count = 0;
    public static String FILE_NAME = "hello";

	public static void doContentResolver(Context context) {
		// 使用ContentResolver增删改查电话本信息http://coderlxl201209164551.iteye.com/blog/2069120
		insert("tester1", context);
//		update(context, "tester2", new String(People.NAME + "='tester1'"));
		delete(context, new String(People.NAME + "='tester2'"));
		select(context);
	}
    /* 
     * 向联系人列表中插入新的联系人 
     * @param name The value of People.NAME 
     */  
	public static void insert(String name, Context context) {
		ContentValues ct = new ContentValues();
		ct.put(People.NAME, name);
		context.getContentResolver().insert(People.CONTENT_URI, ct);
		Log.i("TEST APP", "[18] android.content.ContentResolver insert");
	}
    /* 
     * 更新手机中指定的联系人 
     * @param name A new name for People.NAME 
     * @param where The update requirement. 
     */ 
	public static void update(Context context, String name, String where) { 
		ContentValues ct = new ContentValues();
		ct.put(People.NAME, name);
		context.getContentResolver().update(People.CONTENT_URI, ct, where, null);
		Log.i("TEST APP", "[21] android.content.ContentResolver update");
	}
    /* 
     * 删除手机中指定的联系人 
     * @param where The delete requirement. 
     */ 
	public static void delete(Context context, String where) { 
		context.getContentResolver().delete(People.CONTENT_URI, where, null);
		Log.i("TEST APP", "[20] android.content.ContentResolver delete");
	}

	// 查找所有联系人
	public static void select(Context context) {
		Cursor cursor = context.getContentResolver().query(People.CONTENT_URI,
				new String[] { People._ID, People.NAME }, null, null, null);
		Log.i("TEST APP", "[19] android.content.ContentResolver query");
	}

	public static void doSmsMessage() {
		// http://blog.csdn.net/sxsj333/article/details/6622535，现在有短信来才可读取
		try {
			SmsMessage smsMessage[] = new SmsMessage[0];
			String sender = smsMessage[0].getOriginatingAddress();// 获取短信的发送者
			String content = smsMessage[0].getMessageBody();// 获取短信的内容
			Log.i("TEST APP", "[22] android.telephony.gsm.SmsMessage getMessageBody");
			Date date = new Date(smsMessage[0].getTimestampMillis());// 获取短信的接收时间
			SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			String sendtime = format.format(date);
			Log.v("SmsMessage", "SmsMessage is ok");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			Log.v("SmsMessage", "SmsMessage is wrong");
			e.printStackTrace();
		}

	}

	public static void doTelephonyManager(Context context) {// 单纯调用，不要返回值

		try {
			TelephonyManager tm = (TelephonyManager) context
					.getSystemService(Context.TELEPHONY_SERVICE);
			tm.getCallState();// 返回电话状态
			Log.i("TEST APP", "[23] android.telephony.TelephonyManager getCallState");
			tm.getDeviceId();// 返回当前移动终端的唯一标识
			Log.i("TEST APP", "[24] android.telephony.TelephonyManager getDeviceId");
			tm.getLine1Number();// 返回手机号码，对于GSM网络来说即MSISDN			
			Log.i("TEST APP", "[25] android.telephony.TelephonyManager getLine1Number");
			tm.getSimSerialNumber();// 返回SIM卡的序列号(IMEI)
			Log.i("TEST APP", "[26] android.telephony.TelephonyManager getSimSerialNumber");
			tm.getSubscriberId();// 返回用户唯一标识，比如GSM网络的IMSI编号
			Log.i("TEST APP", "[27] android.telephony.TelephonyManager getSubscriberId");

			Log.v("TelephonyManager", "TelephonyManager is ok");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			Log.v("TelephonyManager", "TelephonyManager is wrong");
			e.printStackTrace();
		}

	}

	public static void dolocationManager(Context context) {
		// http://blog.csdn.net/liuhe688/article/details/6573459
		final LocationManager locMgr = (LocationManager) context.getSystemService(Context.LOCATION_SERVICE);
		
		  //状态监听
	    GpsStatus.Listener listener = new GpsStatus.Listener() {
	        public void onGpsStatusChanged(int event) {
	            switch (event) {
	            //第一次定位
	            case GpsStatus.GPS_EVENT_FIRST_FIX:
	                Log.i("TEST APP", "第一次定位");
	                break;
	            //卫星状态改变
	            case GpsStatus.GPS_EVENT_SATELLITE_STATUS:
/*	                Log.i("TEST APP", "卫星状态改变");
	                //获取当前状态
	                GpsStatus gpsStatus=locMgr.getGpsStatus(null);
	                //获取卫星颗数的默认最大值
	                int maxSatellites = gpsStatus.getMaxSatellites();
	                //创建一个迭代器保存所有卫星 
	                Iterator<GpsSatellite> iters = gpsStatus.getSatellites().iterator();
	                int count = 0;     
	                while (iters.hasNext() && count <= maxSatellites) {     
	                    GpsSatellite s = iters.next();     
	                    count++;     
	                }   
	                System.out.println("搜索到："+count+"颗卫星");*/
	                break;
	            //定位启动
	            case GpsStatus.GPS_EVENT_STARTED:
	                Log.i("TEST APP", "定位启动");
	                break;
	            //定位结束
	            case GpsStatus.GPS_EVENT_STOPPED:
	                Log.i("TEST APP", "定位结束");
	                break;
	            }
	        };
	    };
	//绑定监听状态
	    Log.i("TEST APP", "[28] android.location.LocationManager addGpsStatusListener");
	    locMgr.addGpsStatusListener(listener);
		
		Location location = locMgr.getLastKnownLocation(LocationManager.GPS_PROVIDER);
		Log.i("TEST APP", "[29] android.location.LocationManager getLastKnownLocation");
		LocationListener locationListener = new LocationListener() { // http://blog.csdn.net/dier4836/article/details/7351116
			public void onLocationChanged(Location location) { 
				// 当坐标改变时触发此函数，如果Provider传进相同的坐标，它就不会被触发
				// log it when the location changes
				if (location != null) {
					Log.i("SuperMap",
							"Location changed : Lat: " + location.getLatitude()
									+ " Lng: " + location.getLongitude());
				}
			}

			public void onProviderDisabled(String provider) {
				// Provider被disable时触发此函数，比如GPS被关闭
			}

			public void onProviderEnabled(String provider) {
				// Provider被enable时触发此函数，比如GPS被打开
			}

			public void onStatusChanged(String provider, int status,
					Bundle extras) {
				// Provider的转态在可用、暂时不可用和无服务三个状态直接切换时触发此函数
			}
		};
		locMgr.requestLocationUpdates(LocationManager.GPS_PROVIDER, 5000, 5, locationListener);
		Log.i("TEST APP", "[30] android.location.LocationManager requestLocationUpdates");
		GpsStatus status = locMgr.getGpsStatus(null);// 具体使用http://lszdb1983.blog.163.com/blog/static/204263482012313962936/
		Log.v("locationManager", "locationManager is ok");
	}

	public static void doio(Context context) {
		File inFile = new File("/data/zds/my.txt");
//		File outFile = new File("/data/zds/newFace.txt");
// 创建流文件读入与写出类
		try {
		    byte[] temp = {1,2,3,4,5,6,7,8};
			FileInputStream inStream = new FileInputStream(inFile);
			FileOutputStream outStream = new FileOutputStream(inFile);
			FileDescriptor fd = null;
			// 通过available方法取得流的最大字符数
			try {
			    //add by lwl
                count++;
                FileOutputStream out;
                out = context.openFileOutput(FILE_NAME, context.MODE_PRIVATE);
                out.write(count);
                Log.i("param-test", "count is  " + count);
                out.flush();
                out.close();
                FileInputStream in = context.openFileInput(FILE_NAME);
                Log.i("param-test", "get string from file" + in.read());
                in.close();
                Log.i("TEST APP", "[35] java.io.FileOutputStream write");
                
				fd = inStream.getFD();
				Log.i("TEST APP", "[33] java.io.FileInputStream getFD");
//				outStream.write(temp); // 写出流,保存在文件newFace.gif中
//                Log.i("TEST APP", "[35] java.io.FileOutputStream write");
				byte[] inOutb = new byte[inStream.available()];
				inStream.read(); // 读入流,保存在byte数组
				Log.i("TEST APP", "[31] java.io.FileInputStream read");
				
				inStream.close();
				Log.i("TEST APP", "[32] java.io.FileInputStream close");
				outStream.close();
				Log.i("TEST APP", "[34] java.io.FileOutputStream close");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.v("io", "io is wrong");
		}
	}

	/*
	 * public static void doSmsMessage(Context
	 * context){//通过query查询短信内容http://blog
	 * .csdn.net/pi9nc/article/details/9320691 final String SMS_URI_ALL =
	 * "content://sms/"; final String SMS_URI_INBOX = "content://sms/inbox";
	 * final String SMS_URI_SEND = "content://sms/sent"; final String
	 * SMS_URI_DRAFT = "content://sms/draft"; final String SMS_URI_OUTBOX =
	 * "content://sms/outbox"; final String SMS_URI_FAILED =
	 * "content://sms/failed"; final String SMS_URI_QUEUED =
	 * "content://sms/queued";
	 * 
	 * StringBuilder smsBuilder = new StringBuilder();
	 * 
	 * try { Uri uri = Uri.parse(SMS_URI_ALL); String[] projection = new
	 * String[] { "_id", "address", "person", "body", "date", "type" }; Cursor
	 * cur = context.getContentResolver().query(uri, projection, null, null,
	 * "date desc"); // 获取手机内部短信
	 * 
	 * if (cur.moveToFirst()) { int index_Address =
	 * cur.getColumnIndex("address"); int index_Person =
	 * cur.getColumnIndex("person"); int index_Body =
	 * cur.getColumnIndex("body"); int index_Date = cur.getColumnIndex("date");
	 * int index_Type = cur.getColumnIndex("type");
	 * 
	 * do { String strAddress = cur.getString(index_Address); int intPerson =
	 * cur.getInt(index_Person); String strbody = cur.getString(index_Body);
	 * long longDate = cur.getLong(index_Date); int intType =
	 * cur.getInt(index_Type);
	 * 
	 * SimpleDateFormat dateFormat = new
	 * SimpleDateFormat("yyyy-MM-dd hh:mm:ss"); Date d = new Date(longDate);
	 * String strDate = dateFormat.format(d);
	 * 
	 * String strType = ""; if (intType == 1) { strType = "接收"; } else if
	 * (intType == 2) { strType = "发送"; } else { strType = "null"; }
	 * 
	 * smsBuilder.append("[ "); smsBuilder.append(strAddress + ", ");
	 * smsBuilder.append(intPerson + ", "); smsBuilder.append(strbody + ", ");
	 * smsBuilder.append(strDate + ", "); smsBuilder.append(strType);
	 * smsBuilder.append(" ]\n\n"); } while (cur.moveToNext());
	 * 
	 * if (!cur.isClosed()) { cur.close(); cur = null; } } else {
	 * smsBuilder.append("no result!"); } // end if
	 * 
	 * smsBuilder.append("getSmsInPhone has executed!");
	 * 
	 * } catch (SQLiteException ex) { Log.d("SQLiteException in getSmsInPhone",
	 * ex.getMessage()); }
	 * 
	 * // return smsBuilder.toString(); }
	 */

}
