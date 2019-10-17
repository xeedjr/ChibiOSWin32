#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	void getInterrupt();
 void initObjectModule(void* moduleAddr, char* moduleName);
 void startObjectModule(void* moduleAddr, char* moduleName);

 uint8_t Rest_pal_lld_readport(void* port);
 uint8_t Rest_pal_lld_readlatch(void* port);
 void Rest_pal_lld_writeport(void* port, uint32_t bits);
 void Rest_pal_lld_setpad(void* port, uint8_t pad);
 void Rest_pal_lld_clearpad(void* port, uint8_t pad);

#ifdef __cplusplus
}
#endif