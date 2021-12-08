# 1 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
/*
 *  temperature sensor on analog A0 to test the LoRa gateway
 *  extended version with AES and custom Carrier Sense features
 *  
 *  Copyright (C) 2016-2019 Congduc Pham, University of Pau, France
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with the program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************
 * last update: November 12th, 2020 by C. Pham
 * 
 * NEW: LoRa communicain library moved from Libelium's lib to StuartProject's lib
 * https://github.com/StuartsProjects/SX12XX-LoRa
 * to support SX126X, SX127X and SX128X chips (SX128X is LoRa in 2.4GHz band)
 *  
 * This version uses the same structure than the Arduino_LoRa_Demo_Sensor where
 * the sensor-related code is in a separate file
 */

# 32 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 2
//this is the standard behaviour of library, use SPI Transaction switching

//indicate in this file the radio module: SX126X, SX127X or SX128X
# 36 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 2







# 44 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 2
# 45 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 2







# 53 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 2

/********************************************************************
 _____              __ _                       _   _             
/  __ \            / _(_)                     | | (_)            
| /  \/ ___  _ __ | |_ _  __ _ _   _ _ __ __ _| |_ _  ___  _ __  
| |    / _ \| '_ \|  _| |/ _` | | | | '__/ _` | __| |/ _ \| '_ | \__/\ (_) | | | | | | | (_| | |_| | | | (_| | |_| | (_) | | | |
 |
 \____/\___/|_| |_|_| |_|\__, |\__,_|_|  \__,_|\__|_|\___/|_| |_|
                          __/ |                                  
                         |___/                                   
********************************************************************/

///////////////////////////////////////////////////////////////////
// COMMENT OR UNCOMMENT TO CHANGE FEATURES. 
// ONLY IF YOU KNOW WHAT YOU ARE DOING!!! OTHERWISE LEAVE AS IT IS
// 
// FOR UPLINK WITH ONLY AES ENCRYTION: uncomment WITH_AES
// FOR UPLINK TO LORAWAN CLOUD ENCAPSULATED LORAWAN FORMAT: uncomment WITH_AES & EXTDEVADDR 
// FOR UPLINK TO LORAWAN CLOUD NATIVE LORAWAN FORMAT: uncomment LORAWAN in RadioSettings.h
// FOR UPLINK TO LORAWAN CLOUD AND DOWNLINK WITH NATIVE LORAWAN FORMAT: uncomment LORAWAN in RadioSettings.h & WITH_RCVW
// 
// more info: https://github.com/CongducPham/LowCostLoRaGw/blob/master/gw_full_latest/README-aes_lorawan.md
//
// DEFAULT CONFIGURATION: SF12BW125, no encryption, no LoRaWAN, no downlink
//
//#define WITH_EEPROM
////////////////////////////
//add 4-byte AppKey filtering - only for non-LoRaWAN mode

////////////////////////////
//request an ack from gateway - only for non-LoRaWAN mode
//#define WITH_ACK
////////////////////////////
//if you are low on program memory, comment STRING_LIB to save about 2K
//#define STRING_LIB
////////////////////////////



////////////////////////////
//Use LoRaWAN AES-like encryption

////////////////////////////
//Use our Lightweight Stream Cipher (LSC) algorithm
//#define WITH_LSC
////////////////////////////
//If you want to upload to LoRaWAN cloud without pure LoRaWAN format you have to provide a 4 bytes DevAddr and uncomment #define EXTDEVADDR
//#define EXTDEVADDR
////////////////////////////
//this will enable a receive window after every transmission, uncomment it to also have LoRaWAN downlink

////////////////////////////
//normal behavior is to invert IQ for RX, the normal behavior at gateway is also to invert its IQ setting, only valid with WITH_RCVW

////////////////////////////
//uncomment to use a customized frequency. TTN plan includes 868.1/868.3/868.5/867.1/867.3/867.5/867.7/867.9 for LoRa
//#define MY_FREQUENCY 868100000

////////////////////////////
//when sending to a LoRaWAN gateway (e.g. running util_pkt_logger) but with no native LoRaWAN format, just to set the correct sync word
//#define PUBLIC_SYNCWORD
////////////////////////////

