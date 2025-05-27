#pragma once
#include "Offset.h"
class Rotation
{
public:
    OffsetList m_offsets;
    unsigned int m_hash;

    Rotation(OffsetList offsets);
    Rotation() = delete;
    void BuildHash();
};

typedef std::list<Rotation> RotationList;

