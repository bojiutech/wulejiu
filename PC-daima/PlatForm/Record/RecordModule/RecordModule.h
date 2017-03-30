// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� RECORDMODULE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// RECORDMODULE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef RECORDMODULE_EXPORTS
#define RECORDMODULE_API __declspec(dllexport)
#else
#define RECORDMODULE_API __declspec(dllimport)
#endif

// �����Ǵ� RecordModule.dll ������
class RECORDMODULE_API CRecordModule {
public:
	CRecordModule(void);
	// TODO: �ڴ�������ķ�����
};

extern RECORDMODULE_API int nRecordModule;

RECORDMODULE_API int fnRecordModule(void);
#include "Recorder.h"
//#include "../../include/interface.h"
//���嵼���ĺ���
extern "C" __declspec(dllexport) IRecorderForPlatform* GetRecordForPlatForm()
{ 
	return new CRecorder();
}
extern "C" __declspec(dllexport) IRecorderForPlayer* GetRecordForPlayer()
{ 
	return new CRecorder();
}