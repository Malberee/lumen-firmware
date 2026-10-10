#pragma once

class LedCountSetup : public BaseMode
{
public:
    void initial() override;
};

extern LedCountSetup ledCountSetup;