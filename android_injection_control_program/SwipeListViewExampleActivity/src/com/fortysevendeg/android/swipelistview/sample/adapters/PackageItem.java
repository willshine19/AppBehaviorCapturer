/*
 * Copyright (C) 2013 47 Degrees, LLC
 *  http://47deg.com
 *  hello@47deg.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

package com.fortysevendeg.android.swipelistview.sample.adapters;

//import java.io.Serializable;

import android.graphics.drawable.Drawable;
import android.os.Parcel;
import android.os.Parcelable;

/**  
 *   包信息 只有4个成员变量 getter setter
 *   成员变量 icon name packageName running_status
 *   实现Parcelable接口，该类的对象支持序列化。但是没有吧Drawable序列化
 */  
public class PackageItem implements Parcelable { 

    private Drawable icon;
    private String name;	// 应用名
    private String packageName;	// 包名
    private int running_status;	// 状态
    
    //标识此程序未运行
    public static final int NOT_RUNNING = 0;
    //标识此程序已注入
    public static final int IS_INJECTED = 1;
    //标识此程序已运行，未注入
    public static final int NOT_INJECT = 2;
    
    public void setRunningStatus(int running_status) {
    	this.running_status = running_status;
    }
    
    public int getRunningStatus() {
        return running_status;
    }
    
    public void setPackageName(String packageName) {
    	this.packageName = packageName;
    }
 
    public String getPackageName() {
        return packageName;
    }

    public void setName(String name) {
    	this.name = name;
    }
 
    public String getName() {
        return name;
    }
    
    public void setIcon(Drawable icon) {
    	this.icon = icon;
    }

    public Drawable getIcon() {
        return icon;
    }

	@Override
	public int describeContents() {
		return 0;
	}

	@Override
	public void writeToParcel(Parcel out, int arg1) {
		out.writeString(name);
		out.writeString(packageName);
		out.writeInt(running_status);
	}
	
	public static final Parcelable.Creator<PackageItem> CREATOR	= new Creator<PackageItem>() {

		@Override
		public PackageItem createFromParcel(Parcel in) {
			return new PackageItem(in);
		}


		@Override
		public PackageItem[] newArray(int size) {
			return new PackageItem[size];
		}
		
	};
	
	public PackageItem(Parcel in) {
		this.name = in.readString();
		this.packageName = in.readString();
		this.running_status = in.readInt();
	}

	public PackageItem() {
		// TODO Auto-generated constructor stub
	}
}
