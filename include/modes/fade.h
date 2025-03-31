#pragma once

class Fade : public BaseMode
{
    byte brightness;
    bool increase;
public:
    Fade();
    void initial() override;
    void tick() override;
};

extern Fade fade;