```markdown
# MiniLibX Manual for cub3d (42 School)

## Table of Contents
1. [Introduction](#introduction)
2. [Compilation](#compilation)
3. [Function Index (Alphabetical)](#function-index-alphabetical)
4. [Core Functions](#core-functions)
5. [Window Functions](#window-functions)
6. [Image Functions](#image-functions)
7. [Event Handling](#event-handling)
8. [Text Functions](#text-functions)
9. [Mouse Functions](#mouse-functions)
10. [Utility Functions](#utility-functions)
11. [Pixel Manipulation](#pixel-manipulation)
12. [Common Patterns](#common-patterns)
13. [Key Codes](#key-codes)
14. [Complete Example](#complete-example)

---

## Introduction

MiniLibX is a simple X-Window (X11) programming API in C, designed for beginners. It provides basic tools to create windows, draw pixels, and handle events.

---

## Compilation

```bash
# Linux
cc -o cub3d $(OBJS) -L./minilibx-linux -lmlx -lXext -lX11 -lm

# MacOS
cc -o cub3d $(OBJS) -L./minilibx -lmlx -framework OpenGL -framework AppKit
```

Include in your code:
```c
#include "mlx.h"
```

---

## Function Index (Alphabetical)

### Core & Initialization
- [`mlx_init`](#mlx_init) - Initialize MLX connection
- [`mlx_loop`](#mlx_loop) - Start the event loop
- [`mlx_loop_hook`](#mlx_loop_hook) - Register function for each loop iteration

### Window Management
- [`mlx_clear_window`](#mlx_clear_window) - Clear window content
- [`mlx_destroy_window`](#mlx_destroy_window) - Destroy a window
- [`mlx_get_screen_size`](#mlx_get_screen_size) - Get screen dimensions
- [`mlx_new_window`](#mlx_new_window) - Create a new window
- [`mlx_pixel_put`](#mlx_pixel_put) - Draw a single pixel (slow)

### Image Functions
- [`mlx_destroy_image`](#mlx_destroy_image) - Free an image
- [`mlx_get_data_addr`](#mlx_get_data_addr) - Get image buffer address
- [`mlx_new_image`](#mlx_new_image) - Create a new image
- [`mlx_png_file_to_image`](#mlx_png_file_to_image) - Load PNG file (Linux only)
- [`mlx_put_image_to_window`](#mlx_put_image_to_window) - Display image on window
- [`mlx_xpm_file_to_image`](#mlx_xpm_file_to_image) - Load XPM file
- [`mlx_xpm_to_image`](#mlx_xpm_to_image) - Create image from XPM data

### Event Handling
- [`mlx_expose_hook`](#mlx_expose_hook) - Handle window redraw events
- [`mlx_hook`](#mlx_hook) - Register event handler
- [`mlx_key_hook`](#mlx_key_hook) - Simple key press handler
- [`mlx_mouse_hook`](#mlx_mouse_hook) - Simple mouse button handler

### Text Functions
- [`mlx_string_put`](#mlx_string_put) - Draw text on window
- [`mlx_set_font`](#mlx_set_font) - Change text font (limited)

### Mouse Functions
- [`mlx_mouse_get_pos`](#mlx_mouse_get_pos) - Get mouse position
- [`mlx_mouse_hide`](#mlx_mouse_hide) - Hide mouse cursor
- [`mlx_mouse_move`](#mlx_mouse_move) - Move mouse cursor
- [`mlx_mouse_show`](#mlx_mouse_show) - Show mouse cursor

### Utility Functions
- [`mlx_do_key_autorepeatoff`](#mlx_do_key_autorepeatoff) - Disable key repeat
- [`mlx_do_key_repeaton`](#mlx_do_key_repeaton) - Enable key repeat
- [`mlx_do_sync`](#mlx_do_sync) - Synchronize display

---

## Core Functions

### `mlx_init`
```c
void *mlx_init(void);
```
- **Description**: Initializes the connection to the graphical system
- **Returns**: Pointer to mlx instance (NULL on failure)
- **Example**:
```c
void *mlx_ptr = mlx_init();
if (!mlx_ptr)
    return (error("MLX initialization failed"));
