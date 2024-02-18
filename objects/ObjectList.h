#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "Object.h"

class ObjectList : public Object {
public:
    std::vector<std::shared_ptr<Object>> objects;

    ObjectList() {}
    ObjectList(std::shared_ptr<Object> object) { add(object); }

    void clear() { objects.clear(); }

    void add(std::shared_ptr<Object> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif
