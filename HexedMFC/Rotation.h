#pragma once

#include <list>
#include <vector>

typedef std::pair<size_t, size_t> Offset;
typedef std::list<Offset> OffsetList;

class Rotation
{
public:
    OffsetList m_offsets;
    OffsetList m_borderingOffsets;
    size_t m_hash;

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

