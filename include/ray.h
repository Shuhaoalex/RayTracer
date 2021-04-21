#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray {

public:
    point3 origin;
    vec3 direction;

public:
    ray() {}
    ray(const point3& _origin, const vec3& _direction)
        : origin(_origin), direction(_direction)
    {}

    inline point3 at(double t) const {
        return origin + t * direction;
    }
};


#endif
