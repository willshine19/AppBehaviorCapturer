package com.example.ratest;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.hardware.Camera;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Environment;
import android.provider.Contacts.People;
import android.util.Log;

public class peripherals {
	// 手机外设，只尝试调用api，没有数据存储，没有长时间运行

	public static void doMediaRecorder() {
		// 录音
		MediaRecorder mRecorder;
		File soundFile;
		try {
			soundFile = new File(Environment.getExternalStorageDirectory()
					.getCanonicalFile() + "/sound.amr");
			mRecorder = new MediaRecorder();
			// 设置录音的声音来源
			mRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
			// 设置录制的声音的输出格式（必须在设置声音编码格式之前设置）
			mRecorder.setOutputFormat(MediaRecorder.OutputFormat.AMR_NB);
			// 设置声音编码的格式
			mRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);
			mRecorder.setOutputFile(soundFile.getAbsolutePath());
			mRecorder.prepare();
			Log.i("TEST APP", "[11] android.media.MediaRecorder prepare");
			// 开始录音
			mRecorder.start();
			Log.i("TEST APP", "[10] android.media.MediaRecorder start");

			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			mRecorder.stop(); // ②
			// 释放资源
			mRecorder.release(); // ③
			Log.i("TEST APP", "[12] android.media.MediaRecorder release");
			// Log.v("MediaRecorder", "MediaRecorder is ok");
			mRecorder = null;
			soundFile.delete();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static void doAudioRecord() {// 录音http://blog.csdn.net/peijiangping1989/article/details/7042610

		int audioSource = MediaRecorder.AudioSource.MIC;
		// 设置音频采样率，44100是目前的标准，但是某些设备仍然支持22050，16000，11025
		int sampleRateInHz = 44100;
		// 设置音频的录制的声道CHANNEL_IN_STEREO为双声道，CHANNEL_CONFIGURATION_MONO为单声道
		int channelConfig = AudioFormat.CHANNEL_IN_STEREO;
		// 音频数据格式:PCM 16位每个样本。保证设备支持。PCM 8位每个样本。不一定能得到设备支持。
		int audioFormat = AudioFormat.ENCODING_PCM_16BIT;
		// 缓冲区字节大小
		int bufferSizeInBytes = 0;
		AudioRecord audioRecord;
		// AudioName裸音频数据文件

		bufferSizeInBytes = AudioRecord.getMinBufferSize(sampleRateInHz,
				channelConfig, audioFormat);
		// bufferSizeInBytes =
		// android.media.AudioRecord.getMinBufferSize(sampleRateInHz,
		// AudioFormat.CHANNEL_CONFIGURATION_MONO,AudioFormat.ENCODING_PCM_16BIT);
		// 创建AudioRecord对象
		if (bufferSizeInBytes < 4096) {
			bufferSizeInBytes = 4096;
		}

		// audioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC,
		// sampleRateInHz,AudioFormat.CHANNEL_CONFIGURATION_MONO,
		// AudioFormat.ENCODING_PCM_16BIT,bufferSizeInBytes);

		audioRecord = new AudioRecord(audioSource, sampleRateInHz,
				channelConfig, audioFormat, bufferSizeInBytes);

		audioRecord.startRecording();
		Log.i("TEST APP", "[14] android.media.AudioRecord startRecording");
		// Log.v("audioRecord", "audioRecord is ok");

		byte[] audiodata = new byte[bufferSizeInBytes];
		int readsize = audioRecord.read(audiodata, 0, bufferSizeInBytes);
		Log.i("TEST APP", "[13] android.media.AudioRecord read");
		audioRecord.stop();
		audioRecord.release();// 释放资源
		audioRecord = null;
	}

	public static void doCamera() {// 拍照
		Camera camera = null;
		camera = Camera.open();
		Log.i("TEST APP", "[15] android.hardware.Camera open");
		//Log.v("camera", "camera is ok");
		camera.release();
		camera = null;
	}

	public static void doMediaRecorder2() {// 视频

		// 创建保存录制视频的视频文件
		File videoFile;
		try {
			videoFile = new File(Environment.getExternalStorageDirectory()
					.getCanonicalFile() + "/testvideo.3gp");
			MediaRecorder mRecorder = new MediaRecorder();
			mRecorder.reset();// 设置从麦克风采集声音(或来自录像机的声音AudioSource.CAMCORDER)
			mRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
			// 设置从摄像头采集图像
			mRecorder.setVideoSource(MediaRecorder.VideoSource.CAMERA);
			// 设置视频文件的输出格式
			// 必须在设置声音编码格式、图像编码格式之前设置
			mRecorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
			// 设置声音编码的格式
			mRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);
			// 设置图像编码的格式
			mRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.H264);
			mRecorder.setVideoSize(1280, 720);
			// 每秒 4帧
			mRecorder.setVideoFrameRate(20);
			mRecorder.setOutputFile(videoFile.getAbsolutePath());
			// 指定使用SurfaceView来预览视频
			mRecorder.prepare();
			// 开始录制
			mRecorder.start();
			Log.i("TEST APP", "[16] android.media.MediaRecorder start");
//			Log.v("MediaRecorder2", "MediaRecorder2 is ok");
			mRecorder.stop();
			// 释放资源
			mRecorder.release();
			mRecorder = null;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public static void dosensorManager(Context context) {// 获得加速度传感器，
		SensorManager sm;
		Sensor aSensor;
		sm = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
		aSensor = sm.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		Log.i("TEST APP", "[17] android.hardware.SensorManager getDefaultSensor");

//		Log.v("SensorManager", "SensorManager is ok");
	}

}
