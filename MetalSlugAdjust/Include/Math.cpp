
#include "Math.h"
#include "GameInfo.h"


Vector2::Vector2()	:
	x(0.f),
	y(0.f)
{
}

Vector2::Vector2(float _x, float _y)	:
	x(_x),
	y(_y)
{
}

Vector2::Vector2(const Vector2& v)	:
	x(v.x),
	y(v.y)
{
}

float RadianToDegree(float Radian)
{
	return Radian * 180.f / PI;
}

float DegreeToRadian(float Degree)
{
	return Degree * PI / 180.f;
}

float Distance(const Vector2& Src, const Vector2& Dest)
{
	Vector2 result = Src - Dest;

	return result.Length();
}

float GetAngle(const Vector2& Src, const Vector2& Dest)
{
	// ���� ���̸� ���Ѵ�.
	float c = Distance(Src, Dest);
	// �غ� ����
	// Width�� ������ ���ͼ� Width / c�� ������ �Ǹ�
	// 90������ ũ�� -> Src�� x��ǥ���� Dest�� x��ǥ�� �۴�
	// Width�� ����� ���ͼ� Width / c�� ����� �Ǹ�
	// 90������ �۴� -> Src�� x��ǥ���� Dest�� x��ǥ�� ũ��
	float Width = Dest.x - Src.x;

	// Angle�� cos(theta)��.
	float Angle = Width / c;

	// theta��(����)
	Angle = RadianToDegree(acosf(Angle));

	// ���� Dest�� Src���� ���� �ִٸ� 360���� ���ش�
	// �ð踦 �������� �� src�� �ð��� �߽�, dest�� �ð�ħ ���̶�� �����غ���
	// ������ ������ ��ǥ��� �ﰢ�Լ��� �����ϸ� �ð�ħ�� 3�ø� ����ų ����
	// theta�� 0�̰� �ð� �������� ���ư��� theta�� ����(������ ��ǥ�谡
	// �Ʒ��� ������ �� y��ǥ�� �����ϴ� ���� ��ī��Ʈ ��ǥ��� y��ǥ�� �ݴ�ϱ�
	// �׷���) �׷��� ���� �� src�� dest�� ������ 5PI / 6(150��)�϶���
	// 7PI / 6(210��)�϶��� GetAngle���� RadianToDegree(acosf(Angle))�� Angle��
	// ������ �� Angle�� �Ȱ��� ���´� ���� �� ��츦 �����ϱ� ����
	// dest�� y��ǥ�� src�� y��ǥ���� �۴ٸ� 360 - Angle�� 
	// ���༭ �� ��츦 �������ش�
	if (Dest.y < Src.y)
		Angle = 360.f - Angle;
	
	return Angle;
}
