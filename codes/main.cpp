#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <afxwin.h>
using namespace std;

void astrcpy(char* out, char* in, int addr)
{
	int j = 0;
	for (int i = addr; i < strlen(in); i++)
	{
		out[j] = in[i];
		j++;
	}
}

bool DeleteDirectory(CString DirName)
{
	CString PUBPATH;
	PUBPATH = DirName;
	CFileFind tempFind;
	DirName += "\\*.*";
	BOOL IsFinded = (BOOL)tempFind.FindFile(DirName);
	//cout << IsFinded <<endl;
	while (IsFinded)
	{
		IsFinded = (BOOL)tempFind.FindNextFile();
		if (!tempFind.IsDots())
		{
			CString strDirName;
			strDirName += PUBPATH;
			strDirName += "\\";
			strDirName += tempFind.GetFileName();
			if (tempFind.IsDirectory())
			{
				DeleteDirectory(strDirName);
			}
			else
			{
				SetFileAttributes(strDirName, FILE_ATTRIBUTE_NORMAL); //去掉文件的系统和隐藏属性
				DeleteFile(strDirName);
			}
		}
	}
	tempFind.Close();
	if (!RemoveDirectory(PUBPATH))
	{
		return false;
	}
	return true;

}

int fileCopy(char *in, char *out, int isdelete)
{
	if (!CopyFile(in, out, isdelete))
		return 0;
	SetFileAttributes(out, FILE_ATTRIBUTE_NORMAL); //去掉文件属性
	return 1;
}

void printPrct(int log, int prct)
{
	prct++;
	for (int i = 0; i < log; i++)
	{
		printf("\b");
	}
	int progLong = prct * log / 100;
	for (int i = 0; i < progLong; i++)
	{
		printf("*");
	}
	for (int i = 0; i < log - progLong; i++)
	{
		printf("-");
	}
}

