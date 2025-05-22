#pragma once
#include <list>;

/// <summary>
/// 0 based offset from the origin (lower left)
/// </summary>
struct Offset
{
public:
    Offset(unsigned int x, unsigned int y);
    unsigned int m_x;
    unsigned int m_y;
};

typedef std::list<Offset> OffsetList;
