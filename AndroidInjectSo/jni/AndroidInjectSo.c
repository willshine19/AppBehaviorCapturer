/*
 * AndroidInjectSo.c
 *
 *  Created on: May 14, 2014
 *      Author: auo
 */

#include <stdio.h>
#include <stdlib.h>
#include <asm/ptrace.h>
#include <dlfcn.h>
#include <dirent.h>
#include "myptrace.h"

#include <sys/wait.h>

#define PTRACE_PEEKTEXT 1
#define PTRACE_POKETEXT 4
#define PTRACE_ATTACH	16
#define PTRACE_CONT 	7
#define PTRACE_DETACH   17
#define PTRACE_SYSCALL	24
#define CPSR_T_MASK		( 1u << 5 )

#define REMOTE_ADDR( addr, local_base, remote_base ) \
    ( (uint32_t)(addr) + (uint32_t)(remote_base) - (uint32_t)(local_base) )

#define PAGE_START(addr, size) ~((size) - 1) & (addr)

#define DEBUG

#ifdef DEBUG
#define DPRINTF(format, args...) printf(format, ##args)
#else
#define DPRINTF(format, args...)
#endif

extern struct pt_regs saved_regs;

const char *libc_path 		= "/system/lib/libc.so";
const char *linker_path 	= "/system/bin/linker";
char sbuf[512];

/**
 * 获取目标进程(pid)中指定的动态库(module_name)的基地址
 */
void* get_module_base(pid_t pid, const char* module_name) {
    FILE *fp;
    uint32_t addr = 0;
    char *pch;
    char filename[32];
    char line[1024];

    if(pid < 0) {
        snprintf(filename, sizeof(filename), "/proc/self/maps");
    }
    else {
        snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    }
    fp = fopen(filename, "r");
    if(fp != NULL) {
        while(fgets(line, sizeof(line), fp)) {
            if(strstr(line, module_name)) {
                pch = strtok(line, "-");
                addr = strtoul(pch, NULL, 16);
                if(addr == 0x8000)
                    addr = 0;
                break;
            }
        }
        fclose(fp) ;
    }
    return (void *)addr;
}

/**
 * 得到目标进程(pid)中指定的动态库(module_name)中指定函数的地址
 */
void* get_remote_addr(pid_t target_pid, const char* module_name, void* local_addr) {
    void *local_module_base, *remote_module_base;
    local_module_base = get_module_base(-1, module_name);
    remote_module_base = get_module_base(target_pid, module_name);
    return (void *)REMOTE_ADDR(local_addr, local_module_base, remote_module_base);
}

/**
 * 找到指定进程名(process_name)的pid号
 */
pid_t find_pid_of(const char *process_name) {
    int id;
    pid_t pid = -1;
    DIR *dir;
    FILE *fp;
    char filename[32];
    char cmdline[256];
    struct dirent * entry;
    if (process_name == NULL)
        return -1;
    dir = opendir("/proc");
    if (dir == NULL)
        return -1;
    while((entry = readdir(dir)) != NULL) {
        id = atoi(entry->d_name);
        if (id != 0) {
            sprintf(filename, "/proc/%d/cmdline", id);
            fp = fopen(filename, "r");
            if (fp) {
                fgets(cmdline, sizeof(cmdline), fp);
                fclose(fp);
                if (strcmp(process_name, cmdline) == 0) {
                    pid = id;
                    DPRINTF("[+1]\t%s的pid号为\t: %d\n", process_name, pid);
                    break;
                }
            }
        }
    }
    closedir(dir);
    return pid;
}

/**
 * 找到指定进程(pid)中dlopen函数的地址
 */
uint32_t find_dlopen_addr(pid_t pid) {
	uint32_t dlopen_addr;
	dlopen_addr = (uint32_t)get_remote_addr(pid, linker_path, (void*)dlopen);
	//DPRINTF("dlopen_addr\t%x\n", dlopen_addr);
	return dlopen_addr;
}

/**
 * 找到指定进程(pid)中dlsym函数的地址
 */
uint32_t find_dlsym_addr(pid_t pid) {
	uint32_t dlsym_addr;
	dlsym_addr = (uint32_t)get_remote_addr(pid, linker_path, (void*)dlsym);
	//DPRINTF("dlsym_addr\t%x\n", dlsym_addr);
	return dlsym_addr;
}

/**
 * 找到指定进程(pid)中dlclose函数的地址
 */
uint32_t find_dlclose_addr(pid_t pid) {
	uint32_t dlclose_addr;
	dlclose_addr = (uint32_t)get_remote_addr(pid, linker_path, (void*)dlclose);
	//DPRINTF("dlclose_addr\t%x\n", dlclose_addr);
	return dlclose_addr;
}

