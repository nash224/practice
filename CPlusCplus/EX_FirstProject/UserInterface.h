#pragma once
#include "DataBase.h"

// ���: ����ڿ��� �޴��� �����ϸ�, ��ɾ� ������� ������ �������̽��� ����Ѵ�.

// ����: ����ڰ� ���ϰ� �̿��� �� �ִ� �������̽��� �����Ѵ�.

enum class EInput
{
	Done = 0,
	Hire,
	Fire,
	Promote,
	DisplayAll,
	DisplayCurrent,
	DisplayFormer,
};

/* �޴��� ����ϰ� ������� �Է��� ��ٸ���. */
int DisplayMenu();
/* �����ͺ��̽��� �����ϴ� ������ ����Ѵ� */
void DoHire(Records::DataBase& _DB);
/* �����ͺ��̽��� �����ϴ� ������ �ذ��Ѵ� */
void DoFire(Records::DataBase& _DB);
/* �����ͺ��̽��� �����ϴ� ������ ������ �λ��Ų��. */
void DoPromote(Records::DataBase& _DB);
/* �����ͺ��̽��� �����ϴ� ������ ������ ������Ų��. */
void DoDemote(Records::DataBase& _DB);