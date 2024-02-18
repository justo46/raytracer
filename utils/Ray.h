//
// Created by Julius Stotz on 10.01.24.
//

#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H

#include "Vec3.h"

class Ray {
public:

    Ray() = default;

    Ray(const Point3 &origin, const Vec3 &direction)
            : orig(origin), dir(direction) {}

    Point3 origin() const { return orig; }

    Vec3 direction() const { return dir; }

    Point3 at(double t) const {
        return orig + t * dir;
    }

private:
    Point3 orig;
    Vec3 dir;
};

#endif //RAY_TRACING_RAY_H
