/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

__declspec(dllexport) int cdecl main_tile_cur()
{
	return tile_cur;
}

__declspec(dllexport) int cdecl main_CurMode()
{
	return CurMode;
}

__declspec(dllexport) int cdecl main_activeChara()
{
	return activeChara;
}

__declspec(dllexport) int cdecl main_WindDir()
{
	return WindDir;
}

__declspec(dllexport) int cdecl main_D_96F8()
{
	return D_96F8;
}

__declspec(dllexport) int cdecl main_D_946C()
{
	return D_946C;
}

__declspec(dllexport) int cdecl main_D_95A5_x()
{
	return D_95A5.x;
}

__declspec(dllexport) int cdecl main_D_95A5_y()
{
	return D_95A5.y;
}

__declspec(dllexport) int cdecl main_D_9445()
{
	return D_9445;
}

__declspec(dllexport) int cdecl main_D_9448()
{
	return D_9448;
}

__declspec(dllexport) int cdecl main_D_9141()
{
	return D_9141;
}

__declspec(dllexport) int cdecl main_SoundFlag()
{
	return SoundFlag;
}

extern unsigned D_17FA;/*current opened door's x*/
extern unsigned D_17FC;/*current opened door's y*/
extern unsigned D_17FE;/*current opened door's delay*/

__declspec(dllexport) int cdecl main_D_17FA()
{
	return D_17FA;
}

__declspec(dllexport) int cdecl main_D_17FC()
{
	return D_17FC;
}

__declspec(dllexport) int cdecl main_D_17FE()
{
	return D_17FE;
}

__declspec(dllexport) int cdecl main_spell_sta()
{
	return spell_sta;
}

__declspec(dllexport) void cdecl main_ActiveChar(unsigned char buffer[], int length)
{
	if (length >= 3)
	{
		buffer[0] = activeChara;
		buffer[1] = activeCharaX; // activeCharaX = -1 means inactive
		buffer[2] = activeCharaY;
	}
}

__declspec(dllexport) void cdecl  main_CurMap(unsigned char buffer[], int length)
{
	if (length >= sizeof(D_8742))
	{
		memcpy(buffer, &D_8742, sizeof(D_8742));
	}
}

extern char char_highlight[8];

__declspec(dllexport) void cdecl  main_char_highlight(unsigned char buffer[], int length)
{
	if (length >= sizeof(char_highlight))
	{
		memcpy(buffer, &char_highlight, sizeof(char_highlight));
	}
}

__declspec(dllexport) void cdecl  main_Party(unsigned char buffer[], int length)
{
	if (length >= sizeof(Party))
	{
		memcpy(buffer, &Party, sizeof(Party));
	}
}

__declspec(dllexport) void cdecl  main_Combat(unsigned char buffer[], int length)
{
	if (length >= sizeof(Combat))
	{
		memcpy(buffer, &Combat, sizeof(Combat));
	}
}

__declspec(dllexport) void cdecl  main_Fighters(unsigned char buffer[], int length)
{
	if (length >= sizeof(Fighters))
	{
		memcpy(buffer, &Fighters, sizeof(Fighters));
	}
}
__declspec(dllexport) void cdecl  main_D_96F9(unsigned char buffer[], int length)
{
	if (length >= sizeof(D_96F9))
	{
		memcpy(buffer, &D_96F9, sizeof(D_96F9));
	}
}

// remember the last 10 hits, in a circular buffer
#define MAX_HITS 10
char hit_list_buffer[3 * MAX_HITS + 2]; // extra bytes to make sure we don't overrun the buffer
hit_list_size = 0;
current_hit_list = 0;

void add_to_hit_list()
{
	if (hit_tile)
	{
		//printf("Hit Tile %d (%d, %d)\n", hit_tile, hit_x, hit_y);
		hit_list_buffer[current_hit_list++] = hit_tile;
		hit_list_buffer[current_hit_list++] = hit_x;
		hit_list_buffer[current_hit_list++] = hit_y;
		if (current_hit_list > 3 * MAX_HITS - 1)
		{
			current_hit_list = 0;
		}
		hit_list_size++;
		if (hit_list_size > MAX_HITS)
		{
			hit_list_size = MAX_HITS;
		}
	}
}

#define MAX_TEXT 500
char text_buffer[MAX_TEXT];
int current_text_buffer_pointer;
int current_text_buffer_size;

