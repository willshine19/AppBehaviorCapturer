package com.example.ratest;

import java.util.Random;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.android.internal.telephony.SocketServer;
import com.android.internal.telephony.SocketClient;

public class MainActivity extends Activity {
	public static String[] api_name = { "Activity.onCreate()",
			"Activity.onRestart()", "Activity.onStart()",
			"Activity.onResume()", "Activity.onPause()", "Activity.onStop()",
			"Activity.onDestroy()", "Thread.start()", "Thread.run()",
			"Android.media.MediaRecorder.start()",
			"Android.media.MediaRecorder.prepare()",
			"Android.media.MediaRecorder.release()",
			"Android.media.AudioRecord.read()",
			"Android.media.AudioRecord.startRecording()",
			"Android.hardware.Camera.open()", "MediaRecorder.start()",
			"sensorManager.getDefaultSensor()", "ContentResolver.insert()",
			"ContentResolver.query()", "ContentResolver.delate()",
			"ContentResolver.update()", "SmsMessage.getMessageBody()",
			"TelephonyManager.getCallState()",
			"TelephonyManager.getDeviceId()",
			"TelephonyManager.getLine1Number()",
			"TelephonyManager.getSimSerialNumber()",
			"TelephonyManager.getSubscriberId()",
			"locationManager.addGpsStatusListener()",
			"locationManager.getLastKnownLocation()",
			"locationManager.requestLocationUpdates()",
			"Java.io.FileInputStream.read()",
			"Java.io.FileInputStream.close()",
			"Java.io.FileInputStream.getFD()",
			"Java.io.FileOutputStream.close()",
			"Java.io.FileOutputStream.write()", "SmsManager.SendDataMessage()",
			"SmsManager.sendMultipartTextMessage()",
			"SmsManager.sendTextMessage()", "Itelephony.call()",
			"Itelephony.endCall()",
			"Android.bluetooth.BluetoothAdapter.disable()",
			"Android.bluetooth.BluetoothAdapter.enable()",
			"Java.net.socket.Socket()", "Java.net.socket.close()",
			"Java.net.URL.openConnection()",
			"org.apache.http.client.methods.HttpGet.HttpGet()",
			"org.apache.http.client.methods.HttpPost.HttpPost()",
			"Android.net.wifi.disconnect()",
			"Android.net.wifi.enableNetwork()",
			"Android.net.wifi.setWifiEnabled()" };

	public static final int _Activity_onCreate = 1;
	public static final int _Activity_onRestart = 2;
	public static final int _Activity_onStart = 3;
	public static final int _Activity_onResume = 4;
	public static final int _Activity_onPause = 5;
	public static final int _Activity_onStop = 6;
	public static final int _Activity_onDestroy = 7;
	public static final int _Thread_start = 8;
	public static final int _Thread_run = 9;
	public static final int _Android_media_MediaRecorder_start = 10;
	public static final int _Android_media_MediaRecorder_prepare = 11;
	public static final int _Android_media_MediaRecorder_release = 12;
	public static final int _Android_media_AudioRecord_read = 13;
	public static final int _Android_media_AudioRecord_startRecording = 14;
	public static final int _Android_hardware_Camera_open = 15;
	public static final int _MediaRecorder_start = 16;
	public static final int _sensorManager_getDefaultSensor = 17;
	public static final int _ContentResolver_insert = 18;
	public static final int _ContentResolver_query = 19;
	public static final int _ContentResolver_delate = 20;
	public static final int _ContentResolver_update = 21;
	public static final int _SmsMessage_getMessageBody = 22;
	public static final int _TelephonyManager_getCallState = 23;
	public static final int _TelephonyManager_getDeviceId = 24;
	public static final int _TelephonyManager_getLine1Number = 25;
	public static final int _TelephonyManager_getSimSerialNumber = 26;
	public static final int _TelephonyManager_getSubscriberId = 27;
	public static final int _locationManager_addGpsStatusListener = 28;
	public static final int _locationManager_getLastKnownLocation = 29;
	public static final int _locationManager_requestLocationUpdates = 30;
	public static final int _Java_io_FileInputStream_read = 31;
	public static final int _Java_io_FileInputStream_close = 32;
	public static final int _Java_io_FileInputStream_getFD = 33;
	public static final int _Java_io_FileOutputStream_close = 34;
	public static final int _Java_io_FileOutputStream_write = 35;
	public static final int _SmsManager_SendDataMessage = 36;
	public static final int _SmsManager_sendMultipartTextMessage = 37;
	public static final int _SmsManager_sendTextMessage = 38;
	public static final int _Itelephony_call = 39;
	public static final int _Itelephony_endCall = 40;
	public static final int _Android_bluetooth_BluetoothAdapter_disable = 41;
	public static final int _Android_bluetooth_BluetoothAdapter_enable = 42;
	public static final int _Java_net_socket_Socket = 43;
	public static final int _Java_net_socket_close = 44;
	public static final int _Java_net_URL_openConnection = 45;
	public static final int _org_apache_http_client_methods_HttpGet_HttpGet = 46;
	public static final int _org_apache_http_client_methods_HttpPost_HttpPost = 47;
	public static final int _Android_net_wifi_disconnect = 48;
	public static final int _Android_net_wifi_enableNetwork = 49;
	public static final int _Android_net_wifi_setWifiEnabled = 50;
	private Button random;
	private Button callSysApi;
	private Button callPrphApi;
	private Button callDataApi;
	private Button callCommApi;
	private TextView testview;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		System.out.println("***** TEST APP start! *****");

