//
// Created by Julius Stotz on 10.01.24.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "Object.h"

class Sphere : public Object {
public:
    Sphere() = delete;

    Sphere(const Point3 &center, double radius) {
        this->center = center;
        this->radius = radius;
    }

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override {
        Vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (-half_b + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        Vec3 outward_normal = (rec.p - center) / radius;
        rec.setFaceNormal(r, outward_normal);

        return true;
    }

private:
    Point3 center;
    double radius;
};

#endif //RAY_TRACING_SPHERE_H
