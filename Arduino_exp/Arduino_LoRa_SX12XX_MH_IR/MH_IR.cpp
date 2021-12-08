/*
* Copyright (C) 2016 Nicolas Bertuol, University of Pau, France
*
* nicolas.bertuol@etud.univ-pau.fr
*
* modified by Congduc Pham, University of Pau, France
*/

#include "MH_IR.h"

MH_IR::MH_IR(char* nomenclature, bool is_analog, bool is_connected, bool is_low_power, uint8_t pin_read, uint8_t pin_power):Sensor(nomenclature,is_analog, is_connected, is_low_power, pin_read, pin_power){
  if (get_is_connected()){
    
    pinMode(get_pin_power(),OUTPUT);
    
	if(get_is_low_power())
       digitalWrite(get_pin_power(),LOW);
    else
       digitalWrite(get_pin_power(),HIGH);
   
  set_warmup_time(4000);
  }
}

void MH_IR::update_data()
{
  if (get_is_connected()) {

    set_data(digitalRead(get_pin_read()));
  }
  else {
  	if (has_fake_data())	
    	set_data(-1);
  }

}

double MH_IR::get_value()
{
  Serial.println("mvt");
  
  // if we use a digital pin to power the sensor...
  if (get_is_low_power())
    digitalWrite(get_pin_power(),HIGH);

  update_data();
  Serial.println(get_data());

  if (get_is_low_power())    
    digitalWrite(get_pin_power(),LOW);  
    
  return get_data();
}
