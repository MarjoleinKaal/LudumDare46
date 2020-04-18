#pragma once
#include <raymath.h>
#include <mathematics/Vector2.h>
#include <mathematics/Vector3.h>
#include <mathematics/Quaternion.h>

using Vec2 = reactphysics3d::Vector2;
using Vec3 = reactphysics3d::Vector3;
using Quat = reactphysics3d::Quaternion;

struct Vec2I
{
	int x, y;
};

struct Vec3I
{
	int x, y, z;
};

inline Vec3 ConvertVector3(const Vector3& raymathVec3)
{
	return Vec3{ raymathVec3.x, raymathVec3.y, raymathVec3.z };
}
inline Vector3 ConvertVector3(const Vec3& reactphysicsVec3)
{
	return Vector3{ reactphysicsVec3.x, reactphysicsVec3.y, reactphysicsVec3.z };
}
