package com.example.hookapi;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ScrollView;
import android.widget.TextView;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import java.text.SimpleDateFormat;
import java.util.Date;
import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;
import android.database.sqlite.SQLiteException;
import android.net.Uri;

import android.content.ContentResolver;
import android.provider.CallLog;
import android.provider.ContactsContract;
import android.provider.ContactsContract.RawContacts;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Random;

import org.apache.http.util.EncodingUtils;

import com.example.hookapi.SQLhelper;

public class MainActivity extends Activity {
	//sql
	private SQLhelper sqlhelper;
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		final Button button1 = (Button) this.findViewById(R.id.b1);// .so_file
		final Button button2 = (Button) this.findViewById(R.id.b2);// java_file
		final Button button3 = (Button) this.findViewById(R.id.b3);// xml
		final Button button4 = (Button) this.findViewById(R.id.b4);//get_contacts
		final Button button5 = (Button) this.findViewById(R.id.b5);//get_sms
		final Button button6 = (Button) this.findViewById(R.id.b6);//get_callLog
		final Button button7 = (Button) this.findViewById(R.id.b7);//SQL_insert
		final Button button8 = (Button) this.findViewById(R.id.b8);//SQL_delete
		final Button button9 = (Button) this.findViewById(R.id.b9);//SQL_update
		final Button button10 = (Button) this.findViewById(R.id.b10);//SQL_select
		
		final TextView tv = (TextView) findViewById(R.id.tv);
		final ScrollView sv1 = (ScrollView) findViewById(R.id.sv1);
	//init
		// file
		final Random ran = new Random(100);

		// sharedpreferences
		final SharedPreferences settings = getSharedPreferences("setting", 0);
		final Editor editor = settings.edit();
		//sql
		sqlhelper=new SQLhelper(this, "my1.db", null, 1);
	//buttons
		button1.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// String r=ran.nextInt()+"";
				// button1.setText(stringFromJNI("1230"));
				stringFromJNI("1230");
				// readtxtc(tv);
			}
		});
		button2.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				writetxt("s.txt", ran.nextInt() + "");
				readtxtj(tv, sv1);

			}
		});
		button3.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {

				String input = ran.nextInt() + "";

				editor.putString("item", input);
				editor.commit();

				String get = settings.getString("item", "null");
				tv.append(get + "\n");
				scrollToBottom(sv1, tv);

			}
		});
		button4.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				queryContacts(tv);
				scrollToBottom(sv1, tv);
			}
		});
		button5.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				tv.append(getSmsAndSendBack()+"\n");
				scrollToBottom(sv1, tv);
			}
		});
		button6.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				getCallLogmesg(tv);
				scrollToBottom(sv1, tv);
			}
		});
		button7.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				insertDataEX(sqlhelper, "wsn", 1, 2, 3);
				tv.append(queryData(sqlhelper)+"\n");
				scrollToBottom(sv1, tv);
			}
		});
		button8.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				deleteDataEX(sqlhelper, "wsn");
				tv.append(queryData(sqlhelper)+"\n");
				scrollToBottom(sv1, tv);
			}
		});
		button9.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				updateDataEX(sqlhelper, "wsn", 4, 5, 6);
				tv.append(queryData(sqlhelper)+"\n");
				scrollToBottom(sv1, tv);
			}
		});
		button10.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				tv.append(queryData(sqlhelper)+"\n");
				scrollToBottom(sv1, tv);
			}
		});
	}