```

### `mlx_loop`
```c
int mlx_loop(void *mlx_ptr);
```
- **Description**: Starts the event loop (infinite loop that waits for events)
- **Note**: This should be called at the end of your program
- **Example**:
```c
mlx_loop(mlx_ptr);
```

### `mlx_loop_hook`
```c
int mlx_loop_hook(void *mlx_ptr, int (*funct)(), void *param);
```
- **Description**: Registers a function to be called on each loop iteration
- **Example**:
```c
mlx_loop_hook(mlx_ptr, render_frame, &data);
```

---

## Window Functions

### `mlx_new_window`
```c
void *mlx_new_window(void *mlx_ptr, int width, int height, char *title);
```
- **Description**: Creates a new window
- **Parameters**:
  - `mlx_ptr`: MLX instance pointer
  - `width`: Window width in pixels
  - `height`: Window height in pixels
  - `title`: Window title string
- **Returns**: Window pointer (NULL on failure)
- **Example**:
```c
void *win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "cub3d");
```

### `mlx_clear_window`
```c
int mlx_clear_window(void *mlx_ptr, void *win_ptr);
```
- **Description**: Clears the window (fills with black)

### `mlx_destroy_window`
```c
int mlx_destroy_window(void *mlx_ptr, void *win_ptr);
```
- **Description**: Destroys a window

### `mlx_get_screen_size`
```c
int mlx_get_screen_size(void *mlx_ptr, int *width, int *height);
```
- **Description**: Gets the size of the screen/display
- **Parameters**:
  - `mlx_ptr`: MLX instance pointer
  - `width`: Pointer to store screen width
  - `height`: Pointer to store screen height
- **Returns**: 0 on success
- **Example**:
```c
int screen_w, screen_h;
mlx_get_screen_size(mlx_ptr, &screen_w, &screen_h);
printf("Screen: %dx%d\n", screen_w, screen_h);
```

### `mlx_pixel_put`
```c
int mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
```
- **Description**: Draws a pixel at position (x, y)
- **Note**: ⚠️ VERY SLOW - Don't use for cub3d! Use images instead
- **Color format**: `0xTTRRGGBB` (T=Transparency, R=Red, G=Green, B=Blue)

---

## Image Functions

### `mlx_new_image`
```c
void *mlx_new_image(void *mlx_ptr, int width, int height);
```
- **Description**: Creates a new image in memory
- **Returns**: Image pointer
- **Example**:
```c
void *img = mlx_new_image(mlx_ptr, 1920, 1080);
```

### `mlx_get_data_addr`
```c
char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, 
                        int *size_line, int *endian);
```
- **Description**: Gets the memory address of the image data
- **Parameters**:
  - `img_ptr`: Image pointer
  - `bits_per_pixel`: Returns bits per pixel (usually 32)
  - `size_line`: Returns number of bytes per line
  - `endian`: Returns endianness (0 = little endian)
- **Returns**: Pointer to the image buffer
- **Example**:
```c
typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_data;

t_data img;
img.img = mlx_new_image(mlx_ptr, 1920, 1080);
img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
                             &img.line_length, &img.endian);
```

### `mlx_put_image_to_window`
```c
int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, 
                            void *img_ptr, int x, int y);
```
- **Description**: Puts an image to the window at position (x, y)
- **Note**: This is what you use to display your rendered frame
- **Example**:
```c
mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
```

### `mlx_xpm_file_to_image`
```c
void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, 
                            int *width, int *height);
```
- **Description**: Loads an XPM file as an image
- **Note**: Only supports XPM format
- **Example**:
```c
int width, height;
void *img = mlx_xpm_file_to_image(mlx_ptr, "./textures/wall.xpm", 
                                   &width, &height);
```

### `mlx_xpm_to_image`
```c
void *mlx_xpm_to_image(void *mlx_ptr, char **xpm_data, 
                       int *width, int *height);
```
- **Description**: Creates an image from XPM data in memory (not a file)
- **Example**:
```c
char *xpm_data[] = {
    "2 2 2 1",
    "  c #FF0000",
    ". c #00FF00",
    " .",
    ". "
};
int w, h;
void *img = mlx_xpm_to_image(mlx_ptr, xpm_data, &w, &h);
```

### `mlx_png_file_to_image` (Linux only)
```c
void *mlx_png_file_to_image(void *mlx_ptr, char *filename, 
                            int *width, int *height);
