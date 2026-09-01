#pragma once

class Breathing : public BaseMode
{
    byte brightness;
    bool increase;
public:
    Breathing();
    void initial() override;
    void tick() override;
};

extern Breathing breathing;