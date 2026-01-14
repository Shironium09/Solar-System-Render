#ifndef PLANETS_H
#define PLANETS_H

#include "functions.h"

inline Planet Sun(){

    Planet sun;
    sun.position[0] = 0.0f;
    sun.position[1] = 0.0f;
    sun.radius = 0.12f;
    sun.orbit_speed = 0.0f;
    sun.orbit_radius = 0.0f;

return sun;
}

inline Planet Mercury(){

    Planet mercury;
    mercury.radius = 0.012f;
    mercury.orbit_radius = 0.18f;
    mercury.orbit_speed = 0.8f;
    mercury.orbit_angle = 1.0f;

return mercury;
}

inline Planet Venus(){

    Planet venus;
    venus.radius = 0.024f;
    venus.orbit_radius = 0.27f;
    venus.orbit_speed = 0.6f;
    venus.orbit_angle = 3.5f;

return venus;
}

inline Planet Earth(){

    Planet earth;
    earth.radius = 0.025f;
    earth.orbit_radius = 0.36f;
    earth.orbit_speed = 0.5f;
    earth.orbit_angle = 5.5f;

return earth;
}

inline Planet Mars(){

    Planet mars;
    mars.radius = 0.018f;
    mars.orbit_radius = 0.45f;
    mars.orbit_speed = 0.4f;
    mars.orbit_angle = 2.0f;

return mars;
}

inline Planet Jupiter(){

    Planet jupiter;
    jupiter.radius = 0.055f;
    jupiter.orbit_radius = 0.60f;
    jupiter.orbit_speed = 0.2f;
    jupiter.orbit_angle = 0.5f;

return jupiter;
}

inline Planet Saturn(){

    Planet saturn;
    saturn.radius = 0.045f;
    saturn.orbit_radius = 0.73f;
    saturn.orbit_speed = 0.15f;
    saturn.orbit_angle = 4.0f;

return saturn;
}

inline Planet Uranus(){

    Planet uranus;
    uranus.radius = 0.032f;
    uranus.orbit_radius = 0.84f;
    uranus.orbit_speed = 0.1f;
    uranus.orbit_angle = 1.5f;

return uranus;
}

inline Planet Neptune(){

    Planet neptune;
    neptune.radius = 0.030f;
    neptune.orbit_radius = 0.93f;
    neptune.orbit_speed = 0.08f;
    neptune.orbit_angle = 6.0f;

return neptune;
}

#endif