package com.example.allhookinone;


import android.support.v7.app.ActionBarActivity;
import android.telephony.TelephonyManager;
import android.content.Context;
import android.location.LocationManager;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends ActionBarActivity {
    
    private String TAG = "Java Hook";
    public static WifiManager wifi ;
    public static LocationManager location;
    public static TelephonyManager telephony;
    private int THREAD_NUM = 5;

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
}
