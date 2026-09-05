#pragma once

class DoubleFill : public BaseMode
{
    byte position;
    bool reverse;
public:
    void initial() override;
    void tick() override;
};

extern DoubleFill doubleFill;