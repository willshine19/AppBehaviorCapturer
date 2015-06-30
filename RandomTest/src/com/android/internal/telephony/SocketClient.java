package com.android.internal.telephony;

import java.io.*;
import java.net.*;

import android.util.Log;

public class SocketClient {
     static Socket client;

     public SocketClient(String site, int port){
         try{
             client = new Socket(site,port);
         }catch (UnknownHostException e){
        	 Log.v("Socket", "Socket is wrong4");
             e.printStackTrace();
         }catch (IOException e){
        	 Log.v("Socket", "Socket is wrong5");
             e.printStackTrace();
         }
     }
        
    public String sendMsg(String msg){
         try{
             BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
             PrintWriter out = new PrintWriter(client.getOutputStream());
             out.println(msg);
             out.flush();
             return in.readLine();
         }catch(Exception e){
        	 Log.v("Socket", "Socket is wrong6");
             e.printStackTrace();
         }
         return "";
     }
     public void closeSocket(){
         try{
             client.close();
         }catch(Exception e){
        	 Log.v("Socket", "Socket is wrong7");
             e.printStackTrace();
         }
     }
     public static void main(String[] args) throws Exception{
         
     }
 
 }