void add_char_to_text_buffer(char ch)
{
	//printf("%c", ch);
	text_buffer[current_text_buffer_pointer++] = ch;
	if (current_text_buffer_pointer > MAX_TEXT - 1)
	{
		current_text_buffer_pointer = 0;
	}
	current_text_buffer_size++;
	if (current_text_buffer_size > MAX_TEXT)
	{
		current_text_buffer_size = MAX_TEXT;
	}
}

__declspec(dllexport) int cdecl  main_Text(unsigned char buffer[], int length)
{
	int buffer_index = 0;
	int ret = 0;

	if (length >= current_text_buffer_size)
	{
		ret = current_text_buffer_size;

		//printf("Text buffer size %d\n", current_text_buffer_size);

		// we have not filled the text buffer
		if (current_text_buffer_size < MAX_TEXT - 1)
		{
			for (int i = 0; i < current_text_buffer_size; i++)
			{
				buffer[buffer_index++] = text_buffer[i];
			}
		}
		// the text buffer is full dump from the wrap
		else
		{
			for (int i = 0; i < current_text_buffer_size; i++)
			{
				buffer[buffer_index++] = text_buffer[current_text_buffer_pointer++];

				// wrap
				if (current_text_buffer_pointer > MAX_TEXT - 1)
				{
					current_text_buffer_pointer = 0;
				}
			}
		}

		// empty the text buffer
		current_text_buffer_size = 0;
		current_text_buffer_pointer = 0;
		//printf("text buffer cleared\n");
	}

	return ret;
}

void Text_Dump()
{
	int buffer_index = 0;
	int ret = 0;

	//printf("Text buffer size %d\n", current_text_buffer_size);

	// we have not filled the text buffer
	if (current_text_buffer_size < MAX_TEXT - 1)
	{
		for (int i = 0; i < current_text_buffer_size; i++)
		{
			printf("%c", text_buffer[i]);
		}
	}
	// the text buffer is full dump from the wrap
	else
	{
		for (int i = 0; i < current_text_buffer_size; i++)
		{
			printf("%c", text_buffer[current_text_buffer_pointer++]);

			// wrap
			if (current_text_buffer_pointer > MAX_TEXT - 1)
			{
				current_text_buffer_pointer = 0;
			}
		}
	}

	// empty the text buffer
	current_text_buffer_size = 0;
	current_text_buffer_pointer = 0;
	printf("text buffer cleared\n");
}

#define MAX_TEXT 500
#define MAX_NPC_TEXT 10
char npc_text_buffer[10][MAX_TEXT];
int current_npc_text_buffer_pointer = 0;
int current_npc_text_buffer_size = 0;

void npc_string_copy(char * dst, char * src)
{
	int index = 0;
	for (int i = 0; i < strnlen(src, MAX_TEXT - 1); i++)
	{
		if (src[i] != '\n')
		{
			if (src[i] == '\x12') // remove these
			{
				continue;
			}
			else if (src[i] == '\b') // replace breaks with spaces
			{
				dst[index++] = ' ';
				continue;
			}
			else
			{
				dst[index++] = src[i];
			}
		}
		else if (src[i] == '\n' && src[i + 1] == 0)
		{
			dst[index++] = '\n';
		}
		else if ((src[i] == '\n') && ((i != 0) && (i != 1) && (i != 2))) // remove leading newlines
		{
			if ((i > 1) && (src[i - 1] != '\n')) // remove multiple newlines
			{
				dst[index++] = ' ';
			}
		}
	}

	// terminate the string if we cut out some characters
	dst[index] = 0;
}

void add_npc_talk_long(char npc_index, long number)
{
	npc_text_buffer[current_npc_text_buffer_pointer][0] = npc_index;
	npc_text_buffer[current_npc_text_buffer_pointer][1] = 0;

	snprintf(&npc_text_buffer[current_npc_text_buffer_pointer][1], 10, "%l", number);

	current_npc_text_buffer_pointer++;
	if (current_npc_text_buffer_pointer > MAX_NPC_TEXT - 1)
	{
		current_npc_text_buffer_pointer = 0;
	}
	current_npc_text_buffer_size++;
	if (current_npc_text_buffer_size > MAX_NPC_TEXT)
	{
		current_npc_text_buffer_size = MAX_NPC_TEXT;
	}
}

int input_mode = 0;

void set_input_mode(int mode)
{
	input_mode = mode;
}

int zstats_mode = 0;

void set_zstats_mode(int mode)
{
	zstats_mode = mode;
}

