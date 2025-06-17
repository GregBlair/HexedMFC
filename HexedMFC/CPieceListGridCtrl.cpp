#include "pch.h"

#include <cmath>

#include "CPieceListGridCtrl.h"

CPieceListGridCtrl::CPieceListGridCtrl()
{
}

void CPieceListGridCtrl::SetPieceList(const std::list<Piece>& pieceList)
{
	m_pieceList = pieceList;

	DetermineGridDimensions();
}

void CPieceListGridCtrl::DetermineGridDimensions()
{
	// Determine the max dims and figure out the needed grid.
	size_t maximumX = 0;
	size_t maximumY = 0;

	for (Piece piece : m_pieceList)
	{
		for (Rotation rotation : piece.m_rotations)
		{
			for (Offset offset : rotation.m_offsets)
			{
				maximumX = (((maximumX) > (offset.first)) ? (maximumX) : (offset.first));
				maximumY = (((maximumY) > (offset.second)) ? (maximumY) : (offset.second));
				ASSERT(maximumX == maximumY);
			}
		}
	}

	// Just make it a square for now.
	size_t piecesPerDim =  static_cast<size_t>(std::ceil(sqrt(m_pieceList.size())) + 0.1);
}
