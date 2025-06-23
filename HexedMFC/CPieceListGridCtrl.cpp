#include "pch.h"

#include <cmath>

#include "CPieceListGridCtrl.h"

CPieceListGridCtrl::CPieceListGridCtrl()
{
}

void CPieceListGridCtrl::SetPieceList(const std::list<Piece>& pieceList)
{
	m_pieceList = pieceList;

	DetermineBoards();
}

void CPieceListGridCtrl::DetermineBoards()
{
	size_t blockCount = m_pieceList.begin()->GetRotations().begin()->GetOffsets().size();
	// Determine the smallest maximum dim of all rotations and use that to eliminate grids that are too small.

	size_t minimumDim = blockCount;

	for (Piece piece : m_pieceList)
	{
		size_t maximumXOffset = 0;
		size_t maximumYOffset = 0;
		for (const Rotation& rotation : piece.GetRotations())
		{
			for (const Offset& offset : rotation.GetOffsets())
			{
				maximumXOffset = max(maximumXOffset, offset.first);
				maximumYOffset = max(maximumYOffset, offset.second);
			}
		}
		ASSERT(maximumXOffset == maximumYOffset);
		minimumDim = min(minimumDim, maximumXOffset + 1);
	}

	// Use the total blocks to get the area of the grid and factor out the possible grid dims
	size_t totalBlocks = m_pieceList.size() * blockCount;

	for (size_t i = minimumDim; i <= sqrt(totalBlocks); i++)
	{
		if (totalBlocks % i == 0)
		{
			m_boards.push_back(Board(totalBlocks / i, i, m_pieceList, blockCount));
		}
	}
}
