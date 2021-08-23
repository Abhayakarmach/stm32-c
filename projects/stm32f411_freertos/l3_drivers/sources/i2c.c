#include <stddef.h>

#include "i2c.h"

#include "stm32f411xe.h"
#include "clock.h"


static void enable_clock_for_pins(void ){
  
    uint32_t enable_i2c_clock = (1 << 21);
    uint32_t enable_gpio_clock = (1 << 1);  
    RCC-> APB1ENR = enable_i2c_clock;
    RCC-> APB1ENR = enable_gpio_clock;
    
}

static void configure_i2c_pins(void ){
  
    uint32_t alter_function |= (2 << 16) | (2 << 18);
    uint32_t select_open_drain  |= (3 << 8);  
    uint32_t select_speed  |= (3 << 16 ) | (3 << 18);
    uint32_t select_pull_up  |= (3 << 16 ) | (3 << 18);
    uint32_t i2c_function  |= |=(4 << 0) | (4 << 1)

    GPIOB-> MODER = alter_function;
    GPIOB-> MODER = select_open_drain;
    GPIOB-> OSPEEDR = select_speed;
    GPIOB-> PUPDR = select_pull_up;
    GPIOB-> AFR[1] = i2c_function;
}

static void configure_i2c_clock(void ){
    uint32_t set_pclk1 |= (42 << 0);
    uint32_t set_ccr |= (240 << 0);

    I2C1 -> CCR = set_ccr;
    I2C1 -> CR2 = set_pclk1;

}

static void generate_and_check_start_bit(){
    uint32_t generate_start_bit = (1 << 8);
    I2C1 -> CR1 |= generate_start_bit;
    while (!(I2C1 -> SR1 & (1 << 0))) {
;       
    } 
}
static void generate_and_check_stop_bit(){
while (!(I2C1->SR1) & (1 << 2)){
    ;
}
I2C1 -> CR1 |= (1 << 9);
}

void i2c__init(i2c_e i2c_number, uint32_t peripheral_clock){
unint32_t config_rise_time = (43 << 0);
uint32_t enable_i2c_peripherpal =(1 << 0 );
enable_clock_for_pins();
configure_i2c_pins();
configure_i2c_clock();
enable_i2c_peripherpal();
I2C1 -> TRISE = config_rise_time; 
I2C1 -> CR1 = enable_i2c_peripheral;
}

void i2c_write_single(i2c_e i2c_number, uint8_t slave_address, uint8_t data){

generate_check_start_bit();

I2C1 -> DR = slave_address;
while (!(I2C1 -> SR1 & (1 << 1))) {;} // wait for ADDR bit to set
uint8_t dummy_read= (II2C1 -> SR1 | I2C1 -> SR2);


while (!(I2C1->SR1) & (1 << 7)){
    ;
}
I2C1 -> DR= data;


generate_and_check_stop_bit();
}











void i2c_write_multiple(i2c_e i2c_number, uint8_t slave_address, uint8_t *value, uint32_t number_of_bytest_to_transfer){
generate_check_start_bit();

I2C1 -> DR = slave_address;
while (!(I2C1 -> SR1 & (1 << 1))) {;} // wait for ADDR bit to set
uint8_t dummy_read= (II2C1 -> SR1 | I2C1 -> SR2);


for (int i =0; i < number_of_bytest_to_transfer; i ++){
while (!(I2C1->SR1) & (1 << 7)){
    ;
}
I2C1 -> DR= *value++ ;
} 

generate_and_check_stop_bit();

}
