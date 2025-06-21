#pragma once

#include "PieceList.h"

#include <utility>

size_t constexpr TEST = - 1;
size_t constexpr EMPTY = - 2;

typedef std::vector<std::vector<size_t>> BoardOffsets;

class Board
{
public:
    Board(size_t x, size_t y, const std::list<Piece>& pieceList, size_t m_blockCount);

private:
    const std::list<Piece>& m_pieceList;
    const size_t m_blockCount;
    const size_t m_xDim;
    const size_t m_yDim;
    std::list<BoardOffsets> m_solutions;
    std::list<size_t> m_solutionHashes;

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

    enum Corner
    {
        UpLeft,
        DownLeft,
        UpRight,
        DownRight
    };

    BoardOffsets m_board;

    void GenerateSolutions(std::list<::Piece>::const_iterator nextPieceIter);
    void AddSolution();
    bool PlaceRotation(size_t pieceNumber, const Offset& boardOffset, const Rotation& rotation);
    void PullRotation(const Offset& boardOffset, const Rotation& rotation);
    void CountEmptyBlocks(const Offset& testOffset, OffsetList& tested);
    void TestOffset(Direction direction, const Offset& boardOffset, OffsetList& tested);
    size_t BuildSolutionHash(Corner corner, Direction direction);
    size_t GetOffsetHash(size_t xOffset, size_t yOffset);
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
        case OffsetState::Empty:
            m_board[boardOffset.first][boardOffset.second] = EMPTY;
            break;
        case OffsetState::Test:
            m_board[boardOffset.first][boardOffset.second] = TEST;
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

