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

package com.fortysevendeg.android.swipelistview.sample.utils;

import android.content.Context;
import android.content.SharedPreferences;

public class PreferencesManager {//父类,主界面数据

    public static final String SHARED_PREFERENCES_NAME = "SWIPE_LIST_VIEW_SAMPLE_PREFERENCES";

    /**
     * Instance
     */
    private static PreferencesManager preferencesManager = null;

    /**
     * Shared Preferences
     */
    private SharedPreferences sharedPreferences;//SharedPreferences的使用非常简单，能够轻松的存放数据和读取数据。
    //SharedPreferences只能保存简单类型的数据

    /**
     * Preferences variables
     */
    private static final String SHARED_PREFERENCES_SHOW_ABOUT = "SHARED_PREFERENCES_SHOW_ABOUT";

    /**
     * Constructor
     *
     * @param context
     */
    private PreferencesManager(Context context) {
        sharedPreferences = context.getSharedPreferences(SHARED_PREFERENCES_NAME, Context.MODE_PRIVATE);
    }

    public static PreferencesManager getInstance(Context context) {
        if (preferencesManager == null) {
            preferencesManager = new PreferencesManager(context);
        }
        return preferencesManager;
    }

    public void setShowAbout(boolean showAbout) {
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putBoolean(SHARED_PREFERENCES_SHOW_ABOUT, showAbout);//在preferences editor设置一个布尔值，commit()被调用后写回一次。
        editor.commit();//编辑SharedPreferences对象时从这个editor提交自己的preference的更改。
    }

    public boolean getShowAbout() {
        return sharedPreferences.getBoolean(SHARED_PREFERENCES_SHOW_ABOUT, true);
    }


}
