#pragma once

/* Copyright 2021 George Lamb
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/* Before use, you must #define
 * 	QUO_IMPL
 * in *one* c/cpp file, to provide an implementation.*/

/* CONFIGURATION OPTIONS
 * 	QUO_USE_STB_IMAGE - Allows loading of any image, not just
 * 	bmp files. Make sure `stb_image.h' (from https://github.com/nothings/stb)
 * 	is in the same directory as this file. */

/* COMPLETE EXAMPLE to render a red rectangle on the screen, seen in the
 * below preprocessor #if */
#if 0
#define QUO_IMPL
#include <quo.h>

int main() {
	/* Create window */
	quo_Window window;
	quo_init_window(&window, 640, 480, false);
	quo_set_window_title(&window, "quo example program");

	/* Create renderer */
	quo_Renderer renderer;
	quo_init_renderer(&renderer, &window);

	/* Game loop */
	while (window.is_open) {
		/* Update window event */
		quo_update_window_events(&window);

		/* Clear to a solid black colour */
		quo_clear_renderer(0x000000);

		/* Draw a red rectangle */
		quo_draw_rect(&renderer, (quo_Rect){100, 100, 50, 50}, 0xff1100);

		/* Print the FPS when the space key is pressed */
		if (quo_key_pressed(QUO_KEY_SPACE)) {
			printf("FPS: %g\n", window.fps);
		}

		/* Update window and renderer */
		quo_update_renderer(&renderer);
		quo_update_window(&window);
	}

	/* Clean up */
	quo_free_renderer(&renderer);
	quo_free_window(&window);
}
#endif

#define QUO_VERSION "2.0.0"

/**
 * @file quo.h
 * @brief Quo is a single-header game library written in C.
 *
 * This library is standalone, meaning it doesn't depend on anything that doesn't come with the operating system.
 */


/* Make sure it works with C++, too */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

/* Boolean type */
typedef char quo_bool;
#define true 1
#define false 0

/* Keys */
#define QUO_KEY_UNKNOWN            -1
#define QUO_KEY_SPACE              32
#define QUO_KEY_APOSTROPHE         39  /* ' */
#define QUO_KEY_COMMA              44  /* , */
#define QUO_KEY_MINUS              45  /* - */
#define QUO_KEY_PERIOD             46  /* . */
#define QUO_KEY_SLASH              47  /* / */
#define QUO_KEY_0                  48
#define QUO_KEY_1                  49
#define QUO_KEY_2                  50
#define QUO_KEY_3                  51
#define QUO_KEY_4                  52
#define QUO_KEY_5                  53
#define QUO_KEY_6                  54
#define QUO_KEY_7                  55
#define QUO_KEY_8                  56
#define QUO_KEY_9                  57
#define QUO_KEY_SEMICOLON          59  /* ; */
#define QUO_KEY_EQUAL              61  /* = */
#define QUO_KEY_A                  65
#define QUO_KEY_B                  66
#define QUO_KEY_C                  67
#define QUO_KEY_D                  68
#define QUO_KEY_E                  69
#define QUO_KEY_F                  70
#define QUO_KEY_G                  71
#define QUO_KEY_H                  72
#define QUO_KEY_I                  73
#define QUO_KEY_J                  74
#define QUO_KEY_K                  75
#define QUO_KEY_L                  76
#define QUO_KEY_M                  77
#define QUO_KEY_N                  78
#define QUO_KEY_O                  79
#define QUO_KEY_P                  80
#define QUO_KEY_Q                  81
#define QUO_KEY_R                  82
#define QUO_KEY_S                  83
#define QUO_KEY_T                  84
#define QUO_KEY_U                  85
#define QUO_KEY_V                  86
#define QUO_KEY_W                  87
#define QUO_KEY_X                  88
#define QUO_KEY_Y                  89
#define QUO_KEY_Z                  90
#define QUO_KEY_LEFT_BRACKET       91  /* [ */
#define QUO_KEY_BACKSLASH          92  /* \ */
#define QUO_KEY_RIGHT_BRACKET      93  /* ] */
#define QUO_KEY_GRAVE_ACCENT       96  /* ` */
#define QUO_KEY_WORLD_1            161 /* non-US #1 */
#define QUO_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define QUO_KEY_ESCAPE             256
#define QUO_KEY_ENTER              257
#define QUO_KEY_TAB                258
#define QUO_KEY_BACKSPACE          259
#define QUO_KEY_INSERT             260
#define QUO_KEY_DELETE             261
#define QUO_KEY_RIGHT              262
#define QUO_KEY_LEFT               263
#define QUO_KEY_DOWN               264
#define QUO_KEY_UP                 265
#define QUO_KEY_PAGE_UP            266
#define QUO_KEY_PAGE_DOWN          267
#define QUO_KEY_HOME               268
#define QUO_KEY_END                269
#define QUO_KEY_CAPS_LOCK          280
#define QUO_KEY_SCROLL_LOCK        281
#define QUO_KEY_NUM_LOCK           282
#define QUO_KEY_PRINT_SCREEN       283
#define QUO_KEY_PAUSE              284
#define QUO_KEY_F1                 290
#define QUO_KEY_F2                 291
#define QUO_KEY_F3                 292
#define QUO_KEY_F4                 293
#define QUO_KEY_F5                 294
#define QUO_KEY_F6                 295
#define QUO_KEY_F7                 296
#define QUO_KEY_F8                 297
#define QUO_KEY_F9                 298
#define QUO_KEY_F10                299
#define QUO_KEY_F11                300
#define QUO_KEY_F12                301
#define QUO_KEY_F13                302
#define QUO_KEY_F14                303
#define QUO_KEY_F15                304
#define QUO_KEY_F16                305
#define QUO_KEY_F17                306
#define QUO_KEY_F18                307
#define QUO_KEY_F19                308
#define QUO_KEY_F20                309
#define QUO_KEY_F21                310
#define QUO_KEY_F22                311
#define QUO_KEY_F23                312
#define QUO_KEY_F24                313
#define QUO_KEY_F25                314
#define QUO_KEY_NP_0               320
#define QUO_KEY_NP_1               321
#define QUO_KEY_NP_2               322
#define QUO_KEY_NP_3               323
#define QUO_KEY_NP_4               324
#define QUO_KEY_NP_5               325
#define QUO_KEY_NP_6               326
#define QUO_KEY_NP_7               327
#define QUO_KEY_NP_8               328
#define QUO_KEY_NP_9               329
#define QUO_KEY_NP_DECIMAL         330
#define QUO_KEY_NP_DIVIDE          331
#define QUO_KEY_NP_MULTIPLY        332
#define QUO_KEY_NP_SUBTRACT        333
#define QUO_KEY_NP_ADD             334
#define QUO_KEY_NP_ENTER           335
#define QUO_KEY_NP_EQUAL           336
#define QUO_KEY_LEFT_SHIFT         340
#define QUO_KEY_LEFT_CONTROL       341
#define QUO_KEY_LEFT_ALT           342
#define QUO_KEY_LEFT_SUPER         343
#define QUO_KEY_RIGHT_SHIFT        344
#define QUO_KEY_RIGHT_CONTROL      345
#define QUO_KEY_RIGHT_ALT          346
#define QUO_KEY_RIGHT_SUPER        347
#define QUO_KEY_MENU               348
#define QUO_KEY_COUNT              QUO_KEY_MENU + 1

#define QUO_MOUSE_BUTTON_1          0
#define QUO_MOUSE_BUTTON_3          2
#define QUO_MOUSE_BUTTON_2          1
#define QUO_MOUSE_BUTTON_4          3
#define QUO_MOUSE_BUTTON_5          4
#define QUO_MOUSE_BUTTON_6          5
#define QUO_MOUSE_BUTTON_7          6
#define QUO_MOUSE_BUTTON_8          7
#define QUO_MOUSE_BUTTON_COUNT      QUO_MOUSE_BUTTON_8 + 1
#define QUO_MOUSE_BUTTON_LEFT       QUO_MOUSE_BUTTON_1
#define QUO_MOUSE_BUTTON_RIGHT      QUO_MOUSE_BUTTON_2
#define QUO_MOUSE_BUTTON_MIDDLE     QUO_MOUSE_BUTTON_3

/* Windows */
#if defined(_WIN32)
#define QUO_PLATFORM_WINDOWS
#endif

/* X11 */
#if defined(__linux__) || defined(__FreeBSD__)
#define QUO_PLATFORM_X11
#endif

/* Platform-specific includes */
#if defined(QUO_PLATFORM_X11)
/* Graphics */
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#endif

#if defined(QUO_PLATFORM_WINDOWS)
#include <windows.h>
#include <GL/gl.h>

#if _MSC_VER >= 1500
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#endif
#endif

/* Platform-specific aliases & macros */
#if defined(QUO_PLATFORM_X11)
typedef GLXContext quo_GLDeviceContext;
typedef GLXContext quo_GLRenderContext;
typedef GLXContext (*glXCreateContextAttribsARBProc)
    (Display*, GLXFBConfig, GLXContext, Bool, const int*);


#define CALLSTYLE
#define QUO_LOAD_GL_FUNC(t, n) (t*)glXGetProcAddress((unsigned char*)n)
#endif

#if defined (QUO_PLATFORM_WINDOWS)
typedef HDC quo_GLDeviceContext;
typedef HGLRC quo_GLRenderContext;

#define CALLSTYLE __stdcall
#define QUO_LOAD_GL_FUNC(t, n) (t*)wglGetProcAddress(n)
#endif

#ifndef DOXYGEN_IGNORE
/* OpenGL defines */
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF
#ifndef GL_FRAMEBUFFER
	#define GL_FRAMEBUFFER 0x8D40
#endif
#ifndef GL_COLOR_ATTACHMENT0
	#define GL_COLOR_ATTACHMENT0 0x8CE0
#endif
#ifndef GL_RENDERBUFFER
	#define GL_RENDERBUFFER 0x8D41
#endif
#ifndef GL_DEPTH24_STENCIL8
	#define GL_DEPTH24_STENCIL8 0x88F0
#endif
#ifndef GL_DEPTH_STENCIL_ATTACHMENT
	#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#endif
#endif

#ifndef DOXYGEN_IGNORE
/* GL load types */
typedef int CALLSTYLE quo_gl_get_uniform_location(unsigned int, const char*);
typedef unsigned int CALLSTYLE quo_gl_create_program();
typedef unsigned int CALLSTYLE quo_gl_create_shader(unsigned int);
typedef void CALLSTYLE quo_gl_active_texture(unsigned int);
typedef void CALLSTYLE quo_gl_attach_shader(unsigned int, unsigned int);
typedef void CALLSTYLE quo_gl_bind_buffer(unsigned int, int);
typedef void CALLSTYLE quo_gl_bind_frame_buffer(unsigned int, unsigned int);
typedef void CALLSTYLE quo_gl_bind_render_buffer(unsigned int, unsigned int);
typedef void CALLSTYLE quo_gl_bind_vertex_array(unsigned int);
typedef void CALLSTYLE quo_gl_buffer_data(unsigned int, int, const void*, unsigned int);
typedef void CALLSTYLE quo_gl_buffer_sub_data(unsigned int, int offset, unsigned int size, void* data);
typedef void CALLSTYLE quo_gl_compile_shader(unsigned int);
typedef void CALLSTYLE quo_gl_delete_buffers(unsigned int, unsigned int*);
typedef void CALLSTYLE quo_gl_delete_frame_buffers(unsigned int, unsigned int*);
typedef void CALLSTYLE quo_gl_delete_program(unsigned int*);
typedef void CALLSTYLE quo_gl_delete_render_buffers(unsigned int, unsigned int*);
typedef void CALLSTYLE quo_gl_delete_shader(unsigned int);
typedef void CALLSTYLE quo_gl_delete_vertex_arrays(unsigned int, unsigned int*);
typedef void CALLSTYLE quo_gl_enable_vertex_attrib_array(unsigned int);
typedef void CALLSTYLE quo_gl_frame_buffer_render_buffer(unsigned int, unsigned int, unsigned int, int);
typedef void CALLSTYLE quo_gl_frame_buffer_texture_2d(unsigned int, unsigned int, unsigned int, unsigned int, int);
typedef void CALLSTYLE quo_gl_gen_buffers(unsigned int, unsigned int*);
typedef void CALLSTYLE quo_gl_gen_frame_buffers(unsigned int, unsigned int*);
typedef void CALLSTYLE quo_gl_gen_render_buffers(unsigned int, unsigned int*);
typedef void CALLSTYLE quo_gl_gen_vertex_arrays(unsigned int, unsigned int*);
typedef void CALLSTYLE quo_gl_get_program_info_log(unsigned int, int, int, char*);
typedef void CALLSTYLE quo_gl_get_program_iv(unsigned int, unsigned int, int*);
typedef void CALLSTYLE quo_gl_get_shader_info_log(unsigned int, int, int, char*);
typedef void CALLSTYLE quo_gl_get_shader_iv(unsigned int, unsigned int, int*);
typedef void CALLSTYLE quo_gl_link_program(unsigned int);
typedef void CALLSTYLE quo_gl_render_buffer_storage(unsigned int, unsigned int, unsigned int, unsigned int);
typedef void CALLSTYLE quo_gl_shader_source(unsigned int, int, const char**, const int*);
typedef void CALLSTYLE quo_gl_uniform_1_f(int, float);
typedef void CALLSTYLE quo_gl_uniform_1_i(int, int);
typedef void CALLSTYLE quo_gl_uniform_2_f(int, float, float);
typedef void CALLSTYLE quo_gl_uniform_3_f(int, float, float, float);
typedef void CALLSTYLE quo_gl_uniform_4_f(int, float, float, float, float);
typedef void CALLSTYLE quo_gl_uniform_matrix_4_f_v(int, int, quo_bool, float*);
typedef void CALLSTYLE quo_gl_use_program(unsigned int);
typedef void CALLSTYLE quo_gl_vertex_attrib_pointer(unsigned int, int, unsigned int, quo_bool, int, const void*);

/* Load all OpenGL functions */
void quo_load_gl();
#endif

/**
 * @brief Get the time since the program began, in milliseconds.
 */
double quo_get_elapsed_time();

/* -----------------------
 * START WINDOW
 * -----------------------*/

/**
 * @brief [internal use only] Key value pair, for storing system input map items
 */
typedef struct quo_InputHashTableItem {
	int key; /**< System keycode */
	int value; /**< Corresponding generic keycode */
} quo_InputHashTableItem;

/**
 * @brief [internal use only] Hash table for storing keymaps
 */
typedef struct quo_InputHashTable {
	quo_InputHashTableItem hash_array[QUO_KEY_COUNT]; /**< Array for storing input hash table */
} quo_InputHashTable;

/**
 * @brief [internal use only] Initialise a new input hash table
 */
void quo_init_input_table(quo_InputHashTable* table);
/**
 * @brief [internal use only] Search the input table for a key
 */
int quo_search_input_table(quo_InputHashTable* table, int key);
/**
 * @brief [internal use only] Insert a key value pair into the input table
 */
void quo_insert_input_table(quo_InputHashTable* table, int key, int value);
/**
 * @brief [internal use only] Sorts the input hash table to prepare it for binary search
 */
