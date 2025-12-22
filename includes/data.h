#pragma once
#include <glm/glm.hpp>

struct Player 
{
    glm::vec3 pos;      // position in world
    float angle;        // facing direction in radians
    float moveSpeed;    // movement speed
    float turnSpeed;    // turning speed
};

struct Robot {
    float x, y, z;
    float dir;
    bool alive = true;
};

struct Bullet
{
    glm::vec3 pos;   // current position
    glm::vec3 dir;   // normalized direction
    float speed;
    bool alive;
};

struct Vertex {
    float x, y, z;
    float nx, ny, nz;
    float u, v;
};