//char *ptrace_readstr(int pid, size_t addr)
//{
//    char *str = (char *) malloc(64);
//    int i,count;
//    size_t word;
//    char *pa;
//
//    i = count = 0;
//    pa = (char *)&word;
//
//    while(i <= 60) {
//        word = ptrace(PTRACE_PEEKTEXT, pid, addr + count, NULL);
//        count += 4;
//
//        if (pa[0] == '\0') {
//            str[i] = '\0';
//        break;
//        }
//        else
//            str[i++] = pa[0];
//
//        if (pa[1] == '\0') {
//            str[i] = '\0';
//            break;
//        }
//        else
//            str[i++] = pa[1];
//
//        if (pa[2] == '\0') {
//            str[i] = '\0';
//            break;
//        }
//        else
//            str[i++] = pa[2];
//
//        if (pa[3] == '\0') {
//            str[i] = '\0';
//            break;
//        }
//        else
//            str[i++] = pa[3];
//    }
//    return str;
//}

/**
 * 注入指定动态库(so_path)到指定进程(pid)
 */
uint32_t *inject_so_of(pid_t pid, const char *so_path) {
	struct pt_regs regs;
	memcpy(&regs, &saved_regs, sizeof(regs));
	ptrace_readdata(pid, (void *)regs.ARM_sp, (void *)sbuf, sizeof(sbuf));
	ptrace_writedata(pid, (void *)regs.ARM_sp, (void *)so_path, strlen(so_path) + 1);
	uint32_t parameters[2];
	parameters[0] = regs.ARM_sp;
	parameters[1] = RTLD_NOW;
	if ( ptrace_call(pid, find_dlopen_addr(pid), parameters, 2, &regs ) == -1 )
		DPRINTF("dlopen error\n");
	ptrace_getregs(pid, &regs);
	uint32_t r0 = regs.ARM_r0;
	DPRINTF("[+2]\t注入动态库成功，返回的句柄为: %x\n", r0);
	ptrace_setregs(pid, &saved_regs);
	ptrace_writedata(pid, (uint8_t *)saved_regs.ARM_sp, (uint8_t *)sbuf, sizeof(sbuf));
	ptrace_detach(pid);
	return (uint32_t *)r0;
}

/**
 * 通过inject_so_of函数得到的动态库句柄(handle)调用该动态库中的函数(fun_name)
 */
uint32_t call_hook_fun(pid_t pid, void *handle, char *fun_name) {
	struct pt_regs regs;
	memcpy( &regs, &saved_regs, sizeof(regs) );
	ptrace_readdata(pid, (void *)regs.ARM_sp, (void *)sbuf, sizeof(sbuf));
	ptrace_writedata(pid, (void *)regs.ARM_sp, (void *)fun_name, strlen(fun_name) + 1);
	uint32_t parameters[2];
	parameters[0] = (uint32_t)handle;
	parameters[1] = regs.ARM_sp;
	if ( ptrace_call(pid, find_dlsym_addr(pid), parameters, 2, &regs ) == -1 )
		DPRINTF("dlsym error\n");
    ptrace_getregs(pid, &regs);
    uint32_t r0 = regs.ARM_r0;
    ptrace_writedata(pid, (void *)regs.ARM_sp, (void *)sbuf, sizeof(sbuf));
	ptrace_setregs(pid, &saved_regs);
	ptrace_detach(pid);
	ptrace_attach(pid);
	if ( ptrace_call(pid, r0, parameters, 0, &regs ) == -1 )
		DPRINTF("call error\n");
	DPRINTF("[+3]\t调用hook函数成功，函数地址为: %x\n", r0);
	ptrace_setregs(pid, &saved_regs);
	ptrace_detach(pid);
	return r0;
}

int main(int argc, char* argv[]) {
	uint32_t *handle;
	uint32_t hookfun_addr;
	// pid_t pid = find_pid_of("com.auo.androidinjectso");
	// pid_t pid = find_pid_of("com.dlgcy.preferencesdemo");
//	pid_t pid = find_pid_of("com.example.ratest");
	pid_t pid = find_pid_of(argv[1]);
//	pid_t pid = find_pid_of("com.example.allhookinone");

    // pid_t pid = find_pid_of("sam.sucl.sqltest2");
    // pid_t pid = find_pid_of("com.auo.androidinjectso");
	ptrace_attach(pid);
//	 handle = inject_so_of(pid, "/data/data/com.example.allhookinone/lib/libonehook.so");
	handle = inject_so_of(pid, "/data/inj-allhookinone/libonehook.so");
	ptrace_attach(pid);
	hookfun_addr = call_hook_fun(pid, handle, "injectInterface");
	DPRINTF("[+4]\thook成功！\n");
}
