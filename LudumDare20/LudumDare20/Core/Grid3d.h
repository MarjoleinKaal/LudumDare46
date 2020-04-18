#pragma once
#include <vector>

#include "BasicTypes.h"


template<typename TCell>
class Grid3d
{
	std::vector<TCell> cells;
	Vec3I size{};
	
public:
	Grid3d() = default;
	//! X amount, Y amount, Z amount
	Grid3d(uint w, uint h, uint d) : size{w, h, d}
	{
		cells.resize(w * h * d);
	}

	Vec3I GetSize() const { return size; }
	void Resize(Vec3I newSize)
	{
		size = newSize;
		cells.resize(newSize.x * newSize.y * newSize.z);
	}

	bool IsPosValid(Vec3I pos)
	{
		
	}
	
	TCell& At(Vec3I pos)
	{
		
	}
};