///////////////////////////////////////////////////////////////////
// ADD HERE OTHER PLATFORMS THAT DO NOT SUPPORT EEPROM




///////////////////////////////////////////////////////////////////
// ADD HERE OTHER PLATFORMS THAT DO NOT SUPPORT LOW POWER LIB



///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// CHANGE HERE THE NODE ADDRESS 
uint8_t node_addr=6;
//////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// CHANGE HERE THE TIME IN MINUTES BETWEEN 2 READING & TRANSMISSION
unsigned int idlePeriodInMin = 0;
unsigned int idlePeriodInSec = 20;
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
// CHANGE HERE THE APPKEY, BUT IF GW CHECKS FOR APPKEY, MUST BE
// IN THE APPKEY LIST MAINTAINED BY GW.
uint8_t my_appKey[4]={5, 6, 7, 8};
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
// ENCRYPTION CONFIGURATION AND KEYS FOR LORAWAN






# 157 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 2


///////////////////////////////////////////////////////////////////
// LORAWAN OR EXTENDED DEVICE ADDRESS FOR LORAWAN CLOUD
# 173 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
///////////////////////////////////////////////////////////////////
// DO NOT CHANGE HERE
unsigned char DevAddr[4] = { 0x00, 0x00, 0x00, node_addr };
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
// ENCRYPTION CONFIGURATION AND KEYS FOR LSC ENCRYPTION METHOD




///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// IF YOU SEND A LONG STRING, INCREASE THE SIZE OF MESSAGE
uint8_t message[80];
///////////////////////////////////////////////////////////////////

//create a library class instance called LT
//to handle LoRa radio communications





SX127XLT LT;






//keep track of the number of successful transmissions
uint32_t TXPacketCount=0;

///////////////////////////////////////////////////////////////////
// COMMENT THIS LINE IF YOU WANT TO DYNAMICALLY SET THE NODE'S ADDR 
// OR SOME OTHER PARAMETERS BY REMOTE RADIO COMMANDS (WITH_RCVW)
// LEAVE THIS LINE UNCOMMENTED IF YOU WANT TO USE THE DEFAULT VALUE
// AND CONFIGURE YOUR DEVICE BY CHANGING MANUALLY THESE VALUES IN 
// THE SKETCH.
//
// ONCE YOU HAVE FLASHED A BOARD WITHOUT FORCE_DEFAULT_VALUE, YOU 
// WILL BE ABLE TO DYNAMICALLY CONFIGURE IT AND SAVE THIS CONFIGU-
// RATION INTO EEPROM. ON RESET, THE BOARD WILL USE THE SAVED CON-
// FIGURATION.

// IF YOU WANT TO REINITIALIZE A BOARD, YOU HAVE TO FIRST FLASH IT 
// WITH FORCE_DEFAULT_VALUE, WAIT FOR ABOUT 10s SO THAT IT CAN BOOT
// AND FLASH IT AGAIN WITHOUT FORCE_DEFAULT_VALUE. THE BOARD WILL 
// THEN USE THE DEFAULT CONFIGURATION UNTIL NEXT CONFIGURATION.


///////////////////////////////////////////////////////////////////

/*****************************
 _____           _      
/  __ \         | |     
| /  \/ ___   __| | ___ 
| |    / _ \ / _` |/ _ | \__/\ (_) | (_| |  __/
/
 \____/\___/ \__,_|\___|
*****************************/

// we wrapped Serial.println to support the Arduino Zero or M0
# 272 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
// this is for the Teensy36, Teensy35, Teensy31/32 & TeensyLC
// need v6 of Snooze library
# 284 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
// you need the LowPower library from RocketScream
// https://github.com/rocketscream/Low-Power
# 287 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 2
# 297 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
unsigned long nextTransmissionTime=0L;
# 316 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
// will wait for 1s before opening the rcv window


