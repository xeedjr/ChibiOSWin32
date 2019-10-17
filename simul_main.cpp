#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <ppl.h>
#include <concurrent_queue.h>
#include "simul_struct.h"
#include "Queue.h"


#include "hal.h"

#include "Rest.h"

using namespace std;
using namespace concurrency;
extern void connect_();

Queue<PeripheralMsg> msg_to_periph;
Queue<PeripheralMsg> msg_from_periph;
UINT_PTR STimer;

#ifdef __cplusplus
extern "C" {
#endif
extern int target_main(void);
extern void SIMUL_ISR_TWI_vect();
extern void SIMUL_ISR_SIMUL_TIMER_VECT();
#ifdef __cplusplus
}
#endif

void push_to_periph(PeripheralMsg msg) {
	msg_to_periph.push(msg);
}

void WINAPI callback(
	HWND Arg1,
	UINT Arg2,
	UINT_PTR Arg3,
	DWORD Arg4)
{
	PeripheralMsg msg_ans;
	msg_ans.peripheralId = 0;
	msg_ans.peripheralType = PeripheralMsg::kSTimercmd;
	msg_from_periph.push(msg_ans);
}

static DWORD WINAPI Simulate_Peripheral(LPVOID  data) {
	PeripheralMsg msg;

	while (1) {

		msg_to_periph.pop(msg);

		switch (msg.peripheralType) {
		case PeripheralMsg::kSTimercmd:
		{
			UINT_PTR STimer = SetTimer(NULL, 0, 100, callback);
			break;
		}

		case PeripheralMsg::kIICcmd:
		{
			I2CDriver* i2cp = (I2CDriver*)msg.peripheral_p;
			
			if (i2cp->txbuf != NULL) {
				// Write data
			}

			if (i2cp->rxbuf != NULL) {
				// read data
			}

			// completed 
			PeripheralMsg msg_ans;
			msg_ans.peripheralId = msg.peripheralId;
			msg_ans.peripheralType = PeripheralMsg::kIICisr;
			msg_from_periph.push(msg_ans);
			break;
		}
		default: 
			break;
		}
	}
	return 0;
}


static DWORD WINAPI ISR_thread(LPVOID  data) {
	PeripheralMsg msg;
	while (1) {
		getInterrupt();
		//msg_from_periph.pop(msg);
		msg.peripheralType = PeripheralMsg::kIICisr;
		switch (msg.peripheralType) {
		case PeripheralMsg::kIICisr:
			SIMUL_ISR_TWI_vect();
			break;
		case PeripheralMsg::kSTimercmd:
			SIMUL_ISR_SIMUL_TIMER_VECT();
			break;
		}
	}
	return 0;
}

static DWORD WINAPI main_thread(LPVOID  data) {
	return target_main();
}

int main() {
	connect_();

	HANDLE thread_ISR = CreateThread(NULL, 0, ISR_thread, NULL, CREATE_SUSPENDED, NULL);
	if (thread_ISR == NULL) {
		// Optionally do stuff, such as wait on the thread.
		return 0;
	}
	HANDLE thread_main = CreateThread(NULL, 0, main_thread, NULL, CREATE_SUSPENDED, NULL);
	if (thread_main == NULL) {
		// Optionally do stuff, such as wait on the thread.
		return 0;
	}
	HANDLE thread_peri = CreateThread(NULL, 0, Simulate_Peripheral, NULL, 0, NULL);
	if (thread_peri == NULL) {
		// Optionally do stuff, such as wait on the thread.
		return 0;
	}
	int core = 2;
	DWORD_PTR mask = (1 << core) - 1;
	SetThreadAffinityMask(thread_ISR, mask);
    SetThreadAffinityMask(thread_main, mask);
	
	SetThreadPriority(thread_ISR, THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(thread_main, 0);

	ResumeThread(thread_ISR);
	ResumeThread(thread_main);

	while (1) {
		Sleep(1);
	}
	return 1;
}