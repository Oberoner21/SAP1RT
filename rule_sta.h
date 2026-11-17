/*
    SAP1RT - SAP1 Turing Random Access
    Modul: rule_sta.h

    Copyright(C) 2026 by Oberoner

    Copies the value of A into memory adressed by IR
    Entry point     : NP pointer position M0
    Exit point      : NP pointer position I3 of IR
    Rules           : 364 

*/

void GenerateRuleSTA(uint16_t rule) {

    uint8_t i;

    // Use the IR register as a temporary storage
    // for the target address in memory.


    // 1 +++ Get destination address from opcode argument (low nibble)
    //   addressed by MAR and copy it into register IR +++

    for(i=0; i<4; i++) {

        rule = SetNPPtoMemAddress(rule, MAR, i);

        // Read memory address bit and branch
        SetRule(rule, '0', '0', IR -i, rule +1);
        SetRule(rule, '1', '1', IR -i, rule +2);
        rule++;

        // Write 0 into current bit of IR
        SetRule(rule, '0', '0', IR, rule +2);
        SetRule(rule, '1', '0', IR, rule +2);
        rule++;

        // Write 1 into current bit of IR
        SetRule(rule, '0', '1', IR, rule +1);
        SetRule(rule, '1', '1', IR, rule +1);
        rule++;
    }

    // 2 +++ Copy value of A into memory addressed by IR

    for(i=0; i<8; i++) {

        // Seek to current bit of A
        SetRule(rule, '0', '0', AB -(i*2+1), rule +1);
        SetRule(rule, '1', '1', AB -(i*2+1), rule +1);
        rule++;    

        // Read current bit of A and branche
        SetRule(rule, '0', '0', AB, rule +1);
        SetRule(rule, '1', '1', AB, rule +18);
        rule++;    

        // Set NPP to current bit of destination address in memory
        rule = SetNPPtoMemAddress(rule, IR, i);

        // Write 0 into current bit of A
        SetRule(rule, '0', '0', IR, rule +18);
        SetRule(rule, '1', '0', IR, rule +18);
        rule++;

        // Set NPP to current bit of destination address in memory
        rule = SetNPPtoMemAddress(rule, IR, i);

        // Write 1 into current bit of A
        SetRule(rule, '0', '1', IR, rule +1);
        SetRule(rule, '1', '1', IR, rule +1);
        rule++;
    }

    // Jump to RULE_FETCH
    SetRule(rule, '0', '0', MAR, RULE_FETCH);
    SetRule(rule, '1', '0', MAR, RULE_FETCH);
    rule++;
}