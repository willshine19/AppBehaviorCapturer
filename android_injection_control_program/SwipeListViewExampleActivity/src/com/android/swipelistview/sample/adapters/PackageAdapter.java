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
import com.android.swipelistview.sample.adapters.StraceJSON;
import com.fortysevendeg.android.swipelistview.R;
import com.fortysevendeg.android.swipelistview.R.id;
import com.syh.pubjson.JsonSender;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.widget.Toast;

/**
 * BaseAdapter子类，实现视图与数据的绑定 需要重写4个方法。 BaseAdapter就Android应用程序中经常用到的基础数据适配器，
 * 它的主要用途是将一组数据传到像ListView等UI显示组件，它是继承自接口类Adapter
 */
public class PackageAdapter extends BaseAdapter {
	protected static final String TAG = "PackageAdapter";
	// 用于填充JSON里的num项，计数用？
	private int count = 0;
	// 该线程号，现在就只能跟踪单个进程
	private String mPid;
	// 文件的暂存地址
	private String fileDir = "/data/local/strace/";
	// 捕获到的所有线程（进程）号
	private ArrayList<String> allThreadNum = new ArrayList<String>();
	// 一个所有“进程-父进程”对的映射表
	private HashMap<String, String> ptidMap;
	private List<PackageItem> mPackageItemList;
    private Context mContext;
    
    /**
     * 当前注入的app的包名
     */
    public static Map<Integer, String> sPackageNameMap = new HashMap<Integer, String>();
    
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
			holder.button_strace = (Button) convertView.findViewById(id.example_row_b_action_4);
			holder.button_pack = (Button) convertView.findViewById(id.example_row_b_action_5);
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
                
                try {
					Thread.sleep(500);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
                

            	sPackageNameMap.clear();
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

        //注入按钮 依次注入该app的所有进程
        holder.button_inject.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	sPackageNameMap.clear();
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
                        	os.writeBytes("am force-stop " + pName + " \n");
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

		holder.button_strace.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				Log.v(TAG, "in button_strace");
				String packageName = item.getPackageName();
				Log.v(TAG, "" + packageName);
				String pid = getPID(packageName);
				if (pid != "") {
					mPid = pid;
					Process process = null;
					DataOutputStream os = null;
					try {
						process = Runtime.getRuntime().exec("su");
						os = new DataOutputStream(process.getOutputStream());

						Log.v(TAG, "******************pid:" + pid
								+ "*********************");
						os.writeBytes("mkdir " + fileDir + "\n");
						Log.v(TAG, "mkdir " + fileDir + "\n");
						os.writeBytes("chmod 755 " + fileDir + "\n");
						Log.v(TAG, "chmod 755 " + fileDir + "\n");
						// os.writeBytes("strace -ff -v -tt -o " + fileDir
						// + "a -p " + pid + "\n");
						// Log.v(TAG, "strace -ff -v -tt -o " + fileDir +
						// "a -p "
						// + pid + "\n");
						os.writeBytes("strace -ff -v -tt -o "
								+ fileDir
								+ "a -e ioctl,read,write,open,close,fork,chmod,socket,pipe,mkdir,execve,uname -p "
								+ pid + "\n");
						Log.v(TAG, "strace -ff -v -tt -o "
								+ fileDir
								+ "a -e ioctl,read,write,open,close,fork,chmod,socket,pipe,mkdir,execve,uname -p "
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
				Thread t = new Thread(new packAndSendStraceJson());
				t.start();
				Log.v(TAG, "done");
			}
		});
	}

	// XXX 以下是功能函数
	public class packAndSendStraceJson implements Runnable {

		@Override
		public void run() {
			Log.v(TAG, "in Thread");
			chgModandGetTIDsToFile();
			if (saveTIDsToArray()) {
				// 初始大小为size-1，排除最初父线程
				if (allThreadNum.size() < 1) {
					Log.e(TAG, "no thread!!! cannot init hashmap!!!");
					return;
				}
				ptidMap = new HashMap<String, String>(allThreadNum.size() - 1);
				for (int i = 0; i < allThreadNum.size(); ++i) {
					// Log.v(TAG,""+i+":----GETPIDMAP------"+allThreadNum.get(i)+"-----");
					getPTIDMap(allThreadNum.get(i));
				}

				for (int i = 0; i < allThreadNum.size(); ++i) {
					Log.v(TAG,
							"" + allThreadNum.get(i) + "->"
									+ ptidMap.get(allThreadNum.get(i)));
				}
			} else {
				Log.v(TAG, "save failed!!!");
			}

			Log.v(TAG, "1sender");
			JsonSender sender = new JsonSender();
			Log.v(TAG, "2before login");
			sender.login();
			Log.v(TAG, "3logined");

			for (int i = 0; i < allThreadNum.size(); ++i) {
				// Log.v(TAG,""+i+":----GETPIDMAP------"+allThreadNum.get(i)+"-----");
				packThreadResultToJSON(allThreadNum.get(i), sender);
			}
			Log.v(TAG, "before destroy()");
			destroy();
			Log.v(TAG, "destroyed!!!");
		}

	}

