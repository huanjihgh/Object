


#include <Windows.h>
#include <wchar.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <memory>
#include "../include/StrTool.hpp"
#include <list>
#include "../include/Hook.h"
namespace object {


	bool Reg::Open(const std::string &subKey, HKEY key) {
		std::wstring k = object::StrTool::ToString(subKey);
		return ERROR_SUCCESS == RegOpenKeyEx(key, k.c_str(), NULL, KEY_READ | KEY_WOW64_64KEY, &hKey);
	}
	Reg::~Reg() {
		this->Close();
	}
	std::string Reg::ReadString(const std::string& key) {
		std::wstring k = object::StrTool::ToString(key);
		DWORD dwDataType = REG_SZ;
		//std::wstring s;
		wchar_t buf[1000] = { 0 };
		DWORD dwSize = 1000;

		//s.resize(dwSize);		

		LPBYTE p = (LPBYTE)buf;
		if (ERROR_SUCCESS == RegQueryValueEx(hKey, k.c_str(), NULL, &dwDataType, p, &dwSize)) {
			return object::StrTool::ToString(buf);
		}
		else {
			return nullptr;
		}

	}
	DWORD Reg::ReadInt(const std::string& key) {
		std::wstring k = object::StrTool::ToString(key);
		DWORD dwDataType = REG_DWORD;
		DWORD dwSize = sizeof(DWORD);

		DWORD szLocation = 0;

		if (ERROR_SUCCESS == RegQueryValueExW(hKey, k.c_str(), NULL, &dwDataType, (LPBYTE)&szLocation, &dwSize)) {

			return szLocation;
		}
		else {
			return -1;
		}

	}

	void Reg::Close() {
		RegCloseKey(hKey);
	}



	void HookData::Del() {
		if (this->OldData) {
			delete[]this->OldData;
			this->OldData = nullptr;
		}

	}


	HookData::HookData() :Addr(0), OldData(nullptr) {}

	HookData::HookData(intptr_t Addr,
		uint8_t * OldData) : Addr(Addr) {
		size_t len = std::strlen((char *)OldData);

		this->OldData = new uint8_t[len + 1];

		std::memcpy(this->OldData, OldData, len);
		this->OldData[len] = 0;
		this->len = len;

		this->RetAddr = this->Addr + 5;
	}

	HookData::~HookData() {
		this->Del();
	}


	HookAddr::HookAddr() :OCallAddr(), RetAddr() {}
	HookAddr::HookAddr(const HookAddr & h) {
		this->OCallAddr = h.OCallAddr;
		this->RetAddr = h.RetAddr;
	}
	const HookAddr& HookAddr::operator =(const HookAddr & h) {
		this->OCallAddr = h.OCallAddr;
		this->RetAddr = h.RetAddr;
		return *this;
	}






	std::shared_ptr<HookData> Assemble::_Moditify(intptr_t hookAddress, BYTE *opCode, int opCodeLen) {

		//打开进程
		HANDLE hWHND = OpenProcess(PROCESS_ALL_ACCESS, NULL, GetCurrentProcessId());
		SIZE_T len = 0;

		BYTE backCode[500] = { 0 };

		//int l = 0;
		//备份数据
		if (ReadProcessMemory(hWHND, (LPVOID)hookAddress, backCode, opCodeLen, &len) == 0) {
			MessageBox(NULL, L"hook地址的数据读取失败", L"读取失败", MB_OK);
			return nullptr;
		}

		//真正的hook开始了 把我们要替换的函数地址写进去 让他直接跳到我们函数里面去然后我们处理完毕后再放行吧！
		if (WriteProcessMemory(hWHND, (LPVOID)hookAddress, opCode, opCodeLen, NULL) == 0) {
			MessageBox(NULL, L"hook写入失败，函数替换失败", L"错误", MB_OK);
			return nullptr;
		}



		return std::make_shared<HookData>(
			hookAddress,
			backCode
			);
	}



	Assemble::Assemble() :HookList() {}

	/**
	*author：huanguoheng
	*date:2019-03-02
	*email:470136534@qq.com
	*description:module 为null 获取的是exe的基地址
	*返回值：成功为模块的基地址，失败返回0
	*/

