/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4.h"

unsigned D_07F8 = 1;

/*karmas*/
U16 /*D_07FA*/*pKarmas[] = {
	&(Party._hones),
	&(Party._compa),
	&(Party._valor),
	&(Party._justi),
	&(Party._sacri),
	&(Party._honor),
	&(Party._spiri),
	&(Party._humil),
};

int /*D_080A*/activeCharaX = -1;

char * D_080C = &AVATAR[0xFAC9] /* {-1,0,1,0} */;
char * D_0810 = &AVATAR[0xFACD] /* {0,-1,0,1} */;

/*moongates positions*/
unsigned char * D_0814 = &AVATAR[0xFAD1] /* {0xE0,0x60,0x26,0x32,0xA6,0x68,0x17,0xBB} */;
unsigned char * D_081C = &AVATAR[0xFAD9] /* {0x85,0x66,0xE0,0x25,0x13,0xC2,0x7E,0xA7} */;

/*towns/castles files*/
char *D_0824[] = {
	/*Castles*/
	/*D_06C2*/&AVATAR[0xF97F] /* "LCB_1.ULT" */,
	/*D_06CC*/&AVATAR[0xF989] /* "LYCAEUM.ULT" */,
	/*D_06D8*/&AVATAR[0xF995] /* "EMPATH.ULT" */,
	/*D_06E3*/&AVATAR[0xF9A0] /* "SERPENT.ULT" */,
	/*Townes*/
	/*D_06EF*/&AVATAR[0xF9AC] /* "MOONGLOW.ULT" */,
	/*D_06FC*/&AVATAR[0xF9B9] /* "BRITAIN.ULT" */,
	/*D_0708*/&AVATAR[0xF9C5] /* "JHELOM.ULT" */,
	/*D_0713*/&AVATAR[0xF9D0] /* "YEW.ULT" */,
	/*D_071B*/&AVATAR[0xF9D8] /* "MINOC.ULT" */,
	/*D_0725*/&AVATAR[0xF9E2] /* "TRINSIC.ULT" */,
	/*D_0731*/&AVATAR[0xF9EE] /* "SKARA.ULT" */,
	/*D_073B*/&AVATAR[0xF9F8] /* "MAGINCIA.ULT" */,
	/*Villages*/
	/*D_0748*/&AVATAR[0xFA05] /* "PAWS.ULT" */,
	/*D_0751*/&AVATAR[0xFA0E] /* "DEN.ULT" */,
	/*D_0759*/&AVATAR[0xFA16] /* "VESPER.ULT" */,
	/*D_0764*/&AVATAR[0xFA21] /* "COVE.ULT" */
};

/*places world's coordinates*/
char * D_0844 = &AVATAR[0xFB01] /*{0x56,0xDA,0x1C,0x92,0xE8,0x52,0x24,0x3A,0x9F,0x6A,0x16,0xBB,0x62,0x88,0xC9,0x88,0xF0,0x5B,0x48,0x7E,0x9C,0x3A,0xEF,0xE9, 0xE9,0x80,0x24,0x49,0xCD,0x51,0xE7,0xE7}*/;
char * D_0864 = &AVATAR[0xFB21] /*{0x6B,0x6B,0x32,0xF1,0x87,0x6A,0xDE,0x2B,0x14,0xB8,0x80,0xA9,0x91,0x9E,0x3B,0x5A,0x49,0x43,0xA8,0x14,0x1B,0x66,0xF0,0xE9, 0x42,0x5C,0xE5,0x0B,0x2D,0xCF,0xD8,0xD8}*/;

/*colors*/
char *D_0884[] = {
	/*D_076D*/&AVATAR[0xFA2A] /* "Blue" */,
	/*D_0772*/&AVATAR[0xFA2F] /* "Yellow" */,
	/*D_0779*/&AVATAR[0xFA36] /* "Red" */,
	/*D_077D*/&AVATAR[0xFA3A] /* "Green" */,
	/*D_0783*/&AVATAR[0xFA40] /* "Orange" */,
	/*D_078A*/&AVATAR[0xFA47] /* "Purple" */,
	/*D_0791*/&AVATAR[0xFA4E] /* "White" */,
	/*D_0797*/&AVATAR[0xFA54] /* "Black" */
};

/*dungeons files*/
char *D_0894[] = {
	/*D_079D*/&AVATAR[0xFA5A] /* "Deceit.Dng" */,
	/*D_07A8*/&AVATAR[0xFA65] /* "Despise.Dng" */,
	/*D_07B4*/&AVATAR[0xFA71] /* "Destard.Dng" */,
	/*D_07C0*/&AVATAR[0xFA7D] /* "Wrong.Dng" */,
	/*D_07CA*/&AVATAR[0xFA87] /* "Covetous.Dng" */,
	/*D_07D7*/&AVATAR[0xFA94] /* "Shame.Dng" */,
	/*D_07E1*/&AVATAR[0xFA9E] /* "Hythloth.Dng" */,
	/*D_07EE*/&AVATAR[0xFAAB] /* "Abyss.Dng" */
};
