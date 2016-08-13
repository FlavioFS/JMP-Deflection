#include "screens.h"

u8 next_screen = MAIN_SCREEN;

// [1]
void set_next_screen (u8 screen_code)
{
	next_screen = screen_code;
}


// [2]
/**
 * Displays the current screen
 */
void current_screen()
{
	switch (next_screen)
	{
	case MAIN_SCREEN:
		VDP_clearPlan(VDP_PLAN_A, FALSE);
		VDP_clearPlan(VDP_PLAN_B, FALSE);
		main_screen();
		break;

	case CHARACTER_SELECTION_SCREEN:
		VDP_clearPlan(VDP_PLAN_A, FALSE);
		VDP_clearPlan(VDP_PLAN_B, FALSE);
		character_selection_screen();
		break;

	case GAME_SCREEN:
		VDP_clearPlan(VDP_PLAN_A, FALSE);
		VDP_clearPlan(VDP_PLAN_B, FALSE);
		game_screen();
		break;

	case OPTIONS_SCREEN:
		VDP_clearPlan(VDP_PLAN_A, FALSE);
		VDP_clearPlan(VDP_PLAN_B, FALSE);
		options_screen();
		break;

	case CREDITS_SCREEN:
		VDP_clearPlan(VDP_PLAN_A, FALSE);
		VDP_clearPlan(VDP_PLAN_B, FALSE);
		credits_screen();
		break;
	}

	VDP_fadeOutAll(20, FALSE);
}


// [4]
void menu_cooldown (u8 multiplier)
{
	u32 lastTick = getTick();

	do
	{
		// Screen change cooldown
		VDP_waitVSync();
	} while (getTick() - lastTick < MENU_COOLDOWN * multiplier);

	JOY_waitPressBtn();
}


// [3]
void main_screen ()
{
	u8 selecting = TRUE;
	s8 choice = 0;
	u16 VALID_DIRECTION = BUTTON_UP | BUTTON_DOWN;

	u8 pos_x = 16;
	u8 pos_y[3] = { 18, 20, 22 };	// "Play", "Options", "Credits"

	// Cooldowns
	u32 now = getTick();
	u32 lastTick = now;

	u16 joypads[PLAYER_COUNT];
	int i = 0;					// Never declare variables inside of loops

	// Draws menu (first time)
	VDP_drawText("Play"   , pos_x    , pos_y[0]);
	VDP_drawText("Options", pos_x    , pos_y[1]);
	VDP_drawText("Credits", pos_x    , pos_y[2]);
	VDP_drawText("->"     , pos_x - 3, pos_y[choice]);

	// Fade in
	VDP_fadeIn(0, 15, roster1.palette->data, 20, FALSE);

	do
	{
		// Draws menu
		VDP_drawText("Play"   , pos_x    , pos_y[0]);
		VDP_drawText("Options", pos_x    , pos_y[1]);
		VDP_drawText("Credits", pos_x    , pos_y[2]);
		VDP_drawText("->"     , pos_x - 3, pos_y[choice]);

		// Player inputs
		joypads[P1_CODE] = JOY_readJoypad(JOY_1);
		joypads[P2_CODE] = JOY_readJoypad(JOY_2);
		now = getTick();
		for (i = 0; i < PLAYER_COUNT; i++)
		{
			if (now - lastTick > MENU_COOLDOWN)
			{
				if (joypads[i] & VALID_DIRECTION)
				{
					lastTick = now;
					VDP_drawText("  ", pos_x - 3, pos_y[choice]); // Clears old arrow

					// UP or DOWN
					if (joypads[i] & BUTTON_UP) choice--;
					else choice++;
				}

				else if (joypads[i] & BUTTON_A) selecting = FALSE;
			}
		}

		// Circular list (overflow / underflow)
		if (choice >= 3) choice = 0;
		else if (choice < 0) choice = 2;

		VDP_waitVSync();
	} while (selecting);

	u8 screen_list [3] = { CHARACTER_SELECTION_SCREEN, OPTIONS_SCREEN, CREDITS_SCREEN };
	set_next_screen(screen_list[choice]);
}


