/*
 * hook.c
 *
 *  Created on: May 14, 2014
 *      Author: auo
 */
// #include <unistd.h> 
// #include <dlfcn.h>
// #include <netdb.h>
// #include <sys/types.h>
// #include <pthread.h>
#include <stdio.h>
//#include <stdlib.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
//#include <string.h>
#include <sys/mman.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <android/log.h>
#include <sys/ioctl.h>

//#include <android/sqlite3.h>

#define ANDROID_LOG

#ifdef ANDROID_LOG
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "auo", __VA_ARGS__))
#else
#define LOGD(format,args...)
#endif

#define PAGE_START(addr, size) ~((size) - 1) & (addr)

uint32_t original_addr;
uint32_t entry_addr;
int data_length;
int call_count = 0;

// int (*old_addr) (int fd, const void *buf, size_t count) = 0;//write
// int (*old_addr) (int __fd, unsigned long int __request, void * arg) = 0;//ioctl
// int (*old_addr) (const char *pathname, int oflag,int perms) ;//open
int (*old_addr) (int fd,void * buf ,size_t count) = 0;//read

// int (*old_addr)(//sqlite3_open
//   const char *filename,   // Database filename (UTF-8) 
//   sqlite3 **ppDb          /* OUT: SQLite db handle */
// )=0;

//sqlite3_exec
// int (*old_addr)(
//   sqlite3* ppDb,                             /* An open database */
//   const char *sql,                           /* SQL to be evaluated */
//   int (*callback)(void*,int,char**,char**),  /* Callback function */
//   void *,                                    /* 1st argument to callback */
//   char **errmsg                              /* Error msg written here */
// )=0;
//sqlite3_exec
// int hook(sqlite3* ppDb,const char *sql, int (*callback)(void*,int,char**,char**),void *a,char **errmsg) {
    
//     // if ( __request == BINDER_WRITE_READ )
//     //     {
//             call_count++;
//         // LOGD("c:%d,filename:%s,**ppDb:%x",call_count,filename,ppDb);
//         LOGD("c:%d,*sql:%s",call_count,sql);

//         // }

//         int res = (*old_addr)(ppDb,sql,callback,a,errmsg);
//         return res;
// }
//sqlite3_open
// int hook(const char *filename,sqlite3 **ppDb) {//sqlite3_open
    
//     // if ( __request == BINDER_WRITE_READ )
//     //     {
//             call_count++;
//         // LOGD("c:%d,filename:%s,**ppDb:%x",call_count,filename,ppDb);
//         LOGD("c:%d,filename:%s",call_count,filename);

//         // }

//         int res = (*old_addr)(filename,ppDb);
//         return res;
// }
// int hook(int fd,void * buf ,size_t count) {//read
    
//     // if ( __request == BINDER_WRITE_READ )
//     //     {
//             call_count++;
//         LOGD("c:%d,fd:%d,buf:%s,count:%d",call_count,fd,buf,count);
//            // LOGD("c:%d,fd:%d,buf:%d,count:%d",call_count,fd,buf,count);

//         // }

//         int res = (*old_addr)(fd,buf,count);
//         LOGD("c:%d,fd:%d,buf:%s,count:%d",call_count,fd,buf,count);
//         return res;
// }
int hook(const char *pathname, int oflag,int perms) {//open
    
    // if ( __request == BINDER_WRITE_READ )
    //     {
            call_count++;
        LOGD("c:%d,pathname:%s,oflag:%d,perms:%d",call_count,pathname,oflag,perms);
        // }

        int res = (*old_addr)(pathname,oflag,perms);
        return res;
}
// int hook(int __fd, unsigned long int __request, void * arg) {//ioctl
    
//     // if ( __request == BINDER_WRITE_READ )
//     //     {
//             call_count++;
//         // LOGD("c:%d,__fd:%d,__request:%d,*arg:%d",call_count,__fd,__request,arg);
//              LOGD("c:%d,__fd:%d,__request:%d,*arg:%s",call_count,__fd,__request,arg);
//         // }

//         int res = (*old_addr)(__fd, __request, arg);
//         return res;
// }
// int hook(int fd, const void *buf, size_t count) {//write
    
//     // if ( __request == BINDER_WRITE_READ )
//     //     {
//             call_count++;
//         LOGD("c:%d,fd:%d,buf:%s,count:%d",call_count,fd,buf,count);
//                 // LOGD("c:%d,fd:%d,buf:%d,count:%d",call_count,fd,buf,count);

//         // }

//         int res = (*old_addr)(fd, buf, count);
//         return res;
// }

/**
 * 获取动态库的基地址
 */
uint32_t get_module_base(pid_t pid, const char *module_name) {
    FILE *fp = NULL;
    char *pch = NULL;
    char filename[32];
    char line[512];
    uint32_t addr = 0;
    if (pid < 0)
        snprintf(filename, sizeof(filename), "/proc/self/maps");
    else
        snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);

    if ((fp = fopen(filename, "r")) == NULL) {
        LOGD("open %s failed!", filename);
        return 0;
    }
 int c=0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, module_name)) {
            c++;
            if(c==1){
                 pch = strtok(line, "-");
            addr = strtoul(pch, NULL, 16);
            break;
            }
           
        }
    }

    fclose(fp);

    return addr;
}

