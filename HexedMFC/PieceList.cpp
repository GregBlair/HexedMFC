#include "pch.h"
#include "PieceList.h"

PieceList::PieceList()
{
    m_blockCount = 0;
}

 void PieceList::TestCombos()
{
     // Build list of sequential integers and watch
     std::list<int> testList{ 1, 2, 3 };
     std::list<std::list<int>> testResults;
     std::list<std::list<int>> retVal;
     TestAddToCombinations(testResults, retVal, testList);
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
    // Just one seed location should do it.
    size_t cooridinateValue = blockCount / 2;
    Offset seedOffset(cooridinateValue, cooridinateValue);
    OffsetList offsets{ seedOffset };
    NextOffset(offsets);
    size_t firstTry = m_pieceList.size();
    m_pieceList.clear();
    // Try all possible offset lists for the block count.
    for (int x = 0; x < blockCount / 2; ++x)
    {
        Offset seedOffset(cooridinateValue, cooridinateValue);
        OffsetList offsets{ seedOffset };
        NextOffset(offsets);
     }
    size_t secondTry = m_pieceList.size();
    ASSERT(firstTry == secondTry);
}

void PieceList::NextOffset(OffsetList offsets)
{
    OffsetList addedOffsets;
    // Try all directions.
    HandleNextOffset(Direction::Right, offsets, addedOffsets);
    HandleNextOffset(Direction::Left, offsets, addedOffsets);
    HandleNextOffset(Direction::Up, offsets, addedOffsets);
    HandleNextOffset(Direction::Down, offsets, addedOffsets);

    if (addedOffsets.size() > 0)
    {
        // Need to try all possible combinations of the offsets added at this level.
        std::list<OffsetList> combos = GenerateViableCombos(addedOffsets);

        for (const OffsetList& offsetList : combos)
        {
            // Add the entire offset list and try it.
            OffsetList existingOffsetListCopy = offsets;
            OffsetList newOffsetListCopy = offsetList;
            existingOffsetListCopy.splice(existingOffsetListCopy.end(), newOffsetListCopy);
            if (existingOffsetListCopy.size() == m_blockCount)
            {
                TryOffsets(existingOffsetListCopy);
            }
            else if (existingOffsetListCopy.size() < m_blockCount)
            {
                NextOffset(existingOffsetListCopy);
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
            break;
        }
    }

    if (!found)
    {
        m_pieceList.push_back(Piece(offsets, m_pieceList.size()));
    }
}

// Returns the count of blocks added, 1 or 0.
void PieceList::HandleNextOffset(Direction direction, OffsetList offsets, OffsetList& addedOffsets)
{
    Offset lastOffset = offsets.back();
    Offset nextOffset;
    bool validDirection = false;
    switch (direction)
    {
    case Right:
    {
        if (lastOffset.first < m_blockCount)
        {
            nextOffset = Offset(lastOffset.first + 1, lastOffset.second);
            validDirection = true;
        }
        break;
    }
    case Left:
    {
        if (lastOffset.first > 0)
        {
            nextOffset = Offset(lastOffset.first - 1, lastOffset.second);
            validDirection = true;
        }
        break;
    }
    case Up:
    {
        if (lastOffset.second < m_blockCount)
        {
            nextOffset = Offset(lastOffset.first, lastOffset.second + 1);
            validDirection = true;
        }
        break;
    }
    case Down:
    {
        if (lastOffset.second > 0)
        {
            nextOffset = Offset(lastOffset.first, lastOffset.second - 1);
            validDirection = true;
        }
        break;
    }
    }
    // If the offset is a valid direction and is not already occupied.
    if (validDirection &&
        std::find(offsets.begin(), offsets.end(), nextOffset) == offsets.end())
    {
        offsets.push_back(nextOffset);
        if (offsets.size() == m_blockCount)
        {
            TryOffsets(offsets);
            offsets.pop_back();
        }
        else
        {
            NextOffset(offsets);
            addedOffsets.push_back(nextOffset);
        }
    }
}

std::list<OffsetList> PieceList::GenerateViableCombos(const OffsetList& addedOffsets)
{
    std::list<OffsetList> retVal;
    // Create two list copies and start the recursion.
    AddToCombinations(retVal, OffsetList(addedOffsets));
    return retVal;
}

std::list<OffsetList> PieceList::AddToCombinations(std::list<OffsetList>& results, OffsetList right)
{
    std::list<OffsetList> retVal;
    // If we just have one piece left, add a list with just that piece and end the recursion.
    if (right.size() == 1)
    {
        results.push_back(right);
        retVal.push_back(right);
    }
    else
    {
        OffsetList left;
        // Move one element from rightList to left
        left.splice(left.end(), right, right.begin());
        //// Add both lists to the results.
        results.push_back(left);
        //results.push_back(rightList);
        retVal.push_back(left);
        retVal.push_back(right);
        // Add the left offset to every item from the next recursive call.
        // Add each transferred list to every subsequent list.
        for (OffsetList& offsetList : AddToCombinations(results, right))
        {
            OffsetList temp(left);
            // Put the left together with every result from the subsequent calls;
            temp.insert(temp.end(), offsetList.begin(), offsetList.end());
            results.push_back(temp);
            retVal.push_back(temp);
        }
    }
    //// Add each of the transferred lists to each of the subsequent lists.
    //if (rightList.size() > 1)
    //{
    //    OffsetList left;
    //    // Move one element from rightList to left
    //    left.splice(left.end(), rightList, rightList.begin());
    //    // Add both lists to the results.
    //    results.push_back(left);
    //    results.push_back(rightList);
    //    retVal.push_back(left);
    //    // Add the left offset to every item from the next recursive call.
    //    // Add each transferred list to every subsequent list.
    //    for (OffsetList& offsetList : AddToCombinations(results, rightList))
    //    {
    //        OffsetList temp(left);
    //        // Put the left together with every result from the subsequent calls;
    //        temp.insert(temp.end(), offsetList.begin(), offsetList.end());
    //        results.push_back(temp);
    //        retVal.push_back(temp);
    //    }
    //}

    return retVal;
}

std::list<std::list<int>> PieceList::TestAddToCombinations(std::list<std::list<int>>& results, std::list<std::list<int>>& retVal, std::list<int> rightList)
{
    // If we just have one int left, add a list with just that piece and end the recursion.
    if (rightList.size() == 1)
    {
        results.push_back(rightList);
        retVal.push_back(rightList);
    }
    else
    {
        auto beginIter = rightList.begin();
        auto endIter = rightList.end();
        //retVal.insert(retVal.end(), rightList.begin(), rightList.end());
        std::list<int> left;
        // Move one element from rightList to left
        left.splice(left.end(), rightList, rightList.begin());
        //// Add both lists to the results.
        results.push_back(left);
        //results.push_back(rightList);
        retVal.push_back(left);
        // Add the left offset to every item from the next recursive call.
        // Add each transferred list to every subsequent list.
        for (std::list<int>& integerList : TestAddToCombinations(results, retVal, rightList))
        {
            std::list<int> temp(left);
            // Put the left together with every result from the subsequent calls;
            auto beginIter = integerList.begin();
            auto endIter = integerList.end();
            temp.insert(temp.end(), integerList.begin(), integerList.end());
            results.push_back(temp);
            retVal.push_back(temp);
        }
    }

    return retVal;
}
