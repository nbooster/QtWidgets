#include "digitalsignal.h"

DigitalSignal::DigitalSignal(const std::vector<std::pair<int, bool>> &arg) : data(arg)
{
    std::sort(std::execution::par_unseq, data.begin(), data.end(),
              [](std::pair<int, bool> const &a, std::pair<int, bool> const &b) {
                  return a.first < b.first;
              });

    data.erase(std::unique(std::execution::par_unseq, data.begin(), data.end(),
                           [](std::pair<int, bool> const &a, std::pair<int, bool> const &b) {
                               return a.first == b.first;
                           }),
               data.end());
}

DigitalSignal::DigitalSignal(const std::initializer_list<std::pair<int, bool>> &il) : data(il) {}
