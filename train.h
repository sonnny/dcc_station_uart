// train.h
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef _TRAIN_H
#define _TRAIN_H

#define MAX_TRAINS 10

typedef struct {
  uint8_t name;
  uint8_t address;
  uint8_t speed;
  uint8_t direction;
  uint8_t speed_op;
  uint8_t f1;
  uint8_t f2;} train_t;

void init_trains();  
bool add_train(uint8_t address);
bool set_speed(uint8_t address, uint8_t speed);
bool set_direction(uint8_t address, uint8_t direction);
bool update_function(uint8_t address, uint8_t bit_position, bool on);
train_t get_next_train();

#endif