```
- **Description**: Loads a PNG file as an image
- **Note**: Only available in some versions of MiniLibX (mainly Linux)
- **Example**:
```c
int width, height;
void *img = mlx_png_file_to_image(mlx_ptr, "./textures/wall.png", 
                                   &width, &height);
```

### `mlx_destroy_image`
```c
int mlx_destroy_image(void *mlx_ptr, void *img_ptr);
```
- **Description**: Frees an image from memory

---

## Event Handling

### `mlx_hook`
```c
int mlx_hook(void *win_ptr, int event, int mask, 
             int (*funct)(), void *param);
```
- **Description**: Registers a function to be called on specific events
- **Common Events**:
  - `2`: KeyPress
  - `3`: KeyRelease
  - `4`: ButtonPress (mouse)
  - `5`: ButtonRelease (mouse)
  - `6`: MotionNotify (mouse movement)
  - `12`: Expose (window needs redraw)
  - `17`: DestroyNotify (close window - red X button)
- **Event Masks**: Used for some events (can often be 0)
  - `1L<<0` or `1`: KeyPressMask
  - `1L<<1` or `2`: KeyReleaseMask
  - `1L<<2` or `4`: ButtonPressMask
  - `1L<<3` or `8`: ButtonReleaseMask
  - `1L<<6` or `64`: PointerMotionMask
- **Example**:
```c
mlx_hook(win_ptr, 2, 1L<<0, key_press, &data);
mlx_hook(win_ptr, 3, 1L<<1, key_release, &data);
mlx_hook(win_ptr, 6, 1L<<6, mouse_move, &data);
mlx_hook(win_ptr, 17, 0, close_window, &data);
```

### `mlx_key_hook`
```c
int mlx_key_hook(void *win_ptr, int (*funct)(), void *param);
```
- **Description**: Simplified key event handler
- **Note**: Only detects key press, not release. Use mlx_hook for better control
- **Function signature**: `int func(int keycode, void *param)`

### `mlx_mouse_hook`
```c
int mlx_mouse_hook(void *win_ptr, int (*funct)(), void *param);
```
- **Description**: Simplified mouse button event handler
- **Function signature**: `int func(int button, int x, int y, void *param)`
- **Button codes**: 1 = left, 2 = middle, 3 = right, 4 = scroll up, 5 = scroll down

### `mlx_expose_hook`
```c
int mlx_expose_hook(void *win_ptr, int (*funct)(), void *param);
```
- **Description**: Called when the window needs to be redrawn
- **Function signature**: `int func(void *param)`

---

## Text Functions

### `mlx_string_put`
```c
int mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, 
                   int color, char *string);
```
- **Description**: Draws a string to the window
- **Note**: Draws directly to window (not image buffer)
- **Example**:
```c
mlx_string_put(mlx_ptr, win_ptr, 10, 10, 0xFFFFFF, "Score: 100");
```

### `mlx_set_font` (rarely available/used)
```c
void mlx_set_font(void *mlx_ptr, void *win_ptr, char *name);
```
- **Description**: Changes the font for text rendering
- **Note**: Not available in all versions, limited support

---

## Mouse Functions

### `mlx_mouse_get_pos`
```c
int mlx_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y);
```
- **Description**: Gets the current mouse position relative to the window
- **Example**:
```c
int mouse_x, mouse_y;
mlx_mouse_get_pos(mlx_ptr, win_ptr, &mouse_x, &mouse_y);
printf("Mouse: %d, %d\n", mouse_x, mouse_y);
```

### `mlx_mouse_move`
```c
int mlx_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
```
- **Description**: Moves the mouse cursor to position (x, y) within the window
- **Example**:
```c
mlx_mouse_move(mlx_ptr, win_ptr, WIDTH / 2, HEIGHT / 2);
```

### `mlx_mouse_hide`
```c
int mlx_mouse_hide(void *mlx_ptr, void *win_ptr);
```
- **Description**: Hides the mouse cursor
- **Note**: Useful for first-person games

### `mlx_mouse_show`
```c
int mlx_mouse_show(void *mlx_ptr, void *win_ptr);
```
- **Description**: Shows the mouse cursor

---

## Utility Functions

### `mlx_do_sync`
```c
int mlx_do_sync(void *mlx_ptr);
```
- **Description**: Synchronizes the display (flushes the display buffer)
- **Note**: Usually not needed, but can help with visual glitches

### `mlx_do_key_autorepeatoff`
```c
int mlx_do_key_autorepeatoff(void *mlx_ptr);
```
- **Description**: Disables key auto-repeat
- **Note**: When you hold a key, it won't trigger multiple events

### `mlx_do_key_repeaton`
```c
int mlx_do_key_repeaton(void *mlx_ptr);
```
- **Description**: Enables key auto-repeat (default behavior)

---

## Pixel Manipulation

### Fast Pixel Drawing (Images)
```c
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
```

### Getting Pixel Color from Image
```c
int get_pixel_color(t_data *data, int x, int y)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    return (*(unsigned int*)dst);
}
```

### Color Creation
```c
int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