	intptr_t Assemble::GetModuleAddr(const char* module)
	{
		HMODULE address = GetModuleHandleA(module);
		if (address)
			return (intptr_t)address;
		address = LoadLibraryA(module);
		return (intptr_t)address;
	}


	/**
	*author：huanguoheng
	*date:2019-03-02
	*email:470136534@qq.com
	*更新指令
	*参数：hookAddress，要修改的指令地址位置
	*参数：opCode ，指令的机器码
	*参数：opCodeLen，指令的长度
	*参数：backCode原来的指令
	*返回值：成功返回原来的指令长度，失败返回0
	**/
	bool Assemble::Moditify(intptr_t hookAddress, BYTE *opCode, int opCodeLen) {
		auto hdata = this->_Moditify(hookAddress, opCode, opCodeLen);

		if (!hdata)
			return false;

		this->HookList.push_back(hdata);

		return true;
	}


	/***
	**	author:huangguoheng
	**	date:2020-05-03
	**	description:获取导出函数的函数地址
	**/
	intptr_t Assemble::GetProcAddr(intptr_t handle, const char* fnName) {
		return (intptr_t)GetProcAddress((HMODULE)handle, fnName);
	}


	/**
	*author：huanguoheng
	*date:2019-03-02
	*email:470136534@qq.com
	*更新指令
	*参数：hookAddress，要修改的指令地址位置
	*参数：hookOwnerFn ，我们自己的函数，会被调用
	*参数：opCodeLen，穿进去我们的指令的长度，远跳转默认是5，可能我们会填充内容
	* 返回值，0失败，成功返回原指令的长度
	* __declspec(naked) 注入方法在方法前面加上这句话
	**/
	std::shared_ptr<HookData> Assemble::HookMethod(intptr_t hookAddress, void* hookOwnerFn, int opCodeLen) {


		//打开进程

		//0x90 是空指令机器码
		BYTE JmpCode[20] = { 0x90 };
		int HOOK_LEN = 5;

		//我们需要组成一段这样的数据
		// E9 11051111(这里是跳转的地方这个地方不是一个代码地址 而是根据hook地址和跳转的代码地址的距离计算出来的)
		JmpCode[0] = 0xE9;
		//计算跳转的距离公式是固定的
		//计算公式为 跳转的地址(也就是我们函数的地址) - hook的地址 - hook的字节长度
		*(intptr_t *)&JmpCode[1] = (intptr_t)hookOwnerFn - hookAddress - HOOK_LEN;

		for (int i = HOOK_LEN; i < 20; i++) {
			JmpCode[i] = { 0x90 };
		}

		auto hdata = this->_Moditify(hookAddress, JmpCode, opCodeLen);

		if (hdata) {

			this->HookList.push_back(hdata);
		}
		return hdata;
	}

	HookAddr Assemble::HookMethod(intptr_t hookAddress, void* hookOwnerFn, int opCodeLen, intptr_t oldcallAddr) {
		auto xx = this->HookMethod(hookAddress, hookOwnerFn, opCodeLen);
		HookAddr h;
		if (xx) {

			h.OCallAddr = oldcallAddr;
			h.RetAddr = xx->RetAddr;
		}

		return h;
	}



	Assemble::~Assemble() {
		this->UnHook();
	}

	/**
	**	author:huangguoheng
	**	date:2020-0503
	**	description:卸载hook
	**/
	void Assemble::UnHook() {
		auto b = this->HookList.begin();
		auto e = this->HookList.end();

		for (; b != e; b++) {
			this->_Moditify((*b)->Addr, (*b)->OldData, (*b)->len);
		}

		this->HookList.clear();
	}




	HANDLE  MemoryApi::GetProcess_1() {
		HANDLE  hProcess;

		DuplicateHandle(
			::GetCurrentProcess(),//当前进程

			::GetCurrentProcess(), //要复制内核对象是当前进程句柄

			::GetCurrentProcess(), //复制到当前进程

			&hProcess, //获得句柄值
			0, FALSE, DUPLICATE_SAME_ACCESS);
		return hProcess;
	}

	MemoryApi::MemoryApi(HANDLE hProcess) :m_hProcess(hProcess) {
	}

