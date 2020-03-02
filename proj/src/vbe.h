#ifndef __VBE_H
#define __VBE_H

/** @defgroup VBE VBE
 * @{
 * VESA BIOS Extensions Functions. Mainly done in Lab5
 */

#include <lcom/lcf.h>
#include <sprite.h>
#include <math.h>

int r;
struct minix_mem_range mr; // Physical memory range
unsigned int vram_base;    // VRAM's physical addresss
unsigned int vram_size;    // VRAM's size, but you can use the frame-buffer size, instead
uint8_t *video_mem;        // Frame-buffer VM address
uint16_t h_res;            // Horizontal resolution in pixels
uint16_t v_res;            // Vertical resolution in pixels
uint16_t bitsPerPixel;
uint16_t bytesPerPixel;
uint8_t red_s;
uint8_t red_p;
uint8_t green_s;
uint8_t green_p;
uint8_t blue_s;
uint8_t blue_p;
uint8_t memoryModel;
phys_bytes phys_addr;
uint8_t double_buffer[1024 * 768]; // Double Buffer for mode 0x105 indexed

/**
 * @brief Initialize Graphics Mode
 *
 * @param mode Graphics mode. This project only uses 0x105 mode
 * @return Video Memory
 */
void *(vg_init)(uint16_t mode);

/**
 * @brief Draws one pixel
 *
 * @param x Coordinatey x
 * @param y Coordinate y
 * @param color Color
 * @return 0 if sucess
 */
int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws vertical pixel line
 *
 * @param x Coordinatey x
 * @param y Coordinate y
 * @param len Lenght of line
 * @param color Color
 * @return 0 if sucess
 */
int(vg_draw_vline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws horizontal pixel line
 *
 * @param x Coordinatey x
 * @param y Coordinate y
 * @param len Lenght of line
 * @param color Color
 * @return 0 if sucess
 */
int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws pixel rectangle
 *
 * @param x Coordinatey x
 * @param y Coordinate y
 * @param width Width of rectangle
 * @param height Height of rectangle
 * @param color Color
 * @return 0 if sucess
 */
int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief Draws a rectangle black, erases a rectangle
 *
 * @return 0 if sucess
 */
int(vg_erase_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

/**
 * @brief Draws a pattern. Lab5 function not used in project
 *
 * @return 0 if sucess
 */
int(vg_draw_pattern)(uint8_t no_rectangles, uint32_t first, uint8_t step);

/**
 * @brief Draws a pixmap
 *
 * @return 0 if sucess
 */
int(vg_draw_pixmap)(xpm_map_t xpm, uint16_t x, uint16_t y);

/**
 * @brief Erases a pixmap
 *
 * @return 0 if sucess
 */
void(vg_erase_pixmap)(xpm_map_t xpm, uint16_t x, uint16_t y);

/**
 * @brief Creates a sprite
 *
 * @return Sprite if sucess
 */
uint8_t *(vg_create_sprite)(xpm_map_t xpm, xpm_image_t *img);

/**
 * @brief Draws a sprite
 *
 * @param sprite Sprite to draw
 * @param img Xpm Image to draw
 * @param x Coordinatey x
 * @param y Coordinate y
 * @return 0 if sucess
 */
int(vg_draw_sprite)(uint8_t *sprite, xpm_image_t img, uint16_t x, uint16_t y);

/**
 * @brief Erases a sprite
 *
 * @param sprite Sprite to draw
 * @param img Xpm Image to draw
 * @param x Coordinatey x
 * @param y Coordinate y
 * @return 0 if sucess
 */
int(vg_erase_sprite)(uint8_t *sprite, xpm_image_t img, uint16_t x, uint16_t y);

/**
 * @brief Draws an integer number
 *
 * @return Void
 */
void drawInt(int value, int x, int y);

/**
 * @brief Converts an integer number to an array
 *
 * @return Array if sucess
 */
char *toArray(int number);

#endif /* __VBE_H */
