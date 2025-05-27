#pragma once
#include <list>;

/// <summary>
/// 0 based offset from the origin (lower left)
/// </summary>
struct Offset
{
public:
    Offset() = delete;
    Offset(unsigned int x, unsigned int y);
    unsigned int m_x;
    unsigned int m_y;

    bool operator==(const Offset& other) const {
        return
            m_x == other.m_x &&
            m_y == other.m_y;
    }
};

typedef std::list<Offset> OffsetList;
