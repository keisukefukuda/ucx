/**
 * Copyright (C) Mellanox Technologies Ltd. 2001-2015.  ALL RIGHTS RESERVED.
 *
 * See file LICENSE for terms.
 */

#ifndef UCM_MMAP_H_
#define UCM_MMAP_H_

#include <ucm/api/ucm.h>
#include <ucs/sys/checker.h>

ucs_status_t ucm_mmap_install(int events);

void *ucm_override_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int ucm_override_munmap(void *addr, size_t length);
void *ucm_override_mremap(void *old_address, size_t old_size, size_t new_size, int flags);
void *ucm_override_shmat(int shmid, const void *shmaddr, int shmflg);
int ucm_override_shmdt(const void *shmaddr);
void *ucm_override_sbrk(intptr_t increment);
void *ucm_sbrk_select(intptr_t increment);
int ucm_override_brk(void *addr);
void *ucm_brk_syscall(void *addr);
int ucm_override_madvise(void *addr, size_t length, int advice);
void ucm_fire_mmap_events(int events);

static UCS_F_ALWAYS_INLINE ucm_mmap_hook_mode_t ucm_mmap_hook_mode(void)
{
    return (RUNNING_ON_VALGRIND && (ucm_global_opts.mmap_hook_mode == UCM_MMAP_HOOK_BISTRO)) ?
           UCM_MMAP_HOOK_RELOC : ucm_global_opts.mmap_hook_mode;
}

#endif
