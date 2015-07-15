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

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.*;
import com.fortysevendeg.android.swipelistview.R;
import com.fortysevendeg.android.swipelistview.SwipeListView;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;

import android.widget.Toast;


public class PackageAdapter extends BaseAdapter {/*      * 新建一个类继承BaseAdapter，实现视图与数据的绑定*/
	/*BaseAdapter就Android应用程序中经常用到的基础数据适配器，
	它的主要用途是将一组数据传到像ListView等UI显示组件，它是继承自接口类Adapter */
    private List<PackageItem> data;
    private Context context;
    
    public PackageAdapter(Context context, List<PackageItem> data) {//设置数据
        this.context = context;
        this.data = data;
    }

    @Override
    public int getCount() {//返回数组的长度
        return data.size();
    }

    @Override
    public PackageItem getItem(int position) {
        return data.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    
    /*存放控件*/
    static class ViewHolder {
        ImageView process_image;
        TextView process_title;
        TextView process_description;
        Button button_open;
        Button button_inject;
        Button button_uninject;
        TextView running_status;
    }
    
    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        final PackageItem item = getItem(position);
        final  ViewHolder holder;
/*        Log.v("position", "position:"+position);
        Log.v("convertView", "convertView:"+convertView);*/
      //观察convertView随ListView滚动情况  
        if (convertView == null) {
            LayoutInflater li = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = li.inflate(R.layout.package_row, parent, false);
            holder = new ViewHolder(); 
            /*得到各个控件的对象*/
            holder.process_image = (ImageView) convertView.findViewById(R.id.example_row_iv_image);
            holder.process_title = (TextView) convertView.findViewById(R.id.example_row_tv_title);
            holder.process_description = (TextView) convertView.findViewById(R.id.example_row_tv_description);
            holder.button_open = (Button) convertView.findViewById(R.id.example_row_b_action_1);
            holder.button_inject = (Button) convertView.findViewById(R.id.example_row_b_action_2);
            holder.button_uninject = (Button) convertView.findViewById(R.id.example_row_b_action_3);
            holder.running_status = (TextView) convertView.findViewById(R.id.sText);
            convertView.setTag(holder);//绑定ViewHolder对象  
        } else {
            holder = (ViewHolder) convertView.getTag();//取出ViewHolder对象 //使用缓存的
        }

        ((SwipeListView) parent).recycle(convertView, position);// 自动判断对象是否不再被需要，然后去销毁该对象
        /* 设置TextView显示的内容，即我们存放在动态数组中的数据 */
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
        
        holder.button_open.setOnClickListener(new View.OnClickListener() {//打开按钮
            @Override
            public void onClick(View v) {
                //修改item状态
            	holder.running_status.setText("未注入");
            	item.setRunningStatus(PackageItem.NOT_INJECT);
            	//通过intent启动应用程序
                Intent intent = context.getPackageManager().getLaunchIntentForPackage(item.getPackageName());
                if (intent != null) {
                    context.startActivity(intent);
                } else {
                    Toast.makeText(context, R.string.cantOpen, Toast.LENGTH_SHORT).show();
                    holder.running_status.setText("未运行");
                }      
                
            }
        });

        holder.button_inject.setOnClickListener(new View.OnClickListener() {//注入按钮
            @Override
            public void onClick(View v) {
            	Process process = null;
        		DataOutputStream os = null;
        		DataInputStream is = null;
        		
        		if(item.getRunningStatus() == PackageItem.NOT_RUNNING ){
        		    Toast.makeText(context,"请先点击打开按钮，运行程序",Toast.LENGTH_SHORT).show();
        		    return;
        		}
        		if(item.getRunningStatus() == PackageItem.IS_INJECTED){
                    Toast.makeText(context,"已注入成功",Toast.LENGTH_SHORT).show();
                    return;
        		}
        		try {
        			
        			process = Runtime.getRuntime().exec("su");
        			os = new DataOutputStream(process.getOutputStream());
        			is = new DataInputStream(process.getInputStream());
        			BufferedReader bfr = new BufferedReader(new InputStreamReader(is));

        			String pName = item.getPackageName();
        			String packageName ="com.example.injector";//放的位置
        			Log.v("Injector", "packageName :" + pName);

        			String pid = "";
        			String line = null;

        			os.writeBytes("ps\n");
        			os.flush();
        			
/*        			while ((line = bfr.readLine()) != null) { // 读取输出
    					Log.v("Injector", line);
        				if (line.contains(pName)) {
        					Log.v("Injector", line);
        					String[] splitline = line.split("\\s+");
        					pid = splitline[1];
        					break;
        				}
        			}
        			Log.v("Injector", "pid:" + pid);*/
        			
/*        			os.writeBytes("chmod 777 /data/data/" + packageName + "/*\n");
        			os.flush();
        			os.writeBytes("dd if=/data/data/" + packageName + "/lib/libinj.so "
        					+ "of=/data/data/" + packageName + "/inj\n");
        			os.flush();
        			os.writeBytes("chmod 777 /data/data/" + packageName + "/inj\n");
        			os.flush();
        			os.writeBytes("/data/data/" + packageName + "/inj " + pid + "\n");
        			os.flush();*/
        			os.writeBytes("chmod 777 /data/inj-allhookinone/*\n");
                    os.flush();
                    os.writeBytes("/data/inj-allhookinone/AndroidInjectSo\n");
                    os.flush();
        			os.writeBytes("exit\n");
        			os.flush();
        			
        			while ((line = bfr.readLine()) != null) { // 读取输出
        				Log.v("Injector", line);
        			}
        			Log.v("Injector", "inject successfully!   " + pid);
        			Toast.makeText(context,"注入成功",Toast.LENGTH_SHORT).show();
        			holder.running_status.setText("已注入");
        			item.setRunningStatus(PackageItem.IS_INJECTED);
        			
/*                    if(setcolor(item)==2){//未注入
                    	holder.setText.setText("未注入");
                    }
//                    else if(setcolor(item)==1){//已注入
                    else if(setcolor(item)==2){
                    	holder.setText.setText("已注入");
                    }
                    else if(setcolor(item)==0){//未运行
                    	holder.setText.setText("未运行");
                    }*/
        			process.waitFor();
        		} catch (Exception e) {
        			// TODO Auto-generated catch block
        			Log.e("Error", e.getMessage());
        			e.printStackTrace();
        		} 
        		finally {
        			try {
        				if (os != null) {
        					os.close();
        				}
        				if (is != null) {
        					is.close();
        				}
        				process.destroy();
        			} catch (IOException e) {
        				// TODO Auto-generated catch block
        				e.printStackTrace();
        			}
        		}
     //  		return true;
        		 try{
                 	
                 }catch (Exception e) {
         			// TODO Auto-generated catch block
         			Log.e("Error", e.getMessage());
         			e.printStackTrace();
   //      			return false;
         		} 
            }
        });

        holder.button_uninject.setOnClickListener(new View.OnClickListener() {// 解注入按钮
                @Override
                public void onClick(View v) {
                    Process process = null;
                    DataOutputStream os = null;
                    DataInputStream is = null;
                    
                    if(item.getRunningStatus() != PackageItem.IS_INJECTED){
                        return;
                    }

                    try {

                        process = Runtime.getRuntime().exec("su");
                        os = new DataOutputStream(process.getOutputStream());
                        is = new DataInputStream(process.getInputStream());
                        BufferedReader bfr = new BufferedReader(new InputStreamReader(is));

                        String pName = item.getPackageName();

                        String pid = "";
                        String line = null;

                        os.writeBytes("ps\n");
                        os.flush();
                        while ((line = bfr.readLine()) != null) { // 读取输出
                            if (line.contains(pName)) {
                                String[] splitline = line.split("\\s+");
                                pid = splitline[1];
                                break;
                            }
                        }
                        os.writeBytes("kill " + pid + "\n");
                        os.flush();
                        os.writeBytes("exit\n");
                        os.flush();
                        Toast.makeText(context,"解注入成功",Toast.LENGTH_SHORT).show();
                        holder.running_status.setText("未运行");
                        item.setRunningStatus(PackageItem.NOT_RUNNING);
/*                        if (setcolor(item) == 2) {// 未注入
                            holder.running_status.setText("未注入");
                        }
                        else if (setcolor(item) == 1) {// 已注入
                            holder.running_status.setText("已注入");
                        }
                        else if (setcolor(item) == 0) {// 未运行
                            holder.running_status.setText("未运行");
                        }*/
                        process.waitFor();
                    } catch (Exception e) {
                        // TODO Auto-generated catch block
                        Log.e("Error", e.getMessage());
                        e.printStackTrace();
                        // return false;
                    }
                }

                });

        return convertView;//把写入具体函数之后的view返回
    }

