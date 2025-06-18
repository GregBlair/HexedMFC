#pragma once
#include <list>
#include "Piece.h"
class PieceList
{
public:
    PieceList();
    bool SetBlockCount(size_t blockCount);
    void TestCombos();

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
    void NextOffset(OffsetList offsets);
    void TryOffsets(OffsetList& offsets);
    void HandleNextOffset(Direction direction, OffsetList offsets, OffsetList& addedOffsets);
    template <typename T1>
    std::list<std::list<T1>> GetCombinations(std::list<T1> rightList);
};
