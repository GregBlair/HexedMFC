#pragma once

#include "PieceList.h"
#include "Board.h"

class CPieceListGridCtrl
{

public:
	CPieceListGridCtrl();

	void SetPieceList(const std::list<Piece>& pieceList);

private:
	void DetermineBoards();

private:
	std::list<Piece> m_pieceList; // Keep a copy for safety.
	std::list<Board> m_boards;  // Different dimensioned boards for this piece list.
};

