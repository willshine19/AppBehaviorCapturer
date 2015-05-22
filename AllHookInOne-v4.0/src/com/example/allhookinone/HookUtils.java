package com.example.allhookinone;

import android.util.Log;

import java.lang.reflect.Constructor;
import java.lang.reflect.Member;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

public final class HookUtils {
	static{
		System.loadLibrary("onehook");
        Log.i("s","loadLibrary");
	}
	
	public static int hookMethod(Member method, String methodsig){
		int result = -1;
		
		if(method instanceof Method || method instanceof Constructor<?>){
			//instanceof:判断其左边对象是否为其右边类的实例
			//Constructor:构造函数的意思，new的时候为调用构造函数
			String clsdes = method.getDeclaringClass().getName().replace('.', '/');
			// 将所有.换成/
            //clsdes=com/example/allhookinone/MainActivity
            Log.i("s","clsdes="+clsdes);
            String methodname = method.getName();//methodname=getString
            Log.i("s","methodname="+methodname);
			if(method instanceof Constructor<?>){
                Log.i("s","method is Constructor");
				result = hookMethodNative(clsdes, methodname, methodsig, false);
			}else{//for method
                Log.i("s","method is method");//method is method
                //mothod.getModifiers()可以断类/接口/字段/方法的修饰符
				result = hookMethodNative(clsdes, methodname, methodsig, Modifier.isStatic(method.getModifiers()));
			}
		}
		
		return result;
	}
	
	public static native int elfhook();
	
	private static native int hookMethodNative(String clsdes, String methodname, String methodsig, boolean isstatic);
}
