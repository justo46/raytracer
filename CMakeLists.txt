cmake_minimum_required(VERSION 3.27)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 23)

add_executable(ray_tracing main.cpp
        utils/Vec3.h
        utils/Color.h
        utils/Ray.h
        utils/Image.h
        utils/Camera.h
        objects/Sphere.h
        objects/Object.h
        objects/ObjectList.h
        utils/constants.h
        utils/Interval.h
        utils/OutputFile.h)
