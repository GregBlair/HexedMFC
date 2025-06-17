#pragma once

#include "PieceList.h"

class CPieceListGridCtrl
{

public:
	CPieceListGridCtrl();

	void SetPieceList(const std::list<Piece>& pieceList);

private:
	void DetermineGridDimensions();

private:
	std::list<Piece> m_pieceList; // Keep a copy for safety.
};