int zstats_character = 0;

void set_zstats_character(int character)
{
	zstats_character = character;
}

void add_npc_talk(char npc_index, char * ch)
{
	npc_text_buffer[current_npc_text_buffer_pointer][0] = npc_index;

	npc_string_copy(&npc_text_buffer[current_npc_text_buffer_pointer][1], ch);

	printf(&npc_text_buffer[current_npc_text_buffer_pointer][1]);

	current_npc_text_buffer_pointer++;
	if (current_npc_text_buffer_pointer > MAX_NPC_TEXT - 1)
	{
		current_npc_text_buffer_pointer = 0;
	}
	current_npc_text_buffer_size++;
	if (current_npc_text_buffer_size > MAX_NPC_TEXT)
	{
		current_npc_text_buffer_size = MAX_NPC_TEXT;
	}
}

void NPC_Text_Dump()
{
	int buffer_index = 0;
	int ret = 0;

	//printf("\nnpc Text buffer size %d\n", current_npc_text_buffer_size);

	// we have not filled the text buffer
	if (current_npc_text_buffer_size < MAX_NPC_TEXT - 1)
	{
		for (int i = 0; i < current_npc_text_buffer_size; i++)
		{
			//printf(&npc_text_buffer[i][1]);
			//printf("npc index %d says : %s\n", npc_text_buffer[i][0], &npc_text_buffer[i][1]);
		}
	}
	// the text buffer is full dump from the wrap
	else
	{
		for (int i = 0; i < current_npc_text_buffer_size; i++)
		{
			//printf(&npc_text_buffer[current_npc_text_buffer_pointer][1]);
			//printf("npc index %d says : %s\n", npc_text_buffer[current_npc_text_buffer_pointer][0], &npc_text_buffer[current_npc_text_buffer_pointer][1]);
			current_npc_text_buffer_pointer++;

			// wrap
			if (current_npc_text_buffer_pointer > MAX_NPC_TEXT - 1)
			{
				current_npc_text_buffer_pointer = 0;
			}
		}
	}

	// empty the text buffer
	current_npc_text_buffer_size = 0;
	current_npc_text_buffer_pointer = 0;
	//printf("\nnpc text buffer cleared\n");
}

__declspec(dllexport) int cdecl  main_NPC_Text(unsigned char buffer[], int length)
{
	int ret = 0;

	if (length < sizeof(npc_text_buffer))
		return;

	if (buffer == 0)
		return;

	ret = current_npc_text_buffer_size;

	// we have not filled the text buffer
	if (current_npc_text_buffer_size < MAX_NPC_TEXT - 1)
	{
		for (int i = 0; i < current_npc_text_buffer_size; i++)
		{
			//printf(&npc_text_buffer[i][1]);
			memcpy(&buffer[i * 500], npc_text_buffer[i], MAX_TEXT);
			//printf("npc index %d says : %s\n", npc_text_buffer[i][0], &npc_text_buffer[i][1]);
		}
	}
	// the text buffer is full dump from the wrap
	else
	{
		for (int i = 0; i < current_npc_text_buffer_size; i++)
		{
			//printf(&npc_text_buffer[current_npc_text_buffer_pointer][1]);
			//printf("npc index %d says : %s\n", npc_text_buffer[current_npc_text_buffer_pointer][0], &npc_text_buffer[current_npc_text_buffer_pointer][1]);
			memcpy(&buffer[i * MAX_TEXT], npc_text_buffer[current_npc_text_buffer_pointer], MAX_TEXT);
			current_npc_text_buffer_pointer++;

			// wrap
			if (current_npc_text_buffer_pointer > MAX_NPC_TEXT - 1)
			{
				current_npc_text_buffer_pointer = 0;
			}
		}
	}
	
	// empty the text buffer
	current_npc_text_buffer_size = 0;
	current_npc_text_buffer_pointer = 0;

	return ret;
}