// [4]
void character_selection_screen()
{
//	VDP_setBackgroundColor(8);

	// P1 and P2 choose characters in these positions (from the character list)
	s8 choices[PLAYER_COUNT] = { 0, 0 };

	u8 ready[PLAYER_COUNT] = { FALSE, FALSE };	// Are the players ready or still selecting?
	u8 changed = TRUE;							// Avoid refreshing needlessly
	u8 success = TRUE;							// FALSE when returning to main screen
	u16 joypads[PLAYER_COUNT];

	// Anti-spam 
	s16 VALID_INPUT = BUTTON_LEFT | BUTTON_RIGHT | BUTTON_A | BUTTON_C;
	u32 now = getTick();
	u32 lastTicks[PLAYER_COUNT] = { now, now };

	/**
	 * Displays players's selection cursors in these positions (near the splash arts)
	 *  First index represents the player;
	 *  Second index represents the character chosen (and therefore the cursor position and the splash art)
	 */
	u16 pos_x[PLAYER_COUNT][CHARACTER_LIST_SIZE] = { { 192, 312 } , { 232, 352 } };
	u16 pos_y = 280;
	u16 pos_y_ready = 272;	// When ready, the cursor goes up (towards the splash art)

	u16 preview_x[PLAYER_COUNT] = { 144, 432 };
	u16 preview_y = 310;

	// Splash arts
	VDP_clearPlan(VDP_PLAN_B, FALSE);
	VDP_drawImageEx(BPLAN, &select_char, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX+16 ), 4, 1, FALSE, TRUE);
	VDP_drawImageEx(BPLAN, &roster1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX+144 ), 8, 5, FALSE, TRUE);
	VDP_drawImageEx(BPLAN, &roster4, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX+400), 23, 5, FALSE, TRUE);

	// Cursors as sprites
	Sprite sprites[4];
	SPR_initSprite(&sprites[P1_CODE], &p1_text, pos_x[P1_CODE][choices[P1_CODE]], pos_y, TILE_ATTR(PAL0, 1, 0, 0));
	SPR_initSprite(&sprites[P2_CODE], &p2_text, pos_x[P2_CODE][choices[P2_CODE]], pos_y, TILE_ATTR(PAL0, 1, 0, 0));

	SPR_initSprite(&sprites[P1_CODE+2], &spr_knight_def, preview_x[P1_CODE], preview_y, TILE_ATTR(PAL1, 1, 0, 0));
	SPR_initSprite(&sprites[P2_CODE+2], &spr_wizard_def  , preview_x[P2_CODE], preview_y, TILE_ATTR(PAL2, 1, 0, TRUE));

	// Updating cursor positions (init_Sprite sometimes does not work)
	sprites[P1_CODE].x = pos_x[P1_CODE][choices[P1_CODE]];
	sprites[P1_CODE].y = pos_y;
	sprites[P2_CODE].x = pos_x[P2_CODE][choices[P2_CODE]];
	sprites[P2_CODE].y = pos_y;

	sprites[P1_CODE+2].x = preview_x[P1_CODE];
	sprites[P1_CODE+2].y = preview_y;
	sprites[P2_CODE+2].x = preview_x[P2_CODE];
	sprites[P2_CODE+2].y = preview_y;
	SPR_setAnim(&sprites[P1_CODE+2], 3);
	SPR_setAnim(&sprites[P2_CODE+2], 0);
	SPR_update(sprites, 4);

	// Fade In
	u16 palettes [64];
	memcpy(&palettes[0],  roster1.palette->data, 2 * 16);
	memcpy(&palettes[16], spr_knight_def.palette->data, 2 * 16);
	memcpy(&palettes[32], spr_wizard_def.palette->data, 2 * 16);

	VDP_fadeIn(0, 3 * 16 - 1, palettes, 20, FALSE);

