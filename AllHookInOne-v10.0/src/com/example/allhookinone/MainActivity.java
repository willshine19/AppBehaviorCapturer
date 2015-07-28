package com.example.allhookinone;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Method;
import android.support.v7.app.ActionBarActivity;
import android.telephony.TelephonyManager;
import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.location.Location;
import android.location.LocationManager;
import android.net.Uri;
import android.net.wifi.WifiManager;
import com.android.internal.telephony.ITelephony;
import android.os.Bundle;
import android.os.IBinder;
import android.provider.Contacts.People;
import android.provider.ContactsContract.CommonDataKinds.Phone;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

@SuppressWarnings("deprecation")
public class MainActivity extends ActionBarActivity {
    
    private String TAG = "Java Hook";
    public static WifiManager wifi ;
    public static LocationManager location;
    public static TelephonyManager telephony;
    public static ITelephony telephone;
    private int THREAD_NUM = 1;
    private int count = 0;
    private String FILE_NAME = "hello";
    private Context mContext;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);
		Log.i(TAG,"完成wifiManager初始化");
		location = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
		Log.i(TAG,"完成locationManager初始化");
		telephony = (TelephonyManager)getSystemService(Context.TELEPHONY_SERVICE);
		Log.i(TAG,"完成telephonyManager初始化");
		this.mContext = this.getApplicationContext();
		
        try
        {
            //利用java反射机制 
            //获取隐藏类android.os.ServiceManager的getService方法
            Method method = Class.forName("android.os.ServiceManager")
                .getMethod("getService", String.class);
            // 获取远程phone服务的IBinder对象的代理
            IBinder binder = (IBinder) method.invoke(null,new Object[] { "phone" });
            // 将IBinder对象的代理转换为ITelephony对象
            telephone = ITelephony.Stub.asInterface(binder);
            // 拨打电话
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

		final Button btn1 = (Button) this.findViewById(R.id.button1);
		btn1.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				
			Runner [] r = new Runner[THREAD_NUM];
			for(int i =0;i<THREAD_NUM;i++){
				r[i] = new Runner();
				r[i].setNum(i+1);
			}
			Thread[] t = new Thread[THREAD_NUM];
			for (int i =0;i<THREAD_NUM;i++){
				t[i]= new Thread(r[i]);
				t[i].start();
			}
			}
		});
		
		final Button call1 = (Button)this.findViewById(R.id.param);
		call1.setOnClickListener(new OnClickListener() {
            
            @Override
            public void onClick(View v) {
                //test 1
//                for(int i=0;i<170;i++){
                for(int i=0;i<1;i++){
                    Log.d(TAG,"*************test 1****************");
                    try {
                        count++;
                        FileOutputStream out = openFileOutput(FILE_NAME,MODE_PRIVATE);
                        out.write(count);
                        Log.i("param-test","count is  "+count);
                        out.flush();
                        out.close();
                        FileInputStream in = openFileInput(FILE_NAME);
                        Log.i("param-test","get string from file" + in.read());
                        in.close();
                    } catch (FileNotFoundException e1) {
                        // TODO Auto-generated catch block
                        e1.printStackTrace();
                    } catch (IOException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }
                    //test 2
                    Log.d(TAG,"*************test 2****************");
                    Location location = MainActivity.location.getLastKnownLocation(LocationManager.GPS_PROVIDER);
                    if(location != null){
                        Log.i("Thread", location.toString());
                    }
                    Log.i("param-test","getLastKnownLcoation failed");
                    //test 3
                    Log.d(TAG,"*************test 3****************");
                    insertContacts();
                    //test 4
                    Log.d(TAG,"*************test 4****************");
                    getContacts();
                    //test 5
                    Log.d(TAG,"**************test 5****************");
                    deleteContacts();
                }
                
            }
        });
		
		final Button call2 = (Button)this.findViewById(R.id.Call9802);
        call2.setOnClickListener(new OnClickListener() {
            
            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                try
                {
                    Log.d("Call","begin call 9802");
                    telephone.call("13120329802");
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        });
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	private void getContacts() {
        ContentResolver resolver = mContext.getContentResolver();
        Cursor phoneCursor = resolver.query(Phone.CONTENT_URI, null, null, null, null);
        if (phoneCursor != null) {
            while (phoneCursor.moveToNext()) {
                int nameIndex = phoneCursor.getColumnIndex(Phone.DISPLAY_NAME); // 获取联系人name
                String name = phoneCursor.getString(nameIndex);
                String phoneNumber = phoneCursor.getString(phoneCursor.getColumnIndex(Phone.NUMBER)); // 获取联系人number
                Log.d(TAG, "phoneNumber = "+phoneNumber+", name = "+name);
            }
            phoneCursor.close();
        }
    }
    private void insertContacts(){        
        Uri uri = Uri.parse("content://com.android.contacts/raw_contacts");
        Log.d(TAG,uri.toString());
        ContentResolver resolver = mContext.getContentResolver();  
        ContentValues values = new ContentValues();  
        long contactId = ContentUris.parseId(resolver.insert(uri, values));  
        /* 往 data 中添加数据（要根据前面获取的id号） */  
        // 添加姓名  
        uri = Uri.parse("content://com.android.contacts/data");  
        values.put("raw_contact_id", contactId);  
        values.put("mimetype", "vnd.android.cursor.item/name");  
        values.put("data2", "周国平");  
        resolver.insert(uri, values); 
        // 添加电话  
        values.clear();  
        values.put("raw_contact_id", contactId);  
        values.put("mimetype", "vnd.android.cursor.item/phone_v2");  
        values.put("data2", "2");  
        values.put("data1", "15099144117");  
        resolver.insert(uri, values);  
        // 添加Email  
        values.clear();  
        values.put("raw_contact_id", contactId);  
        values.put("mimetype", "vnd.android.cursor.item/email_v2");  
        values.put("data2", "2");  
        values.put("data1", "zhouguoping@qq.com");  
        resolver.insert(uri, values);  
	}
    @SuppressWarnings("deprecation")
    private void deleteContacts(){
        this.mContext.getContentResolver().delete(People.CONTENT_URI, null, null);
    }
}
