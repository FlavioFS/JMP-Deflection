#include "screens.h"

u8 next_screen = MAIN_SCREEN;

// TODO Remove lastTick
//u32 lastTick;

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


// [3]
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


// [4]
void main_screen ()
{
	u8 selecting = TRUE;
	short choice = 0;
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


// [5]
void character_selection_screen()
{
//	VDP_setBackgroundColor(8);

	// P1 and P2 choose characters in these positions (from the character list)
	short choices[PLAYER_COUNT] = { KNIGHT_CODE, WIZARD_CODE };

	u8 ready[PLAYER_COUNT] = { FALSE, FALSE };	// Are the players ready or still selecting?
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

	u16 preview_x[PLAYER_COUNT] = { 144, 402 };
	u16 preview_y = 310;


	// Splash arts
	VDP_clearPlan(VDP_PLAN_B, FALSE);
	VDP_drawImageEx(BPLAN, &select_char, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX+16 ), 4, 1, FALSE, TRUE);
	VDP_drawImageEx(BPLAN, &roster1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX+144 ), 8, 5, FALSE, TRUE);
	VDP_drawImageEx(BPLAN, &roster4, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX+400), 23, 5, FALSE, TRUE);

	// Cursors as sprites
	Sprite sprites[6];
	SPR_initSprite(&sprites[P1_CODE], &p1_text, pos_x[P1_CODE][choices[P1_CODE]], pos_y, TILE_ATTR(PAL0, 1, 0, 0));
	SPR_initSprite(&sprites[P2_CODE], &p2_text, pos_x[P2_CODE][choices[P2_CODE]], pos_y, TILE_ATTR(PAL0, 1, 0, 0));

	SPR_initSprite(&sprites[P1_CODE+2], &spr_knight_def, preview_x[P1_CODE], preview_y, TILE_ATTR(PAL1, 1, 0, 0));
	SPR_initSprite(&sprites[P2_CODE+2], &spr_knight_def, preview_x[P2_CODE], preview_y, TILE_ATTR(PAL1, 1, 0, 0));
	SPR_initSprite(&sprites[P1_CODE+4], &spr_wizard_def, preview_x[P1_CODE], preview_y, TILE_ATTR(PAL2, 1, 0, 0));
	SPR_initSprite(&sprites[P2_CODE+4], &spr_wizard_def, preview_x[P2_CODE], preview_y, TILE_ATTR(PAL2, 1, 0, TRUE));

	SPR_setNeverVisible(&sprites[P1_CODE+2], choices[P1_CODE]);
	SPR_setNeverVisible(&sprites[P2_CODE+2], choices[P2_CODE]);
	SPR_setNeverVisible(&sprites[P1_CODE+4], 1-choices[P1_CODE]);
	SPR_setNeverVisible(&sprites[P2_CODE+4], 1-choices[P2_CODE]);

	// Updating cursor positions (init_Sprite sometimes does not work)
	sprites[P1_CODE].x = pos_x[P1_CODE][choices[P1_CODE]];
	sprites[P1_CODE].y = pos_y;
	sprites[P2_CODE].x = pos_x[P2_CODE][choices[P2_CODE]];
	sprites[P2_CODE].y = pos_y;

	sprites[P1_CODE+2].x = preview_x[P1_CODE];
	sprites[P1_CODE+2].y = preview_y;
	sprites[P1_CODE+4].x = preview_x[P1_CODE];
	sprites[P1_CODE+4].y = preview_y;

	sprites[P2_CODE+2].x = preview_x[P2_CODE];
	sprites[P2_CODE+2].y = preview_y;
	sprites[P2_CODE+4].x = preview_x[P2_CODE];
	sprites[P2_CODE+4].y = preview_y;

	SPR_setAnim(&sprites[P1_CODE+2], 3);
	SPR_setAnim(&sprites[P1_CODE+4], 3);
	SPR_setAnim(&sprites[P2_CODE+2], 2);
	SPR_setAnim(&sprites[P2_CODE+4], 2);
	SPR_update(sprites, 6);

	// Fade In
	u16 palettes [64];
	memcpy(&palettes[0],  p2_text.palette->data, 2 * 16);
	memcpy(&palettes[16], spr_knight_def.palette->data, 2 * 16);
	memcpy(&palettes[32], spr_wizard_def.palette->data, 2 * 16);

	VDP_fadeIn(0, 3 * 16 - 1, palettes, 20, FALSE);

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
						if (joypads[i] & (BUTTON_LEFT | BUTTON_RIGHT))
						{
							if      (joypads[i] & BUTTON_LEFT)  choices[i]--;
							else if (joypads[i] & BUTTON_RIGHT) choices[i]++;

							// Circular list (overflow / underflow)
							if (choices[i] >= CHARACTER_LIST_SIZE) choices[i] = 0;
							else if (choices[i] < 0) choices[i] = CHARACTER_LIST_SIZE - 1;

							// Updates cursor
							sprites[i].x = pos_x[i][choices[i]];

							// TODO Find a better way to replace sprites
							SPR_setNeverVisible(&sprites[i + 2], choices[i]);
							SPR_setNeverVisible(&sprites[i + 4], 1-choices[i]);
						}

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
					}
				}

			}
		}


		SPR_update(sprites, 6);
		VDP_waitVSync();
	} while (!(ready[P1_CODE] && ready[P2_CODE]));

	SPR_clear();

	// Fails when player press B "twice" (unselected B)
	if (success)
	{
		PL_pickCharacter(P1_CODE, choices[P1_CODE]);
		PL_pickCharacter(P2_CODE, choices[P2_CODE]);
		SPR_clear();
		set_next_screen(GAME_SCREEN);
	}
}