void quo_prepare_input_table(quo_InputHashTable* table);

/**
 * @brief Platform window structure. Responsible for storing data about a window's state and it's OpenGL context
 */
typedef struct quo_Window {
	quo_GLDeviceContext device_context; /**< Platform OpenGL device context */
	quo_GLRenderContext render_context; /**< Platform OpenGL render context */

	quo_bool is_open; /**< Initially set to true, when the window is closed, set to false */
	quo_bool is_focused; /**< Stores whether or not the window is capturing keyboard and mouse input */
	int width; /**< Stores the width of the window. If the window is resizable, then this will be updated on a window resize. */
	int height; /**< Stores the height of the window. If the window is resizable, then this will be updated on a window resize. */
	quo_bool resizable; /**< Stores whether the window is resizable or not. */

	double frame_time; /**< Stores the time since the last frame. */
	double now_time;
	double old_time;

	double fps; /**< Stores the FPS of the window */

	quo_InputHashTable key_map; /**< Hash table for mapping platform keys to generic quo keymaps. */

#if defined(QUO_PLATFORM_X11)
	Display* display;
	Window window_root;
	Window window;
	XVisualInfo* visual_info;
	Colormap color_map;
	XSetWindowAttributes set_window_attribs;
#endif

#if defined(QUO_PLATFORM_WINDOWS)
	HWND hwnd;
#endif
} quo_Window;

/**
 * @brief Open a new window
 * @param window Pointer to the window to initialise
 * @param w Height of the new window
 * @param h Width of the new window
 * @param resizeable Flag to set whether the window should be resizable or not
 */
void quo_init_window(quo_Window* window, int w, int h, quo_bool resizable);

/**
 * @brief Set the title/caption of a window
 * @param window Pointer to the window to set title
 * @param title New title string
 */
void quo_set_window_title(quo_Window* window, const char* title);

/**
 * @brief Update a window, to be called at the end of each frame
 * @param window Pointer to the window to update
 */
void quo_update_window(quo_Window* window);

/**
 * @brief Update a window's events, to be called at the start of each frame
 * @param window Pointer to the window to update events
 */
void quo_update_window_events(quo_Window* window);

/**
 * @brief Close and destroy a window
 * @param window Pointer to the window to free
 */
void quo_free_window(quo_Window* window);

/* -----------------------
 * END WINDOW
 * -----------------------*/

/* -----------------------
 * START MATHS
 * -----------------------*/

#define QUO_PI 3.14159265358f

/**
 * @brief Generic 2 dimensional vector class
 */
typedef struct quo_vec2 {
	float x, y;
} quo_vec2;

/**
 * @brief Add two quo_vec2s together
 * @param a First vector to add
 * @param b Second vector to add
 * @return Result of addition
 */
quo_vec2 quo_add_vec2(quo_vec2 a, quo_vec2 b);

/**
 * @brief Subtract a quo_vec2 from another
 * @param a Vector to subtract from
 * @param b Vector to subtract
 * @return Result of subtraction
 */
quo_vec2 quo_subtract_vec2(quo_vec2 a, quo_vec2 b);

/**
 * @brief Multiply two quo_vec2s
 * @param a First vector to multiply
 * @param b Second vector to multiply
 * @return Result of multiplication
 */
quo_vec2 quo_multiply_vec2(quo_vec2 a, quo_vec2 b);

/**
 * @brief Divide a quo_vec2 by another
 * @param a Vector to be divided
 * @param b Vector to divide by
 * @return Result of division
 */
quo_vec2 quo_divide_vec2(quo_vec2 a, quo_vec2 b);

/**
 * @brief Normalise a quo_vec2
 * @param v Vector to be normalised
 * @return The normalised quo_vec2
 */
quo_vec2 quo_normalise_vec2(quo_vec2 v);

/**
 * @brief Calculate the magnitude of a quo_vec2
 * @param v Vector to calculate magnitude
 * @return The magnitude of the vector
 */
float quo_vec2_magnitude(quo_vec2 v);

/**
 * @brief Calculate the dot product of two quo_vec2s
 * @param a First vector involved in the calculation
 * @param a Second vector involved in the calculation
 * @return The dot product of the two vectors
 */
float quo_dot_vec2(quo_vec2 a, quo_vec2 b);

/**
 * @brief Generic 3 dimensional vector class
 */
typedef struct quo_vec3 {
	float x, y, z;
} quo_vec3;

/**
 * @brief Add two quo_vec3s together
 * @param a First vector to add
 * @param b Second vector to add
 * @return Result of addition
 */
quo_vec3 quo_add_vec3(quo_vec3 a, quo_vec3 b);

/**
 * @brief Subtract a quo_vec3 from another
 * @param a Vector to subtract from
 * @param b Vector to subtract
 * @return Result of subtraction
 */
quo_vec3 quo_subtract_vec3(quo_vec3 a, quo_vec3 b);

/**
 * @brief Multiply two quo_vec3s
 * @param a First vector to multiply
 * @param b Second vector to multiply
 * @return Result of multiplication
 */
quo_vec3 quo_multiply_vec3(quo_vec3 a, quo_vec3 b);

/**
 * @brief Divide a quo_vec3 by another
 * @param a Vector to be divided
 * @param b Vector to divide by
 * @return Result of division
 */
quo_vec3 quo_divide_vec3(quo_vec3 a, quo_vec3 b);

/**
 * @brief Normalise a quo_vec3
 * @param a Vector to be normalised
 * @return Normalised vector
 */
quo_vec3 quo_normalise_vec3(quo_vec3 v);

/**
 * @brief Calculate the magnitude of a quo_vec3
 * @param v Vector to calculate magnitude
 * @return The magnitude of the vector
 */
float quo_vec3_magnitude(quo_vec3 v);

/**
 * @brief Calculate the cross product of two a quo_vec3s
 * @param a First vector involved in calculation
 * @param b Second vector involved in calculation
 * @return Resulting cross product
 */
quo_vec3 quo_cross_vec3(quo_vec3 a, quo_vec3 b);

/**
 * @brief Calculate the dot product of two quo_vec3s
 * @param a First vector involved in the calculation
 * @param a Second vector involved in the calculation
 * @return The dot product of the two vectors
 */
float quo_dot_vec3(quo_vec3 a, quo_vec3 b);

/**
 * @brief Represents a 4x4 float matrix
 */
typedef struct quo_Matrix {
	float elements[16];
} quo_Matrix;

/**
 * @brief Create an identity matrix
 * @return A new identity matrix
 */
quo_Matrix quo_identity();

/**
 * @brief Translate a matrix
 * @param m Matrix to be translated
 * @param translation Translation to be applied
 * @return The translated matrix
 */
quo_Matrix quo_translate(quo_Matrix m, quo_vec3 translation);

/**
 * @brief Rotate a matrix
 * @param m Matrix to be rotated
 * @param angle Angle of rotation to be applied in degrees
 * @param axis Axis on which to apply rotation
 * @return The rotated matrix
 */
quo_Matrix quo_rotate(quo_Matrix m, float angle, quo_vec3 axis);

/**
 * @brief Scale a matrix
 * @param m Matrix to be scaled
 * @param scale Rotation to be applied
 * @return The rotated matrix
 */
quo_Matrix quo_scale(quo_Matrix m, quo_vec3 scale);

/**
 * @brief Create an orthographic projection matrix
 * @param left Left bound
 * @param right Right bound
 * @param bottom Lower bound
 * @param top Upper bound
 * @param near_plane Near clipping plane
 * @param far_plane Far clipping plane
 * @return The new orthographic projection matrix
 */
quo_Matrix quo_orthographic(float left, float right, float bottom, float top, float near_plane, float far_plane);

/**
 * @brief Create a perspective projection matrix
 * @param fov Field of view in degrees
 * @param aspect Aspect ratio
 * @param near_plane Near clipping plane
 * @param far_plane Far clipping plane
 * @return The new perspective projection matrix
 */
quo_Matrix quo_perspective(float fov, float aspect, float near_plane, float far_plane);

/**
 * @brief Convert degrees to radians
 * @param deg Angle in degrees to convert
 * @return Angle in radians
 */
inline static float quo_to_radians(float deg) {
	return (float)(deg * (QUO_PI / 180.0f));
}

/* -----------------------
 * END MATHS
 * -----------------------*/

/**
 * @brief Generic rectangle struct
 */
typedef struct quo_Rect {
	int x; /**< X-axis position. */
	int y; /**< Y-axis position. */
	int w; /**< Width */
	int h; /**< Height */
} quo_Rect;

/* -----------------------
 * START RENDERER
 * -----------------------*/

/**
 * @brief Maximum amount of shaders that can be created
 */
#define QUO_MAX_SHADERS 10

/**
 * @brief Represents a bitmap image, containing it's raw pixel data, it's width and height and it's component count
 */
typedef struct quo_BitmapImage {
	int width; /**< Width of the image */
	int height; /**< Height of the image */
	int component_count; /**< Amount of components in the image */
	unsigned char* pixels; /**< Raw pixe data */
} quo_BitmapImage;

/**
 * @brief Load a bitmap from a file. The file must not have a colour space written to it's header.
 * @param filename Filename string
 * @param image Raw image data
 * @param components Component count, 3 for RGB, 4 for RGBA
 * @return true on success
 */
quo_bool quo_load_bitmap_from_file(const char* filename, quo_BitmapImage* image, unsigned int components);

/**
 * @brief Free a bitmap's pixel data. Should be called once converted into a texture.
 * @param image Image to free
 */
void quo_free_bitmap(quo_BitmapImage* image);

typedef enum quo_TextureFlags {
	QUO_TEXTUREFLAGS_ANTIALIASED = 1 << 0,
	QUO_TEXTUREFLAGS_ALIASED = 1 << 1,
} quo_TextureFlags;

/**
 * @brief A texture that lives on the GPU. Should be created from a bitmap image
 */
typedef struct quo_Texture {
	int width, height;
	unsigned int id;
} quo_Texture;

/**
 * @brief Create a texture
 * @param texture Resulting texture
 * @param bitmap Raw image data
 */
void quo_init_texture_from_bmp(quo_Texture* texture, quo_BitmapImage* bitmap, quo_TextureFlags flags);

/**
 * @brief Free a texture
 * @param texture Texture to free
 */
void quo_free_texture(quo_Texture* texture);

/**
 * @brief Bind a texture to a texture unit
 * @param unit Texture unit where the texture will be bound. Should be < 32
 */
void quo_bind_texture(quo_Texture* texture, unsigned int unit);

/**
 * @brief Unbind the currently bound texture
 */
void quo_unbind_texture();

/**
 * @brief Flags for the vertex buffer
 */
typedef enum quo_VertexBufferFlags {
	QUO_VERTEXBUFFERFLAGS_STATIC_DRAW = 1 << 0, /**< Use if the vertices/indices in this buffer will never change */
	QUO_VERTEXBUFFERFLAGS_DYNAMIC_DRAW = 1 << 1, /**< Use if you plan to call quo_update_vertices or quo_update_indices on this buffer */
	QUO_VERTEXBUFFERFLAGS_DRAW_LINES = 1 << 2, /**< Draw a wireframe */
	QUO_VERTEXBUFFERFLAGS_DRAW_LINE_STRIP = 1 << 3, /**< Draw a more complete wireframe */
	QUO_VERTEXBUFFERFLAGS_DRAW_TRIANGLES = 1 << 4, /**< Draw full triangles */
} quo_VertexBufferFlags;

/**
 * @brief A buffer for vertices
 */
typedef struct quo_VertexBuffer {
	unsigned int va_id; /**< OpenGL vertex array ID */
	unsigned int vb_id; /**< OpenGL vertex buffer ID */
	unsigned int ib_id; /**< OpenGL index buffer ID */
	unsigned int index_count; /**< Stores the number of indices */

	quo_VertexBufferFlags flags;
} quo_VertexBuffer;

/**
 * @brief Start the initialisation of a vertex buffer
 * @param vb Pointer to the vertex buffer
 */
void quo_begin_vertex_buffer(quo_VertexBuffer* vb, quo_VertexBufferFlags flags);

/**
 * @brief End the initialisation of a vertex buffer
 * @param vb Pointer to the vertex buffer
 */
void quo_finalise_vertex_buffer(quo_VertexBuffer* vb);

/**
 * @brief Push an array of vertices into the vertex buffer
 * @param vb Pointer to the vertex buffer
 * @param vertices Array of vertices
 * @param array_size Number of elements in the array of vertices
 */
void quo_push_vertices(quo_VertexBuffer* vb, float* vertices, unsigned int array_size);

/**
 * @brief Push an array of indices into the vertex buffer
 * @param vb Pointer to the vertex buffer
 * @param indices Array of indices
 * @param index_count Number of indices
 */
void quo_push_indices(quo_VertexBuffer* vb, unsigned int* indices, unsigned int index_count);

/**
 * @brief Update the vertex data in a vertex buffer. Make sure quo_push_vertices
 * has been called and the vertex buffer has enough space for the new data.
 * For dynamic buffers, quo_push_vertices can be used with NULL as an allocator.
 * @param vb Pointer to the vertex buffer
 * @param vertices Array of vertices
 * @param array_size Number of elements in the array of vertices
 */
void quo_update_vertices(quo_VertexBuffer* vb, float* vertices, unsigned int array_size);

/**
 * @brief Update the index data in a vertex buffer. Make sure quo_push_indices
 * has been called and the vertex buffer has enough space for the new data.
 * For dynamic buffers, quo_push_indices can be used with NULL as an allocator.
 * @param vb Pointer to the vertex buffer
 * @param indices Array of indices
 * @param index_count Number of indices
 */
void quo_update_indices(quo_VertexBuffer* vb, unsigned int* indices, unsigned int index_count);

/**
 * @brief Configure the kayout of the vertices in the buffer; You can set the location of positions, normals, texture coordinates, etc.
 * @param vb Pointer to the vertex buffer
 * @param index Index of the layout, to be referenced in the shader
 * @param component_count Number of components in the element; 2 for vec2, 3 for vec3, etc.
 * @param stride The amount of elements until the next layout location
 * @param start_offset Offset to start at
 */
void quo_configure_vertices(quo_VertexBuffer* vb, unsigned int index, unsigned int component_count, unsigned int stride, unsigned int start_offset);

/**
 * @brief Draw a vertex buffer
 * @param vb Pointer to the vertex buffer
 */
void quo_draw_vertex_buffer(quo_VertexBuffer* vb);

/**
 * @brief Free a vertex buffer
 * @param vb Pointer to the vertex buffer
 */
void quo_free_vertex_buffer(quo_VertexBuffer* vb);

/**
 * @brief To be used as an index into the renderer's shader array
 */
typedef unsigned int quo_ShaderHandle;

/**
 * @brief Responsible for drawing things to the screen
 */
