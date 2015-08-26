
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
import android.support.v4.util.TimeUtils;
import android.telephony.TelephonyManager;
import android.util.Log;

import com.lwl.utils.AppTimeTestUtils;
import com.lwl.utils.AppToHookerTimeTestUtils;
import com.lwl.utils.HookerTimeTestUtils;
import com.lwl.utils.ServerToHookerTimeTestUtils;
import com.lwl.utils.TimeTestUtils;
import com.syh.pubjson.JsonSender;

public class MultiThreadJsonReceiveThread {
    
    
    private int port = 8821;
    private ServerSocket serverSocket;
    private Socket socket = null;
    private ExecutorService executorService;// 线程池
    private final int POOL_SIZE = 5;// 单个CPU线程池大小
    private Context context;
    
    JSONArray jsonArray;

    public MultiThreadJsonReceiveThread(Context context) throws IOException {
        this.context = context;
        if (serverSocket == null) {
            serverSocket = new ServerSocket(port);
            // serverSocket = new ServerSocket(8000, -1,
            // InetAddress.getByName("127.0.0.1"));
        }
        // serverSocket=new ServerSocket(port);
        // Runtime的availableProcessor()方法返回当前系统的CPU数目.
        executorService = Executors.newFixedThreadPool(POOL_SIZE);
        System.out.println("服务器启动");
    }

	public void service() {
		while (true) {
			try {
				// 接收客户连接,只要客户进行了连接,就会触发accept();从而建立连接
				socket = serverSocket.accept();
				executorService.execute(new Handler(context, socket));
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

}

class Handler implements Runnable {
    private Socket socket;
    private Context context;
    private final int JSON_STRING_LINE_SIZE = 7;

    HookerTimeTestUtils hookerTimeUtils = HookerTimeTestUtils.getInstance();
    AppTimeTestUtils appTimeUtils = AppTimeTestUtils.getInstance();
    AppToHookerTimeTestUtils appToHooker = AppToHookerTimeTestUtils.getInstance();
    ServerToHookerTimeTestUtils serverToHooker = ServerToHookerTimeTestUtils.getInstance();

    public Handler(Context context,Socket socket) {
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

    public void run() {

        StringBuffer jsonStringBuffer = new StringBuffer("Json");
        String msg;
        String jsonString;
        long count = 0;
        
        //用于时间测试
       WriteTimeToFileThread writeFile = new WriteTimeToFileThread(context);
       writeFile.start();
        System.out.println("socket begins reveiving data");
        try {
            System.out.println("New connection accepted " + socket.getInetAddress() + ":"
                    + socket.getPort());
            BufferedReader br = getReader(socket);
//            PrintWriter pw = getWriter(socket);
            
            // syh add
            TelephonyManager tm = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
            JsonSender sender = new JsonSender();
            sender.login();
            sender.subscribe(); //订阅
            // 发送指定内容作为第一条JSON数据
            JSONObject firstData = new JSONObject();
            firstData.put("name", "start");// 待检测数据---对应r=0
            firstData.put("number", "0");
            firstData.put("threadID", "0");
            firstData.put("processID", "0");
            firstData.put("IMEI", tm.getDeviceId());
            firstData.put("time", "0000-00-00 00:00:00:000:000");
            sender.publish(firstData);
            // syh add end
            
            int receive_msg_line_number = 0;
            int json_receive_number = 0;
            int time_test_json_number = 0;
            // 线程阻塞 等待发送json
            while ((msg = new String(br.readLine())) != null) {
                System.out.println(msg);
                jsonStringBuffer = jsonStringBuffer.append(msg);
                //用于解析json，7行一个json
                ++count;
                //用于时间测试
                receive_msg_line_number++;
//                pw.println(echo(msg));
                //当接收到指定数量的json包后，不再接收数据
                if (count % JSON_STRING_LINE_SIZE == 0 && json_receive_number < TimeTestUtils.CESHI_NUMBER) {
                    // add for time test
                    hookerTimeUtils.setT3ReceiveTime();
//                    System.out.println("[time test] start time is " +
//                            timeUtils.setT3ReceiveTime());
                    jsonString = jsonStringBuffer.substring(4, jsonStringBuffer.length());
                    
                    // syh add
                    // 发送 JSON对象
                    JSONObject json = new JSONObject(jsonString);
                    
                    json.put("IMEI", tm.getDeviceId());
                    Log.d("bunengfasong", "看这儿～ " + json);
                    sender.publish(json);
                    // syh add end
                    
//                    JSONObject json = new JSONObject(jsonString);
                    // 输出没有问题
                    // System.out.println(json.get("name"));
                    jsonStringBuffer.delete(4, jsonStringBuffer.length());
                    count = 0;
                    // add for time test
                    hookerTimeUtils.setT4SendTime();
//                    System.out.println("[time test] end time is " +
//                            timeUtils.setT4SendTime());
                    json_receive_number++;
                    // System.out.println("json_receive_number is " +
                    // json_receive_number);
                }
                
                //接收CESHINUMBER组json数据后，接收发送过来的测试数据
                if (receive_msg_line_number > (TimeTestUtils.CESHI_NUMBER * JSON_STRING_LINE_SIZE + 1) && count %  JSON_STRING_LINE_SIZE == 0){
                    jsonString = jsonStringBuffer.substring(4, jsonStringBuffer.length());
                    JSONObject json = new JSONObject(jsonString);
                    //解析json中的t1,t2数据，并存入AppTimeUtils中
                    appTimeUtils.parseTimeFromJson(json);
                    time_test_json_number++;
                    System.out.println("接收到" + time_test_json_number + "组time test 数据");
                }
                
                if(time_test_json_number == TimeTestUtils.CESHI_NUMBER){
                    System.out.println("接受完app中的时间数据");
                    //解析获取App到Hooker的网络时延，精确到毫秒，即t3-t2
                    appToHooker.setT3T2Subtract();
                    //计算t3-t2的平均时延，并存储
                    appToHooker.calculateAvgT3T2Subtract();
                    //计算t3,t4时间间隔，并存储
                    hookerTimeUtils.setT4T3Subtract();
                    //计算t4-t3平均时延，并存储
                    hookerTimeUtils.calculateAvgT4T3Subtract();
                    //等待server端数据完全接收完
                    while (serverToHooker.mListCostStr[TimeTestUtils.CESHI_NUMBER - 2] == null
                            || serverToHooker.mValueCostStr[TimeTestUtils.CESHI_NUMBER - 2] == null) {
                    }
                    // 计算网络时延
                    serverToHooker.setNetworkDelay();
                    // 计算平均网络时延
                    serverToHooker.calculateAVGNetworkDelay();
                    //
//                    while(true){}
                    //写标志位置1
                     WriteTimeToFileThread.writeFlags = true;
                }
            }
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
        System.out.println("Exception occurs during receiving data");
    }
}
