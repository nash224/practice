#pragma once

#ifndef __DEFINE_MYLIST_H
#define __DEFINE_MYLIST_H

#include <cassert>
#include "Header.h"

template<typename T> class MyList;
template<typename T> class MyListIterator;

template<typename T>
class MyListNode
{
public:
	// 노드의 연결을 끊어버립니다.
	// 노드가 끝부분이라면 assert를 발생시킵니다.
	// 반환값은 인자로 전달한 노드 포인터입니다.
	static MyListNode* UnLink(MyListNode* _pNode)
	{
		assert(nullptr != _pNode);
		assert(nullptr != _pNode->mPrev && nullptr != _pNode->mNext);

		Link(_pNode->mPrev, _pNode->mNext);
		return _pNode;
	}

	// 두 노드를 서로 연결시킵니다.
	static void Link(MyListNode* _Prev, MyListNode* _Next)
	{
		assert(nullptr != _Prev && nullptr != _Next);

		_Prev->mNext = _Next;
		_Next->mPrev = _Prev;
	}

public:
	friend class MyList<T>;
	friend class MyListIterator<T>;

public:
	MyListNode(const T& _Data = T())
		: mData(_Data)
	{
	}

private:
	//TODO : 인텔리전스를 위한 임시 접근 제한자
public:
	T mData;
	MyListNode* mPrev = nullptr;
	MyListNode* mNext = nullptr;

};

template<typename T>
class MyListIterator
{
	using Node = MyListNode<T>;

public:
	MyListIterator(Node* _Ptr = nullptr)
		: mPtr(_Ptr)
	{

	}

	T& operator*()
	{
		return mPtr->mData;
	}

	const T& operator*() const
	{
		return mPtr->mData;
	}

	bool operator==(const MyListIterator& _Other) const
	{
		return mPtr == _Other.mPtr;
	}

	bool operator!=(const MyListIterator& _Other) const
	{
		return !operator==(_Other);
	}

	MyListIterator& operator++()
	{
		assert(nullptr != mPtr);
		mPtr = mPtr->mNext;
		return (*this);
	}

	MyListIterator operator++(int)
	{
		MyListIterator Temp = MyListIterator(*this);
		assert(nullptr != mPtr);
		mPtr = mPtr->mNext;
		return Temp;
	}

private:
	Node* mPtr = nullptr;

public:
	friend class MyList<T>;

};

template<typename T>
class MyList
{
	using Node = MyListNode<T>;

public:
	using iterator = MyListIterator<T>;

public:
	MyList()
	{
		mHead = new Node;
		mTail = new Node;
		mHead->mNext = mTail;
		mTail->mPrev = mHead;
	}

	~MyList()
	{
		clear();

		safe_delete(mHead);
		safe_delete(mTail);
	}


	void push_back(const T& _Data)
	{
		Node* NewNode = new Node(_Data);
		Node* PrevNode = mTail->mPrev;

		Node::Link(PrevNode, NewNode);
		Node::Link(NewNode, mTail);
	}

	void push_front(const T& _Data)
	{
		Node* NewNode = new Node(_Data);
		Node* NextNode = mHead->mNext;

		Node::Link(NewNode, NextNode);
		Node::Link(mHead, NewNode);
	}

	void pop_back()
	{
		assert(mHead != mTail->mPrev);
		
		Node* DeleteNode = mTail->mPrev;

		Node::UnLink(DeleteNode);
		safe_delete(DeleteNode);
	}

	void pop_front()
	{
		assert(mTail != mHead->mNext);

		Node* DeleteNode = mHead->mNext;

		Node::UnLink(DeleteNode);
		safe_delete(DeleteNode);
	}

	T& front()
	{
		assert(mHead->mNext != mTail);
		return (mHead->mNext->mData);
	}

	T& back()
	{
		assert(mTail->mPrev != mHead);
		return (mTail->mPrev->mData);
	}

	void clear()
	{
		Node* DeleteNode = mHead->mNext;
		Node* NextNode;
		while (DeleteNode != mTail)
		{
			NextNode = DeleteNode->mNext;
			safe_delete(DeleteNode);
			DeleteNode = NextNode;
		}

		Node::Link(mHead, mTail);
	}

	bool empty() const { return begin() == end(); }

	// iterator
public:
	iterator begin() const { return iterator(mHead->mNext); }
	iterator end() const { return iterator(); }

	iterator erase(iterator& _Where)
	{
		Node* NextNode = _Where.mPtr->mNext;
		Node::UnLink(_Where.mPtr);
		safe_delete(_Where.mPtr);
		return iterator(NextNode);
	}

	iterator erase(iterator&& _Where)
	{
		return erase(_Where);
	}

	void remove(const T& _Data)
	{
		iterator StartIter = begin();
		iterator EndIter = end();

		for (;StartIter != EndIter;)
		{
			assert(nullptr != StartIter.mPtr);
			if (_Data != StartIter.mPtr->mData)
			{
				++StartIter;
				continue;
			}

			StartIter = erase(StartIter);
		}
	}

	void insert(const iterator& _Where, const T& _Data)
	{
		Node* NewNode = new Node(_Data);
		Node* PrevNode = _Where.mPtr->mPrev;
		Node* NextNode = _Where.mPtr->mNext;

		Node::Link(PrevNode, NewNode);
		Node::Link(NewNode, NextNode);
	}

	void insert(const iterator& _Where, T&& _Data)
	{
		Node* NewNode = new Node(_Data);
		Node* PrevNode = _Where.mPtr;
		Node* NextNode = _Where.mPtr->mNext;

		Node::Link(PrevNode, NewNode);
		Node::Link(NewNode, NextNode);
	}

private:
	Node* mHead = nullptr;
	Node* mTail = nullptr;
};

#endif // !__DEFINE_MYLIST_H
