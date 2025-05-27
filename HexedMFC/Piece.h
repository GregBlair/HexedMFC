#pragma once

#include "IPiece.h"
#include "Rotation.h"

class Piece :
    public IPiece
{
public:

    unsigned int m_number;
    RotationList m_rotations;
    std::list<unsigned int> m_hashes;

    Piece(OffsetList offsets, unsigned int number);
    Piece() = delete;
    bool isEquivalent(OffsetList offsets) override;

private:

    void BuildRotations(OffsetList& offsets);
    static Rotation Rotate90(Rotation rotation);
    static Rotation ReflectOverX(Rotation rotation);
    void AddRotation(Rotation rotation);
    void TestFourRotations(Rotation rotation);
};

