#include <game.h>

Ship createShip(int x, int y)
{
    Ship ship;
    ship.x = x;
    ship.y = y;
    ship.hp = 3;
    return ship;
}

Laser createLaser(int x)
{
    Laser laser;
    laser.x = x;
    laser.y = 650;
    laser.active = false;
    return laser;
}

Enemy createEnemy(int x, int y, int spriteIndex)
{
    Enemy enemy;
    enemy.x = x;
    enemy.y = y;
    enemy.score = 10 * (1 + spriteIndex);
    enemy.spriteIndex = spriteIndex;
    enemy.alive = true;
    return enemy;
}

Enemy updateEnemy(Enemy enemy, int deltaX, int deltaY)
{
    eraseEnemy(enemy);
    enemy.x += deltaX;
    enemy.y += deltaY;
    drawEnemy(enemy);
    return enemy;
}

void drawEnemy(Enemy enemy)
{
    xpm_map_t xpm_enemy1 = sprite1;
    xpm_map_t xpm_enemy2 = sprite2;
    xpm_map_t xpm_enemy3 = sprite3;

    xpm_image_t img_enemy;

    uint8_t *sprite_enemy;

    //should be a better way to do this
    switch (enemy.spriteIndex)
    {
    case 0:
        sprite_enemy = vg_create_sprite(xpm_enemy1, &img_enemy);
        break;
    case 1:
        sprite_enemy = vg_create_sprite(xpm_enemy2, &img_enemy);
        break;
    case 2:
        sprite_enemy = vg_create_sprite(xpm_enemy3, &img_enemy);
        break;
    default:
        sprite_enemy = vg_create_sprite(xpm_enemy1, &img_enemy);
    }
    vg_draw_sprite(sprite_enemy, img_enemy, enemy.x, enemy.y);
}

void eraseEnemy(Enemy enemy)
{
    xpm_map_t xpm_enemy1 = sprite1;
    xpm_map_t xpm_enemy2 = sprite2;
    xpm_map_t xpm_enemy3 = sprite3;

    xpm_image_t img_enemy;

    uint8_t *sprite_enemy;

    //should be a better way to do this
    switch (enemy.spriteIndex)
    {
    case 0:
        sprite_enemy = vg_create_sprite(xpm_enemy1, &img_enemy);
        break;
    case 1:
        sprite_enemy = vg_create_sprite(xpm_enemy2, &img_enemy);
        break;
    case 2:
        sprite_enemy = vg_create_sprite(xpm_enemy3, &img_enemy);
        break;
    default:
        sprite_enemy = vg_create_sprite(xpm_enemy1, &img_enemy);
    }

    vg_erase_sprite(sprite_enemy, img_enemy, enemy.x, enemy.y);
}
