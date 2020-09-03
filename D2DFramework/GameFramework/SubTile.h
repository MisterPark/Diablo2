#pragma once
#include "Tile.h"
class SubTile :
    public Tile
{
public:
    virtual void Update() override;
    virtual void Render() override;


};

