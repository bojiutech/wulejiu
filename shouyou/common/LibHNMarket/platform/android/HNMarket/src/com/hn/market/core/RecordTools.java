/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/

package com.hn.market.core;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import com.hn.market.base.ResponseArgs;
import com.hn.market.export.GameChannel;

import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.os.Handler;
import android.os.Message;
import android.util.Base64;
import android.util.Log;

public class RecordTools {
	private MediaRecorder mMediaRecorder;
	private MediaPlayer mMediaPlayer;
	private String mPath;
	private Context mContext;
	private static RecordTools recordTools;

	public static String result = "";

	public static RecordTools getInstance(Context mContext) {
		if (recordTools == null) {
			recordTools = new RecordTools(mContext);
		}
		recordTools.mPath = mContext.getApplicationContext().getFilesDir()
				.getAbsolutePath()
				+ "/temp.amr";
		return recordTools;
	}

	public RecordTools(Context mContext) {
		this.mContext = mContext;

	}
	
	public void startRecoderd() {
		//Vibrator vib = (Vibrator) mContext
		//		.getSystemService(Service.VIBRATOR_SERVICE);
		//vib.vibrate(500);

		mMediaRecorder = new MediaRecorder();
	
		mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
	
		// mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.RAW_AMR);
		mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.RAW_AMR);
	
		mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);

		mMediaRecorder.setOutputFile(mPath);
		try {
			mMediaRecorder.prepare();
			mMediaRecorder.start();

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void playRecoderd(String data, final String callback) {
		mMediaPlayer = new MediaPlayer();
		AudioManager am = (AudioManager) mContext.getSystemService(Context.AUDIO_SERVICE);
		final int currentVolume = am.getStreamVolume(AudioManager.STREAM_MUSIC);
		try {
			byte[] buffer = Base64.decode(data, Base64.DEFAULT);
			onWriteFileByByte(mPath, buffer);
			if (mMediaPlayer != null) {
				mMediaPlayer.stop();
			}

			mMediaPlayer.reset();

			mMediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);

			int maxVolume = am.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
			if (currentVolume < maxVolume / 2) {
				int newVolume = (int) (am.getStreamMaxVolume(AudioManager.STREAM_MUSIC) * 0.8);
				am.setStreamVolume(AudioManager.STREAM_MUSIC, newVolume, 2);
			}
			mMediaPlayer.setDataSource(mPath);
			mMediaPlayer.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
						@Override
						public void onPrepared(MediaPlayer mp) {
							mp.start();
						}
					});
			
			mMediaPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {

						@Override
						public void onCompletion(MediaPlayer mp) {
							// TODO Auto-generated method stub
							
							AudioManager amReset = (AudioManager) mContext.getSystemService(Context.AUDIO_SERVICE);							
							amReset.setStreamVolume(AudioManager.STREAM_MUSIC, currentVolume, 2);
							
							// 播放完成回调
							ResponseArgs args = new ResponseArgs(callback, "finish");
							GameChannel.getInstance().notifyResponseChannel(args);
						}
					});
			mMediaPlayer.prepareAsync();

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public String stopRecordAndReturn() {
		String data = "";
		File file = new File(mPath);
		try {
			if (mMediaRecorder != null) {
				mMediaRecorder.stop();
			}

			FileInputStream in = new FileInputStream(file);
			byte[] buffer = new byte[(int) file.length()];
			int length = in.read(buffer);

			// data = Base64.encodeToString(buffer, 0, length, Base64.DEFAULT);
			data = Base64.encodeToString(buffer, Base64.DEFAULT);
			file.delete();
		} catch (Exception e) {

			e.printStackTrace();
		} finally {
			if (mMediaRecorder != null) {
				mMediaRecorder.release();
				mMediaRecorder = null;
			}
			result = data;
			// result = data.substring(10);
			return data;
		}

	}

	public void cancleRecord() {
		// stopRecordAndReturn();
		result = "";
		if (mMediaRecorder != null) {
			mMediaRecorder.stop();
			mMediaRecorder.release();
			mMediaRecorder = null;
		}
		File file = new File(mPath);
		if (file.exists()) {
			file.delete();
		}

	}

	/**
	 * ����byte�����������д���ļ�
	 * 
	 * @param path
	 * @param buffer
	 */
	public static boolean onWriteFileByByte(String mPath, byte[] buffer) {
		FileOutputStream fos = null;
		try {
			fos = new FileOutputStream(mPath);
			fos.write(buffer);
			return true;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (fos != null) {
				try {
					fos.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
				fos = null;
			}
		}
		return false;
	}
}
