#include "pch.h"
#include "Piece.h"
#include <algorithm>

Piece::Piece(OffsetList offsets, unsigned int number)
{
    Rotation rotation(offsets);
    // Add the seed offset list as the default orientation.
    m_number = number;
    BuildRotations(offsets);
}

bool Piece::isEquivalent(OffsetList offsets)
{
    Rotation testRotation(offsets);
    return std::find(m_hashes.begin(), m_hashes.end(), testRotation.m_hash) != m_hashes.end();
}

void Piece::BuildRotations(OffsetList& offsets)
{   
    // Rotate and add if the rotations produce a unique footprint
    TestFourRotations(Rotation(offsets));
    // Rotate and reflect until we have tried all possibilities.
    Rotation reflected = ReflectOverX(offsets);
    TestFourRotations(reflected);
    // Add distinct rotations to the list of rotations.
}

Rotation Piece::Rotate90(Rotation rotation)
{
    OffsetList rotated;
    unsigned int blockCount = (unsigned int)rotation.m_offsets.size();

    // Move the piece up to make room for the rotation.
    for (Offset& offset : rotation.m_offsets)
    {
        rotated.push_back(Offset(offset.m_x, offset.m_y + blockCount));
    }

    // Rotate counterclockwise 90 and keep track of the min offsets.
    unsigned int minimumX = blockCount;
    unsigned int minimumY = blockCount;
    for (Offset& offset : rotated)
    {
        Offset temp = offset;
        offset.m_x = blockCount * 2 - temp.m_y;
        offset.m_y = temp.m_x;
        minimumX = min(minimumX, offset.m_x);
        minimumY = min(minimumY, offset.m_y);
    }

    // Translate to the lower left
    for (Offset& offset : rotated)
    {
        offset.m_x -= minimumX;
        offset.m_y -= minimumY;
    }

    return Rotation(rotated);
}

Rotation Piece::ReflectOverX(Rotation rotation)
{
    unsigned int blockCount = (unsigned int)rotation.m_offsets.size();

    // To be safe reflect over the line y = block count.
    unsigned int minimumX = blockCount;
    unsigned int minimumY = blockCount;
    for (Offset& offset : rotation.m_offsets)
    {
        offset.m_y = blockCount - offset.m_y;
        minimumX = min(minimumX, offset.m_x);
        minimumY = min(minimumY, offset.m_y);
    }

    // Translate to the lower left
    for (Offset& offset : rotation.m_offsets)
    {
        offset.m_x -= minimumX;
        offset.m_y -= minimumY;
    }

    return Rotation(rotation);
}

void Piece::AddRotation(Rotation rotation)
{
    m_rotations.push_back(rotation);
    m_hashes.push_back(rotation.m_hash);
}

void Piece::TestFourRotations(Rotation rotation)
{
    Rotation testRotation(rotation.m_offsets);
    if ((std::find(m_hashes.begin(), m_hashes.end(), testRotation.m_hash) == m_hashes.end()))
    {
        AddRotation(testRotation);
    }

    for (int i = 0; i < 4; ++i)
    {
        testRotation = Rotate90(testRotation);
        if ((std::find(m_hashes.begin(), m_hashes.end(), testRotation.m_hash) == m_hashes.end()))
        {
            // Rotating 4 times should produce the same block pattern.
            ASSERT(i != 3);
            AddRotation(testRotation);
        }
    }
}