typedef struct quo_Renderer {
	quo_Window* window; /**< Pointer to window on which this renderer should operate */
	quo_Matrix projection; /**< Projection matrix used to render sprites */

	quo_ShaderHandle sprite_shader; /**< Default sprite shader */

	quo_VertexBuffer quad;

	unsigned int shaders[QUO_MAX_SHADERS]; /**< Shader array */
	unsigned int shader_count; /**< Stores the current number of shaders */

	unsigned long background_color; /**< Colour that will be discarded in the fragment shader. Set this to whatever you want to be the "transparent" colour. Can be updated per-frame */
} quo_Renderer;

/**
 * @brief Create a hex colour from red, green and blue values
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @return Hex colour
 */
unsigned long quo_color_from_rgb(int r, int g, int b);

/**
 * @brief Initialise a new renderer
 * @param renderer Pointer to renderer to be initialised
 * @param window Pointer to window where this renderer will operate
 */
void quo_init_renderer(quo_Renderer* renderer, quo_Window* window);

/**
 * @brief Turns on 3D specific features such as depth testing. Call after quo_init_renderer
 */
void quo_enable_3d();

/**
 * @brief Free a renderer
 * @param renderer Pointer to renderer to be freed
 */
void quo_free_renderer(quo_Renderer* renderer);

/**
 * @brief Update a renderer. Should be called before quo_update_window
 * @param renderer Pointer to renderer to be updated
 */
void quo_update_renderer(quo_Renderer* renderer);

/**
 * @brief Clear the screen
 * @param color Hex colour that the screen will clear to
 */
void quo_clear_renderer(unsigned long color);

/**
 * @brief Draw a quo_Rect on the screen
 * @param renderer Pointer to renderer to use to draw the rectangle
 * @param rect Rectangle to be drawn
 * @param color Hex colour that the rectangle will be drawn as
 */
void quo_draw_rect(quo_Renderer* renderer, quo_Rect rect, unsigned long color);

/**
 * @brief Draw a quo_Texture on the screen
 * @param renderer Pointer to renderer to use to draw the texture
 * @param texture Texture to be drawn
 * @param src Source rectangle. This is the rectangle of the image that will be rendered, in terms of a sprite sheet
 * @param dest Destiniation rectangle. This is the rectangle where the texture will be rendered, in terms of the window
 * @param color Hex colour that the texture will be drawn as. Use 0xffffff (White) to use the original image colours.
 */
void quo_draw_texture(quo_Renderer* renderer, quo_Texture* texture, quo_Rect src, quo_Rect dest, unsigned long color);

/**
 * @brief Create a new shader
 * @param renderer Pointer to renderer where to store the shader
 * @param vertex_source String source code for the vertex shader
 * @param fragment_source String source code for the fragment shader
 * @return A handle to the new shader
 */
quo_ShaderHandle quo_create_shader(quo_Renderer* renderer, const char* vertex_source, const char* fragment_source);

/**
 * @brief Bind a shader
 * @param renderer Pointer to renderer where the shader is stored
 * @param shader Handle to shader to be bound
 */
void quo_bind_shader(quo_Renderer* renderer, quo_ShaderHandle shader);

/**
 * @brief Bind the default shader
 * @param renderer Pointer to renderer where the shader is stored
 */
void quo_bind_default_shader(quo_Renderer* renderer);

/**
 * @brief Set a uniform colour. Note: Shader must be bound before calling this function
 * @param renderer Pointer to renderer where the shader is stored
 * @param shader Handle to the shader who's uniform to set
 * @param uniform_name Name of the uniform to be set
 * @param color Value to be set in the shader
 */
void quo_shader_set_color(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, unsigned long color);

/**
 * @brief Set a uniform float. Note: Shader must be bound before calling this function
 * @param renderer Pointer to renderer where the shader is stored
 * @param shader Handle to the shader who's uniform to set
 * @param uniform_name Name of the uniform to be set
 * @param val Value to be set in the shader
 */
void quo_shader_set_float(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, float val);

/**
 * @brief Set a uniform integer. Note: Shader must be bound before calling this function
 * @param renderer Pointer to renderer where the shader is stored
 * @param shader Handle to the shader who's uniform to set
 * @param uniform_name Name of the uniform to be set
 * @param val Value to be set in the shader
 */
void quo_shader_set_int(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, int val);

/**
 * @brief Set a uniform matrix. Note: Shader must be bound before calling this function
 * @param renderer Pointer to renderer where the shader is stored
 * @param shader Handle to the shader who's uniform to set
 * @param uniform_name Name of the uniform to be set
 * @param m Matrix to be set in the shader
 */
void quo_shader_set_matrix(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, quo_Matrix m);

/**
 * @brief Set a uniform 2D vector. Note: Shader must be bound before calling this function
 * @param renderer Pointer to renderer where the shader is stored
 * @param shader Handle to the shader who's uniform to set
 * @param uniform_name Name of the uniform to be set
 * @param val Vector to be set in the shader
 */
void quo_shader_set_vec2(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, quo_vec2 val);

/**
 * @brief Set a uniform 3D vector. Note: Shader must be bound before calling this function
 * @param renderer Pointer to renderer where the shader is stored
 * @param shader Handle to the shader who's uniform to set
 * @param uniform_name Name of the uniform to be set
 * @param val Vector to be set in the shader
 */
void quo_shader_set_vec3(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, quo_vec3 val);

/**
 * @brief Set a uniform vector. Note: Shader must be bound before calling this function
 * @param renderer Pointer to renderer where the shader is stored
 * @param shader Handle to the shader who's uniform to set
 * @param uniform_name Name of the uniform to be set
 * @param x X value to be set in the shader
 * @param y Y value to be set in the shader
 * @param z Z value to be set in the
 * @param w W value to be set in the shader
 */
void quo_shader_set_vec4(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, float x, float y, float z, float w);

/**
 * @brief For offscreen rendering, ie. Rendering to a texture
 */
typedef struct quo_RenderTarget {
	unsigned int frame_buffer; /**< OpenGL frame buffer ID */
	unsigned int render_buffer; /**< OpenGL render buffer ID */

	quo_Texture output; /**< Output texture: Can be rendered using a quo_Renderer */
} quo_RenderTarget;

/**
 * @brief Initialise a render target
 * @param target The render target to initialise
 * @param width The initial width of the render target. Does not have to be the same as the window's width
 * @param height The initial height of the render target. Does not have to be the same as the window's height
 */
void quo_init_render_target(quo_RenderTarget* target, int width, int height);

/**
 * @brief Free a render target
 * @param target The render target to free
 */
void quo_free_render_target(quo_RenderTarget* target);

/**
 * @brief Bind a render target. Everything after this call will be rendered to the target.
 * @param target The render target to bind
 */
void quo_bind_render_target(quo_RenderTarget* target);

/**
 * @brief Bind the default render target, causing everything to continue rendering to the window (default frame buffer).
 */
void quo_bind_default_render_target();

/**
 * @brief Resize a render target.
 * @param target The render target to resize
 * @param width The new width for the target
 * @param height The new height for the target
 */
void quo_resize_render_target(quo_RenderTarget* target, int width, int height);


/* -----------------------
 * END RENDERER
 * -----------------------*/

/* -----------------------
 * START INPUT
 * -----------------------*/

/**
 * @brief Callback that gives information about inputted characters
 */
typedef void (*quo_character_callback)(char*);

/**
 * @brief Handles keyboard and mouse input
 */
typedef struct quo_InputSystem {
	quo_bool held_keys[QUO_KEY_COUNT]; /**< Keys that are currently held down */
	quo_bool down_keys[QUO_KEY_COUNT]; /**< Keys that have been pressed in the current frame */
	quo_bool up_keys[QUO_KEY_COUNT]; /**< Keys that have been released in the current frame */

	quo_bool held_mouse_buttons[QUO_MOUSE_BUTTON_COUNT]; /**< Mouse buttons that are currently held down */
	quo_bool down_mouse_buttons[QUO_MOUSE_BUTTON_COUNT]; /**< Mouse buttons that have been pressed in the current frame */
	quo_bool up_mouse_buttons[QUO_MOUSE_BUTTON_COUNT]; /**< Mouse buttons that have been released in the current frame */

	int mouse_x; /**< Mouse X coordinate */
	int mouse_y; /**< Mouse Y coordinate */

	quo_character_callback char_callback;
} quo_InputSystem;

/**
 * @brief Initialise the static input system. Called in quo_init_window
 */
void quo_init_input_system();

/**
 * @brief Update the input system. Called in quo_update
 */
void quo_update_input_system();

/**
 * @brief Set the character callback
 * @param callback The callback to be set
 */
void quo_set_character_callback(quo_character_callback callback);

/**
 * @brief Get any keys pressed as a character. Returnes '\0' if none are pressed
 */
char quo_get_input_character();

/**
 * @brief Check whether a key is currently held down
 * @param key Keycode to be checked
 * @return True if the key is pressed
 */
quo_bool quo_key_pressed(int key);

/**
 * @brief Check whether a key has been pressed in the current frame
 * @param key Keycode to be checked
 * @return True if the key has been pressed in the current frame
 */
quo_bool quo_key_just_pressed(int key);

/**
 * @brief Check whether a key has been released in the current frame
 * @param key Keycode to be checked
 * @return True if the key has been released in the current frame
 */
quo_bool quo_key_just_released(int key);

/**
 * @brief Check whether a mouse button is currently held down
 * @param button Mouse button code to be checked
 * @return True if the mouse button is pressed
 */
quo_bool quo_mouse_button_pressed(int button);

/**
 * @brief Check whether a mouse button has been pressed in the current frame
 * @param button Mouse button code to be checked
 * @return True if the mouse button has been pressed in the current frame
 */
quo_bool quo_mouse_button_just_pressed(int button);

/**
 * @brief Check whether a mouse button has been released in the current frame
 * @param button Mouse button code to be checked
 * @return True if the mouse button has been released in the current frame
 */
quo_bool quo_mouse_button_just_released(int button);

/**
 * @brief Get the mouse's x coordinate relative to the window
 * @return The mouse's x coordinate relative to the window
 */
int quo_get_mouse_x();

/**
 * @brief Get the mouse's y coordinate relative to the window
 * @return The mouse's y coordinate relative to the window
 */
int quo_get_mouse_y();

/**
 * @brief FOR INTERNAL USE ONLY.
 */
void i_quo_set_key_held_state(int key, quo_bool status);
/**
 * @brief FOR INTERNAL USE ONLY.
 */
void i_quo_set_key_down_state(int key, quo_bool status);
/**
 * @brief FOR INTERNAL USE ONLY.
 */
void i_quo_set_key_up_state(int key, quo_bool status);
/**
 * @brief FOR INTERNAL USE ONLY.
 */
void i_quo_set_mouse_button_held_state(int button, quo_bool status);
/**
 * @brief FOR INTERNAL USE ONLY.
 */
void i_quo_set_mouse_button_down_state(int button, quo_bool status);
/**
 * @brief FOR INTERNAL USE ONLY.
 */
void i_quo_set_mouse_button_up_state(int button, quo_bool status);
/**
 * @brief FOR INTERNAL USE ONLY.
 */
void i_quo_update_mouse_pos(int x, int y);

/**
 * @brief FOR INTERNAL USE ONLY.
 */
void i_quo_call_char_callback(char* characters);

/* -----------------------
 * END INPUT
 * -----------------------*/

/* -----------------------
 * START SERIALISATION
 * -----------------------*/

/**
 * @brief The default size of a byte buffer
 */
#define QUO_BYTE_BUFFER_DEFAULT_CAPACITY 1024

/**
 * @brief A buffer for holding generic data
 */
typedef struct quo_ByteBuffer {
	char* data;  /**< Raw data array */
	unsigned int position;  /**< Position of where to read the next byte from */
	unsigned int size;  /**< Current size of the buffer, increases as elements are added */
	unsigned int capacity;  /**< Maximum capacity of the buffer */
} quo_ByteBuffer;

/**
 * @brief Dump the contents of a byte buffer to a file
 * @param buffer Pointer to the buffer which to dump
 * @param file File stream to dump the buffer to
 */
void quo_byte_buffer_dump(quo_ByteBuffer* buffer, FILE* file);

/**
 * @brief Read a dumped buffer back from a file
 * @param buffer Pointer to the buffer to read into
 * @param file File stream containing the raw buffer data
 */
void quo_byte_buffer_read_file(quo_ByteBuffer* buffer, FILE* file);

/**
 * @brief Initialise a new byte buffer, with a capacity of QUO_BYTE_BUFFER_DEFAULT_CAPACITY
 * @param buffer Pointer to the buffer to initialise
 */
void quo_init_byte_buffer(quo_ByteBuffer* buffer);

/**
 * @brief Free a byte buffer's memory
 * @param buffer Pointer to the buffer to free
 */
void quo_free_byte_buffer(quo_ByteBuffer* buffer);

/**
 * @brief Resize a byte buffer to contain more elements. This happens automatically when writing.
 * @param buffer Pointer to buffer to resize
 */
void quo_resize_byte_buffer(quo_ByteBuffer* buffer, unsigned int capacity);

/**
 * @brief FOR INTERNAL USE ONLY. Use the quo_byte_buffer_write macro instead.
 */
void i_quo_byte_buffer_write_impl(quo_ByteBuffer* buffer, void* data, unsigned int size);


/**
 * @brief Write some data to a byte buffer at the current position
 * @param _buffer Pointer to buffer to write to
 * @param _type Type of data to be written, eg. int, float
 * @param _val Value to write
 */
#define quo_byte_buffer_write(_buffer, _type, _val) \
do {\
	quo_ByteBuffer* _bb = (_buffer); \
	unsigned int _size = sizeof(_type); \
	_type _v = _val; \
	i_quo_byte_buffer_write_impl(_bb, (void*)&(_v), _size); \
} while (0)

/**
 * @brief Read some data from a byte buffer at the current position
 * @param _buffer Pointer to buffer to read from
 * @param _type Type of data to be read, eg. int, float
 * @param _val_p Pointer to value to read into
 */
#define quo_byte_buffer_read(_buffer, _type, _val_p) \
do {\
	_type* _v = (_type*)(_val_p); \
	quo_ByteBuffer* _bb = (_buffer); \
	*(_v) = *(_type*)(_bb->data + _bb->position); \
	_bb->position += sizeof(_type); \
} while (0)

/* -----------------------
 * END SERIALISATION
 * -----------------------*/

/*  _____                 _                           _        _   _
 * |_   _|               | |                         | |      | | (_)
 *   | |  _ __ ___  _ __ | | ___ _ __ ___   ___ _ __ | |_ __ _| |_ _  ___  _ __
 *   | | | '_ ` _ \| '_ \| |/ _ \ '_ ` _ \ / _ \ '_ \| __/ _` | __| |/ _ \| '_ \
 *  _| |_| | | | | | |_) | |  __/ | | | | |  __/ | | | || (_| | |_| | (_) | | | |
 * |_____|_| |_| |_| .__/|_|\___|_| |_| |_|\___|_| |_|\__\__,_|\__|_|\___/|_| |_|
 *                 | |
 *                 |_|
 */

#ifdef QUO_IMPL
#ifndef DOXYGEN_IGNORE

/* C standard includes */
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef QUO_USE_STB_IMAGE
#include "stb_image.h"
#endif

