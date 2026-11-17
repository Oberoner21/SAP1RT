/*
    SAP1RT - SAP1 Turing Random Access
    Modul: rule_SetNPPtoMemAddress.h

    Copyright(C) 2026 by Oberoner

    Sets the Notepad pointer to memory address stored in REG
    Rules           : ?? 

*/

#pragma once
#include "notepad.h"

uint16_t SetNPPtoMemAddress(uint16_t rule, uint8_t REG, uint8_t byte = 0) {

    uint8_t i;

    // Set NPP to REG3
    SetRule(rule, '0', '0', REG-3, rule +1);
    SetRule(rule, '1', '1', REG-3, rule +1);
    rule++;

    // ----- REG address demuxer 4 to 16 --------
  
    // 0
    // Read M3 and branch
    SetRule(rule, '0', '0', REG-2, rule +1);                       // M3=0
    SetRule(rule, '1', '1', REG-2, rule +8);                       // M3=1
    rule++; 

    // 1
    // M3=0, Read M2
    SetRule(rule, '0', '0', REG-1, rule +1);                        // M3=0 & M2=0
    SetRule(rule, '1', '1', REG-1, rule +4);                        // M3=0 & M2=1
    rule++;

    // 2
    // M3=0, M2=0, Read M1
    SetRule(rule, '0', '0', REG, rule +1);                          // M3=0 & M2=0 & M1=0
    SetRule(rule, '1', '1', REG, rule +2);                          // M3=0 & M2=0 & M1=1
    rule++;

    // 3
    // M3=0, M2=0, M1=0, Read M0
    SetRule(rule, '0', '0', MEMSTART +(1*9-1-byte), rule +12);      // M3=0 & M2=0 & M1=0 & M0=0 -> NPP=MEM0
    SetRule(rule, '1', '1', MEMSTART +(2*9-1-byte), rule +12);      // M3=0 & M2=0 & M1=0 & M0=1 -> NPP=MEM1
    rule++;

    // 4
    // M3=0, M2=0, M1=1, Read M0 
    SetRule(rule, '0', '0', MEMSTART +(3*9-1-byte), rule +11);      // M3=0 & M2=0 & M1=1 & M0=0 -> NPP=MEM2
    SetRule(rule, '1', '1', MEMSTART +(4*9-1-byte), rule +11);      // M3=0 & M2=0 & M1=1 & M0=1 -> NPP=MEM3
    rule++;

    // 5
    // M3=0, M2=1, Read M1
    SetRule(rule, '0', '0', REG, rule +1);                          // M3=0 & M2=0 & M1=0
    SetRule(rule, '1', '1', REG, rule +2);                          // M3=0 & M2=0 & M1=1
    rule++;

    // 6
    // M3=0, M2=1, M1=0, Read M0
    SetRule(rule, '0', '0', MEMSTART +(5*9-1-byte), rule +9);       // M3=0 & M2=1 & M1=0 & M0=0 -> NPP=MEM4
    SetRule(rule, '1', '1', MEMSTART +(6*9-1-byte), rule +9);       // M3=0 & M2=1 & M1=0 & M0=1 -> NPP=MEM5
    rule++;

    // 7
    // M3=0, M2=1, M1=1, Read M0
    SetRule(rule, '0', '0', MEMSTART +(7*9-1-byte), rule +8);       // M3=0 & M2=1 & M1=1 & M0=0 -> NPP=MEM6
    SetRule(rule, '1', '1', MEMSTART +(8*9-1-byte), rule +8);       // M3=0 & M2=0 & M1=1 & M0=1 -> NPP=MEM7
    rule++;

    // +++ M3 = 1 +++

    // 8
    // M3=1, Read M2
    SetRule(rule, '0', '0', REG-1, rule +1);                        // M3=1 & M2=0
    SetRule(rule, '1', '1', REG-1, rule +4);                        // M3=1 & M2=1
    rule++;

    // 9
    // M3=1, M2=0, Read M1
    SetRule(rule, '0', '0', REG, rule +1);                          // M3=1 & M2=0 & M1=0
    SetRule(rule, '1', '1', REG, rule +2);                          // M3=1 & M2=0 & M1=1
    rule++;

    // 10
    // M3=1, M2=0, M1=0, Read M0
    SetRule(rule, '0', '0', MEMSTART +(9*9-1-byte), rule +5);      // M3=1 & M2=0 & M1=0 & M0=0 -> NPP=MEM8
    SetRule(rule, '1', '1', MEMSTART +(10*9-1-byte), rule +5);     // M3=1 & M2=0 & M1=0 & M0=1 -> NPP=MEM9
    rule++;

    // 11
    // M3=1, M2=0, M1=1, Read M0 
    SetRule(rule, '0', '0', MEMSTART +(11*9-1-byte), rule +4);      // M3=1 & M2=0 & M1=1 & M0=0 -> NPP=MEM10
    SetRule(rule, '1', '1', MEMSTART +(12*9-1-byte), rule +4);      // M3=1 & M2=0 & M1=1 & M0=1 -> NPP=MEM11
    rule++;

    // 12
    // M3=1, M2=1, Read M1
    SetRule(rule, '0', '0', REG, rule +1);                          // M3=1 & M2=0 & M1=0
    SetRule(rule, '1', '1', REG, rule +2);                          // M3=1 & M2=0 & M1=1
    rule++;

    // 13
    // M3=1, M2=1, M1=0, Read M0
    SetRule(rule, '0', '0', MEMSTART +(13*9-1-byte), rule +2);       // M3=1 & M2=1 & M1=0 & M0=0 -> NPP=MEM12
    SetRule(rule, '1', '1', MEMSTART +(14*9-1-byte), rule +2);       // M3=1 & M2=1 & M1=0 & M0=1 -> NPP=MEM13
    rule++;

    // 14
    // M3=1, M2=1, M1=1, Read M0
    SetRule(rule, '0', '0', MEMSTART +(15*9-1-byte), rule +1);       // M3=1 & M2=1 & M1=1 & M0=0 -> NPP=MEM14
    SetRule(rule, '1', '1', MEMSTART +(16*9-1-byte), rule +1);       // M3=1 & M2=0 & M1=1 & M0=1 -> NPP=MEM15
    rule++;

    return rule;
}