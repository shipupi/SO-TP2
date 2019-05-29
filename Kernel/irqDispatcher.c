#include "drivers/time.h"
#include "drivers/naiveKeyboard.h"
#include "irqDispatcher.h"
#include "drivers/vesaDriver.h"

static void (*irqVector[IRQ_AMOUNT])(void) = {timer_handler, keyboard_handler};

void irqDispatcher(int irq) {
	(*irqVector[irq])();;
}