int get_t(int trgb)
{
    return ((trgb >> 24) & 0xFF);
}

int get_r(int trgb)
{
    return ((trgb >> 16) & 0xFF);
}

int get_g(int trgb)
{
    return ((trgb >> 8) & 0xFF);
}

int get_b(int trgb)
{
    return (trgb & 0xFF);
}
```

---

## Common Patterns

### Basic Setup Structure
```c
typedef struct s_game {
    void    *mlx;
    void    *win;
    t_data  img;
    int     win_width;
    int     win_height;
    // ... your game data
}   t_game;

int main(void)
{
    t_game game;
    int screen_w, screen_h;

    game.mlx = mlx_init();
    
    // Get screen size and create window accordingly
    mlx_get_screen_size(game.mlx, &screen_w, &screen_h);
    game.win_width = (screen_w > 1920) ? 1920 : screen_w;
    game.win_height = (screen_h > 1080) ? 1080 : screen_h;
    
    game.win = mlx_new_window(game.mlx, game.win_width, 
                              game.win_height, "cub3d");
    game.img.img = mlx_new_image(game.mlx, game.win_width, 
                                  game.win_height);
    game.img.addr = mlx_get_data_addr(game.img.img, 
                                      &game.img.bits_per_pixel,
                                      &game.img.line_length,
                                      &game.img.endian);
    
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    mlx_hook(game.win, 17, 0, close_game, &game);
    mlx_loop_hook(game.mlx, render, &game);
    mlx_loop(game.mlx);
}
```

### Rendering Loop
```c
int render(t_game *game)
{
    // 1. Clear/draw to image buffer
    draw_scene(game);
    
    // 2. Display the image
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    
    // 3. Optional: Draw UI text on top
    mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, "FPS: 60");
    
    return (0);
}
```

### Event Handlers
```c
int key_press(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC
        close_game(game);
    if (keycode == 119) // W
        move_forward(game);
    if (keycode == 115) // S
        move_backward(game);
    if (keycode == 97) // A
        move_left(game);
    if (keycode == 100) // D
        move_right(game);
    return (0);
}

int close_game(t_game *game)
{
    mlx_destroy_image(game->mlx, game->img.img);
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}

int mouse_move(int x, int y, t_game *game)
{
    // Handle mouse movement for camera rotation
    static int last_x = -1;
    
    if (last_x == -1)
        last_x = x;
    
    int delta = x - last_x;
    rotate_camera(game, delta * 0.002);
    last_x = x;
    
    return (0);
}
```

---

## Key Codes

### Linux Key Codes (X11)
```c
#define KEY_ESC     65307
#define KEY_W       119
#define KEY_A       97
#define KEY_S       115
#define KEY_D       100
#define KEY_LEFT    65361
#define KEY_RIGHT   65363
#define KEY_UP      65362
#define KEY_DOWN    65364
#define KEY_SPACE   32
#define KEY_SHIFT   65505
#define KEY_CTRL    65507
#define KEY_TAB     65289
#define KEY_ENTER   65293
```

### MacOS Key Codes
```c
#define KEY_ESC     53
#define KEY_W       13
#define KEY_A       0
#define KEY_S       1
#define KEY_D       2
#define KEY_LEFT    123
#define KEY_RIGHT   124
#define KEY_DOWN    125
#define KEY_SPACE   49
#define KEY_SHIFT   257
#define KEY_CTRL    256
#define KEY_TAB     48
#define KEY_ENTER   36
```

### Mouse Codes
```c
#define MOUSE_LEFT      1
#define MOUSE_MIDDLE    2
#define MOUSE_RIGHT     3
#define MOUSE_SCROLL_UP 4
#define MOUSE_SCROLL_DN 5
```

**Pro Tip**: Print the keycode in your handler to find out what key you pressed:
```c
int key_press(int keycode, t_game *game)
{
    printf("Key pressed: %d\n", keycode);
    return (0);
}
```

---

## Complete Example

```c
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_data;

