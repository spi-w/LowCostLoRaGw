/*
* Copyright (C) 2016 Nicolas Bertuol, University of Pau, France
*
* nicolas.bertuol@etud.univ-pau.fr
*/

#ifndef MH_IR_H
#define MH_IR_H

#include "Sensor.h"

class MH_IR : public Sensor {
  public:
    MH_IR(char* nomenclature, bool is_analog, bool is_connected, bool is_low_power, uint8_t pin_read, uint8_t pin_power);
    double get_value();
    void update_data();
    
};

#endif
