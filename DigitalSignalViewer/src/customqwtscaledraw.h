#pragma once

#include <qwt_scale_draw.h>

class CustomQwtScaleDraw : public QwtScaleDraw
{
public:
    explicit CustomQwtScaleDraw(const QwtScaleDiv &, const uint_fast32_t rebaseStep = 2000);
    virtual ~CustomQwtScaleDraw() = default;
    virtual QwtText label(const double value) const override;
    void update(const QwtScaleDiv &div);

private:
    void setMap(const QwtScaleDiv &);

private:
    uint_fast32_t _rebaseStep;
    uint_fast32_t _lowerBound;
    uint_fast32_t _upperBound;
    QMap<double, std::pair<double, bool>> _map;
};
