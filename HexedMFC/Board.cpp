#include "pch.h"

#include "Board.h"
#include "Piece.h"

Board::Board(size_t x, size_t y, const PieceList& pieceList) :
    m_pieceList(pieceList),
    m_blockCount(pieceList.GetBlockCount()),
    m_xDim(x),
    m_yDim(y)
{
    m_board = std::vector<std::vector<size_t>>(x, std::vector<size_t>(y));
    GenerateSolutions(m_pieceList.GetPieceList().begin());
}

void Board::GenerateSolutions(std::list<::Piece>::const_iterator testPieceIter)
{
    const std::list<::Piece>& pieceList = m_pieceList.GetPieceList();
    // For each piece, try every rotation at every location.
    for (size_t boardXOffset = 0; boardXOffset < m_xDim; ++boardXOffset)
    {
        for (size_t boardYOffset = 0; boardYOffset < m_yDim; ++boardYOffset)
        {
            Offset rootOffset(boardXOffset, boardYOffset);
            for (const Rotation& rotation : testPieceIter->GetRotations())
            {
                if (PlaceRotation(testPieceIter->m_number, rootOffset, rotation))
                {
                    std::list<::Piece>::const_iterator nextPieceIter = ++testPieceIter;
                    // If this is the last piece, we have a solution.
                    if (nextPieceIter == pieceList.end())
                    {
                        m_solutions.push_back(m_board);
                    }
                    else
                    {
                        // Place the next piece.
                        GenerateSolutions(nextPieceIter);
                    }
                    PullRotation(rootOffset, rotation);
                }
            }
        }
    }
}

bool Board::PlaceRotation(size_t pieceNumber, const Offset& boardOffset, const Rotation& rotation)
{
    bool retVal = true;
    // First test all offsets in the rotation
    for (const Offset& rotationOffset : rotation.m_offsets)
    {
        if (GetOffsetState(boardOffset + rotationOffset) != OffsetState::Empty)
        {
            retVal = false;
            break;
        }
    }

    if (retVal)
    {
        // Temporarily place the rotation to test it out.
        for (const Offset& rotationOffset : rotation.m_offsets)
        {
            MarkBoardOffset(boardOffset + rotationOffset, pieceNumber);
        }

        // Test every border offset for this rotation by counting the connected block count.
        for (const Offset& borderOffset : rotation.m_borderingOffsets)
        {
            Offset testOffset(boardOffset + borderOffset);
            // If the border rotationOffset is empty, count the available connected blocks.
            if (GetOffsetState(testOffset) == OffsetState::Empty)
            {
                OffsetList tested;
                CountEmptyBlocks(testOffset, tested);
                // Undo the testing.
                for (const Offset& offsetToClear : tested)
                {
                    MarkBoardOffset(offsetToClear, OffsetState::Empty);
                }
                // If counting the connected empty blocks is not a multiple of the block count, then the placement is invalid.
                if (tested.size() % rotation.m_offsets.size() != 0)
                {
                    PullRotation(testOffset, rotation);
                    retVal = false;
                    break;
                }
            }
        }
    }

    return retVal;
}

void Board::PullRotation(const Offset& boardOffset, const Rotation& rotation)
{
    for (const Offset& offset : rotation.m_offsets)
    {
        MarkBoardOffset(boardOffset + offset, OffsetState::Empty);
    }
}

void Board::CountEmptyBlocks(const Offset& testOffset, OffsetList& tested)
{
    // Mark this rotationOffset as Test and look in all directions for more
    MarkBoardOffset(testOffset, OffsetState::Test);
    tested.push_back(testOffset);

    TestOffset(Direction::Right, testOffset, tested);
    TestOffset(Direction::Left, testOffset, tested);
    TestOffset(Direction::Up, testOffset, tested);
    TestOffset(Direction::Down, testOffset, tested);
}

void Board::TestOffset(Direction direction, const Offset& testOffset, OffsetList& tested)
{
    bool validDirection = false;

    switch (direction)
    {
    case Right:
    {
        if (testOffset.first < m_xDim - 1)
        {
            CountEmptyBlocks(Offset(testOffset.first + 1, testOffset.second), tested);
        }
        break;
    }
    case Left:
    {
        if (testOffset.first > 0)
        {
            CountEmptyBlocks(Offset(testOffset.first - 1, testOffset.second), tested);
        }
        break;
    }
    case Up:
    {
        if (testOffset.second < m_yDim - 1)
        {
            CountEmptyBlocks(Offset(testOffset.first, testOffset.second + 1), tested);
        }
        break;
    }
    case Down:
    {
        if (testOffset.second > 0)
        {
            CountEmptyBlocks(Offset(testOffset.first, testOffset.second - 1), tested);
        }
        break;
    }
    }
}
