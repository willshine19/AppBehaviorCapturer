
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

import com.lwl.utils.AppTimeTestUtils;
import com.lwl.utils.AppToHookerTimeTestUtils;
import com.lwl.utils.HookerTimeTestUtils;

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
                executorService.execute(new Handler(context,socket));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

}

class Handler implements Runnable {
    

    
    private Socket socket;
    private Context context;
    
    HookerTimeTestUtils hookerTimeUtils = HookerTimeTestUtils.getInstance();
    AppTimeTestUtils appTimeUtils = AppTimeTestUtils.getInstance();
    AppToHookerTimeTestUtils appToHooker = AppToHookerTimeTestUtils.getInstance();

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
           
//       WriteTimeToFileThread writeFile = new WriteTimeToFileThread(context,timeUtils);
//       writeFile.start();
        System.out.println("socket begins reveiving data");
        try {
            System.out.println("New connection accepted " + socket.getInetAddress() + ":"
                    + socket.getPort());
            BufferedReader br = getReader(socket);
//            PrintWriter pw = getWriter(socket);
            int receive_msg_line_number = 0;
            int json_receive_number = 0;
            while ((msg = new String(br.readLine())) != null) {
                System.out.println(msg);
                jsonStringBuffer = jsonStringBuffer.append(msg);
                //用于解析json，6行一个json
                ++count;
                //用于时间测试
                receive_msg_line_number++;
//                pw.println(echo(msg));
                //当接收到指定数量的json包后，不再接收数据
                if (count % 6 == 0 && json_receive_number < hookerTimeUtils.CESHI_NUMBER) {
                    // add for time test
                    hookerTimeUtils.setT3ReceiveTime();
//                    System.out.println("[time test] start time is " +
//                            timeUtils.setT3ReceiveTime());
                    jsonString = jsonStringBuffer.substring(4, jsonStringBuffer.length());
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
                if (receive_msg_line_number > (HookerTimeTestUtils.CESHI_NUMBER * 6 + 1) && count % 6 == 0){
                    jsonString = jsonStringBuffer.substring(4, jsonStringBuffer.length());
                    JSONObject json = new JSONObject(jsonString);
                    //解析json中的数据，并存入AppTimeUtils中
                    appTimeUtils.parseTimeFromJson(json);
                    //解析获取App到Hooker的网络时延，精确到毫秒，即t3-t2
                    appToHooker.setT3T2Subtract();
                    //计算t3-t2的平均时延，并存储
                    appToHooker.calculateAvgT3T2Subtract();
                    //需要写解析数据的逻辑
//                    while(true){}
                    // writeFile.writeFlags = true;
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
