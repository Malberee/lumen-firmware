#pragma once

class Rainbow : public BaseMode
{
    byte hue;
public:
    Rainbow();
    void initial() override;
    void tick() override;
};

extern Rainbow rainbow;