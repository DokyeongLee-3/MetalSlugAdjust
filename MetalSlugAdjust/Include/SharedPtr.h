#pragma once


template <typename T>
class CSharedPtr
{
public:
	CSharedPtr() :
		m_Ptr(nullptr)
	{

	}

	CSharedPtr(T* Ptr)
	{
		m_Ptr = Ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	CSharedPtr(const CSharedPtr& Ptr)
	{
		m_Ptr = Ptr.m_Ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	~CSharedPtr()
	{
		if (m_Ptr)
			m_Ptr->Release();
	}

private:
	T* m_Ptr;

public:
	void operator = (T* Ptr)
	{
		if (m_Ptr)
			m_Ptr->Release();

		m_Ptr = Ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	void operator = (const CSharedPtr<T>& Ptr)
	{
		if (m_Ptr)
			m_Ptr->Release();

		m_Ptr = Ptr.m_Ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	bool operator == (T* Ptr)	const
	{
		return m_Ptr == Ptr;
	}

	bool operator == (const CSharedPtr<T>& Ptr) const
	{
		return m_Ptr == Ptr.m_Ptr;
	}

	bool operator != (T* Ptr)	const
	{
		return m_Ptr != Ptr;
	}

	bool operator != (const CSharedPtr<T>& Ptr) const
	{
		return m_Ptr != Ptr.m_Ptr;
	}

	// 변환 연산자
	operator T* ()	const
	{
		return m_Ptr;
	}

	T* operator -> ()	const
	{
		return m_Ptr;
	}
};