//	VDP_fadeIn(0, 15, roster1.palette->data, 20, FALSE);

	// Selection loop (until both are ready)
	do
	{
		joypads[P1_CODE] = JOY_readJoypad(JOY_1);
		joypads[P2_CODE] = JOY_readJoypad(JOY_2);
		now = getTick();
		
		// Process inputs for each player
		int i = 0;
		for (i = 0; i < PLAYER_COUNT; i++)
		{
			if (now - lastTicks[i] > MENU_COOLDOWN)
			{
				// Only B key available when ready
				if (ready[i])
				{
					if (joypads[i] & BUTTON_B)
					{
						lastTicks[i] = getTick(); // Cooldown
						ready[i] = FALSE;
						sprites[i].y = pos_y;
						changed = TRUE;
					}
				}

				// Still selecting
				else
				{
					// Valid input = Cooldown refresh
					if (joypads[i] & VALID_INPUT)
					{
						lastTicks[i] = getTick(); // Cooldown

						// Moves cursor
						if      (joypads[i] & BUTTON_LEFT)  choices[i]--;
						else if (joypads[i] & BUTTON_RIGHT) choices[i]++;

						// Ready
						else if (joypads[i] & BUTTON_A)
						{
							ready[i] = TRUE;
							sprites[i].y = pos_y_ready;
						}

						// Back to main screen
						else if (joypads[i] & BUTTON_C)
						{
							set_next_screen(MAIN_SCREEN);
							success = FALSE;
							ready[P1_CODE] = TRUE;
							ready[P2_CODE] = TRUE;
							break;
						}

						// Circular list (overflow / underflow)
						if (choices[i] >= CHARACTER_LIST_SIZE) choices[i] = 0;
						else if (choices[i] < 0) choices[i] = CHARACTER_LIST_SIZE - 1;

						// Updates cursor
						sprites[i].x = pos_x[i][choices[i]];
						changed = TRUE;
					}
				}

			}
		}

		if (changed)
		{
			changed = FALSE;
		}

		SPR_update(sprites, 4);
		VDP_waitVSync();
	} while (!(ready[P1_CODE] && ready[P2_CODE]));

	SPR_clear();

	// Fails when player press B "twice" (unselected B)
	if (success)
	{
		pick_character(P1_CODE, choices[P1_CODE]);
		pick_character(P2_CODE, choices[P2_CODE]);
		set_next_screen(GAME_SCREEN);
	}
}


// [5]
void game_screen ()
{
//	VDP_clearPlan(APLAN, FALSE);
//	VDP_clearPlan(BPLAN, FALSE);

	#define BALL_CODE 3
	#define P1_START_X 210
	#define P2_START_X 330
	#define START_Y 240
	#define CENTER_X 160
	#define CENTER_Y 120
	#define HP_P1_X(index) (1 + 2*index)
	#define HP_P2_X(index) (37 - 2*index)

	Sprite sprites [PLAYER_COUNT + 1]; // Players and the ball

	// Arena
	draw_arena();

	// GUI (HPs)
	int i = 0;
	for ( i = 0; i < player(P1_CODE).hp; i++ ) {
		VDP_drawImageEx(APLAN, &spr_hp_def, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX+16 ), HP_P1_X(i), 1, FALSE, TRUE);
	}
	for ( i = 0; i < player(P2_CODE).hp; i++ ) {
		VDP_drawImageEx(APLAN, &spr_hp_def, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX+16 ), HP_P2_X(i), 1, FALSE, TRUE);
	}

	// Players
	SPR_initSprite(&sprites[P1_CODE], ch_sprite(ch_code(P1_CODE)), P1_START_X, START_Y, TILE_ATTR(PAL1, 1, 0, 0));
	SPR_initSprite(&sprites[P2_CODE], ch_sprite(ch_code(P2_CODE)), P2_START_X, START_Y, TILE_ATTR(PAL2, 1, 0, 0));
	sprites[P1_CODE].x = P1_START_X;
	sprites[P1_CODE].y = START_Y;
	sprites[P2_CODE].x = P2_START_X;
	sprites[P2_CODE].y = START_Y;
	SPR_setAnim(&sprites[P1_CODE], ANIM_IDLE_R);
	SPR_setAnim(&sprites[P2_CODE], ANIM_IDLE_L);

	// TODO Ball
