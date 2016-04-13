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
import com.fortysevendeg.android.swipelistview.R.id;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;

import android.widget.Toast;

/**
 * BaseAdapter子类，实现视图与数据的绑定 需要重写4个方法。 BaseAdapter就Android应用程序中经常用到的基础数据适配器，
 * 它的主要用途是将一组数据传到像ListView等UI显示组件，它是继承自接口类Adapter
 */
public class PackageAdapter extends BaseAdapter {
	protected static final String TAG = "PackageAdapter";
	// 文件的暂存地址
	private String fileDir = "/data/local/strace/";
	private List<PackageItem> mPackageItemList;
	private Context mContext;

	/**
	 * 构造函数
	 */
	public PackageAdapter(Context context, List<PackageItem> data) {// 设置数据
		this.mContext = context;
		this.mPackageItemList = data;
	}

	@Override
	public int getCount() {// 返回数组的长度
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
		Button button_strace;
		Button button_pack;
		ImageView process_image;
		TextView process_title;
		TextView process_description;
		TextView running_status;
	}

	/**
	 * Get a View that displays the data at the specified position in the data
	 * set.
	 */
	@Override
	public View getView(final int position, View convertView, ViewGroup parent) {
		final ViewHolder holder;

		// 观察convertView随ListView滚动情况
		if (convertView == null) {
			LayoutInflater li = (LayoutInflater) mContext
					.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			convertView = li.inflate(R.layout.package_row, parent, false); // 加载列表子项的布局
			/* 得到各个控件的对象 */
			holder = new ViewHolder();
			holder.button_open = (Button) convertView
					.findViewById(R.id.example_row_b_action_1);
			holder.button_inject = (Button) convertView
					.findViewById(R.id.example_row_b_action_2);
			holder.button_uninject = (Button) convertView
					.findViewById(R.id.example_row_b_action_3);
			holder.button_strace = (Button) convertView
					.findViewById(id.example_row_b_action_4);
			holder.button_pack = (Button) convertView
					.findViewById(id.example_row_b_action_5);
			holder.process_image = (ImageView) convertView
					.findViewById(R.id.example_row_iv_image);
			holder.process_title = (TextView) convertView
					.findViewById(R.id.example_row_tv_title);
			holder.process_description = (TextView) convertView
					.findViewById(R.id.example_row_tv_description);
			holder.running_status = (TextView) convertView
					.findViewById(R.id.sText);
			convertView.setTag(holder);// 绑定ViewHolder对象
		} else {
			holder = (ViewHolder) convertView.getTag();// 取出ViewHolder对象 //使用缓存的
		}

		// 自动判断对象是否不再被需要，然后去销毁该对象
		((SwipeListView) parent).recycle(convertView, position);

		/* 设置TextView显示的内容，即我们存放在动态数组中的数据 */
		final PackageItem item = getItem(position);
		holder.process_image.setImageDrawable(item.getIcon());
		holder.process_title.setText(item.getName());
		holder.process_description.setText(item.getPackageName());
		if (item.getRunningStatus() == PackageItem.NOT_INJECT) {
			holder.running_status.setText("未注入");
		} else if (item.getRunningStatus() == PackageItem.IS_INJECTED) {
			holder.running_status.setText("已注入");
		} else if (item.getRunningStatus() == PackageItem.NOT_RUNNING) {
			holder.running_status.setText("未运行");
		}

		// 打开按钮 通过包名开启指定app
		holder.button_open.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				// 通过intent启动应用程序
				Intent intent = mContext.getPackageManager()
						.getLaunchIntentForPackage(item.getPackageName());
				if (intent != null) {
					mContext.startActivity(intent);
					holder.running_status.setText("未注入");
					item.setRunningStatus(PackageItem.NOT_INJECT);
				} else {
					Toast.makeText(mContext, R.string.cantOpen,
							Toast.LENGTH_SHORT).show();
				}
			}
		});

		// 注入按钮
		holder.button_inject.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				Process process = null;
				DataOutputStream os = null;
				DataInputStream is = null;
				BufferedReader reader = null;

				if (item.getRunningStatus() == PackageItem.NOT_RUNNING) {
					Toast.makeText(mContext, "请先点击打开按钮，运行程序",
							Toast.LENGTH_SHORT).show();
					return;
				}

				if (item.getRunningStatus() == PackageItem.IS_INJECTED) {
					Toast.makeText(mContext, "该程序已被注入成功", Toast.LENGTH_SHORT)
							.show();
					return;
				}

				try {
					process = Runtime.getRuntime().exec("su");
					os = new DataOutputStream(process.getOutputStream());
					is = new DataInputStream(process.getInputStream());
					reader = new BufferedReader(new InputStreamReader(is));

					String packageName = item.getPackageName();
					Log.v(TAG, "packageName :" + packageName);

					String line = null;

					os.writeBytes("chmod 777 /data/inj-allhookinone/*\n");
					os.flush();
					os.writeBytes("/data/inj-allhookinone/AndroidInjectSo "
							+ packageName + "\n");
					os.flush();
					os.writeBytes("exit\n");
					os.flush();

					// 读取输出
					while ((line = reader.readLine()) != null) {
						Log.v(TAG, line);
					}

					Log.v(TAG, "inject " + packageName + " successfully!");
					Toast.makeText(mContext, "注入成功", Toast.LENGTH_SHORT).show();
					holder.running_status.setText("已注入");
					item.setRunningStatus(PackageItem.IS_INJECTED);

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
		});

		// 解注入按钮，kill这个进程
		holder.button_uninject.setOnClickListener(new View.OnClickListener() {// 解注入按钮
					@Override
					public void onClick(View v) {
						Process process = null;
						DataOutputStream os = null;
						BufferedReader reader = null;

						if (item.getRunningStatus() != PackageItem.IS_INJECTED) {
							Toast.makeText(mContext, "请先注入", Toast.LENGTH_SHORT)
									.show();
							return;
						}

						try {
							process = Runtime.getRuntime().exec("su");
							os = new DataOutputStream(process.getOutputStream());
							reader = new BufferedReader(new InputStreamReader(
									process.getInputStream()));

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
								Toast.makeText(mContext, "解注入成功",
										Toast.LENGTH_SHORT).show();
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
		holder.button_strace.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				Log.v(TAG, "in button_strace");
				String packageName = item.getPackageName();
				Log.v(TAG, "" + packageName);
				String pid = getPID(packageName);
				if (pid != "") {
					Process process = null;
					DataOutputStream os = null;
					try {
						process = Runtime.getRuntime().exec("su");
						os = new DataOutputStream(process.getOutputStream());

						Log.v(TAG, "******************pid:" + pid
								+ "*********************");

						os.writeBytes("strace -ff -v -tt -o " + fileDir
								+ "a -p " + pid + "\n");
						Log.v(TAG, "strace -ff -v -tt -o " + fileDir + "a -p "
								+ pid + "\n");
						os.flush();
						os.writeBytes("exit\n");
						os.flush();
					} catch (Exception e) {
						Log.e("Error", e.getMessage());
						e.printStackTrace();
					} finally {
					}
				} else {
					Log.v(TAG, "get pid failed!!! pid = " + pid);
				}
			}
		});

		holder.button_pack.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				Log.v(TAG, "in button_pack");
			}
		});
		return convertView;// 把写入具体函数之后的view返回
	}

	/**
	 * 获取ps中进程名为keyWords的进程号
	 * 
	 * @param keyWords
	 * @return
	 */
	public String getPID(String keyWords) {
		Process process = null;
		DataOutputStream os = null;
		DataInputStream is = null;
		String pid = "";
		try {
			process = Runtime.getRuntime().exec("su");
			os = new DataOutputStream(process.getOutputStream());
			is = new DataInputStream(process.getInputStream());
			BufferedReader bfr = new BufferedReader(new InputStreamReader(is));
			String line = null;

			os.writeBytes("ps\n");
			os.flush();
			os.writeBytes("exit\n");
			os.flush();
			while ((line = bfr.readLine()) != null) { // 读取输出
				// 有可能有僵尸进程
				if (line.contains("Z"))
					continue;
				if (line.contains(keyWords)) {
					String[] splitline = line.split("\\s+");
					if (splitline[splitline.length - 1].equals(keyWords)) {
						pid = splitline[1];
						bfr.close();
						break;
					}
				}
			}

			// process.waitFor();
		} catch (Exception e) {
			Log.e("Error", e.getMessage());
			e.printStackTrace();
		} finally {
			try {
				if (os != null) {
					os.close();
				}
				if (is != null) {
					is.close();
				}
				process.destroy();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return pid;
	}

}