/**
 * 获取动态库的绝对路径
 */
char *get_module_path(pid_t pid, const char *module_name) {
    LOGD("module_path = %s",module_name);
    FILE *fp = NULL;
    char *module_path = NULL;
    char filename[32];
    char line[512];
    if (pid < 0)
        snprintf(filename, sizeof(filename), "/proc/self/maps");
    else
        snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);

    if ((fp = fopen(filename, "r")) == NULL) {
        LOGD("open %s failed!", filename);
        return 0;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, module_name)) {
            if(line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = 0;
            module_path = strchr(line, '/');
            break;
        }
    }

    fclose(fp);

    return module_path;
}


/**
 * 找到指定符号在got表的偏移或者静态地址
 */
uint32_t find_got_entry_address(const char *module_name, const char *symbol_name) {
    uint32_t module_base;
    char *module_path;
    module_base = get_module_base(-1, module_name);

    if (module_base == 0) {
        LOGD("目标进程未找到动态库: %s", module_name);
        return -1;
    }
    LOGD("动态库%s的基地址为: 0x%x", module_name, module_base);
    module_path = get_module_path(-1, module_name);
    LOGD("动态库%s的绝对路径为: %s", module_name, module_path);
    int fd;
    // fd = open(module_path, O_RDONLY);
        fd = open(module_path, O_RDONLY);
    if (fd == -1) {
        LOGD("打开动态库%s失败", module_path);
        return -1;
    }
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *)malloc(sizeof(Elf32_Ehdr));
    if (read(fd, ehdr, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr)) {
        LOGD("读取动态库%sehdr头部信息失败", module_path);
        return -1;
    }
    //读取所需的节
    uint32_t shdr_base = ehdr -> e_shoff;
    uint16_t shnum = ehdr -> e_shnum;
    uint32_t shstr_base = shdr_base + ehdr -> e_shstrndx * sizeof(Elf32_Shdr);
    Elf32_Shdr *shstr = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr));
    lseek(fd, shstr_base, SEEK_SET);
    read(fd, shstr, sizeof(Elf32_Shdr));
    char *shstrtab = (char *)malloc(shstr -> sh_size);
    lseek(fd, shstr -> sh_offset, SEEK_SET);
    read(fd, shstrtab, shstr -> sh_size);
    Elf32_Shdr *shdr = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr));
    lseek(fd, shdr_base, SEEK_SET);
    uint16_t i;
    char *str = NULL;
    Elf32_Shdr *relplt_shdr = (Elf32_Shdr *) malloc(sizeof(Elf32_Shdr));
    Elf32_Shdr *dynsym_shdr = (Elf32_Shdr *) malloc(sizeof(Elf32_Shdr));
    Elf32_Shdr *dynstr_shdr = (Elf32_Shdr *) malloc(sizeof(Elf32_Shdr));
    Elf32_Shdr *got_shdr = (Elf32_Shdr *) malloc(sizeof(Elf32_Shdr));
    for(i = 0; i < shnum; ++i) {
        read(fd, shdr, sizeof(Elf32_Shdr));
        str = shstrtab + shdr -> sh_name;
        if(strcmp(str, ".dynsym") == 0)
            memcpy(dynsym_shdr, shdr, sizeof(Elf32_Shdr));
        else if(strcmp(str, ".dynstr") == 0)
            memcpy(dynstr_shdr, shdr, sizeof(Elf32_Shdr));
        else if(strcmp(str, ".got") == 0)
            memcpy(got_shdr, shdr, sizeof(Elf32_Shdr));
        else if(strcmp(str, ".rel.plt") == 0)
            memcpy(relplt_shdr, shdr, sizeof(Elf32_Shdr));
    }

    //读取字符表
    char *dynstr = (char *) malloc(sizeof(char) * dynstr_shdr->sh_size);
    lseek(fd, dynstr_shdr->sh_offset, SEEK_SET);
    if(read(fd, dynstr, dynstr_shdr->sh_size) != dynstr_shdr->sh_size)
        return -1;

    //读取符号表
    Elf32_Sym *dynsymtab = (Elf32_Sym *) malloc(dynsym_shdr->sh_size);
    printf("dynsym_shdr->sh_size\t0x%x\n", dynsym_shdr->sh_size);
    lseek(fd, dynsym_shdr->sh_offset, SEEK_SET);
    if(read(fd, dynsymtab, dynsym_shdr->sh_size) != dynsym_shdr->sh_size)
        return -1;

    //读取重定位表
    Elf32_Rel *rel_ent = (Elf32_Rel *) malloc(sizeof(Elf32_Rel));
    lseek(fd, relplt_shdr->sh_offset, SEEK_SET);
    if(read(fd, rel_ent, sizeof(Elf32_Rel)) != sizeof(Elf32_Rel))
        return -1;

    uint32_t offset = 0;
    //获取指定符号在got表的偏移地址
    for (i = 0; i < relplt_shdr->sh_size / sizeof(Elf32_Rel); i++) {
        uint16_t ndx = ELF32_R_SYM(rel_ent->r_info);
        // LOGD("ndx = %d, str = %s", ndx, dynstr + dynsymtab[ndx].st_name);
        if (strcmp(dynstr + dynsymtab[ndx].st_name, symbol_name) == 0) {
            LOGD("符号%s在got表的偏移地址为: 0x%x", symbol_name, rel_ent->r_offset);
            offset = rel_ent->r_offset;
            break;
        }
        if(read(fd, rel_ent, sizeof(Elf32_Rel)) != sizeof(Elf32_Rel)) {
            LOGD("获取符号%s的重定位信息失败", symbol_name);
            return -1;
        }
    }

    //获取指定符号的地址
    if(offset == 0) {
        LOGD("获取符号%s在got表中的偏移地址失败，可能为静态链接，开始重新获取符号地址", symbol_name);
        for(i = 0; i < (dynsym_shdr->sh_size) / sizeof(Elf32_Sym); ++i) {
            if(strcmp(dynstr + dynsymtab[i].st_name, symbol_name) == 0) {
                LOGD("符号%s的地址位: 0x%x", symbol_name, dynsymtab[i].st_value);
                offset = dynsymtab[i].st_value;
                break;
            }
        }
    }

    if(offset == 0) {
        LOGD("符号%s地址获取失败", symbol_name);
        return -1;
    }

    uint16_t type = ehdr -> e_type;

    free(ehdr);
    free(shstr);
    free(shstrtab);
    free(shdr);
    free(relplt_shdr);
    free(dynsym_shdr);
    free(dynstr_shdr);
    free(dynstr);
    free(dynsymtab);
    free(rel_ent);

    if (type == ET_EXEC)
        return offset;
    else if (type == ET_DYN)
        return module_base + offset;
}

