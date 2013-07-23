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
static float lebar_layar, tinggi_layar;
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

static GLuint brokerquote_bar, brokerquote_caption;
static GLfloat brokerquote_bar_vertices[8], brokerquote_caption_vertices[8];
static GLfloat brokerquote_bar_tex_coord[8], brokerquote_caption_tex_coord[8];

static GLuint buyaction_bg, buyaction_execute, buyaction_caption, buyaction_refresh, buyaction_table, buyaction_whitebar;
static GLfloat buyaction_bg_vertices[8], buyaction_execute_vertices[8], buyaction_caption_vertices[8], buyaction_refresh_vertices[8], buyaction_table_vertices[8], buyaction_whitebar_vertices[8];
static GLfloat buyaction_bg_tex_coord[8], buyaction_execute_tex_coord[8], buyaction_caption_tex_coord[8], buyaction_refresh_tex_coord[8], buyaction_table_tex_coord[8], buyaction_whitebar_tex_coord[8];

static GLuint bartulisan, bar2, bg2, bottom_bar, search, big_1day, big_1week, big_1month, big_1year, big_3year, small_1day, small_1week, small_1month, small_1year, small_3year;
static GLfloat bartulisan_vertices[8], bar2_vertices[8], bg2_vertices[8], bottom_bar_vertices[8], search_vertices[8], big_1day_vertices[8], big_1week_vertices[8], big_1month_vertices[8], big_1year_vertices[8], big_3year_vertices[8], small_1day_vertices[8], small_1week_vertices[8], small_1month_vertices[8], small_1year_vertices[8], small_3year_vertices[8];
static GLfloat bartulisan_tex_coord[8], bar2_tex_coord[8], bg2_tex_coord[8], bottom_bar_tex_coord[8], search_tex_coord[8], big_1day_tex_coord[8], big_1week_tex_coord[8], big_1month_tex_coord[8], big_1year_tex_coord[8], big_3year_tex_coord[8], small_1day_tex_coord[8], small_1week_tex_coord[8], small_1month_tex_coord[8], small_1year_tex_coord[8], small_3year_tex_coord[8];

static GLuint companies, financial_small, ratio_small;
static GLfloat companies_vertices[8], financial_small_vertices[8], ratio_small_vertices[8];
static GLfloat companies_tex_coord[8], financial_small_tex_coord[8], ratio_small_tex_coord[8];

static GLuint completebook_bar1, completebook_bar2, completebook_bar3, completebook_caption;
static GLfloat completebook_bar1_vertices[8], completebook_bar2_vertices[8], completebook_bar3_vertices[8], completebook_caption_vertices[8];
static GLfloat completebook_bar1_tex_coord[8], completebook_bar2_tex_coord[8], completebook_bar3_tex_coord[8], completebook_caption_tex_coord[8];

static GLuint ca_bar, ca_caption, ca_bonus1, ca_bonus2, ca_dividen1, ca_dividen2, ca_rights1, ca_rights2, ca_rups1, ca_rups2, ca_split1, ca_split2, ca_warrant1, ca_warrant2;
static GLfloat ca_bar_vertices[8], ca_caption_vertices[8], ca_bonus1_vertices[8], ca_bonus2_vertices[8], ca_dividen1_vertices[8], ca_dividen2_vertices[8], ca_rights1_vertices[8], ca_rights2_vertices[8], ca_rups1_vertices[8], ca_rups2_vertices[8], ca_split1_vertices[8], ca_split2_vertices[8], ca_warrant1_vertices[8], ca_warrant2_vertices[8];
static GLfloat ca_bar_tex_coord[8], ca_caption_tex_coord[8], ca_bonus1_tex_coord[8], ca_bonus2_tex_coord[8], ca_dividen1_tex_coord[8], ca_dividen2_tex_coord[8], ca_rights1_tex_coord[8], ca_rights2_tex_coord[8], ca_rups1_tex_coord[8], ca_rups2_tex_coord[8], ca_split1_tex_coord[8], ca_split2_tex_coord[8], ca_warrant1_tex_coord[8], ca_warrant2_tex_coord[8];

static GLuint box_account_number, drop_bg, drop_tradingcentral, panah_atas, icon_chart, icon_info, icon_logout, icon_myaccount, icon_portfolio, icon_trade, icon_tradingcentral;
static GLfloat box_account_number_vertices[8], drop_bg_vertices[8], drop_tradingcentral_vertices[8], panah_atas_vertices[8], icon_chart_vertices[8], icon_info_vertices[8], icon_logout_vertices[8], icon_myaccount_vertices[8], icon_portfolio_vertices[8], icon_trade_vertices[8], icon_tradingcentral_vertices[8];
static GLfloat box_account_number_tex_coord[8], drop_bg_tex_coord[8], drop_tradingcentral_tex_coord[8], panah_atas_tex_coord[8], icon_chart_tex_coord[8], icon_info_tex_coord[8], icon_logout_tex_coord[8], icon_myaccount_tex_coord[8], icon_portfolio_tex_coord[8], icon_trade_tex_coord[8], icon_tradingcentral_tex_coord[8];

static GLuint table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
static GLfloat table_bg_vertices[8], buy_vertices[8], sell_vertices[8], info_blue_vertices[8], menu_blue_vertices[8], post_vertices[8], rt_bar_title_vertices[8], rt_bar1_vertices[8], rt_ihsg_vertices[8], subtitle_vertices[8];
static GLfloat table_bg_tex_coord[8], buy_tex_coord[8], sell_tex_coord[8], info_blue_tex_coord[8], menu_blue_tex_coord[8], post_tex_coord[8], rt_bar_title_tex_coord[8], rt_bar1_tex_coord[8], rt_ihsg_tex_coord[8], subtitle_tex_coord[8];

static GLuint bg_green, sell_execute, sell_refresh, table_white, title_sell, white_bar;
static GLfloat bg_green_vertices[8], sell_execute_vertices[8], sell_refresh_vertices[8], table_white_vertices[8], title_sell_vertices[8], white_bar_vertices[8];
static GLfloat bg_green_tex_coord[8], sell_execute_tex_coord[8], sell_refresh_tex_coord[8], table_white_tex_coord[8], title_sell_tex_coord[8], white_bar_tex_coord[8];

static GLuint sq_bar, sq_title;
static GLfloat sq_bar_vertices[8], sq_title_vertices[8];
static GLfloat sq_bar_tex_coord[8], sq_title_tex_coord[8];

static GLuint ss_bar, ss_title;
static GLfloat ss_bar_vertices[8], ss_title_vertices[8];
static GLfloat ss_bar_tex_coord[8], ss_title_tex_coord[8];