//this function is provided to parse the downlink command which is assumed to be in the format /@A6#
//
long getCmdValue(int &i, char* cmdstr, char* strBuff=
# 321 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3 4
                                                    __null
# 321 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
                                                        ) {

     char seqStr[10]="******";

    int j=0;
    // character '#' will indicate end of cmd value
    while ((char)cmdstr[i]!='#' && ( i < strlen(cmdstr) && j<strlen(seqStr))) {
            seqStr[j]=(char)cmdstr[i];
            i++;
            j++;
    }

    // put the null character at the end
    seqStr[j]='\0';

    if (strBuff) {
            strcpy(strBuff, seqStr);
    }
    else
            return (atol(seqStr));
}




char *ftoa(char *a, double f, int precision)
{
 long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};

 char *ret = a;
 long heiltal = (long)f;
 itoa(heiltal, a, 10);
 while (*a != '\0') a++;
 *a++ = '.';
 long desimal = (((long)((f - heiltal) * p[precision]))>0?((long)((f - heiltal) * p[precision])):-((long)((f - heiltal) * p[precision])));
 if (desimal < p[precision-1]) {
  *a++ = '0';
 }
 itoa(desimal, a, 10);
 return ret;
}




void lowPower(unsigned long time_ms) {

  unsigned long waiting_t=time_ms;

  Serial.flush();
  delay(5);
# 396 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
  while (waiting_t>0) {


      // ATmega2560, ATmega328P, ATmega168, ATmega32U4
      // each wake-up introduces an overhead of about 158ms
      if (waiting_t > 8158) {
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
        waiting_t = waiting_t - 8158;

              Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 405 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 405 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             "8"
# 405 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             ); &__c[0];}))
# 405 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             )));

      }
      else if (waiting_t > 4158) {
        LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
        waiting_t = waiting_t - 4158;

              Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 412 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 412 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             "4"
# 412 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             ); &__c[0];}))
# 412 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             )));

      }
      else if (waiting_t > 2158) {
        LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
        waiting_t = waiting_t - 2158;

              Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 419 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 419 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             "2"
# 419 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             ); &__c[0];}))
# 419 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             )));

      }
      else if (waiting_t > 1158) {
        LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
        waiting_t = waiting_t - 1158;

              Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 426 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 426 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             "1"
# 426 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             ); &__c[0];}))
# 426 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             )));

      }
    else {
        delay(waiting_t);

              Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 432 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 432 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             "D["
# 432 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             ); &__c[0];}))
# 432 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             )));
              Serial.print(waiting_t);
              Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 434 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 434 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             "]\n"
# 434 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             ); &__c[0];}))
# 434 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             )));

        waiting_t = 0;
      }


      Serial.flush();
      delay(1);
# 464 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
   }

}


/*****************************
 _____      _               
/  ___|    | |              
\ `--.  ___| |_ _   _ _ __  
 `--. \/ _ \ __| | | | '_ /\__/ /  __/ |_| |_| | |_) |
 |
\____/ \___|\__|\__,_| .__/ 
                     | |    
                     |_|    
******************************/

void setup()
{
  // initialization of the temperature sensor
  sensor_Init();
# 493 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
  delay(3000);
  // Open serial communications and wait for port to open:



  Serial.begin(38400);


  // Print a start message
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 502 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 502 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 "LoRa temperature sensor, extended version\n"
# 502 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 ); &__c[0];}))
# 502 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 )));





  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 508 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 508 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 "Arduino Nano detected\n"
# 508 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 ); &__c[0];}))
# 508 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 )));
# 541 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
// See http://www.nongnu.org/avr-libc/user-manual/using_tools.html
// for the list of define from the AVR compiler


  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 545 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 545 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 "ATmega328P detected\n"
# 545 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 ); &__c[0];}))
# 545 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 )));
# 560 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
  //start SPI bus communication
  SPI.begin();

  //setup hardware pins used by device, then check if device is found





  if (LT.begin(10 /*select pin on LoRa device*/, 4 /*reset pin on LoRa device*/, -1 /*DIO0 pin on LoRa device, used for RX and TX done */, -1 /*DIO1 pin on LoRa device, normally not used so set to -1 */, -1 /*DIO2 pin on LoRa device, normally not used so set to -1*/, 0x11 /*we need to define the device we are using*/))





  {
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 576 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 576 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
   "LoRa Device found\n"
# 576 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
   ); &__c[0];}))
# 576 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
   )));
    delay(1000);
  }
  else
  {
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 581 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 581 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
   "No device responding\n"
# 581 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
   ); &__c[0];}))