//	SPR_initSprite(&sprites[BALL_CODE], &spr_hp_def, CENTER_X, CENTER_Y, TILE_ATTR(PAL0, 1, 0, 0));
//	sprites[P2_CODE].x = CENTER_X;
//	sprites[P2_CODE].y = CENTER_Y;

	SPR_update(sprites, 2);

	u16 palettes [64];
	memcpy(&palettes[0],  spr_hp_def.palette->data, 2 * 16);
	memcpy(&palettes[16], ch_sprite(ch_code(P1_CODE))->palette->data, 2 * 16);
	memcpy(&palettes[32], ch_sprite(ch_code(P2_CODE))->palette->data, 2 * 16);
	memcpy(&palettes[48], tileset_arena.palette->data, 2 * 16);

	VDP_fadeIn(0, 4 * 16 - 1, palettes, 20, FALSE);

	while (TRUE)
	{
		SPR_update(sprites, 2);
		VDP_waitVSync();
	}
}


// [6]
void options_screen ()
{
	u8 pos_x = 0;
	u8 pos_y = 10;

	VDP_drawText("     Options will be available here     ", pos_x, pos_y);
	VDP_fadeIn(0, 15, roster1.palette->data, 20, FALSE);

	menu_cooldown(4);
	set_next_screen(MAIN_SCREEN);
}


// [7]
void credits_screen ()
{
	u8 pos_x = 0;
	u8 pos_y = 2;

	VDP_drawText(" ----- Deflection (2016, Jun-Aug) ----- ", pos_x, pos_y  );
	VDP_drawText("  This is the final project of a subject", pos_x, pos_y+2);
	VDP_drawText("from Universidade Federal do Ceara (UFC)", pos_x, pos_y+3);
	VDP_drawText("         Brazil, CE, Fortaleza          ", pos_x, pos_y+4);

	VDP_drawText("     Open source code available at:     ", pos_x, pos_y+6);
	VDP_drawText("     https://github.com/                ", pos_x, pos_y+7);
	VDP_drawText("            FlavioFS/JMP-Deflection     ", pos_x, pos_y+8);

	VDP_drawText("     Professor Advisor: Gilvan Maia     ", pos_x, pos_y+10);
	VDP_drawText(" Department of Systems and Digital Media", pos_x, pos_y+11);

	VDP_drawText("    ----- Programming and Art -----     ", pos_x, pos_y+14);
	VDP_drawText("     Department of Computer Science     ", pos_x, pos_y+16);
	VDP_drawText("       * Flavio Freitas de Sousa        ", pos_x, pos_y+17);
	VDP_drawText("         (flaviofreitas.h@gmail.com)    ", pos_x, pos_y+18);
	VDP_drawText("          + Knight character            ", pos_x, pos_y+19);
	VDP_drawText("          + Splash arts                 ", pos_x, pos_y+20);

	VDP_drawText("       * Lucas Falcao                   ", pos_x, pos_y+22);
//	VDP_drawText("         (your email here          )    ", pos_x, pos_y+19);
	VDP_drawText("          + Wizard character            ", pos_x, pos_y+23);

	VDP_fadeIn(0, 15, roster1.palette->data, 20, FALSE);

	menu_cooldown(4);
	set_next_screen(MAIN_SCREEN);
}


// TODO remove this?
/**
 * TRUE:  match over
 * FALSE: match continues
 */
void faint (PlayerData * p, u8 * match_over)
{
	p->hp--;

	if (p->hp == 0)
	{
		*match_over = TRUE;
		// Freeze game
		return;
	}

	// Round over, reset positions
}
