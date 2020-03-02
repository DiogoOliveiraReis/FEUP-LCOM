#ifndef __GAME_H
#define __GAME_H

/** @defgroup Game Game
 * @{
 * Game logic information
 */

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include <stdbool.h>
#include <stdint.h>
#include <vbe.h>
#include <keyboard.h>
#include <lcom/timer.h>
#include <i8254.h>
#include <sprite.h>
#include <game.h>

/**
* Structure to represent player ship
*/
typedef struct
{
    int x;  /** The x coordinate */
    int y;  /**< The y coordinate */
    int hp; /**< The ship hit points */
} Ship;

/**
* Structure to represent lasers
*/
typedef struct
{
    int x;       /** The x coordinate */
    int y;       /**< The y coordinate */
    bool active; /**< If laser is active */
} Laser;

/**
* Structure to represent an enemy
*/
typedef struct
{
    int x;           /** The x coordinate */
    int y;           /**< The y coordinate */
    int score;       /**< Score it gives once defeated */
    int spriteIndex; /**< Enemy sprite */
    bool alive;      /**< If it's alive or not */
} Enemy;

/**
 * @brief Creates a ship
 *
 * @return Struct ship if sucess
 */
Ship createShip(int x, int y);

/**
 * @brief Creates a laser
 *
 * @return Struct laser if sucess
 */
Laser createLaser(int x);

/**
 * @brief Creates a enemy laser
 *
 * @return Struct enemy laser if sucess
 */
Enemy createEnemy(int x, int y, int spriteIndex);

/**
 * @brief Updates enemy position
 *
 * @return Struct Enemy if sucess
 */
Enemy updateEnemy(Enemy enemy, int deltaX, int deltaY);

/**
 * @brief Draws an enemy with sprite 1
 *
 * @return void
 */
void drawEnemy(Enemy enemy);

/**
 * @brief Erases an enemy with sprite 1
 *
 * @return void
 */
void eraseEnemy(Enemy enemy);

/**
 * @brief Draws an enemy with sprite 2
 *
 * @return void
 */
void drawEnemy2(Enemy enemy);

/**
 * @brief Erases an enemy with sprite 2
 *
 * @return void
 */
void eraseEnemy2(Enemy enemy);

/**
 * @brief Draws an enemy with sprite 3
 *
 * @return void
 */
void drawEnemy3(Enemy enemy);

/**
 * @brief Erases an enemy with sprite 3
 *
 * @return void
 */
void eraseEnemy3(Enemy enemy);

#endif /* __GAME_H */
