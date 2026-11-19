/*
    SAP1RT - SAP1 Turing Random Access
    Modul: rule_alu.h

    Copyright(C) 2026 by Oberoner

    Compute A = A + B and sets the flags
    Entry point     : NP pointer position M0
    Exit point      : NP pointer position I3 of IR
    Rules           : 364 

*/

void GenerateRuleALU(uint16_t rule) {

    uint8_t i = 0;

    // Seek to B0
    SetRule(rule, '0', '0', AB -(i*2), rule +1);
    SetRule(rule, '1', '1', AB -(i*2), rule +1);
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

    for(i=0; i<7; i++) {

        // 0
        // CI = 0, Read B
        SetRule(rule, '0', '0', AB -(i*2+1), rule +1);  // CI=0, B=0
        SetRule(rule, '1', '1', AB -(i*2+1), rule +2);  // CI=0, B=1
        rule++;

        // 1
        // CI=0, B=0, Read A
        SetRule(rule, '0', '0', AB -(i*2+2), rule +5);    // CI=0, B=0, A=0, SU=0, CO=0, END_NO_CARRY
        SetRule(rule, '1', '1', AB -(i*2+2), rule +5);    // CI=0, B=0, A=1, SU=1, CO=0, END_NO_CARRY
        rule++;

        // 2
        // CI=0, B=1, Read A
        SetRule(rule, '0', '1', AB -(i*2+2), rule +4);    // CI=0, B=1, A=0, SU=1, CO=0, END_NO_CARRY  +4
        SetRule(rule, '1', '0', AB -(i*2+2), rule +7);    // CI=0, B=0, A=1, SU=1, CO=1, END_CARRY
        rule++;

        // 3
        // CI = 1, Read Bx
        SetRule(rule, '0', '0', AB -(i*2+1), rule +1);    // CI=1, B=0
        SetRule(rule, '1', '1', AB -(i*2+1), rule +2);    // CI=1, B=1
        rule++;

        // 4
        // CI = 1, B=0, Read A
        SetRule(rule, '0', '1', AB -(i*2+2), rule +2);    // CI=1, B=0, A=0, SU=1, CO=0, END_NO_CARRY
        SetRule(rule, '1', '0', AB -(i*2+2), rule +5);    // CI=1, B=0, A=1, SU=0, CO=1, END_CARRY
        rule++;

        // 5
        // CI = 1, B=1, Read A
        SetRule(rule, '0', '0', AB -(i*2+2), rule +4);    // CI=1, B=1, A=0, SU=0, CO=1, END_CARRY
        SetRule(rule, '1', '1', AB -(i*2+2), rule +4);    // CI=1, B=1, A=1, SU=1, CO=1, END_CARRY
        rule++;

    }
    
    // ---- Last bit -> EXIT -----
    
    // 0
    // CI = 0, Read B
    SetRule(rule, '0', '0', AB -15, rule +1);  // CI=0, B=0  +1
    SetRule(rule, '1', '1', AB -15, rule +2);  // CI=0, B=1
    rule++;

    // 1
    // CI=0, B=0, Read A
    SetRule(rule, '0', '0', FC, rule +6);    // CI=0, B=0, A=0, SU=0, CO=0, END_NO_CARRY
    SetRule(rule, '1', '1', FC, rule +6);    // CI=0, B=0, A=1, SU=1, CO=0, END_NO_CARRY
    rule++;

    // 2
    // CI=0, B=1, Read A
    SetRule(rule, '0', '1', FC, rule +5);    // CI=0, B=1, A=0, SU=1, CO=0, END_NO_CARRY
    SetRule(rule, '1', '0', FC, rule +4);    // CI=0, B=0, A=1, SU=1, CO=1, END_CARRY
    rule++;

    // 3
    // CI = 1, Read Bx
    SetRule(rule, '0', '0', AB -15, rule +1);  // CI=1, B=0
    SetRule(rule, '1', '1', AB -15, rule +2);  // CI=1, B=1
    rule++;

    // 4
    // CI = 1, B=0, Read A
    SetRule(rule, '0', '1', FC, rule +3);    // CI=1, B=0, A=0, SU=1, CO=0, END_NO_CARRY
    SetRule(rule, '1', '0', FC, rule +2);    // CI=1, B=0, A=1, SU=0, CO=1, END_CARRY
    rule++;

    // 5
    // CI = 1, B=1, Read A
    SetRule(rule, '0', '0', FC, rule +1);    // CI=1, B=1, A=0, SU=0, CO=1, END_CARRY
    SetRule(rule, '1', '1', FC, rule +1);    // CI=1, B=1, A=1, SU=1, CO=1, END_CARRY
    rule++;

    // Set Carry
    SetRule(rule, '0', '1', FC, RULE_FETCH);
    SetRule(rule, '1', '1', FC, RULE_FETCH);
    rule++;

    // Clear Carry
    SetRule(rule, '0', '0', FC, RULE_FETCH);
    SetRule(rule, '1', '0', FC, RULE_FETCH);
    rule++;

}