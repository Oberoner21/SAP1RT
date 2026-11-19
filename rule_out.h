/*
    SAP1RT - SAP1 Turing Random Access
    Modul: rule_out.h

    Copyright(C) 2026 by Oberoner

    Clock out register A into Shift register 74LS595, MSB first
    Rules           : ?? 

*/

void GenerateRuleOUT(uint16_t rule) {

    uint8_t i = 0;

    // Seek to A7
    SetRule(rule, '0', '0', AB -15, rule +1);
    SetRule(rule, '1', '1', AB -15, rule +1);
    rule++; 

    for(i=7; i>0; i--) {

        // Read current bit of A and set Line CLKOUT
        SetOUTCLK(HIGH);
        SetRule(rule, '0', '0', AB -(i*2), rule +1);
        SetRule(rule, '1', '1', AB -(i*2), rule +1);
        rule++;

        // Skip Bx and Clear the line CLKOUT
        SetOUTCLK(LOW);
        SetRule(rule, '0', '0', AB -(i*2-1), rule +1);
        SetRule(rule, '1', '1', AB -(i*2-1), rule +1);
        rule++;
    }

    // Jump to RULE_FETCH
    SetRule(rule, '0', '0', AB, RULE_FETCH);
    SetRule(rule, '1', '1', AB, RULE_FETCH);
    rule++; 
}