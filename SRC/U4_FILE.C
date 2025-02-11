/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */

#include "u4_file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "u4_dos.h"

extern char AVATAR[];

/*C_0812*/Console(bp04)
char *bp04;
{
	int bp_02;

	if((bp_02 = dwrite(1, bp04, strlen(bp04))) == -1 || strlen(bp04) != bp_02) {
		exit(3);
	}
}

/*C_0855*/Load(char* bp0a, unsigned bp08, void far* bp04)
{
	int bp_02, bp_04;

	if((bp_02 = dopen(bp0a, 0)) == -1) {
		Console(&AVATAR[0xF71D + 0x5] /* "\r\nOpening " */);
		Console(bp0a);
		return -1;
	}
	if((bp_04 = dread(bp_02, bp04, bp08)) == -1 || bp08 != bp_04) {
		Console(&AVATAR[0xF728 + 0x5] /* "\r\nReading " */);
		if(bp_04 == -1) {
			Console(bp0a);
		} else {
			Console(bp0a);
			Console(&AVATAR[0xF733 + 0x5] /* ": File wrong size\r\n" */);
		}
		return -1;
	}
	if(dclose(bp_02) == -1) {
		Console(&AVATAR[0xF747 + 0x5] /* "\r\nClosing " */);
		Console(bp0a);
		return -1;
	}
	return 0;
}

/*C_08D1*/Save(char* bp0a, unsigned bp08, void far* bp04)
{
	int bp_02, bp_04;

	if((bp_02 = dopen(bp0a, 1)) == -1) {
		Console(&AVATAR[0xF71D + 0x5] /* "\r\nOpening " */);
		Console(bp0a);
		return -1;
	}
	if((bp_04 = dwrite(bp_02, bp04, bp08)) == -1 || bp08 != bp_04) {
		Console(&AVATAR[0xF75D + 0x5] /* "\r\nWriting " */);
		if(bp_04 == -1) {
			Console(bp0a);
		} else {
			Console(bp0a);
			Console(&AVATAR[0xF733 + 0x5] /* ": File wrong size\r\n" */);
		}
		exit(1);
	}
	if(dclose(bp_02) == -1) {
		Console(&AVATAR[0xF747 + 0x5] /* "\r\nClosing " */);
		Console(bp0a);
		return -1;
	}
	return 0;
}
