#pragma once

#include <list>
#include <vector>

typedef std::pair<size_t, size_t> Offset;
inline Offset operator+(const Offset& lhs, const Offset& rhs)
{
    // Define how the addition should occur for the pair elements
    return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

typedef std::list<Offset> OffsetList;

class Rotation
{
public:
    OffsetList m_offsets;
    OffsetList m_borderingOffsets;
    size_t m_hash;
    Offset m_maxOffset;

    Rotation(const Rotation& rotation);
    Rotation(const OffsetList& offsets);
    Rotation() = delete;
    void Rotate90();
    void ReflectOverX();

private:
    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    void BuildHash();
    void Normalize();
    void BuildBorder(size_t blockCount);
    void TestOffset(Direction direction, const Offset& offset, size_t blockCount);
};

typedef std::vector<Rotation> RotationList;
