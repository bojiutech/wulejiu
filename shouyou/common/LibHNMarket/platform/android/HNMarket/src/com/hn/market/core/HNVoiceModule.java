/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/

package com.hn.market.core;
import com.hn.market.base.Method;
import com.hn.market.base.Module;

public class HNVoiceModule extends Module {
	private static final String TAG = HNVoiceModule.class.getSimpleName();
	
	//private static final int PLAY_AUDIO = 0;
	
	private static HNVoiceModule _voiceModule = null;
	
	//private String _palyAudioCallback = "";

	public static HNVoiceModule getInstance() {
		if (_voiceModule == null) {
			synchronized (HNVoiceModule.class) {
				if (_voiceModule == null) {
					_voiceModule = new HNVoiceModule();
				}
			}
		}
		return _voiceModule;
	}

	public HNVoiceModule() {
		super("hnvoice");
		Register("startRecord",new StartRecord());
		Register("stopRecord",new StopRecord());
		Register("playAudio",new PlayAudio());
		Register("cancelRecord",new CancelRecord());
	}
	
	public class StartRecord implements Method {

		@Override
		public String Execute(String args, String callBack) {
			
			RecordTools recordTools=RecordTools.getInstance(activity);
			recordTools.startRecoderd();
			return "";
		}
	}
	
	public class StopRecord implements Method {

		@Override
		public String Execute(final String args, String callBack) {
			RecordTools recordTools=RecordTools.getInstance(activity);
			String audio = recordTools.stopRecordAndReturn();
			return audio;
		}
	}
	
	public class PlayAudio implements Method {

		@Override
		public String Execute(final String args, String callback) {
			RecordTools recordTools=RecordTools.getInstance(activity);
			RecordTools.result = args;
			recordTools.playRecoderd(RecordTools.result, callback);
			
			return "";
		}
	}
	
	public class CancelRecord implements Method {

		@Override
		public String Execute(final String args, String callBack) {
			// TODO Auto-generated method stub
			RecordTools recordTools=RecordTools.getInstance(activity);
			recordTools.cancleRecord();
			return "";
		}
	}
}


