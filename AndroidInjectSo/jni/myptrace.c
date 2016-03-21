/*
 * myptrace.c
 *
 *  Created on: May 14, 2014
 *      Author: auo
 */

#include <stdio.h>
#include <stdlib.h>
#include <asm/ptrace.h>
#include <sys/wait.h>
#include <android/log.h>
#include <errno.h>
#include "myptrace.h"

#define ENABLE_DEBUG 0

#define PTRACE_PEEKTEXT 1
#define PTRACE_POKETEXT 4
#define PTRACE_ATTACH	16
#define PTRACE_CONT 	7
#define PTRACE_DETACH   17
#define PTRACE_SYSCALL	24
#define CPSR_T_MASK		( 1u << 5 )

#define ANDROID_LOG

#ifdef ANDROID_LOG
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "hook", __VA_ARGS__))
#else
#define LOGD(format,args...)
#endif

struct pt_regs saved_regs; //= (struct pt_regs *)malloc(sizeof(struct pt_regs *));

/**
 * 异常处理
 */
void error(const char* fun) {
	perror(fun);
	exit(errno);
}

/**
 * 绑定目标进程
 */
void ptrace_attach(pid_t pid) {
	if(ptrace(PTRACE_ATTACH, pid, NULL, NULL) < 0)
		error("ptrace_attach");
	waitpid(pid, NULL, WUNTRACED);
	if(ptrace(PTRACE_GETREGS, pid, NULL, &saved_regs) < 0)
		error("ptrace_attach");
}

/**
 * 继续目标进程
 */
void ptrace_continue(pid_t pid) {
    if(ptrace(PTRACE_CONT, pid, NULL, NULL) < 0 )
    	error("ptrace_continue");
}

/**
 * 释放目标进程
 */
void ptrace_detach(pid_t pid) {
    if(ptrace( PTRACE_DETACH, pid, NULL, NULL) < 0)
    	error("ptrace_detach");
}

/**
 * 获取寄存器状态
 */
void ptrace_getregs( pid_t pid, struct pt_regs* regs ) {
    if(ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0)
    	error("ptrace_getregs");
}

/**
 * 设置寄存器状态
 */
void ptrace_setregs( pid_t pid, struct pt_regs* regs ) {
    if (ptrace(PTRACE_SETREGS, pid, NULL, regs) < 0)
    	error("ptrace_setregs");
}

/**
 * 从指定地址(src)读指定字节(size)到指定地址(buf)
 */
void ptrace_readdata( pid_t pid,  void *src, void *buf, size_t size ) {
    int i, j, remain;
    void *laddr;

    union u {
        long val;
        char chars[sizeof(long)];
    } d;

    j = size / 4;
    remain = size % 4;

    laddr = buf;

    for(i = 0; i < j; i++) {
        d.val = ptrace(PTRACE_PEEKTEXT, pid, src, 0);
        memcpy(laddr, d.chars, 4);
        src += 4;
        laddr += 4;
    }

    if(remain > 0) {
        d.val = ptrace(PTRACE_PEEKTEXT, pid, src, 0);
        memcpy(laddr, d.chars, remain);
    }
}

/**
 * 从指定地址(data)写指定字节(size)到指定地址(dest)
 */
void ptrace_writedata(pid_t pid, void *dest, void *data, size_t size) {
    int i, j, remain;
    char *laddr;

    union u {
        long val;
        char chars[sizeof(long)];
    } d;

    j = size / 4;
    remain = size % 4;

    laddr = data;

    for(i = 0; i < j; i++) {
        memcpy(d.chars, laddr, 4);
        ptrace(PTRACE_POKETEXT, pid, dest, d.val);
        dest  += 4;
        laddr += 4;
    }

    if(remain > 0) {
        d.val = ptrace(PTRACE_PEEKTEXT, pid, dest, 0);
        for(i = 0; i < remain; i ++)
            d.chars[i] = *laddr ++;
        ptrace(PTRACE_POKETEXT, pid, dest, d.val);
    }
}

/**
 * 写字符串到指定地址(dest)
 */
void ptrace_writestring(pid_t pid, void *dest, const char *str) {
    ptrace_writedata(pid, dest, (void *)str, strlen(str) + 1);
}

//long ptrace_pushdata(pid_t pid, void *addr, size_t size) {
//	long sp;
//	struct pt_regs regs;
//	memcpy( &regs, &saved_regs, sizeof(regs) );
//	sp = regs.ARM_sp;
//	sp -= size;
//	sp = sp - sp % 4;
//	regs.ARM_sp = sp;
//	ptrace_setregs(pid, &regs);
//	ptrace_writedata(pid, sp, addr, size);
//	return sp;
//}

/**
 * 调用指定函数(addr:函数地址;params:函数参数;num_params:函数参数个数)
 */
int ptrace_call( pid_t pid, uint32_t addr, uint32_t *params, int num_params, struct pt_regs *regs )
{
    int i;

    for ( i = 0; i < num_params && i < 4; i ++ ) // ??
    {
        regs->uregs[i] = params[i];
    }

    //
    // push remained params into stack
    //
    if ( i < num_params )
    {
        regs->ARM_sp -= (num_params - i) * sizeof(long) ;
        ptrace_writedata( pid, (void *)regs->ARM_sp, (uint8_t *)&params[i], (num_params - i) * sizeof(long) );
    }

    regs->ARM_pc = addr;
    if ( regs->ARM_pc & 1 ) // thumb
    {
        regs->ARM_pc &= (~1u);
        regs->ARM_cpsr |= CPSR_T_MASK;
    }
    else  // arm
    {
        regs->ARM_cpsr &= ~CPSR_T_MASK;
    }

    regs->ARM_lr = 0;	//

    ptrace_setregs(pid, regs);
    ptrace_continue(pid);
    waitpid(pid, NULL, WUNTRACED);
    return 0;
}
