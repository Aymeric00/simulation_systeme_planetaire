#ifndef _GFX_H_
#define _GFX_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#define MAKE_COLOR(r, g, b) \
    ((uint32_t)b | ((uint32_t)g << 8) | ((uint32_t)r << 16))

#define COLOR_GET_B(color) (color & 0xff)
#define COLOR_GET_G(color) ((color >> 8) & 0xff)
#define COLOR_GET_R(color) ((color >> 16) & 0xff)

#define COLOR_BLACK 0x00000000
#define COLOR_RED 0x00FF0000
#define COLOR_GREEN 0x0000FF00
#define COLOR_BLUE 0x000000FF
#define COLOR_WHITE 0x00FFFFFF
#define COLOR_YELLOW 0x00FFFF00
#define COLOR_DARK_CYAN 0xFF008B8B
#define COLOR_GOLDEN_ROD 0xFFDAA520
#define COLOR_LINEN 0xFFAF0E6
#define COLOR_LIGHT_SALMON 0xFFFFA07A
#define COLOR_ORANGE_RED 0xFFFF4500
#define COLOR_BROWN 0x5d4c3e

struct gfx_context_t
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    uint32_t *pixels;
    uint32_t width;
    uint32_t height;
};

extern void gfx_putpixel(
    struct gfx_context_t *ctxt, uint32_t column, uint32_t row, uint32_t color);
extern void gfx_clear(struct gfx_context_t *ctxt, uint32_t color);
extern struct gfx_context_t *gfx_create(char *text, uint32_t width, uint32_t height);
extern void gfx_destroy(struct gfx_context_t *ctxt);
extern void gfx_present(struct gfx_context_t *ctxt);
extern SDL_Keycode gfx_keypressed();
extern void draw_full_circle(struct gfx_context_t *ctxt, uint32_t c_column, uint32_t c_row, uint32_t r, uint32_t color);
extern void draw_full_line(struct gfx_context_t *ctxt, uint32_t c_column, uint32_t c_row, uint32_t r_m, uint32_t r_p, uint32_t color);
#endif