void Hit_Dump()
{
	//printf("Hit list size %d\n", hit_list_size);

	// we have not filled the hit list
	if (hit_list_size < MAX_HITS - 1)
	{
		for (int i = 0; i < hit_list_size; i++)
		{
			int tile = hit_list_buffer[i * 3 + 0];
			int x = hit_list_buffer[i * 3 + 1];
			int y = hit_list_buffer[i * 3 + 2];
			//printf("Hit Tile %d (%d, %d)\n", tile, x, y);
		}
	}
	// the hit list is full dump from the wrap
	else
	{
		for (int i = 0; i < hit_list_size; i++)
		{
			int tile = hit_list_buffer[current_hit_list++];
			int x = hit_list_buffer[current_hit_list++];
			int y = hit_list_buffer[current_hit_list++];
			//printf("Hit Tile %d (%d, %d)\n", tile, x, y);

			// wrap
			if (current_hit_list > 3 * MAX_HITS - 1)
			{
				current_hit_list = 0;
			}
		}
	}

	// empty the hit list
	hit_list_size = 0;
	current_hit_list = 0;
	//printf("Hit list cleared\n");
}

__declspec(dllexport) void cdecl  main_Hit(unsigned char buffer[], int length)
{
	int buffer_index = 0;

	if (length >= 4)
	{
		buffer[buffer_index++] = hit_list_size;

		//printf("Hit list size %d\n", hit_list_size);

		// we have not filled the hit list
		if (hit_list_size < MAX_HITS - 1)
		{
			for (int i = 0; i < hit_list_size; i++)
			{
				buffer[buffer_index++] = hit_list_buffer[i * 3 + 0];
				buffer[buffer_index++] = hit_list_buffer[i * 3 + 1];
				buffer[buffer_index++] = hit_list_buffer[i * 3 + 2];
			}
		}
		// the hit list is full dump from the wrap
		else
		{
			for (int i = 0; i < hit_list_size; i++)
			{
				buffer[buffer_index++] = hit_list_buffer[current_hit_list++];
				buffer[buffer_index++] = hit_list_buffer[current_hit_list++];
				buffer[buffer_index++] = hit_list_buffer[current_hit_list++];

				// wrap
				if (current_hit_list > 3 * MAX_HITS - 1)
				{
					current_hit_list = 0;
				}
			}
		}

		// empty the hit list
		hit_list_size = 0;
		current_hit_list = 0;
		//printf("Hit list cleared\n");
	}
}

int current_sound_effect = -1;
int current_sound_effect_length = 0;

void play_sound_effect(unsigned char sound, unsigned char length)
{
	int timeout = 1000;

	current_sound_effect = sound;
	current_sound_effect_length  = length;

#ifndef ENABLE_WINDOWS
	// wait for the sound effect to finish playing
	while (current_sound_effect != -1 && timeout > 0)
	{
		timeout--;
		Sleep(20);
	}
#endif

	current_sound_effect = -1;
	current_sound_effect_length = 0;
}

__declspec(dllexport) int cdecl  main_sound_effect()
{
	return current_sound_effect;
}

__declspec(dllexport) int cdecl  main_input_mode()
{
	return input_mode;
}
__declspec(dllexport) int cdecl  main_zstats_mode()
{
	return zstats_mode;
}
__declspec(dllexport) int cdecl  main_zstats_character()
{
	return zstats_character;
}
__declspec(dllexport) int cdecl  main_sound_effect_length()
{
	return current_sound_effect_length;
}

__declspec(dllexport) void cdecl  main_sound_effect_done()
{
	current_sound_effect = -1;
}

extern int screen_xor_state;

__declspec(dllexport) int cdecl  main_screen_xor_state()
{
	return screen_xor_state;
}

extern int camera_shake_accumulator;

__declspec(dllexport) int cdecl  main_camera_shake_accumulator()
{
	int ret = camera_shake_accumulator;

	// reset accumulator to collect more shaking
	camera_shake_accumulator = 0;

	// return what we have accumulated
	return ret;
}

extern unsigned char D_1665;/*trammel counter*/
extern unsigned char D_1666;/*felucca counter*/

__declspec(dllexport) int cdecl  main_D_1665()
{
	return D_1665;
}

__declspec(dllexport) int cdecl  main_D_1666()
{
	return D_1666;
}

static char U4_ROOT[256] = "C:\\Users\\Jim\\AppData\\LocalLow\\SwivelChairGames\\ANHK-VR\\u4\\";

const char* getDataPath()
{
	return &U4_ROOT[0];
}

__declspec(dllexport) void cdecl main_SetDataPath(unsigned char path[], int length)
{
	// is the path too big for our buffer + null terminator?
	if (length > 255)
	{
		// just bail
		return;
	}

	// save the path from the controlling application
	strncpy(U4_ROOT, path, length);

	U4_ROOT[length] = 0; // make sure it's null terminated
}


static char current_vision[256] = "";

const char* get_current_vision()
{
	return &current_vision[0];
}