typedef struct s_game {
    void    *mlx;
    void    *win;
    t_data  img;
    int     mouse_x;
    int     mouse_y;
    int     frame;
}   t_game;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

int create_color(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void draw_gradient(t_game *game)
{
    int x, y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            int r = (x * 255 / WIDTH);
            int g = (y * 255 / HEIGHT);
            int b = ((x + y + game->frame) % 255);
            my_mlx_pixel_put(&game->img, x, y, create_color(r, g, b));
            x++;
        }
        y++;
    }
}

void draw_circle(t_game *game, int cx, int cy, int radius, int color)
{
    int x, y;

    y = -radius;
    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            if (x * x + y * y <= radius * radius)
                my_mlx_pixel_put(&game->img, cx + x, cy + y, color);
            x++;
        }
        y++;
    }
}

int render(t_game *game)
{
    // Draw animated gradient
    draw_gradient(game);
    
    // Draw circle at mouse position
    draw_circle(game, game->mouse_x, game->mouse_y, 30, 0xFFFFFF);
    
    // Display the rendered frame
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    
    // Draw FPS counter
    char fps_text[50];
    sprintf(fps_text, "Frame: %d", game->frame);
    mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, fps_text);
    
    game->frame++;
    return (0);
}

int mouse_move(int x, int y, t_game *game)
{
    game->mouse_x = x;
    game->mouse_y = y;
    return (0);
}

int mouse_click(int button, int x, int y, t_game *game)
{
    printf("Mouse button %d clicked at (%d, %d)\n", button, x, y);
    if (button == 1) // Left click
        draw_circle(game, x, y, 50, 0xFF0000);
    return (0);
}

int key_press(int keycode, t_game *game)
{
    printf("Key pressed: %d\n", keycode);
    
    // ESC key (Linux: 65307, MacOS: 53)
    if (keycode == 65307 || keycode == 53)
    {
        mlx_destroy_image(game->mlx, game->img.img);
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    
    // Space bar
    if (keycode == 32 || keycode == 49)
        game->frame = 0; // Reset animation
    
    return (0);
}

int close_window(t_game *game)
{
    mlx_destroy_image(game->mlx, game->img.img);
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}

int main(void)
{
    t_game game;
    int screen_w, screen_h;

    // Initialize MLX
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        printf("Error: MLX initialization failed\n");
        return (1);
    }
    
    // Get screen size
    mlx_get_screen_size(game.mlx, &screen_w, &screen_h);
    printf("Screen size: %dx%d\n", screen_w, screen_h);
    
    // Create window
    game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "MiniLibX Complete Example");
    if (!game.win)
    {
        printf("Error: Window creation failed\n");
        return (1);
    }
    
    // Create image buffer
    game.img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    game.img.addr = mlx_get_data_addr(game.img.img, 
                                      &game.img.bits_per_pixel,
                                      &game.img.line_length,
                                      &game.img.endian);
    
    // Initialize game state
    game.mouse_x = WIDTH / 2;
    game.mouse_y = HEIGHT / 2;
    game.frame = 0;
    
    // Register event hooks
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);           // Key press
    mlx_hook(game.win, 6, 1L<<6, mouse_move, &game);          // Mouse move
    mlx_hook(game.win, 4, 1L<<2, mouse_click, &game);         // Mouse click
    mlx_hook(game.win, 17, 0, close_window, &game);           // Window close
    mlx_loop_hook(game.mlx, render, &game);                   // Render loop
    
    // Start event loop
    mlx_loop(game.mlx);
    
    return (0);
}
```

### Compiling the Example

```bash
# Linux
cc -o example example.c -L./minilibx-linux -lmlx -lXext -lX11 -lm

