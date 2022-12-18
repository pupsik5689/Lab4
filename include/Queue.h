#pragma once
#include <iostream>

const size_t MAX_QUEUE_SIZE = 10000;

template <class T>
class TQueue
{
protected:
	T* pMem;
	size_t memSize;
	size_t hi;
	size_t li;
	size_t count;
	const static size_t unzero = ~0;

public:
	TQueue();
	TQueue(size_t sz = 1);
	TQueue(const TQueue& q);
	TQueue(TQueue&& q) noexcept;
	~TQueue();
	TQueue& operator=(const TQueue& q);
	

	bool IsEmpty() const;
	bool IsFull() const;

	void Free();

	void Push(const T& elem);
	T Top() const;
	void Pop();
	T TopPop();

	bool operator==(const TQueue& q) const;
	bool operator!=(const TQueue& q) const;
};

template<class T>
inline TQueue<T>::TQueue()
{
	hi = 0;
	li = 0;
	count = 0;
	memSize = 0;
	pMem = nullptr;
}

template<typename T>
inline TQueue<T>::TQueue(size_t sz) : hi(0), li(0), pMem(nullptr), count(0)
{
	if ((sz == 0) || (sz > MAX_QUEUE_SIZE))
		throw "Error";

	memSize = sz;
	pMem = new T[memSize];
}

template<typename T>
inline TQueue<T>::TQueue(const TQueue<T>& q)
{
	if (q.pMem == nullptr)
	{
		memSize = 0;
		pMem = nullptr;
		Free();
	}
	else
	{
		memSize = q.memSize;
		hi = q.hi;
		li = q.li;
		count = q.count;
		pMem = new T[memSize];

		if (!(q.IsEmpty()))
		{
			size_t j = hi;
			for (size_t i = 0; i < count; i++)
			{
				pMem[j] = q.pMem[j];
				j--;
				if (j == unzero)
					j = memSize - 1;
			}
		}
	}
}

template<typename T>
inline TQueue<T>::TQueue(TQueue<T>&& q) noexcept
{
	this->operator=(q);
}

template<typename T>
inline TQueue<T>& TQueue<T>::operator=(const TQueue<T>& q)
{
	if (this == &q)
		return *this;

	if (memSize != q.memSize)
	{
		T* tmp = new T[q.memSize];
		delete[] pMem;
		memSize = q.memSize;
		pMem = tmp;
	}

	hi = q.hi;
	li = q.li;
	count = q.count;

	if (!(q.IsEmpty()))
	{
		size_t j = hi;
		for (size_t i = 0; i < count; i++)
		{
			pMem[j] = q.pMem[j];
			j--;

			if (j == unzero)
				j = memSize - 1;
		}
	}
	return *this;
}

template<typename T>
inline TQueue<T>::~TQueue()
{
	delete[] pMem;
	memSize = 0;
	Free();
}

template<typename T>
inline bool TQueue<T>::IsEmpty() const 
{
	return count == 0;
}

template<typename T>
inline bool TQueue<T>::IsFull() const 
{
	return count == memSize;
}

template<typename T>
inline void TQueue<T>::Free() 
{
	hi = 0;
	li = 0;
	count = 0;
}

template<typename T>
inline void TQueue<T>::Push(const T& e)
{
	if (IsFull())
		throw std::out_of_range("Queue is full");
	pMem[li] = e;

	li++;
	li = (li < memSize) ? li : 0;
	count++;
}

template<typename T>
inline T TQueue<T>::Top() const
{
	if (IsEmpty())
		throw "Queue is empty";
	return pMem[hi];
}

template<typename T>
inline void TQueue<T>::Pop()
{
	if (IsEmpty())
		throw "Error";

	hi++;
	hi = (hi < memSize) ? hi : 0;
	count--;
}

template<typename T>
inline T TQueue<T>::TopPop()
{
	T tmp = Top();
	Pop();
	return tmp;
}

template<typename T>
inline bool TQueue<T>::operator==(const TQueue& q) const 
{
	if (count != q.count)
		return false;
	size_t j = hi, k = q.hi;
	for (size_t i = 0; i < count; i++)
	{
		if (pMem[j] != q.pMem[k])
			return false;
		j--;
		if (j == unzero)
			j = memSize - 1;
		k--;
		if (k == unzero)
			k = q.memSize - 1;
	}
	return true;
}

template<typename T>
inline bool TQueue<T>::operator!=(const TQueue& q) const 
{
	return !(this->operator==(q));
}