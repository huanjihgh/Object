#ifndef _HOOK_H_
#define _HOOK_H_

#include <Windows.h>
#include <wchar.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <memory>
#include "../include/Object.hpp"
#include "../include/StrTool.hpp"
#include <list>

namespace object {


#define NKAsm __declspec(naked)

#define PushAsm \
	_asm push eax \
	_asm push ebx \
	_asm push ecx \
	_asm push edi \
	_asm push esi \
	_asm push edx 


#define PopAsm \
	_asm pop edx \
	_asm pop esi \
	_asm pop edi \
	_asm pop ecx \
	_asm pop ebx \
	_asm pop eax


	/*
	*	author:huangguoheng
	*	description:注册表工具类
	*/
	class HLIB_API Reg {
	protected:
		HKEY hKey;
	public:
		bool Open(const std::string &subKey, HKEY key = HKEY_LOCAL_MACHINE);
		~Reg();
		std::string ReadString(const std::string& key);
		DWORD ReadInt(const std::string& key);

		void Close();

	};

	class CHookFn
	{
	public:

		CHookFn(PROC hookFn, PROC oldHookFn = NULL) {
			this->oldHookFn = oldHookFn;
			this->hookFn = hookFn;
		}

		PROC oldHookFn;
		PROC hookFn;

	};

	class HLIB_API HookData
	{
	private:
		void Del();
	public:
		intptr_t Addr;
		intptr_t RetAddr;
		uint8_t * OldData;

		size_t len;

		HookData();

		HookData(intptr_t Addr,
			uint8_t * OldData);

		~HookData();



	};


	class HLIB_API HookAddr {
	public:
		HookAddr();
		HookAddr(const HookAddr & h);
		const HookAddr& operator =(const HookAddr & h);
		intptr_t RetAddr;
		intptr_t OCallAddr;
	};



	/**
	**	author:huanguoheng
	**	date:2020-05-03
	**	description:汇编工具类
	**
	**/
	class HLIB_API Assemble {

	private:
		std::list<std::shared_ptr<HookData>> HookList;


		std::shared_ptr<HookData> _Moditify(intptr_t hookAddress, BYTE *opCode, int opCodeLen);

	public:

		Assemble();

		/**
		*author：huanguoheng
		*date:2019-03-02
		*email:470136534@qq.com
		*description:module 为null 获取的是exe的基地址
		*返回值：成功为模块的基地址，失败返回0
		*/

		intptr_t GetModuleAddr(const char* module);


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
		bool Moditify(intptr_t hookAddress, BYTE *opCode, int opCodeLen);


		/***
		**	author:huangguoheng
		**	date:2020-05-03
		**	description:获取导出函数的函数地址
		**/
		intptr_t GetProcAddr(intptr_t handle, const char* fnName);
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
		std::shared_ptr<HookData> HookMethod(intptr_t hookAddress, void* hookOwnerFn, int opCodeLen);

		HookAddr HookMethod(intptr_t hookAddress, void* hookOwnerFn, int opCodeLen, intptr_t oldcallAddr);



		~Assemble();

		/**
		**	author:huangguoheng
		**	date:2020-0503
		**	description:卸载hook
		**/
		void UnHook();

	};



	/**
	**	author:huanguoheng
	**	date:2020-05-23
	**	description:进程内存读写类
	**
	**/
	class HLIB_API MemoryApi {

	private:
		HANDLE  GetProcess_1();


	public:
		MemoryApi(HANDLE hProcess);

		MemoryApi();

		bool ReadOffsetMem(intptr_t m_dwBase, intptr_t vOffset[], int vOffsetSize, void *pBuf, int pBufSize = sizeof(intptr_t));


		bool ReadMem(intptr_t m_dwBase, void *pBuf, int pBufSize);


		bool ReadOffsetPtr(intptr_t m_dwBase, intptr_t vOffset[], int vOffsetSize, intptr_t * ptr);

		bool WriteOffsetMem(intptr_t m_dwBase, intptr_t vOffset[], int vOffsetSize, void *pBuf, int pBufSize = sizeof(intptr_t));


		bool WriteOffsetPtr(intptr_t m_dwBase, intptr_t vOffset[], int vOffsetSize, intptr_t ptr);


		// <summary>
		// author:huangguoheng
		// email:470136534@qq.com
		// date:2021-04-24
		// description:修改
		// </summary>
		// <param name="arg1">参数</param>
		// <returns></returns>
		bool WriteMem(intptr_t m_dwBase, void *pBuf, int pBufSize);


		//std::string ReadString()


