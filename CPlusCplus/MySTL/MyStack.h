#pragma once
#include <cassert>
#include "Header.h"

template<typename T> class MyStack;

template <typename T>
class StackNode
{
public:
	friend class MyStack<T>;

public:
	StackNode(const T& _Data)
		: mData(_Data)
	{
	}

	~StackNode()
	{
	}

private:
	T mData;
	StackNode* mNext = nullptr;

};

template <typename T>
class MyStack
{
private:
	using Node = StackNode<T>;

public:
	MyStack() {}
	~MyStack()
	{
		Destroy();
	}

	void Push(const T& _Data)
	{
		Node* NewNode = new Node(_Data);

		const bool Contained = (nullptr != mTop);
		if (Contained)
		{
			NewNode->mNext = mTop;
		}
		mTop = NewNode;
	}

	void Pop()
	{
		Node* DeleteNode = mTop;
		Node* NextNode = mTop->mNext;
		mTop = NextNode;

		safe_delete(DeleteNode);
	}

	T& Top()
	{
		assert(nullptr != mTop);
		return (mTop->mData);
	}

	void clear()
	{
		Destroy();
	}

private:
	void Destroy()
	{
		Node* DeleteNode;
		Node* NextNode;

		while (nullptr != mTop)
		{
			DeleteNode = mTop;
			NextNode = mTop->mNext;
			mTop = NextNode;

			safe_delete(DeleteNode);
		}
	}

private:
	Node* mTop = nullptr;

};