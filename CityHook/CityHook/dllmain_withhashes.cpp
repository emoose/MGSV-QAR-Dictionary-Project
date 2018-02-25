#include "stdafx.h"
#include <fstream>
#include <string>
#include "include\MinHook.h"

const size_t CityHash1Addr = 0x141841EB0; // different offset to the main CityHash funcs, these hooks let us capture the hash after it's been fully generated
const size_t CityHash2Addr = 0x141842110;

const size_t BaseAddr = 0x140000000; // from ImageBase field in the EXE

typedef unsigned __int64(__fastcall *cityHash1_func)(char* a1, uint64_t a2, uint64_t a3);
typedef unsigned __int64(__fastcall *cityHash2_func)(char* a1, uint64_t a2);

cityHash1_func origCityHash1;
cityHash2_func origCityHash2;

// uncomment if you only want to log paths (contains '/' or '\', or ends in .lua/.json/.fpk/.ftexs)
//#define PATHS_ONLY

// comment to disable using a buffer and write each hashed string directly to disk... will cause massive slowdowns, but might find more entries!
#define USE_BUFFER

#ifdef USE_BUFFER
const int logBufferSize = 1024;
int logBufferOffset = 0;

char logBuffer[logBufferSize];
HANDLE logBufferMutex = 0;
#endif

void LogString(char* str, int str_len, uint64_t hash)
{
	// string might have a null char anywhere between 0 - str_len, so lets find it and make sure we don't add it to the buffer
	// (because that would stop later buffer entries being written to the log, as the null would come before them)
	int real_len = str_len;
	for (int i = 0; i < str_len - 1; i++) // have to check up to str_len - 1 instead of up to str_len otherwise it crashes?
	{
		if (str[i] == '\0')
		{
			real_len = i - 1;
			break;
		}
	}

	if (str[real_len - 1] == '\0') // above might have missed the null because we had to do str_len - 1, so check again just incase (we really don't want to copy any nulls)
		real_len--;

	char* buff = new char[real_len + 1];
	memcpy(buff, str, real_len);
	buff[real_len] = '\0';

	std::string nuBuff = std::string(buff);
	nuBuff += "___:___";
	nuBuff += std::to_string(hash);

#ifdef USE_BUFFER
	if(!logBufferMutex)
		logBufferMutex = CreateMutex(NULL, FALSE, NULL);

	WaitForSingleObject(logBufferMutex, INFINITE);
	if (logBufferOffset + (nuBuff.length() + 2) >= logBufferSize)
	{
#endif
		std::ofstream outfile;
		outfile.open("logger.log", std::ios_base::app);
		if (outfile.fail())
			return;
#ifdef USE_BUFFER
		outfile << logBuffer << '\n';
#endif
		outfile << nuBuff << '\n';
		outfile.close();

#ifdef USE_BUFFER
		logBufferOffset = 0;
	}
	else
	{
		memcpy(logBuffer + logBufferOffset, nuBuff.c_str(), nuBuff.length());

		logBuffer[logBufferOffset + nuBuff.length()] = '\n';
		logBuffer[logBufferOffset + nuBuff.length() + 1] = '\0';
		logBufferOffset += nuBuff.length() + 1; // only + 1 so the next logBuffer write will overwrite the null we added above
	}
	ReleaseMutex(logBufferMutex);
#endif

	delete[] buff;
}

void LogFlush()
{
#ifdef USE_BUFFER
	if (!logBufferOffset)
		return;

	std::ofstream outfile;
	outfile.open("logger.log", std::ios_base::app);
	if (outfile.fail())
		return;

	outfile << logBuffer << '\n';
	outfile.close();

	logBufferOffset = 0;
#endif
}

