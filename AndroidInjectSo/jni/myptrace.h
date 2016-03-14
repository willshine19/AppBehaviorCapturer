void error(const char* fun);

void ptrace_attach(pid_t pid);

void ptrace_continue(pid_t pid);

void ptrace_detach(pid_t pid);

void ptrace_getregs(pid_t pid, struct pt_regs* regs);

void ptrace_setregs(pid_t pid, struct pt_regs* regs);

void ptrace_readdata( pid_t pid,  void *src, void *buf, size_t size );

void ptrace_writedata(pid_t pid, void *dest, void *data, size_t size);

void ptrace_writestring(pid_t pid, void *dest, const char *str);

long ptrace_pushdata(pid_t pid, void *addr, size_t size);

int ptrace_call(pid_t pid, uint32_t addr, uint32_t *params, int num_params, struct pt_regs *regs);
