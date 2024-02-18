#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include "Vec3.h"
#include "Image.h"
#include "Color.h"
#include "../objects/ObjectList.h"

class Camera {
public:
    double focal_length = 2.0;
    Image image = Image(400, 16.0 / 9.0);  // Rendered image width in pixel count
    Point3 center = Point3(0, 0, 0);
    double viewport_height = 2.0;
    int samples_per_pixel = 100;
    int max_depth = 10;

    void render(const Object &world) {
        initialize();

        for (int j = 0; j < image.height; ++j) {
            std::clog << "\rScanlines remaining: " << (image.height - j) << ' ' << std::flush;
            for (int i = 0; i < image.width; ++i) {
                Color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    Ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(outputFile, pixel_color, samples_per_pixel);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
    Vec3 pixel00_loc;
    // Not sure if the camera should be responsible for the output file
    OutputFile outputFile = OutputFile("out.ppm", image);

    void initialize() {
        auto viewport_width = viewport_height * (static_cast<double>(image.width) / image.height);

        auto viewport_u = Vec3(viewport_width, 0, 0);
        auto viewport_v = Vec3(0, -viewport_height, 0);
        this->pixel_delta_u = viewport_u / image.width;
        this->pixel_delta_v = viewport_v / image.height;
        auto viewport_upper_left = center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        this->pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    Ray get_ray(int i, int j) const {
        // Get a randomly sampled camera ray for the pixel at location i,j.

        auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto pixel_sample = pixel_center + pixel_sample_square();

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

    Vec3 pixel_sample_square() const {
        // Returns a random point in the square surrounding a pixel at the origin.
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }

    Color ray_color(const Ray &r, int depth, const Object &world) const {
        HitRecord rec;

        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return Color(0, 0, 0);

        if (world.hit(r, Interval(0.001, infinity), rec)) {
            Vec3 direction = rec.normal + random_unit_vector();
            // See CG slides for the factor: dot(rec.normal, unit_vector(direction)) (Lambertian reflectance)
            return 0.3 * ray_color(Ray(rec.p, direction), depth - 1, world);
        }

        Vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }
};

#endif //RAY_TRACING_CAMERA_H