unsigned __int64 __fastcall CityHash1Hook(char* a1, unsigned int a2, __int64 a3)
{
	uint64_t res = origCityHash1(a1, a2, a3);
	if (a1 && a2)
	{
		if (a2 >= 4)
			if (a1[0] == 'c' && a1[1] == 'a' && a1[2] == 'a' && a1[3] == 'r') // caar gets spammed, fuck caar
				return res;
#ifdef PATHS_ONLY
		bool isPath = false;
		for (int i = 0; i < a2; i++)
			if (a1[i] == '/' || a1[i] == '\\')
			{
				isPath = true;
				break;
			}

		// doesn't contain '/' or '\', check for .lua/.json/.fpk/.ftexs
		if (!isPath && a2 > 5)
		{
			// have to go through the whole string to check, since it seems strings can end with a variable amount of null bytes
			for (int i = 0; i < a2 - 4; i++)
			{
				if (a1[i] == '.' && a1[i + 1] == 'l' && a1[i + 2] == 'u' && a1[i + 3] == 'a') // check for .lua
				{
					isPath = true;
					break;
				}
				if (a1[i] == '.' && a1[i + 1] == 'j' && a1[i + 2] == 's' && a1[i + 3] == 'o') // check for .jso(n)
				{
					isPath = true;
					break;
				}
				if (a1[i] == '.' && a1[i + 1] == 'f' && a1[i + 2] == 'p' && a1[i + 3] == 'k') // check for .fpk(d)
				{
					isPath = true;
					break;
				}
				if (a1[i] == '.' && a1[i + 1] == 'f' && a1[i + 2] == 't' && a1[i + 3] == 'e') // check for .fte(xs)
				{
					isPath = true;
					break;
				}
			}
		}

		if (!isPath)
			return res;
#endif
		LogString(a1, a2, res);
	}
	return res;
}

unsigned __int64 __fastcall CityHash2Hook(char* a1, unsigned int a2)
{
	uint64_t res = origCityHash2(a1, a2);
	if (a1 && a2)
	{
		if (a2 >= 4)
			if (a1[0] == 'c' && a1[1] == 'a' && a1[2] == 'a' && a1[3] == 'r') // caar gets spammed, fuck caar
				return res;
#ifdef PATHS_ONLY
		bool isPath = false;
		for (int i = 0; i < a2; i++)
			if (a1[i] == '/' || a1[i] == '\\')
			{
				isPath = true;
				break;
			}

		// doesn't contain '/' or '\', check for .lua/.json/.fpk/.ftexs
		if (!isPath && a2 > 5)
		{
			// have to go through the whole string to check, since it seems strings can end with a variable amount of null bytes
			for (int i = 0; i < a2 - 4; i++)
			{
				if (a1[i] == '.' && a1[i + 1] == 'l' && a1[i + 2] == 'u' && a1[i + 3] == 'a') // check for .lua
				{
					isPath = true;
					break;
				}
				if (a1[i] == '.' && a1[i + 1] == 'j' && a1[i + 2] == 's' && a1[i + 3] == 'o') // check for .jso(n)
				{
					isPath = true;
					break;
				}
				if (a1[i] == '.' && a1[i + 1] == 'f' && a1[i + 2] == 'p' && a1[i + 3] == 'k') // check for .fpk(d)
				{
					isPath = true;
					break;
				}
				if (a1[i] == '.' && a1[i + 1] == 'f' && a1[i + 2] == 't' && a1[i + 3] == 'e') // check for .fte(xs)
				{
					isPath = true;
					break;
				}
			}
		}

		if (!isPath)
			return res;
#endif
		LogString(a1, a2, res);
	}
	return res;
}

HMODULE ourModule;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		ourModule = hModule;

		MH_Initialize();

		size_t RealBaseAddr = (size_t) GetModuleHandle(NULL);

		// CityHash1Addr / CityHash2Addr addresses are from IDA, which uses the ImageBase field in the exe as the base address (usually 0x140000000)
		// the real base address changes every time the game is run though, so we have to remove that base address and add the real one
		void* CityHash1_rebased = (void*)((CityHash1Addr - BaseAddr) + RealBaseAddr);
		void* CityHash2_rebased = (void*)((CityHash2Addr - BaseAddr) + RealBaseAddr);

		MH_CreateHook(CityHash1_rebased, CityHash1Hook, (LPVOID*)&origCityHash1);
		MH_CreateHook(CityHash2_rebased, CityHash2Hook, (LPVOID*)&origCityHash2);

		MH_EnableHook(CityHash1_rebased);
		MH_EnableHook(CityHash2_rebased);
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		LogFlush(); // this should flush the rest of the buffer when the app closes, but idk
	}

	return TRUE;
}

