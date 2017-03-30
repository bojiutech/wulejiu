#if !defined(BR_ANYCHAT_CORE_SDK_H__INCLUDED_)
#define BR_ANYCHAT_CORE_SDK_H__INCLUDED_

#include <mmsystem.h>
#include <wingdi.h>


/**
 *	AnyChat Core SDK Include File
 */


#pragma once

#include "GVSDK.h"

#define BRAC_API extern "C" __declspec(dllexport)

// ��Ƶͼ���ʽ����
enum BRAC_PixelFormat{
	BRAC_PIX_FMT_RGB24 = 0,						///< Packed RGB 8:8:8, 24bpp, RGBRGB...��MEDIASUBTYPE_RGB24��
	BRAC_PIX_FMT_RGB32,							///< ��Ӧ�ڣ�MEDIASUBTYPE_RGB32��Packed RGB 8:8:8, 32bpp, (msb)8A 8R 8G 8B(lsb), in cpu endianness
	BRAC_PIX_FMT_YV12,							///< ��Ӧ�ڣ�MEDIASUBTYPE_YV12��Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	BRAC_PIX_FMT_YUY2,							///< ��Ӧ�ڣ�MEDIASUBTYPE_YUY2��Packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
};

// ��Ƶ�豸����
enum BRAC_AudioDevice{
	BRAC_AD_WAVEIN = 0,							///< �����豸��Mic
	BRAC_AD_WAVEOUT,							///< ����豸��Wave
};

// ����ģʽ����
#define BRAC_FUNC_VIDEO_CBDATA		0x00000001L	///< ͨ���ص����������Ƶ����
#define BRAC_FUNC_VIDEO_AUTODISP	0x00000002L	///< ��SDK��������Ƶ������Ƶ��ʾ��ָ���Ĵ�����
#define BRAC_FUNC_AUDIO_CBDATA		0x00000004L	///< ͨ���ص����������Ƶ����
#define BRAC_FUNC_AUDIO_AUTOPLAY	0x00000008L	///< ��SDK��������Ƶ��ֱ�Ӳ���
#define BRAC_FUNC_CONFIG_LOCALINI	0x00000010L	///< ���ɱ��������ļ���AnyChatSDK.ini��
#define BRAC_FUNC_FIREWALL_OPEN		0x00000020L	///< ����SDK����Windows����ǽ������ǰӦ�ó���������ǽ�����б�����Windows��ʾ�û��Ƿ���ֹ��ǰӦ�ó���
#define BRAC_FUNC_CHKDEPENDMODULE	0x00000040L	///< �Զ����SDK����������������Զ�ע��
#define BRAC_FUNC_AUDIO_VOLUMECALC	0x00000080L	///< ��SDK�Զ���������������
#define BRAC_FUNC_AUDIO_AUTOVOLUME	0x00000100L	///< ����SDK�Զ�����Mic¼������
#define BRAC_FUNC_NET_SUPPORTUPNP	0x00000200L	///< ����SDK���û������е�UPNP�豸������û���·�������Ƿ���ǽ֧��UPNPЭ�飬������P2P�򶴵ĳɹ���


// �ں˲�������
#define BRAC_SO_AUDIO_VADCTRL				1	///< ��Ƶ���������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_NSCTRL				2	///< ��Ƶ�������ƿ��ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_ECHOCTRL				3	///< ��Ƶ�����������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�
#define BRAC_SO_AUDIO_AGCCTRL				4	///< ��Ƶ�Զ�������ƣ�����Ϊ��int�ͣ�1�򿪣�0�رգ�

#define BRAC_SO_RECORD_VIDEOBR				10	///< ¼����Ƶ�������ã�����Ϊ��int�ͣ���λ��bps��
#define BRAC_SO_RECORD_AUDIOBR				11	///< ¼����Ƶ�������ã�����Ϊ��int�ͣ���λ��bps��
#define BRAC_SO_RECORD_TMPDIR				12	///< ¼���ļ���ʱĿ¼���ã�����Ϊ�ַ���PCHAR���ͣ�
#define BRAC_SO_SNAPSHOT_TMPDIR				13	///< �����ļ���ʱĿ¼���ã�����Ϊ�ַ���PCHAR���ͣ�

#define BRAC_SO_CORESDK_PATH				20	///< ����AnyChat Core SDK������·��������Ϊ�ַ���PCHAR���ͣ�

// ����������Ϣ��������
#define BRAC_TRANSTASK_PROGRESS				1	///< ����������Ȳ�ѯ������Ϊ��DOUBLE�ͣ�0.0 ~ 100.0����
#define BRAC_TRANSTASK_BITRATE				2	///< ��������ǰ�������ʣ�����Ϊ��int�ͣ���λ��bps��
#define BRAC_TRANSTASK_STATUS				3	///< ��������ǰ״̬������Ϊ��int�ͣ�


// ¼���ܱ�־����
#define BRAC_RECORD_FLAGS_VIDEO		0x00000001L	///< ¼����Ƶ
#define BRAC_RECORD_FLAGS_AUDIO		0x00000002L	///< ¼����Ƶ


// �û�״̬��־����
#define BRAC_USERSTATE_CAMERA				1	///< �û�����ͷ״̬������Ϊint�ͣ�
#define BRAC_USERSTATE_HOLDMIC				2	///< �û�����Mic״̬������Ϊint�ͣ�
#define BRAC_USERSTATE_SPEAKVOLUME			3	///< �û���ǰ˵������������ΪDOUBLE���ͣ�0.0 ~ 100.0����
#define BRAC_USERSTATE_RECORDING			4	///< �û�¼������״̬������Ϊint�ͣ�
#define	BRAC_USERSTATE_LEVEL				5	///< �û����𣨲���Ϊint�ͣ�
#define BRAC_USERSTATE_NICKNAME				6	///< �û��ǳƣ�����Ϊ�ַ���PCHAR���ͣ�
#define BRAC_USERSTATE_LOCALIP				7	///< �û�����IP��ַ������������Ϊ�ַ���PCHAR���ͣ�
#define BRAC_USERSTATE_INTERNETIP			8	///< �û�������IP��ַ������Ϊ�ַ���PCHAR���ͣ�


