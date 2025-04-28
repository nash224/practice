#pragma once

#ifndef __DEFINE_Class_H_
#define __DEFINE_Class_H_

class ADefaultClass
{
public:
	ADefaultClass() {}
	~ADefaultClass() {}

	ADefaultClass(const ADefaultClass& _Other) = delete;
	ADefaultClass(ADefaultClass&& _Other) noexcept = delete;
	ADefaultClass& operator=(const ADefaultClass& _Other) = delete;
	ADefaultClass& operator=(ADefaultClass&& _Other) = delete;

protected:

private:

};


#endif // !__DEFINE_Class_H_
