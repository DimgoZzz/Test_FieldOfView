#pragma once
#include <DirectXMath.h>


//https://docs.microsoft.com/en-us/windows/win32/dxmath/ovw-xnamath-reference-functions-vector2
namespace DogFW
{

class SSEVector2
{
public:
	//================================================================
#pragma region Contructors
public:
	SSEVector2();
	SSEVector2(DirectX::XMVECTOR invec);
	SSEVector2(float x, float y);
	SSEVector2(uint32_t x, uint32_t y);
	SSEVector2(float valueforXY);
	SSEVector2(uint32_t valueforXY);

	//Конструктор копирования
	SSEVector2(const SSEVector2& in) noexcept : mXMVec(in.mXMVec) {};
	//Конструктор присваивания
	SSEVector2(SSEVector2&& in) noexcept : mXMVec(in.mXMVec) {};


#pragma endregion Contructors
	//================================================================
#pragma region Operators
public:
	//Присваивание копированием
	inline SSEVector2& operator=(SSEVector2 const& in) noexcept
	{
		if (&in != this)
		{
			mXMVec = in.mXMVec;
		}
		return *this;
	}
	//Присваивание перемещением
	inline SSEVector2& operator=(SSEVector2 const&& in) noexcept
	{
		if (&in != this)
		{
			mXMVec = in.mXMVec;
		}
		return *this;
	}

	//Returns Negative(Vector)
	inline SSEVector2 operator-() const
	{
		SSEVector2 temp;
		temp.mXMVec = DirectX::XMVectorNegate(mXMVec);
		return temp;
	}

	inline SSEVector2& operator+=(SSEVector2 const& in)
	{
		mXMVec = DirectX::XMVectorAdd(mXMVec, in.mXMVec);
		return *this;
	}
	inline SSEVector2& operator-=(SSEVector2 const& in)
	{
		//using namespace DirectX;
		mXMVec = DirectX::XMVectorSubtract(mXMVec, in.mXMVec);
		return *this;
	}
	inline SSEVector2& operator*=(SSEVector2 const& in)
	{
		mXMVec = DirectX::XMVectorMultiply(mXMVec, in.mXMVec);
		return *this;
	}
	inline SSEVector2& operator/=(SSEVector2 const& in)
	{
		mXMVec = DirectX::XMVectorMultiply(mXMVec, DirectX::XMVectorReciprocal(in.mXMVec));
		return *this;
	}
		
	inline SSEVector2 operator+ (SSEVector2 const& rin) const 
	{
		return SSEVector2(DirectX::XMVectorAdd(mXMVec, rin.mXMVec));
	}
	inline SSEVector2 operator- (SSEVector2 const& rin) const
	{
		return SSEVector2(DirectX::XMVectorSubtract(mXMVec,rin.mXMVec));
	}
	inline SSEVector2 operator* (SSEVector2 const& rin) const
	{
		return SSEVector2(DirectX::XMVectorMultiply(mXMVec, rin.mXMVec));
	}
	inline SSEVector2 operator/ (SSEVector2 const& rin) const
	{
		return SSEVector2(DirectX::XMVectorDivide(mXMVec, rin.mXMVec));
	}
		
#		pragma endregion Operators
	//================================================================
#pragma region GetSet
public:
	inline float GetX() const { return DirectX::XMVectorGetX(mXMVec); }
	inline float GetY() const { return DirectX::XMVectorGetY(mXMVec); }
	inline uint32_t  GetIntX() const { return DirectX::XMVectorGetIntX(mXMVec); }
	inline uint32_t  GetIntY() const { return DirectX::XMVectorGetIntY(mXMVec); }

	inline void SetX(const float value) { mXMVec = DirectX::XMVectorSetX(mXMVec, value); }
	inline void SetIntX(const uint32_t value) { mXMVec = DirectX::XMVectorSetIntX(mXMVec, value); }
	inline void SetY(const float value) { mXMVec = DirectX::XMVectorSetY(mXMVec, value); }
	inline void SetIntY(const uint32_t value) { mXMVec = DirectX::XMVectorSetIntY(mXMVec, value); }
#pragma endregion GetSet
	//================================================================
#pragma region Functions 
public:
	//Returns Abs(Vector)
	inline SSEVector2 Abs() const
	{
		SSEVector2 temp;
		temp.mXMVec = DirectX::XMVectorAbs(mXMVec);
		return temp;
	};
	inline SSEVector2 Length() const
	{
		SSEVector2 temp;
		temp.mXMVec = DirectX::XMVector2Length(mXMVec);
		return temp;
	};
	inline float LengthPow2() const
	{
		float x = GetX();
		float y = GetY();

		return (x*x+y*y);
	};
	inline SSEVector2 GetNewRotated(float angle)const
	{ 
		SSEVector2 temp = DirectX::XMVector2Transform(mXMVec, DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-angle)));
		return temp;
	};

#pragma endregion Functions
	//================================================================
private:
	alignas(16) DirectX::XMVECTOR mXMVec;
};


}