static GLuint sw_title, banking, cons, mining, port1, box_black, plus_green, sw_green, sw_red, sw_yellow;
static GLfloat sw_title_vertices[8], banking_vertices[8], cons_vertices[8], mining_vertices[8], port1_vertices[8], box_black_vertices[8], plus_green_vertices[8], sw_green_vertices[8], sw_red_vertices[8], sw_yellow_vertices[8];
static GLfloat sw_title_tex_coord[8], banking_tex_coord[8], cons_tex_coord[8], mining_tex_coord[8], port1_tex_coord[8], box_black_tex_coord[8], plus_green_tex_coord[8], sw_green_tex_coord[8], sw_red_tex_coord[8], sw_yellow_tex_coord[8];



static screen_context_t screen_cxt;
static float pos_x, pos_y;

static font_t* font;

static int current_window;

enum state
{
	STATE_OPEN = 0,
	STATE_LOADING,
	STATE_LOGIN,
	STATE_RUNNING_TRADE,
	STATE_STOCK_WATCH,
	STATE_COMPLETE_BOOK,
	STATE_CORPORATE_ACTION,
	STATE_STOCK_QUOTE,
	STATE_BROKER_QUOTE,
	STATE_STOCK_SUMMARY,
	STATE_BROKER_SUMMARY,
	STATE_NON_REGULAR,
	STATE_CHARTS,
	STATE_INFORMATIONS,
	STATE_PORTFOLIO,
	STATE_ORDER_TRADE,
	STATE_MY_ACCOUNT,
	STATE_COMPANIES,
	STATE_END
};

enum state currentState;

static void handle_events() {
}

static void handleNavigatorEvent(bps_event_t *event) {
    switch (bps_event_get_code(event)) {
    case NAVIGATOR_ORIENTATION_CHECK:
        //Signal navigator that we intend to resize
        navigator_orientation_check_response(event, true);
        break;
    case NAVIGATOR_ORIENTATION:
        //if (EXIT_FAILURE == resize(event)) {
            //shutdown = true;
        //}
        break;
    case NAVIGATOR_SWIPE_DOWN:
        //menu_show_animation = true;
        //menu_hide_animation = false;
        break;
    case NAVIGATOR_EXIT:
        //shutdown = true;
        break;
    case NAVIGATOR_WINDOW_INACTIVE:
        //Wait for NAVIGATOR_WINDOW_ACTIVE event
        for (;;) {
            if (BPS_SUCCESS != bps_get_event(&event, -1)) {
                fprintf(stderr, "bps_get_event failed\n");
                break;
            }

            if (event && (bps_event_get_domain(event) == navigator_get_domain())) {
                int code = bps_event_get_code(event);
                if (code == NAVIGATOR_EXIT) {
                    //shutdown = true;
                    break;
                } else if (code == NAVIGATOR_WINDOW_ACTIVE) {
                    break;
                }
            }
        }
        break;
    }
}

void handleClick(int x, int y)
{
	if (currentState == STATE_LOGIN)
	{
		// periksa tombol login
		//if (x > 307 && x < 460 && y > 712 && y < 772)
		if ( x > tombol_login_vertices[0] && x < tombol_login_vertices[2] && y > tinggi_layar - tombol_login_vertices[1] && y < tinggi_layar -tombol_login_vertices[5] )
		{
			// do login
			currentState = STATE_RUNNING_TRADE;
		}
	}
}

void handleScreenEvent(bps_event_t *event) {
    screen_event_t screen_event = screen_event_get_event(event);
    int screen_val, buttons;
	int pair[2];

	static bool mouse_pressed = false;

    screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_TYPE,
            &screen_val);
    screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_SOURCE_POSITION,
                pair);

    switch (screen_val)
    {
    	case SCREEN_EVENT_MTOUCH_TOUCH:
    		break;
    	case SCREEN_EVENT_MTOUCH_MOVE:
    		break;
    	case SCREEN_EVENT_MTOUCH_RELEASE:
    		handleClick(pair[0], pair[1]);
    		break;
    	case SCREEN_EVENT_POINTER:
    		screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_BUTTONS,
					&buttons);

			if (buttons == SCREEN_LEFT_MOUSE_BUTTON) {
				//Left mouse button is pressed
				mouse_pressed = true;
			} else {
				if (mouse_pressed) {
					//Left mouse button was released, handle left click
					handleClick(pair[0], pair[1]);
					mouse_pressed = false;
				}
			}
			break;
    }
}

