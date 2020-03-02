#ifndef __SCREENS_H
#define __SCREENS_H

/** @defgroup Screens Screens
 * @{
 * Main Menu, Game and GameOver screen information
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
#include <db.h>

/**
* Enumerate to the various screen types
*/
typedef enum
{
	Main_Menu, /**< Main Menu Screen */
	Game,	  /**< Game Screen */
	GameOver   /**< GameOver Screen */
} Screen;

/**
 * @brief Clears the screen. Prints the whole screen black
 *
 * @return 0 if sucess
 */
int clearScreen();

/**
 * @brief Displays the gameover screen
 *
 * @return 0 if sucess
 */
int gameOverScreen();

/**
 * @brief Displays the game screen
 *
 * @return true if the game is over
 */
bool gameScreen(int level, int lives);

#endif /* __SCREENS_H */