	/**
	 * 销毁函数 先销毁生成的目录文件/data/local/a 同样需要销毁/data/local/strace/文件夹^-^
	 */
	public void destroy() {
		Process process = null;
		DataOutputStream os = null;
		DataInputStream is = null;
		try {
			process = Runtime.getRuntime().exec("su");
			os = new DataOutputStream(process.getOutputStream());
			is = new DataInputStream(process.getInputStream());
			Thread.sleep(1000);
			os.writeBytes("rm /data/local/a\n");
			os.flush();
			os.writeBytes("rm -r /data/local/strace\n");
			os.flush();
			// Log.v(TAG, "/data/local/a destroyed!!!");
			os.writeBytes("exit\n");
			os.flush();
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
				// process.destroy();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	/**
	 * 将每个线程的strace结果打包JSON
	 */
	public void packThreadResultToJSON(String tid, JsonSender js) {
		File file = new File("" + fileDir + "a." + tid);
		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(file));
			String tString = null;
			StraceJSON tStraceJSON = new StraceJSON();
			System.out.println("ok");
			while ((tString = reader.readLine()) != null) {
				Log.v(TAG, tString);
				/**
				 * 先排除特殊情况: +++ SIG KILL +++ <unfinished ...> --- {sig ...} ---
				 */
				// if
				// (tString.contains("+++")||tString.contains("unfinished")||tString.contains("---"))
				// {
				// Log.v(TAG,tString);
				// Log.e("strace", "LAST LINE!!!");
				// } else {
				++count;
				tStraceJSON.reset();
				tStraceJSON.number = "" + count;

				String[] tSplit = tString.split(" ", 2);
				tStraceJSON.time = tSplit[0];
				if (tSplit.length < 2)
					break;
				tSplit = tSplit[1].split("\\(", 2);
				tStraceJSON.name = tSplit[0];
				if (tSplit.length < 2)
					break;
				tSplit = tSplit[1].split("\\)", 2);
				tStraceJSON.context = tSplit[0];
				if (tSplit.length < 2)
					break;
				tSplit = tSplit[1].split("\\s+", 3);
				if (tSplit.length < 3)
					break;
				tStraceJSON.result = tSplit[2];

				tStraceJSON.processID = mPid;
				tStraceJSON.threadID = tid;
				tStraceJSON.FatherThreadIdofAPI = ptidMap.get(tid);
				tStraceJSON.show();

				js.publishStrace(tStraceJSON);
			}
			// }
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e1) {
				}
			}
		}
	}

	/**
	 * 在线程号为tid的结果文件中扫描clone，填充进程-父进程映射表ptidMap
	 * 
	 * @param tid
	 */
	public void getPTIDMap(String tid) {
		File file = new File("" + fileDir + "a." + tid);
		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(file));
			String tString = null;
			// int num = 1;
			// System.out.println("ok");
			while ((tString = reader.readLine()) != null) {
				if (tString.contains("clone")) {
					// Log.v(TAG, tString);
					String[] tSplit = tString.split("\\s+");
					// 排除clone信息是最后一行且不完整的情况
					if (tSplit.length < 5)
						continue;
					// Log.v(TAG,""+tSplit.length);
					// Log.v(TAG, tSplit[4]);
					ptidMap.put(tSplit[4], tid);
					// Log.v(TAG,
					// "getit-----------"+tSplit[4]+"-->"+ptidMap.get(tSplit[4]));

					// System.out.println(""+num+":"+tSplit[4]);
					// num++;
				}
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e1) {
				}
			}
		}
	}

	/**
	 * 将所有捕获到的线程号填充allThreadNum数组
	 */
	public boolean saveTIDsToArray() {
		File file = new File("/data/local/a");
		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(file));
			String tString = null;
			while ((tString = reader.readLine()) != null) {
				Log.v(TAG, tString);
				allThreadNum.add(tString.substring(2));
			}
			reader.close();
		} catch (IOException e) {
			Log.v(TAG, "read file a failed!!!");
			e.printStackTrace();
			return false;
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e1) {
				}
			}
		}
		return true;
	}

	/**
	 * 将捕获到的信息文件全部提权到755以便可读 由于用输入输出流ls获取所有结果文件会阻塞，所以将ls结果输出到文件
	 * 集合这些函数一体的原因是它们都需要用到shell命令
	 */
	public void chgModandGetTIDsToFile() {
		Process process = null;
		DataOutputStream os = null;
		DataInputStream is = null;
		try {
			process = Runtime.getRuntime().exec("su");
			os = new DataOutputStream(process.getOutputStream());
			is = new DataInputStream(process.getInputStream());
			Thread.sleep(3000);
			// 将strace的结果文件提权，以便今后读取
			os.writeBytes("chmod -R 755 " + fileDir + "*\n");
			Log.v(TAG, "chmod -R 755 " + fileDir + "*\n");
			os.flush();
			// 将ls结果输出到文件a
			os.writeBytes("ls /data/local/strace >> /data/local/a\n");
			Log.v(TAG, "ls /data/local/strace >> /data/local/a\n");
			os.flush();
			// 将a文件提权，以便今后读取
			os.writeBytes("chmod 755 /data/local/a\n");
			Log.v(TAG, "chmod 755 /data/local/a\n");
			os.flush();
			os.writeBytes("exit\n");
			os.flush();
			Thread.sleep(1000);
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
				// process.destroy();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
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
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return pid;
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
        		String[] splitFactors = each.split("\\s+");
        		packageNameList.add(splitFactors[8]);
        		sPackageNameMap.put(Integer.valueOf(splitFactors[1]), splitFactors[8]);
        	}
        }
        return packageNameList;
    }
}
