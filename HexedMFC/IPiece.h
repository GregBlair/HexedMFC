#pragma once
#include "Offset.h"
class IPiece
{
    virtual bool isEquivalent(OffsetList offsets) = 0;
};