void setupPolygon(GLfloat * vertices, GLfloat *tex_coord, float pos_x, float pos_y, float size_x, float size_y, float tex_x, float tex_y)
{
	vertices[0] = pos_x;
	vertices[1] = pos_y;
	vertices[2] = pos_x + size_x;
	vertices[3] = pos_y;
	vertices[4] = pos_x;
	vertices[5] = pos_y + size_y;
	vertices[6] = pos_x + size_x;
	vertices[7] = pos_y + size_y;

	tex_coord[0] = 0.0f;
	tex_coord[1] = 0.0f;
	tex_coord[2] = 0.0f +tex_x;
	tex_coord[3] = 0.0f;
	tex_coord[4] = 0.0f;
	tex_coord[5] = 0.0f +tex_y;
	tex_coord[6] = 0.0f +tex_x;
	tex_coord[7] = 0.0f +tex_y;
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
	tinggi_layar = height;
	lebar_layar = width;

	float tex_x = 1.0f, tex_y = 1.0f;
	int size_x, size_y;

	//Load background texture

	if (EXIT_SUCCESS
			!= bbutil_load_texture("app/native/assets/latar.png",
					NULL, NULL, &tex_x, &tex_y, &latar)) {
		fprintf(stderr, "Unable to load background texture\n");
	}
	//Setup background polygon
	setupPolygon(latar_vertices, latar_tex_coord, 0.0f, 0.0f, width, height, tex_x, tex_y);

	size_x = 347; size_y = 430;
	pos_x = (width - size_x)/2;
	pos_y = height - 106.0f - size_y;
	//size_x = 60; size_y = 60;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/logo.png",
				NULL, NULL, &tex_x, &tex_y, &logo))
	{
		fprintf(stderr, "Unable to load logo texture\n");
	}
	setupPolygon(logo_vertices, logo_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 579; size_y = 70;
	pos_x = (width - size_x)/2;
	pos_y = height - 574.0f - size_y;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/kotak_username.png",
				NULL, NULL, &tex_x, &tex_y, &latar_username))
	{
		fprintf(stderr, "Unable to load latar_username texture\n");
	}
	setupPolygon(latar_username_vertices, latar_username_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 579; size_y = 70;
	pos_x = (width - size_x)/2;
	pos_y = height - 635.0f - size_y;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/kotak_password.png",
				NULL, NULL, &tex_x, &tex_y, &latar_password))
	{
		fprintf(stderr, "Unable to load latar_password texture\n");
	}
	setupPolygon(latar_password_vertices, latar_password_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 179; size_y = 83;
	pos_x = (width - size_x)/2;
	pos_y = height - 710.0f - size_y;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/btn_login.png",
				NULL, NULL, &tex_x, &tex_y, &tombol_login))
	{
		fprintf(stderr, "Unable to load btn_login texture\n");
	}
	setupPolygon(tombol_login_vertices, tombol_login_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 786; size_y = 56;
	pos_x = (width - size_x)/2;
	pos_y = height - 827.0f - size_y;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/pita_kuning.png",
				NULL, NULL, &tex_x, &tex_y, &latar_ihsg))
	{
		fprintf(stderr, "Unable to load pita_kuning texture\n");
	}
	setupPolygon(latar_ihsg_vertices, latar_ihsg_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 403; size_y = 109;
	pos_x = (width - size_x)/2;
	pos_y = height - 908.0f - size_y;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/latar_ihsg.png",
				NULL, NULL, &tex_x, &tex_y, &latar_ihsg_nilai))
	{
		fprintf(stderr, "Unable to load latar_ihsg texture\n");
	}
	setupPolygon(latar_ihsg_nilai_vertices, latar_ihsg_nilai_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 446; size_y = 105;
	pos_x = (width - size_x)/2;
	pos_y = height - 984.0f - size_y;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/latar_ihsg_nilai.png",
				NULL, NULL, &tex_x, &tex_y, &latar_ihsg_volume))
	{
		fprintf(stderr, "Unable to load latar_ihsg_nilai texture\n");
	}
	setupPolygon(latar_ihsg_volume_vertices, latar_ihsg_volume_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 616; size_y = 110;
	pos_x = (width - size_x)/2;
	pos_y = height - 1057.0f - size_y;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/latar_tanggal.png",
				NULL, NULL, &tex_x, &tex_y, &latar_tanggal))
	{
		fprintf(stderr, "Unable to load latar_tanggal texture\n");
	}
	setupPolygon(latar_tanggal_vertices, latar_tanggal_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 51; size_y = 50;
	pos_x = 310.0f;
	pos_y = height - 1180.0f - size_y;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/info.png",
				NULL, NULL, &tex_x, &tex_y, &info))
	{
		fprintf(stderr, "Unable to load info texture\n");
	}
	setupPolygon(info_vertices, info_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 51; size_y = 50;
	pos_x = 399.0f;
	//pos_y = height - 1180.0f - size_y;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/setel.png",
				NULL, NULL, &tex_x, &tex_y, &setel))
	{
		fprintf(stderr, "Unable to load setel texture\n");
	}
	setupPolygon(setel_vertices, setel_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//brokerquote_bar, brokerquote_caption;
	size_x = 709; size_y = 39;
	pos_x = 0.0f;
	pos_y = height - 263.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/broker_quote/bq_bar.png",
				&size_x, &size_y, &tex_x, &tex_y, &brokerquote_bar))
	{
		fprintf(stderr, "Unable to load bq_bar texture\n");
	}
	setupPolygon(brokerquote_bar_vertices, brokerquote_bar_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 2069; size_y = 53;
	pos_x = 28.0f;
	pos_y = height - 198.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/broker_quote/bq_caption.png",
			&size_x, &size_y, &tex_x, &tex_y, &brokerquote_caption))
	{
		fprintf(stderr, "Unable to load bq_caption texture\n");
	}
	setupPolygon(brokerquote_caption_vertices, brokerquote_caption_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//buyaction_bg, buyaction_execute, buyaction_caption, buyaction_refresh, buyaction_table, buyaction_whitebar.
	size_x = 736; size_y = 689;
	pos_x = 57.0f;
	pos_y = height - 1020.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/buy_action/buy_bg.png",
				NULL, NULL, &tex_x, &tex_y, &buyaction_bg))
	{
		fprintf(stderr, "Unable to load buy_action texture\n");
	}
	setupPolygon(buyaction_bg_vertices, buyaction_bg_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 206; size_y = 74;
	pos_x = 450.0f;
	pos_y = height - 908.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/buy_action/execute.png",
				NULL, NULL, &tex_x, &tex_y, &buyaction_execute))
	{
		fprintf(stderr, "Unable to load execute texture\n");
	}
	setupPolygon(buyaction_execute_vertices, buyaction_execute_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 206; size_y = 74;
	pos_x = 173.0f;
	pos_y = height - 908.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/buy_action/refresh.png",
				NULL, NULL, &tex_x, &tex_y, &buyaction_refresh))
	{
		fprintf(stderr, "Unable to load refresh texture\n");
	}
	setupPolygon(buyaction_refresh_vertices, buyaction_refresh_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 626; size_y = 48;
	pos_x = 75.0f;
	pos_y = height - 427.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/buy_action/buy_caption.png",
				NULL, NULL, &tex_x, &tex_y, &buyaction_caption))
	{
		fprintf(stderr, "Unable to load buy_caption texture\n");
	}
	setupPolygon(buyaction_caption_vertices, buyaction_caption_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 208; size_y = 26;
	pos_x = 448.0f;
	pos_y = height - 466.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/buy_action/table.png",
				NULL, NULL, &tex_x, &tex_y, &buyaction_table))
	{
		fprintf(stderr, "Unable to load table texture\n");
	}
	setupPolygon(buyaction_table_vertices, buyaction_table_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 662; size_y = 89;
	pos_x = 57.0f;
	pos_y = height - 922.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/buy_action/white_bar.png",
				NULL, NULL, &tex_x, &tex_y, &buyaction_whitebar))
	{
		fprintf(stderr, "Unable to load white_bar texture\n");
	}
	setupPolygon(buyaction_whitebar_vertices, buyaction_whitebar_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//bartulisan, bar2, bg2, bottom_bar, search, big_1day, big_1week, big_1month, big_1year, big_3year, small_1day, small_1week, small_1month, small_1year, small_3year;
	size_x = 1104; size_y = 46;
	pos_x = 80.0f;
	pos_y = width - 198.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/bar_tulisan.png",
				NULL, NULL, &tex_x, &tex_y, &bartulisan))
	{
		fprintf(stderr, "Unable to load bar_tulisan texture\n");
	}
	setupPolygon(bartulisan_vertices, bartulisan_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 1280; size_y = 82;
	pos_x = 80.0f;
	pos_y = width - 198.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/bar2.png",
				NULL, NULL, &tex_x, &tex_y, &bar2))
	{
		fprintf(stderr, "Unable to load bar2 texture\n");
	}
	setupPolygon(bar2_vertices, bar2_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y =0.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/bg2.png",
				&size_x, &size_y, &tex_x, &tex_y, &bg2))
	{
		fprintf(stderr, "Unable to load bg2 texture\n");
	}
	setupPolygon(bg2_vertices, bg2_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 1231; size_y = 31;
	pos_x = 22.0f;
	pos_y = width - 742.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/bottom_bar.png",
				NULL, NULL, &tex_x, &tex_y, &bottom_bar))
	{
		fprintf(stderr, "Unable to load bottom_bar texture\n");
	}
	setupPolygon(bottom_bar_vertices, bottom_bar_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 44; size_y = 44;
	pos_x = 1157.0f;
	pos_y = width - 196.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/search.png",
				NULL, NULL, &tex_x, &tex_y, &search))
	{
		fprintf(stderr, "Unable to load search texture\n");
	}
	setupPolygon(search_vertices, search_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 235; size_y = 30;
	pos_x = 22.0f;
	pos_y = width - 742.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/big_1day.png",
				NULL, NULL, &tex_x, &tex_y, &big_1day))
	{
		fprintf(stderr, "Unable to load big_1day texture\n");
	}
	setupPolygon(big_1day_vertices, big_1day_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 235; size_y = 30;
	pos_x = 22.0f;
	pos_y = width - 742.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/big_1week.png",
				NULL, NULL, &tex_x, &tex_y, &big_1week))
	{
		fprintf(stderr, "Unable to load big_1week texture\n");
	}
	setupPolygon(big_1week_vertices, big_1week_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 235; size_y = 30;
	pos_x = 22.0f;
	pos_y = width - 742.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/big_1month.png",
				NULL, NULL, &tex_x, &tex_y, &big_1month))
	{
		fprintf(stderr, "Unable to load big_1month texture\n");
	}
	setupPolygon(big_1month_vertices, big_1month_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 235; size_y = 30;
	pos_x = 22.0f;
	pos_y = width - 742.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/big_1year.png",
				NULL, NULL, &tex_x, &tex_y, &big_1year))
	{
		fprintf(stderr, "Unable to load big_1year texture\n");
	}
	setupPolygon(big_1year_vertices, big_1year_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 235; size_y = 30;
	pos_x = 22.0f;
	pos_y = width - 742.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/big_3year.png",
				NULL, NULL, &tex_x, &tex_y, &big_3year))
	{
		fprintf(stderr, "Unable to load big_3year texture\n");
	}
	setupPolygon(big_3year_vertices, big_3year_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 150; size_y = 27;
	pos_x = 245.0f;
	pos_y = width - 722.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/small_1day.png",
				NULL, NULL, &tex_x, &tex_y, &small_1day))
	{
		fprintf(stderr, "Unable to load small_1day texture\n");
	}
	setupPolygon(small_1day_vertices, small_1day_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 150; size_y = 27;
	pos_x = 245.0f;
	pos_y = width - 722.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/small_1week.png",
				NULL, NULL, &tex_x, &tex_y, &small_1week))
	{
		fprintf(stderr, "Unable to load small_1week texture\n");
	}
	setupPolygon(small_1week_vertices, small_1week_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 150; size_y = 27;
	pos_x = 404.0f;
	pos_y = width - 722.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/small_1month.png",
				NULL, NULL, &tex_x, &tex_y, &small_1month))
	{
		fprintf(stderr, "Unable to load small_1month texture\n");
	}
	setupPolygon(small_1month_vertices, small_1month_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 150; size_y = 27;
	pos_x = 558.0f;
	pos_y = width - 722.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/small_1year.png",
				NULL, NULL, &tex_x, &tex_y, &small_1year))
	{
		fprintf(stderr, "Unable to load small_1year texture\n");
	}
	setupPolygon(small_1year_vertices, small_1year_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	size_x = 150; size_y = 27;
	pos_x = 717.0f;
	pos_y = width - 722.0f;		// change orientation to landscape
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/charts/small_3year.png",
				NULL, NULL, &tex_x, &tex_y, &small_3year))
	{
		fprintf(stderr, "Unable to load small_3year texture\n");
	}
	setupPolygon(small_3year_vertices, small_3year_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//companies, financial_small, ratio_small;
	pos_x = 26.0f;
	pos_y = height - 197.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/companies/companies.png",
				&size_x, &size_y, &tex_x, &tex_y, &companies))
	{
		fprintf(stderr, "Unable to load companies texture\n");
	}
	setupPolygon(companies_vertices, companies_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 359.0f;
	pos_y = height - 180.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/companies/financial_small.png",
				&size_x, &size_y, &tex_x, &tex_y, &financial_small))
	{
		fprintf(stderr, "Unable to load financial_small texture\n");
	}
	setupPolygon(financial_small_vertices, financial_small_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 542.0f;
	pos_y = height - 180.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/companies/ratio_small.png",
				&size_x, &size_y, &tex_x, &tex_y, &ratio_small))
	{
		fprintf(stderr, "Unable to load ratio_small texture\n");
	}
	setupPolygon(ratio_small_vertices, ratio_small_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//completebook_bar1, completebook_bar2, completebook_bar3, completebook_caption;
	pos_x = 0.0f;
	pos_y = height - 263.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/completebook/bar1.png",
				&size_x, &size_y, &tex_x, &tex_y, &completebook_bar1))
	{
		fprintf(stderr, "Unable to load bar1 texture\n");
	}
	setupPolygon(completebook_bar1_vertices, completebook_bar1_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 452.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/completebook/bar2.png",
				&size_x, &size_y, &tex_x, &tex_y, &completebook_bar2))
	{
		fprintf(stderr, "Unable to load bar2 texture\n");
	}
	setupPolygon(completebook_bar2_vertices, completebook_bar2_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 738.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/completebook/bar3.png",
				&size_x, &size_y, &tex_x, &tex_y, &completebook_bar3))
	{
		fprintf(stderr, "Unable to load bar3 texture\n");
	}
	setupPolygon(completebook_bar3_vertices, completebook_bar3_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 28.0f;
	pos_y = height - 198.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/completebook/completebook_caption.png",
				&size_x, &size_y, &tex_x, &tex_y, &completebook_caption))
	{
		fprintf(stderr, "Unable to load completebook_caption texture\n");
	}
	setupPolygon(completebook_caption_vertices, completebook_caption_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//ca_bar, ca_caption, ca_bonus1, ca_bonus2, ca_dividen1, ca_dividen2, ca_rights1, ca_rights2, ca_rups1, ca_rups2, ca_split1, ca_split2, ca_warrant1, ca_warrant2;
	pos_x = 0.0f;
	pos_y = height - 318.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/bar.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_bar))
	{
		fprintf(stderr, "Unable to load bar texture\n");
	}
	setupPolygon(ca_bar_vertices, ca_bar_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 28.0f;
	pos_y = height - 198.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/ca_caption.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_caption))
	{
		fprintf(stderr, "Unable to load ca_caption texture\n");
	}
	setupPolygon(ca_caption_vertices, ca_caption_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 214.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/bonus1.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_bonus1))
	{
		fprintf(stderr, "Unable to load bonus1 texture\n");
	}
	setupPolygon(ca_bonus1_vertices, ca_bonus1_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 214.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/bonus2.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_bonus2))
	{
		fprintf(stderr, "Unable to load buy_caption texture\n");
	}
	setupPolygon(ca_bonus2_vertices, ca_bonus2_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 28.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/dividen1.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_dividen1))
	{
		fprintf(stderr, "Unable to load buy_caption texture\n");
	}
	setupPolygon(ca_dividen1_vertices, ca_dividen1_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 28.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/dividen2.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_dividen2))
	{
		fprintf(stderr, "Unable to load dividen2 texture\n");
	}
	setupPolygon(ca_dividen2_vertices, ca_dividen2_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 710.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/rights1.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_rights1))
	{
		fprintf(stderr, "Unable to load rights1 texture\n");
	}
	setupPolygon(ca_rights1_vertices, ca_rights1_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 710.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/rights2.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_rights2))
	{
		fprintf(stderr, "Unable to load rights2 texture\n");
	}
	setupPolygon(ca_rights2_vertices, ca_rights2_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 840.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/rups1.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_rups1))
	{
		fprintf(stderr, "Unable to load rups1 texture\n");
	}
	setupPolygon(ca_rups1_vertices, ca_rups1_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 840.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/rups2.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_rups2))
	{
		fprintf(stderr, "Unable to load rups2 texture\n");
	}
	setupPolygon(ca_rups2_vertices, ca_rups2_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 341.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/split1.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_split1))
	{
		fprintf(stderr, "Unable to load buy_caption texture\n");
	}
	setupPolygon(ca_split1_vertices, ca_split1_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 341.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/split2.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_split2))
	{
		fprintf(stderr, "Unable to load buy_caption texture\n");
	}
	setupPolygon(ca_split2_vertices, ca_split2_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 525.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/warrant1.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_warrant1))
	{
		fprintf(stderr, "Unable to load warrant1 texture\n");
	}
	setupPolygon(ca_warrant1_vertices, ca_warrant1_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 525.0f;
	pos_y = height - 240.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/corporate_action/warrant2.png",
				&size_x, &size_y, &tex_x, &tex_y, &ca_warrant2))
	{
		fprintf(stderr, "Unable to load warrant2 texture\n");
	}
	setupPolygon(ca_warrant2_vertices, ca_warrant2_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//box_account_number, drop_bg, drop_tradingcentral, panah_atas, icon_chart, icon_info, icon_logout, icon_myaccount, icon_portfolio, icon_trade, icon_tradingcentral;
	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/box_account_number.png",
				&size_x, &size_y, &tex_x, &tex_y, &box_account_number))
	{
		fprintf(stderr, "Unable to load box_account_number texture\n");
	}
	setupPolygon(box_account_number_vertices, box_account_number_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/drop_bg.png",
				&size_x, &size_y, &tex_x, &tex_y, &drop_bg))
	{
		fprintf(stderr, "Unable to load drop_bg texture\n");
	}
	setupPolygon(drop_bg_vertices, drop_bg_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/drop_tradingcentral.png",
				&size_x, &size_y, &tex_x, &tex_y, &drop_tradingcentral))
	{
		fprintf(stderr, "Unable to load drop_tradingcentral texture\n");
	}
	setupPolygon(drop_tradingcentral_vertices, drop_tradingcentral_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/panah_atas.png",
				&size_x, &size_y, &tex_x, &tex_y, &panah_atas))
	{
		fprintf(stderr, "Unable to load panah_atas texture\n");
	}
	setupPolygon(panah_atas_vertices, panah_atas_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/icon_chart.png",
				&size_x, &size_y, &tex_x, &tex_y, &icon_chart))
	{
		fprintf(stderr, "Unable to load icon_chart texture\n");
	}
	setupPolygon(icon_chart_vertices, icon_chart_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/icon_info.png",
				&size_x, &size_y, &tex_x, &tex_y, &icon_info))
	{
		fprintf(stderr, "Unable to load icon_info texture\n");
	}
	setupPolygon(icon_info_vertices, icon_info_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/icon_logout.png",
				&size_x, &size_y, &tex_x, &tex_y, &icon_logout))
	{
		fprintf(stderr, "Unable to load icon_logout texture\n");
	}
	setupPolygon(icon_logout_vertices, icon_logout_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/icon_myaccount.png",
				&size_x, &size_y, &tex_x, &tex_y, &icon_myaccount))
	{
		fprintf(stderr, "Unable to load icon_myaccount texture\n");
	}
	setupPolygon(icon_myaccount_vertices, icon_myaccount_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/icon_portfolio.png",
				&size_x, &size_y, &tex_x, &tex_y, &icon_portfolio))
	{
		fprintf(stderr, "Unable to load icon_portfolio texture\n");
	}
	setupPolygon(icon_portfolio_vertices, icon_portfolio_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/icon_trade.png",
				&size_x, &size_y, &tex_x, &tex_y, &icon_trade))
	{
		fprintf(stderr, "Unable to load icon_trade texture\n");
	}
	setupPolygon(icon_trade_vertices, icon_trade_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 60.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/dropdown/icon_tradingcentral.png",
				&size_x, &size_y, &tex_x, &tex_y, &icon_tradingcentral))
	{
		fprintf(stderr, "Unable to load icon_tradingcentral texture\n");
	}
	setupPolygon(icon_tradingcentral_vertices, icon_tradingcentral_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	pos_x = 0.0f;
	pos_y = height - 1169.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/running_trade/table_bg.png",
				&size_x, &size_y, &tex_x, &tex_y, &table_bg))
	{
		fprintf(stderr, "Unable to load table_bg texture\n");
	}
	setupPolygon(table_bg_vertices, table_bg_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 460.0f;
	pos_y = height - 1254.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/running_trade/buy.png",
				&size_x, &size_y, &tex_x, &tex_y, &buy))
	{
		fprintf(stderr, "Unable to load buy texture\n");
	}
	setupPolygon(buy_vertices, buy_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 622.0f;
	pos_y = height - 1254.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/running_trade/sell.png",
				&size_x, &size_y, &tex_x, &tex_y, &sell))
	{
		fprintf(stderr, "Unable to load sell texture\n");
	}
	setupPolygon(sell_vertices, sell_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 680.0f;
	pos_y = height - 128.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/running_trade/info_blue.png",
				&size_x, &size_y, &tex_x, &tex_y, &info_blue))
	{
		fprintf(stderr, "Unable to load info_blue texture\n");
	}
	setupPolygon(info_blue_vertices, info_blue_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 25.0f;
	pos_y = height - 128.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/running_trade/menu_blue.png",
				&size_x, &size_y, &tex_x, &tex_y, &menu_blue))
	{
		fprintf(stderr, "Unable to load menu_blue texture\n");
	}
	setupPolygon(menu_blue_vertices, menu_blue_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 296.0f;
	pos_y = height - 124.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/running_trade/post.png",
				&size_x, &size_y, &tex_x, &tex_y, &post))
	{
		fprintf(stderr, "Unable to load post texture\n");
	}
	setupPolygon(post_vertices, post_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 27.0f;
	pos_y = height - 200.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/running_trade/rt_bar_title.png",
				&size_x, &size_y, &tex_x, &tex_y, &rt_bar_title))
	{
		fprintf(stderr, "Unable to load rt_bar_title texture\n");
	}
	setupPolygon(rt_bar_title_vertices, rt_bar_title_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 137.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/running_trade/rt_bar1.png",
				&size_x, &size_y, &tex_x, &tex_y, &rt_bar1))
	{
		fprintf(stderr, "Unable to load rt_bar1 texture\n");
	}
	setupPolygon(rt_bar1_vertices, rt_bar1_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 15.0f;
	pos_y = height - 1268.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/running_trade/rt_ihsg.png",
				&size_x, &size_y, &tex_x, &tex_y, &rt_ihsg))
	{
		fprintf(stderr, "Unable to load rt_ihsg texture\n");
	}
	setupPolygon(rt_ihsg_vertices, rt_ihsg_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 262.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/running_trade/subtitle.png",
				&size_x, &size_y, &tex_x, &tex_y, &subtitle))
	{
		fprintf(stderr, "Unable to load subtitle texture\n");
	}
	setupPolygon(subtitle_vertices, subtitle_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//bg_green, sell_execute, sell_refresh, table_white, title_sell, white_bar;
	pos_x = 55.0f;
	pos_y = height - 1010.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/sell_coloumn/bg_green.png",
				&size_x, &size_y, &tex_x, &tex_y, &bg_green))
	{
		fprintf(stderr, "Unable to load bg_green texture\n");
	}
	setupPolygon(bg_green_vertices, bg_green_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 454.0f;
	pos_y = height - 906.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/sell_coloumn/sell_execute.png",
				&size_x, &size_y, &tex_x, &tex_y, &sell_execute))
	{
		fprintf(stderr, "Unable to load sell_execute texture\n");
	}
	setupPolygon(sell_execute_vertices, sell_execute_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 179.0f;
	pos_y = height - 906.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/sell_coloumn/sell_refresh.png",
				&size_x, &size_y, &tex_x, &tex_y, &sell_refresh))
	{
		fprintf(stderr, "Unable to load sell_refresh texture\n");
	}
	setupPolygon(sell_refresh_vertices, sell_refresh_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 446.0f;
	pos_y = height - 465.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/sell_coloumn/table_white.png",
				&size_x, &size_y, &tex_x, &tex_y, &table_white))
	{
		fprintf(stderr, "Unable to load table_white texture\n");
	}
	setupPolygon(table_white_vertices, table_white_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 75.0f;
	pos_y = height - 422.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/sell_coloumn/title_sell.png",
				&size_x, &size_y, &tex_x, &tex_y, &title_sell))
	{
		fprintf(stderr, "Unable to load title_sell texture\n");
	}
	setupPolygon(title_sell_vertices, title_sell_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 920.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/sell_coloumn/white_bar.png",
				&size_x, &size_y, &tex_x, &tex_y, &white_bar))
	{
		fprintf(stderr, "Unable to load white_bar texture\n");
	}
	setupPolygon(white_bar_vertices, white_bar_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//sq_bar, sq_title;
	pos_x = 27.0f;
	pos_y = height - 200.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_quote/sq_bar.png",
				&size_x, &size_y, &tex_x, &tex_y, &sq_bar))
	{
		fprintf(stderr, "Unable to load sq_bar texture\n");
	}
	setupPolygon(sq_bar_vertices, sq_bar_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 0.0f;
	pos_y = height - 262.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_quote/sq_title.png",
				&size_x, &size_y, &tex_x, &tex_y, &sq_title))
	{
		fprintf(stderr, "Unable to load sq_title texture\n");
	}
	setupPolygon(sq_title_vertices, sq_title_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//ss_bar, ss_title;
	pos_x = 0.0f;
	pos_y = height - 262.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_summary/ss_bar.png",
				&size_x, &size_y, &tex_x, &tex_y, &ss_bar))
	{
		fprintf(stderr, "Unable to load ss_bar texture\n");
	}
	setupPolygon(ss_bar_vertices, ss_bar_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 27.0f;
	pos_y = height - 200.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_summary/ss_title.png",
				&size_x, &size_y, &tex_x, &tex_y, &ss_title))
	{
		fprintf(stderr, "Unable to load ss_title texture\n");
	}
	setupPolygon(ss_title_vertices, ss_title_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	//sw_title, banking, cons, mining, port1, box_black, plus_green, sw_green, sw_red, sw_yellow;
	pos_x = 27.0f;
	pos_y = height - 200.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_watch/sw_title.png",
				&size_x, &size_y, &tex_x, &tex_y, &sw_title))
	{
		fprintf(stderr, "Unable to load sw_title texture\n");
	}
	setupPolygon(sw_title_vertices, sw_title_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 201.0f;
	pos_y = height - 270.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_watch/banking.png",
				&size_x, &size_y, &tex_x, &tex_y, &banking))
	{
		fprintf(stderr, "Unable to load banking texture\n");
	}
	setupPolygon(banking_vertices, banking_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 520.0f;
	pos_y = height - 270.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_watch/cons.png",
				&size_x, &size_y, &tex_x, &tex_y, &cons))
	{
		fprintf(stderr, "Unable to load cons texture\n");
	}
	setupPolygon(cons_vertices, cons_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 362.0f;
	pos_y = height - 270.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_watch/mining.png",
				&size_x, &size_y, &tex_x, &tex_y, &mining))
	{
		fprintf(stderr, "Unable to load mining texture\n");
	}
	setupPolygon(mining_vertices, mining_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 41.0f;
	pos_y = height - 270.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_watch/port1.png",
				&size_x, &size_y, &tex_x, &tex_y, &port1))
	{
		fprintf(stderr, "Unable to load port1 texture\n");
	}
	setupPolygon(port1_vertices, port1_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 27.0f;
	pos_y = height - 455.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_watch/box_black.png",
				&size_x, &size_y, &tex_x, &tex_y, &box_black))
	{
		fprintf(stderr, "Unable to load box_black texture\n");
	}
	setupPolygon(box_black_vertices, box_black_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 676.0f;
	pos_y = height - 270.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_watch/plus_green.png",
				&size_x, &size_y, &tex_x, &tex_y, &plus_green))
	{
		fprintf(stderr, "Unable to load plus_green texture\n");
	}
	setupPolygon(plus_green_vertices, plus_green_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 40.0f;
	pos_y = height - 413.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_watch/sw_green.png",
				&size_x, &size_y, &tex_x, &tex_y, &sw_green))
	{
		fprintf(stderr, "Unable to load sw_green texture\n");
	}
	setupPolygon(sw_green_vertices, sw_green_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 40.0f;
	pos_y = height - 413.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_watch/sw_red.png",
				&size_x, &size_y, &tex_x, &tex_y, &sw_red))
	{
		fprintf(stderr, "Unable to load sw_red texture\n");
	}
	setupPolygon(sw_red_vertices, sw_red_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);

	pos_x = 40.0f;
	pos_y = height - 413.0f;
	if (EXIT_SUCCESS != bbutil_load_texture("app/native/assets/stock_watch/sw_yellow.png",
				&size_x, &size_y, &tex_x, &tex_y, &sw_yellow))
	{
		fprintf(stderr, "Unable to load sw_yellow texture\n");
	}
	setupPolygon(sw_yellow_vertices, sw_yellow_tex_coord, pos_x, pos_y, (float)size_x, (float)size_y, tex_x, tex_y);



	int dpi = bbutil_calculate_dpi(screen_cxt);

	//As bbutil renders text using device-specifc dpi, we need to compute a point size
	//for the font, so that the text string fits into the bubble. Note that Playbook is used
	//as a reference point in this equation as we know that at dpi of 170, font with point size of
	//15 fits into the bubble texture.
	float stretch_factor = (float)surface_width / (float)width;
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

