package com.lwl.service;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.*;
import java.util.concurrent.*;
import org.json.JSONArray;
import org.json.JSONObject;

import android.content.Context;
import android.telephony.TelephonyManager;
import android.util.Log;

import com.lwl.utils.AppTimeTestUtils;
import com.lwl.utils.AppToHookerTimeTestUtils;
import com.lwl.utils.HookerTimeTestUtils;
import com.lwl.utils.ServerToHookerTimeTestUtils;
import com.lwl.utils.TimeTestUtils;
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
			// serverSocket = new ServerSocket(8000, -1,
			// InetAddress.getByName("127.0.0.1"));
		}

		// Runtime的availableProcessor()方法返回当前系统的CPU数目.
		executorService = Executors.newFixedThreadPool(POOL_SIZE);
	}

	/**
	 * 为什么要加while循环？
	 */
	public void startThead() {
		while (true) {
			try {
				// 阻塞线程，等待客户连接。只要客户进行了连接,就会触发accept();从而建立连接
				socket = serverSocket.accept();
				// 用线程池 开启新的线程
				executorService.execute(new Handler(context, socket));
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}

/**
 * 实现Runnable，用于开启新线程
 */
class Handler implements Runnable {

	private Socket socket;
	private Context context;
	private static final String TAG = "MultiThreadJsonReceiveThread";
	/** 从allhookinone中发来的一条json字符串（行为采集），占几行 */
	private static final int JSON_STRING_LINE_SIZE = 11;
	/** 从allhookinone中发来的一条json字符串（时间），占几行 */
	private final int JSON_STRING_TIMETESE_LINE_SIZE = 6;

	AppTimeTestUtils appTimeUtils = AppTimeTestUtils.getInstance();
	AppToHookerTimeTestUtils appToHooker = AppToHookerTimeTestUtils
			.getInstance();
	HookerTimeTestUtils hookerTimeUtils = HookerTimeTestUtils.getInstance();
	ServerToHookerTimeTestUtils serverToHooker = ServerToHookerTimeTestUtils
			.getInstance();

	/**
	 * 构造函数
	 */
	public Handler(Context context, Socket socket) {
		this.context = context;
		this.socket = socket;
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

	/**
	 * 线程执行体
	 */
	public void run() {
		// WriteTimeToFileThread writeFile = new WriteTimeToFileThread(context);
		// writeFile.start();

		try {
			BufferedReader br = getReader(socket);
			TelephonyManager tm = (TelephonyManager) context
					.getSystemService(Context.TELEPHONY_SERVICE);

			JsonSender sender = new JsonSender();
			sender.login(); // login服务器
//			sender.subscribe(); // 订阅
			// 发送第一条JSON数据，指定内容
			sender.pubFirstData(tm.getDeviceId());

			// 接受到的行数的总数
			int receivedLineNum = 0;
			// 已接受到的完整json字符串(行为记录)的总数
			int receivedJsonStringNum = 0;
			// 已接受到的完整json字符串(时间测试)的总数
			int receivedTimeTestJsonStringNum = 0;

			String receivedLine;
			StringBuffer jsonStringBuffer = new StringBuffer();

			// 线程阻塞 等待jni层发送json，由三个if块组成
			while ((receivedLine = br.readLine()) != null) {
				Log.v(TAG, "从jni层接受到的单行：" + receivedLine);
				// 拼接字符串
				jsonStringBuffer = jsonStringBuffer.append(new String(
						receivedLine));
				// 用于解析json，7行一个json
				receivedLineNum++;

				// 接收完一个完整的json字符串，发送出去
				if (receivedLineNum % JSON_STRING_LINE_SIZE == 0
						&& receivedJsonStringNum < TimeTestUtils.CESHI_NUMBER) {
					hookerTimeUtils.setT3ReceiveTime(); // 打时间戳
					receivedLineNum = 0;

					String jsonString = jsonStringBuffer.toString();
					jsonStringBuffer.delete(0, jsonStringBuffer.length());

					// 转为Json对象
					JSONObject json = new JSONObject(jsonString);
					// 加一组信息
					json.put("IMEI", tm.getDeviceId());
					sender.publish(json);
					// Log.e("what's in json", "" + json);
//					 sender.saveToFile(json);

					receivedJsonStringNum++;
					Log.i(TAG, "[+] 成功从【jni层】接收到第" + receivedJsonStringNum
							+ "组行为【记录数据】");
					Log.i(TAG,  json.toString());

					hookerTimeUtils.setT4SendTime(); // 打时间戳
					continue;
				}

				// 开始接受timetest测试数据，接收完一组解析并保存结果
				if (receivedLineNum % JSON_STRING_TIMETESE_LINE_SIZE == 0
						&& receivedTimeTestJsonStringNum < TimeTestUtils.CESHI_NUMBER
						&& receivedJsonStringNum == TimeTestUtils.CESHI_NUMBER) {
					receivedLineNum = 0;
					String jsonString = jsonStringBuffer.toString();
					jsonStringBuffer.delete(0, jsonStringBuffer.length());
					JSONObject json = new JSONObject(jsonString);
					// 解析json中的t1,t2数据，并存入AppTimeUtils中
					appTimeUtils.parseTimeFromJson(json);
					receivedTimeTestJsonStringNum++;
					Log.i(TAG, "[+] 成功从【jni层】接收到第"
							+ receivedTimeTestJsonStringNum + "组【time test 数据】");
				}

				// 接收完Json字符串（时间测试数据），计算
				if (receivedTimeTestJsonStringNum == TimeTestUtils.CESHI_NUMBER) {
					Log.v(TAG, "接受完app(allhookinone)中的时间数据");
					// 解析获取App到Hooker的网络时延，精确到毫秒，即t3-t2
					appToHooker.setT3T2Subtract();
					// 计算t3-t2的平均时延，并存储
					appToHooker.calculateAvgT3T2Subtract();
					// 计算t3,t4时间间隔，并存储
					hookerTimeUtils.setT4T3Subtract();
					// 计算t4-t3平均时延，并存储
					hookerTimeUtils.calculateAvgT4T3Subtract();
					appTimeUtils.print();
					appToHooker.print();
					hookerTimeUtils.print();

					// 等待server端数据完全接收完
					while (serverToHooker.mListCostStr.size() < TimeTestUtils.CESHI_NUMBER - 2
							|| serverToHooker.mValueCostStr.size() < TimeTestUtils.CESHI_NUMBER - 2) {
						Log.v(TAG, "正在等待server端数据的数据...");
						Thread.sleep(5000);
					}

					// 计算网络时延
					serverToHooker.setNetworkDelay();
					// 计算平均网络时延
					serverToHooker.calculateAVGNetworkDelay();
					serverToHooker.print();

					// 通过修改标志位, 唤醒WriteTimeToFileThread线程,可以将所有的时间数据写入文件了
					WriteTimeToFileThread.writeFlags = true;
					return;
				}

			} // while
			socket.close();
//			sender.logout();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				if (socket != null)
					socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		// System.out.println("Exception occurs during receiving data");
	}
}
