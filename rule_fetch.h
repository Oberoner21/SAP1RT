/*
    SAP1RT - SAP1 Turing Random Access
    Modul: rule_fetch.h

    Copyright(C) 2026 by Oberoner

    Fetch the current instruction into IR and the argument into MAR. Then jump to RULE_DECODE
    Entry point     : NP pointer position M0 of the register MAR
    Exit point      : NP pointer position I3 of Instruction Registers IR
    Rules           : ?? 

*/
#pragma once
#include "utils.h"
#include "rule_SetNPPtoMemAddress.h"

uint16_t CopyPCtoMAR(uint16_t rule) {
    
    // Seek to P0
    SetRule(rule, '0', '0', PC -1, rule +1);
    SetRule(rule, '1', '1', PC -1, rule +1);
    rule++;

    // --- Copy Intreleaved PC to MAR
    for(uint8_t i=0; i<4; i++){

        // Read current PC bit and branch
        SetRule(rule, '0', '0', MAR -i, rule +1);
        SetRule(rule, '1', '1', MAR -i, rule +2);
        rule++;

        // Write 0 into current MAR bit
        SetRule(rule, '0', '0', PC -(i*2+3), rule +2);
        SetRule(rule, '1', '0', PC -(i*2+3), rule +2);
        rule++;

        // Write 1 into current MAR bit
        SetRule(rule, '0', '1', PC -(i*2+3), rule +1);
        SetRule(rule, '1', '1', PC -(i*2+3), rule +1);
        rule++;
    }

    return rule;
}