// ��Ƶ���ݻص���������
typedef void (CALLBACK * BRAC_VideoData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue);
// ��Ƶ���ݻص���������
typedef void (CALLBACK * BRAC_AudioData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue);
// ������Ϣ�ص���������
typedef void (CALLBACK * BRAC_TextMessage_CallBack)(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue);
// ͸��ͨ�����ݻص���������
typedef void (CALLBACK * BRAC_TransBuffer_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// ͸��ͨ��������չ�ص���������
typedef void (CALLBACK * BRAC_TransBufferEx_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// �ļ�����ص���������
typedef void (CALLBACK * BRAC_TransFile_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// �����仯�ص���������
typedef void (CALLBACK * BRAC_VolumeChange_CallBack)(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue);
// SDK Filter ͨ�����ݻص���������
typedef void (CALLBACK * BRAC_SDKFilterData_CallBack)(LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// ¼�񡢿���������ɻص���������
typedef void (CALLBACK * BRAC_RecordSnapShot_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType, LPVOID lpUserValue);
// �첽��Ϣ֪ͨ�ص���������
typedef void (CALLBACK* BRAC_NotifyMessage_CallBack)(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue);


/**
 *	API��������
 */

// ��ȡSDK�汾��Ϣ
BRAC_API DWORD BRAC_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, LPSTR lpCompileTime, DWORD dwBufLen);
// ����رգ�SDK������־
BRAC_API DWORD BRAC_ActiveCallLog(BOOL bActive);

// ���÷�������֤���루��������ֹ�Ƿ��û���SDK���ӷ��������Ϸ��û����������ӣ�
BRAC_API DWORD BRAC_SetServerAuthPass(LPCTSTR lpPassword);
// ��ʼ��ϵͳ
BRAC_API DWORD BRAC_InitSDK(HWND hWnd, DWORD dwFuncMode);

// ������Ƶ���ݻص�����
BRAC_API DWORD BRAC_SetVideoDataCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶ���ݻص�����
BRAC_API DWORD BRAC_SetAudioDataCallBack(BRAC_AudioData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����������Ϣ�ص�����
BRAC_API DWORD BRAC_SetTextMessageCallBack(BRAC_TextMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����͸��ͨ�����ݻص�����
BRAC_API DWORD BRAC_SetTransBufferCallBack(BRAC_TransBuffer_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����͸��ͨ��������չ�ص�����
BRAC_API DWORD BRAC_SetTransBufferExCallBack(BRAC_TransBufferEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// �����ļ�����ص�����
BRAC_API DWORD BRAC_SetTransFileCallBack(BRAC_TransFile_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ���������仯�ص�����
BRAC_API DWORD BRAC_SetVolumeChangeCallBack(BRAC_VolumeChange_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����SDK Filterͨ�����ݻص���������
BRAC_API DWORD BRAC_SetSDKFilterDataCallBack(BRAC_SDKFilterData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����¼������������֪ͨ�ص�����
BRAC_API DWORD BRAC_SetRecordSnapShotCallBack(BRAC_RecordSnapShot_CallBack lpFunction, LPVOID lpUserValue=NULL);
// �����첽��Ϣ֪ͨ�ص�����
BRAC_API DWORD BRAC_SetNotifyMessageCallBack(BRAC_NotifyMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);


// ���ӷ�����
BRAC_API DWORD BRAC_Connect(LPCTSTR lpServerAddr, DWORD dwPort);
// ��¼ϵͳ
BRAC_API DWORD BRAC_Login(LPCTSTR lpUserName, LPCTSTR lpPassword, DWORD dwPassEncType); 
// ���뷿��
BRAC_API DWORD BRAC_EnterRoom(DWORD dwRoomid, LPCTSTR lpRoomPass, DWORD dwPassEncType);
// ���뷿��
BRAC_API DWORD BRAC_EnterRoomEx(LPCTSTR lpRoomName, LPCTSTR lpRoomPass);
// �뿪����
BRAC_API DWORD BRAC_LeaveRoom(DWORD dwRoomid);
// ע��ϵͳ
BRAC_API DWORD BRAC_Logout(VOID);

// �ͷ�������Դ
BRAC_API DWORD BRAC_Release(VOID);

// ��ȡ��ǰ���������û��б�
BRAC_API DWORD BRAC_GetOnlineUser(LPDWORD lpUserIDArray, DWORD& dwUserNum);
// ��ѯ�û�����ͷ��״̬
BRAC_API DWORD BRAC_GetCameraState(DWORD dwUserid, DWORD& dwState);
// ��ѯ�û�����״̬
BRAC_API DWORD BRAC_GetSpeakState(DWORD dwUserid, DWORD& dwState);
// ��ѯ�û�����
BRAC_API DWORD BRAC_GetUserLevel(DWORD dwUserid, DWORD& dwLevel);
// ��ѯ�û�����
BRAC_API DWORD BRAC_GetUserName(DWORD dwUserid, CHAR* lpUserName, DWORD dwLen);
// ��ѯ��������
BRAC_API DWORD BRAC_GetRoomName(DWORD dwRoomId, CHAR* lpRoomName, DWORD dwLen);
// ��ʾ������Ƶ������ڶԻ���
BRAC_API DWORD BRAC_ShowLVProperty(HWND hParent, LPCTSTR szCaption=NULL, DWORD dwX=0, DWORD dwY=0);

// ��ѯָ���û����״̬
BRAC_API DWORD BRAC_QueryUserState(DWORD dwUserId, int infoname, char FAR* infoval, int infolen);

// ö�ٱ�����Ƶ�ɼ��豸
BRAC_API DWORD BRAC_EnumVideoCapture(CHAR** lpDeviceName, DWORD& dwDeviceNum);
// ѡ��ָ������Ƶ�ɼ��豸
BRAC_API DWORD BRAC_SelectVideoCapture(LPCTSTR szCaptureName);
// ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
BRAC_API DWORD BRAC_GetCurVideoCapture(CHAR* lpDeviceName, DWORD dwLen);
// ö�ٱ�����Ƶ�ɼ��豸
BRAC_API DWORD BRAC_EnumAudioCapture(CHAR** lpDeviceName, DWORD& dwDeviceNum);
// ѡ��ָ������Ƶ�ɼ��豸
BRAC_API DWORD BRAC_SelectAudioCapture(LPCTSTR szCaptureName);
// ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
BRAC_API DWORD BRAC_GetCurAudioCapture(CHAR* lpDeviceName, DWORD dwLen);


// �����û���Ƶ
BRAC_API DWORD BRAC_UserCameraControl(DWORD dwUserid, BOOL bOpen);
// �����û�����
BRAC_API DWORD BRAC_UserSpeakControl(DWORD dwUserid, BOOL bOpen);
// ������Ƶ��ʾλ��
BRAC_API DWORD BRAC_SetVideoPos(DWORD dwUserid, HWND hWnd, DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom);

// ��ȡָ����Ƶ�豸�ĵ�ǰ����
BRAC_API DWORD BRAC_AudioGetVolume(BRAC_AudioDevice device, DWORD& dwVolume);
// ����ָ����Ƶ�豸������
BRAC_API DWORD BRAC_AudioSetVolume(BRAC_AudioDevice device, DWORD dwVolume);

// �û�������Ƶ¼��
BRAC_API DWORD BRAC_StreamRecordCtrl(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam);
// ���û�����Ƶ����ץ�ģ����գ�
BRAC_API DWORD BRAC_SnapShot(DWORD dwUserId, DWORD dwFlags, DWORD dwParam);

// ͸��ͨ�����ͻ�����
BRAC_API DWORD BRAC_TransBuffer(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
// ͸��ͨ�����ͻ�������չ
BRAC_API DWORD BRAC_TransBufferEx(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// �����ļ�
BRAC_API DWORD BRAC_TransFile(DWORD dwUserid, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// ��ѯ�������������Ϣ
BRAC_API DWORD BRAC_QueryTransTaskInfo(DWORD dwUserid, DWORD dwTaskId, int infoname, char FAR* infoval, int infolen);
// ȡ����������
BRAC_API DWORD BRAC_CancelTransTask(DWORD dwUserid, DWORD dwTaskId);
// �����ı���Ϣ
BRAC_API DWORD BRAC_SendTextMessage(DWORD dwUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);
// ����SDK Filter ͨ������
BRAC_API DWORD BRAC_SendSDKFilterData(LPBYTE lpBuf, DWORD dwLen);

// ���ĵ�ǰ������ģʽ
BRAC_API DWORD BRAC_ChangeChatMode(DWORD dwChatMode);
// ��ȡָ���û���ǰ������ģʽ
BRAC_API DWORD BRAC_GetUserChatMode(DWORD dwUserid, DWORD& dwChatMode);
// ������Է�˽�ģ���Է�����˽������
BRAC_API DWORD BRAC_PrivateChatRequest(DWORD dwUserid);
// �ظ��Է���˽������
BRAC_API DWORD BRAC_PrivateChatEcho(DWORD dwUserid, DWORD dwRequestid,BOOL bAccept);
// �ظ��Է���˽��������չ�����Ը���������룩
BRAC_API DWORD BRAC_PrivateChatEchoEx(DWORD dwUserid, DWORD dwRequestid,DWORD dwErrorCode);
// �˳���ĳ�û���˽�ģ����߽�ĳ�û����Լ���˽���б������
BRAC_API DWORD BRAC_PrivateChatExit(DWORD dwUserid);

// SDK�ں˲�������
BRAC_API DWORD BRAC_SetSDKOption(int optname, const char FAR* optval, int optlen);
// SDK�ں˲���״̬��ѯ
BRAC_API DWORD BRAC_GetSDKOption(int optname, char FAR* optval, int optlen);



#endif //BR_ANYCHAT_CORE_SDK_H__INCLUDED_
