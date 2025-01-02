// command.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "train.h"


char input_string[80];

char parameter[6][10];

void init_command(){
  uart_init(uart0, 115200);
  gpio_set_function(0, GPIO_FUNC_UART);
  gpio_set_function(1, GPIO_FUNC_UART);}

void parse_input(){
	char *buffer = input_string;
	int i = 0;
	char *token=strtok(buffer," ");
	while (token != NULL){
		strcpy(parameter[i++],token);
		token=strtok(NULL, " ");}}

// command examples:
// add loco 15 --
// throttle 20 loco 15 --
// direction forward loco 15 --
// direction reverse loco 15 --
// function 1 on loco 15 --
// function 2 off loco 15 --
void process_command(){
	
	parse_input();
	if(strcmp("add",parameter[0]) == 0){
		add_train(atoi(parameter[2]));}
	
	if(strcmp("throttle",parameter[0]) == 0){
		set_speed(atoi(parameter[3]), atoi(parameter[1]));}
		
	if(strcmp("direction",parameter[0]) == 0){
		if(strcmp("forward",parameter[1]) == 0){
			set_direction(atoi(parameter[3]),0x01);
		} else {set_direction(atoi(parameter[3]),0x00);}}
		
	if(strcmp("function",parameter[0]) == 0){	
		if(strcmp("on",parameter[2]) == 0) {
			update_function(atoi(parameter[4]),atoi(parameter[1]), true);}
		else{update_function(atoi(parameter[4]),atoi(parameter[1]), false);}}
}
	
void get_command(){
	int i=0;
	char c;
	uart_puts(uart0,"\nenter dcc command end with extra space\n");
	uart_puts(uart0,"i.e. add loco 15 <cr>, throttle 20 loco 15 <cr>\n");
	uart_puts(uart0,"direction forward loco 15<cr>, direction reverse loco 15 <cr>\n");
	uart_puts(uart0,"i.e. function 1 on loco 15 <cr>, function 1 off loco 15 <cr>\n");

    
    while ((c=uart_getc(uart0)) != '\n'){
		input_string[i++]=c;
	}
	input_string[i]='\0';}



