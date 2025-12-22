#pragma once
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include "data.h"
#include "Maze.h"
#include "player.h"
#include "robot.h"

inline void spawnPlayerBullet(std::vector<Bullet>& bullets, const Player& player)
{
    Bullet b;
    b.pos = player.pos + glm::vec3(sin(player.angle), 0.1f, cos(player.angle));
    b.dir = glm::normalize(glm::vec3(sin(player.angle), 0.0f, cos(player.angle)));
    b.speed = 0.11f;
    b.alive = true;
    bullets.push_back(b);
}


inline void drawBullets(const std::vector<Bullet>& bullets)
{
    glColor3f(1.0f, 1.0f, 0.0f);

    for (const auto& b : bullets)
    {
        if (!b.alive) continue;

        glPushMatrix();
        glTranslatef(b.pos.x, b.pos.y, b.pos.z);
        glutSolidSphere(0.07, 10, 10);
        glPopMatrix();
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    
    glEnable(GL_TEXTURE_2D);
}
inline void updateBullets(std::vector<Bullet>& bullets,
                          std::vector<Robot>& robots,
                          const Maze& maze,
                          const Player&)
{
        const float HIT_RADIUS  = 0.30f;
    const float HIT_RADIUS2 = HIT_RADIUS * HIT_RADIUS;

    for (auto& b : bullets)
    {
        if (!b.alive) continue;

        b.pos += b.dir * b.speed;

        if (!canMove(b.pos.x, b.pos.z, maze))
        {
            b.alive = false;
            continue;
        }

        for (auto& r : robots)
        {
            if (!r.alive) continue;

            float dx = b.pos.x - r.x;
            float dz = b.pos.z - r.z;

            if (dx*dx + dz*dz < HIT_RADIUS2)
            {
                r.alive = false;
                b.alive = false;
                break;
            }
        }
    }

    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
                       [](const Bullet& b){ return !b.alive; }),
        bullets.end()
    );
}

