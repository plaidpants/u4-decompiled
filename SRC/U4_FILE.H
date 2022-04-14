/*
 * Ultima IV - Quest Of The Avatar
 * (c) Copyright 1987 Lord British
 * reverse-coded by Ergonomy Joe in 2012
 */
#ifndef __U4_FILE_H__
#define __U4_FILE_H__

#ifdef WIN32
#define far
#endif

#ifdef ENABLE_WINDOWS
extern /*C_0812*/Console(char *);
#endif
extern /*C_0855*/Load(char *, unsigned, void far *);
extern /*C_08D1*/Save(char *, unsigned, void far *);

#endif
