#pragma once
#include <vector>
#include <cmath>
#include <glm/glm.hpp>
#include <GL/freeglut.h>

#include "data.h"
#include "Maze.h"
#include "player.h"
inline void robotShoot(std::vector<Bullet>& bullets,
                       const Robot& r,
                       const Player& player)
{
    Bullet b;

    glm::vec3 toPlayer = player.pos - glm::vec3(r.x, 0.0f, r.z);
    if (glm::length(toPlayer) < 0.6f) return;

    b.dir = glm::normalize(toPlayer);

    b.pos = glm::vec3(
        r.x + b.dir.x * 0.4f,
        0.6f,
        r.z + b.dir.z * 0.4f
        );

    b.speed = 0.05f;
    b.alive = true;
    bullets.push_back(b);
}

inline void updateRobots(std::vector<Robot>& robots, const Player& player, const Maze& maze)
{
    const float SPEED = 0.03f;

    for (auto& r : robots)
    {
        if (!r.alive) continue;

        // stop near player so they don’t overlap
        glm::vec3 toPlayer = player.pos - glm::vec3(r.x, 0.0f, r.z);
        float dist = glm::length(toPlayer);
        if (dist < 0.6f) continue;

        int pr = int(player.pos.z);
        int pc = int(player.pos.x);
        int rr = int(r.z);
        int rc = int(r.x);

        int dr = 0, dc = 0;
        if (pr < rr) dr = -1;
        else if (pr > rr) dr = 1;

        if (pc < rc) dc = -1;
        else if (pc > rc) dc = 1;

        auto tryMove = [&](float nx, float nz) {
            if (canMove(nx, nz, maze)) { r.x = nx; r.z = nz; return true; }
            return false;
        };

        bool moved = false;

        // try vertical first
        if (dr != 0)
            moved = tryMove(r.x, r.z + dr * SPEED);

        // then horizontal
        if (!moved && dc != 0)
            moved = tryMove(r.x + dc * SPEED, r.z);
    }
}

inline void drawRobotSphere(const Robot& r)
{
    if (!r.alive) return;

    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(r.x, r.y + 0.3f, r.z);
    glutSolidSphere(0.25, 16, 16);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
}

inline void drawTexturedSphere(float radius, int rings, int segments, GLuint texID)
{
    glBindTexture(GL_TEXTURE_2D, texID);
    glEnable(GL_TEXTURE_2D);

    float dt = float(M_PI) / rings;
    float du = 2.0f * float(M_PI) / segments;

    for (int i = 0; i < rings; i++)
    {
        float t1 = i * dt;
        float t2 = (i + 1) * dt;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= segments; j++)
        {
            float u = j * du;

            float x1 = radius * std::sin(t1) * std::sin(u);
            float y1 = radius * std::cos(t1);
            float z1 = radius * std::sin(t1) * std::cos(u);

            float u_tex  = u / (2.0f * float(M_PI));
            float v1_tex = 1.0f - t1 / float(M_PI);

            glNormal3f(x1 / radius, y1 / radius, z1 / radius);
            glTexCoord2f(u_tex, v1_tex);
            glVertex3f(x1, y1, z1);

            float x2 = radius * std::sin(t2) * std::sin(u);
            float y2 = radius * std::cos(t2);
            float z2 = radius * std::sin(t2) * std::cos(u);

            float v2_tex = 1.0f - t2 / float(M_PI);

            glNormal3f(x2 / radius, y2 / radius, z2 / radius);
            glTexCoord2f(u_tex, v2_tex);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}

inline void drawRobotTexturedSphere(const Robot& r, float radius, GLuint texID)
{
    if (!r.alive) return;
    glPushMatrix();
    glTranslatef(r.x, r.y + radius, r.z);
    drawTexturedSphere(radius, 20, 30, texID);
    glPopMatrix();
}