//	float text_width, text_height;
//	bbutil_measure_text(font, "Username", &text_width, &text_height);
//	pos_x = (width - text_width) / 2;
//	pos_y = height / 2;

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

void drawLoginView ()
{
	//Typical rendering pass
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, logo_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, logo_tex_coord);
	glBindTexture(GL_TEXTURE_2D, logo);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_username_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_username_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar_username);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_password_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_password_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar_password);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, tombol_login_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, tombol_login_tex_coord);
	glBindTexture(GL_TEXTURE_2D, tombol_login);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_ihsg_nilai_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_ihsg_nilai_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar_ihsg_nilai);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_ihsg_volume_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_ihsg_volume_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar_ihsg_volume);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, latar_tanggal_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tanggal_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar_tanggal);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, setel_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, setel_tex_coord);
	glBindTexture(GL_TEXTURE_2D, setel);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	//Use utility code to render welcome text onto the screen
	int dpi = bbutil_calculate_dpi(screen_cxt);
	float stretch_factor = (float)surface_width / (float)width;
	int point_size = (int)(15.0f * stretch_factor / ((float)dpi / 170.0f ));
	font = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);

	float text_width, text_height;
	bbutil_measure_text(font, "Username", &text_width, &text_height);
	pos_x = 390;
	pos_y = height -620;
	bbutil_render_text(font, "Username", pos_x, pos_y, 0.05f, 0.05f, 0.05f, 1.0f);

	bbutil_measure_text(font, "Password", &text_width, &text_height);
	pos_x = 390;
	pos_y = height -677;
	bbutil_render_text(font, "Password", pos_x, pos_y, 0.05f, 0.05f, 0.05f, 1.0f);

	stretch_factor = (float)surface_width / (float)width;
	point_size = (int)(20.0f * stretch_factor / ((float)dpi / 170.0f ));
	font = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);

	bbutil_measure_text(font, "5000.00", &text_width, &text_height);
	pos_x = (width - text_width) /2;
	pos_y = height -980;
	bbutil_render_text(font, "5000.00", pos_x, pos_y, 0.05f, 0.05f, 0.05f, 1.0f);

	stretch_factor = (float)surface_width / (float)width;
	point_size = (int)(16.5f * stretch_factor / ((float)dpi / 170.0f ));
	font = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);

	bbutil_measure_text(font, "3415.10 bn 17.77 (30%)", &text_width, &text_height);
	pos_x = (width - text_width) /2;
	pos_y = height -1050;
	bbutil_render_text(font, "3415.10 bn 17.77 (30%)", pos_x, pos_y, 0.05f, 0.05f, 0.05f, 1.0f);

	stretch_factor = (float)surface_width / (float)width;
	point_size = (int)(15.0f * stretch_factor / ((float)dpi / 170.0f ));
	font = bbutil_load_font("/usr/fonts/font_repository/monotype/arial.ttf", point_size, dpi);

	bbutil_measure_text(font, "30 September 2013 23:59:59", &text_width, &text_height);
	pos_x = (width - text_width) /2;
	pos_y = height -1125;
	bbutil_render_text(font, "30 September 2013 23:59:59", pos_x, pos_y, 0.35f, 0.35f, 0.35f, 1.0f);

	//Use utility code to update the screen
	bbutil_swap();
}

