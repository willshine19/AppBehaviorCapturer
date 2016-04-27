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

package com.android.swipelistview.sample.adapters;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.*;

import com.android.swipelistview.SwipeListView;
import com.fortysevendeg.android.swipelistview.R;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import android.widget.Toast;

/** 
 * BaseAdapter子类，实现视图与数据的绑定
 * 需要重写4个方法。
 * BaseAdapter就Android应用程序中经常用到的基础数据适配器，
 * 它的主要用途是将一组数据传到像ListView等UI显示组件，它是继承自接口类Adapter
 */
public class PackageAdapter extends BaseAdapter {
    protected static final String TAG = "PackageAdapter";
	private List<PackageItem> mPackageItemList;
    private Context mContext;
    
    /**
     * 当前注入的app的包名
     */
    public static String sPackageName;
    
    /**  
     * 构造函数
     */ 
    public PackageAdapter(Context context, List<PackageItem> data) {//设置数据
        this.mContext = context;
        this.mPackageItemList = data;
    }

    @Override
    public int getCount() {//返回数组的长度
        return mPackageItemList.size();
    }

    @Override
    public PackageItem getItem(int position) {
        return mPackageItemList.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }
    
    /**  
     * 静态内部类，存放列表子项的view信息
     */  
    static class ViewHolder {
    	Button button_open;
    	Button button_inject;
    	Button button_uninject;
        ImageView process_image;
        TextView process_title;
        TextView process_description;
        TextView running_status;
    }
    
    
    /**
     * Get a View that displays the data at the specified position in the data set.
     */
    @Override
	public View getView(final int position, View convertView, ViewGroup parent) {
		final ViewHolder holder;
		
		// 观察convertView随ListView滚动情况
		if (convertView == null) {
            LayoutInflater li = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = li.inflate(R.layout.package_row, parent, false); // 加载列表子项的布局
            /*得到各个控件的对象*/
            holder = new ViewHolder(); 
            holder.button_open = (Button) convertView.findViewById(R.id.example_row_b_action_1);
            holder.button_inject = (Button) convertView.findViewById(R.id.example_row_b_action_2);
            holder.button_uninject = (Button) convertView.findViewById(R.id.example_row_b_action_3);
            holder.process_image = (ImageView) convertView.findViewById(R.id.example_row_iv_image);
            holder.process_title = (TextView) convertView.findViewById(R.id.example_row_tv_title);
            holder.process_description = (TextView) convertView.findViewById(R.id.example_row_tv_description);
            holder.running_status = (TextView) convertView.findViewById(R.id.sText);
            convertView.setTag(holder);//绑定ViewHolder对象  
        } else {
            holder = (ViewHolder) convertView.getTag();//取出ViewHolder对象 //使用缓存的
        }
		initViews(position, holder);

		// 自动判断对象是否不再被需要，然后去销毁该对象
        ((SwipeListView) parent).recycle(convertView, position);
        return convertView;//把写入具体函数之后的view返回
    }

