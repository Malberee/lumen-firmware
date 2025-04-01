#pragma once

class Chroma : public BaseMode
{
    byte hue;
public:
    Chroma();
    void initial() override;
    void tick() override;
};

extern Chroma chroma;