void drawRunningTrade()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar_title_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar_title_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar_title);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, subtitle_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, subtitle_tex_coord);
	glBindTexture(GL_TEXTURE_2D, subtitle);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, table_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, table_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, table_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}

void drawStockWatch()
{
	//buyaction_bg, buyaction_execute, buyaction_caption, buyaction_refresh, buyaction_table, buyaction_whitebar;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buyaction_table_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buyaction_table_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buyaction_table);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buyaction_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buyaction_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buyaction_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buyaction_caption_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buyaction_caption_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buyaction_caption);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buyaction_execute_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buyaction_execute_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buyaction_execute);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buyaction_refresh_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buyaction_refresh_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buyaction_refresh);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buyaction_whitebar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buyaction_whitebar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buyaction_whitebar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}

void drawCompleteBook()
{
	//completebook_bar1, completebook_bar2, completebook_bar3, completebook_caption;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, completebook_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, completebook_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, completebook_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, completebook_bar2_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, completebook_bar2_tex_coord);
	glBindTexture(GL_TEXTURE_2D, completebook_bar2);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, completebook_bar3_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, completebook_bar3_tex_coord);
	glBindTexture(GL_TEXTURE_2D, completebook_bar3);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, completebook_caption_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, completebook_caption_tex_coord);
	glBindTexture(GL_TEXTURE_2D, completebook_caption);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}

