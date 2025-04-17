#pragma once
#include "DataBase.h"

// 기능: 사용자에게 메뉴를 제공하며, 명령어 기반으로 구현된 인터페이스를 출력한다.

// 목적: 사용자가 편리하게 이용할 수 있는 인터페이스를 제공한다.

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

/* 메뉴를 출력하고 사용자의 입력을 기다린다. */
int DisplayMenu();
/* 데이터베이스에 존재하는 직원을 고용한다 */
void DoHire(Records::DataBase& _DB);
/* 데이터베이스에 존재하는 직원을 해고한다 */
void DoFire(Records::DataBase& _DB);
/* 데이터베이스에 존재하는 직원의 연봉을 인상시킨다. */
void DoPromote(Records::DataBase& _DB);
/* 데이터베이스에 존재하는 직원의 연봉을 감봉시킨다. */
void DoDemote(Records::DataBase& _DB);