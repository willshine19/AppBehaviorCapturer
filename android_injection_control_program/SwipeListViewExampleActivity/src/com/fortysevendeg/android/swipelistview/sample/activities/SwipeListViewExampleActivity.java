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

package com.fortysevendeg.android.swipelistview.sample.activities;

import android.app.ProgressDialog;
import android.app.Service;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.IBinder;
import android.support.v4.app.FragmentActivity;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.ActionMode;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.AbsListView;
import android.widget.ListView;
import com.fortysevendeg.android.swipelistview.BaseSwipeListViewListener;
import com.fortysevendeg.android.swipelistview.R;
import com.fortysevendeg.android.swipelistview.SwipeListView;
import com.fortysevendeg.android.swipelistview.sample.adapters.PackageAdapter;
import com.fortysevendeg.android.swipelistview.sample.adapters.PackageItem;
import com.fortysevendeg.android.swipelistview.sample.adapters.PackageItemModel;
import com.fortysevendeg.android.swipelistview.sample.dialogs.AboutDialog;
import com.fortysevendeg.android.swipelistview.sample.utils.PreferencesManager;
import com.fortysevendeg.android.swipelistview.sample.utils.SettingsManager;
import com.lwl.service.JsonService;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class SwipeListViewExampleActivity extends FragmentActivity {

    private static final int REQUEST_CODE_SETTINGS = 0; 
    private static final String TAG = "SwipeListViewExampleActivity";
    private PackageAdapter adapter;
    private ArrayList<PackageItem> appInfoList;
    private SwipeListView swipeListView;
    private ProgressDialog progressDialog;
    //保存启动的service的Binder对象，用于传输Service中的数据
    private JsonService.JsonBinder binder;
    
    // 内部类
    ServiceConnection  connection = new ServiceConnection() {
        @Override
        public void onServiceDisconnected(ComponentName name) {
        	Log.i(TAG, "--service disconnected--");
        }
        
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
        	Log.i(TAG, "--service connected--");
            binder = (JsonService.JsonBinder)service;
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.swipe_list_view_activity);// 设置Activity采用R.layout下的**布局文件进行布局
        appInfoList = PackageItemModel.getInstance().getList();
        adapter = new PackageAdapter(this, appInfoList);
        swipeListView = (SwipeListView) findViewById(R.id.example_lv_list); // 获取xml中创建的实例
        swipeListView.setAdapter(adapter);
        swipeListView.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE_MODAL);

        setSwipeListView();
        
        //开启sJsonervice
        Log.d(TAG, "即将绑定service");
        Intent intent = new Intent();
        intent.setAction("com.lwl.service.JSON_SERVICE");
        bindService(intent,connection,Service.BIND_AUTO_CREATE);
        Log.d(TAG, "成功绑定service");

        progressDialog = new ProgressDialog(this);// 进度条
        progressDialog.setMessage(getString(R.string.loading));
        progressDialog.setCancelable(false);
//         progressDialog.show();
    }

    
    /**  
     * 设置界面的设置
     */
    private void setSwipeListView() {
        SettingsManager settings = SettingsManager.getInstance();
        swipeListView.setSwipeMode(settings.getSwipeMode());
        swipeListView.setSwipeActionLeft(settings.getSwipeActionLeft());
        swipeListView.setSwipeActionRight(settings.getSwipeActionRight());
        swipeListView.setOffsetLeft(convertDpToPixel(settings.getSwipeOffsetLeft()));
        swipeListView.setOffsetRight(convertDpToPixel(settings.getSwipeOffsetRight()));
        swipeListView.setAnimationTime(settings.getSwipeAnimationTime());
        swipeListView.setSwipeOpenOnLongPress(settings.isSwipeOpenOnLongPress());
     // api level >= 11
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            // Set a {@link MultiChoiceModeListener} that will manage the
            // lifecycle of the selection {@link ActionMode}
            swipeListView.setMultiChoiceModeListener(new AbsListView.MultiChoiceModeListener() {

                @Override
                public void onItemCheckedStateChanged(ActionMode mode, int position,
                        long id, boolean checked) {
                    mode.setTitle("Selected (" + swipeListView.getCountSelected() + ")");
                }

                @Override
                public boolean onActionItemClicked(ActionMode mode, MenuItem item) {
                    switch (item.getItemId()) {// 判断id为删除就删掉（单个）
                        case R.id.menu_delete:
                            swipeListView.dismissSelected();
                            mode.finish();
                            return true;
                        default:
                            return false;
                    }
                }

                @Override
                public boolean onCreateActionMode(ActionMode mode, Menu menu) {
                    MenuInflater inflater = mode.getMenuInflater();// MenuInflater是用来加载menu布局文件的
                    inflater.inflate(R.menu.menu_choice_items, menu);
                    return true;
                }

                @Override
                public void onDestroyActionMode(ActionMode mode) {
                    swipeListView.unselectedChoiceStates();
                }

                @Override
                public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
                    return false;
                }
            });
        }

        swipeListView.setSwipeListViewListener(new BaseSwipeListViewListener() {
            @Override
            public void onOpened(int position, boolean toRight) {
            }

            @Override
            public void onClosed(int position, boolean fromRight) {
            }

            @Override
            public void onListChanged() {
            }

            @Override
            public void onMove(int position, float x) {
            }

            @Override
            public void onStartOpen(int position, int action, boolean right) {
//                Log.d("swipe", String.format("onStartOpen %d - action %d", position, action));
            }

            @Override
            public void onStartClose(int position, boolean right) {
//                Log.d("swipe", String.format("onStartClose %d", position));
            }

            @Override
            public void onClickFrontView(int position) {
//                Log.d("swipe", String.format("onClickFrontView %d", position));
            }

            @Override
            public void onClickBackView(int position) {
//                Log.d("swipe", String.format("onClickBackView %d", position));
            }

            @Override
            public void onDismiss(int[] reverseSortedPositions) {
                for (int position : reverseSortedPositions) {
                    appInfoList.remove(position);
                }
                // 可以在修改适配器绑定的数组后，不用重新刷新Activity，通知Activity更新ListView
                adapter.notifyDataSetChanged();
            }

        });
    }

    public int convertDpToPixel(float dp) {
        DisplayMetrics metrics = getResources().getDisplayMetrics();
        float px = dp * (metrics.densityDpi / 160f);
        return (int) px;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {// 此方法用于初始化菜单，其中menu参数就是即将要显示的Menu实例。
                                                   // 返回true则显示该menu,false 则不显示;
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu_app, menu);
        return false;
    }

    @Override
    public boolean onMenuItemSelected(int featureId, MenuItem item) {// 对触控的反应
        boolean handled = false;
        switch (item.getItemId()) {
            case android.R.id.home: // Actionbar home/up icon
                finish();
                break;
            case R.id.menu_settings:// 切换到设置界面
                Intent intent = new Intent(this, SettingsActivity.class);
                startActivityForResult(intent, REQUEST_CODE_SETTINGS);
                break;
        }
        return handled;
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {// 未用
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode) {
            case REQUEST_CODE_SETTINGS:
                setSwipeListView();
        }
    }


}
