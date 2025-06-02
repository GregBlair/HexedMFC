#include "pch.h"
#include "Piece.h"
#include <algorithm>

Piece::Piece(OffsetList offsets, size_t number)
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

void Piece::BuildRotations(const OffsetList& offsets)
{   
    Rotation rotation(offsets);
    TestFourRotations(rotation);
    // Reflect and try 4 more.
    rotation.ReflectOverX();
    TestFourRotations(rotation);
}

void Piece::AddRotation(const Rotation& rotation)
{
    m_rotations.push_back(rotation);
    m_hashes.push_back(rotation.m_hash);
}

void Piece::TestFourRotations(Rotation& rotation)
{
    if ((std::find(m_hashes.begin(), m_hashes.end(), rotation.m_hash) == m_hashes.end()))
    {
        AddRotation(rotation);
        // Rotate and add if the rotations produce a unique footprint
        for (int i = 0; i < 4; ++i)
        {
            rotation.Rotate90();
            if ((std::find(m_hashes.begin(), m_hashes.end(), rotation.m_hash) == m_hashes.end()))
            {
                // Rotating 4 times should produce the same block pattern.
                ASSERT(i != 3);
                AddRotation(rotation);
            }
        }
    }
}

