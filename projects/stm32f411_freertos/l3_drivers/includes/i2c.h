#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum {
i2c__1 =0,
i2c__2 =1,
i2c__3 =2,
} i2c_e

/**
 * Initialize a i2c peripheral 
 * @param i2c_id is the i2c peripheral to initialize 
 * @param peripheral_clock is the clock frequency in Hz fed to the i2c
 * @note  high speed is selected as a default
**/
void i2c__init(i2c_e i2c_number, uint32_t peripheral_clock);


// have it in the .c file void i2c_start(void);


/** 
 * Detect the ACK for the given slave_address 
 **/
bool i2c__detect(i2c_e i2c_number, uint8_t slave_address);


/**
 * Write a single data and stop 
 * @param slave_address is the slave address sent to the DR register
 * @param value is the data to write 
 **/
void i2c_write_single(i2c_e i2c_number, uint8_t slave_address, uint8_t value);


/**
 * Write a multiple data and stop 
 * @param slave_address is the slave address sent to the DR register
 * @param value is the data to write 
 * @param number_of_bytest_to_transfer is the number of bytest to write  
 **/
void i2c_write_multiple(i2c_e i2c_number, uint8_t slave_address, uint8_t *value, uint32_t number_of_bytest_to_transfer);
