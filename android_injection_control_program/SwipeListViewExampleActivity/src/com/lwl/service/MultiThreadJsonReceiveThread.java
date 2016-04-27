package com.lwl.service;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.telephony.TelephonyManager;
import android.util.Log;

import com.android.swipelistview.sample.adapters.PackageAdapter;
import com.lwl.utils.AppTimeTestUtils;
import com.lwl.utils.AppToHookerTimeTestUtils;
import com.lwl.utils.HookerTimeTestUtils;
import com.lwl.utils.ServerToHookerTimeTestUtils;
import com.syh.pubjson.JsonSender;

/**
 * 接收jni层的json字符串，向服务器端发送json字符串 用到了线程池， 用于开启新的线程
 */
public class MultiThreadJsonReceiveThread {

	private static final int port = 8821;
	private ServerSocket serverSocket;
	private Socket socket = null;
	private ExecutorService executorService;// 线程池
	private final int POOL_SIZE = 15;// 单个CPU线程池大小
	private Context context;

	JSONArray jsonArray;

	/**
	 * 构造函数
	 */
	public MultiThreadJsonReceiveThread(Context context) throws IOException {
		this.context = context;
		if (serverSocket == null) {
			serverSocket = new ServerSocket(port);
		}

		// Runtime的availableProcessor()方法返回当前系统的CPU数目.
		executorService = Executors.newFixedThreadPool(POOL_SIZE);
	}

	/**
	 * 一旦接收到客户端的socket请求就开启一个线程（通过线程池），可以有多个客户端同时接入
	 */
	public void startThead() {
		while (true) {
			try {
				// 阻塞线程，等待客户连接。只要客户进行了连接,就会触发accept();从而建立连接
				socket = serverSocket.accept();
				// 用线程池 开启新的线程
				executorService.execute(new ReceiveAndPub(context, socket));
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * 内部类
	 * 新线程的执行逻辑
	 */
	class ReceiveAndPub implements Runnable {
		
		private Socket mSocket;
		private Context mContext;
		
		private static final String TAG = "MultiThreadJsonReceiveThread";
		
		/**
		 * 构造函数
		 */
		public ReceiveAndPub(Context context, Socket socket) {
			this.mContext = context;
			this.mSocket = socket;
		}
		
		private PrintWriter getWriter(Socket socket) throws IOException {
			OutputStream socketOut = socket.getOutputStream();
			return new PrintWriter(socketOut, true);// 每条不会删除，继续写
		}
		
		private BufferedReader getReader(Socket socket) throws IOException {
			InputStream socketIn = socket.getInputStream();
			return new BufferedReader(new InputStreamReader(socketIn));// 字节流的管道流，可读ajskaoiw
		}
		
		public String echo(String msg) {
			return "echo:" + msg;
		}
		
		public void run() {
			// WriteTimeToFileThread writeFile = new WriteTimeToFileThread(context);
			// writeFile.start();
			
			try {
				BufferedReader br = getReader(mSocket);
				
				JsonSender sender = new JsonSender();
				sender.login(); // login服务器
//			sender.subscribe(); // 订阅
				
				int receivedCount = 0;
				String receivedLine;
				StringBuilder builder = new StringBuilder();
				while ((receivedLine = br.readLine()) != null) {
//					Log.v(TAG, "从jni层接受到的单行：" + receivedLine);
					builder = builder.append(receivedLine);
					if (receivedLine.equals("}")) {
						// 一个json字符串 接收完毕
						String jsonString = builder.toString();
						builder.delete(0, builder.length());
						JSONObject json = completeJson(new JSONObject(jsonString));
						Log.i(TAG, "[+] 成功从【jni层】接收到第" + ++receivedCount + "组行为【记录数据】");
						Log.i(TAG, json.toString());
						sender.publish(json);
						// sender.saveToFile(json);
						continue;
					}
				} // while
//			sender.logout();
			} catch (Exception e) {
				e.printStackTrace();
			} finally {
				try {
					if (mSocket != null)
						mSocket.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		
		/**
		 * 加工json，在json中加入IMEI和app包名信息
		 * @param jsonObject
		 * @return
		 */
		private JSONObject completeJson(JSONObject jsonObject) {
			TelephonyManager tm = (TelephonyManager) mContext
					.getSystemService(Context.TELEPHONY_SERVICE);
			try {
				jsonObject.put("IMEI", tm.getDeviceId());
				jsonObject.put("packageName", PackageAdapter.sPackageName);
			} catch (JSONException e) {
				e.printStackTrace();
			}
			return jsonObject;
		}
	}
}

