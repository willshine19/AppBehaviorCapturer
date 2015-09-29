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

/**  
 *   包信息 只有4个成员变量 getter setter
 *   成员变量 icon name packageName running_status
 */  
public class PackageItem { // implements Serializable 

    private Drawable icon;
    private String name;
    private String packageName;
    private int running_status;
    
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
}