__declspec(dllexport) void cdecl main_GetVision(unsigned char vision[], int length)
{
	// is the vision too big for our buffer + null terminator?
	if (length < 256)
	{
		// just bail
		return;
	}

	// return the vision to the controlling application
	memcpy(vision, get_current_vision(), 255);

	vision[254] = 0; // make sure it's null terminated
}

__declspec(dllexport) void cdecl  main_set_dir(int direction)
{
	Party._dir = direction;
}

int QUIT = 0;

//__declspec(dllexport) void cdecl /*C_191E*/main_start()
__declspec(dllexport) void cdecl /*C_191E*/ main()
{
	register unsigned si = 0;
	int bp_04;

	low_init();
	C_C51C();
	if (Party._loc >= 0x11 && Party._loc <= 0x18) {
		CurMode = MOD_DUNGEON;
		if (Load("DNGMAP.SAV", sizeof(tMap8x8x8), &(D_8742._map)) == -1)
			exit(3);
		//File_DNG = dopen(D_0894[Party._loc - 0x11], 0);
		if (setjmp(D_9458) == 0)
			DNG_main();
	} else {
		Party._loc = 0;
	}
	u_kbflush();
	bp_04 = 0;
	for(;;) {
		// need to set this here as we pend on the keyboard before we get to the one below
		set_input_mode(INPUT_MODE_MAIN_INPUT);
		if (QUIT)
		{
			return;
		}
	setjmp(D_9458);
	t_callback();
	C_9209();
	if (C_10FD()) {
		u4_putc(0x10);
		set_input_mode(INPUT_MODE_MAIN_INPUT);
		u_delay(25, 1);
		si = u_kbhit() ? u_kbread() : KBD_SPACE;
		if (u4_isupper((unsigned char)si))
			si = (si & 0xff00) | u4_lower((unsigned char)si);
		switch (si) {
		case KBD_ESC: QUIT = 1;  return;
		case KBD_SPACE: w_Pass(); break;
		case 0x487e:
		case KBD_UP: CMDDIR_Up(); break;
		case 0x4b7c:
		case KBD_LEFT: CMDDIR_Left(); break;
		case 0x5060:
		case KBD_DOWN: CMDDIR_Down(); break;
		case 0xf400:
		case KBD_RIGHT: CMDDIR_Right(); break;
		case KBD_A: CMD_Attack(); break;
		case KBD_B: CMD_Board(); break;
		case KBD_C: CMD_Cast(); break;
		case KBD_D: CMD_Descend();  break;
		case KBD_E: CMD_Enter(); break;
		case KBD_F: CMD_Fire(); break;
		case KBD_G: CMD_Get(); break;
		case KBD_H: CMD_HoleUp(); break;
		case KBD_I: CMD_Ignite(); break;
		case KBD_J: CMD_Jimmy(); break;
		case KBD_K: CMD_Klimb(); break;
		case KBD_L: CMD_Locate(); break;
		case KBD_M: CMD_Mix(); break;
		case KBD_N: CMD_NewOrder(); break;
		case KBD_O: CMD_Open(); break;
		case KBD_P: CMD_Peer(); break;
		case KBD_Q: CMD_Quit(); break;
		case KBD_R: CMD_Ready(); break;
		case KBD_S: CMD_Search(); break;
		case KBD_T: CMD_Talk(); break;
		case KBD_U: CMD_Use(); break;
		case KBD_V: CMD_Volume(); break;
		case KBD_W: CMD_Wear(); break;
		case KBD_X: CMD_X_it(); break;
		case KBD_Y: CMD_Yell(); break;
		case KBD_Z: CMD_Ztats(); break;
		case KBD_CTRL_S:
					if(bp_04 == KBD_ALT_Z) {
				C_1C21();
				break;
			}
		default:
			u4_puts("Bad command!\n");
			sound(2);
			D_07F8 = 0;
			break;
		}
		} else {
		u4_puts("Zzzzz\n");
	}
	if (D_07F8 != 0) {
		C_1C53();
		} else {
		t_callback();
		D_07F8 = 1;
	}
		bp_04 = si;
}
}

#define VK_SPACE          0x20
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_ESCAPE         0x1B
#define VK_RETURN         0x0D
#define VK_BACK           0x08
extern int CMN_kbhit;

