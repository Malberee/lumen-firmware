#pragma once

class Breathing : public BaseMode
{
    byte brightness;
    bool increasing;
public:
    Breathing();
    void initial() override;
    void tick() override;
};

extern Breathing breathing;