#ifndef __ATOMIC_COORDINATES_H__
#define __ATOMIC_COORDINATES_H__

#include "coordinates.h"
#include <atomic>


struct AtomicCoordinates{
    public:
    std::atomic<double> x;
    std::atomic<double> y;

    AtomicCoordinates(): x(0), y(0) {}
    AtomicCoordinates(Coordinates& c): x(c.x), y(c.y) {
    }
    void operator()(Coordinates& c) {
        x = c.x;
        y = c.y;
    }
};

#endif