/* OpenGL functions */
quo_gl_attach_shader* glAttachShader = NULL;
quo_gl_bind_buffer* glBindBuffer = NULL;
quo_gl_bind_frame_buffer* glBindFramebuffer = NULL;
quo_gl_bind_render_buffer* glBindRenderbuffer = NULL;
quo_gl_bind_vertex_array* glBindVertexArray = NULL;
quo_gl_buffer_data* glBufferData = NULL;
quo_gl_buffer_sub_data* glBufferSubData = NULL;
quo_gl_compile_shader* glCompileShader = NULL;
quo_gl_create_program* glCreateProgram = NULL;
quo_gl_create_shader* glCreateShader = NULL;
quo_gl_delete_buffers* glDeleteBuffers = NULL;
quo_gl_delete_frame_buffers* glDeleteFramebuffers = NULL;
quo_gl_delete_program* glDeleteProgram = NULL;
quo_gl_delete_render_buffers* glDeleteRenderbuffers = NULL;
quo_gl_delete_shader* glDeleteShader = NULL;
quo_gl_delete_vertex_arrays* glDeleteVertexArrays = NULL;
quo_gl_enable_vertex_attrib_array* glEnableVertexAttribArray = NULL;
quo_gl_frame_buffer_render_buffer* glFramebufferRenderbuffer = NULL;
quo_gl_frame_buffer_texture_2d* glFramebufferTexture2D = NULL;
quo_gl_gen_buffers* glGenBuffers = NULL;
quo_gl_gen_frame_buffers* glGenFramebuffers = NULL;
quo_gl_gen_render_buffers* glGenRenderbuffers = NULL;
quo_gl_gen_vertex_arrays* glGenVertexArrays = NULL;
quo_gl_get_program_info_log* glGetProgramInfoLog = NULL;
quo_gl_get_program_iv* glGetProgramiv = NULL;
quo_gl_get_shader_info_log* glGetShaderInfoLog = NULL;
quo_gl_get_shader_iv* glGetShaderiv = NULL;
quo_gl_get_uniform_location* glGetUniformLocation = NULL;
quo_gl_link_program* glLinkProgram = NULL;
quo_gl_render_buffer_storage* glRenderbufferStorage = NULL;
quo_gl_shader_source* glShaderSource = NULL;
quo_gl_uniform_1_f* glUniform1f = NULL;
quo_gl_uniform_1_i* glUniform1i = NULL;
quo_gl_uniform_2_f* glUniform2f = NULL;
quo_gl_uniform_3_f* glUniform3f = NULL;
quo_gl_uniform_4_f* glUniform4f = NULL;
quo_gl_uniform_matrix_4_f_v* glUniformMatrix4fv = NULL;
quo_gl_use_program* glUseProgram = NULL;
quo_gl_vertex_attrib_pointer* glVertexAttribPointer = NULL;

#ifdef QUO_PLATFORM_WINDOWS
/* X11 already defines this, on Windows it has to be done manually */
quo_gl_active_texture* glActiveTexture = NULL;
#endif

void quo_load_gl() {
	/* Load modern OpenGL functions */
	glAttachShader = QUO_LOAD_GL_FUNC(quo_gl_attach_shader, "glAttachShader");
	glBindBuffer = QUO_LOAD_GL_FUNC(quo_gl_bind_buffer, "glBindBuffer");
	glBindFramebuffer = QUO_LOAD_GL_FUNC(quo_gl_bind_frame_buffer, "glBindFramebuffer");
	glBindRenderbuffer = QUO_LOAD_GL_FUNC(quo_gl_bind_render_buffer, "glBindRenderbuffer");
	glBindVertexArray = QUO_LOAD_GL_FUNC(quo_gl_bind_vertex_array, "glBindVertexArray");
	glBufferData = QUO_LOAD_GL_FUNC(quo_gl_buffer_data, "glBufferData");
	glBufferSubData = QUO_LOAD_GL_FUNC(quo_gl_buffer_sub_data, "glBufferSubData");
	glCompileShader = QUO_LOAD_GL_FUNC(quo_gl_compile_shader, "glCompileShader");
	glCreateProgram = QUO_LOAD_GL_FUNC(quo_gl_create_program, "glCreateProgram");
	glCreateShader = QUO_LOAD_GL_FUNC(quo_gl_create_shader, "glCreateShader");
	glDeleteBuffers = QUO_LOAD_GL_FUNC(quo_gl_delete_buffers, "glDeleteBuffers");
	glDeleteFramebuffers = QUO_LOAD_GL_FUNC(quo_gl_delete_frame_buffers, "glDeleteFramebuffers");
	glDeleteProgram = QUO_LOAD_GL_FUNC(quo_gl_delete_program, "glDeleteProgram");
	glDeleteRenderbuffers = QUO_LOAD_GL_FUNC(quo_gl_delete_render_buffers, "glDeleteRenderbuffers");
	glDeleteShader = QUO_LOAD_GL_FUNC(quo_gl_delete_shader, "glDeleteShader");
	glDeleteVertexArrays = QUO_LOAD_GL_FUNC(quo_gl_delete_vertex_arrays, "glDeleteVertexArrays");
	glEnableVertexAttribArray = QUO_LOAD_GL_FUNC(quo_gl_enable_vertex_attrib_array, "glEnableVertexAttribArray");
	glFramebufferRenderbuffer = QUO_LOAD_GL_FUNC(quo_gl_frame_buffer_render_buffer, "glFramebufferRenderbuffer");
	glFramebufferTexture2D = QUO_LOAD_GL_FUNC(quo_gl_frame_buffer_texture_2d, "glFramebufferTexture2D");
	glGenBuffers = QUO_LOAD_GL_FUNC(quo_gl_gen_buffers, "glGenBuffers");
	glGenFramebuffers = QUO_LOAD_GL_FUNC(quo_gl_gen_frame_buffers, "glGenFramebuffers");
	glGenRenderbuffers = QUO_LOAD_GL_FUNC(quo_gl_gen_render_buffers, "glGenRenderbuffers");
	glGenVertexArrays = QUO_LOAD_GL_FUNC(quo_gl_gen_vertex_arrays, "glGenVertexArrays");
	glGetProgramInfoLog = QUO_LOAD_GL_FUNC(quo_gl_get_program_info_log, "glGetProgramInfoLog");
	glGetProgramiv = QUO_LOAD_GL_FUNC(quo_gl_get_program_iv, "glGetProgramiv");
	glGetShaderInfoLog = QUO_LOAD_GL_FUNC(quo_gl_get_shader_info_log, "glGetShaderInfoLog");
	glGetShaderiv = QUO_LOAD_GL_FUNC(quo_gl_get_shader_iv, "glGetShaderiv");
	glGetUniformLocation = QUO_LOAD_GL_FUNC(quo_gl_get_uniform_location, "glGetUniformLocation");
	glLinkProgram = QUO_LOAD_GL_FUNC(quo_gl_link_program, "glLinkProgram");
	glRenderbufferStorage = QUO_LOAD_GL_FUNC(quo_gl_render_buffer_storage, "glRenderbufferStorage");
	glShaderSource = QUO_LOAD_GL_FUNC(quo_gl_shader_source, "glShaderSource");
	glUniform1f = QUO_LOAD_GL_FUNC(quo_gl_uniform_1_f, "glUniform1f");
	glUniform1i = QUO_LOAD_GL_FUNC(quo_gl_uniform_1_i, "glUniform1i");
	glUniform2f = QUO_LOAD_GL_FUNC(quo_gl_uniform_2_f, "glUniform2f");
	glUniform3f = QUO_LOAD_GL_FUNC(quo_gl_uniform_3_f, "glUniform3f");
	glUniform4f = QUO_LOAD_GL_FUNC(quo_gl_uniform_4_f, "glUniform4f");
	glUniformMatrix4fv = QUO_LOAD_GL_FUNC(quo_gl_uniform_matrix_4_f_v, "glUniformMatrix4fv");
	glUseProgram = QUO_LOAD_GL_FUNC(quo_gl_use_program, "glUseProgram");
	glVertexAttribPointer = QUO_LOAD_GL_FUNC(quo_gl_vertex_attrib_pointer, "glVertexAttribPointer");


#ifdef QUO_PLATFORM_WINDOWS
	/* X11 already defines this, on Windows it has to be done manually */
	glActiveTexture = QUO_LOAD_GL_FUNC(quo_gl_active_texture, "glActiveTexture");
#endif
}

/* Get the time since the program started in seconds */
double quo_get_elapsed_time() {
	return ((double)clock() / (double)CLOCKS_PER_SEC) * 1000.0;
}

/* -----------------------
 * START WINDOW
 * -----------------------*/

/* Hash a key code, for the input table */
static int quo_input_hash_code(int key) {
	return key % QUO_KEY_COUNT;
}

/* For sorting the elements of the input table */
static int quo_input_table_compare_func(const void* a, const void* b) {
	return (((quo_InputHashTableItem*)a)->key - ((quo_InputHashTableItem*)b)->key);
}

void quo_init_input_table(quo_InputHashTable* table) {
	assert(table != NULL);

	for (unsigned int i = 0; i < QUO_KEY_COUNT; i++) {
		table->hash_array[i] = (quo_InputHashTableItem){-1, 0};
	}
}

void quo_prepare_input_table(quo_InputHashTable* table) {
	assert(table != NULL);

	/* STD quicksort function, so that we can use a binary
	 * search instead of a linear one. */
	qsort(table->hash_array, QUO_KEY_COUNT, sizeof(quo_InputHashTableItem), quo_input_table_compare_func);
}

/* Recursive binary search */
static int quo_binary_search_input_table(quo_InputHashTable* table, int l, int r, int key) {
	if (r >= l) {
		int mid = l + (r - l) / 2;

		if (table->hash_array[mid].key == key) {
			return mid;
		}

		if (table->hash_array[mid].key > key) {
			return quo_binary_search_input_table(table, l, mid - 1, key);
		}

		return quo_binary_search_input_table(table, mid + 1, r, key);
	}

	return 0;
}

int quo_search_input_table(quo_InputHashTable* table, int key) {
	assert(table != NULL);

	int hash_index = quo_input_hash_code(key);

	return table->hash_array[quo_binary_search_input_table(table, 0, QUO_KEY_COUNT, key)].value;
}

void quo_insert_input_table(quo_InputHashTable* table, int key, int value) {
	assert(table != NULL);

	quo_InputHashTableItem item = {key, value};

	int hash_index = quo_input_hash_code(key);

	while (table->hash_array[hash_index].key != -1) {
		hash_index++;

		hash_index %= QUO_KEY_COUNT;
	}

	table->hash_array[hash_index] = item;
}

/* Win32 event callback */
#if defined(QUO_PLATFORM_WINDOWS)
static LRESULT CALLBACK quo_win32_event_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	/* Grab the necessary data */
	LONG_PTR lpUserData = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	quo_Window* q_window = (quo_Window*)lpUserData;

	/* Make sure the window pointer is not null */
	if (q_window) {
		switch (msg) { /* Switch on the event message type */
		case WM_DESTROY:
			q_window->is_open = false;
			return 0;
		case WM_SIZE:
				q_window->width = lparam & 0xFFFF;
				q_window->height = (lparam >> 16) & 0xFFFF;
				return 0;
		case WM_KEYDOWN: {
			if (q_window->is_focused) {
				/* Set the correct inputs */
				int key = quo_search_input_table(&q_window->key_map, wparam);
				i_quo_set_key_held_state(key, true);
				i_quo_set_key_down_state(key, true);

				/* Get the input string, for the character callback */
				char state[256];
				char buffer[256];
				GetKeyboardState(state);

				unsigned int scan_code = (lparam >> 16) & 0xFF;
				int i = ToUnicode(wparam, scan_code, state, buffer, 16, 0);
				buffer[i] = 0;
				if (strlen(buffer) > 0) {
					i_quo_call_char_callback(buffer);
				}
			}
			return 0;
		}
		case WM_KEYUP: {
			if (q_window->is_focused) {
				/* Set the correct inputs */
				int key = quo_search_input_table(&q_window->key_map, wparam);
				i_quo_set_key_held_state(key, false);
				i_quo_set_key_up_state(key, true);
			}
			return 0;
		}
		case WM_SETFOCUS:
			q_window->is_focused = true;
			return 0;
		case WM_KILLFOCUS:
			q_window->is_focused = false;
			return 0;
		case WM_LBUTTONDOWN:
			if (q_window->is_focused) {
				i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_1, true);
				i_quo_set_mouse_button_down_state(QUO_MOUSE_BUTTON_1, true);
			}
			return 0;
		case WM_MBUTTONDOWN:
			if (q_window->is_focused) {
				i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_2, true);
				i_quo_set_mouse_button_down_state(QUO_MOUSE_BUTTON_2, true);
			}
			return 0;
		case WM_RBUTTONDOWN:
			if (q_window->is_focused) {
				i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_3, true);
				i_quo_set_mouse_button_down_state(QUO_MOUSE_BUTTON_3, true);
			}
			return 0;
		case WM_LBUTTONUP:
			if (q_window->is_focused) {
				i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_1, false);
				i_quo_set_mouse_button_up_state(QUO_MOUSE_BUTTON_1, true);
			}
			return 0;
		case WM_MBUTTONUP:
			if (q_window->is_focused) {
				i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_2, false);
				i_quo_set_mouse_button_up_state(QUO_MOUSE_BUTTON_2, true);
			}
			return 0;
		case WM_RBUTTONUP:
			if (q_window->is_focused) {
				i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_3, false);
				i_quo_set_mouse_button_up_state(QUO_MOUSE_BUTTON_3, true);
			}
			return 0;
		case WM_MOUSEMOVE:
			if (q_window->is_focused) {
				unsigned int x = lparam & 0xFFFF; unsigned int y = (lparam >> 16) & 0xFFFF;
				i_quo_update_mouse_pos(x, y);
			}
			return 0;
		default:
			break;
		}
	}

	/* No inputs occured */
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
#endif

