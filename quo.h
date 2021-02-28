#pragma once

/* Standard includes */
#include <stdbool.h>

/* Windows */
#if defined(_WIN32)
#error Windows is not supported yet
#endif

/* X11 */
#if defined(__linux__) || defined(__FreeBSD__)
#define QUO_PLATFORM_X11
#endif

/* Platform-specific includes */
#if defined(QUO_PLATFORM_X11)
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#endif

/* Platform-specific aliases & macros */
#if defined(QUO_PLATFORM_X11)
typedef GLXContext quo_GLDeviceContext;
typedef GLXContext quo_GLRenderContext;

#define CALLSTYLE
#define QUO_LOAD_GL_FUNC(t, n) (t*)glXGetProcAddress((unsigned char*)n);
#endif

/* GL load types */
typedef unsigned int CALLSTYLE quo_gl_create_program();
typedef unsigned int CALLSTYLE quo_gl_create_shader(unsigned int);
typedef void CALLSTYLE quo_gl_attach_shader(unsigned int, unsigned int);
typedef void CALLSTYLE quo_gl_bind_buffer(unsigned int, int);
typedef void CALLSTYLE quo_gl_bind_vertex_array(unsigned int);
typedef void CALLSTYLE quo_gl_buffer_data(unsigned int, int, const void*, unsigned int);
typedef void CALLSTYLE quo_gl_compile_shader(unsigned int);
typedef void CALLSTYLE quo_gl_delete_shader(unsigned int);
typedef void CALLSTYLE quo_gl_enable_vertex_attrib_array(unsigned int);
typedef void CALLSTYLE quo_gl_gen_buffers(unsigned int, unsigned int*);
typedef void CALLSTYLE quo_gl_gen_vertex_arrays(unsigned int, unsigned int*);
typedef void CALLSTYLE quo_gl_get_program_info_log(unsigned int, int, int, char*);
typedef void CALLSTYLE quo_gl_get_program_iv(unsigned int, unsigned int, int*);
typedef void CALLSTYLE quo_gl_get_shader_info_log(unsigned int, int, int, char*);
typedef void CALLSTYLE quo_gl_get_shader_iv(unsigned int, unsigned int, int*);
typedef void CALLSTYLE quo_gl_link_program(unsigned int);
typedef void CALLSTYLE quo_gl_shader_source(unsigned int, int, const char**, const int*);
typedef void CALLSTYLE quo_gl_use_program(unsigned int);
typedef void CALLSTYLE quo_gl_vertex_attrib_pointer(unsigned int, int, unsigned int, GLboolean, int, const void*);

/* OpenGL functions */
quo_gl_attach_shader* glAttachShader = NULL;
quo_gl_bind_buffer* glBindBuffer = NULL;
quo_gl_bind_vertex_array* glBindVertexArray = NULL;
quo_gl_buffer_data* glBufferData = NULL;
quo_gl_compile_shader* glCompileShader = NULL;
quo_gl_create_program* glCreateProgram = NULL;
quo_gl_create_shader* glCreateShader = NULL;
quo_gl_delete_shader* glDeleteShader = NULL;
quo_gl_enable_vertex_attrib_array* glEnableVertexAttribArray = NULL;
quo_gl_gen_buffers* glGenBuffers = NULL;
quo_gl_gen_vertex_arrays* glGenVertexArrays = NULL;
quo_gl_get_program_info_log* glGetProgramInfoLog = NULL;
quo_gl_get_program_iv* glGetProgramiv = NULL;
quo_gl_get_shader_info_log* glGetShaderInfoLog = NULL;
quo_gl_get_shader_iv* glGetShaderiv = NULL;
quo_gl_link_program* glLinkProgram = NULL;
quo_gl_shader_source* glShaderSource = NULL;
quo_gl_use_program* glUseProgram = NULL;
quo_gl_vertex_attrib_pointer* glVertexAttribPointer = NULL;

/* Load all OpenGL functions */
void quo_load_gl();

/* -----------------------
 * START WINDOW
 * -----------------------*/

/* Window struct */
typedef struct quo_Window {
	quo_GLDeviceContext device_context;
	quo_GLRenderContext render_context;

	bool is_open;
	int width, height;

#if defined(QUO_PLATFORM_X11)
	Display* display;
	Window window_root;
	Window window;
	XVisualInfo* visual_info;
	Colormap color_map;
	XSetWindowAttributes set_window_attribs;
#endif
} quo_Window;

void quo_init_window(quo_Window* window, int w, int h);
void quo_clear_window(quo_Window* window, int r, int g, int b);
void quo_update_window(quo_Window* window);
void quo_free_window(quo_Window* window);
/* -----------------------
 * END WINDOW
 * -----------------------*/

 /* -----------------------
 * START RENDERER
 * -----------------------*/

typedef struct quo_Renderer {
} quo_Renderer;

 /* -----------------------
 * END RENDERER
 * -----------------------*/

/* Implementation */
#ifdef QUO_IMPL
/* C standard includes */
#include <assert.h>
#include <stdio.h>
#include <string.h>

