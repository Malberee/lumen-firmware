#pragma once

class Carousel : public BaseMode
{
public:
    Carousel();
    void initial() override;
    void tick() override;
};

extern Carousel carousel;