    public String findpid(PackageItem item){
    	Process process = null;
		DataOutputStream os = null;
		DataInputStream is = null;
		String pid = "";
		try {
			
			process = Runtime.getRuntime().exec("su");
			os = new DataOutputStream(process.getOutputStream());
			is = new DataInputStream(process.getInputStream());
			BufferedReader bfr = new BufferedReader(new InputStreamReader(is));

			String pName = item.getPackageName();
			Log.v("Injector", "packageName :" + pName);

			
			String line = null;

			os.writeBytes("ps\n");
			os.flush();
			os.writeBytes("exit\n");
			os.flush();

			while ((line = bfr.readLine()) != null) { // 读取输出
				if (line.contains(pName)) {
					String[] splitline = line.split("\\s+");
					pid = splitline[1];
					break;
				}      
			}
			
    }catch (Exception e) {
		// TODO Auto-generated catch block
		Log.e("Error", e.getMessage());
		e.printStackTrace();
	}
		return pid;            
    }
    
   /* public int setcolor(PackageItem item){
    	Process process = null;
		DataOutputStream os = null;
		DataInputStream is = null;
		
		String pid;	
		pid=findpid(item);
		if(pid==""){
			return 0;
		}
		
		try {
			
			process = Runtime.getRuntime().exec("su");
			os = new DataOutputStream(process.getOutputStream());
			is = new DataInputStream(process.getInputStream());
			BufferedReader bfr = new BufferedReader(new InputStreamReader(is));

			String pName = item.getPackageName();
			Log.v("Injector", "packageName :" + pName);

			String line = null;

			os.writeBytes("cat /proc/"+pid+"/maps | grep liballhookinone.so\n");
			os.flush();
   			os.writeBytes("exit\n");
			os.flush();	
			Log.v("Injector", "Not been injected");   
			
			while ((line = bfr.readLine()) != null) { // 读取输出
				if (line.contains("liballhookinone.so")) {
					Log.v("Injector", "Has been injected");
					return 1;//已注入
				}
			}
			process.waitFor();
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			Log.e("Error", e.getMessage());
			e.printStackTrace();
		} 
		return 2;//未注入
    }*/
}