#ifdef QUO_PLATFORM_WINDOWS
static void quo_init_window_windows(quo_Window* window, int w, int h, quo_bool resizable) {
	/* Configure the window */
	WNDCLASS wc;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = quo_win32_event_callback;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszMenuName = NULL;
	wc.hbrBackground = NULL;
	wc.lpszClassName = "quo";
	RegisterClass(&wc);

	/* Window styling */
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;

	if (resizable) {
		dwStyle |= WS_THICKFRAME | WS_MAXIMIZEBOX;
	}

	window->width = w;
	window->height = h;

	RECT rWndRect = { 0, 0, w, h };
	AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);
	int width = rWndRect.right - rWndRect.left;
	int height = rWndRect.bottom - rWndRect.top;

	/* Create the window */
	window->hwnd = CreateWindowEx(dwExStyle, "quo", "", dwStyle, 0, 0, width, height, NULL, NULL, GetModuleHandle(NULL), window);

	SetWindowLongPtr(window->hwnd, GWLP_USERDATA, (LONG_PTR)window);

	/* Set up OpenGL */
	window->device_context = GetDC((HWND)window->hwnd);
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	/* Set the pixel format */
	int pf = 0;
	if (!(pf = ChoosePixelFormat(window->device_context, &pfd))) { return; }
	SetPixelFormat(window->device_context, pf, &pfd);

	if (!(window->render_context = wglCreateContext(window->device_context))) { return; }
	wglMakeCurrent(window->device_context, window->render_context);

	/* Set the keyboard mapping */
	quo_init_input_table(&window->key_map);
	quo_insert_input_table(&window->key_map, 0x00, QUO_KEY_UNKNOWN);
	quo_insert_input_table(&window->key_map, 0x41, QUO_KEY_A);
	quo_insert_input_table(&window->key_map, 0x42, QUO_KEY_B);
	quo_insert_input_table(&window->key_map, 0x43, QUO_KEY_C);
	quo_insert_input_table(&window->key_map, 0x44, QUO_KEY_D);
	quo_insert_input_table(&window->key_map, 0x45, QUO_KEY_E);
	quo_insert_input_table(&window->key_map, 0x46, QUO_KEY_F);
	quo_insert_input_table(&window->key_map, 0x47, QUO_KEY_G);
	quo_insert_input_table(&window->key_map, 0x48, QUO_KEY_H);
	quo_insert_input_table(&window->key_map, 0x49, QUO_KEY_I);
	quo_insert_input_table(&window->key_map, 0x4A, QUO_KEY_J);
	quo_insert_input_table(&window->key_map, 0x4B, QUO_KEY_K);
	quo_insert_input_table(&window->key_map, 0x4C, QUO_KEY_L);
	quo_insert_input_table(&window->key_map, 0x4D, QUO_KEY_M);
	quo_insert_input_table(&window->key_map, 0x4E, QUO_KEY_N);
	quo_insert_input_table(&window->key_map, 0x4F, QUO_KEY_O);
	quo_insert_input_table(&window->key_map, 0x50, QUO_KEY_P);
	quo_insert_input_table(&window->key_map, 0x51, QUO_KEY_Q);
	quo_insert_input_table(&window->key_map, 0x52, QUO_KEY_R);
	quo_insert_input_table(&window->key_map, 0x53, QUO_KEY_S);
	quo_insert_input_table(&window->key_map, 0x54, QUO_KEY_T);
	quo_insert_input_table(&window->key_map, 0x55, QUO_KEY_U);
	quo_insert_input_table(&window->key_map, 0x56, QUO_KEY_V);
	quo_insert_input_table(&window->key_map, 0x57, QUO_KEY_W);
	quo_insert_input_table(&window->key_map, 0x58, QUO_KEY_X);
	quo_insert_input_table(&window->key_map, 0x59, QUO_KEY_Y);
	quo_insert_input_table(&window->key_map, 0x5A, QUO_KEY_Z);

	/* Function keys */
	quo_insert_input_table(&window->key_map, VK_F1, QUO_KEY_F1);
	quo_insert_input_table(&window->key_map, VK_F2, QUO_KEY_F2);
	quo_insert_input_table(&window->key_map, VK_F3, QUO_KEY_F3);
	quo_insert_input_table(&window->key_map, VK_F4, QUO_KEY_F4);
	quo_insert_input_table(&window->key_map, VK_F5, QUO_KEY_F5);
	quo_insert_input_table(&window->key_map, VK_F6, QUO_KEY_F6);
	quo_insert_input_table(&window->key_map, VK_F7, QUO_KEY_F7);
	quo_insert_input_table(&window->key_map, VK_F8, QUO_KEY_F8);
	quo_insert_input_table(&window->key_map, VK_F9, QUO_KEY_F9);
	quo_insert_input_table(&window->key_map, VK_F10, QUO_KEY_F10);
	quo_insert_input_table(&window->key_map, VK_F11, QUO_KEY_F11);
	quo_insert_input_table(&window->key_map, VK_F12, QUO_KEY_F12);

	/* Navigation */
	quo_insert_input_table(&window->key_map, VK_DOWN, QUO_KEY_DOWN);
	quo_insert_input_table(&window->key_map, VK_LEFT, QUO_KEY_LEFT);
	quo_insert_input_table(&window->key_map, VK_RIGHT, QUO_KEY_RIGHT);
	quo_insert_input_table(&window->key_map, VK_UP, QUO_KEY_UP);
	quo_insert_input_table(&window->key_map, VK_ESCAPE, QUO_KEY_ESCAPE);

	/* General navigation & editing */
	quo_insert_input_table(&window->key_map, VK_ESCAPE, QUO_KEY_ESCAPE);
	quo_insert_input_table(&window->key_map, VK_RETURN, QUO_KEY_ENTER);
	quo_insert_input_table(&window->key_map, VK_BACK, QUO_KEY_BACKSPACE);
	quo_insert_input_table(&window->key_map, VK_PAUSE, QUO_KEY_PAUSE);
	quo_insert_input_table(&window->key_map, VK_SCROLL, QUO_KEY_SCROLL_LOCK);
	quo_insert_input_table(&window->key_map, VK_TAB, QUO_KEY_TAB);
	quo_insert_input_table(&window->key_map, VK_DELETE, QUO_KEY_DELETE);
	quo_insert_input_table(&window->key_map, VK_HOME, QUO_KEY_HOME);
	quo_insert_input_table(&window->key_map, VK_END, QUO_KEY_END);
	quo_insert_input_table(&window->key_map, VK_PRIOR, QUO_KEY_PAGE_UP);
	quo_insert_input_table(&window->key_map, VK_NEXT, QUO_KEY_PAGE_DOWN);
	quo_insert_input_table(&window->key_map, VK_INSERT, QUO_KEY_INSERT);
	quo_insert_input_table(&window->key_map, VK_SHIFT, QUO_KEY_LEFT_SHIFT);
	quo_insert_input_table(&window->key_map, VK_CONTROL, QUO_KEY_LEFT_CONTROL);
	quo_insert_input_table(&window->key_map, VK_SPACE, QUO_KEY_SPACE);
	quo_insert_input_table(&window->key_map, VK_OEM_PERIOD, QUO_KEY_PERIOD);
	quo_insert_input_table(&window->key_map, VK_OEM_COMMA, QUO_KEY_COMMA);
	quo_insert_input_table(&window->key_map, VK_OEM_3, QUO_KEY_GRAVE_ACCENT);

	/* Number keys */
	quo_insert_input_table(&window->key_map, 0x30, QUO_KEY_0);
	quo_insert_input_table(&window->key_map, 0x31, QUO_KEY_1);
	quo_insert_input_table(&window->key_map, 0x32, QUO_KEY_2);
	quo_insert_input_table(&window->key_map, 0x33, QUO_KEY_3);
	quo_insert_input_table(&window->key_map, 0x34, QUO_KEY_4);
	quo_insert_input_table(&window->key_map, 0x35, QUO_KEY_5);
	quo_insert_input_table(&window->key_map, 0x36, QUO_KEY_6);
	quo_insert_input_table(&window->key_map, 0x37, QUO_KEY_7);
	quo_insert_input_table(&window->key_map, 0x38, QUO_KEY_8);
	quo_insert_input_table(&window->key_map, 0x39, QUO_KEY_9);

	/* Numpad keys */
	quo_insert_input_table(&window->key_map, VK_NUMPAD0, QUO_KEY_NP_0);
	quo_insert_input_table(&window->key_map, VK_NUMPAD1, QUO_KEY_NP_1);
	quo_insert_input_table(&window->key_map, VK_NUMPAD2, QUO_KEY_NP_2);
	quo_insert_input_table(&window->key_map, VK_NUMPAD3, QUO_KEY_NP_3);
	quo_insert_input_table(&window->key_map, VK_NUMPAD4, QUO_KEY_NP_4);
	quo_insert_input_table(&window->key_map, VK_NUMPAD5, QUO_KEY_NP_5);
	quo_insert_input_table(&window->key_map, VK_NUMPAD6, QUO_KEY_NP_6);
	quo_insert_input_table(&window->key_map, VK_NUMPAD7, QUO_KEY_NP_7);
	quo_insert_input_table(&window->key_map, VK_NUMPAD8, QUO_KEY_NP_8);
	quo_insert_input_table(&window->key_map, VK_NUMPAD9, QUO_KEY_NP_9);
	quo_insert_input_table(&window->key_map, VK_MULTIPLY, QUO_KEY_NP_MULTIPLY);
	quo_insert_input_table(&window->key_map, VK_ADD, QUO_KEY_NP_ADD);
	quo_insert_input_table(&window->key_map, VK_DIVIDE, QUO_KEY_NP_DIVIDE);
	quo_insert_input_table(&window->key_map, VK_SUBTRACT, QUO_KEY_NP_SUBTRACT);
	quo_insert_input_table(&window->key_map, VK_DECIMAL, QUO_KEY_NP_DECIMAL);

	quo_insert_input_table(&window->key_map, VK_CAPITAL, QUO_KEY_CAPS_LOCK);
}

/* Swap the window on Windows */
static void quo_update_window_windows(quo_Window* window) {
	SwapBuffers(window->device_context);
}

