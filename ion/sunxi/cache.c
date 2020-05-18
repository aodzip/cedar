#if __ARM_ARCH__ == 7
#include "cache-v7.S"
#else
int flush_clean_user_range(long start, long end)
{
    return -1;
}
void flush_dcache_all(void)
{
}
#endif
