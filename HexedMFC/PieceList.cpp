#include "pch.h"
#include "PieceList.h"

PieceList::PieceList()
{
    m_blockCount = 0;
}

bool PieceList::SetBlockCount(size_t blockCount)
{
    if (blockCount < 9)
    {
        m_pieceList.clear();
        m_blockCount = blockCount;
        GeneratePieceList(blockCount);
        return true;
    }
    else
    {
        return false;
    }
}

void PieceList::GeneratePieceList(size_t blockCount)
{
    // Try all possible offset lists for the block count.
    for (int x = 0; x < blockCount / 2; ++x)
    {
        Offset seedOffset(x, x);
        OffsetList offsets{ seedOffset };
        NextOffsetGlobs(offsets, seedOffset);
     }
}

void PieceList::NextOffsetGlobs(OffsetList offsets, Offset lastOffset)
{
    OffsetList addedOffsets;
    // Try all directions.
    // Right
    if (lastOffset.first < m_blockCount)
    {
        HandleNextOffset(lastOffset, Direction::Right, offsets, addedOffsets);
    }
    // Left
    if (lastOffset.first > 0)
    {
        HandleNextOffset(lastOffset, Direction::Left, offsets, addedOffsets);
    }
    // Up
    if (lastOffset.second < m_blockCount)
    {
        HandleNextOffset(lastOffset, Direction::Up, offsets, addedOffsets);
    }
    // Down
    if (lastOffset.second > 0)
    {
        HandleNextOffset(lastOffset, Direction::Down, offsets, addedOffsets);
    }

    // Need to try all possible combinations of the offsets added at this level.
    std::list<OffsetList> combos = GenerateViableCombos(addedOffsets);

    for (OffsetList& offsetList : combos)
    {
        size_t count = offsetList.size();
        for (Offset& offset : offsetList)
        {
            // Add the offsets to the current list and try again.
            // Copy the offset lists so they can be reused.
            OffsetList existingOffsetListCopy = offsets;
            OffsetList newOffsetListCopy = offsetList;
            existingOffsetListCopy.splice(existingOffsetListCopy.end(), newOffsetListCopy);
            if (existingOffsetListCopy.size() == m_blockCount)
            {
                TryOffsets(existingOffsetListCopy);
            }
            else if (existingOffsetListCopy.size() < m_blockCount)
            {
                NextOffsetGlobs(existingOffsetListCopy, existingOffsetListCopy.back());
            }
        }
    }
}

void PieceList::TryOffsets(OffsetList& offsets)
{
    // Look for an equivalent piece in the existing pieces.
    bool found = false;
    for (const Piece& piece : m_pieceList)
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

// Returns the count of blocks added, 1 or 0.
void PieceList::HandleNextOffset(const Offset& lastOffset, Direction direction, OffsetList offsets, OffsetList& addedOffsets)
{
    Offset nextOffset;
    switch (direction)
    {
    case Up:
        nextOffset = Offset(lastOffset.first, lastOffset.second + 1);
        break;
    case Right:
        nextOffset = Offset(lastOffset.first + 1, lastOffset.second);
        break;
    case Down:
        nextOffset = Offset(lastOffset.first, lastOffset.second - 1);
        break;
    case Left:
        nextOffset = Offset(lastOffset.first - 1, lastOffset.second);
        break;
    }
    // If the offset is not already occupied.
    if (std::find(offsets.begin(), offsets.end(), nextOffset) == offsets.end())
    {
        offsets.push_back(nextOffset);
        if (offsets.size() == m_blockCount)
        {
            TryOffsets(offsets);
            offsets.pop_back();
        }
        else
        {
            NextOffsetGlobs(offsets, nextOffset);
            addedOffsets.push_back(nextOffset);
        }
    }
}

std::list<OffsetList> PieceList::GenerateViableCombos(const OffsetList& addedOffsets)
{
    std::list<OffsetList> retVal;
    // Create two list copies and start the recursion.
    OffsetList original = addedOffsets;
    OffsetList transfered;
    AddToCombinations(retVal, original, transfered);
    return retVal;
}

void PieceList::AddToCombinations(std::list<OffsetList>& listOfLists, const OffsetList& original, const OffsetList& transfered)
{
    for (Offset offset : original)
    {
        OffsetList originalCopy = original;
        OffsetList transferedCopy = transfered;
        auto iter = std::find(originalCopy.begin(), originalCopy.end(), offset);
        transferedCopy.splice(transferedCopy.end(), originalCopy, iter);
        listOfLists.push_back(transferedCopy);
        AddToCombinations(listOfLists, originalCopy, transferedCopy);
    }
}
