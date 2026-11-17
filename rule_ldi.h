/*
    SAP1RT - SAP1 Turing Random Access
    Modul: rule_ldi.h

    Copyright(C) 2026 by Oberoner

    Rule for Opcode LDI
    Copies the opcode argument (low nibble) into register A
    Entry point     : NP pointer position M0
    Exit point      : NP pointer position I3 of IR
    Rules           : ?? 

*/
#pragma once

void GenerateRuleLDI(uint16_t rule) {

    uint8_t i = 0;
  
    for(i=0; i<4; i++) {

        rule = SetNPPtoMemAddress(rule, MAR, i);

        // Read current memory bit and branch
        SetRule(rule, '0', '0', AB -(i*2+1), rule +1);
        SetRule(rule, '1', '1', AB -(i*2+1), rule +2);
        rule++;

        // Write 0 into current bit of A
        SetRule(rule, '0', '0', MAR, rule +2);
        SetRule(rule, '1', '0', MAR, rule +2);
        rule++;

        // Write 1 into current bit of A
        SetRule(rule, '0', '1', MAR, rule +1);
        SetRule(rule, '1', '1', MAR, rule +1);
        rule++;
    }

    // +++ Set the high nibble of A to zero +++

    // Seek to A4
    SetRule(rule, '0', '0', AB -9, rule +1);
    SetRule(rule, '1', '1', AB -9, rule +1);
    rule++;

    for(i=4; i<8; i++) {

        // Write 0 into current bit of A
        SetRule(rule, '0', '0', AB -(i*2+1), rule +1);
        SetRule(rule, '1', '0', AB -(i*2+1), rule +1);
        rule++;    
    }

    // Jump to RULE_FETCH
    SetRule(rule, '0', '0', MAR, RULE_FETCH);
    SetRule(rule, '1', '1', MAR, RULE_FETCH);
    rule++;

}