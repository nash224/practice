#pragma once

#ifndef __DEFINE_BASENODE_H
#define __DEFINE_BASENODE_H
#include <cassert>

template<typename T, typename NodeType>
class BaseNode
{
public:
	// 노드의 연결을 끊어버립니다.
	// 노드가 끝부분이라면 assert를 발생시킵니다.
	// 반환값은 인자로 전달한 노드 포인터입니다.
	static NodeType* UnLink(NodeType* _pNode)
	{
		assert(nullptr != _pNode);
		assert(nullptr != _pNode->mPrev && nullptr != _pNode->mNext);

		Link(_pNode->mPrev, _pNode->mNext);
		return _pNode;
	}

	// 두 노드를 서로 연결시킵니다.
	static void Link(NodeType* _Prev, NodeType* _Next)
	{
		assert(nullptr != _Prev && nullptr != _Next);

		_Prev->mNext = _Next;
		_Next->mPrev = _Prev;
	}

public:
	BaseNode(const T& _Data = T())
		: mData(_Data)
	{
	}

private:
	//TODO : 인텔리전스를 위한 임시 접근 제한자
public:
	T mData;
	NodeType* mPrev = nullptr;
	NodeType* mNext = nullptr;

};

#endif // !__DEFINE_BASENODE_H


