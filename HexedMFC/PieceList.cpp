#include "pch.h"
#include "PieceList.h"

PieceList::PieceList()
{
    m_blockCount = 0;
}

bool PieceList::SetBlockCount(size_t blockCount)
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

void PieceList::NextOffsetSnakes(OffsetList& offsets)
{
    // Terminate recursion and try the piece.
    if (offsets.size() == m_blockCount)
    {
        TryOffsets(offsets);
    }
    else
    {
        Offset lastOffset = offsets.back();
        // Try all directions.
        // Right
        if (lastOffset.first < m_blockCount)
        {
            HandleNextOffsetSnakes(Offset(lastOffset.first + 1, lastOffset.second), offsets);
        }
        // Left
        if (lastOffset.first > 0)
        {
            HandleNextOffsetSnakes(Offset(lastOffset.first - 1, lastOffset.second), offsets);
        }
        // Up
        if (lastOffset.first < m_blockCount)
        {
            HandleNextOffsetSnakes(Offset(lastOffset.first, lastOffset.second + 1), offsets);
        }
        // Down
        if (lastOffset.second > 0)
        {
            HandleNextOffsetSnakes(Offset(lastOffset.first, lastOffset.second - 1), offsets);
        }
    }
}

void PieceList::NextOffsetGlobs(OffsetList offsets, Offset lastOffset)
{
    OffsetList addedOffsets;
    // Try all directions.
    // Right
    if (lastOffset.first < m_blockCount)
    {
        HandleNextOffsetGlobs(lastOffset, Direction::Right, offsets, addedOffsets);
    }
    // Left
    if (lastOffset.first > 0)
    {
        HandleNextOffsetGlobs(lastOffset, Direction::Left, offsets, addedOffsets);
    }
    // Up
    if (lastOffset.second < m_blockCount)
    {
        HandleNextOffsetGlobs(lastOffset, Direction::Up, offsets, addedOffsets);
    }
    // Down
    if (lastOffset.second > 0)
    {
        HandleNextOffsetGlobs(lastOffset, Direction::Down, offsets, addedOffsets);
    }

    //if (addedOffsets.size() > 0)
    //{
    //    // Generate a list of all combinations of the added offsets, with more than 1 element in the list.
    //    if (addedOffsets.size() + offsets.size() == m_blockCount)
    //    {
    //        auto endIter = offsets.end();
    //        offsets.insert(offsets.end(), addedOffsets.begin(), addedOffsets.end());
    //        TryOffsets(offsets);
    //        for (int i = 0; i < addedOffsets.size(); ++i)
    //        {
    //            offsets.pop_back();
    //        }
    //        offsets.erase(endIter, offsets.end());
    //    }
    //    else if (addedOffsets.size() + offsets.size() < m_blockCount)
    //    {
    //        // Add all blocks to the offsets and try each one as the last offset
    //        offsets.splice(offsets.end(), addedOffsets);
    //        for (Offset offset : addedOffsets)
    //        {
    //            NextOffsetGlobs(offsets, offset);
    //        }
    //    }
    //}

    // Need to try all possible combinations of the offsets added at this level.
    std::list<OffsetList> combos = GenerateViableCombos(addedOffsets);

    for (OffsetList offsetList : combos)
    {
        size_t count = offsetList.size();
        for (Offset offset : offsetList)
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

    //if (offsets.size() == m_blockCount)
    //{
    //    TryOffsets(offsets);
    //}
    //else
    //{
    //    // Need to try every offset added at this level
    //    for (Offset offset : addedOffsets)
    //    {
    //        NextOffsetGlobs(offsets, offset);
    //    }
    //}

    //// Clean up this level
    //while (addedOffsets.size() > 0)
    //{
    //    offsets.pop_back();
    //    NextOffsetGlobs(offsets, addedOffsets.back());
    //    addedOffsets.pop_back();
    //}
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

// Returns the count of blocks added, 1 or 0.
void PieceList::HandleNextOffsetSnakes(Offset& nextOffset, OffsetList& offsets)
{
    // If the offset is not already occupied.
    if (std::find(offsets.begin(), offsets.end(), nextOffset) == offsets.end())
    {
        offsets.push_back(nextOffset);
        NextOffsetSnakes(offsets);
        offsets.pop_back();
    }
}

// Returns the count of blocks added, 1 or 0.
void PieceList::HandleNextOffsetGlobs(const Offset& lastOffset, Direction direction, OffsetList offsets, OffsetList& addedOffsets)
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
