#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray {

public:
    point3 origin;
    vec3 direction;
    double time;

public:
    ray() {}
    ray(const point3& _origin, const vec3& _direction, double _time = 0.0)
        : origin(_origin), direction(_direction), time(_time)
    {}

    inline point3 at(double t) const {
        return origin + t * direction;
    }
};


#endif
