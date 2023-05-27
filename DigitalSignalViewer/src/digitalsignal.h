#pragma once

#include <QString>
#include <execution>
#include <vector>

/*! A class for holding the data of each signal. */
class DigitalSignal
{
public:
    explicit DigitalSignal(const std::vector<std::pair<int, bool>> &data);
    DigitalSignal(const std::initializer_list<std::pair<int, bool>> &il);

public:
    std::vector<std::pair<int, bool>> data; // signal's value at each time point (in nanosecs)
};
