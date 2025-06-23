#pragma once

#include "IPiece.h"
#include "Rotation.h"

class Piece : public IPiece
{
public:

    Piece(OffsetList offsets, size_t number);
    Piece() = delete;

    bool IsEquivalent(OffsetList offsets) const override;
    size_t GetPieceNumber() const override { return m_number; }
    const RotationList& GetRotations() const override { return m_rotations; }

private:

    size_t m_number;
    std::list<size_t> m_hashes;
    RotationList m_rotations;

    void BuildRotations(const OffsetList& offsets);
    void AddRotation(const Rotation& rotation);
    void TestFourRotations(Rotation& rotation);
};

