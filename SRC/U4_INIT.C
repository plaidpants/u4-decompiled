/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

#include <string.h>
#include <stdlib.h>

C_C445() {}
C_C44A() {}
C_C44F() {}

static int D_9138;

/*confirmFileInDrive?*/
C_C454(bp06, bp04)
char *bp06;
char *bp04;
{
	// always have either disk inserted
	return 0;
	int bp_02;

	if(!C_182F(bp04)) {
		CurMode = MOD_VISION;
		txt_Y = 10;
		txt_X = (unsigned int)(40 - strlen(bp06)) >> 1;
		u4_puts(bp06);
		txt_Y ++;
		txt_X = 18;
		u4_puts(/*D_3024*/&AVATAR[0xF339 + 0x5] /* "and" */);
		txt_Y ++;
		txt_X = 11;
		u4_puts(/*D_3028*/&AVATAR[0x122A3 + 0x2E2E] /* "press drive letter" */);
		set_input_mode(INPUT_MODE_DRIVE_LETTER);
		while(!u_kbhit());
		do {
			set_input_mode(INPUT_MODE_DRIVE_LETTER);
			bp_02 = (unsigned char)u_kbread();
			u4_toupper(bp_02);
			if(bp_02 != 'B' || D_9138 != 0) {
				if(bp_02 >= 'A' && bp_02 <= 'P') {
					bp_02 &= 0xf;
					C_181D(bp_02);
				}
			}
			if(C_1814() == bp_02 && C_182F(bp04))
				return 0;
			sound(1,0);
			set_input_mode(INPUT_MODE_DRIVE_LETTER);
			while(!u_kbhit());
		} while(1);
	}
}

#define NPARAM (far_psp->_80[0])
#define PARAM0 (far_psp->_80[2])
#define PARAM1 (far_psp->_80[4])

