/*
    SAP1RT - SAP1 Turing Random Access
    Modul: rule_decode.h

    Copyright(C) 2026 by Oberoner

    Decode the instruction and jump to the decoded rule
    Entry point     : NP pointer position I3 of the register IR
    Exit point      : NP pointer position I3 of IR
    Rules           : ?? 

*/

void GenerateRuleDECODE(uint16_t rule){

    // ----- Instructio demuxer 4 to 16 --------
  
    // 0
    // Read I3 and branch
    SetRule(rule, '0', '0', IR-2, rule +1);     // I3=0
    SetRule(rule, '1', '1', IR-2, rule +8);     // I3=1
    rule++; 

    // 1
    // I3=0, Read I2
    SetRule(rule, '0', '0', IR-1, rule +1);     // I3=0 & I2=0
    SetRule(rule, '1', '1', IR-1, rule +4);     // I3=0 & I2=1
    rule++;

    // 2
    // I3=0, I2=0, Read I1
    SetRule(rule, '0', '0', IR, rule +1);       // I3=0 & I2=0 & I1=0
    SetRule(rule, '1', '1', IR, rule +2);       // I3=0 & I2=0 & I1=1
    rule++;

    // 3
    // I3=0, I2=0, I1=0, Read I0
    SetRule(rule, '0', '0', MAR, RULE_NOP);     // I3=0 & I2=0 & I1=0 & I0=0 -> 0x0 NOP
    SetRule(rule, '1', '1', MAR, RULE_LDA);     // I3=0 & I2=0 & I1=0 & I0=1 -> 0x1 LDA
    rule++;

    // 4
    // I3=0, I2=0, I1=1, Read I0 
    SetRule(rule, '0', '0', MAR, RULE_ADD);     // I3=0 & I2=0 & I1=1 & I0=0 -> 0x2 ADD
    SetRule(rule, '1', '1', MAR, RULE_SUB);     // I3=0 & I2=0 & I1=1 & I0=1 -> 0x3 SUB
    rule++;

    // 5
    // I3=0, I2=1, Read I1
    SetRule(rule, '0', '0', IR, rule +1);       // I3=0 & I2=0 & I1=0
    SetRule(rule, '1', '1', IR, rule +2);       // I3=0 & I2=0 & I1=1
    rule++;

    // 6
    // I3=0, I2=1, I1=0, Read I0
    SetRule(rule, '0', '0', MAR, RULE_STA);     // I3=0 & I2=1 & I1=0 & I0=0 -> 0x4 STA
    SetRule(rule, '1', '1', MAR, RULE_LDI);     // I3=0 & I2=1 & I1=0 & I0=1 -> 0x5 LDI
    rule++;

    // 7
    // I3=0, I2=1, I1=1, Read I0
    SetRule(rule, '0', '0', MAR, RULE_JMP);     // I3=0 & I2=1 & I1=1 & I0=0 -> 0x6 JMP
    SetRule(rule, '1', '1', MAR, RULE_JC);      // I3=0 & I2=1 & I1=1 & I0=1 -> 0x7 JC
    rule++;

    // +++ I3 = 1 +++

    // 8
    // I3=1, Read I2
    SetRule(rule, '0', '0', IR-1, rule +1);     // I3=1 & I2=0
    SetRule(rule, '1', '1', IR-1, rule +4);     // I3=1 & I2=1
    rule++;

    // 9
    // I3=1, I2=0, Read I1
    SetRule(rule, '0', '0', IR, rule +1);       // I3=1 & I2=0 & I1=0
    SetRule(rule, '1', '1', IR, rule +2);       // I3=1 & I2=0 & I1=1
    rule++;

    // 10
    // I3=1, I2=0, I1=0, Read I0
    SetRule(rule, '0', '0', MAR, RULE_JZ);      // I3=1 & I2=0 & I1=0 & I0=0 -> 0x8 JZ
    SetRule(rule, '1', '1', MAR, RULE_ERROR);   // I3=1 & I2=0 & I1=0 & I0=1 -> 0x9 
    rule++;

    // 11
    // I3=1, I2=0, I1=1, Read I0 
    SetRule(rule, '0', '0', MAR, RULE_ERROR);   // I3=1 & I2=0 & I1=1 & I0=0 -> 0xA
    SetRule(rule, '1', '1', MAR, RULE_ERROR);   // I3=1 & I2=0 & I1=1 & I0=1 -> 0xB
    rule++;

    // 12
    // I3=1, I2=1, Read I1
    SetRule(rule, '0', '0', IR, rule +1);       // I3=1 & I2=0 & I1=0
    SetRule(rule, '1', '1', IR, rule +2);       // I3=1 & I2=0 & I1=1
    rule++;

    // 13
    // I3=1, I2=1, I1=0, Read I0
    SetRule(rule, '0', '0', MAR, RULE_ERROR);   // I3=1 & I2=1 & I1=0 & I0=0 -> 0xC
    SetRule(rule, '1', '1', MAR, RULE_ERROR);   // I3=1 & I2=1 & I1=0 & I0=1 -> 0xD
    rule++;

    // 14
    // I3=1, I2=1, I1=1, Read I0
    SetRule(rule, '0', '0', MAR, RULE_OUT);     // I3=1 & I2=1 & I1=1 & I0=0 -> 0xE OUT
    SetRule(rule, '1', '1', MAR, RULE_HLT);     // I3=1 & I2=0 & I1=1 & I0=1 -> 0xF HLT
    rule++;

}