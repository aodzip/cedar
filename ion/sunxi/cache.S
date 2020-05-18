#if __LINUX_ARM_ARCH__ == 7
#include "cache-v7.S"
#else
#warning "[sunxi-cedar] No platform cache flush support"
#endif
