#pragma once

class Chrome : public BaseMode
{
    byte hue;

public:
    Chrome();
    void initial() override;
    void tick() override;
};

extern Chrome chrome;