//ca_bar, ca_caption, ca_bonus1, ca_bonus2, ca_dividen1, ca_dividen2, ca_rights1, ca_rights2, ca_rups1, ca_rups2, ca_split1, ca_split2, ca_warrant1, ca_warrant2;
void drawCorporateAction()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	glVertexPointer(2, GL_FLOAT, 0, ca_bar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, ca_bar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, ca_bar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//ca_caption, ca_bonus1, ca_bonus2, ca_dividen1, ca_dividen2, ca_rights1, ca_rights2, ca_rups1, ca_rups2, ca_split1, ca_split2, ca_warrant1, ca_warrant2;
	glVertexPointer(2, GL_FLOAT, 0, ca_caption_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, ca_caption_tex_coord);
	glBindTexture(GL_TEXTURE_2D, ca_caption);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, ca_bonus1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, ca_bonus1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, ca_bonus1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, ca_dividen1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, ca_dividen1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, ca_dividen1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, ca_rights1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, ca_rights1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, ca_rights1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, ca_rups1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, ca_rups1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, ca_rups1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, ca_split1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, ca_split1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, ca_split1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, ca_warrant1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, ca_warrant1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, ca_warrant1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}
void drawStockQuote()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, brokerquote_bar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, brokerquote_bar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, brokerquote_bar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, brokerquote_caption_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, brokerquote_caption_tex_coord);
	glBindTexture(GL_TEXTURE_2D, brokerquote_caption);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}