	MemoryApi::MemoryApi() {
		this->m_hProcess = GetProcess_1();
	}

	bool MemoryApi::ReadOffsetMem(intptr_t m_dwBase, intptr_t vOffset[], int vOffsetSize, void *pBuf, int pBufSize) {
		SIZE_T dwTemp = 0;
		void* pBaseAddr = (void*)m_dwBase;
		intptr_t dwAddr = 0;
		for (int k = 0; k < vOffsetSize; k++) {
			if (!::ReadProcessMemory(this->m_hProcess, pBaseAddr, &dwAddr, sizeof(intptr_t), &dwTemp)) {
				return false;
			}
			pBaseAddr = (void*)(dwAddr - vOffset[k]);
		}

		return ::ReadProcessMemory(this->m_hProcess, pBaseAddr, pBuf, pBufSize, &dwTemp) && dwTemp > 0;
	}


	bool MemoryApi::ReadMem(intptr_t m_dwBase, void *pBuf, int pBufSize) {
		return this->ReadOffsetMem(m_dwBase, nullptr, 0, pBuf, pBufSize);
	}


	bool MemoryApi::ReadOffsetPtr(intptr_t m_dwBase, intptr_t vOffset[], int vOffsetSize, intptr_t * ptr) {
		return this->ReadOffsetMem(m_dwBase, vOffset, vOffsetSize, ptr, sizeof(intptr_t));
	}

	bool MemoryApi::WriteOffsetMem(intptr_t m_dwBase, intptr_t vOffset[], int vOffsetSize, void *pBuf, int pBufSize ) {
		SIZE_T dwTemp = 0;
		void* pBaseAddr = (void*)m_dwBase;
		intptr_t dwAddr = 0;
		for (int k = 0; k < vOffsetSize; k++) {
			if (!::ReadProcessMemory(this->m_hProcess, pBaseAddr, &dwAddr, sizeof(intptr_t), &dwTemp)) {
				return false;
			}
			pBaseAddr = (void*)(dwAddr - vOffset[k]);
		}

		return ::WriteProcessMemory(this->m_hProcess, pBaseAddr, pBuf, pBufSize, &dwTemp) && dwTemp > 0;
	}


	bool MemoryApi::WriteOffsetPtr(intptr_t m_dwBase, intptr_t vOffset[], int vOffsetSize, intptr_t ptr) {
		return this->WriteOffsetMem(m_dwBase, vOffset, vOffsetSize, (void*)ptr);
	}


	// <summary>
	// author:huangguoheng
	// email:470136534@qq.com
	// date:2021-04-24
	// description:修改
	// </summary>
	// <param name="arg1">参数</param>
	// <returns></returns>
	bool MemoryApi::WriteMem(intptr_t m_dwBase, void *pBuf, int pBufSize) {
		return this->WriteOffsetMem(m_dwBase, nullptr, 0, pBuf, pBufSize);
	}


	// <summary>
	// author:huangguoheng
	// email:470136534@qq.com
	// date:2021-04-24
	// description:判断给定的地址是否是合法的地址
	// </summary>
	// <param name="arg1">参数</param>
	// <returns></returns>
	bool MemoryApi::IsValidPtr(intptr_t Address) {
		unsigned char ch;
		SIZE_T dwTemp = 0;
		return ::ReadProcessMemory(this->m_hProcess, (void*)Address, &ch, sizeof(ch), &dwTemp);
	}

	// <summary>
	// author:huangguoheng
	// email:470136534@qq.com
	// date:2021-04-24
	// description:判断给定的地址是否是合法的地址
	// </summary>
	// <param name="arg1">参数</param>
	// <returns></returns>
	bool MemoryApi::IsValidPtr(void* Address) {
		unsigned char ch;
		SIZE_T dwTemp = 0;
		return ::ReadProcessMemory(this->m_hProcess, Address, &ch, sizeof(ch), &dwTemp);
	}



	/**
	*author：huanguoheng
	*date:2019-03-02
	*email:470136534@qq.com
	*processName:进程名称
	*返回值 通过进程名称查找进程ID，失败0
	*/

