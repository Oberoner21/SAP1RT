/*
    SAP1RT - SAP1 Turing Random Access
    Modul: rule_jc.h

    Copyright(C) 2026 by Oberoner

    Jump then carry flag is set
    Entry point     : NP pointer position I3 of the register IR
    Exit point      : NP pointer position I3 of IR
    Rules           : ?? 

*/

void GenerateRuleJC(uint16_t rule) {

    // Seek to carry flag
    SetRule(rule, '0', '0', FC, rule +1);
    SetRule(rule, '1', '1', FC, rule +1);
    rule++; 

    // Read carry flag and branch
    SetRule(rule, '0', '0', MAR, RULE_FETCH);    // Carry not set -> Exit
    SetRule(rule, '1', '1', MAR, rule +1);
    rule++; 

    // +++ Carry is set -> Load PC with jump address

    for(uint8_t i=0; i<4; i++) {

        rule = SetNPPtoMemAddress(rule, MAR, i);

        // Read current memory bit and branch
        SetRule(rule, '0', '0', PC -(i*2+1), rule +1);
        SetRule(rule, '1', '1', PC -(i*2+1), rule +2);
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

    // Jump to RULE_FETCH
    SetRule(rule, '0', '0', MAR, RULE_FETCH);
    SetRule(rule, '1', '1', MAR, RULE_FETCH);
    rule++;

}