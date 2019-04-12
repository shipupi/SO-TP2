#include "time.h"
#include "naiveKeyboard.h"
#include "irqDispatcher.h"

static void (*irqVector[IRQ_AMOUNT])(void) = {timer_handler, keyboard_handler};

void irqDispatcher(int irq) {
	(*irqVector[irq])();   
}
