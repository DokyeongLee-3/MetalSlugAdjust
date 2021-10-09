#pragma once


#include <Windows.h>
#include "resource.h" 

#include <list>
#include <vector>
#include <stack>
#include <functional>
#include <unordered_map>
#include <crtdbg.h>
#include <string>

#include "SharedPtr.h"
#include "Flag.h"
#include "Math.h"
#include "fmod.hpp"

#pragma comment(lib, "msimg32.lib")

#pragma comment(lib, "fmod64_vc.lib")

#define	GRAVITY	9.8f

#define KEYCOUNT_MAX	256

#define ROOT_PATH		"RootPath"
#define TEXTURE_PATH	"TexturePath"
#define SOUND_PATH		"SoundPath"
#define FONT_PATH		"FontPath"

#define SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p)	if(p) {delete[] p; p = nullptr;}
#define SAFE_RELEASE(p)	if(p)	{p->Release(); p = nullptr;}

#define PLAYER_TOPWIDTH		100
#define PLAYER_TOPHEIGHT	78
#define PLAYER_BOTTOMWIDTH	70
#define PLAYER_BOTTOMHEIGHT	53

struct Resolution
{
	int Width;
	int Height;
};

struct RectInfo
{
	float Left;
	float Top;
	float Right;
	float Bottom;
};

struct SphereInfo
{
	Vector2 Center;
	float Radius;
};

struct BulletInfo
{
	RectInfo	rc;
	float		Distance;
};

struct AnimationFrameData
{
	Vector2 StartPos;
	Vector2 Size;
	Vector2 Offset;

	AnimationFrameData() :
		StartPos(0.f, 0.f),
		Offset(0.f, 0.f)
	{
	}
};

struct CharacterInfo
{
	int Attack;
	int Armor;
	int HP;
	int HPMax;
	int MP;
	int MPMax;
	int Level;
	int Exp;
	int Gold;
	float AttackSpeed;
	float AttackDistance;
};

struct CollisionProfile
{
	std::string			Name;
	ECollision_Channel	Channel;
	// �̰� False�� ����� �� ä���� �浹ü����
	// ��� ��Ȱ��ȭ
	bool				CollisionEnable;

	// Channel ����ŭ ���Ϳ� Collision_State�� �ְ�
	// �浹�� ���ϴ� ä�θ� Collision���� �����ϰ�
	// �������� Ignore�� ����
	// ���� �� �� CollsionProfile�� ���� Collider����
	// Player�� �Ѿ˸� �浹�ϰ� �������� ���� �浹�ϰ�
	// ���� �ʴٸ� vector�� 4�� �ε������� Collision�� �ְ�
	// �������� Ignore�� ������ �ȴ�.
	std::vector<ECollision_State> vecState;
};