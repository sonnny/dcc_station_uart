/////////////////////////////////
// filename: dcc.h
/////////////////////////////////
#include <stdint.h>
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "train.h"

#ifndef _DCC_H
#define _DCC_H

#define DCC_PIN       14
#define DUMMY_LOCO    99

void init_dcc();
bool send_speed(train_t train);
bool send_function1(train_t train);
bool send_idle();

#endif
