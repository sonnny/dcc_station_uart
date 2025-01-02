///////////////////////
// filename: dcc.c
//////////////////////
#include "dcc.h"
#include "dcc.pio.h"

void init_dcc(){
	uint offset=pio_add_program(pio0, &dcc_program);
	dcc_program_init(pio0,0,offset,DCC_PIN);
	pio_sm_set_enabled(pio0,0,true);}	

bool send_idle(){ 
	pio_sm_put_blocking(pio0,0,0xFFFEFF00); 
	pio_sm_put_blocking(pio0,0,0x3FF00000);}

bool send_speed(train_t train){
	uint32_t packet1, packet2;
	uint8_t checksum, speed, b1, b2, b3, temp;
	
	if(train.address != DUMMY_LOCO){ // skip dummy loco in the array
	
	    temp = train.speed_op >> 1;
	    packet1 = (0xFF << 24)|(0xFE << 16)|(train.address << 8)|(temp << 0);
	    pio_sm_put_blocking(pio0,0,packet1);
	
	    speed = train.speed;
	    if(train.direction == 0x01){speed |= 1 << 7;}
        else {speed &= ~(1 << 7);}
	
	    checksum = train.address ^ train.speed ^ train.speed_op;
	
	    // todo explain below code
	    b1 = speed >> 2;
	    b1 |= 0x80;
	
	    b2 = checksum >> 3;
	    temp = speed << 6;
	    b2 |= temp;
	
	    b3 = checksum << 5;
	    b3 = 0x10;
	
	    packet2 = (b1 << 24)|(b2 << 16)|(b3 << 8)|(0x00 << 00);
	    pio_sm_put_blocking(pio0,0,packet2);}
}	    

	
bool send_function1(train_t train){
	uint32_t packet1, packet2;
	uint8_t checksum, temp_f1, b1, b2, temp;
	
	packet2 = 0x00000000;
	
	if(train.address != DUMMY_LOCO){
		
		temp = train.f1 >> 1;
		packet1 = (0xFF << 24)|(0xFE << 16)|(train.address << 8)|(temp << 0);
		pio_sm_put_blocking(pio0,0,packet1);
		
		// todo explain below code
		checksum = train.address ^ train.f1;
		
		temp_f1 = train.f1 << 7;
		
	    b1 = checksum >> 2;
	    if (train.f1 == 0x81) b1 |= 0x01;
		
		b2 = checksum << 6;
		b2 = b2 | (1 <<5); // end bit
		
		packet2 = (temp_f1 << 24)|(b1 << 16);
		pio_sm_put_blocking(pio0,0,packet2);
	}

}
