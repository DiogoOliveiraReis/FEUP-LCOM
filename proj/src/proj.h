#ifndef __PROJ_H
#define __PROJ_H

/** @defgroup Proj Proj
 * @{
 * Project main loop
 */

#include <game.h>
#include <i8254.h>
#include <keyboard.h>
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include <lcom/timer.h>
#include <screens.h>
#include <sprite.h>
#include <stdbool.h>
#include <stdint.h>
#include <vbe.h>
#include <mouse.h>
#include <stdio.h>
#include <string.h>
#include <db.h>

/**
 * @brief LCOM Framework
 *
 * @return 0 if sucess
 */
int main(int argc, char *argv[]);

/**
 * @brief Project main loop and main menu
 *
 * @return 0 if sucess
 */
int(proj_main_loop)(int argc, char *argv[]);

#endif /* __PROJ_H */
