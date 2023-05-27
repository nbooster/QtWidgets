#include "customqwtscaledraw.h"

CustomQwtScaleDraw::CustomQwtScaleDraw(const QwtScaleDiv &div, const uint_fast32_t rebaseStep)
    : QwtScaleDraw(),
      _rebaseStep(rebaseStep),
      _lowerBound(div.lowerBound()),
      _upperBound(div.upperBound())
{
    setMap(div);
    setScaleDiv(div);
}

void CustomQwtScaleDraw::update(const QwtScaleDiv &div)
{
    _lowerBound = div.lowerBound();
    _upperBound = div.upperBound();
    _map.clear();
    setMap(div);
    setScaleDiv(div);
}

QwtText CustomQwtScaleDraw::label(const double value) const
{
    const auto &[drawnValue, cond] = _map.value(value);
    if (cond)
    {
        return QwtScaleDraw::label(drawnValue);
    }
    if (drawnValue < 1000)
    {
        return QwtText("+" + QString::number(drawnValue));
    }
    else
    {
        const auto s = QString::number(drawnValue / 1000);
        return QwtText("+" + s.left(s.indexOf('.') + 3) + "K");
    }
}

void CustomQwtScaleDraw::setMap(const QwtScaleDiv &div)
{
    auto majorTicks = div.ticks(QwtScaleDiv::MajorTick);
    std::sort(majorTicks.begin(), majorTicks.end());
    double base = _lowerBound;
    double nextBase = base + _rebaseStep;
    _map.insert(base, { base, true });
    for (auto i = 1; i < majorTicks.size() - 1; ++i)
    {
        if (_map.contains(majorTicks.at(i)))
            continue;
        if (majorTicks.at(i) < nextBase)
        {
            _map.insert(majorTicks.at(i), { majorTicks.at(i) - base, false });
        }
        else if (majorTicks.at(i) > nextBase)
        {
            base = nextBase;
            nextBase += _rebaseStep;
            _map.insert(majorTicks.at(i), { majorTicks.at(i) - base, false });
        }
        else
        {
            base = nextBase;
            nextBase += _rebaseStep;
            _map.insert(majorTicks.at(i), { majorTicks.at(i), true });
        }
    }
    _map.insert(_upperBound, { _upperBound, true });
}
