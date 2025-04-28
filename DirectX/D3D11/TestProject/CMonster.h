#pragma once

#ifndef __DEFINE_Class_H_
#define __DEFINE_Class_H_

class CMonster
{
public:
	// constructor & destructor
	CMonster() {}
	~CMonster() {}

	// delete function
	CMonster(const CMonster& _Other) = delete;
	CMonster(CMonster&& _Other) noexcept = delete;
	CMonster& operator=(const CMonster& _Other) = delete;
	CMonster& operator=(CMonster&& _Other) = delete;

protected:

private:

};


#endif // !__DEFINE_Class_H_
