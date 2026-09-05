#pragma once

class Fill : public BaseMode
{
    byte position;
    bool reverse;
public:
    void initial() override;
    void tick() override;
};

extern Fill fill;