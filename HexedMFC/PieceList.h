#pragma once
#include <list>
#include "Piece.h"
class PieceList
{
public:
    PieceList();
    bool SetBlockCount(unsigned int blockCount);

private:
    size_t m_blockCount;
    std::list<Piece> m_pieceList;
    void GeneratePieceList(unsigned int blockCount);
    OffsetList NextOffset(OffsetList& offsets);
    void TryOffsets(OffsetList& offsets);
};

