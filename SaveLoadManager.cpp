#include "SaveLoadManager.h"
#include "NormalBrick.h"
#include "HardBrick.h"
#include "UnbreakableBrick.h"
#include "PowerBrick.h"
#include "PowerUp.h"
#include "MyStr.h"
#include <fstream>

void SaveLoadManager::saveLevel(const Level& level, const char* filename) {
    std::ofstream out(filename, std::ios::binary);
    Rectangle rect = level.getPaddle()->getRect();
    out.write((char*)&rect.x, sizeof(float));
    out.write((char*)&rect.width, sizeof(float));

    int ballCount = level.getBalls().size();
    out.write((char*)&ballCount, sizeof(int));
    for (int i = 0; i < ballCount; i++) {
        Ball b = level.getBalls().at(i);
        float x = b.getX(), y = b.getY(), vx = b.getVelocityX(), vy = b.getVelocityY();
        out.write((char*)&x, sizeof(float));
        out.write((char*)&y, sizeof(float));
        out.write((char*)&vx, sizeof(float));
        out.write((char*)&vy, sizeof(float));
    }

    int brickCount = level.getBricks().size();
    out.write((char*)&brickCount, sizeof(int));
    for (int i = 0; i < brickCount; i++) {
        Brick* br = level.getBricks().at(i);
        Rectangle r = br->getRect();
        MyStr type = MyStr("Normal");
        if (dynamic_cast<HardBrick*>(br)) type = MyStr("Hard");
        else if (dynamic_cast<UnbreakableBrick*>(br)) type = MyStr("Unbreakable");
        else if (dynamic_cast<PowerBrick*>(br)) {
            PowerBrick* pb = static_cast<PowerBrick*>(br);
            PowerUp* p = pb->releasePowerUp();
            if (dynamic_cast<ExpandPaddlePowerUp*>(p)) type = MyStr("PowerExpand");
            else type = MyStr("PowerMulti");
        }
        int len = type.Length();
        out.write((char*)&len, sizeof(int));
        out.write(type.ToCharArray(), len);
        out.write((char*)&r.x, sizeof(float));
        out.write((char*)&r.y, sizeof(float));
        out.write((char*)&r.width, sizeof(float));
        out.write((char*)&r.height, sizeof(float));
    }

    out.close();
}

void SaveLoadManager::loadLevel(Level& level, const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) return;

    float px, pw;
    in.read((char*)&px, sizeof(float));
    in.read((char*)&pw, sizeof(float));
    level.getPaddle()->updatePosition(px, pw);


    int ballCount;
    in.read((char*)&ballCount, sizeof(int));
    level.getBalls().clear();
    for (int i = 0; i < ballCount; i++) {
        float x, y, vx, vy;
        in.read((char*)&x, sizeof(float));
        in.read((char*)&y, sizeof(float));
        in.read((char*)&vx, sizeof(float));
        in.read((char*)&vy, sizeof(float));
        level.getBalls().push(Ball(x, y, vx, vy, 8));
    }

    int brickCount;
    in.read((char*)&brickCount, sizeof(int));
    level.getBricks().clear();
    for (int i = 0; i < brickCount; i++) {
        int len;
        in.read((char*)&len, sizeof(int));
        char* buffer = new char[len + 1];
        in.read(buffer, len);
        buffer[len] = '\0';
        MyStr type = MyStr(buffer);
        delete[] buffer;

        float x, y, w, h;
        in.read((char*)&x, sizeof(float));
        in.read((char*)&y, sizeof(float));
        in.read((char*)&w, sizeof(float));
        in.read((char*)&h, sizeof(float));

        if (type == MyStr("Normal"))
            level.getBricks().push(new NormalBrick(x, y, w, h));
        else if (type == MyStr("Hard"))
            level.getBricks().push(new HardBrick(x, y, w, h));
        else if (type == MyStr("Unbreakable"))
            level.getBricks().push(new UnbreakableBrick(x, y, w, h));
        else if (type == MyStr("PowerExpand"))
            level.getBricks().push(new PowerBrick(x, y, w, h, new ExpandPaddlePowerUp()));
        else if (type == MyStr("PowerMulti"))
            level.getBricks().push(new PowerBrick(x, y, w, h, new MultiBallPowerUp()));
    }

    in.close();
}