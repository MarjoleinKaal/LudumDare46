#pragma once
#include <cstdint>
#include <mathematics/Vector2.h>
#include <mathematics/Vector3.h>
#include <mathematics/Quaternion.h>

using uint = uint32_t;
using uint16 = uint16_t;
using uint64 = uint64_t;

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
