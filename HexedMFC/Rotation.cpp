#include "pch.h"
#include "Rotation.h"

Rotation::Rotation(OffsetList offsets)
{
    m_offsets = offsets;
    BuildHash();
}

void Rotation::BuildHash()
{
    m_hash = 0;
    for (Offset offset : m_offsets)
    {
        m_hash += offset.m_x;
        m_hash += 1000 * offset.m_y;
    }
}

