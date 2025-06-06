#pragma once
#include "Rotation.h"

class IPiece
{
    virtual bool isEquivalent(OffsetList offsets) const = 0;
};

