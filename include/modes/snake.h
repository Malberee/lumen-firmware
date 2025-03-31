#pragma once

class Snake : public BaseMode
{
public:
    void initial() override;
    void tick() override;
};

extern Snake snake;