# 581 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
   )));
    while (1){ }
  }

/*******************************************************************************************************
  Based from SX12XX example - Stuart Robinson 
*******************************************************************************************************/

  //The function call list below shows the complete setup for the LoRa device using the
  // information defined in the Settings.h file.
  //The 'Setup LoRa device' list below can be replaced with a single function call;
  //LT.setupLoRa(Frequency, Offset, SpreadingFactor, Bandwidth, CodeRate, Optimisation);

  //***************************************************************************************************
  //Setup LoRa device
  //***************************************************************************************************
  //got to standby mode to configure device
  LT.setMode(0x01);
# 610 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
  //set for LoRa transmissions                              
  LT.setPacketType(0x80 /*regopmode setting for LoRa */);
  //set the operating frequency                 

  LT.setRfFrequency(433175000, Offset);



//run calibration after setting frequency

  LT.calibrateImage(0);

  //set LoRa modem parameters

  LT.setModulationParams(SpreadingFactor, Bandwidth, CodeRate, Optimisation);




  //where in the SX buffer packets start, TX and RX
  LT.setBufferBaseAddress(0x00, 0x00);
  //set packet parameters

  LT.setPacketParams(8, 0x00, 255, 0x01 /*Packet CRC is activated*/, 0x00);




  //syncword, LORA_MAC_PRIVATE_SYNCWORD = 0x12, or LORA_MAC_PUBLIC_SYNCWORD = 0x34 




  LT.setSyncWord(0x12);

  //set for highest sensitivity at expense of slightly higher LNA current
  LT.setHighSensitivity(); //set for maximum gain






  //set for IRQ on RX done
  LT.setDioIrqParams(0xFFFF, 0x08 /*active on DIO0 */, 0, 0);
  LT.setPA_BOOST(PA_BOOST);





  if (IQ_Setting==0x40) {
    LT.invertIQ(true);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 663 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 663 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
   "Invert I/Q on RX\n"
# 663 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
   ); &__c[0];}))
# 663 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
   )));
  }
  else {
    LT.invertIQ(false);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 667 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 667 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
   "Normal I/Q\n"
# 667 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
   ); &__c[0];}))
# 667 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
   )));
  }

  //***************************************************************************************************

  Serial.println("");
  //reads and prints the configured LoRa settings, useful check
  LT.printModemSettings();
  Serial.println("");
  //reads and prints the configured operating settings, useful check
  LT.printOperatingSettings();
  Serial.println("");
  Serial.println("");

  //print contents of device registers, normally 0x00 to 0x4F
  LT.printRegisters(0x00, 0x4F);






/*******************************************************************************************************
  End from SX12XX example - Stuart Robinson 
*******************************************************************************************************/
# 760 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 760 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 760 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 "Setting Power: "
# 760 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 ); &__c[0];}))
# 760 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 )));
  Serial.print(14);
  Serial.println("");

  LT.setDevAddr(node_addr);
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 765 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 765 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 "node addr: "
# 765 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 ); &__c[0];}))
# 765 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 )));
  Serial.print(node_addr);
  Serial.println("");
# 779 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 779 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 779 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 "SX127X"
# 779 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 ); &__c[0];}))
# 779 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 )));





  // Print a success message
  Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 786 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 786 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 " successfully configured\n"
# 786 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
 ); &__c[0];}))
# 786 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
 )));

  //printf_begin();
  delay(500);
}


/*****************************
 _                       
| |                      
| |     ___   ___  _ __  
| |    / _ \ / _ \| '_ | |___| (_) | (_) | |_) |
 |
\_____/\___/ \___/| .__/ 
                  | |    
                  |_|    
*****************************/

