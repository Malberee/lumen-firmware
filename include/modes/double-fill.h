#pragma once

class DoubleFill : public BaseMode
{
    byte position;
    bool reverse;
public:
    DoubleFill();
    void initial() override;
    void tick() override;
};

extern DoubleFill doubleFill;