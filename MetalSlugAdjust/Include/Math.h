#pragma once

#include <Windows.h>
#include <math.h>

#define PI	3.141592f

float RadianToDegree(float Radian);
float DegreeToRadian(float Degree);

// ��ǥ �ǹ��ϴ� ����ü
struct Vector2
{
	float x;
	float y;

public:
	Vector2();
	Vector2(float _x, float _y);
	Vector2(const Vector2& v);

public:
	const Vector2& operator = (const Vector2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	const Vector2& operator = (const POINT& v)
	{
		x = (float)v.x;
		y = (float)v.y;
		return *this;
	}

	// + ������ �����ε�
	Vector2 operator + (const Vector2& v)	const
	{
		Vector2 result;
		result.x = x + v.x;
		result.y = y + v.y;
		return result;
	}

	Vector2 operator + (const POINT& v)	const
	{
		Vector2 result;
		result.x = x + (float)v.x;
		result.y = y + (float)v.y;
		return result;
	}

	Vector2 operator + (float f)	const
	{
		Vector2 result;
		result.x = x + f;
		result.y = y + f;
		return result;
	}

	Vector2 operator + (int i)	const
	{
		Vector2	result;
		result.x = x + (float)i;
		result.y = y + (float)i;
		return result;
	}

	// += ������ �����ε�
	const Vector2& operator += (const Vector2& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	const Vector2& operator += (const POINT& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	const Vector2& operator += (float f)
	{
		x += f;
		y += f;
		return *this;
	}

	const Vector2& operator += (int i)
	{
		x += i;
		y += i;
		return *this;
	}

	Vector2 operator - (const Vector2& v) const
	{
		Vector2 result;
		result.x = x - v.x;
		result.y = y - v.y;
		return result;
	}

	Vector2 operator - (const POINT& v)	const
	{
		Vector2	result;
		result.x = x - v.x;
		result.y = y - v.y;
		return result;
	}

	Vector2 operator - (float f)	const
	{
		Vector2	result;
		result.x = x - f;
		result.y = y - f;
		return result;
	}

	Vector2 operator - (int i)	const
	{
		Vector2	result;
		result.x = x - i;
		result.y = y - i;
		return result;
	}

	const Vector2& operator -= (const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	const Vector2& operator -= (const POINT& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	const Vector2& operator -= (float f)
	{
		x -= f;
		y -= f;
		return *this;
	}

	const Vector2& operator -= (int i)
	{
		x -= i;
		y -= i;
		return *this;
	}

	// *
	Vector2 operator * (const Vector2& v)	const
	{
		Vector2	result;
		result.x = x * v.x;
		result.y = y * v.y;
		return result;
	}

	Vector2 operator * (const POINT& v)	const
	{
		Vector2	result;
		result.x = x * v.x;
		result.y = y * v.y;
		return result;
	}

	Vector2 operator * (float f)	const
	{
		Vector2	result;
		result.x = x * f;
		result.y = y * f;
		return result;
	}

	Vector2 operator * (int i)	const
	{
		Vector2	result;
		result.x = x * i;
		result.y = y * i;
		return result;
	}

	// *=
	const Vector2& operator *= (const Vector2& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	const Vector2& operator *= (const POINT& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	const Vector2& operator *= (float f)
	{
		x *= f;
		y *= f;
		return *this;
	}

	const Vector2& operator *= (int i)
	{
		x *= i;
		y *= i;
		return *this;
	}

	// /
	Vector2 operator / (const Vector2& v)	const
	{
		Vector2	result;
		result.x = x / v.x;
		result.y = y / v.y;
		return result;
	}

	Vector2 operator / (const POINT& v)	const
	{
		Vector2	result;
		result.x = x / v.x;
		result.y = y / v.y;
		return result;
	}

	Vector2 operator / (float f)	const
	{
		Vector2	result;
		result.x = x / f;
		result.y = y / f;
		return result;
	}

	Vector2 operator / (int i)	const
	{
		Vector2	result;
		result.x = x / i;
		result.y = y / i;
		return result;
	}

	// /=
	const Vector2& operator /= (const Vector2& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	const Vector2& operator /= (const POINT& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	const Vector2& operator /= (float f)
	{
		x /= f;
		y /= f;
		return *this;
	}

	const Vector2& operator /= (int i)
	{
		x /= i;
		y /= i;
		return *this;
	}

	float Length()	const
	{
		return sqrtf(x * x + y * y);
	}

	// ������ ũ�⸦ 1�� ����� ����ȭ
	// ���࿡ 45�� ���� �Ʒ� �밢������ �Ÿ� 1��ŭ �Ѿ��� ������ �ʹٸ�
	// �Ѿ��� Vector2 m_Dir�� x = 1, y = 1�ϰ� ����ȭ �������
	// x�������� 1/root(2), y�������� 1/root(2)��ŭ ����
	// �밢���� ���� 1��ŭ ���ư���. ���� ����ȭ�� �������� ������
	// �밢�� ���� root(1^2 + 1^2) = ��ŭ ���ư��� ���� ������ ���� �Ÿ�����
	// ������ �� ���� ���ư��� �ȴ�. ���� �׻� Vector2�� ���� ������ �ϰ� ����
	// ����ȭ�� ������� �Ѵ�
	void Normalize()
	{
		float SelfLength = Length();
		x /= SelfLength;
		y /= SelfLength;
	}

};

float Distance(const Vector2& Src, const Vector2& Dest);
float GetAngle(const Vector2& Src, const Vector2& Dest);