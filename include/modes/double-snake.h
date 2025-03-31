#pragma once

class DoubleSnake : public BaseMode
{
public:
    void initial() override;
    void tick() override;
};

extern DoubleSnake doubleSnake;