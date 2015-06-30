package com.android.internal.telephony;

import java.io.*;
import java.net.*;

import android.util.Log;

public class SocketServer {
	ServerSocket sever;
	     public SocketServer(int port){
	         try{
	             sever = new ServerSocket(port);
	         }catch(Exception e){
	        	 Log.v("Socket", "Socket is wrong1");
	             e.printStackTrace();
	         }
	     }
	     public void beginListen(){
	         while(true){
	             try{
	                 final Socket socket = sever.accept();
	                 
	                 new Thread(new Runnable(){
	                     public void run(){
	                         BufferedReader in;
	                         try{
	                             in = new BufferedReader(new InputStreamReader(socket.getInputStream(),"UTF-8"));
	                             PrintWriter out = new PrintWriter(socket.getOutputStream());
	                             while (!socket.isClosed()){
	                                 String str;
	                                 str = in.readLine();
	                                 out.println("Hello!world!! " + str);
	                                 out.flush();
	                                 if (str == null || str.equals("end"))
	                                     break;
	                                 System.out.println(str);
	                             }
	                             socket.close();
	                         }catch(Exception e){
	                        	 Log.v("Socket", "Socket is wrong2");
	                             e.printStackTrace();
	                         }
	                     }
	                 }).start();
	             }catch(Exception e){
	            	 Log.v("Socket", "Socket is wrong3");
	                 e.printStackTrace();
	             }
	         }
	     }
	 }