C_C51C()
{
	int bp_02, bp_04;

	u4_toupper(PARAM1);
	u4_toupper(PARAM0);
	/*set drive number*/
	if(NPARAM < 4) {
		D_9138 = ((equip_flags & 0xc0) >> 6)?1:0;
		PARAM1 = D_9138 + '0';
	} else if (PARAM1 == '0') {
		D_9138 = 0;
	} else if (PARAM1 == '1') {
		D_9138 = 1;
	} else {
		D_9138 = ((equip_flags & 0xc0) >> 6)?1:0;
	}
	/*set graphic type*/
	if(NPARAM < 2) {
		D_943A = low_gra();
	} else if(PARAM0 == 'C') {
		D_943A = 1;
	} else if(PARAM0 == 'E') {
		D_943A = 2;
	} else if(PARAM0 == 'T') {
		D_943A = 3;
	} else {
		D_943A = low_gra();
	}
	/* */
	pShapes = dalloc((D_943A == 1)?0x4000:0x8000);
	pCharset = dalloc((D_943A == 1)?0x0800:0x1000);
	if(pShapes == 0 || pCharset == 0)
		exit(3);
	if(Load((D_943A == 1)?/*D_303B*/&AVATAR[0x122B6 + 0x2E2E] /* "CHARSET.CGA" */:/*D_3047*/&AVATAR[0x122C2 + 0x2E2E] /* "CHARSET.EGA" */, (D_943A == 1)?0x0800:0x1000, pCharset) == -1)
		exit(3);
	if(D_943A == 1) {
		if(Load(/*D_3053*/&AVATAR[0x122CE + 0x2E2E] /* "SHAPES.CGA" */, 0x4000, pShapes) == -1)
			exit(3);
	}
	bp_02 = C_1814();
	switch(D_943A) {
		case 1:
			dfree(patch_tandy);
			patch_tandy = 0;
			C_20C1(/*D_305E*/&AVATAR[0x122D9 + 0x2E2E] /* "CGA.DRV" */);
		break;
		case 2:
			dfree(patch_tandy);
			patch_tandy = 0;
			C_20C1(/*D_3066*/&AVATAR[0x122E1 + 0x2E2E] /* "EGA.DRV" */);
		break;
		case 3:
			C_20C1(/*D_306E*/&AVATAR[0x122E9 + 0x2E2E] /* "TANDY.DRV" */);
		break;
		case -1:
			//Console(/*D_3078*/&AVATAR[0x122F3 + 0x2E2E] /* "I can't find a color graphics card.\r\n" */);
			exit(2);
		break;
	}
	bp_04 = C_184F();/*piracy check function ?*/
	Gra_init(&pShapes, &pCharset, exit);
	if(D_943A == 2)
		sizzleCharset();
	C_18A2();
	if(D_943A == 1)
		speed_info ++;
	Gra_clrscr();
	if(PARAM1 >= (char)'A' && PARAM1 <= (char)'P') {
		if(C_1814() == (PARAM1 & 0x0f)) {
			C_C454(/*D_30A8*/&AVATAR[0x12323 + 0x2E2E] /* "Re-Insert PLAYER Disk" */, /*D_309E*/&AVATAR[0x12319 + 0x2E2E] /* "WORLD.MAP" */);
		} else {
			C_181D((unsigned char)PARAM1 & 0x0f);
		}
	}
	C_C454(/*D_30C8*/&AVATAR[0x12343 + 0x2E2E] /* "Insert PLAYER disk" */, /*D_30BE*/&AVATAR[0x12319 + 0x2E2E] /* "WORLD.MAP" */);
	if(D_943A != 1) {
		if(Load(/*D_30DB*/&AVATAR[0x12356 + 0x2E2E] /* "SHAPES.EGA" */, 0x8000, pShapes) == -1)
			exit(3);
	}
	if(D_943A == 2)
		sizzleShapes();
	if(Load(/*D_30E6*/&AVATAR[0x11478 + 0x200F] /* "PARTY.SAV" */, sizeof(struct tParty), &Party) == -1)
		exit(3);
#if 0/*def WIN32*/
	/*for debug*/
	Party._x = 0x5b; Party._y = 0x44;
#endif
	if(Party.f_1d8 == 0) {
		Gra_clrscr();
		txt_Y = 8;
		txt_X = 12;
		u4_puts(/*D_30F0*/&AVATAR[0x1236B + 0x2E2E] /* "No party formed!" */);
		sound(8,0);
		set_input_mode(INPUT_MODE_DELAY_NO_CONTINUE);
		u_delay(3, 0);
		u_kbflush();
		if(bp_02 == C_1814()) {
			C_C454(/*D_310B*/&AVATAR[0x12386 + 0x2E2E] /* "Re-Insert PROGRAM Disk" */, /*D_3010*/&AVATAR[0x1237C + 0x2E2E] /* "TITLE.EXE" */);
		} else {
			C_181D(bp_02);
			C_C454(/*D_312C*/&AVATAR[0x123A7 + 0x2E2E] /* "Insert PROGRAM disk" */, /*D_3122*/&AVATAR[0x1237C + 0x2E2E] /* "TITLE.EXE" */);
		}
		low_clean();
		exit(4);
	}
	if(Load(/*D_3140*/&AVATAR[0x11482 + 0x200F] /* "MONSTERS.SAV" */, sizeof(struct tNPC), &(D_8742._npc)) == -1)
		exit(3);
#if 0 // we will open and close this as needed instead of leaving it open
	if((File_MAP = dopen(/*D_314D*/&AVATAR[0x12319 + 0x2E2E] /* "WORLD.MAP" */, 0)) == -1) {
		//Console(/*D_3157*/&AVATAR[0x123D2 + 0x2E2E] /* "Can't open map file\r\n" */);
		exit(3);
	}
#endif
	File_TLK = 0;
	D_9445 = D_0814[Party._trammel];
	D_9448 = D_081C[Party._felucca];
	C_213B();/*draw game screen frame*/
	Gra_CR();
	spell_sta = 7;
	spell_cnt = 0;
	D_9440 = (Party.f_1dc == 0);/*flying status*/
	D_95C6 = 0;
	CurMode = MOD_OUTDOORS;
	WindDir = DIR_N;
	SoundFlag = 1;
	dspl_Stats();
	C_26B6();
}
