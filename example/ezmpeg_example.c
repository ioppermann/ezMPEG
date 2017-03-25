//This file is part of ezMPEG
//Copyright (C)2002 Ingo Oppermann ( ingo_opp@users.sourceforge.net / http://sourceforge.net/projects/ezmpeg/ )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../ezmpeg.h"

int main(int argc, char *argv[])
{
	FILE *in;
	int i, j, m;
	char *picture;
	clock_t dur;
	ezMPEGStream ms;

	picture = (char *)malloc(3 * 320 * 240 * sizeof(char));

	if(!ezMPEG_Init(&ms, "ezmpeg_test.mpeg", 320, 240, 25, 30, 2))
		printf("%s\n", ezMPEG_GetLastError(&ms));
	if(!ezMPEG_Start(&ms))
		printf("%s\n", ezMPEG_GetLastError(&ms));

	for(m = 0; m < 75; m++) {
		if((in = fopen("ezmpeg_test.ppm", "rb")) == NULL)
			exit(1);

		fseek(in, 45, SEEK_SET);
		j = 0;
		do {
			i = fgetc(in);

			if(i != EOF)
				picture[j++] = i;
			else
				break;
		}while(i != EOF);

		fclose(in);

		dur = clock();

		if(!ezMPEG_Add(&ms, picture))
			printf("%s\n", ezMPEG_GetLastError(&ms));

		dur = clock() - dur;
		printf("Frame %4d: %f secs\n", m, (float)dur / (float)CLOCKS_PER_SEC);
	}

	if(!ezMPEG_Finalize(&ms))
		printf("%s\n", ezMPEG_GetLastError(&ms));

	return 0;
}