// [6]
void game_screen ()
{
	#define BALL_CODE 3
	#define P1_START_X 210
	#define P2_START_X 330
	#define START_Y 240
	#define CENTER_X 278
	#define CENTER_Y 248
	#define HP_P1_X(index) (1 + 2*index)
	#define HP_P2_X(index) (37 - 2*index)

	Sprite sprites [PLAYER_COUNT + 1]; // Players and the ball

	/////////////////////////////////////////////////////////////
	/**
	 *  This is a NESTED joy handler, so it can access the variable "sprites"
	 */
	void joyNonDirectional ( u16 joy, u16 changed, u16 state )
	{
		if (joy == JOY_1)
		{
			// START button state changed
			if (changed & BUTTON_START)
			{
				// Pause game
			}

			if (changed & state)
			{
				if ( state & ( BUTTON_A | BUTTON_B | BUTTON_C ) )
				{
					PlayerData * player = PL_player(P1_CODE);

					// Already attacking
					if ( getTick() - player->last_attack < CHL_cd(player->char_code) ) return;
					PL_attack(P1_CODE);

					u8 lastDir = player->last_direction;
					if      (lastDir == ANIM_IDLE_U) SPR_setAnim(&sprites[P1_CODE], ANIM_ATK_L);
					else if (lastDir == ANIM_IDLE_D) SPR_setAnim(&sprites[P1_CODE], ANIM_ATK_R);
					else if (lastDir == ANIM_IDLE_L) SPR_setAnim(&sprites[P1_CODE], ANIM_ATK_L);
					else if (lastDir == ANIM_IDLE_R) SPR_setAnim(&sprites[P1_CODE], ANIM_ATK_R);
				}
			}
		}

		else if (joy == JOY_2)
		{
			// START button state changed
			if (changed & BUTTON_START)
			{
				// Pause game
			}

			if (changed & state)
			{
				if ( state & ( BUTTON_A | BUTTON_B | BUTTON_C ) )
				{
					PlayerData * player = PL_player(P2_CODE);

					// Already attacking
					if ( getTick() - player->last_attack < CHL_cd(player->char_code) ) return;
					PL_attack(P2_CODE);

					u8 lastDir = player->last_direction;
					if      (lastDir == ANIM_IDLE_U) SPR_setAnim(&sprites[P2_CODE], ANIM_ATK_L);
					else if (lastDir == ANIM_IDLE_D) SPR_setAnim(&sprites[P2_CODE], ANIM_ATK_R);
					else if (lastDir == ANIM_IDLE_L) SPR_setAnim(&sprites[P2_CODE], ANIM_ATK_L);
					else if (lastDir == ANIM_IDLE_R) SPR_setAnim(&sprites[P2_CODE], ANIM_ATK_R);
				}
			}
		}
	}
	// The joy handler ends here
	/////////////////////////////////////////////////////////////

	// Arena
	draw_arena();

	// GUI (HPs)
	int i = 0;
	for ( i = 0; i < PL_hp(P1_CODE); i++ ) {
		VDP_drawImageEx(APLAN, &spr_hp_def, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX+16 ), HP_P1_X(i), 0, FALSE, TRUE);
	}
	for ( i = 0; i < PL_hp(P2_CODE); i++ ) {
		VDP_drawImageEx(APLAN, &spr_hp_def, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX+16 ), HP_P2_X(i), 0, FALSE, TRUE);
	}

	// Players
	SPR_initSprite(&sprites[P1_CODE], CHL_chSprite(PL_chCode(P1_CODE)), P1_START_X, START_Y, TILE_ATTR(PAL1, 1, 0, 0));
	SPR_initSprite(&sprites[P2_CODE], CHL_chSprite(PL_chCode(P2_CODE)), P2_START_X, START_Y, TILE_ATTR(PAL2, 1, 0, 0));
	sprites[P1_CODE].x = P1_START_X;
	sprites[P1_CODE].y = START_Y;
	sprites[P2_CODE].x = P2_START_X;
	sprites[P2_CODE].y = START_Y;
	SPR_setAnim(&sprites[P1_CODE], ANIM_IDLE_R);
	SPR_setAnim(&sprites[P2_CODE], ANIM_IDLE_L);

	// TODO Ball
	SPR_initSprite(&sprites[BALL_CODE], &spr_ball_def, CENTER_X, CENTER_Y, TILE_ATTR(PAL1, 1, 0, 0));
	sprites[BALL_CODE].x = CENTER_X;
	sprites[BALL_CODE].y = CENTER_Y;
	SPR_setAnim(&sprites[BALL_CODE], 0); // Onle one animation for the ball

	SPR_update(sprites, 4);

	u16 palettes [64];
	memcpy(&palettes[0],  spr_hp_def.palette->data, 2 * 16);
	memcpy(&palettes[16], CHL_chSprite(PL_chCode(P1_CODE))->palette->data, 2 * 16);
	memcpy(&palettes[32], CHL_chSprite(PL_chCode(P2_CODE))->palette->data, 2 * 16);
	memcpy(&palettes[48], tileset_arena.palette->data, 2 * 16);

	JOY_setEventHandler(joyNonDirectional);

	VDP_fadeIn(0, 4 * 16 - 1, palettes, 20, FALSE);

	while (TRUE)
	{
		control_char(&sprites[P1_CODE], P1_CODE, JOY_1);
		control_char(&sprites[P2_CODE], P2_CODE, JOY_2);
		SPR_update(sprites, 4);
		VDP_waitVSync();
	}

	JOY_setEventHandler(emptyJoyHandler);

}


// [7]
void options_screen ()
{
	u8 pos_x = 0;
	u8 pos_y = 10;

	VDP_drawText("     Options will be available here     ", pos_x, pos_y);
	VDP_fadeIn(0, 15, roster1.palette->data, 20, FALSE);

	menu_cooldown(4);
	set_next_screen(MAIN_SCREEN);
}


// [8]
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


// TODO setar isso depois do jogo
void emptyJoyHandler ( u16 joy, u16 changed, u16 state )
{

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