# MacOS
cc -o example example.c -L./minilibx -lmlx -framework OpenGL -framework AppKit
```

---

## Tips for cub3d

### Performance
1. **Always use images, never mlx_pixel_put** - It's too slow for raycasting
2. **Double buffering** - Draw to an image buffer, then display it with `mlx_put_image_to_window`
3. **Pre-calculate constants** - Don't recalculate the same values every frame
4. **Optimize loops** - The raycasting loop is your bottleneck

### Memory Management
5. **Load textures at init** - Don't reload textures every frame
6. **Free resources** - Destroy images and windows before exiting
7. **Check for leaks** - Use `valgrind` to find memory leaks

### Event Handling
8. **Handle ESC and window close (X)** - Use mlx_hook with events 2 and 17
9. **Use mlx_loop_hook for continuous rendering** - Not mlx_key_hook
10. **Consider key release events** - For smooth movement, track key states

### Drawing
11. **Check bounds** - Always validate x/y coordinates before drawing
12. **Use integer arithmetic** - Faster than floating point when possible
13. **Draw vertical lines** - For wall slices in raycasting

### Textures
14. **XPM format** - Easiest to work with in cub3d
15. **Power-of-2 dimensions** - 64x64, 128x128 for easy calculations
16. **Extract texture pixels** - Use `mlx_get_data_addr` on loaded textures

---

## Common Errors & Solutions

### Segmentation Fault
- **Cause**: Drawing outside image bounds
- **Solution**: Always check `if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)`

### Black Screen
- **Cause**: Forgot to call `mlx_put_image_to_window`
- **Solution**: Call it after drawing to your image buffer

### Window Won't Close
- **Cause**: No handler for close button
- **Solution**: Add `mlx_hook(win, 17, 0, close_window, &data);`

### Slow Performance
- **Cause**: Using `mlx_pixel_put` instead of images
- **Solution**: Use image buffer with `my_mlx_pixel_put`

### Memory Leaks
- **Cause**: Not freeing images/windows
- **Solution**: Call `mlx_destroy_image` and `mlx_destroy_window`

### Can't Load Textures
- **Cause**: Wrong file path or format
- **Solution**: Use XPM format, check relative paths

### Colors Look Wrong
- **Cause**: Wrong color format or endianness
- **Solution**: Use `0xRRGGBB` format (no transparency in most cases)

### Keys Don't Work
- **Cause**: Wrong keycodes for your OS
- **Solution**: Print keycodes to find correct values for your system

---

## Quick Reference Card

### Must-Have Setup
```c
mlx = mlx_init();
win = mlx_new_window(mlx, w, h, "title");
img = mlx_new_image(mlx, w, h);
addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
mlx_hook(win, 2, 1L<<0, key_press, &data);
mlx_hook(win, 17, 0, close_win, &data);
mlx_loop_hook(mlx, render, &data);
mlx_loop(mlx);
```

### Fast Pixel Drawing
```c
dst = addr + (y * line_len + x * (bpp / 8));
*(unsigned int*)dst = color;
```

### Display Frame
```c
mlx_put_image_to_window(mlx, win, img, 0, 0);
```

### Load Texture
```c
tex = mlx_xpm_file_to_image(mlx, "file.xpm", &w, &h);
tex_addr = mlx_get_data_addr(tex, &bpp, &line, &end);
```

---

## Additional Resources

- **42 Docs**: Check your school's intranet for project-specific guidelines
- **Man Pages**: `man mlx` (if available on your system)
- **Test Simple Programs**: Start small before tackling raycasting
- **Debug with Prints**: Print keycodes, coordinates, and colors

---

## Conclusion

MiniLibX is a minimal but powerful library for cub3d. The key to success is:

1. ✅ Use image buffers (not `mlx_pixel_put`)
2. ✅ Handle events properly (especially window close)
3. ✅ Free all resources before exiting
4. ✅ Test frequently with small examples
5. ✅ Keep your code organized and modular

**Good luck with cub3d!** 🎮🚀

---

**Document Version**: 1.0  
**Last Updated**: 2024  
**Compatible with**: MiniLibX (Linux & MacOS versions)  
**For**: 42 School cub3d project

---
```

