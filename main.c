/*
 * Copyright (c) 2011-2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <screen/screen.h>
#include <bps/navigator.h>
#include <bps/screen.h>
#include <bps/bps.h>
#include <bps/event.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include "bbutil.h"

#include <sys/keycodes.h>

#include <math.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


static float width, height;
static GLuint latar;
static GLfloat latar_vertices[8];
static GLfloat latar_tex_coord[8];

static GLuint logo;
static GLfloat logo_vertices[8];
static GLfloat logo_tex_coord[8];

static GLuint latar_username, latar_password;
static GLfloat latar_username_vertices[8], latar_password_vertices[8];
static GLfloat latar_username_tex_coord[8], latar_password_tex_coord[8];

static GLuint tombol_login;
static GLfloat tombol_login_vertices[8];
static GLfloat tombol_login_tex_coord[8];

static GLuint latar_ihsg, latar_ihsg_nilai, latar_ihsg_volume;
static GLfloat latar_ihsg_vertices[8], latar_ihsg_nilai_vertices[8], latar_ihsg_volume_vertices[8];
static GLfloat latar_ihsg_tex_coord[8], latar_ihsg_nilai_tex_coord[8], latar_ihsg_volume_tex_coord[8];

static GLuint latar_tanggal;
static GLfloat latar_tanggal_vertices[8];
static GLfloat latar_tanggal_tex_coord[8];

static GLuint info, setel;
static GLfloat info_vertices[8],setel_vertices[8];
static GLfloat info_tex_coord[8], setel_tex_coord[8];

static GLfloat *background_vertices, *background_texcoord;


static GLfloat vertices[8];
static GLfloat tex_coord[8];

static screen_context_t screen_cxt;
static float pos_x, pos_y;

static font_t* font;

static int current_window;


void handleScreenEvent(bps_event_t *event) {
    screen_event_t screen_event = screen_event_get_event(event);

    int screen_val;
    screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_TYPE,
            &screen_val);

    switch (screen_val) {
    case SCREEN_EVENT_MTOUCH_TOUCH:
    case SCREEN_EVENT_MTOUCH_MOVE:
    case SCREEN_EVENT_MTOUCH_RELEASE:
        break;
    }
}

int initialize() {

    //Query width and height of the window surface created by utility code
    EGLint surface_width, surface_height;

    eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
    eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

    EGLint err = eglGetError();
    if (err != 0x3000) {
        fprintf(stderr, "Unable to query EGL surface dimensions\n");
        return EXIT_FAILURE;
    }

    width = (float) surface_width;
	height = (float) surface_height;

	float tex_x = 1.0f, tex_y = 1.0f;
	int size_x, size_y;

	//Load background texture

	if (EXIT_SUCCESS
			!= bbutil_load_texture("app/native/assets/latar.png",
					NULL, NULL, &tex_x, &tex_y, &latar)) {
		fprintf(stderr, "Unable to load background texture\n");
	}
	//Setup background polygon
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	vertices[2] = width;
	vertices[3] = 0.0f;
	vertices[4] = 0.0f;
	vertices[5] = height;
	vertices[6] = width;
	vertices[7] = height;

	tex_coord[0] = 0.0f;
	tex_coord[1] = 0.0f;
	tex_coord[2] = tex_x;
	tex_coord[3] = 0.0f;
	tex_coord[4] = 0.0f;
	tex_coord[5] = tex_y;
	tex_coord[6] = tex_x;
	tex_coord[7] = tex_y;

	size_x = 347; size_y = 430;
	//size_x = 60; size_y = 60;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/logo.png",
				NULL, NULL, &tex_x, &tex_y, &logo))
	{
		fprintf(stderr, "Unable to load logo texture\n");;
	}

	logo_vertices[0] = 0.0f;
	logo_vertices[1] = 0.0f;
	logo_vertices[2] = size_x;
	logo_vertices[3] = 0.0f;
	logo_vertices[4] = 0.0f;
	logo_vertices[5] = size_y;
	logo_vertices[6] = size_x;
	logo_vertices[7] = size_y;

	logo_tex_coord[0] = 0.0f;
	logo_tex_coord[1] = 0.0f;
	logo_tex_coord[2] = tex_x;
	logo_tex_coord[3] = 0.0f;
	logo_tex_coord[4] = 0.0f;
	logo_tex_coord[5] = tex_y;
	logo_tex_coord[6] = tex_x;
	logo_tex_coord[7] = tex_y;

	size_x = 579; size_y = 70;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/kotak_username.png",
				NULL, NULL, &tex_x, &tex_y, &latar_username))
	{
		fprintf(stderr, "Unable to load latar_username texture\n");;
	}

	latar_username_vertices[0] = 0.0f;
	latar_username_vertices[1] = 0.0f;
	latar_username_vertices[2] = size_x;
	latar_username_vertices[3] = 0.0f;
	latar_username_vertices[4] = 0.0f;
	latar_username_vertices[5] = size_y;
	latar_username_vertices[6] = size_x;
	latar_username_vertices[7] = size_y;

	latar_username_tex_coord[0] = 0.0f;
	latar_username_tex_coord[1] = 0.0f;
	latar_username_tex_coord[2] = tex_x;
	latar_username_tex_coord[3] = 0.0f;
	latar_username_tex_coord[4] = 0.0f;
	latar_username_tex_coord[5] = tex_y;
	latar_username_tex_coord[6] = tex_x;
	latar_username_tex_coord[7] = tex_y;

	size_x = 579; size_y = 70;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/kotak_password.png",
				NULL, NULL, &tex_x, &tex_y, &latar_password))
	{
		fprintf(stderr, "Unable to load latar_password texture\n");;
	}

	latar_password_vertices[0] = 0.0f;
	latar_password_vertices[1] = 0.0f;
	latar_password_vertices[2] = size_x;
	latar_password_vertices[3] = 0.0f;
	latar_password_vertices[4] = 0.0f;
	latar_password_vertices[5] = size_y;
	latar_password_vertices[6] = size_x;
	latar_password_vertices[7] = size_y;

	latar_password_tex_coord[0] = 0.0f;
	latar_password_tex_coord[1] = 0.0f;
	latar_password_tex_coord[2] = tex_x;
	latar_password_tex_coord[3] = 0.0f;
	latar_password_tex_coord[4] = 0.0f;
	latar_password_tex_coord[5] = tex_y;
	latar_password_tex_coord[6] = tex_x;
	latar_password_tex_coord[7] = tex_y;

	size_x = 179; size_y = 83;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/btn_login.png",
				NULL, NULL, &tex_x, &tex_y, &tombol_login))
	{
		fprintf(stderr, "Unable to load btn_login texture\n");;
	}

	tombol_login_vertices[0] = 0.0f;
	tombol_login_vertices[1] = 0.0f;
	tombol_login_vertices[2] = size_x;
	tombol_login_vertices[3] = 0.0f;
	tombol_login_vertices[4] = 0.0f;
	tombol_login_vertices[5] = size_y;
	tombol_login_vertices[6] = size_x;
	tombol_login_vertices[7] = size_y;

	tombol_login_tex_coord[0] = 0.0f;
	tombol_login_tex_coord[1] = 0.0f;
	tombol_login_tex_coord[2] = tex_x;
	tombol_login_tex_coord[3] = 0.0f;
	tombol_login_tex_coord[4] = 0.0f;
	tombol_login_tex_coord[5] = tex_y;
	tombol_login_tex_coord[6] = tex_x;
	tombol_login_tex_coord[7] = tex_y;

	size_x = 786; size_y = 56;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/pita_kuning.png",
				NULL, NULL, &tex_x, &tex_y, &latar_ihsg))
	{
		fprintf(stderr, "Unable to load pita_kuning texture\n");;
	}

	latar_ihsg_vertices[0] = 0.0f;
	latar_ihsg_vertices[1] = 0.0f;
	latar_ihsg_vertices[2] = size_x;
	latar_ihsg_vertices[3] = 0.0f;
	latar_ihsg_vertices[4] = 0.0f;
	latar_ihsg_vertices[5] = size_y;
	latar_ihsg_vertices[6] = size_x;
	latar_ihsg_vertices[7] = size_y;

	latar_ihsg_tex_coord[0] = 0.0f;
	latar_ihsg_tex_coord[1] = 0.0f;
	latar_ihsg_tex_coord[2] = tex_x;
	latar_ihsg_tex_coord[3] = 0.0f;
	latar_ihsg_tex_coord[4] = 0.0f;
	latar_ihsg_tex_coord[5] = tex_y;
	latar_ihsg_tex_coord[6] = tex_x;
	latar_ihsg_tex_coord[7] = tex_y;

	size_x = 403; size_y = 109;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/latar_ihsg.png",
				NULL, NULL, &tex_x, &tex_y, &latar_ihsg_nilai))
	{
		fprintf(stderr, "Unable to load latar_ihsg texture\n");;
	}

	latar_ihsg_nilai_vertices[0] = 0.0f;
	latar_ihsg_nilai_vertices[1] = 0.0f;
	latar_ihsg_nilai_vertices[2] = size_x;
	latar_ihsg_nilai_vertices[3] = 0.0f;
	latar_ihsg_nilai_vertices[4] = 0.0f;
	latar_ihsg_nilai_vertices[5] = size_y;
	latar_ihsg_nilai_vertices[6] = size_x;
	latar_ihsg_nilai_vertices[7] = size_y;

	latar_ihsg_nilai_tex_coord[0] = 0.0f;
	latar_ihsg_nilai_tex_coord[1] = 0.0f;
	latar_ihsg_nilai_tex_coord[2] = tex_x;
	latar_ihsg_nilai_tex_coord[3] = 0.0f;
	latar_ihsg_nilai_tex_coord[4] = 0.0f;
	latar_ihsg_nilai_tex_coord[5] = tex_y;
	latar_ihsg_nilai_tex_coord[6] = tex_x;
	latar_ihsg_nilai_tex_coord[7] = tex_y;

	size_x = 446; size_y = 105;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/latar_ihsg_nilai.png",
				NULL, NULL, &tex_x, &tex_y, &latar_ihsg_volume))
	{
		fprintf(stderr, "Unable to load latar_ihsg_nilai texture\n");;
	}

	latar_ihsg_volume_vertices[0] = 0.0f;
	latar_ihsg_volume_vertices[1] = 0.0f;
	latar_ihsg_volume_vertices[2] = size_x;
	latar_ihsg_volume_vertices[3] = 0.0f;
	latar_ihsg_volume_vertices[4] = 0.0f;
	latar_ihsg_volume_vertices[5] = size_y;
	latar_ihsg_volume_vertices[6] = size_x;
	latar_ihsg_volume_vertices[7] = size_y;

	latar_ihsg_volume_tex_coord[0] = 0.0f;
	latar_ihsg_volume_tex_coord[1] = 0.0f;
	latar_ihsg_volume_tex_coord[2] = tex_x;
	latar_ihsg_volume_tex_coord[3] = 0.0f;
	latar_ihsg_volume_tex_coord[4] = 0.0f;
	latar_ihsg_volume_tex_coord[5] = tex_y;
	latar_ihsg_volume_tex_coord[6] = tex_x;
	latar_ihsg_volume_tex_coord[7] = tex_y;

	size_x = 616; size_y = 110;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/latar_tanggal.png",
				NULL, NULL, &tex_x, &tex_y, &latar_tanggal))
	{
		fprintf(stderr, "Unable to load latar_tanggal texture\n");;
	}

	latar_tanggal_vertices[0] = 0.0f;
	latar_tanggal_vertices[1] = 0.0f;
	latar_tanggal_vertices[2] = size_x;
	latar_tanggal_vertices[3] = 0.0f;
	latar_tanggal_vertices[4] = 0.0f;
	latar_tanggal_vertices[5] = size_y;
	latar_tanggal_vertices[6] = size_x;
	latar_tanggal_vertices[7] = size_y;

	latar_tanggal_tex_coord[0] = 0.0f;
	latar_tanggal_tex_coord[1] = 0.0f;
	latar_tanggal_tex_coord[2] = tex_x;
	latar_tanggal_tex_coord[3] = 0.0f;
	latar_tanggal_tex_coord[4] = 0.0f;
	latar_tanggal_tex_coord[5] = tex_y;
	latar_tanggal_tex_coord[6] = tex_x;
	latar_tanggal_tex_coord[7] = tex_y;

	size_x = 51; size_y = 50;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/info.png",
				NULL, NULL, &tex_x, &tex_y, &info))
	{
		fprintf(stderr, "Unable to load info texture\n");;
	}

	info_vertices[0] = 0.0f;
	info_vertices[1] = 0.0f;
	info_vertices[2] = size_x;
	info_vertices[3] = 0.0f;
	info_vertices[4] = 0.0f;
	info_vertices[5] = size_y;
	info_vertices[6] = size_x;
	info_vertices[7] = size_y;

	info_tex_coord[0] = 0.0f;
	info_tex_coord[1] = 0.0f;
	info_tex_coord[2] = tex_x;
	info_tex_coord[3] = 0.0f;
	info_tex_coord[4] = 0.0f;
	info_tex_coord[5] = tex_y;
	info_tex_coord[6] = tex_x;
	info_tex_coord[7] = tex_y;

	size_x = 51; size_y = 50;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/setel.png",
				NULL, NULL, &tex_x, &tex_y, &setel))
	{
		fprintf(stderr, "Unable to load setel texture\n");;
	}

	setel_vertices[0] = 0.0f;
	setel_vertices[1] = 0.0f;
	setel_vertices[2] = size_x;
	setel_vertices[3] = 0.0f;
	setel_vertices[4] = 0.0f;
	setel_vertices[5] = size_y;
	setel_vertices[6] = size_x;
	setel_vertices[7] = size_y;

	setel_tex_coord[0] = 0.0f;
	setel_tex_coord[1] = 0.0f;
	setel_tex_coord[2] = tex_x;
	setel_tex_coord[3] = 0.0f;
	setel_tex_coord[4] = 0.0f;
	setel_tex_coord[5] = tex_y;
	setel_tex_coord[6] = tex_x;
	setel_tex_coord[7] = tex_y;

	int dpi = bbutil_calculate_dpi(screen_cxt);

	//As bbutil renders text using device-specifc dpi, we need to compute a point size
	//for the font, so that the text string fits into the bubble. Note that Playbook is used
	//as a reference point in this equation as we know that at dpi of 170, font with point size of
	//15 fits into the bubble texture.
	float stretch_factor = (float)surface_width / (float)size_x;
	int point_size = (int)(15.0f * stretch_factor / ((float)dpi / 170.0f ));

	font = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);

	if (!font) {
		return EXIT_FAILURE;
	}


	//Initialize GL for 2D rendering
	glViewport(0, 0, (int) width, (int) height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrthof(0.0f, width / height, 0.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Set world coordinates to coincide with screen pixels
	glScalef(1.0f / height, 1.0f / height, 1.0f);

	float text_width, text_height;
	bbutil_measure_text(font, "Hello world", &text_width, &text_height);
	pos_x = (width - text_width) / 2;
	pos_y = height / 2;

	/*
	glBindTexture(GL_TEXTURE_2D, logo);
	glTranslatef(190.0f, 60.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, latar_username);
	glTranslatef(72.0f, 542.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, latar_password);
	glTranslatef(72.0f, 605.0f, 0.0f);

	//glVertexPointer(2, GL_FLOAT, 0, tombol_login_vertices);
	//glTexCoordPointer(2, GL_FLOAT, 0, tombol_login_tex_coord);
	glBindTexture(GL_TEXTURE_2D, tombol_login);
	glTranslatef(300.0f, 600.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, latar_ihsg);
	glTranslatef(0.0f, 810.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, latar_ihsg_nilai);
	glTranslatef(180.0f, 893.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, latar_ihsg_volume);
	glTranslatef(168.0f, 970.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, latar_tanggal);
	glTranslatef(72.0f, 1067.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, info);
	glTranslatef(300.0f, 1180.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, setel);
	glTranslatef(390.0f, 1180.0f, 0.0f);
	*/

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

    return EXIT_SUCCESS;
}

