package com.example.ratest;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class SecondActivity extends Activity {
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.i("TEST APP", "[1] android.app.Activity onCreate");
		TextView tv = new TextView(this);
		tv.setText("请点击按返回键");
		setContentView(tv);
//		try {
//			Thread.sleep(1000);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		SecondActivity.this.finish();

	}
	@Override
	public void onDestroy()
	{
		super.onDestroy();
		// 输出日志
		Log.i("TEST APP", "[7] android.app.Activity onDestroy");
	}
	@Override
	public void onRestart()
	{
		super.onRestart();
		// 输出日志
		Log.i("TEST APP", "[2] android.app.Activity onRestart");
	}

	@Override
	public void onResume()
	{
		super.onResume();
		// 输出日志
		Log.i("TEST APP", "[4] android.app.Activity onResume");
	}
}
