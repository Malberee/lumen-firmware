#pragma once

class Carousel : public BaseMode
{
public:
    void initial() override;
    void tick() override;
};

extern Carousel carousel;