void drawStockSummary()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar_title_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar_title_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar_title);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, subtitle_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, subtitle_tex_coord);
	glBindTexture(GL_TEXTURE_2D, subtitle);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, table_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, table_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, table_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}

//brokerquote_bar, brokerquote_caption;
void drawBrokerQuote()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, brokerquote_bar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, brokerquote_bar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, brokerquote_bar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, brokerquote_caption_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, brokerquote_caption_tex_coord);
	glBindTexture(GL_TEXTURE_2D, brokerquote_caption);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}

void drawBrokerSummary()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar_title_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar_title_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar_title);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, subtitle_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, subtitle_tex_coord);
	glBindTexture(GL_TEXTURE_2D, subtitle);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, table_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, table_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, table_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}


void drawNonRegular()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar_title_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar_title_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar_title);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, subtitle_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, subtitle_tex_coord);
	glBindTexture(GL_TEXTURE_2D, subtitle);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, table_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, table_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, table_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}


void drawCharts()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar_title_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar_title_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar_title);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, subtitle_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, subtitle_tex_coord);
	glBindTexture(GL_TEXTURE_2D, subtitle);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, table_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, table_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, table_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}


void drawInformation()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar_title_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar_title_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar_title);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, subtitle_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, subtitle_tex_coord);
	glBindTexture(GL_TEXTURE_2D, subtitle);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, table_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, table_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, table_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}

