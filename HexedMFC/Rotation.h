#pragma once

#include <list>
#include <vector>

typedef std::pair<size_t, size_t> Offset;
typedef std::list<Offset> OffsetList;

class Rotation
{
public:
    OffsetList m_offsets;
    size_t m_hash;

    Rotation(const Rotation& rotation);
    Rotation(const OffsetList& offsets);
    Rotation() = delete;
    void BuildHash();
    void Rotate90();
    void ReflectOverX();
    void Normalize();
};

typedef std::vector<Rotation> RotationList;

