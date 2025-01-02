/*
 main file
 
 my attempt of making dcc station
 debug with pulseview setting 1 M samples, 100 khz

 starting pulseview from linux
 sudo LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libgmodule-2.0.so.0 ./pulseview.AppImage

 loading .elf file to pico using debug pins
 sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000"
     -c "program filename.elf verify reset exit"
     
command examples:
  add loco 15 --
  throttle 20 loco 15 --
  direction forward loco 15 --
  direction reverse loco 15 --
  function 1 on loco 15 --
  function 2 off loco 15 --
  
files:
  command.c command.h  -  serial input command and parsing command
  dcc.c dcc.h dcc.pio  -  assembling packet and sending to pio to generate dcc signal
  train.c train.h      -  maintain train listing as well as setting individual trains speed, direction, and function
*/ 

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "command.h"
#include "train.h"
#include "dcc.h"

repeating_timer_t timer;
train_t train;

bool timer_callback(__unused repeating_timer_t *rt){
  train = get_next_train();
  send_speed(train);
  if(train.f1 != 0x80) send_function1(train);
  send_idle();
  return true;}

int main(){
    stdio_init_all();
    init_command();
    init_trains();
    init_dcc();
    add_repeating_timer_ms(15,  // 15 millis interval
	                       timer_callback,
	                       NULL,
	                       &timer);
for(;;){
get_command();
process_command();
sleep_ms(200);}return 0;}