void loop(void)
{
  long startSend;
  long endSend;
  uint8_t app_key_offset=0;
  int e;
  float temp;





      //time for next wake up
      nextTransmissionTime=millis()+((idlePeriodInSec==0)?(unsigned long)idlePeriodInMin*60*1000:(unsigned long)idlePeriodInSec*1000);
      Serial.println(nextTransmissionTime);
      Serial.println((idlePeriodInSec==0)?(unsigned long)idlePeriodInMin*60*1000:(unsigned long)idlePeriodInSec*1000);



      digitalWrite(9,0x1);
      // security?
      delay(200);


      temp = 0.0;

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // change here how the temperature should be computed depending on your sensor type
      //  

      for (int i=0; i<5; i++) {
          temp += sensor_getValue();
          delay(100);
      }

      //
      // 
      // /////////////////////////////////////////////////////////////////////////////////////////////////////////// 


      digitalWrite(9,0x0);


      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 847 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 847 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "Mean temp is "
# 847 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 847 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));
      temp = temp/5;
      Serial.print(temp);
      Serial.println("");

      // for testing, uncomment if you just want to test, without a real temp sensor plugged
      temp = 22.5;


      app_key_offset = sizeof(my_appKey);
      // set the app key in the payload
      memcpy(message,my_appKey,app_key_offset);


      uint8_t r_size;

      // the recommended format if now \!TC/22.5







      char float_str[10];
      ftoa(float_str,temp,2);
      r_size=sprintf((char*)message+app_key_offset,"\\!%s/%s",nomenclature_str,float_str);


      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 876 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 876 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "Sending "
# 876 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 876 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));
      Serial.print((char*)(message+app_key_offset));
      Serial.println("");

      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 880 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 880 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "Real payload size is "
# 880 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 880 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));
      Serial.print(r_size);
      Serial.println("");

      LT.printASCIIPacket(message, r_size);
      Serial.println("");

      int pl=r_size+app_key_offset;

      uint8_t p_type=0x10;


      // indicate that payload is encrypted
      p_type = p_type | 0x04;



      // indicate that we have an appkey
      p_type = p_type | 0x02;


/**********************************  
  ___   _____ _____ 
 / _ \ |  ___/  ___|
/ /_\ \| |__ \ `--. 
|  _  ||  __| `--. | | | || |___/\__/ /
/
\_| |_/\____/\____/ 
***********************************/
//use AES (LoRaWAN-like) encrypting
///////////////////////////////////




      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 915 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 915 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "end-device uses encapsulated LoRaWAN packet format only for encryption\n"
# 915 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 915 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));

      pl=local_aes_lorawan_create_pkt(message, pl, app_key_offset);


/********************************** 
 _      _____ _____ 
| |    /  ___/  __ | |    \ `--.| /  \/
/
| |     `--. \ |    
| |____/\__/ / \__/\_____/\____/ \____/
/
***********************************/
//use our Lightweight Stream Cipher (LSC) encrypting
////////////////////////////////////////////////////





      startSend=millis();

      LT.CarrierSense();
# 949 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
      //will return packet length sent if OK, otherwise 0 if transmit error
      if (LT.transmitAddressed(message, pl, p_type, 1, node_addr, 10000, 14, 0x01))

      {
        endSend = millis();
        TXPacketCount++;
        uint16_t localCRC = LT.CRCCCITT(message, pl, 0xFFFF);
        Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 956 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 956 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
       "CRC,"
# 956 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
       ); &__c[0];}))
# 956 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
       )));
        Serial.print(localCRC,16);

        if (LT.readAckStatus()) {
          Serial.println("");
          Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 961 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
         (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 961 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
         "Received ACK from "
# 961 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
         ); &__c[0];}))
# 961 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
         )));
          Serial.println(LT.readRXSource());
          Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 963 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
         (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 963 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
         "SNR of transmitted pkt is "
# 963 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
         ); &__c[0];}))
# 963 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
         )));
          Serial.println(LT.readPacketSNRinACK());
        }
      }
      else
      {
        endSend=millis();
        //if here there was an error transmitting packet
        uint16_t IRQStatus;
        IRQStatus = LT.readIrqStatus();
        Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 973 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 973 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
       "SendError,"
# 973 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
       ); &__c[0];}))
# 973 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
       )));
        Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 974 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 974 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
       ",IRQreg,"
# 974 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
       ); &__c[0];}))
# 974 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
       )));
        Serial.print(IRQStatus,16);
        LT.printIrqStatus();
      }






      Serial.println("");
      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 985 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 985 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "LoRa pkt size "
# 985 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 985 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));
      Serial.print(pl);
      Serial.println("");

      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 989 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 989 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "LoRa pkt seq "
