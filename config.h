/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"
#define BROWSER "firefox"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "launch_polybar"; /* Alternate bar launch command */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static char normbordercolor[]       = "#444444";
static char selbordercolor[]        = "#770000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, normbordercolor },
	[SchemeSel]  = { col_gray4, col_cyan,  selbordercolor  },
};
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */

	// { "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },

  /* No borders for single window in a workspace */
  // { NULL,       NULL,       NULL,       1 << 8,       0,            0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char scratchpadname[] = "scratchpad";

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	/* { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,            		XK_u,	   togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
        // Switch windows using Mod + [j,k]
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        // Change current master Window
	{ MODKEY|ShiftMask,             XK_j,      incnmaster,     {.i = -1 } },
        { MODKEY|ShiftMask,             XK_k,      incnmaster,     {.i = +1 } },
        // Switch monitors using Mod + [h,l]
	{ MODKEY,                       XK_h,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_l,      focusmon,       {.i = +1 } },

	{ MODKEY,		                    XK_m,		   spawn,		       {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },

	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	/* { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },*/
/* 	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	/* { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	/* { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */
        // Switch tag using Win + <tag_number>
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,           quit,           {0} },

        /* MUSIC CONTROL */
	{ MODKEY,	XK_comma,	            spawn,	{.v = (const char*[]){ "music", "prev", NULL } } },
	{ MODKEY,	XK_period,	          spawn,	{.v = (const char*[]){ "music", "next", NULL } } },
	{ MODKEY,	XK_p,		              spawn,	{.v = (const char*[]){ "music", "plpa", NULL } } },

        /* Function Keys */
	{ 0, XF86XK_AudioPrev,	       spawn,	{.v = (const char*[]){ "music",      "prev",      NULL } } },
	{ 0, XF86XK_AudioNext,	       spawn,	{.v = (const char*[]){ "music",      "next",      NULL } } },
	{ 0, XF86XK_AudioPlay,	       spawn,	{.v = (const char*[]){ "music",      "plpa",      NULL } } },
  { 0, XF86XK_AudioLowerVolume,  spawn, {.v = (const char*[]){ "pamixer",    "-d",   "5", NULL } } },
  { 0, XF86XK_AudioRaiseVolume,  spawn, {.v = (const char*[]){ "pamixer",    "-i",   "5", NULL } } },
  { 0, XF86XK_AudioMute,         spawn, {.v = (const char*[]){ "pamixer",    "-t",        NULL } } },
	{ 0, XF86XK_MonBrightnessUp,	 spawn,	{.v = (const char*[]){ "xbacklight", "+5",        NULL } } },
	{ 0, XF86XK_MonBrightnessDown, spawn,	{.v = (const char*[]){ "xbacklight", "-3",        NULL } } },


        /* PROGRAMS SHORTCUTS */
	{ MODKEY|ShiftMask,		XK_w,		spawn,		{.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,		        XK_w,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "nmtui", NULL } } },
	{ MODKEY,			XK_d,		spawn,          {.v = (const char*[]){ "rofi", "-show", "drun", NULL } } },
	{ MODKEY,			XK_BackSpace,	spawn,		{.v = (const char*[]){ "sysact", NULL } } },
/* 	{ MODKEY,		        XK_i,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } }, */
  { MODKEY,           XK_i,   spawn,    {.v = (const char*[]){"flameshot", "gui", NULL}}},

        /* WINDOWS ACTIONS */
        // TODO: Here
// 	{ MODKEY,			XK_s,		togglesticky,	{0} },
// 	{ MODKEY,			XK_z,		incrgaps,	{.i = +3 } },
// 	{ MODKEY,			XK_x,		incrgaps,	{.i = -3 } },
  // Increase/Decrease windows size using Mod + [n,m]
	// { MODKEY,                       XK_n,      setmfact,       {.f = -0.05} },
	// { MODKEY,                       XK_m,      setmfact,       {.f = +0.05} },
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY|ShiftMask,		XK_h,	        tagmon,		{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_l,	        tagmon,		{.i = +1 } },

  { MODKEY,                       XK_x,           spawn,          {.v = (const char*[]){"slock", NULL}}},
  { MODKEY,                       XK_y,           spawn,          {.v = (const char*[]){"ytdlp", NULL}}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

