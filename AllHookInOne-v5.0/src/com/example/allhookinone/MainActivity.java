package com.example.allhookinone;

import java.lang.reflect.Method;

import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;



public class MainActivity extends Activity {
    
    private  Method method;
    private String TAG = "Java Hook";
	
	static class MyEntity{
		public String value = "HelloWorld";
	}

/*	private String getString(int a, String b){
	    Log.i("TTT","getString method implement");
		return a + "str: " + b;
	}
	
	private String getString2(String... str1){
	    Log.i("TTT","getString2 method implement");
		return str1[0] + " " + str1[1];
	}
	
	private String getString3(MyEntity entity){
		return entity.value;
	}*/
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		Button btn1 = (Button) findViewById(R.id.button1);
		btn1.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                WifiManager wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);
                WifiInfo info = wifi.getConnectionInfo();
                info.getMacAddress();
                Log.i(TAG, info.getMacAddress());
/*                Thread t1 = new Runner2() ; // Runner2 继承了Thread类
                t1.start();*/

                // ELFHook测试
//                HookUtils.elfhook();                
            }
        });
/*		Button btn2 = (Button)findViewById(R.id.button2);
		btn2.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                // 可变类型测试
                Log.i(TAG, getString2("aa", "bb"));
            }
        });
		Button btn3 =(Button)findViewById(R.id.button3);
		btn3.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                // 自定义类型测试
                MyEntity entity = new MyEntity();
                Log.i(TAG,getString3(entity));
            }
        });*/
		Button btn4 = (Button)findViewById(R.id.button4);
		btn4.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
//                Runner r1 = new Runner2();
                Thread t1 = new Runner2() ; // Runner2 继承了Thread类
                t1.start();
            }
        });
		
		Button btn5 = (Button)findViewById(R.id.button5);
		btn5.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                Intent intent = new Intent(MainActivity.this,SecondActivity.class);
                startActivity(intent);
            }
        });
		Button btn6 = (Button)findViewById(R.id.button6);
		btn6.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                try {
                    //hook method getString
                	//通过反射获取方法，int.class=int，String.class=class java.lang.String
                    method = MainActivity.class.getDeclaredMethod("getString", int.class, String.class);

                    Log.i("s","int.class="+int.class+", String.class="+String.class);
                    HookUtils.hookMethod(method, "(ILjava/lang/String;)Ljava/lang/String;");
                    
//                    //hook method getString2
                    method = MainActivity.class.getDeclaredMethod("getString2", String[].class);
                    HookUtils.hookMethod(method, "([Ljava/lang/String;)Ljava/lang/String;");
                    
//                    //hook method getString3
                    method = MainActivity.class.getDeclaredMethod("getString3", MyEntity.class);
                    HookUtils.hookMethod(method, "(Lcom/example/allhookinone/MainActivity$MyEntity;)Ljava/lang/String;");
                    
                    //hook method start in Thread class
                    method = Thread.class.getDeclaredMethod("start");
                    HookUtils.hookMethod(method, "()V");
                    
//                    hook method onCreate in Activity class
                    method = Activity.class.getDeclaredMethod("onCreate",Bundle.class);
                    HookUtils.hookMethod(method, "(Landroid/os/Bundle;)V");
                } catch (NoSuchMethodException e) {
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
	
	

}
