#pragma once

#include "IPiece.h"
#include "Rotation.h"

class Piece :
    public IPiece
{
public:

    const RotationList& GetRotations() const { return m_rotations; }
    size_t m_number;
    std::list<size_t> m_hashes;

    Piece(OffsetList offsets, size_t number);
    Piece() = delete;
    bool isEquivalent(OffsetList offsets) const override;

private:

    RotationList m_rotations;

    void BuildRotations(const OffsetList& offsets);
    void AddRotation(const Rotation& rotation);
    void TestFourRotations(Rotation& rotation);
};