void enable_2d()
{
    glViewport(0, 0, (int) width, (int) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrthof(0.0f, width / height, 0.0f, 1.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(1.0f / height, 1.0f / height, 1.0f);
}

void render() {
	//Typical rendering pass
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, logo_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, logo_tex_coord);
	glTranslatef(190.0f, height -60.0f -430, 0.0f);
	glBindTexture(GL_TEXTURE_2D, logo);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_username_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_username_tex_coord);
	glTranslatef(-120.0f, -100.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, latar_username);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_password_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_password_tex_coord);
	glTranslatef(0.0f, -62.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, latar_password);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, tombol_login_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, tombol_login_tex_coord);
	glTranslatef(223.0f, -82.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, tombol_login);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_ihsg_tex_coord);
	glTranslatef(-300.0f, -104.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, latar_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_ihsg_nilai_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_ihsg_nilai_tex_coord);
	glTranslatef(180.0f, -120.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, latar_ihsg_nilai);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_ihsg_volume_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_ihsg_volume_tex_coord);
	glTranslatef(-25.0f, -52.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, latar_ihsg_volume);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_tanggal_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tanggal_tex_coord);
	glTranslatef(-90.0f, -140.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, latar_tanggal);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_tex_coord);
	glTranslatef(236.0f, -80.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, info);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, setel_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, setel_tex_coord);
	glTranslatef(100.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, setel);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	//Use utility code to render welcome text onto the screen
	bbutil_render_text(font, "", pos_x, pos_y, 0.35f, 0.35f, 0.35f, 1.0f);

	//Use utility code to update the screen
	bbutil_swap();
}

