package com.example.hookapi;

import android.app.Activity;  
import android.content.Intent;
import android.os.Bundle;  
import android.view.View;  
import android.view.View.OnClickListener;  
import android.widget.Button;  

public class hello extends Activity
{
	Button huoqu;
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.hello);
		huoqu = (Button) findViewById(R.id.huoqu);
		huoqu.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View arg0) 
			{
				Intent intent01 = new Intent();
				intent01.setClass(hello.this,MainActivity.class);
				startActivity(intent01);
				hello.this.finish();
			} 
		}); 
	}
}