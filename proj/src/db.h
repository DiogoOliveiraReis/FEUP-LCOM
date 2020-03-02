#ifndef __DB_H
#define __DB_H

/** @defgroup Db Db
 * @{
 * Database information, mainly scores
 */

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include <stdbool.h>
#include <stdint.h>
#include <game.h>
#include <i8254.h>
#include <keyboard.h>
#include <screens.h>
#include <sprite.h>
#include <stdbool.h>
#include <stdint.h>
#include <vbe.h>
#include <mouse.h>
#include <rtc.h>

extern int score;

typedef struct
{
    unsigned int day;  /** Info of the day */
    unsigned int month;  /** Info of the month */
    unsigned int year;  /** Info of the year */
} Date;

/**
 * @brief Writes game score to scores.txt
 *
 * @return 0 if sucess
 */
int writeScore();

/**
 * @brief Writes highscores to highscores.txt
 *
 * @return 0 if sucess
 */
int writeHighscore();

/**
 * @brief Gets scores.txt information
 *
 * @return 0 if sucess
 */
char getScores();

/**
 * @brief Displays information of scores.txt
 *
 * @return 0 if sucess
 */
int displayScores();

/**
 * @brief Deletes scores.txt
 *
 * @return 0 if sucess
 */
int clearScores();

/**
 * @brief Draws date @ x, y position
 *
 * @return 0 if sucess
 */
int drawDate(unsigned day, unsigned month, unsigned year, unsigned hours, unsigned minutes, unsigned seconds, int x, int y);

/**
 * @brief Draws top 10 scores
 *
 * @return 0 if sucess
 */
int drawTopScores();

#endif /* __DB_H */
