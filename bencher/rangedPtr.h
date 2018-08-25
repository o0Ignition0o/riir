#include <stddef.h>

template<typename T>
class RangedPtr
{
	T* mPtr;

	void checkSanity()
	{
	}

	RangedPtr<T> create(T* aPtr) const
	{
		return RangedPtr<T>(aPtr, nullptr, size_t(0));
	}
public:

	RangedPtr(T* aPtr, T* aStart, T* aEnd)
		: mPtr(aPtr)
	{
		checkSanity();
	}

	/* Equivalent to RangedPtr(aPtr, aPtr, aLength). */
	RangedPtr(T* aPtr, size_t aLength)
		: mPtr(aPtr)
	{
		checkSanity();
	}

	RangedPtr<T> operator+(size_t aInc) const
	{
		return create(mPtr + aInc);
	}

	RangedPtr<T>& operator++()
	{
		return (*this += 1);
	}

	RangedPtr<T>& operator+=(size_t aInc)
	{
		*this = *this + aInc;
		return *this;
	}


	T& operator*() const
	{
		return *mPtr;
	}

	T* operator->() const
	{
		return mPtr;
	}

	template <typename U>
	bool operator==(const RangedPtr<U>& aOther) const
	{
		return mPtr == aOther.mPtr;
	}
	template <typename U>
	bool operator!=(const RangedPtr<U>& aOther) const
	{
		return !(*this == aOther);
	}

	template<typename U>
	bool operator==(const U* u) const
	{
		return mPtr == u;
	}
	template<typename U>
	bool operator!=(const U* u) const
	{
		return !(*this == u);
	}

	template <typename U>
	bool operator<(const RangedPtr<U>& aOther) const
	{
		return mPtr < aOther.mPtr;
	}
	template <typename U>
	bool operator<=(const RangedPtr<U>& aOther) const
	{
		return mPtr <= aOther.mPtr;
	}

	template <typename U>
	bool operator>(const RangedPtr<U>& aOther) const
	{
		return mPtr > aOther.mPtr;
	}
	template <typename U>
	bool operator>=(const RangedPtr<U>& aOther) const
	{
		return mPtr >= aOther.mPtr;
	}

private:
	RangedPtr() = delete;
};
