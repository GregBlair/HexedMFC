#pragma once

#include "IPiece.h"
#include "Rotation.h"

class Piece :
    public IPiece
{
public:

    size_t m_number;
    RotationList m_rotations;
    std::list<size_t> m_hashes;

    Piece(OffsetList offsets, size_t number);
    Piece() = delete;
    bool isEquivalent(OffsetList offsets) override;

private:

    void BuildRotations(const OffsetList& offsets);
    void AddRotation(const Rotation& rotation);
    void TestFourRotations(Rotation& rotation);
};