__declspec(dllexport) void cdecl main_keyboardHit(char wParam)
{
	switch (wParam) {
		case VK_LEFT: CMN_kbhit = KBD_LEFT; break;
		case VK_RIGHT: CMN_kbhit = KBD_RIGHT; break;
		case VK_UP: CMN_kbhit = KBD_UP; break;
		case VK_DOWN: CMN_kbhit = KBD_DOWN; break;

		case VK_RETURN: CMN_kbhit = KBD_ENTER; break;
		case VK_ESCAPE: CMN_kbhit = KBD_ESC; break;
		case VK_SPACE: CMN_kbhit = KBD_SPACE; break;
		case VK_BACK: CMN_kbhit = KBD_BS; break;

		case 'A': CMN_kbhit = KBD_A; break;
		case 'B': CMN_kbhit = KBD_B; break;
		case 'C': CMN_kbhit = KBD_C; break;
		case 'D': CMN_kbhit = KBD_D; break;
		case 'E': CMN_kbhit = KBD_E; break;
		case 'F': CMN_kbhit = KBD_F; break;
		case 'G': CMN_kbhit = KBD_G; break;
		case 'H': CMN_kbhit = KBD_H; break;
		case 'I': CMN_kbhit = KBD_I; break;
		case 'J': CMN_kbhit = KBD_J; break;
		case 'K': CMN_kbhit = KBD_K; break;
		case 'L': CMN_kbhit = KBD_L; break;
		case 'M': CMN_kbhit = KBD_M; break;
		case 'N': CMN_kbhit = KBD_N; break;
		case 'O': CMN_kbhit = KBD_O; break;
		case 'P': CMN_kbhit = KBD_P; break;
		case 'Q': CMN_kbhit = KBD_Q; break;
		case 'R': CMN_kbhit = KBD_R; break;
		case 'S': CMN_kbhit = KBD_S; break;
		case 'T': CMN_kbhit = KBD_T; break;
		case 'U': CMN_kbhit = KBD_U; break;
		case 'V': CMN_kbhit = KBD_V; break;
		case 'W': CMN_kbhit = KBD_W; break;
		case 'X': CMN_kbhit = KBD_X; break;
		case 'Y': CMN_kbhit = KBD_Y; break;
		case 'Z': CMN_kbhit = KBD_Z; break;

		case '0': CMN_kbhit = KBD_0; break;
		case '1': CMN_kbhit = KBD_1; break;
		case '2': CMN_kbhit = KBD_2; break;
		case '3': CMN_kbhit = KBD_3; break;
		case '4': CMN_kbhit = KBD_4; break;
		case '5': CMN_kbhit = KBD_5; break;
		case '6': CMN_kbhit = KBD_6; break;
		case '7': CMN_kbhit = KBD_7; break;
		case '8': CMN_kbhit = KBD_8; break;
		//case '9': CMN_kbhit = KBD_9; break;
	}
}

/*cheat code --> reveal the different levels of karmas*/
C_1C21()
{
	register int si;

	Gra_CR();
	for(si = 0; si < 8; si++)
		u4_putl(*(pKarmas[si]), 2, '0');
	Gra_CR();
}

C_1C53()
{
	register int si;
	register struct tChara *di;

	C_10FD();
	/*restore some hull*/
	if(Party._ship < 50 && U4_RND1(3) == 0)
		Party._ship ++;
	/*S=>G(randomly), P=>takes 2 hit*/
	for(di = Party.chara, si = 0; si < Party.f_1d8; di++, si++) {
		if(di->_stat == 'S' && U4_RND1(7) == 0) {
			di->_stat = 'G';
		} else if(di->_stat == 'P') {
			hitChara(si, 2);
			Gra_11(si); sound(6); Gra_11(si);
		}
	}
	/*FOOD management*/
	if(food_dec(Party.f_1d8)) {
		u4_puts("\nStarving!!!\n");
		for(si = 0; si < Party.f_1d8; si ++) {
			if(isCharaAlive(si))
				hitChara(si, 2);
		}
		si = Party.f_1d8;
		while(--si >= 0)
			Gra_11(si);
		sound(6);
		si = Party.f_1d8;
		while(--si >= 0)
			Gra_11(si);
	}
	/* */
	MP_recover();
	if(Party.f_1dc == 0) {
		C_7918();
		C_5834();
		C_5851();
		C_7918();
	}
	Party._moves ++;
	if(spell_cnt) {
		if(--spell_cnt == 0)
			spell_sta = 7;
	}
	dspl_Stats();
	/*automatic door closing*/
	C_431D();
}
