package com.auo.androidinjectso;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Random;

import org.apache.http.util.EncodingUtils;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		final Button button1 = (Button)this.findViewById(R.id.button1);
		final Button button2 = (Button)this.findViewById(R.id.button2);
		final TextView tv = (TextView) findViewById(R.id.tv);
	    final Random ran = new Random(100);
		
		button1.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
			//	String r=ran.nextInt()+"";
				button1.setText(stringFromJNI("1230"));
	//		readtxtc(tv);
			}
		});
		button2.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				writetxt("s.txt",ran.nextInt()+"");
				readtxtj(tv);
				
			}
		});
	}
	public void writetxt(String fileName,String message){
		try{
		FileOutputStream fout =openFileOutput(fileName, MODE_PRIVATE);
		byte [] bytes = message.getBytes();
		fout.write(bytes);
		fout.close();
		}
		catch(Exception e){
		e.printStackTrace();
		}
		}
	public void readtxtj(TextView tv) {  
		String res="";
	try{
		FileInputStream fin = openFileInput("s.txt");
		int length = fin.available();
		byte [] buffer = new byte[length];
		fin.read(buffer);
		res = EncodingUtils.getString(buffer, "UTF-8");
		res=res+"  --JAVA--";
		tv.setText(res);
		fin.close();
		}
		catch(Exception e){
		e.printStackTrace();
		}
    } 
	
	public void readtxtc(TextView tv) {  
		String res="";
	try{
		FileInputStream fin = openFileInput("s.txt");
		int length = fin.available();
		byte [] buffer = new byte[length];
		fin.read(buffer);
		res = EncodingUtils.getString(buffer, "UTF-8");
		res=res+"  --C--";
		tv.setText(res);
		fin.close();
		}
		catch(Exception e){
		e.printStackTrace();
		}
    } 
	static {
		System.loadLibrary("test");
	}
	
	
	public static native String stringFromJNI(String str);
}
