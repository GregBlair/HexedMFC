#pragma once

#include <list>
#include <vector>

#include "IRotation.h"

typedef std::pair<size_t, size_t> Offset;
inline Offset operator+(const Offset& lhs, const Offset& rhs)
{
    // Define how the addition should occur for the pair elements
    return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

typedef std::list<Offset> OffsetList;

class Rotation : public IRotation
{
public:
    Rotation(const Rotation& rotation);
    Rotation(const OffsetList& offsets);
    Rotation() = delete;
    void Rotate90();
    void ReflectOverX();

    inline OffsetList GetOffsets() const { return m_offsets; }
    inline OffsetList GetBorderingOffsets() const { return m_borderingOffsets; }
    inline size_t GetHash() const { return m_hash; }

private:
    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    size_t m_hash;
    Offset m_maxOffset;
    OffsetList m_offsets;
    OffsetList m_borderingOffsets;

    void BuildHash();
    void Normalize();
    void BuildBorder(size_t blockCount);
    void TestOffset(Direction direction, const Offset& offset, size_t blockCount);
};

typedef std::vector<Rotation> RotationList;
