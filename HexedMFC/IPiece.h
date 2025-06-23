#pragma once
#include "Rotation.h"

class IPiece
{
    virtual bool IsEquivalent(OffsetList offsets) const = 0;
    virtual size_t GetPieceNumber() const = 0;
    virtual const RotationList& GetRotations() const = 0;
};
