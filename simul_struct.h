#pragma once
#include <stdint.h>

typedef struct {
	uint32_t peripheralId;
	void* peripheral_p;
	enum {
		kIICcmd,
		kIICans,
		kIICisr,
		kTimercmd,
		kTimerans,
		kTimerisr,
		kSTimercmd,
		kSTimerans,
		kSTimerisr,
	} peripheralType;
	union {
		union IIC {
			struct {
				char none;
			} cmd;
			struct {
				char none;
			} ans;
			struct {
				char none;
			} isr;
		} iic;
		union Timer {
			struct {
				char none;
			} cmd;
			struct {
				char none;
			} ans;
			struct {
				char none;
			} isr;
		} timer;
		union STimer {
			struct {
				char none;
			} cmd;
			struct {
				char none;
			} ans;
			struct {
				char none;
			} isr;
		} stimer;
	} data;

} PeripheralMsg;

#ifdef __cplusplus
extern "C" {
#endif
	extern void push_to_periph(PeripheralMsg msg);
#ifdef __cplusplus
}
#endif