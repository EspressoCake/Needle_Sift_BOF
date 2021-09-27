#include <windows.h>
#include "headers/beacon.h"
#include "headers/win32_api.h"

/////////////////
// Definitions //
/////////////////
#define CURRENT_LINESIZE_MAX_NO_HEAP 2048

//////////////////////
// Local Prototypes //
//////////////////////
ssize_t FetchUntilNewlineOrBufferEnd(FILE* stream, char* buf, size_t size);
int SearchForNewlinesWithNeedle(char* filename, char* cNeedle);


//////////////////////
// Implementations //
/////////////////////
ssize_t FetchUntilNewlineOrBufferEnd(FILE* stream, char* buf, size_t size) {
	if (size == 0) {
		return 0;
	}

	size_t count;
	int c = 0;
	
	for (count = 0; c != '\n' && count < size - 1; count++) {
		c = MSVCRT$getc(stream);

		if (c == EOF) {
			if (count == 0) {
				return -1;
			}
			break;
		}

		buf[count] = (char)c;
	}

	buf[count] = '\0';
	
	return (ssize_t)count;
}


int SearchForNewlinesWithNeedle(char* filename, char* cNeedle) {
	FILE* fpFilePointer = NULL;
	long iFileSize = 0;
	char currentBuff[CURRENT_LINESIZE_MAX_NO_HEAP] = { 0 };
	ssize_t ssIndex = 0;

	MSVCRT$fopen_s(&fpFilePointer, filename, "r");
    if ( fpFilePointer == NULL ) {
        BeaconPrintf(CALLBACK_ERROR, "Unable to open the desired file for reading: %s\n", filename);
		return EXIT_FAILURE;
	}

	MSVCRT$fseek(fpFilePointer, 0L, SEEK_END);
	iFileSize = MSVCRT$ftell(fpFilePointer);
	MSVCRT$rewind(fpFilePointer);

	BeaconPrintf(CALLBACK_OUTPUT, "Current file size: %lu\n", iFileSize);

	ssize_t count = 0;
	long fTellIndex = 0;

	while (fTellIndex < iFileSize) {
		fTellIndex = MSVCRT$ftell(fpFilePointer);
		if (fTellIndex == EOF) {
			break;
		}

		MSVCRT$memset(currentBuff, 0, sizeof(currentBuff));

		count = FetchUntilNewlineOrBufferEnd(fpFilePointer, currentBuff, CURRENT_LINESIZE_MAX_NO_HEAP);

		if (count && count <= CURRENT_LINESIZE_MAX_NO_HEAP && fTellIndex < iFileSize) {
			char* pch = NULL;
			pch = MSVCRT$strstr(currentBuff, cNeedle);
			
			if (pch != NULL) {
				BeaconPrintf(CALLBACK_OUTPUT, "Current needle found: %s\n", pch);
			}
		}
		else {
			break;
		}
	}

	if (fpFilePointer) {
		MSVCRT$fclose(fpFilePointer);
	}
}


void go (char* args, int len) {
    datap parser;
    char *cFileName = NULL;
    char *cNeedle   = NULL;

    LPCWSTR lpDBanner =    L"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n"
                           L"|           String Sifter           |\n"
                           L"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n"
                           L"| By:                               |\n"
                           L"|          @the_bit_diddler         |\n"
                           L"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n";

    BeaconPrintf(CALLBACK_OUTPUT, "%ls\n", (wchar_t*)lpDBanner);

    BeaconDataParse(&parser, args, len);

    cFileName = BeaconDataExtract(&parser, NULL);
    cNeedle   = BeaconDataExtract(&parser, NULL);
    
    BeaconPrintf(CALLBACK_OUTPUT, "Current filename: %s\n", cFileName);
    BeaconPrintf(CALLBACK_OUTPUT, "Current needle:   %s\n", cNeedle);

    SearchForNewlinesWithNeedle(cFileName, cNeedle);
}