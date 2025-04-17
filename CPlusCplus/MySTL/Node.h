#pragma once

#ifndef __DEFINE_BASENODE_H
#define __DEFINE_BASENODE_H
#include <cassert>

template<typename T, typename NodeType>
class BaseNode
{
public:
	// ����� ������ ��������ϴ�.
	// ��尡 ���κ��̶�� assert�� �߻���ŵ�ϴ�.
	// ��ȯ���� ���ڷ� ������ ��� �������Դϴ�.
	static NodeType* UnLink(NodeType* _pNode)
	{
		assert(nullptr != _pNode);
		assert(nullptr != _pNode->mPrev && nullptr != _pNode->mNext);

		Link(_pNode->mPrev, _pNode->mNext);
		return _pNode;
	}

	// �� ��带 ���� �����ŵ�ϴ�.
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
	//TODO : ���ڸ������� ���� �ӽ� ���� ������
public:
	T mData;
	NodeType* mPrev = nullptr;
	NodeType* mNext = nullptr;

};

#endif // !__DEFINE_BASENODE_H


