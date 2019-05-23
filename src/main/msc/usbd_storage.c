#ifdef USE_HAL_DRIVER
#include "usbd_msc.h"
#else
#include "usbd_msc_mem.h"
#include "usbd_msc_core.h"
#endif

#include "usbd_storage.h"

#ifdef USE_HAL_DRIVER
USBD_StorageTypeDef *USBD_STORAGE_fops;
#else
USBD_STORAGE_cb_TypeDef *USBD_STORAGE_fops;
#endif