	/**
	 * 初始化ListView子项中的各个View，每一个ListView子项对应一个ViewHolder
	 * @param position
	 * @param holder
	 */
	private void initViews(final int position, final ViewHolder holder) {
		/* 设置TextView显示的内容，即我们存放在动态数组中的数据 */
        final PackageItem item = getItem(position);
        holder.process_image.setImageDrawable(item.getIcon());
        holder.process_title.setText(item.getName());
        holder.process_description.setText(item.getPackageName());
        if (item.getRunningStatus() == PackageItem.NOT_INJECT) {
            holder.running_status.setText("未注入");
        }
        else if (item.getRunningStatus() == PackageItem.IS_INJECTED) {
            holder.running_status.setText("已注入");
        }
        else if (item.getRunningStatus() == PackageItem.NOT_RUNNING) {
            holder.running_status.setText("未运行");
        }
        
        //打开按钮 通过包名开启指定app
        holder.button_open.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	//通过intent启动应用程序
                Intent intent = mContext.getPackageManager().getLaunchIntentForPackage(item.getPackageName());
                if (intent != null) {
                    mContext.startActivity(intent);
                    holder.running_status.setText("未注入");
                    item.setRunningStatus(PackageItem.NOT_INJECT);
                } else {
                    Toast.makeText(mContext, R.string.cantOpen, Toast.LENGTH_SHORT).show();
                }      
            }
        });

        //注入按钮 依次注入该app的所有进程
        holder.button_inject.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	List<String> runningProcessList = getRunningProcessList();
            	List<String> packageNameList = findPackageName(item, runningProcessList);
            	for (String each : packageNameList) {
            		injectProcess(each);
            	}
        		Toast.makeText(mContext,"注入成功",Toast.LENGTH_SHORT).show();
        		holder.running_status.setText("已注入");
        		item.setRunningStatus(PackageItem.IS_INJECTED);
            }
        });

     // 解注入按钮，kill这个进程
        holder.button_uninject.setOnClickListener(new View.OnClickListener() {// 解注入按钮
                @Override
                public void onClick(View v) {
                    Process process = null;
                    DataOutputStream os = null;
                    BufferedReader reader = null;
                    
                    if(item.getRunningStatus() != PackageItem.IS_INJECTED){
            		    Toast.makeText(mContext,"请先注入",Toast.LENGTH_SHORT).show();
                        return;
                    }

                    try {
                        process = Runtime.getRuntime().exec("su");
                        os = new DataOutputStream(process.getOutputStream());
                        reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

                        String pName = item.getPackageName();

                        String pid = null;
                        String line = null;

                        os.writeBytes("ps\n");
                        os.flush();
                        while ((line = reader.readLine()) != null) { // 读取输出
                            if (line.contains(pName)) {
                                String[] splitline = line.split("\\s+");
                                pid = splitline[1];
                                break;
                            }
                        }
                        if (pid != null) {
                        	os.writeBytes("kill " + pid + "\n");
                        	os.flush();
                        	os.writeBytes("exit\n");
                        	os.flush();
                        	Toast.makeText(mContext,"解注入成功",Toast.LENGTH_SHORT).show();
                        	process.waitFor();
                        }
                        holder.running_status.setText("未运行");
                        item.setRunningStatus(PackageItem.NOT_RUNNING);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						Log.e("Error", e.getMessage());
						e.printStackTrace();
							// return false;
					} finally {
						try {
							if (os != null) {
								os.close();
							}
							if (reader != null) {
								reader.close();
							}
						} catch (IOException ex) {
							Log.e(TAG, "关闭流失败");
						}
					}
				}
			});
	}
	
	/**
	 * 注入一个进程，
	 * @param 该进程对应的包名
	 */
	private void injectProcess(String packageName) {
		Process process = null;
		DataOutputStream os = null;
		DataInputStream is = null;
		BufferedReader reader = null;
		
		try {
			process = Runtime.getRuntime().exec("su");
			os = new DataOutputStream(process.getOutputStream());
			is = new DataInputStream(process.getInputStream());
			reader = new BufferedReader(new InputStreamReader(is));

			sPackageName = packageName;
			Log.v("InjectButton", "packageName :" + packageName);

			String line = null;

			os.writeBytes("chmod 777 /data/inj-allhookinone/*\n");
            os.flush();
            os.writeBytes("/data/inj-allhookinone/AndroidInjectSo " +packageName +"\n");
            os.flush();
			os.writeBytes("exit\n");
			os.flush();
			
			// 读取输出
			while ((line = reader.readLine()) != null) { 
//				Log.v("InjectButton", line);
			}
			
			Log.i("InjectButton", "[+] 注入 " + packageName + " 完成!");
			
			process.waitFor();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			Log.e("Error", e.getMessage());
			e.printStackTrace();
		} finally {
			try {
				if (os != null) {
					os.close();
				}
				if (reader != null) {
					reader.close();
				}
				process.destroy();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
    /**  
     * 用linux命令行运行 ps，将所有正在运行的进程信息保存在数组中,返回这个数组
     * 这个数组中的元素是字符串，每个字符串对应ps命令输出的一行，未加工
     */
    private List<String> getRunningProcessList() {
    	List<String> runningProcessList = new ArrayList<String>();
        Process process = null;
        DataOutputStream os = null;
        BufferedReader reader = null;

        try {
        	process = Runtime.getRuntime().exec("su");
            os = new DataOutputStream(process.getOutputStream());
            reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            os.writeBytes("ps\n");
            os.flush();
            String line = null;
            os.writeBytes("exit\n");
            os.flush();
            while ((line = reader.readLine()) != null) {
            	runningProcessList.add(line);
            }
        } catch (Exception e) {
            Log.e(TAG, e.getMessage());
            e.printStackTrace();
        } finally {
        	try {
        		if (os != null) {
        			os.close();
        		}
        		if (reader != null) {
        			reader.close();
        		}
        	} catch (IOException ex) {
        		Log.e(TAG,	"关闭流失败");
        	}
        }
        return runningProcessList;
    }
    
    /**  
     * 返回满足条件的包名List，List中的包名所对应的进程都是同一个app的。解决多进程问题
     * @param item 代表已安装到手机上的一个app
     * @param list getRunningProcessList的返回值
     */
    private List<String> findPackageName(PackageItem item, List<String> list) {
    	List<String> packageNameList = new ArrayList<String>();
        String pName = item.getPackageName();

        for (String each : list) {
        	if(each.contains(pName)) {
        		String[] splitFactors = each.split(" ");
        		 for (String factor : splitFactors) {
        			 if (factor.contains(pName)) {
        				 packageNameList.add(factor);
        			 }
        		 }
        	}
        }
        return packageNameList;
    }

    
}