	DWORD RemoteInject::ProcessNameToPID(LPCWSTR processName)
	{
		wchar_t buffText[0x100] = { 0 };
		//创建进程快照
		HANDLE ProcessAll = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 processInfo = { 0 };
		processInfo.dwSize = sizeof(PROCESSENTRY32);
		do
		{
			if (wcscmp(processName, processInfo.szExeFile) == 0) {
				//swprintf_s(buffText, L"进程名称=%s 进程ID=%d \r\n", processInfo.szExeFile, processInfo.th32ProcessID);
				//OutputDebugString(buffText);
				return processInfo.th32ProcessID;
			}
		} while (Process32Next(ProcessAll, &processInfo));

		return 0;
	}

	/**
	*author：huanguoheng
	*date:2019-03-02
	*email:470136534@qq.com
	*processName:进程的名称
	*dllPath：要注入的dll
	*返回值：成功将返回远程线程的句柄。否则0
	*/
	HANDLE RemoteInject::Inject(LPCWSTR processName, LPSTR dllPath) {
		wchar_t buff[0x100] = { 0 };
		//获取目标进程PID
		DWORD PID = ProcessNameToPID(processName);
		if (PID == 0) {
			MessageBox(NULL, L"没有找到该进程，可能为启动该软件", L"没有找到", MB_OK);
			return 0;
		}
		else {
			//找到pid我们就打开进程
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID);
			if (NULL == hProcess) {
				MessageBox(NULL, L"进程打开失败", L"错误", MB_OK);
				return 0;
			}
			else {
				DWORD strSize = strlen(dllPath) * 2;
				//进程打开后我们把我们的dll路径存进去
				//首先申请一片内存用于储存dll路径
				LPVOID allocRes = VirtualAllocEx(hProcess, NULL, strSize, MEM_COMMIT, PAGE_READWRITE);
				if (NULL == allocRes) {
					MessageBox(NULL, L"内存申请失败", L"错误", MB_OK);
					return 0;
				}

				//申请好后 我们写入路径到目标内存当中
				if (WriteProcessMemory(hProcess, allocRes, dllPath, strSize, NULL) == 0) {
					MessageBox(NULL, L"DLL路径写入失败", L"错误", MB_OK);
					return 0;
				}
				//路径写入 成功后我们现在获取LoadLibraryW 基址
				//LoadLibraryW 在Kernel32.dll里面 所以我们先获取这个dll的基址
				HMODULE hModule = GetModuleHandle(L"Kernel32.dll");
				LPVOID address = GetProcAddress(hModule, "LoadLibraryA");

				//通过远程线程执行这个函数 参数传入 我们dll的地址
				//开始注入dll
				HANDLE hRemote = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)address, allocRes, 0, NULL);
				if (NULL == hRemote) {
					MessageBox(NULL, L"远程执行失败", L"错误", MB_OK);
					return 0;
				}
				/*	WaitForSingleObject(hRemote, INFINITE);
					CloseHandle(hRemote);*/
				return hRemote;
			}
		}
	}


	/**
	*author：huanguoheng
	*date:2019-03-02
	*email:470136534@qq.com
	*PID:进程的号
	*dllPath：要注入的dll
	*返回值：成功将返回远程线程的句柄。否则0
	*/
	HANDLE RemoteInject::Inject(DWORD PID, LPSTR dllPath) {
		wchar_t buff[0x100] = { 0 };

		{
			//找到pid我们就打开进程
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID);
			if (NULL == hProcess) {
				MessageBox(NULL, L"进程打开失败", L"错误", MB_OK);
				return 0;
			}
			else {
				DWORD strSize = strlen(dllPath) * 2;
				//进程打开后我们把我们的dll路径存进去
				//首先申请一片内存用于储存dll路径
				LPVOID allocRes = VirtualAllocEx(hProcess, NULL, strSize, MEM_COMMIT, PAGE_READWRITE);
				if (NULL == allocRes) {
					MessageBox(NULL, L"内存申请失败", L"错误", MB_OK);
					return 0;
				}

				//申请好后 我们写入路径到目标内存当中
				if (WriteProcessMemory(hProcess, allocRes, dllPath, strSize, NULL) == 0) {
					MessageBox(NULL, L"DLL路径写入失败", L"错误", MB_OK);
					return 0;
				}
				//路径写入 成功后我们现在获取LoadLibraryW 基址
				//LoadLibraryW 在Kernel32.dll里面 所以我们先获取这个dll的基址
				HMODULE hModule = GetModuleHandle(L"Kernel32.dll");
				LPVOID address = GetProcAddress(hModule, "LoadLibraryA");

				//通过远程线程执行这个函数 参数传入 我们dll的地址
				//开始注入dll
				HANDLE hRemote = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)address, allocRes, 0, NULL);
				if (NULL == hRemote) {
					//MessageBox(NULL, L"远程执行失败", L"错误", MB_OK);
					return 0;
				}
				/*	WaitForSingleObject(hRemote, INFINITE);
					CloseHandle(hRemote);*/
				return hRemote;
			}
		}
	}

	/**
	*author：huanguoheng
	*date:2019-03-02
	*email:470136534@qq.com
	*参数dllPath:我们要注入的dll
	*参数appPaht:要注入的app
	*返回值：成功放回非0值
	*/
	HANDLE RemoteInject::RunApp(LPWSTR dllPath, LPWSTR appPath,LPWSTR cmdParams) {

		STARTUPINFO si = { 0 };
		PROCESS_INFORMATION pi = { 0 };
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOW;

		CreateProcess(appPath, cmdParams, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
		LPVOID Param = VirtualAllocEx(pi.hProcess, NULL, MAX_PATH, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		TCHAR add[0x100] = { 0 };

		WriteProcessMemory(pi.hProcess, Param, dllPath, wcslen(dllPath) * 2 + sizeof(char), NULL);

		TCHAR buff[0x100] = { 0 };
		HMODULE hModule = GetModuleHandle(L"Kernel32.dll");
		LPVOID address = GetProcAddress(hModule, "LoadLibraryW");
		/*
		通过远程线程执行这个函数 参数传入 我们dll的地址
		开始注入dll*/
		HANDLE hRemote = CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)address, Param, 0, NULL);
		if (NULL == hRemote) {
			MessageBox(NULL, L"远程执行失败", L"错误", MB_OK);
			return hRemote;
		}
		///休眠主线程让我们的注入可以修改指令
		Sleep(400);
		//重启主我们要注入的应用
		ResumeThread(pi.hThread);


		//HANDLE hRemote = 0;
		return hRemote;
	}

	void RemoteInject::Wait(HANDLE hRemote) {
		WaitForSingleObject(hRemote, INFINITE);
		CloseHandle(hRemote);
	}



	//获取二进制文件的基地址
	DWORD SigMaskHelper::GetModuleBase(HMODULE hModule)
	{
		MEMORY_BASIC_INFORMATION mem;

		if (!VirtualQuery(hModule, &mem, sizeof(MEMORY_BASIC_INFORMATION)))
			return 0;

		return (DWORD)mem.AllocationBase;
	}

	//获取二进制文件的大小
	DWORD SigMaskHelper::GetModuleSize(HMODULE hModule)
	{
		return ((IMAGE_NT_HEADERS *)((DWORD)hModule + ((IMAGE_DOS_HEADER *)hModule)->e_lfanew))->OptionalHeader.SizeOfImage;
	}



	/**
	*author:huangguoheng
	*date:2019-03-16
	*description:通过特征码获取特征码地址
	* Buff 特征码
	* ModuleName 模块名称，在这个模块里面找特征码
	*result 保存返回的地址
	*resultLen 最多获取特征码结果的数量
	*return 返回查找到多少个结果
	*/
	int SigMaskHelper::FindAddr(const char *Buff, const char *ModuleName, intptr_t* result, int resultLen)
	{
		MODULEENTRY32 Module32;
		if (GetProcessModuleHandle(GetCurrentProcessId(), ModuleName, &Module32) == FALSE)
			return 0;//如果没找到该模块则返回
		DWORD BuffLen = strlen(Buff) / 2;//保存传入字符串的长度
		BYTE *OutBuff = new BYTE[BuffLen];//零时变量保存转换后的数组,+3是因为
		if (!StringToByte(Buff, OutBuff))
		{//如果转换失败则释放内存返回
			delete[] OutBuff;
			return 0;
		}
		BYTE *Temp = MemoryFind(Module32.modBaseAddr, OutBuff, Module32.modBaseSize, BuffLen);//保存一个零时变量来保存返回值的

		int index = 0;
		while (Temp)//找到一个特征码的位置了
		{
			///强制转换他为指针整数
			result[index] = (intptr_t)Temp;
			index++;

			if (index >= resultLen) {
				break;
			}
			Temp = MemoryFind(Temp + 1, OutBuff, Module32.modBaseSize - (Temp - Module32.modBaseAddr), BuffLen);
		}
		delete[]OutBuff;
		return index;
	}

	/**
	*author:huangguoheng
	*date:2019-03-16
	*description:通过特征码获取特征码地址,在当前进程中查找所有模块的特征码地址
	* Buff 特征码
	*result 保存返回的地址
	*resultLen 最多获取特征码结果的数量
	* 返回查找到的结果数量
	*/
	int SigMaskHelper::FindAddress(DWORD PID, const char *Buff, intptr_t* result, int resultLen) {

		HANDLE handle;
		MODULEENTRY32  Module32;
		memset(&Module32, 0, sizeof(Module32));
		Module32.dwSize = sizeof(Module32);
		BOOL bRet = FALSE;
		handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
		if (handle == INVALID_HANDLE_VALUE) return false;
		bRet = Module32First(handle, &Module32);

		intptr_t* cresult = result;
		char buf[600] = { 0 };
		int index = 0;
		int size = 0;
		while (bRet)
		{
			//memset(buf, 0, 600);
			//StringConvert::UnicodeToANSI(buf, Module32.szModule);

			std::string buf= object::StrTool::Wide2Ansi(Module32.szModule);

			index = FindAddr(Buff, buf.c_str(), cresult, resultLen);

			cresult = cresult + index;
			resultLen -= index;
			size += index;
			if (resultLen < 1)
				break;
			bRet = Module32Next(handle, &Module32);
		}
		CloseHandle(handle);
		return size;
	}

	/**
	*author:huangguoheng
	*date:2019-03-16
	*description:通过特征码获取特征码地址,在当前进程中查找所有模块的特征码地址
	* Buff 特征码
	*result 保存返回的地址
	*resultLen 最多获取特征码结果的数量
	* 返回查找到的结果数量
	*/
	int SigMaskHelper::FindAddress(const char *Buff, intptr_t* result, int resultLen) {
		return FindAddress(GetCurrentProcessId(), Buff, result, resultLen);
	}

	void SigMaskHelper::FindFunctionAddr(const char *Buff, int OffsetSize, const char *ModuleName, char *Regexp)
	{
		MODULEENTRY32 Module32;
		if (GetProcessModuleHandle(GetCurrentProcessId(), ModuleName, &Module32) == FALSE)
			return;//如果没找到该模块则返回
		DWORD BuffLen = strlen(Buff) / 2;//保存传入字符串的长度
		BYTE *OutBuff = new BYTE[BuffLen];//零时变量保存转换后的数组,+3是因为
		if (!StringToByte(Buff, OutBuff))
		{//如果转换失败则释放内存返回
			delete[]OutBuff;
			return;
		}
		BYTE *Temp = MemoryFind(Module32.modBaseAddr, OutBuff, Module32.modBaseSize, BuffLen);//保存一个零时变量来保存返回值的
		while (Temp)
		{
			char DbgOutBuff[MAX_PATH] = { 0 };
			sprintf_s(DbgOutBuff, Regexp, (int)Temp + OffsetSize);
			//OutputDebugString(DbgOutBuff);
			Temp = MemoryFind(Temp + 1, OutBuff, Module32.modBaseSize - (Temp - Module32.modBaseAddr), BuffLen);
		}
		delete[]OutBuff;
	}


	void SigMaskHelper::FindCallAddr(const char *Buff, int OffsetSize, const char *ModuleName, char *Regexp)
	{
		MODULEENTRY32 Module32;
		if (GetProcessModuleHandle(GetCurrentProcessId(), ModuleName, &Module32) == FALSE)
			return;//如果没找到该模块则返回
		DWORD BuffLen = strlen(Buff) / 2;//保存传入字符串的长度
		BYTE *OutBuff = new BYTE[BuffLen];//零时变量保存转换后的数组,+3是因为
		if (!StringToByte(Buff, OutBuff))
		{//如果转换失败则释放内存返回
			delete[]OutBuff;
			return;
		}
		BYTE *Temp = MemoryFind(Module32.modBaseAddr, OutBuff, Module32.modBaseSize, BuffLen);//保存一个零时变量来保存返回值的
		while (Temp)
		{
			DWORD CallAddr = *(DWORD*)(Temp + OffsetSize + 1) + (int)Temp + OffsetSize + 5;
			char DbgOutBuff[MAX_PATH] = { 0 };
			sprintf_s(DbgOutBuff, Regexp, CallAddr);
			//OutputDebugString(DbgOutBuff);
			Temp = MemoryFind(Temp + 1, OutBuff, Module32.modBaseSize - (Temp - Module32.modBaseAddr), BuffLen);
		}
		delete[]OutBuff;
	}

	/***
	* Buff1 开始搜索的内存地址的开始位置
	*Buff2 要被搜索的内存内容 就是特征码
	* Buff1Size buff1的大小
	* Buff2Size 特征码的长度
	*/
	BYTE *SigMaskHelper::MemoryFind(BYTE *Buff1, BYTE *Buff2, DWORD Buff1Size, DWORD Buff2Size)
	{
		if (Buff1Size < Buff2Size)
			return NULL;
		for (DWORD Count1 = 0; Count1 + Buff2Size <= Buff1Size; Count1++)
		{
			DWORD Count2 = 0;
			for (; Count2 < Buff2Size; Count2++)
			{
				if (Buff2[Count2] == 0)
					continue;
				if (Buff1[Count1 + Count2] != Buff2[Count2])
					break;
			}
			if (Count2 == Buff2Size)
			{
				return &Buff1[Count1];
			}
		}
		return NULL;
	}


	BOOL SigMaskHelper::GetProcessModuleHandle(DWORD PID, const char*szModuleName, MODULEENTRY32 *pModule)
	{
		BOOL FunctionRetn = FALSE;
		HANDLE handle;
		MODULEENTRY32  Module32;
		memset(&Module32, 0, sizeof(Module32));
		Module32.dwSize = sizeof(Module32);
		BOOL bRet = FALSE;
		handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
		if (handle == INVALID_HANDLE_VALUE) return FunctionRetn;
		bRet = Module32First(handle, &Module32);
		while (bRet)
		{

			//char buf[600] = { 0 };
			//StringConvert::UnicodeToANSI(buf, Module32.szModule);
			std::string buf = object::StrTool::Wide2Ansi(Module32.szModule);

			if (strcmp(szModuleName, buf.c_str()) == 0)
			{
				memcpy(pModule, &Module32, sizeof(MODULEENTRY32));
				FunctionRetn = TRUE;
				break;
			}
			//		OutputDebugString(buf);
			bRet = Module32Next(handle, &Module32);
		}
		CloseHandle(handle);
		return FunctionRetn;
	}


	BOOL SigMaskHelper::VaidAddr(DWORD PID, intptr_t point)
	{
		BOOL FunctionRetn = FALSE;
		HANDLE handle;
		MODULEENTRY32  Module32;
		memset(&Module32, 0, sizeof(Module32));
		Module32.dwSize = sizeof(Module32);
		BOOL bRet = FALSE;
		handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
		if (handle == INVALID_HANDLE_VALUE) return FunctionRetn;
		bRet = Module32First(handle, &Module32);
		while (bRet)
		{

			if ((intptr_t)Module32.modBaseAddr <= point && (intptr_t(Module32.modBaseAddr + Module32.modBaseSize))) {
				return true;
			}

			/*char buf[600] = { 0 };
			StringConvert::UnicodeToANSI(buf, Module32.szModule);

			if (strcmp(szModuleName, buf) == 0)
			{
				memcpy(pModule, &Module32, sizeof(MODULEENTRY32));
				FunctionRetn = TRUE;
				break;
			}*/
			//		OutputDebugString(buf);
			bRet = Module32Next(handle, &Module32);
		}
		CloseHandle(handle);
		return false;
	}



	BOOL SigMaskHelper::StringToByte(const char *InBuff, unsigned char *OutBuff)
	{
		DWORD BuffSize = strlen(InBuff);
		if (BuffSize % 2 != 0)
		{
			MessageBox(0, L"特征有误", L"", 0);
			return FALSE;
		}
		//零时变量保存转换后的数组,+3是因为sscanf复制的是4个字节,最后一个字节时会访问越界
		BYTE *TMPBUF = new BYTE[BuffSize / 2 + 3];
		memset(TMPBUF, 0, BuffSize / 2);
		for (DWORD Index = 0; Index < BuffSize; Index += 2)
		{
			char buf[3] = { 0 };
			buf[0] = InBuff[Index];
			buf[1] = InBuff[Index + 1];
			sscanf_s(buf, "%X", &TMPBUF[Index / 2]);
		}
		memcpy(OutBuff, TMPBUF, BuffSize / 2);
		delete[]TMPBUF;
		return TRUE;
	}



	/**
	**author:huangguoheng
	**description:判断是否已经有存在的窗口在允许
	**/
	bool WinHelper::HasWindow(const std::string& name) {
		return ::FindWindowW(NULL, object::StrTool::ToString(name).c_str()) != NULL;
	}

	HWND WinHelper::FindWin(const std::string& name) {
		return ::FindWindowW(NULL, object::StrTool::ToString(name).c_str());
	}

	std::string WinHelper::GetSoftVersion(const std::string& exepath)
	{
		std::string strVersionInfo;
		if (exepath.empty())
			return strVersionInfo;
		if (_access(exepath.c_str(), 0) != 0)
			return strVersionInfo;

		HMODULE hDll = NULL;
		char szDbgHelpPath[MAX_PATH];

		sprintf_s(szDbgHelpPath, sizeof(szDbgHelpPath), "version.dll");
		hDll = ::LoadLibraryA(szDbgHelpPath);
		if (hDll == NULL)
		{
			return strVersionInfo;
		}

		typedef DWORD(WINAPI *func_GetFileVersionInfoSizeA)(LPCSTR, LPDWORD);
		func_GetFileVersionInfoSizeA p_GetFileVersionInfoSizeA =
			(func_GetFileVersionInfoSizeA)::GetProcAddress(hDll, "GetFileVersionInfoSizeA");


		typedef DWORD(WINAPI *func_GetFileVersionInfoA)(LPCSTR, DWORD, DWORD, LPVOID);
		func_GetFileVersionInfoA p_GetFileVersionInfoA =
			(func_GetFileVersionInfoA)::GetProcAddress(hDll, "GetFileVersionInfoA");


		typedef DWORD(WINAPI *func_VerQueryValueA)(LPCVOID, LPCSTR, LPVOID  *, PUINT);
		func_VerQueryValueA p_VerQueryValueA =
			(func_VerQueryValueA)::GetProcAddress(hDll, "VerQueryValueA");


		if (p_GetFileVersionInfoSizeA == NULL
			|| p_GetFileVersionInfoA == NULL
			|| p_VerQueryValueA == NULL)
		{
			if (hDll)
			{
				FreeLibrary(hDll);
				hDll = NULL;
			}
			return strVersionInfo;
		}

		UINT infoSize = p_GetFileVersionInfoSizeA(exepath.c_str(), 0);
		if (infoSize != 0) {
			strVersionInfo.resize(infoSize, 0);
			char *pBuf = NULL;
			pBuf = new char[infoSize];
			VS_FIXEDFILEINFO *pVsInfo;
			if (p_GetFileVersionInfoA(exepath.c_str(), 0, infoSize, pBuf)) {
				if (p_VerQueryValueA(pBuf, "\\", (void **)&pVsInfo, &infoSize))
				{
					sprintf_s(pBuf, infoSize, "%d.%d.%d.%d",
						HIWORD(pVsInfo->dwFileVersionMS),
						LOWORD(pVsInfo->dwFileVersionMS),
						HIWORD(pVsInfo->dwFileVersionLS),
						LOWORD(pVsInfo->dwFileVersionLS));

					strVersionInfo = pBuf;
				}
			}
			delete[] pBuf;
		}

		if (hDll)
		{
			FreeLibrary(hDll);
		}
		return strVersionInfo;
	}

}