int main(int argc, char *argv[]) {
    int exit_application = 0;
    //static screen_context_t screen_cxt;

    //Create a screen context that will be used to create an EGL surface to to receive libscreen events
    screen_create_context(&screen_cxt, 0);

    //Initialize BPS library
    bps_initialize();

    //Use utility code to initialize EGL for rendering with GL ES 1.1
    if (EXIT_SUCCESS != bbutil_init_egl(screen_cxt)) {
        fprintf(stderr, "bbutil_init_egl failed\n");
        bbutil_terminate();
        screen_destroy_context(screen_cxt);
        return 0;
    }

    //Initialize application logic
    if (EXIT_SUCCESS != initialize()) {
        fprintf(stderr, "initialize failed\n");
        bbutil_terminate();
        screen_destroy_context(screen_cxt);
        return 0;
    }

    //Signal BPS library that navigator and screen events will be requested
    if (BPS_SUCCESS != screen_request_events(screen_cxt)) {
        fprintf(stderr, "screen_request_events failed\n");
        bbutil_terminate();
        screen_destroy_context(screen_cxt);
        return 0;
    }

    if (BPS_SUCCESS != navigator_request_events(0)) {
        fprintf(stderr, "navigator_request_events failed\n");
        bbutil_terminate();
        screen_destroy_context(screen_cxt);
        return 0;
    }

    //Signal BPS library that navigator orientation is not to be locked
    if (BPS_SUCCESS != navigator_rotation_lock(false)) {
        fprintf(stderr, "navigator_rotation_lock failed\n");
        bbutil_terminate();
        screen_destroy_context(screen_cxt);
        return 0;
    }

    while (!exit_application) {
        //Request and process all available BPS events
        bps_event_t *event = NULL;

        for(;;) {
            if (BPS_SUCCESS != bps_get_event(&event, 0)) {
                fprintf(stderr, "bps_get_event failed\n");
                break;
            }

            if (event) {
                int domain = bps_event_get_domain(event);

                if (domain == screen_get_domain()) {
                    handleScreenEvent(event);
                } else if ((domain == navigator_get_domain())
                        && (NAVIGATOR_EXIT == bps_event_get_code(event))) {
                    exit_application = 1;
                }
            } else {
                break;
            }
        }
        render();
    }

    //Stop requesting events from libscreen
    screen_stop_events(screen_cxt);

    //Shut down BPS library for this process
    bps_shutdown();

    //Use utility code to terminate EGL setup
    bbutil_terminate();

    //Destroy libscreen context
    screen_destroy_context(screen_cxt);
    return 0;
}
