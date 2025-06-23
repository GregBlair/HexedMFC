#pragma once

#include "Piece.h"

class IPieceList
{
    virtual bool SetBlockCount(size_t blockCount) = 0;
    virtual void TestCombos() = 0;
    virtual size_t GetBlockCount() const = 0;
    virtual const std::list<Piece>& GetPieceList() const = 0;
};