static void quo_update_window_events_windows(quo_Window* window) {
	/* Poll for events, handled in quo_win32_event_callback */
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

#endif /* QUO_PLATFORM_WINDOWS */

#ifdef QUO_PLATFORM_X11
/* Initialise an X11 window */
static void quo_init_window_x11(quo_Window* window, int w, int h, quo_bool resizable) {
	window->is_focused = true;

	window->display = XOpenDisplay(NULL);
	window->window_root = DefaultRootWindow(window->display);

	/* Configure window */
	int gl_attribs[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	window->visual_info = glXChooseVisual(window->display, 0, gl_attribs);
	window->color_map = XCreateColormap(window->display, window->window_root, window->visual_info->visual, AllocNone);
	window->set_window_attribs.colormap = window->color_map;

	window->set_window_attribs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask | StructureNotifyMask;

	/* Create the window */
	window->window = XCreateWindow(window->display, window->window_root, 0, 0, w, h, 0, window->visual_info->depth, InputOutput, window->visual_info->visual, CWColormap | CWEventMask, &window->set_window_attribs);

	if (!resizable) {
		/* This works by setting the miniumum and maximum heights of the window
		 * to the input width and height. I'm not sure if this is the correct
		 * way to do it, but it works, and even removes the maximise button */
		XSizeHints* hints = XAllocSizeHints();
		hints->flags = PMinSize | PMaxSize;
		hints->min_width = w;
		hints->min_height = h;
		hints->max_width = w;
		hints->max_height = h;

		XSetWMNormalHints(window->display, window->window, hints);

		XFree(hints);
	}

	/* Remap close event */
	Atom atomWmDeleteWindow = XInternAtom(window->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(window->display, window->window, &atomWmDeleteWindow, 1);

	/* Display the window */
	XClearWindow(window->display, window->window);
	XMapRaised(window->display, window->window);

	/* Create OpenGL context */
	{
		static int visual_attribs[] = {
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_DOUBLEBUFFER, true,
			GLX_RED_SIZE,       8,
			GLX_GREEN_SIZE,     8,
			GLX_BLUE_SIZE,      8,
			GLX_ALPHA_SIZE,     8,
			GLX_DEPTH_SIZE,     24,
			GLX_STENCIL_SIZE,   8,
			None
		};

		int num_fbc = 0;
		GLXFBConfig *fbc = glXChooseFBConfig(window->display,  DefaultScreen(window->display), visual_attribs, &num_fbc);
		if (!fbc) {
			printf("glXChooseFBConfig() failed\n");
			exit(1);
		}

		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
		glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

		if (!glXCreateContextAttribsARB) {
			printf("glXCreateContextAttribsARB() not found\n");
			exit(1);
		}

		static int context_attribs[] = {
			GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
			GLX_CONTEXT_MINOR_VERSION_ARB, 3,
			None
		};

		window->device_context = glXCreateContextAttribsARB(window->display, fbc[0], NULL, true, context_attribs);
		glXMakeCurrent(window->display, window->window, window->device_context);
	}

	/* Set width and height */
	XWindowAttributes gwa;
	XGetWindowAttributes(window->display, window->window, &gwa);
	glViewport(0, 0, gwa.width, gwa.height);
	window->width = gwa.width;
	window->height = gwa.height;

	quo_init_input_table(&window->key_map);

	/* Key mapping */
	quo_insert_input_table(&window->key_map, 0x00, QUO_KEY_UNKNOWN);
	quo_insert_input_table(&window->key_map, 0x61, QUO_KEY_A);
	quo_insert_input_table(&window->key_map, 0x62, QUO_KEY_B);
	quo_insert_input_table(&window->key_map, 0x63, QUO_KEY_C);
	quo_insert_input_table(&window->key_map, 0x64, QUO_KEY_D);
	quo_insert_input_table(&window->key_map, 0x65, QUO_KEY_E);
	quo_insert_input_table(&window->key_map, 0x66, QUO_KEY_F);
	quo_insert_input_table(&window->key_map, 0x67, QUO_KEY_G);
	quo_insert_input_table(&window->key_map, 0x68, QUO_KEY_H);
	quo_insert_input_table(&window->key_map, 0x69, QUO_KEY_I);
	quo_insert_input_table(&window->key_map, 0x6A, QUO_KEY_J);
	quo_insert_input_table(&window->key_map, 0x6B, QUO_KEY_K);
	quo_insert_input_table(&window->key_map, 0x6C, QUO_KEY_L);
	quo_insert_input_table(&window->key_map, 0x6D, QUO_KEY_M);
	quo_insert_input_table(&window->key_map, 0x6E, QUO_KEY_N);
	quo_insert_input_table(&window->key_map, 0x6F, QUO_KEY_O);
	quo_insert_input_table(&window->key_map, 0x70, QUO_KEY_P);
	quo_insert_input_table(&window->key_map, 0x71, QUO_KEY_Q);
	quo_insert_input_table(&window->key_map, 0x72, QUO_KEY_R);
	quo_insert_input_table(&window->key_map, 0x73, QUO_KEY_S);
	quo_insert_input_table(&window->key_map, 0x74, QUO_KEY_T);
	quo_insert_input_table(&window->key_map, 0x75, QUO_KEY_U);
	quo_insert_input_table(&window->key_map, 0x76, QUO_KEY_V);
	quo_insert_input_table(&window->key_map, 0x77, QUO_KEY_W);
	quo_insert_input_table(&window->key_map, 0x78, QUO_KEY_X);
	quo_insert_input_table(&window->key_map, 0x79, QUO_KEY_Y);
	quo_insert_input_table(&window->key_map, 0x7A, QUO_KEY_Z);

	/* Function keys */
	quo_insert_input_table(&window->key_map, XK_F1, QUO_KEY_F1);
	quo_insert_input_table(&window->key_map, XK_F2, QUO_KEY_F2);
	quo_insert_input_table(&window->key_map, XK_F3, QUO_KEY_F3);
	quo_insert_input_table(&window->key_map, XK_F4, QUO_KEY_F4);
	quo_insert_input_table(&window->key_map, XK_F5, QUO_KEY_F5);
	quo_insert_input_table(&window->key_map, XK_F6, QUO_KEY_F6);
	quo_insert_input_table(&window->key_map, XK_F7, QUO_KEY_F7);
	quo_insert_input_table(&window->key_map, XK_F8, QUO_KEY_F8);
	quo_insert_input_table(&window->key_map, XK_F9, QUO_KEY_F9);
	quo_insert_input_table(&window->key_map, XK_F10, QUO_KEY_F10);
	quo_insert_input_table(&window->key_map, XK_F11, QUO_KEY_F11);
	quo_insert_input_table(&window->key_map, XK_F12, QUO_KEY_F12);

	/* Navigation */
	quo_insert_input_table(&window->key_map, XK_Down, QUO_KEY_DOWN);
	quo_insert_input_table(&window->key_map, XK_Left, QUO_KEY_LEFT);
	quo_insert_input_table(&window->key_map, XK_Right, QUO_KEY_RIGHT);
	quo_insert_input_table(&window->key_map, XK_Up, QUO_KEY_UP);
	quo_insert_input_table(&window->key_map, XK_Escape, QUO_KEY_ESCAPE);

	/* General navigation & editing */
	quo_insert_input_table(&window->key_map, XK_Escape, QUO_KEY_ESCAPE);
	quo_insert_input_table(&window->key_map, XK_Return, QUO_KEY_ENTER);
	quo_insert_input_table(&window->key_map, XK_BackSpace, QUO_KEY_BACKSPACE);
	quo_insert_input_table(&window->key_map, XK_Linefeed, QUO_KEY_ENTER);
	quo_insert_input_table(&window->key_map, XK_Pause, QUO_KEY_PAUSE);
	quo_insert_input_table(&window->key_map, XK_Scroll_Lock, QUO_KEY_SCROLL_LOCK);
	quo_insert_input_table(&window->key_map, XK_Tab, QUO_KEY_TAB);
	quo_insert_input_table(&window->key_map, XK_Delete, QUO_KEY_DELETE);
	quo_insert_input_table(&window->key_map, XK_Home, QUO_KEY_HOME);
	quo_insert_input_table(&window->key_map, XK_End, QUO_KEY_END);
	quo_insert_input_table(&window->key_map, XK_Page_Up, QUO_KEY_PAGE_UP);
	quo_insert_input_table(&window->key_map, XK_Page_Down, QUO_KEY_PAGE_DOWN);
	quo_insert_input_table(&window->key_map, XK_Insert, QUO_KEY_INSERT);
	quo_insert_input_table(&window->key_map, XK_Shift_L, QUO_KEY_LEFT_SHIFT);
	quo_insert_input_table(&window->key_map, XK_Shift_R, QUO_KEY_RIGHT_SHIFT);
	quo_insert_input_table(&window->key_map, XK_Control_L, QUO_KEY_LEFT_CONTROL);
	quo_insert_input_table(&window->key_map, XK_Control_R, QUO_KEY_RIGHT_CONTROL);
	quo_insert_input_table(&window->key_map, XK_space, QUO_KEY_SPACE);
	quo_insert_input_table(&window->key_map, XK_period, QUO_KEY_PERIOD);

	/* Number keys */
	quo_insert_input_table(&window->key_map, XK_0, QUO_KEY_0);
	quo_insert_input_table(&window->key_map, XK_1, QUO_KEY_1);
	quo_insert_input_table(&window->key_map, XK_2, QUO_KEY_2);
	quo_insert_input_table(&window->key_map, XK_3, QUO_KEY_3);
	quo_insert_input_table(&window->key_map, XK_4, QUO_KEY_4);
	quo_insert_input_table(&window->key_map, XK_5, QUO_KEY_5);
	quo_insert_input_table(&window->key_map, XK_6, QUO_KEY_6);
	quo_insert_input_table(&window->key_map, XK_7, QUO_KEY_7);
	quo_insert_input_table(&window->key_map, XK_8, QUO_KEY_8);
	quo_insert_input_table(&window->key_map, XK_9, QUO_KEY_9);

	/* Numpad keys */
	quo_insert_input_table(&window->key_map, XK_KP_0, QUO_KEY_NP_0);
	quo_insert_input_table(&window->key_map, XK_KP_1, QUO_KEY_NP_1);
	quo_insert_input_table(&window->key_map, XK_KP_2, QUO_KEY_NP_2);
	quo_insert_input_table(&window->key_map, XK_KP_3, QUO_KEY_NP_3);
	quo_insert_input_table(&window->key_map, XK_KP_4, QUO_KEY_NP_4);
	quo_insert_input_table(&window->key_map, XK_KP_5, QUO_KEY_NP_5);
	quo_insert_input_table(&window->key_map, XK_KP_6, QUO_KEY_NP_6);
	quo_insert_input_table(&window->key_map, XK_KP_7, QUO_KEY_NP_7);
	quo_insert_input_table(&window->key_map, XK_KP_8, QUO_KEY_NP_8);
	quo_insert_input_table(&window->key_map, XK_KP_9, QUO_KEY_NP_9);
	quo_insert_input_table(&window->key_map, XK_KP_Multiply, QUO_KEY_NP_MULTIPLY);
	quo_insert_input_table(&window->key_map, XK_KP_Add, QUO_KEY_NP_ADD);
	quo_insert_input_table(&window->key_map, XK_KP_Divide, QUO_KEY_NP_DIVIDE);
	quo_insert_input_table(&window->key_map, XK_KP_Subtract, QUO_KEY_NP_SUBTRACT);
	quo_insert_input_table(&window->key_map, XK_KP_Decimal, QUO_KEY_NP_DECIMAL);

	quo_insert_input_table(&window->key_map, XK_Caps_Lock, QUO_KEY_CAPS_LOCK);
}

static void quo_update_window_x11(quo_Window* window) {
	/* Swap window */
	glXSwapBuffers(window->display, window->window);
}

static void quo_update_window_events_x11(quo_Window* window) {
	/* Handle events */
	XEvent e;
	while (XPending(window->display)) {
		XNextEvent(window->display, &e);

		if (e.type == ClientMessage) {
			window->is_open = false;
		} else if (e.type == Expose) {
			XWindowAttributes gwa;
			XGetWindowAttributes(window->display, window->window, &gwa);
			glViewport(0, 0, gwa.width, gwa.height);

			window->width = gwa.width;
			window->height = gwa.height;
		} else if (e.type == KeyPress) {
			if (window->is_focused) {
				/* Set the necessary inputs */
				KeySym sym = XLookupKeysym(&e.xkey, 0);

				int key = quo_search_input_table(&window->key_map, sym);
				i_quo_set_key_held_state(key, true);
				i_quo_set_key_down_state(key, true);

				/* Get the input string and call the string event callback */
				char buffer[16];
				XLookupString(&e.xkey, buffer, 16, NULL, NULL);
				if (strlen(buffer) > 0) {
					i_quo_call_char_callback(buffer);
				}
			}
		} else if (e.type == KeyRelease) {
			if (window->is_focused) {
				KeySym sym = XLookupKeysym(&e.xkey, 0);

				int key = quo_search_input_table(&window->key_map, sym);
				i_quo_set_key_held_state(key, false);
				i_quo_set_key_up_state(key, true);
			}
		} else if (e.type == FocusIn) {
			window->is_focused = true;
		} else if (e.type == FocusOut) {
			window->is_focused = false;
		} else if (e.type == ButtonPress) {
			switch (e.xbutton.button) {
				case 1:
					i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_1, true);
					i_quo_set_mouse_button_down_state(QUO_MOUSE_BUTTON_1, true);
					break;
				case 2:
					i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_2, true);
					i_quo_set_mouse_button_down_state(QUO_MOUSE_BUTTON_2, true);
					break;
				case 3:
					i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_3, true);
					i_quo_set_mouse_button_down_state(QUO_MOUSE_BUTTON_3, true);
					break;
				default:
					break;
			}
		} else if (e.type == ButtonRelease) {
			switch (e.xbutton.button) {
				case 1:
					i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_1, false);
					i_quo_set_mouse_button_up_state(QUO_MOUSE_BUTTON_1, true);
					break;
				case 2:
					i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_2, false);
					i_quo_set_mouse_button_up_state(QUO_MOUSE_BUTTON_2, true);
					break;
				case 3:
					i_quo_set_mouse_button_held_state(QUO_MOUSE_BUTTON_3, false);
					i_quo_set_mouse_button_up_state(QUO_MOUSE_BUTTON_3, true);
					break;
				default:
					break;
			}
		} else if (e.type == MotionNotify) {
			i_quo_update_mouse_pos(e.xmotion.x, e.xmotion.y);
		}
	}
}

#endif /* QUO_PLATFORM_X11 */

/* Single wrapper around system calls */
void quo_init_window(quo_Window* window, int w, int h, quo_bool resizable) {
	assert(window != NULL);

	/* Initialise window properties */
	window->is_open = true;
	window->frame_time = 0;
	window->now_time = 0;
	window->old_time = 0;
	window->resizable = resizable;

#if defined(QUO_PLATFORM_X11)
	quo_init_window_x11(window, w, h, resizable);
#endif

#if defined(QUO_PLATFORM_WINDOWS)
	quo_init_window_windows(window, w, h, resizable);
#endif

	/* Sort the input table for binary searching */
	quo_prepare_input_table(&window->key_map);

	/* Load OpenGL functions */
	quo_load_gl();

	/* Initialise the input system */
	quo_init_input_system();
}

void quo_set_window_title(quo_Window* window, const char* title) {
	assert(window != NULL);

#if defined(QUO_PLATFORM_WINDOWS)
	wchar_t wchar_title[1024];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, title, -1, wchar_title, 1024);

	SetWindowText(window->hwnd, wchar_title);
#endif

#if defined(QUO_PLATFORM_X11)
	XStoreName(window->display, window->window, title);
#endif
}

void quo_update_window(quo_Window* window) {
	assert(window != NULL);

#if defined(QUO_PLATFORM_X11)
	quo_update_window_x11(window);
#endif

#if defined(QUO_PLATFORM_WINDOWS)
	quo_update_window_windows(window);
#endif

	/* Update the timing and fps counter */
	window->now_time = quo_get_elapsed_time();
	window->frame_time = window->now_time - window->old_time;
	window->old_time = window->now_time;

	window->fps = 1000.0 / window->frame_time;

	/* Update the input system */
	quo_update_input_system();
}

void quo_update_window_events(quo_Window* window) {
	assert(window != NULL);

#if defined(QUO_PLATFORM_X11)
	quo_update_window_events_x11(window);
#endif

#if defined(QUO_PLATFORM_WINDOWS)
	quo_update_window_events_windows(window);
#endif
}

void quo_free_window(quo_Window* window) {
	assert(window != NULL);

#if defined(QUO_PLATFORM_X11)
	/* Destroy the OpenGL context */
	glXDestroyContext(window->display, window->device_context);

	XFreeColormap(window->display, window->color_map);

	XDestroyWindow(window->display, window->window);
	XCloseDisplay(window->display);
#endif


#if defined(QUO_PLATFORM_WINDOWS)
	/* I'm not sure why the window has to be destroyed before the
	 * context, it would make sense for it to be the other way around...
	 * But it segfaulted when I swapped the order, so this must
	 * correct, right? */
	PostQuitMessage(0);
	DestroyWindow(window->hwnd);
	wglDeleteContext(window->render_context);
#endif
}
/* -----------------------
 * END WINDOW
 * -----------------------*/

/* -----------------------
 * START MATHS
 * -----------------------*/
quo_vec2 quo_add_vec2(quo_vec2 a, quo_vec2 b) {
	return (quo_vec2){a.x + b.x, a.y + b.y};
}

quo_vec2 quo_subtract_vec2(quo_vec2 a, quo_vec2 b) {
	return (quo_vec2){a.x - b.x, a.y - b.y};
}

quo_vec2 quo_multiply_vec2(quo_vec2 a, quo_vec2 b) {
	return (quo_vec2){a.x * b.x, a.y * b.y};
}

quo_vec2 quo_divide_vec2(quo_vec2 a, quo_vec2 b) {
	return (quo_vec2){a.x / b.x, a.y / b.y};
}

