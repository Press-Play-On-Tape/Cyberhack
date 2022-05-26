#pragma once

#include "Arduboy2Ext.h"
#include "../entities/Player.h"
#include "Constants.h"

class EEPROM_Utils {

  public: 

    EEPROM_Utils(){};
        
    static void initEEPROM(bool force);
    static bool isGameSaved();
    static void loadGame(Player &player);
    static void saveGame(Player &player);
    static int16_t checkSum(bool update);

};


/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'C' and 'H' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_START.  
 */

const uint8_t letter1 = 'C'; 
const uint8_t letter2 = 'H'; 

void EEPROM_Utils::initEEPROM(bool force) {

    byte c1 = EEPROM.read(Constants::EEPROM_Start_C1);
    byte c2 = EEPROM.read(Constants::EEPROM_Start_C2);

    if (c1 != letter1 || c2 != letter2 || force) { 

        uint8_t gameSaved = 0;

        EEPROM.put(Constants::EEPROM_Start_C1, letter1);
        EEPROM.put(Constants::EEPROM_Start_C2, letter2);
        EEPROM.put(Constants::EEPROM_Game_Saved, gameSaved);

        EEPROM_Utils::checkSum(true);

    }
    else {

        int16_t checkSumOld = 0;
        int16_t checkSumNow = EEPROM_Utils::checkSum(false);
        EEPROM.get(Constants::EEPROM_Checksum, checkSumOld);

        if (checkSumNow != checkSumOld) {

            EEPROM_Utils::initEEPROM(true);

        }
        
    }  

}


/* -----------------------------------------------------------------------------
 *   Has the game been saved? 
 */
bool EEPROM_Utils::isGameSaved() {

    uint8_t gameSaved = 0;
    EEPROM.get(Constants::EEPROM_Game_Saved, gameSaved);
    return gameSaved == 1;

}


/* -----------------------------------------------------------------------------
 *   Save game ..
 */
void EEPROM_Utils::saveGame(Player &player) {

    EEPROM.put(Constants::EEPROM_Game_Saved, 1);
    EEPROM.put(Constants::EEPROM_Data, player);

    EEPROM_Utils::checkSum(true);
    
}


/* -----------------------------------------------------------------------------
 *   Save game ..
 */
void EEPROM_Utils::loadGame(Player &player) {

    EEPROM.get(Constants::EEPROM_Data, player);

}


/* -----------------------------------------------------------------------------
 *   Generate and optionally save a check sum .. 
 */
int16_t EEPROM_Utils::checkSum(bool update) {

    int16_t checksum = 0;

    for (uint8_t i = 0; i < (Constants::EEPROM_End - Constants::EEPROM_Start); i++) {

        checksum = checksum + ((i % 2 == 0 ? 1 : -1) * eeprom_read_byte(reinterpret_cast<uint8_t *>(Constants::EEPROM_Start + i)));

    }

    if (update) {
        EEPROM.put(Constants::EEPROM_Checksum, static_cast<uint16_t>(checksum));
    }

    return checksum;

}