/**
 * 将需要hook的符号的got表地址替换为自己符号的地址
 */
uint32_t do_hook(const char *module_path, uint32_t hook_func, const char *symbol_name) {
    entry_addr = find_got_entry_address(module_path, symbol_name);
    if (entry_addr == 0)
        return -1;
   
    // old_write = write; 
    // old_ioctl = ioctl; 

    // old_open = open; 
    // old_read = read; 
    // old_sqlite3_open=sqlite3_open;
    //保存被hook符号的原始got表地址的值
    memcpy(&original_addr, (uint32_t *) entry_addr, sizeof(uint32_t));
    // memcpy(&old_sqlite3_open, (uint32_t *) entry_addr, sizeof(uint32_t));
    LOGD("自己函数的地址hook_func: 0x%x", hook_func);
    LOGD("待hook符号的got表地址为entry_addr: 0x%x", entry_addr);
    LOGD("待hook符号的got表地址的值为original_addr: 0x%x", original_addr);
    old_addr=original_addr;


    //页对齐
    uint32_t page_size = getpagesize();
    LOGD("1 ---- page_size = %x",page_size);
    uint32_t entry_page_start = PAGE_START(entry_addr, page_size);
    LOGD("2 ---- entry_page_start = %x", entry_page_start);
    //修改页权限
    // mprotect((uint32_t *) entry_page_start, page_size, PROT_READ | PROT_WRITE);
    if(mprotect((uint32_t *) entry_page_start, page_size, PROT_READ | PROT_WRITE)){
        LOGD("mprotect FAILED!!!");
        perror("cannot");
        exit(errno);
    }
    LOGD("3");
    //将需要hook的符号的got表地址替换为自己符号的地址
    memcpy((uint32_t *) entry_addr, &hook_func, sizeof(uint32_t));
    LOGD("4");
    //恢复页权限
    //mprotect((uint32_t *) entry_page_start, page_size, PROT_READ | PROT_EXEC);

    return 0;
}

void handle_hook() {
    uint32_t mfun_addr;
    char *module_path = NULL;
//  mfun_addr = find_got_entry_address("libhook.so", "hook") + 0x04; //加上0x04是要跳过函数自身的入栈操作
    mfun_addr = find_got_entry_address("libhook.so", "hook");

    // module_path = get_module_path(-1, "libbinder.so");
    // module_path = get_module_path(-1, "libjavacore.so");
        // module_path = get_module_path(-1, "libcutils.so");
    // module_path = get_module_path(-1, "libutils.so");
    module_path = get_module_path(-1, "libsqlite.so");
    // module_path = get_module_path(-1, "libandroid_runtime.so");

    // do_hook(module_path, mfun_addr, "write");
    // do_hook(module_path, mfun_addr, "read");
     do_hook(module_path, mfun_addr, "open");
        // do_hook(module_path, mfun_addr, "ioctl");
         // do_hook(module_path, mfun_addr, "sqlite3_open");
 // do_hook(module_path, mfun_addr, "sqlite3_exec");


}
