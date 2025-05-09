
//---------------------------------------------------------------------------------------
// Filename: main.ccp
//---------------------------------------------------------------------------------------

// �� ������ �������� �ǵ��� �ڵ� ��Ÿ��, ���� ������ 
// ö���� �����ϰ� �ۼ��Ǿ����� �˷��帳�ϴ�. 

// ���� ����Ʈ: https://www.rastertek.com/

#include "systemclass.h"

// window ���� ���α׷��� ������
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	SystemClass* System;
	bool result;

	// �ý��� ��ü ����
	System = new SystemClass;

	// �ý��� ��ü �ʱ�ȭ
	result = System->Initialize();
	if (result)
	{
		// �ý��� ���� 
		System->Run();
	}

	// �ý��� �ı�
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}



