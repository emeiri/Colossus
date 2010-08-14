/*

	Copyright 2010 Etay Meiri

	This file is part of Colossus

    Colossus is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Colosssus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Colosssus.  If not, see <http://www.gnu.org/licenses/>.

*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "file.h"

char* ReadFile(const char* pFilename, long long* pSize)
{
	struct stat FileStat;

	if (stat(pFilename, &FileStat)) {
		fprintf(stderr, "Error getting stat of '%s'\n", pFilename);
		return NULL;
	}

	char* pBuf = (char*)malloc(FileStat.st_size);

	FILE* pFile = NULL;

	if (!(pFile = fopen(pFilename, "r"))) {
		free(pBuf);
	}

	char* p = pBuf;
	int BytesRead = 0;
	do {
		BytesRead = fread(p, 1, 1024, pFile);
		p += BytesRead;
	} while (BytesRead);

	if (!feof(pFile)) {
		free(pBuf);
		pBuf = NULL;
	}
	else if (pSize) {
		*pSize = FileStat.st_size;
	}

	fclose(pFile);

	return pBuf;
}