		// new MyThread().start();

		testview = (TextView) findViewById(R.id.api_name);
		random = (Button) findViewById(R.id.api_ra);
		callSysApi = (Button) findViewById(R.id.call_sys_api);
		callPrphApi = (Button) findViewById(R.id.call_prph_api);
		callDataApi = (Button) findViewById(R.id.call_data_api);
		callCommApi = (Button) findViewById(R.id.call_comm_api);
		random.setOnClickListener(listener);
		callSysApi.setOnClickListener(listener);
		callPrphApi.setOnClickListener(listener);
		callDataApi.setOnClickListener(listener);
		callCommApi.setOnClickListener(listener);

		/*
		 * random.setOnClickListener(new View.OnClickListener() {
		 * 
		 * @Override public void onClick(View v) { try{
		 * System.out.println("begin random ");
		 * 
		 * // Intent intent = new
		 * Intent(MainActivity.this,SecondActivity.class); //
		 * startActivity(intent); // Thread.sleep(50000); // while(i<=49){ int i
		 * = ApiRandom(); String name = api_name[i]; testview.setText(name);
		 * DoApi(i); // i++;
		 * System.out.println("---------------------------------------- "); //
		 * Thread.sleep(2000);
		 * System.out.println("888888888888888*****************8 "); // }
		 * 
		 * } catch (Exception e) { e.printStackTrace(); // Log.e("Error",
		 * e.getMessage()); } } });
		 */
	}

	private OnClickListener listener = new OnClickListener() {

		@Override
		public void onClick(View v) {
			Button btn = (Button) v;
			switch (btn.getId()) {
			case R.id.api_ra: // 点击随机调用
				try {
					int i = ApiRandom();
					System.out.println("[1] start to call No." + i + " api !");
					String name = api_name[i];
					testview.setText(name);
					System.out.println("[2] calling " + name);
					callApi(i);
					System.out.println("[3] the end of random calling !");
				} catch (Exception e) {
					e.printStackTrace();
					// Log.e("Error", e.getMessage());
				}
				break;
			case R.id.call_sys_api:
				callApi(6);
				callApi(8);
				Toast.makeText(MainActivity.this, "已完成对系统api的调用",
						Toast.LENGTH_LONG).show();
				break;
			case R.id.call_prph_api:
				callApi(11);
				callApi(13);
				callApi(14);
				callApi(15);
				callApi(16);
				Toast.makeText(MainActivity.this, "已完成对外设api的调用",
						Toast.LENGTH_LONG).show();
				break;
			case R.id.call_data_api:
/*				callApi(20);
				callApi(21);
				callApi(26);*/
				callApi(_locationManager_getLastKnownLocation);
				callApi(_Java_io_FileInputStream_read);
				Toast.makeText(MainActivity.this, "已完成对数据api的调用",
						Toast.LENGTH_LONG).show();
				break;
			case R.id.call_comm_api:
//				callApi(_SmsManager_SendDataMessage);
				callApi(_Itelephony_call);
//				callApi(41);
//				callApi(43);
//				callApi(44);
//				callApi(46);
//				callApi(49);
				Toast.makeText(MainActivity.this, "已完成对通信api的调用",
						Toast.LENGTH_LONG).show();
				break;
			}
		}
	};

	public void callApi(int name) {
		name++;// 把0-49转为1-50
		switch (name) {
		case _Activity_onCreate:
		case _Activity_onRestart:
		case _Activity_onStart:
		case _Activity_onResume:
		case _Activity_onPause:
		case _Activity_onStop:
		case _Activity_onDestroy:
			Intent intent = new Intent(MainActivity.this, SecondActivity.class);
			startActivity(intent);
			break;

		case _Thread_start:
		case _Thread_run:
			new Thread() {
				public void run() {
					Log.i("TEST APP", "[9] java.lang.Thread run");
				}
			}.start();
			Log.i("TEST APP", "[8] java.lang.Thread start");
			break;

		case _Android_media_MediaRecorder_start:
		case _Android_media_MediaRecorder_prepare:
		case _Android_media_MediaRecorder_release:
			peripherals.doMediaRecorder();
			break;
		case _Android_media_AudioRecord_read:
		case _Android_media_AudioRecord_startRecording: {
			peripherals.doAudioRecord();
		}
			break;
		case _Android_hardware_Camera_open: {
			peripherals.doCamera();
		}
			break;
		case _MediaRecorder_start: {// 视频
			peripherals.doMediaRecorder2();
		}
			break;
		case _sensorManager_getDefaultSensor: {
			peripherals.dosensorManager(this);
		}
			break;

		case _ContentResolver_insert:
		case _ContentResolver_query:
		case _ContentResolver_delate:
		case _ContentResolver_update: {
			// 实验室的测试机会闪退
			data.doContentResolver(this);
		}
			break;

		case _SmsMessage_getMessageBody: {
			data.doSmsMessage();
		}
			break;

		case _TelephonyManager_getCallState:
		case _TelephonyManager_getDeviceId:
		case _TelephonyManager_getLine1Number:
		case _TelephonyManager_getSimSerialNumber:
		case _TelephonyManager_getSubscriberId: {
			data.doTelephonyManager(this);
		}
			break;

		case _locationManager_addGpsStatusListener:
		case _locationManager_getLastKnownLocation:
		case _locationManager_requestLocationUpdates: {
			data.dolocationManager(this);
		}
			break;
		case _Java_io_FileInputStream_read:
		case _Java_io_FileInputStream_close:
		case _Java_io_FileInputStream_getFD:
		case _Java_io_FileOutputStream_close:
		case _Java_io_FileOutputStream_write: {
			data.doio(this);
		}
			break;

		case _SmsManager_SendDataMessage:
		case _SmsManager_sendMultipartTextMessage:
		case _SmsManager_sendTextMessage: {
			// 可以发送短息，先关掉，节省话费
			 Communication.doSmsMessager();
		}
			break;
		case _Itelephony_call:
		case _Itelephony_endCall: {
			// 可以进入通话状态
			 Communication.doItelephony(this);
		}
			break;
		case _Android_bluetooth_BluetoothAdapter_disable:
		case _Android_bluetooth_BluetoothAdapter_enable: {
			Communication.doBluetoothAdapter();
		}
			break;
		case _Java_net_socket_Socket:
		case _Java_net_socket_close: {
			// 这部分有问题，会报异常
			// SocketClient client = new SocketClient("127.0.0.1", 12345);
			// client.sendMsg("nimei1");
			// client.closeSocket();
			// Log.v("Socket", "Socket is ok");

			Communication.dosocket();
		}
			break;

		case _Java_net_URL_openConnection: {
			Communication.doURL();
		}
			break;

		case _org_apache_http_client_methods_HttpGet_HttpGet:
		case _org_apache_http_client_methods_HttpPost_HttpPost: {
			Communication.doHttp();
		}
			break;
		case _Android_net_wifi_disconnect:
		case _Android_net_wifi_enableNetwork:
		case _Android_net_wifi_setWifiEnabled: {
			Communication.dowifi(this);
		}
			break;

		}
	}

	// 返回一个随机数， 该随机数用于api数组的序号api_name[r];
	public int ApiRandom() {
		Random random = new Random();
		int ret = random.nextInt(49);
		Log.v("apiname", api_name[ret]);
		return ret;
	}

	class MyThread extends Thread {
		@Override
		public void run() {
			SocketServer server = new SocketServer(12345);
			server.beginListen();
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void onStart() {
		super.onStart();
		Log.i("TEST APP", "[3] android.app.Activity onStart");
	}

	@Override
	public void onRestart() {
		super.onRestart();
		Log.i("TEST APP", "[2] android.app.Activity onRestart");
	}

	@Override
	public void onPause() {
		super.onPause();
		Log.i("TEST APP", "[5] android.app.Activity onPause");
	}

	@Override
	public void onStop() {
		super.onStop();
		Log.i("TEST APP", "[6] android.app.Activity onStop");
	}

}