		// <summary>
		// author:huangguoheng
		// email:470136534@qq.com
		// date:2021-04-24
		// description:判断给定的地址是否是合法的地址
		// </summary>
		// <param name="arg1">参数</param>
		// <returns></returns>
		bool IsValidPtr(intptr_t Address);

		// <summary>
		// author:huangguoheng
		// email:470136534@qq.com
		// date:2021-04-24
		// description:判断给定的地址是否是合法的地址
		// </summary>
		// <param name="arg1">参数</param>
		// <returns></returns>
		bool IsValidPtr(void* Address);

	private:
		HANDLE m_hProcess;

	};

	/**
		*远程注入
		*author：huanguoheng
		*date:2019-03-02
		*email:470136534@qq.com
	*/
	class HLIB_API RemoteInject
	{
	public:

		/**
		*author：huanguoheng
		*date:2019-03-02
		*email:470136534@qq.com
		*processName:进程名称
		*返回值 通过进程名称查找进程ID，失败0
		*/

		DWORD static ProcessNameToPID(LPCWSTR processName);

		/**
		*author：huanguoheng
		*date:2019-03-02
		*email:470136534@qq.com
		*processName:进程的名称
		*dllPath：要注入的dll
		*返回值：成功将返回远程线程的句柄。否则0
		*/
		HANDLE Inject(LPCWSTR processName, LPSTR dllPath);


		/**
		*author：huanguoheng
		*date:2019-03-02
		*email:470136534@qq.com
		*PID:进程的号
		*dllPath：要注入的dll
		*返回值：成功将返回远程线程的句柄。否则0
		*/
		HANDLE Inject(DWORD PID, LPSTR dllPath);

		/**
		*author：huanguoheng
		*date:2019-03-02
		*email:470136534@qq.com
		*参数dllPath:我们要注入的dll
		*参数appPaht:要注入的app
		*返回值：成功放回非0值
		*/
		HANDLE RunApp(LPWSTR dllPath, LPWSTR appPath,LPWSTR cmdParams);

		void Wait(HANDLE hRemote);

	private:

	};



	///特征码工具类
	class HLIB_API SigMaskHelper {
	public:

		//获取二进制文件的基地址
		static DWORD GetModuleBase(HMODULE hModule);

		//获取二进制文件的大小
		static DWORD GetModuleSize(HMODULE hModule);



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
		static int FindAddr(const char *Buff, const char *ModuleName, intptr_t* result, int resultLen);
		/**
		*author:huangguoheng
		*date:2019-03-16
		*description:通过特征码获取特征码地址,在当前进程中查找所有模块的特征码地址
		* Buff 特征码
		*result 保存返回的地址
		*resultLen 最多获取特征码结果的数量
		* 返回查找到的结果数量
		*/
		static int FindAddress(DWORD PID, const char *Buff, intptr_t* result, int resultLen);

		/**
		*author:huangguoheng
		*date:2019-03-16
		*description:通过特征码获取特征码地址,在当前进程中查找所有模块的特征码地址
		* Buff 特征码
		*result 保存返回的地址
		*resultLen 最多获取特征码结果的数量
		* 返回查找到的结果数量
		*/
		static int FindAddress(const char *Buff, intptr_t* result, int resultLen);

		static void FindFunctionAddr(const char *Buff, int OffsetSize, const char *ModuleName, char *Regexp);


		static void FindCallAddr(const char *Buff, int OffsetSize, const char *ModuleName, char *Regexp);

		/***
		* Buff1 开始搜索的内存地址的开始位置
		*Buff2 要被搜索的内存内容 就是特征码
		* Buff1Size buff1的大小
		* Buff2Size 特征码的长度
		*/
		static BYTE *MemoryFind(BYTE *Buff1, BYTE *Buff2, DWORD Buff1Size, DWORD Buff2Size);


		static BOOL GetProcessModuleHandle(DWORD PID, const char*szModuleName, MODULEENTRY32 *pModule);


		static BOOL VaidAddr(DWORD PID, intptr_t point);



		static BOOL StringToByte(const char *InBuff, unsigned char *OutBuff);

	};

	//
	//author:huangguoheng
	//date:2020-02-14
	//window工具类
	//
	class HLIB_API WinHelper {
	public:
		/**
		**author:huangguoheng
		**description:判断是否已经有存在的窗口在允许
		**/
		static bool HasWindow(const std::string& name);

		static HWND FindWin(const std::string& name);

		// <summary>
		// author:huangguoheng
		// email:470136534@qq.com
		// date:2021-06-22
		// description:获取文件版本号
		// </summary>
		// <param name="arg1">参数</param>
		// <returns></returns>
		static std::string  GetSoftVersion(const std::string& exepath);
	};

}
#endif // 