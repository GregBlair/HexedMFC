#pragma once

#include "PieceList.h"

#include <utility>

size_t constexpr TEST = - 1;
size_t constexpr EMPTY = - 2;

class Board
{
public:
    Board(size_t x, size_t y, const PieceList& pieceList);

private:
    const PieceList& m_pieceList;
    const size_t m_blockCount;
    const size_t m_xDim;
    const size_t m_yDim;
    std::list<std::vector<std::vector<size_t>>> m_solutions;

    enum OffsetState
    {
        OffBoard,
        Empty,
        Test,
        Piece
    };

    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    std::vector<std::vector<size_t>> m_board;

    void GenerateSolutions(std::list<::Piece>::const_iterator nextPieceIter);
    bool PlaceRotation(size_t pieceNumber, const Offset& boardOffset, const Rotation& rotation);
    void PullRotation(const Offset& boardOffset, const Rotation& rotation);
    void CountEmptyBlocks(const Offset& testOffset, OffsetList& tested);
    void TestOffset(Direction direction, const Offset& boardOffset, OffsetList& tested);
    OffsetState inline GetOffsetState(const Offset& offset)
    {
        OffsetState retVal;
        if (offset.first >= m_xDim || offset.second >= m_yDim)
        {
            retVal = OffsetState::OffBoard;
        }
        else
        {
            size_t value = m_board[offset.first][offset.second];
            switch (value)
            {
            case EMPTY:
                retVal = OffsetState::Empty;
                break;
            case TEST:
                retVal = OffsetState::Test;
                break;
            default:
                retVal = OffsetState::Piece;
                break;
            }
        }

        return retVal;
    }

    void inline MarkBoardOffset(const Offset& boardOffset, OffsetState state)
    {
        switch (state)
        {
        case EMPTY:
            m_board[boardOffset.first][boardOffset.second] = OffsetState::Empty;
            break;
        case TEST:
            m_board[boardOffset.first][boardOffset.second] = OffsetState::Test;
            break;
        default:
            ASSERT(false);
            break;
        }
    }

    void inline MarkBoardOffset(const Offset& offset, size_t pieceNumber)
    {
        m_board[offset.first][offset.second] = pieceNumber;
    }
};