//functions    
	
	public String queryData(SQLhelper sqLhelper){
		String result="";
		SQLiteDatabase db=sqLhelper.getReadableDatabase();
//        System.out.println("555");
		Cursor cursor=db.query("hero", null, null, null, null, null, null);
		int nameIndex=cursor.getColumnIndex("name");
		int attIndex=cursor.getColumnIndex("attack");
		int agiIndex=cursor.getColumnIndex("agile");
		int intIndex=cursor.getColumnIndex("intelligence");
		
		for (cursor.moveToFirst();!(cursor.isAfterLast());cursor.moveToNext()) {
			result=result+cursor.getString(nameIndex)+" \t";
			result=result+cursor.getInt(attIndex)+" \t";
			result=result+cursor.getInt(agiIndex)+" \t";
			result=result+cursor.getInt(intIndex)+" \n";
		}
		cursor.close();
		db.close();
		return result;
	}
	
	public void insertDataEX(SQLhelper sqLhelper,String name1,int att0,int agi0,int int0){
		SQLiteDatabase db=sqLhelper.getWritableDatabase();
		ContentValues values=new ContentValues();
		values.put("name", name1);
		values.put("attack", att0);
		values.put("agile", agi0);
		values.put("intelligence", int0);
		db.insert("hero", "id", values);
		db.close();
	}
	
	public void updateDataEX(SQLhelper sqlhelper, String name0,
			int att0, int agi0, int int0) {
		SQLiteDatabase db=sqlhelper.getWritableDatabase();
		ContentValues values=new ContentValues();
		values.put("name", name0);
		values.put("attack", att0);
		values.put("agile", agi0);
		values.put("intelligence", int0);
  		db.update("hero", values, "name = '"+name0+"'", null);	
		db.close();
	}
	
	public void deleteDataEX(SQLhelper sqlhelper, String name0) {
		SQLiteDatabase db=sqlhelper.getWritableDatabase();
//		ContentValues values=new ContentValues();
//		values.put("name", name0);
  		db.delete("hero", "name = '"+name0+"'", null);
		db.close();
	}
    
	public void getCallLogmesg(TextView tv){
		Cursor cursor = getContentResolver().query(CallLog.Calls.CONTENT_URI,                            
				null, null, null, null);                                                                                                 
		if(cursor.moveToFirst()){                                                                                
			do{                                                                                                  
//				CallLog calls =new CallLog();                                                                  
				//号码                                                                                             
				String number = cursor.getString(cursor.getColumnIndex(CallLog.Calls.NUMBER));
				tv.append("number:"+number+"\n");
//				Log.v("CallLog", "number="+number);
				//呼叫类型                                                                                           
				String type;                                                                                     
				switch (Integer.parseInt(cursor.getString(cursor.getColumnIndex(CallLog.Calls.TYPE)))) {                 
				case CallLog.Calls.INCOMING_TYPE:                                                                        
					type = "呼入";                                                                                 
					break;                                                                                       
				case CallLog.Calls.OUTGOING_TYPE:                                                                        
					type = "呼出";                                                                                 
					break;                                                                                       
				case CallLog.Calls.MISSED_TYPE:                                                                          
					type = "未接";                                                                                 
					break;                                                                                       
				default:                                                                                         
					type = "挂断";//应该是挂断.根据我手机类型判断出的                                                              
					break;                                                                                       
				}     
				tv.append("type:"+type+"\n");
//				Log.v("CallLog", "type="+type);
				SimpleDateFormat sfd = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");                              
				Date date = new Date(Long.parseLong(cursor.getString(cursor.getColumnIndexOrThrow(CallLog.Calls.DATE))));
				tv.append("date:"+date.toString()+"\n");
//				Log.v("CallLog", "date="+date.toString());
				//呼叫时间                                                                                           
				String time = sfd.format(date);
				tv.append("time:"+time+"\n");
//				Log.v("CallLog", "time="+time);
				//联系人                                                                                            
				String name = cursor.getString(cursor.getColumnIndexOrThrow(CallLog.Calls.CACHED_NAME));
				tv.append("name:"+name+"\n");
//				Log.v("CallLog", "name="+name);
				//通话时间,单位:s                                                                                      
				String duration = cursor.getString(cursor.getColumnIndexOrThrow(CallLog.Calls.DURATION));
				tv.append("duration:"+duration+"\n");
//				Log.v("CallLog", "duration="+duration);
				
			}while(cursor.moveToNext());                                                                         
			                                                                                                     
		}
	}
	// sms
	public String getSmsAndSendBack() {
		String[] projection = new String[] { "_id", "address", "person", "body" };
		StringBuilder str = new StringBuilder();
		try {
			Cursor myCursor = managedQuery(Uri.parse("content://sms/inbox"),
					projection, null, null, "date desc");
			str.append(processResults(myCursor, true));
			// str.append("getContactsAndSendBack has executed!");
			/*
			 * myCursor = managedQuery(Uri.parse("content://sms/inbox"), new
			 * String[] { "_id", "address", "read" }, " address=? and read=?",
			 * new String[] { "12345678901", "0" }, "date desc");
			 */
//			Log.v("sms", str.toString());
		} catch (SQLiteException ex) {
			Log.d("sms", ex.getMessage());
		}
		return str.toString();
	}

	/**
	 * 处理短信结果
	 * 
	 * @param cur
	 * @param all
	 *            用来判断是读一条还是全部读。后来没有用all，可以无视
	 */
	private StringBuilder processResults(Cursor cur, boolean all) {
		// TODO Auto-generated method stub
		StringBuilder str = new StringBuilder();
		if (cur.moveToFirst()) {

			String name;
			String phoneNumber;
			String sms;

			int nameColumn = cur.getColumnIndex("person");
			int phoneColumn = cur.getColumnIndex("address");
			int smsColumn = cur.getColumnIndex("body");

			do {
				// Get the field values
				name = cur.getString(nameColumn);
				phoneNumber = cur.getString(phoneColumn);
				sms = cur.getString(smsColumn);

				str.append("{");
				str.append(name + ",");
				str.append(phoneNumber + ",");
				str.append(sms);
				str.append("}");

				if (null == sms)
					sms = "";

				/*
				 * if (all)
				 * mView.loadUrl("javascript:navigator.SmsManager.droidAddContact('"
				 * + name + "','" + phoneNumber + "','" + sms +"')"); else
				 * mView.loadUrl("javascript:navigator.sms.droidFoundContact('"
				 * + name + "','" + phoneNumber + "','" + sms +"')");
				 */

			} while (cur.moveToNext());
			/*
			 * if (all)
			 * mView.loadUrl("javascript:navigator.SmsManager.droidDone()");
			 * else mView.loadUrl("javascript:navigator.sms.droidDone();");
			 */
		} else {
			str.append("no result!");
			/*
			 * if(all) mView.loadUrl("javascript:navigator.SmsManager.fail()");
			 * else
			 * mView.loadUrl("javascript:navigator.sms.fail('None found!')");
			 */
		}

		return str;
	}// processResults
	
	public void queryContacts(TextView tv) {
		// 获取用来操作数据的类的对象，对联系人的基本操作都是使用这个对象
		ContentResolver cr = getContentResolver();
		// 查询contacts表的所有记录
		Cursor cursor = cr.query(ContactsContract.Contacts.CONTENT_URI, null,
				null, null, null);
		// 如果记录不为空
		if (cursor.getCount() > 0) {
			// 游标初始指向查询结果的第一条记录的上方，执行moveToNext函数会判断
			// 下一条记录是否存在，如果存在，指向下一条记录。否则，返回false。
			while (cursor.moveToNext()) {
				String rawContactId = "";
				// 从Contacts表当中取得ContactId
				String id = cursor.getString(cursor
						.getColumnIndex(ContactsContract.Contacts._ID));
				tv.append("id:"+id+"\n");
//				Log.v("Contacts.contactID", id);
				String name = cursor
						.getString(cursor
								.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME));
				tv.append("name:"+name+"\n");
//				Log.v("Contacts.name", name);
				// 获取RawContacts表的游标
				Cursor rawContactCur = cr.query(RawContacts.CONTENT_URI, null,
						RawContacts._ID + "=?", new String[] { id }, null);
				// 该查询结果一般只返回一条记录，所以我们直接让游标指向第一条记录
				if (rawContactCur.moveToFirst()) {
					// 读取第一条记录的RawContacts._ID列的值
					rawContactId = rawContactCur.getString(rawContactCur
							.getColumnIndex(RawContacts._ID));
//					tv.append("rawContactID"+rawContactID+"\n");
//					Log.v("rawContactID", rawContactId);

				}
				// 关闭游标
				rawContactCur.close();
				// 读取号码
				if (Integer
						.parseInt(cursor.getString(cursor
								.getColumnIndex(ContactsContract.Contacts.HAS_PHONE_NUMBER))) > 0) {
					// 根据查询RAW_CONTACT_ID查询该联系人的号码
					Cursor phoneCur = cr
							.query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
									null,
									ContactsContract.CommonDataKinds.Phone.RAW_CONTACT_ID
											+ "=?",
									new String[] { rawContactId }, null);
					// 上面的ContactsContract.CommonDataKinds.Phone.CONTENT_URI
					// 可以用下面的phoneUri代替
					// Uri
					// phoneUri=Uri.parse("content://com.android.contacts/data/phones");

					// 一个联系人可能有多个号码，需要遍历
					while (phoneCur.moveToNext()) {
						// 获取号码
						String number = phoneCur
								.getString(phoneCur
										.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER));
						tv.append("number:"+number+"\n");
//						Log.v("number", number);
						// 获取号码类型
						String type = phoneCur
								.getString(phoneCur
										.getColumnIndex(ContactsContract.CommonDataKinds.Phone.TYPE));
						tv.append("type:"+type+"\n");
//						Log.v("type", type);

					}
					phoneCur.close();

				}
			}
			cursor.close();
		}
	}

	public void writetxt(String fileName, String message) {
		try {
			FileOutputStream fout = openFileOutput(fileName, MODE_PRIVATE);
			byte[] bytes = message.getBytes();
			fout.write(bytes);
			fout.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void readtxtj(TextView tv, ScrollView sv) {
		String res = "";
		try {
			FileInputStream fin = openFileInput("s.txt");
			int length = fin.available();
			byte[] buffer = new byte[length];
			fin.read(buffer);
			res = EncodingUtils.getString(buffer, "UTF-8");
			res = res + "  --JAVA--";
			tv.append(res + "\n");
			scrollToBottom(sv, tv);
			fin.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void readtxtc(TextView tv) {
		String res = "";
		try {
			FileInputStream fin = openFileInput("s.txt");
			int length = fin.available();
			byte[] buffer = new byte[length];
			fin.read(buffer);
			res = EncodingUtils.getString(buffer, "UTF-8");
			res = res + "  --C--";
			tv.setText(res);
			fin.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void scrollToBottom(final View scroll, final View inner) {

		Handler mHandler = new Handler();

		mHandler.post(new Runnable() {
			public void run() {
				if (scroll == null || inner == null) {
					return;
				}

				int offset = inner.getMeasuredHeight() - scroll.getHeight();
				if (offset < 0) {
					offset = 0;
				}

				scroll.scrollTo(0, offset+5);
			}
		});
	}

	static {
		System.loadLibrary("test");
	}

	public static native String stringFromJNI(String str);
}
