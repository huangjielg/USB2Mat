#pragma once
class CEnablePriv
{
public:            //公有(对外开放的接口)

//
//设置当前进程优先级为最高(实时)
//
	BOOL SetRealTimePriority();

	//
	//提升当前进程权限函数("SeShutdownPrivilege"关机权限)
	//
	BOOL EnableShutdownPriv();

	//
	//提升当前进程权限函数("SeDebugPrivilege"读、写控制权限)
	//
	BOOL EnableDebugPriv();

	//
	//提升当前进程权限函数("SeBackupPrivilege"注册表备份权限)
	//
	BOOL EnableBackupPriv();

	//
	//提升当前进程权限函数("SeRestorePrivilege"恢复数据权限)
	//
	BOOL EnableRestorePriv();

private:           //私有(内部使用的接口)

};