#include "pch.h"
#include "PieceList.h"

PieceList::PieceList()
{
    m_blockCount = 0;
}

bool PieceList::SetBlockCount(unsigned int blockCount)
{
    if (blockCount > 2 && blockCount < 7)
    {
        m_blockCount = blockCount;
        GeneratePieceList(blockCount);
        return true;
    }
    else
    {
        return false;
    }
}

void PieceList::GeneratePieceList(unsigned int blockCount)
{
    // Try all possible offset lists for the block count.
    for (int x = 0; x < blockCount; ++x)
    {
        for (int y = 0; y < blockCount; ++y)
        {
            // Use this point as the first offset
            OffsetList offsets{ Offset(x, y) };
            NextOffset (offsets);
        }
    }
}

OffsetList PieceList::NextOffset(OffsetList& offsets)
{
    // Terminate recursiion and try the piece.
    if (offsets.size() == m_blockCount)
    {
        TryOffsets(offsets);
    }
    else
    {
        Offset lastOffset = offsets.back();
        // Try all directions.
        // Right
        if (lastOffset.m_x < m_blockCount)
        {
            Offset nextOffset(lastOffset.m_x + 1, lastOffset.m_y);
            if (std::find(offsets.begin(), offsets.end(), nextOffset) == offsets.end())
            {
                offsets.push_back(nextOffset);
                NextOffset(offsets);
                offsets.pop_back();
            }
        }
        // Left
        if (lastOffset.m_x > 0)
        {
            Offset nextOffset(lastOffset.m_x - 1, lastOffset.m_y);
            if (std::find(offsets.begin(), offsets.end(), nextOffset) == offsets.end())
            {
                offsets.push_back(Offset(lastOffset.m_x - 1, lastOffset.m_y));
                NextOffset(offsets);
                offsets.pop_back();
            }
        }
        // Up
        if (lastOffset.m_y < m_blockCount)
        {
            Offset nextOffset(lastOffset.m_x, lastOffset.m_y + 1);
            if (std::find(offsets.begin(), offsets.end(), nextOffset) == offsets.end())
            {
                offsets.push_back(Offset(lastOffset.m_x, lastOffset.m_y + 1));
                NextOffset(offsets);
                offsets.pop_back();
            }
        }
        // Down
        if (lastOffset.m_y > 0)
        {
            Offset nextOffset(lastOffset.m_x, lastOffset.m_y - 1);
            if (std::find(offsets.begin(), offsets.end(), nextOffset) == offsets.end())
            {
                offsets.push_back(Offset(lastOffset.m_x, lastOffset.m_y - 1));
                NextOffset(offsets);
                offsets.pop_back();
            }
        }
    }
    return offsets;
}

void PieceList::TryOffsets(OffsetList& offsets)
{
    // Look for an equivalent piece in the existing pieces.
    bool found = false;
    for (Piece piece : m_pieceList)
    {
        if (piece.isEquivalent(offsets))
        {
            found = true;
        }
    }

    if (!found)
    {
        m_pieceList.push_back(Piece(offsets, m_pieceList.size()));
    }
}