void quo_load_gl() {
	glAttachShader = QUO_LOAD_GL_FUNC(quo_gl_attach_shader, "glAttachShader");
	glBindBuffer = QUO_LOAD_GL_FUNC(quo_gl_bind_buffer, "glBindBuffer");
	glBindVertexArray = QUO_LOAD_GL_FUNC(quo_gl_bind_vertex_array, "glBindVertexArray");
	glBufferData = QUO_LOAD_GL_FUNC(quo_gl_buffer_data, "glBufferData");
	glCompileShader = QUO_LOAD_GL_FUNC(quo_gl_compile_shader, "glCompileShader");
	glCreateProgram = QUO_LOAD_GL_FUNC(quo_gl_create_program, "glCreateProgram");
	glCreateShader = QUO_LOAD_GL_FUNC(quo_gl_create_shader, "glCreateShader");
	glDeleteShader = QUO_LOAD_GL_FUNC(quo_gl_delete_shader, "glDeleteShader");
	glEnableVertexAttribArray = QUO_LOAD_GL_FUNC(quo_gl_enable_vertex_attrib_array, "glEnableVertexAttribArray");
	glGenBuffers = QUO_LOAD_GL_FUNC(quo_gl_gen_buffers, "glGenBuffers");
	glGenVertexArrays = QUO_LOAD_GL_FUNC(quo_gl_gen_vertex_arrays, "glGenVertexArrays");
	glGetProgramInfoLog = QUO_LOAD_GL_FUNC(quo_gl_get_program_info_log, "glGetProgramInfoLog");
	glGetProgramiv = QUO_LOAD_GL_FUNC(quo_gl_get_program_iv, "glGetProgramiv");
	glGetShaderInfoLog = QUO_LOAD_GL_FUNC(quo_gl_get_shader_info_log, "glGetShaderInfoLog");
	glGetShaderiv = QUO_LOAD_GL_FUNC(quo_gl_get_shader_iv, "glGetShaderiv");
	glLinkProgram = QUO_LOAD_GL_FUNC(quo_gl_link_program, "glLinkProgram");
	glShaderSource = QUO_LOAD_GL_FUNC(quo_gl_shader_source, "glShaderSource");
	glUseProgram = QUO_LOAD_GL_FUNC(quo_gl_use_program, "glUseProgram");
	glVertexAttribPointer = QUO_LOAD_GL_FUNC(quo_gl_vertex_attrib_pointer, "glVertexAttribPointer");
}

/* -----------------------
 * START WINDOW
 * -----------------------*/

void quo_init_window(quo_Window* window, int w, int h) {
	assert(window != NULL);

	window->is_open = true;

#if defined(QUO_PLATFORM_X11)
	window->display = XOpenDisplay(NULL);
	window->window_root = DefaultRootWindow(window->display);

	/* Configure window */
	int gl_attribs[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	window->visual_info = glXChooseVisual(window->display, 0, gl_attribs);
	window->color_map = XCreateColormap(window->display, window->window_root, window->visual_info->visual, AllocNone);
	window->set_window_attribs.colormap = window->color_map;

	/* Let X11 know which events we are interested in */
	window->set_window_attribs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask | StructureNotifyMask;

	/* Create the window */
	window->window = XCreateWindow(window->display, window->window_root, 0, 0, w, h, 0, window->visual_info->depth, InputOutput, window->visual_info->visual, CWColormap | CWEventMask, &window->set_window_attribs);

	/* Remap close event */
	Atom atomWmDeleteWindow = XInternAtom(window->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(window->display, window->window, &atomWmDeleteWindow, 1);

	/* Display the window */
	XClearWindow(window->display, window->window);
	XMapRaised(window->display, window->window);

	/* Create OpenGL context */
	window->device_context = glXCreateContext(window->display, window->visual_info, NULL, GL_TRUE);
	glXMakeCurrent(window->display, window->window, window->device_context);

	XWindowAttributes gwa;
	XGetWindowAttributes(window->display, window->window, &gwa);
	glViewport(0, 0, gwa.width, gwa.height);

	window->width = gwa.width;
	window->height = gwa.height;
#endif

	quo_load_gl();
}

void quo_clear_window(quo_Window* window, int r, int g, int b) {
	assert(window != NULL);

	float rf = (float)r / 255.0f;
	float gf = (float)g / 255.0f;
	float bf = (float)b / 255.0f;

	glClearColor(rf, gf, bf, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void quo_update_window(quo_Window* window) {
	assert(window != NULL);

#if defined(QUO_PLATFORM_X11)
	/* Swap window */
	glXSwapBuffers(window->display, window->window);

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
		}
	}
#endif
}

void quo_free_window(quo_Window* window) {
	assert(window != NULL);

#if defined(QUO_PLATFORM_X11)
	glXDestroyContext(window->display, window->device_context);

	XFreeColormap(window->display, window->color_map);

	XDestroyWindow(window->display, window->window);
	XCloseDisplay(window->display);
#endif
}
/* -----------------------
 * END WINDOW
 * -----------------------*/

 /* -----------------------
 * START RENDERER
 * -----------------------*/

 /* -----------------------
 * END RENDERER
 * -----------------------*/

#endif