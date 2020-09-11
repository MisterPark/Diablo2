#pragma once
#include "Tile.h"
class SubTile :
    public Tile
{
public:
    SubTile();

    virtual void Update() override;
    virtual void Render() override;


};

