#pragma once

#ifndef __DEFINE_CPlayer_H_
#define __DEFINE_CPlayer_H_

class CPlayer
{
public:
	// constructor & destructor
	CPlayer() {}
	~CPlayer() {}

	// delete function
	CPlayer(const CPlayer& _Other) = delete;
	CPlayer(CPlayer&& _Other) noexcept = delete;
	CPlayer& operator=(const CPlayer& _Other) = delete;
	CPlayer& operator=(CPlayer&& _Other) = delete;

protected:

private:

};


#endif // !__DEFINE_CPlayer_H_
