
package com.lwl.service;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.*;

import org.json.JSONArray;
import org.json.JSONObject;

public class MultiThreadJsonReceiveThread {
    private int port = 8821;
    private ServerSocket serverSocket;
    private Socket socket = null;
    private ExecutorService executorService;// 线程池
    private final int POOL_SIZE = 5;// 单个CPU线程池大小
    JSONArray jsonArray;

    public MultiThreadJsonReceiveThread() throws IOException {
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
                executorService.execute(new Handler(socket));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

}

class Handler implements Runnable {
    private Socket socket;

    public Handler(Socket socket) {
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
        try {
            System.out.println("New connection accepted " + socket.getInetAddress() + ":"
                    + socket.getPort());
            SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss:SS");// 设置日期格式
            System.out.println(df.format(new Date()));
            
            BufferedReader br = getReader(socket);
            PrintWriter pw = getWriter(socket);
            while ((msg = new String(br.readLine())) != null) {
                System.out.println(msg);
                jsonStringBuffer = jsonStringBuffer.append(msg);
//                System.out.println(jsonStringBuffer.toString());
                ++count;
//                pw.println(echo(msg));
                if(count%6 == 0){
                    jsonString = jsonStringBuffer.substring(4, jsonStringBuffer.length());
//                    System.out.println(jsonString);
                    JSONObject json = new JSONObject(jsonString);
                    System.out.println(json.get("name"));
//                    System.out.println(json.toString());
                    jsonStringBuffer.delete(4, jsonStringBuffer.length());
                    count = 0;
                }
            }
            System.out.println(df.format(new Date()));
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
    }
}
