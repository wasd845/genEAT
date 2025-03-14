﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

PIMAGE_DOS_HEADER DosHeader = nullptr;
PIMAGE_NT_HEADERS NtHeader = nullptr;
unsigned long long FileBase = 0;

void OpenPeFile(LPCSTR FileName)
{
	HANDLE Handle = CreateFileA(FileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (Handle == INVALID_HANDLE_VALUE)
		return;

	DWORD FileSize = GetFileSize(Handle, NULL);
	DWORD OperSize = 0;
	FileBase = (unsigned long long)new BYTE[FileSize];
	BOOL bRet = ReadFile(Handle, (LPVOID)FileBase, FileSize, &OperSize, NULL);
	if (!bRet)
		exit(0);

	// Get DOS header and check if it's a valid DOS file
	DosHeader = (PIMAGE_DOS_HEADER)FileBase;
	if (DosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		exit(0);

	// Get NT header and check if it's a valid PE file
	NtHeader = (PIMAGE_NT_HEADERS)(FileBase + DosHeader->e_lfanew);
	if (NtHeader->Signature != IMAGE_NT_SIGNATURE)
		exit(0);

	CloseHandle(Handle);
}


unsigned long long RVAtoFOA(unsigned long long rva)
{
	auto SectionTables = IMAGE_FIRST_SECTION(NtHeader);
	WORD Count = NtHeader->FileHeader.NumberOfSections;
	for (int i = 0; i < Count; ++i)
	{
		unsigned long long Section_Start = SectionTables[i].VirtualAddress;
		unsigned long long Section_Ends = SectionTables[i].VirtualAddress + SectionTables[i].SizeOfRawData;
		if (rva >= Section_Start && rva < Section_Ends)
		{
			return rva - SectionTables[i].VirtualAddress + SectionTables[i].PointerToRawData;
		}
	}
	return -1;
}


void GenerateEAT(char* FileName, char* OldDllName)
{
	unsigned long long rav = NtHeader->OptionalHeader.DataDirectory[0].VirtualAddress;
	auto ExportTable = (PIMAGE_EXPORT_DIRECTORY)(RVAtoFOA(rav) + FileBase);

	DWORD NameCount = ExportTable->NumberOfNames;
	DWORD FunctionCount = ExportTable->NumberOfFunctions;

	DWORD* Addr_Table = (DWORD*)(RVAtoFOA(ExportTable->AddressOfFunctions) + FileBase);
	DWORD* Name_Table = (DWORD*)(RVAtoFOA(ExportTable->AddressOfNames) + FileBase);
	WORD* Id_Table = (WORD*)(RVAtoFOA(ExportTable->AddressOfNameOrdinals) + FileBase);

	FILE* fp = fopen(FileName, "a+");
	char buf[8192] = { 0 };

	sprintf(buf, "// PowerBy:GenEAT\n#include <stdio.h>\n#include <windows.h>\n\n");
	fwrite(buf, strlen(buf), 1, fp);

	for (DWORD i = 0; i < FunctionCount; ++i)
	{
		for (DWORD j = 0; j < NameCount; ++j)
		{
			if (i == Id_Table[j])
			{
				CHAR* Name = (CHAR*)(RVAtoFOA(Name_Table[j]) + FileBase);
				sprintf(buf, "#pragma comment(linker, \"/EXPORT:%s=%s.%s,@%d\") \n", Name, OldDllName, Name, i + 1);
				fwrite(buf, strlen(buf), 1, fp);
				_flushall();
				Sleep(20);
				printf("%s", buf);
				break;
			}
		}
	}
	sprintf(buf,
		"\nBOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)\n"
		"{\n"
		" if (dwReason == DLL_PROCESS_ATTACH)\n"
		" {\n"
		"   DisableThreadLibraryCalls(hModule);\n"
		" }\n"
		" return TRUE;\n"
		"}\n");
	fwrite(buf, strlen(buf), 1, fp);
	_fcloseall();
}

void PrintHelp()
{
    printf("GenEAT - Generate Export Address Table Tool\n");
    printf("Usage: genEAT.exe -d <dll_path> -c <output_cpp_path> -n <old_dll_name>\n\n");
    printf("Options:\n");
    printf("  -h, --help     Show this help message\n");
    printf("  -d <dll_path>  Path to the input DLL file\n");
    printf("  -c <cpp_path>  Path to output the generated C++ file\n");
    printf("  -n <dll_name>  Original DLL name for export\n\n");
    printf("Example:\n");
    printf("  genEAT.exe -d mydll.dll -c output.cpp -n original.dll\n");
}

int main(int argc, char* argv[])
{
    if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")))
    {
        PrintHelp();
        return 0;
    }

    if (argc == 7)
    {
        if (!strcmp(argv[1], "-d") && !strcmp(argv[3], "-c") && !strcmp(argv[5], "-n"))
        {
            OpenPeFile(argv[2]);
            GenerateEAT(argv[4], argv[6]);
            return 0;
        }
    }

    PrintHelp();
    return 1;
}
