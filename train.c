// train.c

#include <stdio.h>
#include "train.h"

train_t trains[MAX_TRAINS];
int next_train_index = 0;

bool address_exists(uint8_t address){
	for(int i=0; i<MAX_TRAINS; i++){
		if(trains[i].address == address){
			return true;}}
	return false;}

// todo check for full
bool add_train(uint8_t address){
	if(!address_exists(address)){
		for(int i=0; i<MAX_TRAINS; i++){
			if(trains[i].address == 0){
				trains[i].address = address; break;}}}}

void init_trains(){
	for(int i=0; i<MAX_TRAINS; i++){
		trains[i].name=0;
		trains[i].address=0;
		trains[i].speed=0;
		trains[i].direction=1; // init forward
		trains[i].speed_op=0x3F;
		trains[i].f1=0x80;
		trains[i].f2=0;}
	add_train(99);} // init array with loco address 99
				
void show_all_trains(){
	for(int i=0; i<MAX_TRAINS; i++){
		printf("train address: %d speed: %d\n",trains[i].address,trains[i].speed);}}
		
train_t get_next_train(){
	if (next_train_index < MAX_TRAINS){
		do{
			if(trains[next_train_index].address != 0){
				return trains[next_train_index++];
			} else {
				next_train_index = 0;
			}
		} while (next_train_index < MAX_TRAINS);
	} else {
		next_train_index = 0;}}
    
bool set_speed(uint8_t address, uint8_t speed){
	for(int i=0; i<MAX_TRAINS; i++){
		if (trains[i].address == address) {
			trains[i].speed = speed; break;}}}
			

bool set_direction(uint8_t address, uint8_t direction){
	for(int i=0; i<MAX_TRAINS; i++){
		if (trains[i].address == address) {
			trains[i].direction = direction; break;}}}
			
bool update_function(uint8_t address, uint8_t bit_position, bool on){
	if (bit_position == 0) bit_position = 5;
	for(int i=0; i<MAX_TRAINS; i++){
		if(trains[i].address == address){
			if(on){trains[i].f1 |= 1 << (bit_position - 1);}
			else{trains[i].f1 &= ~(1 << (bit_position) - 1);}
			break;}}}
	
