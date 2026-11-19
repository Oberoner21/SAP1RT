/*
    SAP1RT - SAP1 Turing Random Access
    Modul: rule_jmp.h

    Copyright(C) 2026 by Oberoner

    Jump to address stored in the argument of JMP instruction
    Rules           : ?? 

*/

void GenerateRuleJMP(uint16_t rule) {

    uint8_t i = 0;
  
    for(i=0; i<4; i++) {

        rule = SetNPPtoMemAddress(rule, MAR, i);

        // Read current memory bit and branch
        SetRule(rule, '0', '0', PC -(i*2+1), rule +1);
        SetRule(rule, '1', '1', PC -(i*2+1), rule +2);
        rule++;

        // Write 0 into current bit of PC
        SetRule(rule, '0', '0', MAR, rule +2);
        SetRule(rule, '1', '0', MAR, rule +2);
        rule++;

        // Write 1 into current bit of PC
        SetRule(rule, '0', '1', MAR, rule +1);
        SetRule(rule, '1', '1', MAR, rule +1);
        rule++;
    }

    // Jump to RULE_FETCH
    SetRule(rule, '0', '0', MAR, RULE_FETCH);
    SetRule(rule, '1', '1', MAR, RULE_FETCH);
    rule++;
}