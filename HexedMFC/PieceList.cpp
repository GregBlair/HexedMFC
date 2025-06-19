#include "pch.h"
#include "PieceList.h"

#include <iostream>
#include <sstream>

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

void PieceList::TestCombos()
{
    // Build list of sequential integers and watch
    std::list<int> testList;
    for (int i = 1; i < 5; ++i)
    {
        testList.push_back(i);
        std::list<std::list<int>> testResults = GetCombinations(testList);
        std::stringstream str;
        str << std::endl << "Source list size: " << testList.size() << " Combos size: " << testResults.size() << "  ";
        TRACE(str.str().c_str());
        str.str(std::string());
        str << std::endl;
        for (const std::list<int>& temp : testResults)
        {
            str << "(";
            for (int combinations : temp)
            {
                str << " " << combinations;
            }
            str << " )" << std::endl;
            TRACE(str.str().c_str());
            str.str(std::string());
        }
    }
}

void PieceList::GeneratePieceList(size_t blockCount)
{
    // Just one seed location should do it.
    size_t cooridinateValue = (blockCount - 1) / 2;
    Offset seedOffset(cooridinateValue, cooridinateValue);
    OffsetList offsets{ seedOffset };
    NextOffset(offsets);
    size_t firstTry = m_pieceList.size();
    m_pieceList.clear();
    // Try all possible offset lists for the block count.
    for (int x = 0; x <= blockCount / 2; ++x)
    {
        Offset seedOffset(x, x);
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
        std::list<OffsetList> combos = GetCombinations(addedOffsets);

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

    template<typename T>
    std::list<std::list<T>> PieceList::GetCombinations(std::list<T> rightList)
    {
        std::list<std::list<T>> retVal;

        if (rightList.size() == 1)
        {
            // Add a list with the last element.
            // This element will appear at the end of the results.
            retVal.push_back(rightList);
        }
        else
        {
            std::list<T> leftList;
            // Split off the first element from the right list.
            leftList.splice(leftList.end(), rightList, rightList.begin());
            // Add the list of one element to the results
            retVal.push_back(leftList);
            // Get results from the remaining elements.
            std::list<std::list<T>> combinations = GetCombinations(rightList);
            for (const std::list<T>& valueList : combinations)
            {
                std::list<T> temp(leftList);
                // Append every result to the left list of one value.
                temp.insert(temp.end(), valueList.begin(), valueList.end());
                // Add this list to the results
                retVal.push_back(temp);
            }
            // Add in the results from the last recursion.
            retVal.splice(retVal.end(), combinations); // This preserves the order from the input list.
        }

        return retVal;
    }
