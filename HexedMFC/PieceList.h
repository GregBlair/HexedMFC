#pragma once
#include <list>
#include "Piece.h"
class PieceList
{
public:
    PieceList();
    bool SetBlockCount(size_t blockCount);

private:
    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    size_t m_blockCount;
    std::list<Piece> m_pieceList;
    void GeneratePieceList(size_t blockCount);
    void NextOffsetSnakes(OffsetList& offsets);
    void NextOffsetGlobs(OffsetList offsets, Offset lastOffset);
    void TryOffsets(OffsetList& offsets);
    void HandleNextOffsetSnakes(Offset& nextOffset, OffsetList& offsets);
    void HandleNextOffsetGlobs(const Offset& lastOffset, Direction direction, OffsetList offsets, OffsetList& addedOffsets);
    std::list<OffsetList> GenerateViableCombos(const OffsetList& addedOffsets);
    void AddToCombinations(std::list<OffsetList>& listOfLists, const OffsetList& original, const OffsetList& transfered);
};

