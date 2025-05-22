#include "pch.h"
#include "PieceList.h"

PieceList::PieceList(unsigned int blockCount)
{
    m_blockCount = blockCount;
    GeneratePieceList(blockCount);
}

void PieceList::GeneratePieceList(unsigned int blockCount)
{
    // Try all possible offset lists for the block count.
    for (int x = 0; ++x; x < blockCount)
    {
        for (int y = 0; ++y; y < blockCount)
        {
            // Use this point as the first offset
        }
    }
}

OffsetList PieceList::NextOffset(OffsetList offsets)
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
            offsets.push_back(Offset(lastOffset.m_x + 1, lastOffset.m_y));
            NextOffset(offsets);
            offsets.pop_back();
        }
        // Left
        if (lastOffset.m_x > 0)
        {
            offsets.push_back(Offset(lastOffset.m_x - 1, lastOffset.m_y));
            NextOffset(offsets);
            offsets.pop_back();
        }
        // Up
        if (lastOffset.m_y < m_blockCount)
        {
            offsets.push_back(Offset(lastOffset.m_x, lastOffset.m_y + 1));
            NextOffset(offsets);
            offsets.pop_back();
        }
        // Down
        if (lastOffset.m_y > 0)
        {
            offsets.push_back(Offset(lastOffset.m_x, lastOffset.m_y - 1));
            NextOffset(offsets);
            offsets.pop_back();
        }
    }
    return offsets;
}

void PieceList::TryOffsets(OffsetList offsets)
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
