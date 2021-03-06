/* From libc-5.3.12 */

#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

void * ___brk_addr = 0;

#define __NR__brk __NR_brk
_syscall1(void *, _brk, void *, ptr);

int
__init_brk ()
{
    if (___brk_addr == 0)
    {
		___brk_addr = _brk(0);
		if (___brk_addr == 0)
		{
		  __set_errno(ENOMEM);
		  return -1;
		}
    }
    return 0;
}
