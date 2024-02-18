//
// Created by Julius Stotz on 10.01.24.
//

#ifndef RAY_TRACING_OBJECT_H
#define RAY_TRACING_OBJECT_H

#include "../utils/Ray.h"

class HitRecord {
public:
    Point3 p;
    Vec3 normal;
    double t;
    bool front_face;

    void setFaceNormal(const Ray& r, const Vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }

};

class Object {
public:
    virtual ~Object() = default;

    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};

#endif //RAY_TRACING_OBJECT_H
