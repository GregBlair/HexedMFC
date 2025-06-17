#include "pch.h"
#include "Rotation.h"

Rotation::Rotation(const Rotation& rotation)
{
    m_offsets = rotation.m_offsets;
    Normalize();
}

Rotation::Rotation(const OffsetList& offsets)
{
    m_offsets = offsets;
    Normalize();
}

void Rotation::BuildHash()
{
    m_hash = 0;
    for (Offset offset : m_offsets)
    {
        m_hash += 1009 * offset.first * offset.first + 10013 * offset.second * offset.second;
    }
}

void Rotation::Rotate90()
{
    size_t blockCount = m_offsets.size();

    // Rotate counterclockwise 90 and keep track of the min offsets.
    for (Offset& offset : m_offsets)
    {
        Offset temp = offset;
        // Move the piece up to make room for the rotation.
        offset.second = blockCount + temp.first;
        // Bump the piece right by a safe distance.
        offset.first = blockCount * 2 - temp.second;
    }

    Normalize();
}

void Rotation::ReflectOverX()
{
    size_t blockCount = m_offsets.size();

    // To be safe reflect over the line y = block count.
    for (Offset& offset : m_offsets)
    {
        offset.second = blockCount - offset.second;
    }

    Normalize();
}

void Rotation::Normalize()
{
    size_t blockCount = m_offsets.size();

    // Find the minimum x and y values.  Start way out since some blocks might be kicked way out.
    size_t minimumX = blockCount * 3;
    size_t minimumY = blockCount * 3;
    for (Offset& offset : m_offsets)
    {
        minimumX = min(minimumX, offset.first);
        minimumY = min(minimumY, offset.second);
    }

    // Translate to the lower left
    for (Offset& offset : m_offsets)
    {
        offset.first -= minimumX;
        offset.second -= minimumY;
    }

    BuildHash();
    BuildBorder(blockCount);
}

void Rotation::BuildBorder(size_t blockCount)
{
    // For every offset, look in all 4 directions to see if we find a value not in either list.
    for (const Offset& offset : m_offsets)
    {
        TestOffset(Direction::Right, offset, blockCount);
        TestOffset(Direction::Left, offset, blockCount);
        TestOffset(Direction::Up, offset, blockCount);
        TestOffset(Direction::Down, offset, blockCount);
    }
}

void Rotation::TestOffset(Direction direction, const Offset& offset, size_t blockCount)
{
    Offset testOffset;
    bool validDirection = false;

    switch (direction)
    {
    case Right:
    {
        if (offset.first < blockCount)
        {
            testOffset = Offset(offset.first + 1, offset.second);
            validDirection = true;
        }
        break;
    }
    case Left:
    {
        if (offset.first > 0)
        {
            testOffset = Offset(offset.first - 1, offset.second);
            validDirection = true;
        }
        break;
    }
    case Up:
    {
        if (offset.second < blockCount)
        {
            testOffset = Offset(offset.first, offset.second + 1);
            validDirection = true;
        }
        break;
    }
    case Down:
    {
        if (offset.second > 0)
        {
            testOffset = Offset(offset.first, offset.second - 1);
            validDirection = true;
        }
        break;
    }
    }

    if (validDirection &&
        std::find(m_offsets.begin(), m_offsets.end(), testOffset) == m_offsets.end() &&
        std::find(m_borderingOffsets.begin(), m_borderingOffsets.end(), testOffset) == m_borderingOffsets.end())
    {
        m_borderingOffsets.push_back(testOffset);
    }
}