uint16_t IncPC(uint16_t rule) {

    uint8_t i = 0;

    // Seek to PC
    SetRule(rule, '0', '0', PC -(i*2), rule +1);
    SetRule(rule, '1', '1', PC -(i*2), rule +1);
    rule++;

    // --- A + B -> PC + 1 ---
    
    /*
    |   |   | C |   | C |
    | A | B | I | S | O |
    |---|---|---|---|---|
    | 0 | 0 | 0 | 0 | 0 |
    | 0 | 0 | 1 | 1 | 0 |
    | 0 | 1 | 0 | 1 | 0 |
    | 0 | 1 | 1 | 0 | 1 |
    | 1 | 0 | 0 | 1 | 0 |
    | 1 | 0 | 1 | 0 | 1 |
    | 1 | 1 | 0 | 0 | 1 |
    | 1 | 1 | 1 | 1 | 1 |
    */

    for(i=0; i<3; i++) {

        // 0
        // CI = 0, Read B
        SetRule(rule, '0', '0', PC -(i*2+1), rule +1);  // CI=0, B=0
        SetRule(rule, '1', '1', PC -(i*2+1), rule +2);  // CI=0, B=1
        rule++;

        // 1
        // CI=0, B=0, Read A
        SetRule(rule, '0', '0', PC -(i*2+2), rule +5);    // CI=0, B=0, A=0, SU=0, CO=0, END_NO_CARRY
        SetRule(rule, '1', '1', PC -(i*2+2), rule +5);    // CI=0, B=0, A=1, SU=1, CO=0, END_NO_CARRY
        rule++;

        // 2
        // CI=0, B=1, Read A
        SetRule(rule, '0', '1', PC -(i*2+2), rule +4);    // CI=0, B=1, A=0, SU=1, CO=0, END_NO_CARRY  +4
        SetRule(rule, '1', '0', PC -(i*2+2), rule +7);    // CI=0, B=0, A=1, SU=1, CO=1, END_CARRY
        rule++;

        // 3
        // CI = 1, Read Bx
        SetRule(rule, '0', '0', PC -(i*2+1), rule +1);  // CI=1, B=0
        SetRule(rule, '1', '1', PC -(i*2+1), rule +2);  // CI=1, B=1
        rule++;

        // 4
        // CI = 1, B=0, Read A
        SetRule(rule, '0', '1', PC -(i*2+2), rule +2);    // CI=1, B=0, A=0, SU=1, CO=0, END_NO_CARRY
        SetRule(rule, '1', '0', PC -(i*2+2), rule +5);    // CI=1, B=0, A=1, SU=0, CO=1, END_CARRY
        rule++;

        // 5
        // CI = 1, B=1, Read A
        SetRule(rule, '0', '0', PC -(i*2+2), rule +4);    // CI=1, B=1, A=0, SU=0, CO=1, END_CARRY
        SetRule(rule, '1', '1', PC -(i*2+2), rule +4);    // CI=1, B=1, A=1, SU=1, CO=1, END_CARRY
        rule++;

    }
    
    // ---- Last bit -> EXIT -----
    
    // 0
    // CI = 0, Read B
    SetRule(rule, '0', '0', PC -7, rule +1);  // CI=0, B=0  +1
    SetRule(rule, '1', '1', PC -7, rule +2);  // CI=0, B=1
    rule++;

    // 1
    // CI=0, B=0, Read A
    SetRule(rule, '0', '0', PC -7, rule +5);    // CI=0, B=0, A=0, SU=0, CO=0, END_NO_CARRY  +5
    SetRule(rule, '1', '1', PC -7, rule +5);    // CI=0, B=0, A=1, SU=1, CO=0, END_NO_CARRY
    rule++;

    // 2
    // CI=0, B=1, Read A
    SetRule(rule, '0', '1', PC -7, rule +4);    // CI=0, B=1, A=0, SU=1, CO=0, END_NO_CARRY
    SetRule(rule, '1', '0', PC -7, rule +4);    // CI=0, B=0, A=1, SU=1, CO=1, END_CARRY
    rule++;

    // 3
    // CI = 1, Read Bx
    SetRule(rule, '0', '0', PC -7, rule +1);  // CI=1, B=0
    SetRule(rule, '1', '1', PC -7, rule +2);  // CI=1, B=1
    rule++;

    // 4
    // CI = 1, B=0, Read A
    SetRule(rule, '0', '1', PC -7, rule +2);    // CI=1, B=0, A=0, SU=1, CO=0, END_NO_CARRY
    SetRule(rule, '1', '0', PC -7, rule +2);    // CI=1, B=0, A=1, SU=0, CO=1, END_CARRY
    rule++;

    // 5
    // CI = 1, B=1, Read A
    SetRule(rule, '0', '0', PC -7, rule +1);    // CI=1, B=1, A=0, SU=0, CO=1, END_CARRY
    SetRule(rule, '1', '1', PC -7, rule +1);    // CI=1, B=1, A=1, SU=1, CO=1, END_CARRY
    rule++;

    return rule;
}

// Copy next instruction into IR. This is the high nibble of
// the current operation code
uint16_t GetInstruction(uint16_t rule) {

    uint8_t i = 0;

    for(i=0; i<4; i++) {

        // Set NPP to current memory bit
        rule = SetNPPtoMemAddress(rule, MAR, i +4);

        // Read current memory bit and branch
        SetRule(rule, '0', '0', IR -i, rule +1);
        SetRule(rule, '1', '1', IR -i, rule +2);
        rule++;

        // Write 0 into current bit of IR
        SetRule(rule, '0', '0', IR -i, rule +2);
        SetRule(rule, '1', '0', IR -i, rule +2);
        rule++;    

        // Write 1 into current bit of IR
        SetRule(rule, '0', '1', IR -i, rule +1);
        SetRule(rule, '1', '1', IR -i, rule +1);
        rule++;  
    }


    return rule;
}


void GenerateRuleFETCH(uint16_t rule)
{

    rule = CopyPCtoMAR(rule);
    rule = IncPC(rule);
    rule = GetInstruction(rule);

    // Sek to I3 and go to RULE_DECODE
    SetRule(rule, '0', '0', IR -3, RULE_DECODE);
    SetRule(rule, '0', '0', IR -3, RULE_DECODE);
    rule++; 
}