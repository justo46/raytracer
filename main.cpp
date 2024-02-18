#include "objects/ObjectList.h"
#include "objects/Sphere.h"
#include "utils/Camera.h"
#include "utils/Color.h"
#include "utils/OutputFile.h"
#include "utils/constants.h"

int main() {
  Camera cam;
  cam.focal_length = 1.0;
  cam.image = Image(400, 16.0 / 9.0);
  cam.center = Point3(0, 0, 0);
  cam.viewport_height = 2.0;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  // Objects

  ObjectList world = ObjectList();
  world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  // Render

  cam.render(world);
}