float quo_vec2_magnitude(quo_vec2 v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

float quo_dot_vec2(quo_vec2 a, quo_vec2 b) {
	return a.x * b.x + a.y * b.y;
}

quo_vec2 quo_normalise_vec2(quo_vec2 v) {
	float length = quo_vec2_magnitude(v);
	return (quo_vec2){v.x / length, v.y / length};
}

quo_vec3 quo_add_vec3(quo_vec3 a, quo_vec3 b) {
	return (quo_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

quo_vec3 quo_subtract_vec3(quo_vec3 a, quo_vec3 b) {
	return (quo_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

quo_vec3 quo_multiply_vec3(quo_vec3 a, quo_vec3 b) {
	return (quo_vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

quo_vec3 quo_divide_vec3(quo_vec3 a, quo_vec3 b) {
	return (quo_vec3){a.x / b.x, a.y / b.y, a.z / b.z};
}

float quo_vec3_magnitude(quo_vec3 v) {
	sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float quo_dot_vec3(quo_vec3 a, quo_vec3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

quo_vec3 quo_normalise_vec3(quo_vec3 v) {
	float length = quo_vec3_magnitude(v);
	return (quo_vec3){v.x / length, v.y / length, v.z / length};
}

quo_vec3 quo_cross_vec3(quo_vec3 a, quo_vec3 b) {
	return (quo_vec3){a.y * b.z - a.z * b.y,
					  a.z * b.x - a.x * b.z,
					  a.x * b.y - a.y * b.x};
}

quo_Matrix quo_identity() {
	quo_Matrix result;

	memset(result.elements, 0, 16 * sizeof(float));

	result.elements[0 + 0 * 4] = 1.0f;
	result.elements[1 + 1 * 4] = 1.0f;
	result.elements[2 + 2 * 4] = 1.0f;
	result.elements[3 + 3 * 4] = 1.0f;

	return result;
}

quo_Matrix quo_translate(quo_Matrix m, quo_vec3 translation) {
	m.elements[3 + 0 * 4] = translation.x;
	m.elements[3 + 1 * 4] = translation.y;
	m.elements[3 + 2 * 4] = translation.z;

	return m;
}

quo_Matrix quo_rotate(quo_Matrix m, float angle, quo_vec3 axis) {
	float r = quo_to_radians(angle);
	float c = cos(r);
	float s = sin(r);
	float omc = 1.0f - c;

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	m.elements[0 + 0 * 4] = x * x * omc + c;
	m.elements[0 + 1 * 4] = y * x * omc + z * s;
	m.elements[0 + 2 * 4] = x * z * omc - y * s;

	m.elements[1 + 0 * 4] = x * y * omc - z * s;
	m.elements[1 + 1 * 4] = y * y * omc + c;
	m.elements[1 + 2 * 4] = y * z * omc + x * s;

	m.elements[2 + 0 * 4] = x * z * omc + y * s;
	m.elements[2 + 1 * 4] = y * z * omc - x * s;
	m.elements[2 + 2 * 4] = z * z * omc + c;

	return m;
}

quo_Matrix quo_scale(quo_Matrix m, quo_vec3 scale) {
	m.elements[0 + 0 * 4] = scale.x;
	m.elements[1 + 1 * 4] = scale.y;
	m.elements[2 + 2 * 4] = scale.z;

	return m;
}

quo_Matrix quo_orthographic(float left, float right, float bottom, float top, float near_plane, float far_plane) {
	quo_Matrix result = quo_identity();

	result.elements[0 + 0 * 4] = 2.0f / (right - left);
	result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result.elements[2 + 2 * 4] = 2.0f / (near_plane - far_plane);

	result.elements[3 + 0 * 4] = (left + right) / (left - right);
	result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
	result.elements[3 + 2 * 4] = (far_plane + near_plane) / (far_plane - near_plane);

	return result;
}

quo_Matrix quo_perspective(float fov, float aspect, float near_plane, float far_plane) {
	quo_Matrix result = quo_identity();

	float q = 1.0f / tan(quo_to_radians(0.5f * fov));
	float a = q / aspect;

	float b = (near_plane + far_plane) / (near_plane - far_plane);
	float c = (2.0f * near_plane * far_plane) / (near_plane - far_plane);

	result.elements[0 + 0 * 4] = a;
	result.elements[1 + 1 * 4] = q;
	result.elements[2 + 2 * 4] = b;
	result.elements[2 + 3 * 4] = -1.0f;
	result.elements[3 + 2 * 4] = c;

	return result;
}

/* -----------------------
 * END MATHS
 * -----------------------*/

 /* -----------------------
  * START RENDERER
  * -----------------------*/

#define LOADBMP_RGB  3
#define LOADBMP_RGBA 4

quo_bool quo_load_bitmap_from_file(const char* filename, quo_BitmapImage* image, unsigned int components) {
	assert(image != NULL);
	assert(filename != NULL);

/* Load the bitmap image from a .bmp file */
#ifndef QUO_USE_STB_IMAGE

	FILE *f = fopen(filename, "rb");

	if (!f) {
		printf("%s not found\n", filename);
		return false;
	}

	unsigned char bmp_file_header[14];
	unsigned char bmp_info_header[40];
	unsigned char bmp_pad[3];

	unsigned int w, h;
	unsigned char *data = NULL;

	unsigned int x, y, i, padding;

	memset(bmp_file_header, 0, sizeof(bmp_file_header));
	memset(bmp_info_header, 0, sizeof(bmp_info_header));

	if (fread(bmp_file_header, sizeof(bmp_file_header), 1, f) == 0) {
		fclose(f);
		printf("%s not a valid bmp file\n", filename);
		return false;
	}

	if (fread(bmp_info_header, sizeof(bmp_info_header), 1, f) == 0) {
		fclose(f);
		printf("%s not a valid bmp file\n", filename);
		return false;
	}

	if ((bmp_file_header[0] != 'B') || (bmp_file_header[1] != 'M')) {
		fclose(f);
		printf("%s has an invalid signature\n", filename);
		return false;
	}

	if ((bmp_info_header[14] != 24) && (bmp_info_header[14] != 32)) {
		fclose(f);
		printf("%s has invalid bits-per-pixel data\n", filename);
		return false;
	}

	w = (bmp_info_header[4] + (bmp_info_header[5] << 8) + (bmp_info_header[6] << 16) + (bmp_info_header[7] << 24));
	h = (bmp_info_header[8] + (bmp_info_header[9] << 8) + (bmp_info_header[10] << 16) + (bmp_info_header[11] << 24));

	if ((w > 0) && (h > 0)) {
		data = (unsigned char*)malloc(w * h * components);

		if (!data) {
			fclose(f);
			printf("Not enough memory to load %s\n", filename);
			return false;
		}

		for (y = (h - 1); y != -1; y--) {
			for (x = 0; x < w; x++) {
				i = (x + y * w) * components;

				if (fread(data + i, 3, 1, f) == 0) {
					free(data);

					fclose(f);
					printf("%s not a valid bmp file\n", filename);
					return false;
				}

				data[i] ^= data[i + 2] ^= data[i] ^= data[i + 2]; // BGR -> RGB

				if (components == LOADBMP_RGBA) {
					data[i + 3] = 255;
				}
			}

			padding = ((4 - (w * 3) % 4) % 4);

			if (fread(bmp_pad, 1, padding, f) != padding) {
				free(data);

				printf("%s not a valid bmp file\n", filename);
				return false;
			}
		}
	}

	image->width = w;
	image->height = h;
	image->pixels = data;
	image->component_count = 3;

	fclose(f);

#else

	/* If STB support is enabled, we can use stb's loader in order to laod
	 * many other image formats, not just .bmp images */

	image->pixels = (unsigned char*)stbi_load(filename, &image->width, &image->height, &image->component_count, components);

#endif

	return true;
}

void quo_free_bitmap(quo_BitmapImage* image) {
	assert(image != NULL);

	if (image->pixels) {
		free(image->pixels);
	}

	image->width = 0;
	image->height = 0;
}


void quo_init_texture_from_bmp(quo_Texture* texture, quo_BitmapImage* bitmap, quo_TextureFlags flags) {
	assert(texture != NULL);
	assert(bitmap != NULL);

	if (bitmap->pixels == NULL) {
		return;
	}

	/* Setup initial texture data */
	texture->width = bitmap->width;
	texture->height = bitmap->height;

	/* Create the OpenGL texture */
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	/* Choose the alias mode */
	int alias_mode;
	if (flags & QUO_TEXTUREFLAGS_ALIASED) {
		alias_mode = GL_NEAREST;
	} else if (flags & QUO_TEXTUREFLAGS_ANTIALIASED) {
		alias_mode = GL_LINEAR;
	}

	/* Configure the texture */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, alias_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, alias_mode);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* Choose the pixel mode */
	int mode = GL_RGB;
	if (bitmap->component_count == 4) {
		mode = GL_RGBA;
	} else if (bitmap->component_count == 0) {
		mode = GL_ALPHA;
	}

	/* Push the data onto the GPU */
	glTexImage2D(GL_TEXTURE_2D, 0, mode, texture->width, texture->height, 0, mode, GL_UNSIGNED_BYTE, bitmap->pixels);
}

void quo_free_texture(quo_Texture* texture) {
	assert(texture != NULL);

	texture->width = 0;
	texture->height = 0;

	glDeleteTextures(1, &texture->id);
}

void quo_bind_texture(quo_Texture* texture, unsigned int unit) {
	assert(texture != NULL);

	/* This causes a segfault if the texture hasn't been initialised
	 * properly, eg. if the bitmap data was null and the init function
	 * returned immediately. Too bad. */

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture->id);
}

void quo_unbind_texture() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

/* Legacy shaders. Doesn't work on some Windows AMD drivers */
#if defined(QUO_LEGACY_SHADERS) || defined(QUO_LEGACY)
static const char* g_quad_shader_vertex = "#version 130\n"
"attribute vec2 vertex;\n"

"uniform mat4 projection = mat4(1.0);\n"
"uniform mat4 model = mat4(1.0);\n"
"uniform mat4 view = mat4(1.0);\n"
"out vec2 uv;\n"

"uniform vec2 image_size;\n"
"uniform vec4 source_rect;\n"

"void main() {\n"
"vec2 texPos = vertex.zw;\n"
    "float widthPixel = 1.0f / image_size.x;\n"
    "float heightPixel = 1.0f / image_size.y;\n"

    "float startX = source_rect.x, startY = source_rect.y, width = source_rect.z, height = source_rect.w;\n"

    "uv = vec2(widthPixel * startX + width * widthPixel * texPos.x, heightPixel * startY + height * heightPixel * texPos.y);\n"

    "gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);\n"
"}\n";

static const char* g_quad_shader_fragment = "#version 130\n"
"out vec4 out_color;\n"

"in vec2 uv;\n"

"uniform vec3 color = vec3(1.0);\n"
"uniform vec3 background_color = vec3(1.0, 0.0, 1.0);\n"
"uniform sampler2D tex;\n"
"uniform bool use_tex = false;\n"

"void main() {\n"
    "vec4 tex_color = vec4(1.0f);"
    "if (use_tex) {\n"
        "tex_color = texture(tex, uv);\n"
    "}\n"

    "if (tex_color.xyz == background_color){\n"
        "discard;\n"
    "}\n"

    "out_color = tex_color * vec4(color, 1.0);\n"
"}\n";
#else
/* Modern shaders. Should work on all platforms that support GLSL 3.3+ */
static const char* g_quad_shader_vertex = "#version 330 core\n"
"layout (location = 0) in vec4 vertex;\n"

"uniform mat4 projection = mat4(1.0);\n"
"uniform mat4 model = mat4(1.0);\n"
"uniform mat4 view = mat4(1.0);\n"
"out vec2 uv;\n"

"uniform vec2 image_size;\n"
"uniform vec4 source_rect;\n"

"void main() {\n"
"vec2 texPos = vertex.zw;\n"
	"float widthPixel = 1.0f / image_size.x;\n"
	"float heightPixel = 1.0f / image_size.y;\n"

	"float startX = source_rect.x, startY = source_rect.y, width = source_rect.z, height = source_rect.w;\n"

	"uv = vec2(widthPixel * startX + width * widthPixel * texPos.x, heightPixel * startY + height * heightPixel * texPos.y);\n"

	"gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);\n"
"}\n";

static const char* g_quad_shader_fragment = "#version 330 core\n"
"out vec4 out_color;\n"

"in vec2 uv;\n"

"uniform vec3 color = vec3(1.0);\n"
"uniform vec3 background_color = vec3(1.0, 0.0, 1.0);\n"
"uniform sampler2D tex;\n"
"uniform bool use_tex = false;\n"

"void main() {\n"
	"vec4 tex_color = vec4(1.0f);"
	"if (use_tex) {\n"
		"tex_color = texture(tex, uv);\n"
	"}\n"

	"if (tex_color.xyz == background_color || tex_color.a < 0.1){\n"
		"discard;\n"
	"}\n"

	"out_color = tex_color * vec4(color, 1.0);\n"
"}\n";
#endif

static void check_shader_errors(unsigned int shader) {
	int r;
	char info_log[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &r);
	if (!r) {
		/* Get and print out the error message */
		glGetShaderInfoLog(shader, 1024, 0, info_log);
		fprintf(stderr, "Shader error %s\n", info_log);
	}
}

unsigned long quo_color_from_rgb(int r, int g, int b) {
	/* Some bitshifing magic */
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void quo_init_renderer(quo_Renderer* renderer, quo_Window* window) {
	assert(renderer != NULL);
	assert(window != NULL);

	renderer->shader_count = 0;
	renderer->window = window;

	/* By default, the background colour will be
	 * bright pink (RGB: {255, 0, 255}) */
	renderer->background_color = 0xff00ff;

	for (unsigned int i = 0; i < QUO_MAX_SHADERS; i++) {
		renderer->shaders[i] = 0;
	}

	/* Create the projection matrix */
	renderer->projection = quo_orthographic(0.0f, window->width, window->height, 0.0f, -1.0f, 1.0f);

	/* Create the default sprite shader */
	renderer->sprite_shader = quo_create_shader(renderer, g_quad_shader_vertex, g_quad_shader_fragment);

	/* Quad vertices. */
	float verts[] = {
		/* position     UV */
		1.0, 1.0, 	1.0f, 1.0f,
		1.0, 0.0, 	1.0f, 0.0f,
		0.0, 0.0, 	0.0f, 0.0f,
		0.0, 1.0, 	0.0f, 1.0f
	};

	/* Quad indices */
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	/* Create the vertex buffer for the quad */
	quo_begin_vertex_buffer(&renderer->quad,
		QUO_VERTEXBUFFERFLAGS_STATIC_DRAW |
		QUO_VERTEXBUFFERFLAGS_DRAW_TRIANGLES);

	quo_push_vertices(&renderer->quad, verts, sizeof(verts));
	quo_push_indices(&renderer->quad, indices, sizeof(indices)/sizeof(indices[0]));

	quo_configure_vertices(&renderer->quad, 0, 4, 4, 0);

	quo_finalise_vertex_buffer(&renderer->quad);

	quo_bind_shader(renderer, renderer->sprite_shader);
}

void quo_enable_3d() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void quo_update_renderer(quo_Renderer* renderer) {
	assert(renderer != NULL);
	assert(renderer->window != NULL);

	/* Only recalculate the projection if the window can be resized. */
	if (renderer->window->resizable) {
		renderer->projection = quo_orthographic(0.0f, renderer->window->width, renderer->window->height, 0.0f, -1.0f, 1.0f);
	}
}

void quo_draw_rect(quo_Renderer* renderer, quo_Rect rect, unsigned long color) {
	assert(renderer != NULL);

	/* Setup the transform. */
	quo_Matrix model = quo_identity();
	model = quo_translate(model, (quo_vec3){rect.x, rect.y, 0});
	model = quo_scale(model, (quo_vec3){rect.w, rect.h, 1});

	/* Set shader uniforms */
	quo_shader_set_matrix(renderer, renderer->sprite_shader, "model", model);
	quo_shader_set_matrix(renderer, renderer->sprite_shader, "projection", renderer->projection);
	quo_shader_set_color(renderer, renderer->sprite_shader, "color", color);
	quo_shader_set_int(renderer, renderer->sprite_shader, "use_tex", 0);

	/* Draw the quad */
	quo_draw_vertex_buffer(&renderer->quad);
}

void quo_draw_texture(quo_Renderer* renderer, quo_Texture* texture, quo_Rect src, quo_Rect dest, unsigned long color) {
	assert(renderer != NULL);
	assert(texture != NULL);

	/* Setup the transform. */
	quo_Matrix model = quo_identity();
	model = quo_translate(model, (quo_vec3){dest.x, dest.y, 0});
	model = quo_scale(model, (quo_vec3){dest.w, dest.h, 1});

	/* Set shader uniforms */
	quo_shader_set_matrix(renderer, renderer->sprite_shader, "model", model);
	quo_shader_set_matrix(renderer, renderer->sprite_shader, "projection", renderer->projection);
	quo_shader_set_color(renderer, renderer->sprite_shader, "color", color);
	quo_shader_set_color(renderer, renderer->sprite_shader, "background_color", renderer->background_color);
	quo_shader_set_int(renderer, renderer->sprite_shader, "use_tex", 1);
	quo_shader_set_vec2(renderer, renderer->sprite_shader, "image_size", (quo_vec2){texture->width, texture->height});
	quo_shader_set_vec4(renderer, renderer->sprite_shader, "source_rect", src.x, src.y, src.w, src.h);

	/* Bind and set uniform texture */
	quo_bind_texture(texture, 0);
	quo_shader_set_int(renderer, renderer->sprite_shader, "tex", 0);

	/* Draw the quad */
	quo_draw_vertex_buffer(&renderer->quad);
}

void quo_free_renderer(quo_Renderer* renderer) {
	assert(renderer != NULL);

	/* Delete all the shaders */
	for (unsigned int i = 0; i < renderer->shader_count; i++) {
		glDeleteProgram(&renderer->shaders[i]);
	}

	/* Delete the vertex array & buffer */
	quo_free_vertex_buffer(&renderer->quad);
}

void quo_clear_renderer(unsigned long color) {
	/* Grab the 0-255 rgb colours */
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;

	/* Turn them into 0-1 range rgb colours */
	float rf = (float)r / 255.0f;
	float gf = (float)g / 255.0f;
	float bf = (float)b / 255.0f;

	/* Clear the screen */
	glClearColor(rf, gf, bf, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

quo_ShaderHandle quo_create_shader(quo_Renderer* renderer, const char* vertex_source, const char* fragment_source) {
	assert(renderer != NULL);

	/* Make sure this shader is allowed */
	if (renderer->shader_count > QUO_MAX_SHADERS) {
		fprintf(stderr, "Failed to create shader: Shader count too high (max %d)\n", QUO_MAX_SHADERS);
		return 0;
	}

	unsigned int program = glCreateProgram();

	/* Create the vertex shader */
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCompileShader(vertex_shader);
	check_shader_errors(vertex_shader);

	/* Create the fragment shader */
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCompileShader(fragment_shader);
	check_shader_errors(fragment_shader);

	/* Link the program */
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	/* Delete the shaders */
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	/* Push back the shader into the renderer's shader array */
	unsigned int index = renderer->shader_count++;
	renderer->shaders[index] = program;

	return index;
}

void quo_bind_shader(quo_Renderer* renderer, quo_ShaderHandle shader) {
	assert(renderer != NULL);

	glUseProgram(renderer->shaders[shader]);
}


void quo_bind_default_shader(quo_Renderer* renderer) {
	assert(renderer != NULL);

	quo_bind_shader(renderer, renderer->sprite_shader);
}

void quo_shader_set_color(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, unsigned long color) {
	/* Grab the 0-255 rgb colours */
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;

	/* Turn them into 0-1 range rgb colours */
	float rf = (float)r / 255.0f;
	float gf = (float)g / 255.0f;
	float bf = (float)b / 255.0f;

	/* Set the uniform colour vec3 */
	quo_shader_set_vec3(renderer, shader, uniform_name, (quo_vec3){rf, gf, bf});
}

void quo_shader_set_float(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, float val) {
	assert(renderer != NULL);
	assert(shader < renderer->shader_count);

	unsigned int shader_id = renderer->shaders[shader];
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);

	glUniform1f(location, val);
}

void quo_shader_set_int(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, int val) {
	assert(renderer != NULL);
	assert(shader < renderer->shader_count);

	unsigned int shader_id = renderer->shaders[shader];
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);

	glUniform1i(location, val);
}

void quo_shader_set_matrix(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, quo_Matrix m) {
	assert(renderer != NULL);
	assert(shader < renderer->shader_count);

	unsigned int shader_id = renderer->shaders[shader];
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);

	glUniformMatrix4fv(location, 1, true, m.elements);
}

void quo_shader_set_vec2(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, quo_vec2 val) {
	assert(renderer != NULL);
	assert(shader < renderer->shader_count);

	unsigned int shader_id = renderer->shaders[shader];
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);

	glUniform2f(location, val.x, val.y);
}

void quo_shader_set_vec3(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, quo_vec3 val) {
	assert(renderer != NULL);
	assert(shader < renderer->shader_count);

	unsigned int shader_id = renderer->shaders[shader];
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);

	glUniform3f(location, val.x, val.y, val.z);
}

void quo_shader_set_vec4(quo_Renderer* renderer, quo_ShaderHandle shader, const char* uniform_name, float x, float y, float z, float w) {
	assert(renderer != NULL);
	assert(shader < renderer->shader_count);

	unsigned int shader_id = renderer->shaders[shader];
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);

	glUniform4f(location, x, y, z, w);
}

void quo_begin_vertex_buffer(quo_VertexBuffer* vb, quo_VertexBufferFlags flags) {
	assert(vb != NULL);

	vb->flags = flags;

	/* Create the vertex array and vertex & element buffers */
	glGenVertexArrays(1, &vb->va_id);
	glGenBuffers(1, &vb->vb_id);
	glGenBuffers(1, &vb->ib_id);
}

void quo_finalise_vertex_buffer(quo_VertexBuffer* vb) {
	assert(vb != NULL);

	glBindVertexArray(0);
}

void quo_push_vertices(quo_VertexBuffer* vb, float* vertices, unsigned int array_size) {
	assert(vb != NULL);

	int mode = GL_STATIC_DRAW;
	if (vb->flags & QUO_VERTEXBUFFERFLAGS_DYNAMIC_DRAW) {
		mode = GL_DYNAMIC_DRAW;
	}

	/* Make sure the vertex array and buffer are bound */
	glBindVertexArray(vb->va_id);
	glBindBuffer(GL_ARRAY_BUFFER, vb->vb_id);

	/* Push the data into the buffer */
	glBufferData(GL_ARRAY_BUFFER, array_size, vertices, mode);
}

void quo_push_indices(quo_VertexBuffer* vb, unsigned int* indices, unsigned int index_count) {
	assert(vb != NULL);

	int mode = GL_STATIC_DRAW;
	if (vb->flags & QUO_VERTEXBUFFERFLAGS_DYNAMIC_DRAW) {
		mode = GL_DYNAMIC_DRAW;
	}

	/* Make sure the vertex array and buffer are bound */
	glBindVertexArray(vb->va_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vb->ib_id);

	/* Push the data into the buffer */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(indices[0]), indices, mode);

	/* Set the index count used for drawing */
	vb->index_count = index_count;
}

void quo_update_vertices(quo_VertexBuffer* vb, float* vertices, unsigned int array_size) {
	assert(vb != NULL);

	glBindVertexArray(vb->va_id);
	glBindBuffer(GL_ARRAY_BUFFER, vb->vb_id);

	glBufferSubData(GL_ARRAY_BUFFER, 0, array_size, vertices);
}

void quo_update_indices(quo_VertexBuffer* vb, unsigned int* indices, unsigned int index_count) {
	assert(vb != NULL);

	glBindVertexArray(vb->va_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vb->ib_id);

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
	index_count * sizeof(indices[0]), indices);

	vb->index_count = index_count;
}

void quo_configure_vertices(quo_VertexBuffer* vb, unsigned int index, unsigned int component_count, unsigned int stride, unsigned int start_offset) {
	assert(vb != NULL);

	/* Make sure the vertex array is bound */
	glBindVertexArray(vb->va_id);

	/* Setup the attrib pointer */
	glVertexAttribPointer(index, component_count, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(long unsigned int)start_offset);
	glEnableVertexAttribArray(index);
}

void quo_draw_vertex_buffer(quo_VertexBuffer* vb) {
	assert(vb != NULL);

	int draw_type = GL_TRIANGLES;
	if (vb->flags & QUO_VERTEXBUFFERFLAGS_DRAW_LINES) {
		draw_type = GL_LINES;
	} else if (vb->flags & QUO_VERTEXBUFFERFLAGS_DRAW_LINE_STRIP) {
		draw_type = GL_LINE_STRIP;
	}

	/* Draw the vertex array */
	glBindVertexArray(vb->va_id);
	glDrawElements(draw_type, vb->index_count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

static unsigned int i_g_quo_old_frame_buffer_width = 0;
static unsigned int i_g_quo_old_frame_buffer_height = 0;

void quo_free_vertex_buffer(quo_VertexBuffer* vb) {
	glDeleteVertexArrays(1, &vb->va_id);
	glDeleteBuffers(1, &vb->vb_id);
	glDeleteBuffers(1, &vb->ib_id);
}

void quo_init_render_target(quo_RenderTarget* target, int width, int height) {
	assert(target != NULL);

	target->output.width = width;
	target->output.height = height;

	/* Initialise a new framebuffer, renderbuffer and output texture */
	glGenFramebuffers(1, &target->frame_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, target->frame_buffer);

	glGenTextures(1, &target->output.id);
	glBindTexture(GL_TEXTURE_2D, target->output.id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, target->output.id, 0);

	glGenRenderbuffers(1, &target->render_buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, target->render_buffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, target->render_buffer);
}

void quo_free_render_target(quo_RenderTarget* target) {
	assert(target != NULL);

	quo_free_texture(&target->output);
	glDeleteRenderbuffers(1, &target->render_buffer);
	glDeleteFramebuffers(1, &target->frame_buffer);
}

void quo_bind_render_target(quo_RenderTarget* target) {
	assert(target != NULL);

	/* Get the current viewport, so we can reset it
	 * once the framebuffer is unbound without having
	 * to pass a window pointer. */
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	i_g_quo_old_frame_buffer_width = viewport[2];
	i_g_quo_old_frame_buffer_height = viewport[3];

	/* Bind and clear the framebuffer */
	glBindFramebuffer(GL_FRAMEBUFFER, target->frame_buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, target->render_buffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, target->output.width, target->output.height);
}

void quo_bind_default_render_target() {
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/* Reset the viewport */
	glViewport(0, 0, i_g_quo_old_frame_buffer_width, i_g_quo_old_frame_buffer_height);
}

void quo_resize_render_target(quo_RenderTarget* target, int width, int height) {
	assert(target != NULL);

	target->output.width = width;
	target->output.height = height;

	/* Resize the framebuffer's output texture */
	glBindFramebuffer(GL_FRAMEBUFFER, target->frame_buffer);
	glBindTexture(GL_TEXTURE_2D, target->output.id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glBindRenderbuffer(GL_RENDERBUFFER, target->render_buffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, target->render_buffer);

	quo_bind_default_render_target();
}

/* -----------------------
 * END RENDERER
 * -----------------------*/

/* -----------------------
 * START INPUT
 * -----------------------*/

/* Static quo_InputSystem */
static quo_InputSystem input_system;

void quo_init_input_system() {
	memset(input_system.held_keys, 0, QUO_KEY_COUNT * sizeof(quo_bool));
	memset(input_system.held_mouse_buttons, 0, QUO_MOUSE_BUTTON_COUNT * sizeof(quo_bool));

	input_system.char_callback = NULL;
}

void quo_update_input_system() {
	memset(input_system.down_keys, 0, QUO_KEY_COUNT * sizeof(quo_bool));
	memset(input_system.up_keys, 0, QUO_KEY_COUNT * sizeof(quo_bool));
	memset(input_system.down_mouse_buttons, 0, QUO_MOUSE_BUTTON_COUNT * sizeof(quo_bool));
	memset(input_system.up_mouse_buttons, 0, QUO_MOUSE_BUTTON_COUNT * sizeof(quo_bool));
}

void quo_set_character_callback(quo_character_callback callback) {
	input_system.char_callback = callback;
}

quo_bool quo_key_pressed(int key) {
	return input_system.held_keys[key];
}

quo_bool quo_key_just_pressed(int key) {
	return input_system.down_keys[key];
}

quo_bool quo_key_just_released(int key) {
	return input_system.up_keys[key];
}

quo_bool quo_mouse_button_pressed(int button) {
	return input_system.held_mouse_buttons[button];
}

quo_bool quo_mouse_button_just_pressed(int button) {
	return input_system.down_mouse_buttons[button];
}

quo_bool quo_mouse_button_just_released(int button) {
	return input_system.up_mouse_buttons[button];
}

void i_quo_set_key_held_state(int key, quo_bool status) {
	input_system.held_keys[key] = status;
}

void i_quo_set_key_down_state(int key, quo_bool status) {
	input_system.down_keys[key] = status;
}

void i_quo_set_key_up_state(int key, quo_bool status) {
	input_system.up_keys[key] = status;
}

void i_quo_set_mouse_button_held_state(int button, quo_bool status) {
	input_system.held_mouse_buttons[button] = status;
}

void i_quo_set_mouse_button_down_state(int button, quo_bool status) {
	input_system.down_mouse_buttons[button] = status;
}

void i_quo_set_mouse_button_up_state(int button, quo_bool status) {
	input_system.up_mouse_buttons[button] = status;
}

void i_quo_update_mouse_pos(int x, int y) {
	input_system.mouse_x = x;
	input_system.mouse_y = y;
}

void i_quo_call_char_callback(char* characters) {
	if (input_system.char_callback != NULL) {
		input_system.char_callback(characters);
	}
}

int quo_get_mouse_x() { return input_system.mouse_x; }
int quo_get_mouse_y() { return input_system.mouse_y; }

/* -----------------------
 * END INPUT
 * -----------------------*/

/* -----------------------
 * START SERIALISATION
 * -----------------------*/

void quo_init_byte_buffer(quo_ByteBuffer* buffer) {
	assert(buffer != NULL);

	/* Set the byte buffer's initial data */
	buffer->data = malloc(QUO_BYTE_BUFFER_DEFAULT_CAPACITY);
	memset(buffer->data, 0, QUO_BYTE_BUFFER_DEFAULT_CAPACITY);
	buffer->capacity = QUO_BYTE_BUFFER_DEFAULT_CAPACITY;
	buffer->size = 0;
	buffer->position = 0;
}

void quo_free_byte_buffer(quo_ByteBuffer* buffer) {
	assert(buffer != NULL);

	free(buffer->data);

	buffer->capacity = 0;
	buffer->size = 0;
	buffer->position = 0;
}

void quo_resize_byte_buffer(quo_ByteBuffer* buffer, unsigned int capacity) {
	/* Reallocate a byte buffer in order to contain more or less data */
	buffer->data = realloc(buffer->data, capacity);
	buffer->capacity = capacity;
}

void quo_byte_buffer_dump(quo_ByteBuffer* buffer, FILE* file) {
	assert(buffer != NULL);
	assert(file != NULL);

	/* Write the header data (size and capacity) to the file */
	fwrite(&buffer->size, 1, sizeof(uint32_t), file);
	fwrite(&buffer->capacity, 1, sizeof(uint32_t), file);

	/* Write the main data */
	fwrite(buffer->data, 1, buffer->size, file);
}

void quo_byte_buffer_read_file(quo_ByteBuffer* buffer, FILE* file) {
	assert(buffer != NULL);
	assert(file != NULL);

	/* Read the header data (size and capacity) */
	fread(&buffer->size, sizeof(uint32_t), 1, file);
	fread(&buffer->capacity, sizeof(uint32_t), 1, file);

	/* Allocate the buffer's data. Realloc is used to avoid
	 * a memory leak when using a pre-initialised byte buffer */
	buffer->data = realloc(buffer->data, buffer->capacity);
	memset(buffer->data, 0, buffer->capacity);

	/* Read the body of the data */
	fread(buffer->data, buffer->size, 1, file);

	buffer->position = 0;
}

void i_quo_byte_buffer_write_impl(quo_ByteBuffer* buffer, void* data, unsigned int size) {
	/* Resize the buffer if required. */
	unsigned int total_write_size = buffer->position + size;
	if (total_write_size >= buffer->capacity) {
		unsigned int new_capacity = buffer->capacity ? buffer->capacity * 2 : QUO_BYTE_BUFFER_DEFAULT_CAPACITY;
		while (new_capacity < total_write_size) {
			new_capacity *= 2;
		}
		quo_resize_byte_buffer(buffer, new_capacity);
	}

	/* Copy the data into the buffer */
	memcpy(buffer->data + buffer->position, data, size);

	/* Increment position and size */
	buffer->position += size;
	buffer->size += size;
}

/* -----------------------
 * END SERIALISATION
 * -----------------------*/


#endif /* DOXYGEN_IGNORE */
#endif /* QUO_IMPL */

#ifdef __cplusplus
}
#endif
