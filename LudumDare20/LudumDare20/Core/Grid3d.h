#pragma once
#include <vector>

#include "Defines.h"
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

	bool IsPosValid(Vec3I pos) const
	{
		return pos.x >= 0 && pos.y >= 0 && pos.z >= 0
			&& pos.x < size.x&& pos.y < size.y&& pos.z < size.z;
	}
	
	TCell& At(Vec3I pos)
	{
		ASSERT(IsPosValid(pos));

		return cells[FlattenPosToIndex(pos)];
	}
	const TCell& At(Vec3I pos) const
	{
		ASSERT(IsPosValid(pos));

		return cells[FlattenPosToIndex(pos)];
	}

	TCell* TryAt(Vec3I pos)
	{
		if(!IsPosValid(pos))
		{
			return nullptr;
		}

		return &cells[FlattenPosToIndex(pos)];
	}
	const TCell* TryAt(Vec3I pos) const
	{
		if (!IsPosValid(pos))
		{
			return nullptr;
		}

		return &cells[FlattenPosToIndex(pos)];
	}

private:
	int FlattenPosToIndex(Vec3I pos) const
	{
		return (pos.x) + (pos.z * size.x) + (pos.y * size.x * size.z);
	}
};