# 989 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 989 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));
      Serial.print(LT.readTXSeqNo()-1);
      Serial.println("");

      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 993 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 993 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "LoRa Sent in "
# 993 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 993 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));
      Serial.print(endSend-startSend);
      Serial.println("");

///////////////////////////////////////////////////////////////////
// DOWNLINK BLOCK - EDIT ONLY NEW COMMAND SECTION
// 
///////////////////////////////////////////////////////////////////






      uint8_t rxw_max=1;



      // Invert I/Q
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 1012 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1012 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "Inverting I/Q for RX"
# 1012 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 1012 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));
      LT.invertIQ(true);

      uint8_t rxw=1;
      uint8_t RXPacketL;

      do {
          Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1019 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
         (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1019 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
         "Wait for "
# 1019 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
         ); &__c[0];}))
# 1019 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
         )));
          Serial.print((endSend+rxw*2000) - millis());
          Serial.println("");

          //target 1s which is RX1 for LoRaWAN in most regions
          //then target 1s more which is RX2 for LoRaWAN in most regions
          while (millis()-endSend < rxw*2000)
            ;

          Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1028 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
         (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1028 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
         "Wait for incoming packet-RX"
# 1028 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
         ); &__c[0];}))
# 1028 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
         )));
          Serial.print(rxw);
          Serial.println("");

          // wait for incoming packets
          RXPacketL = LT.receive(message, sizeof(message), 850, 0x01);

          //we received something in RX1
          if (RXPacketL && rxw==1)
            rxw=rxw_max+1;
          else
            // try RX2 only if we are in LoRaWAN mode and nothing has been received in RX1
            if (++rxw<=rxw_max) {







              //change freq to 434.665 as we are targeting RX2 window
              Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1049 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1049 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             "Set downlink frequency to 434.665MHz\n"
# 1049 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             ); &__c[0];}))
# 1049 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             )));
              LT.setRfFrequency(434655000, Offset);



              //change to SF12 as we are targeting RX2 window
              //valid for EU868 and EU433 band        
              Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1056 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1056 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             "Set to SF12\n"
# 1056 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
             ); &__c[0];}))
# 1056 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
             )));

              LT.setModulationParams(0x0C, Bandwidth, CodeRate, Optimisation);




            }
            else {
# 1082 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
          }
      } while (rxw<=rxw_max);


      // Invert I/Q
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 1087 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1087 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "I/Q back to normal"
# 1087 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 1087 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));
      LT.invertIQ(false);

      // we have received a downlink message
      //
      if (RXPacketL) {
        int i=0;
        long cmdValue;


        char print_buff[50];

        sprintf((char*)print_buff, "^p%d,%d,%d,%d,%d,%d,%d\n",
                   LT.readRXDestination(),
                   LT.readRXPacketType(),
                   LT.readRXSource(),
                   LT.readRXSeqNo(),
                   RXPacketL,
                   LT.readPacketSNR(),
                   LT.readPacketRSSI());
        Serial.print((char*)print_buff);

        Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1109 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1109 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
       "frame hex\n"
# 1109 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
       ); &__c[0];}))
# 1109 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
       )));

        for ( i=0 ; i<RXPacketL; i++) {
          if (message[i]<16)
            Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1113 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1113 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
           "0"
# 1113 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
           ); &__c[0];}))
# 1113 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
           )));
          Serial.print(message[i],16);
          Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1115 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
         (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1115 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
         " "
# 1115 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
         ); &__c[0];}))
# 1115 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
         )));
        }
        Serial.println("");

        message[i]=(char)'\0';
        // in non-LoRaWAN, we try to print the characters
        Serial.print((char*)message);
        i=0;







        Serial.println("");
        Serial.flush();

        // commands have following format /@A6#
        //
        if (i>=0 && message[i]=='/' && message[i+1]=='@') {

            char cmdstr[15];
            // copy the downlink payload, up to sizeof(cmdstr)
            strncpy(cmdstr,(char*)(message+i),sizeof(cmdstr));

            Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1141 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1141 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
           "Parsing command\n"
# 1141 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
           ); &__c[0];}))
