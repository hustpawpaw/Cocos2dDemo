#ifndef __RES_MANAGE__TOOLS_H__
#define  __RES_MANAGE__TOOLS_H__

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)   //win32¼üÅÌÏìÓ¦ÊÂ¼þ
#include <windows.h>
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)
#endif



static const char button_back[]         = "images/button-back.png";
static const char button_off[]          = "images/button-off.png";
static const char button_on[]           = "images/button-on.png";
static const char button_fight[]        = "images/fight.png";
static const char button_fight_[]       = "images/fight_.png";
static const char button_freeforall[]   = "images/freeforall.png";
static const char button_freeforall_[]  = "images/freeforall_.png";
static const char button_left[]         = "images/leftarrow.png";
static const char button_right[]         = "images/rightarrow.png";
static const char button_practice[]     = "images/practice.png";
static const char button_practice_[]    = "images/practice_.png";
static const char button_yes[]          = "images/yes.png";
static const char button_no[]           = "images/no.png";
static const char button_createhost[]   = "images/createhost.png"; 
static const char button_selecthost[]   = "images/selecthost.png";
static const char button_OK[]           = "images/OK.png";
static const char exit_bg[]             = "images/closewindow.png";
static const char inputname_bg[]        = "images/inputname.png";
static const char menu_exit[]			= "images/exit.png";
static const char menu_main[]           = "images/main.png";
//static const char menu_exit_[]			= "images/exit_.png";
static const char menu_help[]           = "images/help.png";
static const char menu_menubg[]			= "images/menubg.png";
static const char menu_options[]		= "images/options.png";
//static const char menu_options_[]		= "images/options_.png";
static const char menu_shop[]           = "images/shop.png";
static const char snow[]				= "images/snow.png";
static const char options_bg[]          = "images/optionsbg.png";
static const char selectmode_bg[]       = "images/selectmode.png";
static const char selecthostwindow_bg[] = "images/selecthostwindow.png";
static const char menu_start[]			= "images/start.png";
static const char wait_bg[]             = "images/waitplayer.png";
static const char helpCotent_bg[]       = "images/helpcontent.png";
//static const char menu_start_[]			= "images/start_.png";

#endif									   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   
										   