int main(int argc,char **argv)
{
	if (argc <= 2)
	{
		puts("WHITEBOX.exe - Launcher for Windows CE x86 Image Emulator based on 86Box");
		puts("Usage: WHITEBOX [LOADCEPC.exe configuration(s)...] [Whitebox configuration(s)...]<Path to NK.bin>");
		puts("Whitebox configuration:");
		puts("	/M:<Path to config.cfg for 86Box>");
		puts("	We provide some sample profiles: PRO2.cfg for CE2.0 emulation, PRO1.cfg for other emulation.");
		printf(
			"===================================LOADCEPC.exe configs===================================\n"
			"Usage: /B:baud /C:Port /D:display /P /H /V /N:name\n"
			"  (/E|/K):IO:IRQ[:<dotted IP>] /L:VXxVYxBPP[:PXxPY] <file name>\n"
			"\n"
			"  /B  Baud Rate [9600|19200|38400(default)|57600|115200]"
			"\n"
			"  /C  Communications Port [0=disable|1|2|3|4]"
			"\n"
			"  /D  Display Resolution (for VESA modes, use the /L option instead).\n"
			"      0 = 320x200x256 (default), 1 = 480x240x256,\n"
			"      2 = 640x480x256, 3 = 800x600x256, 4 = 1024x768x256\n"
			"      5 = 240x320x256, 6 = 208x240x256\n"
			"\n"
			"  /P  Parallel port boot download.\n"
			"\n"
			"  /A  Use permanent storage device to store NK image.\n"
			"\n"
			"  /H  Help - displays this message.\n"
			"\n"
			"  Default <file name> is NK.BIN except for /P option which uses\n"
			"  default on host unless <file name> specified.\n"
			"\n" 
			"  (/E|/K):IO:IRQ[:<dotted IP>] /L:VXxVYxBPP[:PXxPY] <file name>\n"
			"\n"
			"  /V  Verbose - displays extra status information during boot.\n"
			"\n"
			"  /E:IO:IRQ[:<dotted IP>]  (Debug Ethernet Card parameters)\n"
			"      IO - IO Base Address (specified in hexadecimal)\n"
			"      IRQ - Interrupt (specified in decimal or hexadecimal)\n"
			"      Dotted IP - (optional) static IP address (No DHCP)\n"
			"    NOTE: The /E and /K options are mutually exclusive.\n"
			"\n"
			"  /K:IO:IRQ[:<dotted IP>]  (RNDIS Card parameters)\n"
			"      IO - IO Base Address (specified in hexadecimal)\n"
			"      IRQ - Interrupt (specified in decimal or hexadecimal)\n"
			"      Dotted IP - (optional) static IP address (No DHCP)\n"
			"    NOTE: The /E and /K options are mutually exclusive.\n"
			"\n"
			"  /L:DXxDYxBPP[:PXxPY] (Use VESA VBE Linear/Flat Framebuffer video mode)\n"
			"      DX, DY  - Display X and Y Sizes\n"
			"      BPP - Bits Per Pixel Color Depth (8, 16, 24, or 32)\n"
			"      PX, PY  - (optional) Physical Screen X and Y Sizes to simulate a\n"
			"                small device display (PX & PY should be greater than DX & DY)."
			"\n"
			" /N:name  Optionally specify a device name to be used when creating\n"
			"          the Ethernet debug name (for host-side connectivity).\n"
			"\n"
			"Usage: -s[:]<pattern> -(g|r|u)[[:]<pattern> [<destination>]\n"
			"-s    Show a directory of files matching <pattern>.\n"
			"\n"
			"-g    Get files matching <pattern> and copy them to the\n"
			"      optionally specified <destination>.  Any existing file with\n"
			"      the same name will be overwritten.\n"
			"\n"
			"-r    Refresh files matching <pattern> which already exist in <destination>\n"
			"      and have a timestamp newer than the one in <destination>.\n"
			"\n"
			"-u    Update files matching <pattern> which don't already exist in\n"
			"      <destination> or those that have a timestamp newer than those\n"
			"      in <destination>.\n"
			"\n"
			"<pattern> Windows filename path with optional wildcard characters.\n"
			"\n"
			"<destination> If not specified then the current directory is the default.\n"
			"      If specified and it doesn't exist and the last character is \\,\n"
			"      then the directory is created.  Otherwise <destination> is\n"
			"      treated as the name of the file.\n"
			"      It is an error for <pattern> to match multiple files\n"
			"      when <destination> specifies a file.\n"
			"========================================================================================\n"
		);
		puts("Version:100B103");
		puts("Copyright 351Workshop 2025");
		return 1;
	}


	char batBuffer[120] = { 0 };
	char profilePath[255] = ".\\PRO1.cfg";
	strcat_s(batBuffer, "loadcepc ");
	for (int i = 0; i < argc - 2; i++)
	{
		if (argv[i + 1][1] == 'M' || argv[i + 1][1] == 'm')
		{
			memset(profilePath, 0, 120);
			strcat_s(profilePath, ".\\");
			astrcpy(profilePath, argv[i + 1], 3);
		}
		else
		{
			strcat_s(batBuffer, argv[i + 1]);
			strcat_s(batBuffer, " ");
		}

	}
	strcat_s(batBuffer, "C:\\ce\\nk.bin");


	char nkPath[255] = { 0 };
	strcpy_s(nkPath, argv[argc-1]);
	char imgPath[255] = { 0 };
	char outPath[255] = { 0 };
	GetPrivateProfileString("Img", "imgPath", ".\\samp.img", imgPath, 255, ".\\whitebox.ini");
	GetPrivateProfileString("Img", "outPath", NULL, outPath, 255, ".\\whitebox.ini");
	int nkAddrOffset = GetPrivateProfileInt("Img", "nkAddrOffset", 0x81000, ".\\whitebox.ini");
	int batAddrOffset = GetPrivateProfileInt("Img", "batAddrOffset", 0x4081000, ".\\whitebox.ini");
	if (outPath[0] == NULL)
	{
		if (GetTempPath(255, outPath) == 0)
		{
			puts("Error - Can't get TEMP path");
			return 1;
		}
		if (GetTempFileName(outPath, "wboutimg", 0, outPath) == 0)
		{
			puts("Error - Can't get WBOUTIMG file name");
			return 1;
		}
	}


	printf("====================Start write img====================\n");
	printf("nkPath:...............%s\n", nkPath);
	printf("outPath:..............%s\n", outPath);
	printf("nkAddrOffset:.........%#x\n", nkAddrOffset);
	printf("batAddrOffset:........%#x\n", batAddrOffset);
	printf("batBuffer:............%s\n", batBuffer);


	if (!fileCopy(imgPath, outPath, FALSE))
	{
		puts("Error - Can't copy %%OUT.img%%");
		return 1;
	}


	HANDLE hFileNk = CreateFile(
		nkPath, // 文件路径
		GENERIC_READ, // 读取权限
		0, // 不共享
		NULL, // 默认安全属性
		OPEN_EXISTING, // 打开已存在的文件
		FILE_ATTRIBUTE_NORMAL, // 普通文件属性
		NULL // 无模板文件
	);
	if (hFileNk == INVALID_HANDLE_VALUE) {
		puts("Error - Can't open NK.bin");
		return 1;
	}
	HANDLE hFileImg = CreateFile(
		outPath, // 文件路径
		GENERIC_WRITE, // 读取权限
		0, // 不共享
		NULL, // 默认安全属性
		OPEN_EXISTING, // 打开已存在的文件
		FILE_ATTRIBUTE_NORMAL, // 普通文件属性
		NULL // 无模板文件
	);
	if (hFileImg == INVALID_HANDLE_VALUE) {
		puts("Error - Can't open OUT.img");
		return 1;
	}

	printf("Start write OUT.img: ");
	printf("********************");
	long long int iFileNkSize = GetFileSize(hFileNk, NULL);
	OVERLAPPED overlappedNk = { 0 };
	overlappedNk.Offset = 0; // 从偏移位置 0 开始读取
	overlappedNk.OffsetHigh = 0;
	long long int iFileImgSize = GetFileSize(hFileImg, NULL);
	OVERLAPPED overlappedImg = { 0 };
	overlappedImg.Offset = nkAddrOffset; // 从偏移位置 0x81000 开始写入
	overlappedImg.OffsetHigh = 0;
 	char buffer[255] = { 0 }; // 缓冲区
	DWORD bytesRead = 0;
	DWORD bytesWritten = 0;
	for (int i = 0; i < (iFileNkSize / 128)+1; i++)
	{
		strcpy_s(buffer, "");
		if (!ReadFile(
			hFileNk, // 文件句柄
			buffer, // 缓冲区
			128, // 要读取的字节数
			&bytesRead, // 实际读取的字节数
			&overlappedNk // OVERLAPPED 结构
		))
		{
			printf("Error - Can't read NK.bin at %#x\n", i * 128);
			return 1;
		}

		if (!WriteFile(
			hFileImg, 
			buffer, 
			128, 
			&bytesWritten, 
			&overlappedImg
		)) 
		{
			printf("Error - Can't write OUT.img at %#x\n", i * 128);
			return 1;
		}
		overlappedNk.Offset += 128;
		overlappedImg.Offset += 128;
		if (i % 200 == 0)
			printPrct(20, i * 100 / ((iFileNkSize / 128) + 1));
	}
	puts("");


	overlappedImg.Offset = batAddrOffset;
	if (!WriteFile(
		hFileImg,
		batBuffer,
		120,
		&bytesWritten,
		&overlappedImg
	))
	{
		printf("Error - Can't write RUNCEPC.bat on out.img\n");
		return 1;
	}
	CloseHandle(hFileNk);
	CloseHandle(hFileImg);
	printf("====================Write img done=====================\n"
		   "\n");






	char emulPath[255] = { 0 };
	char hdCfgKey[255] = { 0 };
	char proOutPath[255] = { 0 };
	char emulMch[255] = { 0 };
	char nvrPath[255] = { 0 };
	char nvrOutPath[255] = { 0 };
	char nvrOutDir[255] = { 0 };
	char emulCommand[255] = { 0 };
	GetPrivateProfileString("86Box", "emulPath", "86Box.exe", emulPath, 255, ".\\whitebox.ini");
	GetPrivateProfileString("86Box", "hdCfgKey", "hdd_01_fn", hdCfgKey, 255, ".\\whitebox.ini");
	GetPrivateProfileString("86Box", "enulMch", "p54tp4xe", emulMch, 255, ".\\whitebox.ini");
	GetPrivateProfileString("86Box", "nvrPath", NULL, nvrPath, 255, ".\\whitebox.ini");
	GetPrivateProfileString("86Box", "proOutPath", NULL, proOutPath, 255, ".\\whitebox.ini");
	GetPrivateProfileString("86Box", "nvrOutPath", NULL, nvrOutPath, 255, ".\\whitebox.ini");
	GetPrivateProfileString("86Box", "nvrOutDir", NULL, nvrOutDir, 255, ".\\whitebox.ini");

	if (proOutPath[0] == NULL)
	{
		if (GetTempPath(255, proOutPath) == 0)
		{
			puts("Error - Can't get TEMP path");
			return 1;
		}
		if (GetTempFileName(proOutPath, "wbproout", 0, proOutPath) == 0)
		{
			puts("Error - Can't get WBPROOUT file name");
			return 1;
		}
	}

	if (nvrOutPath[0] == NULL && nvrOutDir[0] == NULL)
	{
		if (GetTempPath(255, nvrOutPath) == 0)
		{
			puts("Error - Can't get TEMP path");
			return 1;
		}
		sprintf_s(nvrOutDir, "%s\\nvr\\", nvrOutPath);
		sprintf_s(nvrOutPath, "%s\\nvr\\%s.nvr", nvrOutPath, emulMch);
	}

	if (nvrPath[0] == NULL)
	{
		sprintf_s(nvrPath, ".\\nvr\\%s.nvr", emulMch);
	}

	printf("====================Starting 86Box=====================\n");
	printf("outPath:..............%s\n", outPath);
	printf("profilePath:..........%s\n", profilePath);
	printf("proOutPath:...........%s\n", proOutPath);
	printf("emulPath:.............%s\n", emulPath);
	printf("emulMchName...........%s\n", emulMch);
	printf("hdCfgKey..............%s\n", hdCfgKey);
	printf("nvrPath...............%s\n", nvrPath);
	printf("nvrOutPath............%s\n", nvrOutPath);
	printf("nvrOutDir.............%s\n", nvrOutDir);

	if (!fileCopy(profilePath, proOutPath, FALSE))
		puts("Warning - Can't copy %%PROOUT.cfg%%");
	if (!CreateDirectory(nvrOutDir, NULL))
		puts("Warning - Can't create %%NVRDIR%%");
	if (!fileCopy(nvrPath, nvrOutPath, FALSE))
		puts("Warning - Can't copy %%MCH.nvr%%");
	WritePrivateProfileString("Hard disks", "hdd_01_fn", outPath, proOutPath);

	sprintf_s(emulCommand, "-V WhiteboxEmulator %s", proOutPath);
	printf("Starting 86Box as %s %s\n", emulPath, emulCommand);
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = emulPath;
	ShExecInfo.lpParameters = emulCommand;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOWNORMAL;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
	printf("====================86Box closed=======================\n"
		   "\n");

	Sleep(200);
	if (!DeleteDirectory(nvrOutDir))
		printf("Warning - Can't delete %%NVRDIR%%");
	if (!DeleteFile(proOutPath))
		printf("Warning - Can't delete %%PROOUT.cfg%%");
	if (!DeleteFile(outPath))
		printf("Warning - Can't delete %%OUT.IMG%%");
	printf("TEMP files removed.\n");

	return 0;
}