void drawPortFolio()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar_title_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar_title_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar_title);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, subtitle_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, subtitle_tex_coord);
	glBindTexture(GL_TEXTURE_2D, subtitle);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, table_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, table_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, table_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}

void drawOrderTrade()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar_title_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar_title_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar_title);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, subtitle_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, subtitle_tex_coord);
	glBindTexture(GL_TEXTURE_2D, subtitle);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, table_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, table_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, table_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}

void drawMyAccount()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar_title_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar_title_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar_title);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, subtitle_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, subtitle_tex_coord);
	glBindTexture(GL_TEXTURE_2D, subtitle);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, table_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, table_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, table_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}

void drawCompanies()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);

	enable_2d();

	//Render background quad first
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//table_bg, buy, sell, info_blue, menu_blue, post, rt_bar_title, rt_bar1, rt_ihsg, subtitle;
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glVertexPointer(2, GL_FLOAT, 0, latar_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, latar_tex_coord);
	glBindTexture(GL_TEXTURE_2D, latar);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, buy_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, buy_tex_coord);
	glBindTexture(GL_TEXTURE_2D, buy);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, sell_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, sell_tex_coord);
	glBindTexture(GL_TEXTURE_2D, sell);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, info_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, info_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, info_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, menu_blue_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, menu_blue_tex_coord);
	glBindTexture(GL_TEXTURE_2D, menu_blue);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar1_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar1_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, post_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, post_tex_coord);
	glBindTexture(GL_TEXTURE_2D, post);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_bar_title_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_bar_title_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_bar_title);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, rt_ihsg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, rt_ihsg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, rt_ihsg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, subtitle_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, subtitle_tex_coord);
	glBindTexture(GL_TEXTURE_2D, subtitle);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glVertexPointer(2, GL_FLOAT, 0, table_bg_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, table_bg_tex_coord);
	glBindTexture(GL_TEXTURE_2D, table_bg);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	bbutil_swap();
}

void render() {

	switch (currentState)
	{
		case STATE_OPEN:
			currentState = STATE_LOGIN;
			break;

		case STATE_LOGIN:
			drawLoginView();
			break;

		case STATE_RUNNING_TRADE:
			drawRunningTrade();
			break;

		case STATE_STOCK_WATCH:
			drawStockWatch();
			break;

		case STATE_COMPLETE_BOOK:
			drawCompleteBook();
			break;

		case STATE_CORPORATE_ACTION:
			drawCorporateAction();
			break;

		case STATE_STOCK_QUOTE:
			drawStockQuote();
			break;

		case STATE_BROKER_QUOTE:
			drawBrokerQuote();
			break;

		case STATE_STOCK_SUMMARY:
			drawStockSummary();
			break;

		case STATE_BROKER_SUMMARY:
			drawBrokerSummary();
			break;

		case STATE_NON_REGULAR:
			drawNonRegular();
			break;

		case STATE_CHARTS:
			drawCharts();
			break;

		case STATE_INFORMATIONS:
			drawInformation();
			break;

		case STATE_PORTFOLIO:
			drawPortFolio();
			break;

		case STATE_ORDER_TRADE:
			drawOrderTrade();
			break;

		case STATE_MY_ACCOUNT:
			drawMyAccount();
			break;

		case STATE_COMPANIES:
			drawCompanies();
			break;

	}

}

int main(int argc, char *argv[]) {
    int exit_application = 0;
    //static screen_context_t screen_cxt;

    currentState = STATE_OPEN;

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