# 1141 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
           )));
            Serial.print(cmdstr);
            Serial.println("");
            i=2;

            switch ((char)cmdstr[i]) {


                  // set the node's address, /@A10# to set the address to 10 for instance
                  case 'A':

                      i++;
                      cmdValue=getCmdValue(i, cmdstr);

                      // cannot set addr greater than 255
                      if (cmdValue > 255)
                              cmdValue = 255;
                      // cannot set addr lower than 2 since 0 is broadcast and 1 is for gateway
                      if (cmdValue < 2)
                              cmdValue = node_addr;
                      // set node addr        
                      node_addr=cmdValue;

                      DevAddr[3] = (unsigned char)node_addr;

                      LT.setDevAddr(node_addr);
                      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1167 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1167 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
                     "Set LoRa node addr to "
# 1167 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
                     ); &__c[0];}))
# 1167 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
                     )));
                      Serial.print(node_addr);
                      Serial.println("");







                      break;

                  // set the time between 2 transmissions, /@I10# to set to 10 minutes for instance
                  case 'I':

                      i++;
                      cmdValue=getCmdValue(i, cmdstr);

                      // cannot set addr lower than 1 minute
                      if (cmdValue < 1)
                              cmdValue = idlePeriodInMin;
                      // idlePeriodInMin      
                      idlePeriodInMin=cmdValue;

                      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1191 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1191 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
                     "Set duty-cycle to "
# 1191 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
                     ); &__c[0];}))
# 1191 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
                     )));
                      Serial.print(idlePeriodInMin);
                      Serial.println("");
# 1202 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
                      break;

                  // Toggle a LED to illustrate an actuation example
                  // command syntax is /@L2# for instance
                  case 'L':

                      i++;
                      cmdValue=getCmdValue(i, cmdstr);

                      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1211 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1211 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
                     "Toggle LED on pin "
# 1211 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
                     ); &__c[0];}))
# 1211 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
                     )));
                      Serial.print(cmdValue);
                      Serial.println("");

                      // warning, there is no check on the pin number
                      // /@L2# for instance will toggle LED connected to digital pin number 2
                      pinMode(cmdValue, 0x1);
                      digitalWrite(cmdValue, 0x1);
                      delay(500);
                      digitalWrite(cmdValue, 0x0);
                      delay(500);
                      digitalWrite(cmdValue, 0x1);
                      delay(500);
                      digitalWrite(cmdValue, 0x0);

                      break;

                  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                  // add here new commands
                  //  

                  //
                  /////////////////////////////////////////////////////////////////////////////////////////////////////////////

                  default:

                    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1237 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1237 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
                   "Unrecognized cmd\n"
# 1237 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
                   ); &__c[0];}))
# 1237 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
                   )));
                    break;
            }
        }
      }
      else
        Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1243 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1243 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
       "No downlink\n"
# 1243 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
       ); &__c[0];}))
# 1243 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
       )));


///////////////////////////////////////////////////////////////////
// LOW-POWER BLOCK - DO NOT EDIT
// 
///////////////////////////////////////////////////////////////////


      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1252 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1252 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "Switch to power saving mode\n"
# 1252 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 1252 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));

      //CONFIGURATION_RETENTION=RETAIN_DATA_RAM on SX128X
      //parameter is ignored on SX127X
      LT.setSleep(0x04 /*these have no effect in SX127x, kept for compatibility*/);

      //how much do we still have to wait, in millisec?
      unsigned long now_millis=millis();

      Serial.println(now_millis);
      Serial.println(nextTransmissionTime);

      if (millis() > nextTransmissionTime)
        nextTransmissionTime=millis()+1000;

      unsigned long waiting_t = nextTransmissionTime-now_millis;

      Serial.println(waiting_t);
      Serial.flush();

      lowPower(waiting_t);

      Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 1274 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 1274 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     "Wake from power saving mode\n"
# 1274 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino" 3
     ); &__c[0];}))
# 1274 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
     )));
      LT.wake();
# 1286 "/home/william/Documents/Ecoles/cesure/rhf/lora/LowCostLoRaGw/Arduino_exp/Arduino_LoRa_SX12XX_temp/Arduino_LoRa_SX12XX_temp.ino"
}
