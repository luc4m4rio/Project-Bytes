/* Dell Latitude 3310 Embedded Controller firmware (Microchip MEC, ARCompact LE)
   Load base 0xBFCF0000  -  Ghidra decompilation  -  lang=ARCompact:LE:32:default
   Note: 'halt_unimplemented' markers are ARCompact opcodes the community SLEIGH
   module does not yet model; surrounding logic is still valid. */


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf0fe6) overlaps instruction at (ram,0xbfcf0fe4)
    */
/* WARNING: Removing unreachable block (ram,0xbfcf0fca) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fba) */
/* WARNING: Removing unreachable block (ram,0xbfcf0faa) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fbc) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fbe) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fcc) */
/* WARNING: Removing unreachable block (ram,0xbfcf27ce) */
/* WARNING: Removing unreachable block (ram,0xbfcf27d4) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fd2) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fd4) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fda) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fdc) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fe2) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fe6) */
/* WARNING: Removing unreachable block (ram,0xbfcd07ec) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fe8) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fea) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fec) */
/* WARNING: Removing unreachable block (ram,0xbfcf27ee) */
/* WARNING: Removing unreachable block (ram,0xbfcf0ff0) */
/* WARNING: Removing unreachable block (ram,0xbfcf27d6) */
/* WARNING: Removing unreachable block (ram,0xbfcf27da) */
/* WARNING: Removing unreachable block (ram,0xbfcf27de) */
/* WARNING: Removing unreachable block (ram,0xbfcf27e6) */
/* WARNING: Removing unreachable block (ram,0xbfd3e7f4) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fc2) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fc6) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fc8) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fce) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fd4) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fd8) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fd6) */
/* WARNING: Removing unreachable block (ram,0xbfd09ff0) */
/* WARNING: Removing unreachable block (ram,0xbfd09ff6) */
/* WARNING: Removing unreachable block (ram,0xbfc69040) */
/* WARNING: Removing unreachable block (ram,0xbfc69034) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fc2) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fc8) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fb2) */
/* WARNING: Removing unreachable block (ram,0xbfcf0ff2) */

void FUN_ram_bfcf0b9c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
  int iVar41;
  int iVar42;
  int iVar43;
  int iVar44;
  int iVar45;
  int iVar46;
  int iVar47;
  int iVar48;
  int iVar49;
  int iVar50;
  int iVar51;
  undefined1 *puVar52;
  undefined4 in_ilink1;
  undefined4 in_blink;
  bool in_Z;
  undefined1 uVar53;
  bool in_N;
  undefined1 uVar54;
  
  if (!in_N && !in_Z) {
    in_blink = 0xbfcf0ba0;
    func_0xbfc706cc();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ba0);
  if (0 < iVar1) {
    in_blink = 0xbfcf0ba8;
    func_0xbfc706cc();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ba8);
  if (0 < iVar1) {
    in_blink = 0xbfcf0bb0;
    func_0xbfc706d0();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0bb0);
  if (0 < iVar1) {
    in_blink = 0xbfcf0bb8;
    func_0xbfc706d4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0bb8);
  if (0 < iVar1) {
    in_blink = 0xbfcf0bc0;
    func_0xbfc706d0();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0bc0);
  if (0 < iVar1) {
    in_blink = 0xbfcf0bc8;
    func_0xbfc706d0();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0bc8);
  if (0 < iVar1) {
    in_blink = 0xbfcf0bd0;
    func_0xbfc706d4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0bd0);
  if (0 < iVar1) {
    in_blink = 0xbfcf0bd8;
    func_0xbfc706d4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0bd8);
  if (0 < iVar1) {
    in_blink = 0xbfcf0be0;
    func_0xbfc706d4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0be0);
  if (0 < iVar1) {
    in_blink = 0xbfcf0be8;
    func_0xbfc706d4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0be8);
  if (0 < iVar1) {
    in_blink = 0xbfcf0bf0;
    func_0xbfc706d8();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0bf0);
  if (0 < iVar1) {
    in_blink = 0xbfcf0bf8;
    func_0xbfc706dc();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0bf8);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c00;
    func_0xbfc706e0();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c00);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c08;
    func_0xbfc706e4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c08);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c10;
    func_0xbfc706e8();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c10);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c18;
    func_0xbfc706e4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c18);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c20;
    func_0xbfc706e4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c20);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c28;
    func_0xbfc706e8();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c28);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c30;
    func_0xbfc706ec();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c30);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c38;
    func_0xbfc706f0();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c38);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c40;
    func_0xbfc706f4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c40);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c48;
    func_0xbfc706f8();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c48);
  uVar53 = iVar1 == 0;
  uVar54 = iVar1 < 0;
  if (0 < iVar1) {
    in_blink = 0xbfcf0c50;
    func_0xbfc706f8();
  }
  if (!(bool)uVar54 && !(bool)uVar53) {
    in_blink = 0xbfcf0c58;
    func_0xbfc70c0c();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c58);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c60;
    func_0xbfc706b4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c60);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c68;
    func_0xbfc70670();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c68);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c70;
    func_0xbfc70650();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c70);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c78;
    func_0xbfc70630();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c78);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c80;
    func_0xbfc70634();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c80);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c88;
    func_0xbfc70638();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c88);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c90;
    func_0xbfc7063c();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c90);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c98;
    func_0xbfc70630();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c98);
  if (0 < iVar1) {
    in_blink = 0xbfcf0ca0;
    func_0xbfc7061c();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ca0);
  if (0 < iVar1) {
    in_blink = 0xbfcf0ca8;
    func_0xbfc70574();
  }
  iVar1 = asm_instruction_05(0x1b,in_blink,0xbfcf0ca8);
  if (0 < iVar1) {
    in_blink = 0xbfcf0cb0;
    func_0xbfc70554();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cb0);
  if (0 < iVar1) {
    in_blink = 0xbfcf0cb8;
    func_0xbfc704c0();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cb8);
  if (0 < iVar1) {
    in_blink = 0xbfcf0cc0;
    func_0xbfc704bc();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cc0);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_05(0x1b,in_blink,0xbfcf0cc8);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_05(0x1b,in_blink,0xbfcf0cd0);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cd8);
  if ((0 < iVar1) || (iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ce0), 0 < iVar1)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ce8);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cf0);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cf8);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar2 = asm_instruction_08(0x35,&stack0x00000000,0xbfcf0d00);
  if (0 < iVar2) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar3 = asm_instruction_08(0x35,iVar2,0xbfcf0d08);
  if (0 < iVar3) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar4 = asm_instruction_08(0x35,iVar3,0xbfcf0d10);
  if (0 < iVar4) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  puVar5 = (undefined4 *)asm_instruction_08(0x35,iVar4,0xbfcf0d18);
  if (0 < (int)puVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *puVar5 = 0xbfcf0d20;
  if (0 < (int)puVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined4 *)((int)puVar5 + -0xab) = 0xbfcf0d28;
  if (0 < (int)puVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined4 *)((int)puVar5 + -0x156) = 0xbfcf0d30;
  if (0 < (int)puVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar6 = asm_instruction_08(0x35,(int)puVar5 + -0x201,0xbfcf0d38);
  if (iVar6 < 1) {
    iVar7 = asm_instruction_08(0x35,iVar6,0xbfcf0d40);
    if (0 < iVar7) {
      halt_baddata();
    }
    iVar8 = asm_instruction_08(0x35,iVar7,0xbfcf0d48);
    if (0 < iVar8) {
      halt_baddata();
    }
    iVar9 = asm_instruction_08(0x35,iVar8,0xbfcf0d50);
    if (0 < iVar9) {
      halt_baddata();
    }
    iVar10 = asm_instruction_08(0x35,iVar9,0xbfcf0d58);
    if (0 < iVar10) {
      halt_baddata();
    }
    iVar11 = asm_instruction_08(0x35,iVar10,0xbfcf0d60);
    if (((iVar11 < 1) && (iVar12 = asm_instruction_08(0x35,iVar11,0xbfcf0d68), iVar12 < 1)) &&
       (iVar13 = asm_instruction_08(0x35,iVar12,0xbfcf0d70), iVar13 < 1)) {
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0d78);
      if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar14 = asm_instruction_08(0x35,iVar13,0xbfcf0d80);
      if (0 < iVar14) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar15 = asm_instruction_08(0x35,iVar14,0xbfcf0d88);
      if (0 < iVar15) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar16 = asm_instruction_08(0x35,iVar15,0xbfcf0d90);
      if (((0 < iVar16) || (iVar17 = asm_instruction_08(0x35,iVar16,0xbfcf0d98), 0 < iVar17)) ||
         (iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0da0), 0 < iVar1)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar18 = asm_instruction_08(0x35,iVar17,0xbfcf0da8);
      if (0 < iVar18) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0db0);
      if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar19 = asm_instruction_08(0x35,iVar18,0xbfcf0db8);
      if (0 < iVar19) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar20 = asm_instruction_08(0x35,iVar19,0xbfcf0dc0);
      if (((0 < iVar20) || (iVar21 = asm_instruction_08(0x35,iVar20,0xbfcf0dc8), 0 < iVar21)) ||
         (iVar22 = asm_instruction_08(0x35,iVar21,0xbfcf0dd0), 0 < iVar22)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar23 = asm_instruction_08(0x35,iVar22,0xbfcf0dd8);
      if (0 < iVar23) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar1 = asm_instruction_05(0x1b,in_blink,0xbfcf0de0);
      if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (0 < iVar1) {
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0df0);
      if ((0 < iVar1) || (iVar24 = asm_instruction_08(0x35,iVar23,0xbfcf0df8), 0 < iVar24)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (0 < iVar24) {
        halt_baddata();
      }
      if (0 < iVar24) {
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e10);
      if (0 < iVar1) {
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e18);
      if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar25 = asm_instruction_08(0x35,iVar24,0xbfcf0e20);
      if (0 < iVar25) {
        halt_baddata();
      }
      iVar26 = asm_instruction_08(0x35,iVar25,0xbfcf0e28);
      if (0 < iVar26) {
        halt_baddata();
      }
      iVar27 = asm_instruction_08(0x35,iVar26,0xbfcf0e30);
      if (0 < iVar27) {
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e38);
      if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (0 < iVar1) {
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e48);
      if (0 < iVar1) {
        halt_baddata();
      }
      iVar28 = asm_instruction_08(0x35,iVar27,0xbfcf0e50);
      if (0 < iVar28) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar29 = asm_instruction_08(0x35,iVar28,0xbfcf0e58);
      if (((iVar29 < 1) && (iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e60), iVar1 < 1)) &&
         (iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e68), iVar1 < 1)) {
        iVar30 = asm_instruction_08(0x35,iVar29,0xbfcf0e70);
        if (0 < iVar30) {
          halt_baddata();
        }
        iVar31 = asm_instruction_08(0x35,iVar30,0xbfcf0e78);
        if (iVar31 < 1) {
          iVar32 = asm_instruction_08(0x35,iVar31,0xbfcf0e80);
          if (0 < iVar32) {
            halt_baddata();
          }
          iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e88);
          if (iVar1 < 1) {
            iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e90);
            if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e98);
            if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ea0);
            if ((0 < iVar1) || (iVar33 = asm_instruction_08(0x35,iVar32,0xbfcf0ea8), 0 < iVar33)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            iVar34 = asm_instruction_08(0x35,iVar33,0xbfcf0eb0);
            if (iVar34 < 1) {
              iVar35 = asm_instruction_08(0x35,iVar34,0xbfcf0eb8);
              if (0 < iVar35) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                halt_baddata();
              }
              iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ec0);
              if ((iVar1 < 1) && (iVar36 = asm_instruction_08(0x35,iVar35,0xbfcf0ec8), iVar36 < 1))
              {
                iVar37 = asm_instruction_08(0x35,iVar36,0xbfcf0ed0);
                if (0 < iVar37) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                  halt_baddata();
                }
                iVar38 = asm_instruction_08(0x35,iVar37,0xbfcf0ed8);
                if (0 < iVar38) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                  halt_baddata();
                }
                iVar39 = asm_instruction_08(0x35,iVar38,0xbfcf0ee0);
                if ((0 < iVar39) ||
                   (iVar40 = asm_instruction_08(0x35,iVar39,0xbfcf0ee8), 0 < iVar40)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                  halt_baddata();
                }
                iVar41 = asm_instruction_08(0x35,iVar40,0xbfcf0ef0);
                if (iVar41 < 1) {
                  iVar42 = asm_instruction_08(0x35,iVar41,0xbfcf0ef8);
                  if (0 < iVar42) {
                    halt_baddata();
                  }
                  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f00);
                  if ((iVar1 < 1) &&
                     (iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f08), iVar1 < 1)) {
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f10);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f18);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar43 = asm_instruction_08(0x35,iVar42,0xbfcf0f20);
                    if (0 < iVar43) {
                      halt_baddata();
                    }
                    iVar44 = asm_instruction_08(0x35,iVar43,0xbfcf0f28);
                    if (0 < iVar44) {
                      halt_baddata();
                    }
                    iVar45 = asm_instruction_08(0x35,iVar44,0xbfcf0f30);
                    if (0 < iVar45) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f38);
                    if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f40);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f48);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f50);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f58);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar46 = asm_instruction_08(0x35,iVar45,0xbfcf0f60);
                    if (0 < iVar46) {
                      halt_baddata();
                    }
                    iVar47 = asm_instruction_08(0x35,iVar46,0xbfcf0f68);
                    if (0 < iVar47) {
                      halt_baddata();
                    }
                    iVar48 = asm_instruction_08(0x35,iVar47,0xbfcf0f70);
                    if (0 < iVar48) {
                      halt_baddata();
                    }
                    iVar49 = asm_instruction_08(0x35,iVar48,0xbfcf0f78);
                    if (0 < iVar49) {
                      halt_baddata();
                    }
                    iVar50 = asm_instruction_08(0x35,iVar49,0xbfcf0f80);
                    if (0 < iVar50) {
                      halt_baddata();
                    }
                    iVar51 = asm_instruction_08(0x35,iVar50,0xbfcf0f88);
                    if (iVar51 < 1) {
                      puVar52 = (undefined1 *)asm_instruction_08(0x35,iVar51,0xbfcf0f90);
                      if (0 < (int)puVar52) {
                        halt_baddata();
                      }
                      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f98);
                      while( true ) {
                        if (0 < iVar1) {
                          halt_baddata();
                        }
                        puVar52 = (undefined1 *)asm_instruction_08(0x35,puVar52,0xbfcf0fa0);
                        if (0 < (int)puVar52) break;
                        iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0fa8);
                        if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                          halt_baddata();
                        }
                        iVar1 = asm_instruction_05(0x1b,in_blink,0xbfcf0fb0);
                      }
                    /* WARNING: Bad instruction - Truncating control flow here */
                      halt_baddata();
                    }
                    halt_baddata();
                  }
                }
                    /* WARNING: Bad instruction - Truncating control flow here */
                halt_baddata();
              }
            }
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
        }
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf0fe6) overlaps instruction at (ram,0xbfcf0fe4)
    */
/* WARNING: Removing unreachable block (ram,0xbfcf0fca) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fba) */
/* WARNING: Removing unreachable block (ram,0xbfcf0faa) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fbc) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fbe) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fcc) */
/* WARNING: Removing unreachable block (ram,0xbfcf27ce) */
/* WARNING: Removing unreachable block (ram,0xbfcf27d4) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fd2) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fd4) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fda) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fdc) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fe2) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fe6) */
/* WARNING: Removing unreachable block (ram,0xbfcd07ec) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fe8) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fea) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fec) */
/* WARNING: Removing unreachable block (ram,0xbfcf27ee) */
/* WARNING: Removing unreachable block (ram,0xbfcf0ff0) */
/* WARNING: Removing unreachable block (ram,0xbfcf27d6) */
/* WARNING: Removing unreachable block (ram,0xbfcf27da) */
/* WARNING: Removing unreachable block (ram,0xbfcf27de) */
/* WARNING: Removing unreachable block (ram,0xbfcf27e6) */
/* WARNING: Removing unreachable block (ram,0xbfd3e7f4) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fc2) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fc6) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fc8) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fce) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fd4) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fd8) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fd6) */
/* WARNING: Removing unreachable block (ram,0xbfd09ff0) */
/* WARNING: Removing unreachable block (ram,0xbfd09ff6) */
/* WARNING: Removing unreachable block (ram,0xbfc69040) */
/* WARNING: Removing unreachable block (ram,0xbfc69034) */
/* WARNING: Removing unreachable block (ram,0xbfcf1fc2) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fc8) */
/* WARNING: Removing unreachable block (ram,0xbfcf0fb2) */
/* WARNING: Removing unreachable block (ram,0xbfcf0ff2) */

void FUN_ram_bfcf0c54(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
  int iVar41;
  int iVar42;
  int iVar43;
  int iVar44;
  int iVar45;
  int iVar46;
  int iVar47;
  int iVar48;
  int iVar49;
  int iVar50;
  int iVar51;
  undefined1 *puVar52;
  undefined4 in_ilink1;
  undefined4 in_blink;
  bool in_Z;
  bool in_N;
  
  if (!in_N && !in_Z) {
    in_blink = 0xbfcf0c58;
    func_0xbfc70c0c();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c58);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c60;
    func_0xbfc706b4();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c60);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c68;
    func_0xbfc70670();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c68);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c70;
    func_0xbfc70650();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c70);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c78;
    func_0xbfc70630();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c78);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c80;
    func_0xbfc70634();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c80);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c88;
    func_0xbfc70638();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c88);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c90;
    func_0xbfc7063c();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c90);
  if (0 < iVar1) {
    in_blink = 0xbfcf0c98;
    func_0xbfc70630();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0c98);
  if (0 < iVar1) {
    in_blink = 0xbfcf0ca0;
    func_0xbfc7061c();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ca0);
  if (0 < iVar1) {
    in_blink = 0xbfcf0ca8;
    func_0xbfc70574();
  }
  iVar1 = asm_instruction_05(0x1b,in_blink,0xbfcf0ca8);
  if (0 < iVar1) {
    in_blink = 0xbfcf0cb0;
    func_0xbfc70554();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cb0);
  if (0 < iVar1) {
    in_blink = 0xbfcf0cb8;
    func_0xbfc704c0();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cb8);
  if (0 < iVar1) {
    in_blink = 0xbfcf0cc0;
    func_0xbfc704bc();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cc0);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_05(0x1b,in_blink,0xbfcf0cc8);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_05(0x1b,in_blink,0xbfcf0cd0);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cd8);
  if ((0 < iVar1) || (iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ce0), 0 < iVar1)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ce8);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cf0);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0cf8);
  if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar2 = asm_instruction_08(0x35,&stack0x00000000,0xbfcf0d00);
  if (0 < iVar2) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar3 = asm_instruction_08(0x35,iVar2,0xbfcf0d08);
  if (0 < iVar3) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar4 = asm_instruction_08(0x35,iVar3,0xbfcf0d10);
  if (0 < iVar4) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  puVar5 = (undefined4 *)asm_instruction_08(0x35,iVar4,0xbfcf0d18);
  if (0 < (int)puVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *puVar5 = 0xbfcf0d20;
  if (0 < (int)puVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined4 *)((int)puVar5 + -0xab) = 0xbfcf0d28;
  if (0 < (int)puVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined4 *)((int)puVar5 + -0x156) = 0xbfcf0d30;
  if (0 < (int)puVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar6 = asm_instruction_08(0x35,(int)puVar5 + -0x201,0xbfcf0d38);
  if (iVar6 < 1) {
    iVar7 = asm_instruction_08(0x35,iVar6,0xbfcf0d40);
    if (0 < iVar7) {
      halt_baddata();
    }
    iVar8 = asm_instruction_08(0x35,iVar7,0xbfcf0d48);
    if (0 < iVar8) {
      halt_baddata();
    }
    iVar9 = asm_instruction_08(0x35,iVar8,0xbfcf0d50);
    if (0 < iVar9) {
      halt_baddata();
    }
    iVar10 = asm_instruction_08(0x35,iVar9,0xbfcf0d58);
    if (0 < iVar10) {
      halt_baddata();
    }
    iVar11 = asm_instruction_08(0x35,iVar10,0xbfcf0d60);
    if (((iVar11 < 1) && (iVar12 = asm_instruction_08(0x35,iVar11,0xbfcf0d68), iVar12 < 1)) &&
       (iVar13 = asm_instruction_08(0x35,iVar12,0xbfcf0d70), iVar13 < 1)) {
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0d78);
      if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar14 = asm_instruction_08(0x35,iVar13,0xbfcf0d80);
      if (0 < iVar14) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar15 = asm_instruction_08(0x35,iVar14,0xbfcf0d88);
      if (0 < iVar15) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar16 = asm_instruction_08(0x35,iVar15,0xbfcf0d90);
      if (((0 < iVar16) || (iVar17 = asm_instruction_08(0x35,iVar16,0xbfcf0d98), 0 < iVar17)) ||
         (iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0da0), 0 < iVar1)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar18 = asm_instruction_08(0x35,iVar17,0xbfcf0da8);
      if (0 < iVar18) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0db0);
      if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar19 = asm_instruction_08(0x35,iVar18,0xbfcf0db8);
      if (0 < iVar19) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar20 = asm_instruction_08(0x35,iVar19,0xbfcf0dc0);
      if (((0 < iVar20) || (iVar21 = asm_instruction_08(0x35,iVar20,0xbfcf0dc8), 0 < iVar21)) ||
         (iVar22 = asm_instruction_08(0x35,iVar21,0xbfcf0dd0), 0 < iVar22)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar23 = asm_instruction_08(0x35,iVar22,0xbfcf0dd8);
      if (0 < iVar23) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar1 = asm_instruction_05(0x1b,in_blink,0xbfcf0de0);
      if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (0 < iVar1) {
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0df0);
      if ((0 < iVar1) || (iVar24 = asm_instruction_08(0x35,iVar23,0xbfcf0df8), 0 < iVar24)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (0 < iVar24) {
        halt_baddata();
      }
      if (0 < iVar24) {
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e10);
      if (0 < iVar1) {
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e18);
      if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar25 = asm_instruction_08(0x35,iVar24,0xbfcf0e20);
      if (0 < iVar25) {
        halt_baddata();
      }
      iVar26 = asm_instruction_08(0x35,iVar25,0xbfcf0e28);
      if (0 < iVar26) {
        halt_baddata();
      }
      iVar27 = asm_instruction_08(0x35,iVar26,0xbfcf0e30);
      if (0 < iVar27) {
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e38);
      if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (0 < iVar1) {
        halt_baddata();
      }
      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e48);
      if (0 < iVar1) {
        halt_baddata();
      }
      iVar28 = asm_instruction_08(0x35,iVar27,0xbfcf0e50);
      if (0 < iVar28) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar29 = asm_instruction_08(0x35,iVar28,0xbfcf0e58);
      if (((iVar29 < 1) && (iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e60), iVar1 < 1)) &&
         (iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e68), iVar1 < 1)) {
        iVar30 = asm_instruction_08(0x35,iVar29,0xbfcf0e70);
        if (0 < iVar30) {
          halt_baddata();
        }
        iVar31 = asm_instruction_08(0x35,iVar30,0xbfcf0e78);
        if (iVar31 < 1) {
          iVar32 = asm_instruction_08(0x35,iVar31,0xbfcf0e80);
          if (0 < iVar32) {
            halt_baddata();
          }
          iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e88);
          if (iVar1 < 1) {
            iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e90);
            if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e98);
            if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ea0);
            if ((0 < iVar1) || (iVar33 = asm_instruction_08(0x35,iVar32,0xbfcf0ea8), 0 < iVar33)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            iVar34 = asm_instruction_08(0x35,iVar33,0xbfcf0eb0);
            if (iVar34 < 1) {
              iVar35 = asm_instruction_08(0x35,iVar34,0xbfcf0eb8);
              if (0 < iVar35) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                halt_baddata();
              }
              iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ec0);
              if ((iVar1 < 1) && (iVar36 = asm_instruction_08(0x35,iVar35,0xbfcf0ec8), iVar36 < 1))
              {
                iVar37 = asm_instruction_08(0x35,iVar36,0xbfcf0ed0);
                if (0 < iVar37) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                  halt_baddata();
                }
                iVar38 = asm_instruction_08(0x35,iVar37,0xbfcf0ed8);
                if (0 < iVar38) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                  halt_baddata();
                }
                iVar39 = asm_instruction_08(0x35,iVar38,0xbfcf0ee0);
                if ((0 < iVar39) ||
                   (iVar40 = asm_instruction_08(0x35,iVar39,0xbfcf0ee8), 0 < iVar40)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                  halt_baddata();
                }
                iVar41 = asm_instruction_08(0x35,iVar40,0xbfcf0ef0);
                if (iVar41 < 1) {
                  iVar42 = asm_instruction_08(0x35,iVar41,0xbfcf0ef8);
                  if (0 < iVar42) {
                    halt_baddata();
                  }
                  iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f00);
                  if ((iVar1 < 1) &&
                     (iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f08), iVar1 < 1)) {
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f10);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f18);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar43 = asm_instruction_08(0x35,iVar42,0xbfcf0f20);
                    if (0 < iVar43) {
                      halt_baddata();
                    }
                    iVar44 = asm_instruction_08(0x35,iVar43,0xbfcf0f28);
                    if (0 < iVar44) {
                      halt_baddata();
                    }
                    iVar45 = asm_instruction_08(0x35,iVar44,0xbfcf0f30);
                    if (0 < iVar45) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f38);
                    if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f40);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f48);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f50);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f58);
                    if (0 < iVar1) {
                      halt_baddata();
                    }
                    iVar46 = asm_instruction_08(0x35,iVar45,0xbfcf0f60);
                    if (0 < iVar46) {
                      halt_baddata();
                    }
                    iVar47 = asm_instruction_08(0x35,iVar46,0xbfcf0f68);
                    if (0 < iVar47) {
                      halt_baddata();
                    }
                    iVar48 = asm_instruction_08(0x35,iVar47,0xbfcf0f70);
                    if (0 < iVar48) {
                      halt_baddata();
                    }
                    iVar49 = asm_instruction_08(0x35,iVar48,0xbfcf0f78);
                    if (0 < iVar49) {
                      halt_baddata();
                    }
                    iVar50 = asm_instruction_08(0x35,iVar49,0xbfcf0f80);
                    if (0 < iVar50) {
                      halt_baddata();
                    }
                    iVar51 = asm_instruction_08(0x35,iVar50,0xbfcf0f88);
                    if (iVar51 < 1) {
                      puVar52 = (undefined1 *)asm_instruction_08(0x35,iVar51,0xbfcf0f90);
                      if (0 < (int)puVar52) {
                        halt_baddata();
                      }
                      iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f98);
                      while( true ) {
                        if (0 < iVar1) {
                          halt_baddata();
                        }
                        puVar52 = (undefined1 *)asm_instruction_08(0x35,puVar52,0xbfcf0fa0);
                        if (0 < (int)puVar52) break;
                        iVar1 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0fa8);
                        if (0 < iVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                          halt_baddata();
                        }
                        iVar1 = asm_instruction_05(0x1b,in_blink,0xbfcf0fb0);
                      }
                    /* WARNING: Bad instruction - Truncating control flow here */
                      halt_baddata();
                    }
                    halt_baddata();
                  }
                }
                    /* WARNING: Bad instruction - Truncating control flow here */
                halt_baddata();
              }
            }
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
        }
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf0fe6) overlaps instruction at (ram,0xbfcf0fe4)
    */
/* WARNING: Removing unreachable block (ram,0xbfcf0fb2) */
/* WARNING: Removing unreachable block (ram,0xbfcf0faa) */

void FUN_ram_bfcf0f80(uint param_1,undefined4 param_2,undefined4 param_3,int param_4,
                     undefined4 param_5)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int in_r12;
  int unaff_r13;
  uint unaff_r15;
  undefined1 *unaff_r16;
  int iVar4;
  int unaff_r20;
  undefined4 unaff_r25;
  int unaff_gp;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  undefined4 in_ilink1;
  undefined4 in_ilink2;
  undefined4 in_blink;
  undefined4 in_r48;
  undefined1 uVar8;
  bool in_V;
  
  iVar5 = asm_instruction_08(0x35,&stack0x00000000,0xbfcf0f80);
  if (0 < iVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar6 = asm_instruction_08(0x35,iVar5,0xbfcf0f88);
  if (0 < iVar6) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  puVar7 = (undefined1 *)asm_instruction_08(0x35,iVar6,0xbfcf0f90);
  if (((int)puVar7 < 1) && (iVar4 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f98), iVar4 < 1)) {
    while( true ) {
      puVar7 = (undefined1 *)asm_instruction_08(0x35,puVar7,0xbfcf0fa0);
      if (0 < (int)puVar7) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar4 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0fa8);
      if (0 < iVar4) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar4 = asm_instruction_05(0x1b,in_blink,0xbfcf0fb0);
      uVar8 = iVar4 < 0;
      if (0 < iVar4) break;
      if (unaff_r15 == 0) {
        if (in_V != (bool)uVar8) {
          if ((bool)uVar8) {
            func_0xbfccd3bc();
          }
LAB_ram_bfcf1fc2:
          *(short *)(in_r12 + 4) = (short)param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        cVar1 = ext_condition(0x1b);
        if (cVar1 != '\0') {
          if (unaff_r13 != 0) {
            *unaff_r16 = (char)unaff_r20;
            if (unaff_r13 != 0) {
              *(short *)(unaff_r16 + 0x50) = (short)unaff_r20;
              uVar2 = (uint)*(ushort *)(unaff_gp + 0x154);
              cVar1 = ext_condition(0x10);
              if (cVar1 != '\0') {
                uVar2 = func_0xbfd1b3d4(uVar2);
              }
              asm_instruction_06(0x20,uVar2,3);
              *(short *)(in_r12 + 8) = (short)param_4;
              FUN_ram_bfd09fe4();
              return;
            }
            asm_instruction_05(0xd,in_ilink2,1);
            uVar3 = asm_instruction_08(0x12,param_1,param_1);
            asm_instruction_08(0x10,uVar3,uVar3);
            if (in_V == false) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            if (in_V == false) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            asm_instruction_07(0x1a,in_r12,unaff_r20 + 0x90);
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
          goto LAB_ram_bfcf1fc2;
        }
        cVar1 = ext_condition(0x15);
        if (cVar1 == '\0') {
          cVar1 = ext_condition(0x16);
          if (cVar1 == '\0') {
            cVar1 = ext_condition(0x17);
            if (cVar1 == '\0') {
              if ((in_V == false) && (cVar1 = ext_condition(0x15), cVar1 != '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                halt_baddata();
              }
              if (iVar4 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                halt_baddata();
              }
              *(short *)(in_r12 + 0xc) = (short)unaff_r13;
              asm_instruction_08(0x23,unaff_r25,0x47f);
              FUN_ram_bfd0affa();
              return;
            }
            goto LAB_ram_bfcf27de;
          }
          *(short *)(param_4 + 2) = (short)in_r12;
        }
        else {
          asm_instruction_07(0x1d,param_5,in_r48);
          param_1 = (uint)*(ushort *)(unaff_gp + -0xb4);
          *(short *)(param_4 + 2) = (short)in_r12;
          if (!in_V) {
            param_1 = func_0xbfde23d4(param_1);
          }
        }
        cVar1 = ext_condition(0x1d);
        if (cVar1 != '\0') {
          param_1 = func_0xbfd22bd8();
        }
LAB_ram_bfcf27de:
        asm_instruction_06(0x3c,param_1,0x16);
        if ((bool)uVar8) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      unaff_r15 = unaff_r15 & 0x3ffff;
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Instruction at (ram,0xbfcf10f6) overlaps instruction at (ram,0xbfcf10f4)
    */
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcf28e6) */
/* WARNING: Removing unreachable block (ram,0xbfc87154) */
/* WARNING: Removing unreachable block (ram,0xbfcf28ee) */
/* WARNING: Removing unreachable block (ram,0xbfcf28f2) */
/* WARNING: Removing unreachable block (ram,0xbfd1c218) */
/* WARNING: Removing unreachable block (ram,0xbfcf2906) */
/* WARNING: Removing unreachable block (ram,0xbfcc691c) */

void FUN_ram_bfcf10bc(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  int unaff_r13;
  undefined1 unaff_r15;
  undefined4 unaff_r17;
  undefined4 unaff_r21;
  undefined4 unaff_gp;
  int iVar4;
  int iVar5;
  undefined4 in_r53;
  bool bVar6;
  bool bVar7;
  bool in_V;
  
  cVar1 = ext_condition(0x13);
  iVar4 = asm_instruction_06(0x2b,unaff_gp,0xbfcf10c0);
  if (cVar1 != '\0') {
    if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_05(0x21,unaff_r21,in_r53);
    asm_instruction_08(0x22,unaff_r17,0x3c0);
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
      func_0xbfd1acf8(*(undefined2 *)(iVar4 + 0x2e));
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar5 = asm_instruction_06(0x2b,iVar4,0xbfcf10c8);
  bVar6 = iVar5 == 0;
  bVar7 = iVar5 < 0;
  if ((in_V == iVar4 < 0) && (in_V != bVar7)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  while( true ) {
    bVar2 = !bVar7;
    bVar3 = !bVar6;
    iVar4 = asm_instruction_06(0x2b,iVar5,0xbfcf10d0);
    bVar6 = iVar4 == 0;
    bVar7 = iVar4 < 0;
    if (bVar2 && bVar3) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x10);
    *(undefined1 *)(param_1 + 1) = unaff_r15;
    if ((cVar1 != '\0') && (bVar6)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (!bVar6) {
      *(int *)(param_1 + 0x3c) = param_1;
      cVar1 = ext_condition(0x1c);
      if (cVar1 != '\0') {
        func_0xbfd21ce0(*(undefined2 *)(iVar4 + 0xec));
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(undefined1 *)(param_1 + 1) = unaff_r15;
    *(undefined1 *)(param_1 + 1) = unaff_r15;
    *(undefined1 *)(param_1 + 1) = unaff_r15;
    if (in_V) break;
    if (param_3 == 0) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
    iVar5 = 0;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf1394(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  char cVar1;
  char cVar2;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  uint unaff_r15;
  undefined4 unaff_r22;
  undefined4 in_ilink2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r56;
  undefined1 uVar6;
  char cVar7;
  char in_V;
  
  while (!(bool)in_V) {
    uVar3 = asm_instruction_07(0x3b,in_ilink2,0xbfcf1398);
    cVar1 = ext_condition(0x15);
    iVar4 = asm_instruction_07(0x3b,uVar3,0xbfcf13a0);
    if (cVar1 != '\0') goto LAB_ram_bfcf239e;
    cVar1 = ext_condition(0x1e);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar3 = asm_instruction_07(0x3b,iVar4,0xbfcf13a8);
    cVar1 = ext_condition(0x1f);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar4 = asm_instruction_07(0x3b,uVar3,0xbfcf13b0);
    iVar5 = asm_instruction_07(0x3b,iVar4,0xbfcf13b8);
    if (-1 < iVar4) {
      halt_baddata();
    }
    if (unaff_r14 != 0) {
      if (iVar5 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (iVar5 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_06(0x35,&stack0x00000000,0xbfcf13c8);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1b);
    unaff_r15 = unaff_r15 & 0xffff;
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x11);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar3 = asm_instruction_07(0x3b,iVar5,0xbfcf1378);
    cVar1 = ext_condition(0x12);
    if (cVar1 != '\0') {
      if (unaff_r13 == 0) {
        asm_instruction_06(0x20,in_r56,0x3e);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      uVar3 = func_0xbfcf0d08();
      asm_instruction_06(0x20,uVar3,4);
      *(undefined2 *)(in_r12 + 8) = param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar3 = asm_instruction_07(0x3b,uVar3,0xbfcf1380);
    cVar1 = ext_condition(0x1a);
    if (cVar1 != '\0') {
      halt_baddata();
    }
    uVar3 = asm_instruction_07(0x3b,uVar3,0xbfcf1388);
    cVar1 = ext_condition(0x14);
    in_ilink2 = asm_instruction_07(0x3b,uVar3,0xbfcf1390);
    if (cVar1 != '\0') {
      cVar1 = ext_condition(0x18);
      if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
  }
  param_1 = asm_instruction_08(0x22,param_1,unaff_r15);
  iVar4 = asm_instruction_06(0x1c,param_1,0x16);
LAB_ram_bfcf239e:
  cVar7 = iVar4 < 0;
  uVar6 = iVar4 == 0;
  cVar1 = ext_condition(0x10);
  cVar2 = ext_condition(0x10);
  if ((cVar2 != '\0') && (param_1 = func_0xbfd22cd8(), cVar1 != '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x13);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!(bool)uVar6 && in_V == cVar7) {
    *(undefined4 *)param_1 = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0x3c,param_3,unaff_r22);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf1520(void)

{
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf1708(void)

{
  undefined4 unaff_r16;
  undefined4 unaff_r20;
  
  asm_instruction_05(0xd,unaff_r20,unaff_r16);
  asm_instruction_08(3,&stack0x00000000,1);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf1710(void)

{
  asm_instruction_08(3,&stack0x00000000,1);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



void FUN_ram_bfcf1788(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int in_r12;
  
  uVar1 = asm_instruction_06(0,param_1,2);
  FUN_ram_bfd09796(param_1,param_2,*(undefined2 *)(in_r12 + 0x22),uVar1);
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf19f4(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf1d54(void)

{
  undefined4 unaff_r22;
  
  asm_instruction_05(0xd,unaff_r22,0x34);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf1da8(undefined4 param_1)

{
  int unaff_r13;
  undefined4 *unaff_r16;
  undefined4 unaff_r20;
  int unaff_gp;
  char in_Z;
  
  asm_instruction_08(0x22,param_1,0xfffffbc1);
  *unaff_r16 = unaff_r20;
  do {
  } while (unaff_r13 == 0);
  if (in_Z != '\0') {
    *(uint *)(*(ushort *)(unaff_gp + -0x9a) + 0x3c) = (uint)*(ushort *)(unaff_gp + -0x9a);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



void FUN_ram_bfcf2178(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int in_r12;
  undefined4 unaff_r25;
  
  asm_instruction_08(0x23,unaff_r25,0x4bf);
  *(undefined2 *)(in_r12 + 6) = param_3;
  FUN_ram_bfd0a698();
  return;
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcf227c) */

void FUN_ram_bfcf223c(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5,
                     undefined4 param_6)

{
  char cVar1;
  undefined4 extraout_r1;
  undefined2 in_r12;
  int unaff_r14;
  undefined4 unaff_r22;
  undefined4 in_r24;
  undefined4 unaff_r25;
  undefined4 uVar2;
  undefined4 uVar3;
  uint unaff_fp;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 in_ilink1;
  undefined4 in_blink;
  undefined4 in_r52;
  undefined4 in_mmid;
  undefined8 uVar7;
  
  asm_instruction_04(0x31,unaff_fp,0xbfcf2240);
  uVar4 = unaff_fp | 0x3ff;
  iVar5 = asm_instruction_04(0x27,&stack0x00000000,0x3ff);
  if (0 < iVar5) {
    uVar4 = uVar4 ^ 0xbfcf2254;
  }
  uVar6 = asm_instruction_04(0x27,iVar5,0x3ff);
  asm_instruction_04(0x3d,uVar6,0x3ff);
  asm_instruction_04(0x2b,in_blink,0xbfcf2264);
  asm_instruction_05(0x27,uVar4,0xbfcf226c);
  asm_instruction_05(0x31,in_r24,0x3f);
  uVar2 = asm_instruction_05(0x37,unaff_r25,0x3ff);
  uVar2 = asm_instruction_05(0x3b,uVar2,0x3ff);
  *(undefined2 *)(param_4 + 2) = in_r12;
  if (uVar4 != 0xbfcf227c) {
    FUN_ram_bfd0ee84();
  }
  uVar3 = asm_instruction_08(0x22,uVar2,0x4bf);
  uVar7 = FUN_ram_bfcf1394();
  uVar2 = (undefined4)((ulonglong)uVar7 >> 0x20);
  if (unaff_r14 != 0) {
    *(undefined4 *)(param_3 + -0x390) = unaff_r22;
    asm_instruction_08(0x30,uVar3,0x4bf);
    asm_instruction_06(0x10,in_mmid,param_5);
    cVar1 = ext_condition(0x1a);
    if (cVar1 != '\0') {
      func_0xbfd8ab28();
      uVar2 = extraout_r1;
    }
    asm_instruction_05(0x2d,in_ilink1,uVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0x21,param_6,in_r52);
  asm_instruction_08(0x27,uVar3,0x4bf);
  *(char *)(param_5 + 0x70) = (char)uVar7;
  asm_instruction_08(3,(int)uVar7,0);
  FUN_ram_bfd122f2();
  return;
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcf227c) */

void FUN_ram_bfcf2264(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5,
                     undefined4 param_6)

{
  char cVar1;
  undefined4 extraout_r1;
  undefined2 in_r12;
  int unaff_r14;
  undefined4 unaff_r22;
  undefined4 in_r24;
  undefined4 unaff_r25;
  undefined4 uVar2;
  undefined4 uVar3;
  int unaff_fp;
  undefined4 in_ilink1;
  undefined4 in_blink;
  undefined4 in_r52;
  undefined4 in_mmid;
  undefined8 uVar4;
  
  asm_instruction_04(0x2b,in_blink,0xbfcf2264);
  asm_instruction_05(0x27,unaff_fp,0xbfcf226c);
  asm_instruction_05(0x31,in_r24,0x3f);
  uVar2 = asm_instruction_05(0x37,unaff_r25,0x3ff);
  uVar2 = asm_instruction_05(0x3b,uVar2,0x3ff);
  *(undefined2 *)(param_4 + 2) = in_r12;
  if (unaff_fp != -0x4030dd84) {
    FUN_ram_bfd0ee84();
  }
  uVar3 = asm_instruction_08(0x22,uVar2,0x4bf);
  uVar4 = FUN_ram_bfcf1394();
  uVar2 = (undefined4)((ulonglong)uVar4 >> 0x20);
  if (unaff_r14 != 0) {
    *(undefined4 *)(param_3 + -0x390) = unaff_r22;
    asm_instruction_08(0x30,uVar3,0x4bf);
    asm_instruction_06(0x10,in_mmid,param_5);
    cVar1 = ext_condition(0x1a);
    if (cVar1 != '\0') {
      func_0xbfd8ab28();
      uVar2 = extraout_r1;
    }
    asm_instruction_05(0x2d,in_ilink1,uVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0x21,param_6,in_r52);
  asm_instruction_08(0x27,uVar3,0x4bf);
  *(char *)(param_5 + 0x70) = (char)uVar4;
  asm_instruction_08(3,(int)uVar4,0);
  FUN_ram_bfd122f2();
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf228c(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                     int param_5,undefined4 param_6)

{
  char cVar1;
  undefined4 extraout_r1;
  undefined4 uVar2;
  int unaff_r14;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  undefined4 in_ilink1;
  undefined4 in_r52;
  undefined4 in_mmid;
  undefined8 uVar3;
  
  uVar3 = FUN_ram_bfcf1394();
  uVar2 = (undefined4)((ulonglong)uVar3 >> 0x20);
  if (unaff_r14 == 0) {
    asm_instruction_05(0x21,param_6,in_r52);
    asm_instruction_08(0x27,unaff_r25,0x4bf);
    *(char *)(param_5 + 0x70) = (char)uVar3;
    asm_instruction_08(3,(int)uVar3,0);
    FUN_ram_bfd122f2();
    return;
  }
  *(undefined4 *)(param_3 + -0x390) = unaff_r22;
  asm_instruction_08(0x30,unaff_r25,0x4bf);
  asm_instruction_06(0x10,in_mmid,param_5);
  cVar1 = ext_condition(0x1a);
  if (cVar1 != '\0') {
    func_0xbfd8ab28();
    uVar2 = extraout_r1;
  }
  asm_instruction_05(0x2d,in_ilink1,uVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



void FUN_ram_bfcf22b4(undefined4 param_1,int param_2)

{
  FUN_ram_bfcf1400(param_1,param_2,(int)*(short *)(param_2 + 0x20));
  FUN_ram_bfd062b8();
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf22c8(void)

{
  char cVar1;
  undefined4 in_r4;
  undefined4 in_r48;
  int iVar2;
  undefined4 in_mlo;
  undefined1 uVar3;
  char cVar4;
  char in_V;
  
  iVar2 = asm_instruction_06(0x27,in_r48,in_mlo);
  uVar3 = iVar2 == 0;
  cVar4 = iVar2 < 0;
  func_0xbeee20ec();
  FUN_ram_bfcf1520();
  cVar1 = ext_condition(0x11);
  if (!(bool)uVar3 && in_V == cVar4) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 == '\0') {
    asm_instruction_06(0x1c,in_r4,0xc);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf230a) overlaps instruction at (ram,0xbfcf2308)
    */

void FUN_ram_bfcf2304(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
                     int param_5)

{
  char cVar1;
  undefined4 uVar2;
  int in_r12;
  int unaff_r13;
  int iVar3;
  
  iVar3 = *(int *)(unaff_r13 + 0x20);
  if (iVar3 != 0) {
    in_r12 = *(int *)(iVar3 + 0x60);
  }
  asm_instruction_06(0x1c,param_1,0x16);
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    cVar1 = ext_condition(0x10);
    if (cVar1 == '\0') {
      uVar2 = *(undefined4 *)(param_5 + 0x72);
      if (iVar3 != 0) {
        *(undefined2 *)(in_r12 + 6) = param_3;
      }
      FUN_ram_bfd0a720(param_1,uVar2);
      return;
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf2700(void)

{
  undefined4 in_r39;
  
  asm_instruction_05(0x24,in_r39,3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf2728(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  undefined2 in_r12;
  undefined4 in_ilink2;
  undefined4 in_r39;
  bool in_Z;
  bool in_C;
  
  uVar1 = (uint)*(ushort *)(param_1 + 4);
  if (!in_C && !in_Z) {
    *(undefined2 *)(param_4 + 2) = in_r12;
    *(uint *)(uVar1 + 0x74) = uVar1;
    asm_instruction_04(0x24,in_ilink2,param_2);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_07(0x1d,uVar1,0);
  asm_instruction_05(0x24,in_r39,3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf2798(void)

{
  undefined4 in_r5;
  undefined4 in_r52;
  
  asm_instruction_05(0x24,in_r5,in_r52);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf2ab8(undefined4 param_1,int param_2,int param_3)

{
  char cVar1;
  undefined2 unaff_r13;
  int unaff_r14;
  undefined4 unaff_r17;
  undefined4 in_r48;
  char in_Z;
  bool in_C;
  bool in_V;
  
  *(undefined2 *)(param_3 + 0x12) = unaff_r13;
  if (unaff_r14 == 0) {
    *(undefined2 *)(param_2 + 0x1e) = 0;
    if (!in_V) {
      param_1 = func_0xbfce26c4();
    }
    asm_instruction_06(0x11,in_r48,0x339);
    func_0xc08c5ed0(param_1);
    asm_instruction_08(0x22,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x22,param_1,param_1);
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!in_C) {
    cVar1 = ext_condition(0x18);
    if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcf2a70) */

void FUN_ram_bfcf2ac4(void)

{
  char cVar1;
  int unaff_r14;
  char in_Z;
  bool in_C;
  
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x18);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf2b24(undefined4 param_1)

{
  char cVar1;
  int unaff_r13;
  int iVar2;
  undefined4 unaff_r22;
  int unaff_gp;
  
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    param_1 = func_0xbfd5b724();
  }
  iVar2 = *(int *)(unaff_r13 + 0x20);
  asm_instruction_08(0x22,param_1,0xc1);
  *(undefined4 *)(*(ushort *)(unaff_gp + 0x84) - 0x390) = unaff_r22;
  do {
  } while (iVar2 != 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf2b58(undefined4 param_1,undefined4 param_2)

{
  asm_instruction_06(0x3d,param_2,param_1);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf2c38(void)

{
  undefined2 in_r3;
  int in_r12;
  int unaff_r13;
  
  FUN_ram_bfcf1da8();
  if (unaff_r13 == 0) {
    *(undefined2 *)(in_r12 + 4) = in_r3;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf2edc(void)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_r13;
  int unaff_gp;
  undefined1 in_Z;
  char in_N;
  char in_V;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar2 = FUN_ram_bfcf30d0(*(undefined2 *)(unaff_gp + 0xce));
  uVar2 = func_0xbfcf2054(uVar2,*(undefined4 *)(unaff_r13 + 0x20));
  FUN_ram_bfcf30dc(uVar2,*(undefined4 *)(unaff_r13 + 0x20));
  if (!(bool)in_Z && in_V == in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf3010(void)

{
  char cVar1;
  
  cVar1 = ext_condition(0x1c);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf308c(void)

{
  int in_r12;
  undefined4 unaff_r13;
  undefined4 unaff_r22;
  int unaff_gp;
  undefined4 in_r37;
  
  func_0xbfd0ab08(*(undefined2 *)(in_r12 + 6));
  FUN_ram_bfd0bb10(unaff_gp + -0x80,unaff_r13,*(undefined4 *)(in_r12 + 0x40));
  asm_instruction_08(0x24,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf30d0(void)

{
  int unaff_gp;
  
  FUN_ram_bfcf22c8(*(undefined2 *)(unaff_gp + 0x1d4));
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf30dc(void)

{
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf3320(void)

{
  uint uVar1;
  int unaff_r13;
  undefined2 unaff_r22;
  int unaff_gp;
  
  uVar1 = (uint)*(ushort *)(unaff_gp + 0x1b4);
  *(uint *)uVar1 = uVar1;
  do {
  } while (unaff_r13 == 0);
  *(undefined2 *)(uVar1 - 0x27) = unaff_r22;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf35d4(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined2 *in_r12;
  uint unaff_r13;
  undefined1 in_Z;
  undefined1 in_C;
  undefined8 uVar1;
  
  *(char *)(unaff_r13 + 9) = (char)in_r12;
  uVar1 = func_0xc0600bd4();
  if (!(bool)in_C && !(bool)in_Z) {
    asm_instruction_06(0,(int)uVar1,param_3);
    FUN_ram_bfd0ba6a(*in_r12,(uint)((ulonglong)uVar1 >> 0x20) & ~unaff_r13);
    return;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf3610(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  undefined2 in_r12;
  bool in_Z;
  bool in_C;
  
  uVar1 = asm_instruction_08(0x24,param_1,param_1);
  if (!in_C && !in_Z) {
    *(undefined2 *)(param_3 + 0x22) = in_r12;
    asm_instruction_06(0x20,uVar1,0x609);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfd0ba6a(uVar1);
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf36d0(undefined4 param_1)

{
  undefined4 in_r54;
  
  asm_instruction_08(0,param_1,in_r54);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf36fc(undefined2 param_1)

{
  int in_r12;
  
  *(undefined2 *)(in_r12 + 6) = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf3774(undefined2 param_1)

{
  int in_r12;
  int unaff_r14;
  
  if (unaff_r14 == 0) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  *(undefined2 *)(in_r12 + 6) = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf391c) overlaps instruction at (ram,0xbfcf391a)
    */

void FUN_ram_bfcf390c(undefined2 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int in_r7;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  uint uVar7;
  int unaff_r15;
  undefined4 unaff_r16;
  undefined4 unaff_r21;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_ilink1;
  undefined4 in_r48;
  undefined2 *puVar8;
  undefined2 in_mlo;
  undefined4 in_lp_count;
  char cVar9;
  undefined1 uVar10;
  bool bVar11;
  undefined1 in_C;
  char in_V;
  undefined8 uVar12;
  
  puVar8 = (undefined2 *)asm_instruction_06(0x11,in_r48,0x13b);
  cVar9 = puVar8 == (undefined2 *)0x0;
  bVar11 = (int)puVar8 < 0;
  if (unaff_r14 != 0) {
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
      param_1 = func_0xbfcec57c();
    }
    *(undefined2 *)(in_r12 + 4) = param_1;
    if (cVar9 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar3 = (uint)*(ushort *)(unaff_gp + 0x24);
  uVar7 = 0;
  iVar5 = unaff_r15;
  if (unaff_r15 == 0) goto LAB_ram_bfcf393a;
  puVar8 = (undefined2 *)((int)puVar8 + -0xad);
  *puVar8 = in_mlo;
  if ((bool)in_V == bVar11) {
    uVar12 = func_0xbfcced58();
    param_2 = (undefined4)((ulonglong)uVar12 >> 0x20);
    uVar3 = (uint)uVar12;
  }
  do {
    cVar9 = ext_condition(0x10);
    if (cVar9 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar5 = unaff_r15 + 1;
    cVar9 = ext_condition(0x10);
    if (cVar9 != '\0') {
      asm_instruction_08(0x23,param_2,1);
      asm_instruction_08(0x1c,in_lp_count,0x21);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(short *)(in_r12 + 4) = (short)param_4;
    uVar12 = FUN_ram_bfcf390c(uVar3,unaff_r13);
    uVar7 = (uint)*(byte *)(iVar5 + 1);
    do {
      uVar3 = (uint)uVar12;
      puVar8 = (undefined2 *)asm_instruction_06(0x11,puVar8,0x13b);
      uVar10 = puVar8 == (undefined2 *)0x0;
      if (uVar7 != 0) {
        *(short *)(uVar7 + 0x20) = (short)uVar7;
        cVar9 = ext_condition(0x1c);
        if (cVar9 != '\0') {
          uVar3 = func_0xbfcec5a4();
        }
        *(short *)(in_r12 + 4) = (short)uVar3;
        cVar9 = ext_condition(0x1c);
        if (cVar9 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        asm_instruction_08(0x24,unaff_r25,0x4bf);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar5 = in_r7;
      if (unaff_r15 != 0) {
LAB_ram_bfcf393a:
        if (!(bool)in_V) {
          uVar3 = func_0xbfce353c(uVar3,*(undefined2 *)(uVar7 + 0xc));
        }
        iVar4 = asm_instruction_06(0x1c,uVar3,0xffffff15);
        uVar10 = iVar4 == 0;
        uVar12 = FUN_ram_bfcf2ab8(*(undefined2 *)(unaff_gp + 0x184));
        unaff_r15 = iVar5;
      }
      param_2 = (undefined4)((ulonglong)uVar12 >> 0x20);
      uVar3 = (uint)uVar12;
      param_4 = *(undefined4 *)(unaff_r13 + 0x60);
      if (!(bool)in_C && !(bool)uVar10) {
        asm_instruction_06(0x20,uVar3,0xfffffd07);
        cVar9 = ext_condition(0x1c);
        if (cVar9 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        uVar6 = asm_instruction_05(0x21,in_ilink1,unaff_r16);
        cVar9 = ext_condition(0x1c);
        if (cVar9 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        do {
        } while (*(byte *)(uVar3 + 0x1a) == 0);
        iVar5 = FUN_ram_bfcf2b58(*(undefined2 *)(in_r12 + 4),param_2,uVar6,
                                 *(undefined4 *)(*(byte *)(uVar3 + 0x1a) + 0x30));
        iVar4 = asm_instruction_06(0x11,puVar8,0x13b);
        if (uVar7 == 0) {
          *(short *)(in_r12 + 6) = (short)uVar6;
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        *(undefined4 *)(iVar5 + -0x290) = unaff_r21;
        if (0 < iVar4) {
          iVar5 = func_0xbfc8c228();
        }
        uVar2 = (undefined2)iVar5;
        if ((bool)in_C) {
          uVar2 = func_0xbfd54e24();
        }
        iVar5 = asm_instruction_06(0x23,iVar4,0x39);
        if (uVar7 == 0) {
          *(undefined2 *)(iVar5 + 4) = uVar2;
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    } while (unaff_r13 != 0);
  } while( true );
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf3a1c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 uVar1;
  int iVar2;
  int in_r12;
  int unaff_r13;
  undefined4 unaff_r21;
  int unaff_gp;
  undefined4 in_r48;
  undefined4 uVar3;
  undefined1 in_Z;
  char in_N;
  undefined1 in_C;
  undefined1 in_V;
  
  if (unaff_r13 != 0) {
    *(short *)(in_r12 + 6) = (short)param_3;
    FUN_ram_bfd0c26e();
    return;
  }
  FUN_ram_bfcf43cc();
  iVar2 = FUN_ram_bfcf3ad0();
  uVar1 = uRam00000008;
  if (!(bool)in_Z && in_V == in_N) {
    *(undefined4 *)(iVar2 + -0x210) = unaff_r21;
    if (!(bool)in_Z && in_V == in_N) {
      *(undefined4 *)(*(ushort *)(unaff_gp + 0x50) - 0x210) = unaff_r21;
      if ((bool)in_C) {
        func_0xbfd76ebc();
      }
      uVar3 = asm_instruction_06(0x25,in_r48,0xfffffd07);
      asm_instruction_06(4,uVar3,0x339);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(undefined4 *)(iVar2 + 0x40) = param_3;
    if (!(bool)in_V) {
      func_0xbfd046e0(iVar2,uVar1);
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf3ad0(void)

{
  int unaff_r13;
  
  do {
  } while (unaff_r13 != 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf4330(void)

{
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf43cc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf4484) overlaps instruction at (ram,0xbfcf4482)
    */
/* WARNING: Removing unreachable block (ram,0xbfd10cba) */
/* WARNING: Removing unreachable block (ram,0xbfcf446e) */
/* WARNING: Removing unreachable block (ram,0xbfcf4476) */

void FUN_ram_bfcf4408(undefined4 param_1,uint param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  uint uVar2;
  uint in_r7;
  uint unaff_r13;
  int iVar3;
  int iVar4;
  uint unaff_r15;
  undefined1 *unaff_r16;
  undefined4 unaff_r17;
  undefined1 unaff_r20;
  int unaff_r21;
  undefined4 unaff_r25;
  undefined4 uVar5;
  int unaff_gp;
  undefined4 in_r48;
  int iVar6;
  undefined4 in_r50;
  undefined4 in_r52;
  undefined4 in_r56;
  int in_mmid;
  undefined4 in_lp_count;
  undefined1 in_V;
  undefined8 uVar7;
  
  iVar4 = *(int *)(param_4 + 0x78);
  asm_instruction_07(0x1c,(uint)*(ushort *)(unaff_gp + -0x30),unaff_r15);
  if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *unaff_r16 = unaff_r20;
  unaff_r16[0x50] = unaff_r20;
  uVar2 = (uint)*(ushort *)(unaff_gp + -0x40);
  cVar1 = ext_condition(0x11);
  if (cVar1 != '\0') {
    uVar7 = func_0xbfd7781c();
    param_2 = (uint)((ulonglong)uVar7 >> 0x20);
    uVar2 = (uint)uVar7;
  }
  iVar6 = asm_instruction_06(0x11,in_r48,0x334);
  uVar7 = CONCAT44(param_2 & ~unaff_r13,uVar2);
  if (!(bool)in_V) {
    uVar7 = func_0xbfde40c4();
  }
  if ((unaff_r15 & 0x7ffff) == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar3 = asm_instruction_05(0x2d,unaff_r21,in_r52);
  asm_instruction_06(0x30,unaff_r16 + 0x60,0x4d4);
  if (iVar4 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (iVar3 == 0) {
    uVar2 = unaff_r21 + iVar6 * 4;
    uVar5 = asm_instruction_08(0x31,unaff_r25,0x4bf);
    *(undefined2 *)(in_mmid + -0x1de) = *(undefined2 *)(iVar3 + 0x20);
    asm_instruction_08(0x32,uVar5,0x4bf);
    uVar5 = asm_instruction_06(0x12,in_r56,0x74c);
    if (!(bool)in_V) {
      func_0xbfde4130((int)uVar7,(uint)((ulonglong)uVar7 >> 0x20) & ~uVar2);
    }
    if ((in_r7 & 0x7ffff) == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    do {
    } while (uVar2 == 0);
    asm_instruction_06(0x32,uVar5,0xc);
    asm_instruction_08(0x24,unaff_r17,0x3c0);
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_07(0x1d,in_r52,in_lp_count);
  asm_instruction_07(0x24,param_4,in_r50);
  cVar1 = ext_condition(0x14);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf4484) overlaps instruction at (ram,0xbfcf4482)
    */
/* WARNING: Removing unreachable block (ram,0xbfd10cba) */
/* WARNING: Removing unreachable block (ram,0xbfcf446e) */
/* WARNING: Removing unreachable block (ram,0xbfcf4476) */

void FUN_ram_bfcf4410(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  uint in_r7;
  uint unaff_r13;
  int iVar3;
  int unaff_r14;
  uint unaff_r15;
  undefined1 *unaff_r16;
  undefined4 unaff_r17;
  undefined1 unaff_r20;
  int unaff_r21;
  undefined4 unaff_r25;
  undefined4 uVar4;
  int unaff_gp;
  undefined4 in_r48;
  int iVar5;
  undefined4 in_r50;
  undefined4 in_r52;
  undefined4 in_r56;
  int in_mmid;
  undefined4 in_lp_count;
  undefined1 in_V;
  undefined8 uVar6;
  
  if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *unaff_r16 = unaff_r20;
  unaff_r16[0x50] = unaff_r20;
  uVar2 = (uint)*(ushort *)(unaff_gp + -0x40);
  cVar1 = ext_condition(0x11);
  if (cVar1 != '\0') {
    uVar6 = func_0xbfd7781c();
    param_2 = (uint)((ulonglong)uVar6 >> 0x20);
    uVar2 = (uint)uVar6;
  }
  iVar5 = asm_instruction_06(0x11,in_r48,0x334);
  uVar6 = CONCAT44(param_2 & ~unaff_r13,uVar2);
  if (!(bool)in_V) {
    uVar6 = func_0xbfde40c4();
  }
  if ((unaff_r15 & 0x7ffff) == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar3 = asm_instruction_05(0x2d,unaff_r21,in_r52);
  asm_instruction_06(0x30,unaff_r16 + 0x60,0x4d4);
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (iVar3 == 0) {
    uVar2 = unaff_r21 + iVar5 * 4;
    uVar4 = asm_instruction_08(0x31,unaff_r25,0x4bf);
    *(undefined2 *)(in_mmid + -0x1de) = *(undefined2 *)(iVar3 + 0x20);
    asm_instruction_08(0x32,uVar4,0x4bf);
    uVar4 = asm_instruction_06(0x12,in_r56,0x74c);
    if (!(bool)in_V) {
      func_0xbfde4130((int)uVar6,(uint)((ulonglong)uVar6 >> 0x20) & ~uVar2);
    }
    if ((in_r7 & 0x7ffff) == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    do {
    } while (uVar2 == 0);
    asm_instruction_06(0x32,uVar4,0xc);
    asm_instruction_08(0x24,unaff_r17,0x3c0);
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_07(0x1d,in_r52,in_lp_count);
  asm_instruction_07(0x24,param_4,in_r50);
  cVar1 = ext_condition(0x14);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf4484) overlaps instruction at (ram,0xbfcf4482)
    */
/* WARNING: Removing unreachable block (ram,0xbfd10cba) */
/* WARNING: Removing unreachable block (ram,0xbfcf446e) */
/* WARNING: Removing unreachable block (ram,0xbfcf4476) */

void FUN_ram_bfcf4420(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint in_r7;
  uint unaff_r13;
  int iVar2;
  uint uVar3;
  int unaff_r14;
  uint unaff_r15;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  int unaff_r21;
  undefined4 unaff_r25;
  undefined4 uVar4;
  undefined4 in_r48;
  int iVar5;
  undefined4 in_r50;
  undefined4 in_r52;
  undefined4 in_r56;
  int in_mmid;
  undefined4 in_lp_count;
  undefined1 in_V;
  undefined8 uVar6;
  
  iVar5 = asm_instruction_06(0x11,in_r48,0x334);
  param_2 = param_2 & ~unaff_r13;
  if (!(bool)in_V) {
    uVar6 = func_0xbfde40c4();
    param_2 = (uint)((ulonglong)uVar6 >> 0x20);
    param_1 = (undefined4)uVar6;
  }
  if ((unaff_r15 & 0x7ffff) == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar2 = asm_instruction_05(0x2d,unaff_r21,in_r52);
  asm_instruction_06(0x30,unaff_r16,0x4d4);
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (iVar2 != 0) {
    asm_instruction_07(0x1d,in_r52,in_lp_count);
    asm_instruction_07(0x24,param_4,in_r50);
    cVar1 = ext_condition(0x14);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar3 = unaff_r21 + iVar5 * 4;
  uVar4 = asm_instruction_08(0x31,unaff_r25,0x4bf);
  *(undefined2 *)(in_mmid + -0x1de) = *(undefined2 *)(iVar2 + 0x20);
  asm_instruction_08(0x32,uVar4,0x4bf);
  uVar4 = asm_instruction_06(0x12,in_r56,0x74c);
  if (!(bool)in_V) {
    func_0xbfde4130(param_1,param_2 & ~uVar3);
  }
  if ((in_r7 & 0x7ffff) == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  do {
  } while (uVar3 == 0);
  asm_instruction_06(0x32,uVar4,0xc);
  asm_instruction_08(0x24,unaff_r17,0x3c0);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf4570(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 in_r5;
  int in_r7;
  undefined4 in_r9;
  uint unaff_r13;
  undefined4 unaff_r14;
  undefined4 unaff_r21;
  undefined4 unaff_r25;
  undefined4 uVar2;
  undefined4 in_r53;
  undefined4 in_r56;
  undefined1 in_V;
  undefined8 uVar3;
  
  uVar3 = CONCAT44(param_2,param_1);
  *param_1 = unaff_r14;
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    uVar3 = func_0xbfd1d174();
  }
  uVar2 = asm_instruction_08(0x24,unaff_r25,0x4bf);
  asm_instruction_06(4,in_r56,0xd);
  if (!(bool)in_V) {
    func_0xbfde4228((int)uVar3,(uint)((ulonglong)uVar3 >> 0x20) & ~unaff_r13);
  }
  if (in_r7 == 0) {
    asm_instruction_05(0x3d,in_r5,0x181);
    asm_instruction_08(0x10,in_r9,0x14);
    asm_instruction_08(0x22,uVar2,0x4bf);
    asm_instruction_08(0x1f,unaff_r13,0xfffff8a1);
    asm_instruction_05(0x2a,unaff_r21,in_r53);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf4670(void)

{
  undefined4 unaff_r13;
  
  asm_instruction_05(0x3d,unaff_r13,0x711);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf49a4(undefined1 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r8;
  undefined1 unaff_r16;
  undefined4 unaff_r21;
  undefined4 in_r34;
  undefined4 in_r38;
  undefined4 in_r52;
  
  asm_instruction_06(0x23,in_r8,0x26);
  cVar1 = ext_condition(0x10);
  *param_1 = unaff_r16;
  if (cVar1 == '\0') {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  asm_instruction_06(0x35,in_r34,0x2c);
  iVar3 = asm_instruction_05(0x2d,unaff_r21,in_r52);
  uVar2 = asm_instruction_08(0x23,param_2,0x400);
  if (-1 < iVar3) {
    if (-1 < iVar3) {
      func_0xbfd8b374(param_1 + -0x84,uVar2);
    }
    asm_instruction_05(0x12,in_r38,3);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf49b0(void)

{
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Removing unreachable block (ram,0xbfd01250) */

void FUN_ram_bfcf49c4(undefined2 *param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 in_r8;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined1 unaff_r16;
  undefined2 unaff_r17;
  undefined2 unaff_r19;
  undefined4 unaff_r21;
  int iVar3;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r33;
  undefined4 in_r34;
  undefined4 in_r37;
  undefined4 in_r38;
  undefined4 in_r42;
  undefined2 *in_r48;
  int iVar4;
  undefined4 in_r52;
  undefined4 in_r56;
  undefined4 in_mlo;
  undefined1 in_Z;
  char in_N;
  undefined1 in_C;
  char in_V;
  
  if (!(bool)in_C && !(bool)in_Z) {
    asm_instruction_07(0x2e,unaff_r13,0x20);
    do {
    } while (unaff_r13 == 0);
    *param_1 = unaff_r17;
    param_1 = param_1 + -0x52;
    if ((bool)in_Z || in_V != in_N) {
      while( true ) {
        if ((bool)in_C || (bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        iVar4 = asm_instruction_06(0x31,in_r48,in_mlo);
        in_Z = iVar4 == 0;
        uVar2 = asm_instruction_08(0x22,param_1,0x500);
        cVar1 = ext_condition(0x10);
        if (cVar1 != '\0') {
          func_0xbfc9d6b4(uVar2);
          param_2 = extraout_r1;
        }
        if (!(bool)in_Z) {
          func_0xbfd88628();
          param_2 = extraout_r1_00;
        }
        in_r48 = (undefined2 *)(iVar4 + -0x9e);
        *in_r48 = (short)in_mlo;
        if (!(bool)in_Z) {
          func_0xbfdda430();
          param_2 = extraout_r1_01;
        }
        uVar2 = asm_instruction_06(0,in_r8,param_2);
        if (!(bool)in_C && !(bool)in_Z) break;
        param_1 = *(undefined2 **)(unaff_gp + 0x110);
        in_r8 = asm_instruction_06(0,uVar2,param_1);
      }
      asm_instruction_06(0x31,in_r48,in_mlo);
      asm_instruction_08(0x22,in_r56,0xbfd05244);
      asm_instruction_04(0x3d,in_r42,0xfffff800);
      asm_instruction_08(0x1f,in_r37,0x770);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *param_1 = unaff_r19;
    do {
    } while (unaff_r13 != 0);
    asm_instruction_08(0x22,unaff_r25,0x4bf);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar4 = *(int *)(in_r12 + 0x58);
  do {
  } while (unaff_r13 != 0);
  *param_1 = unaff_r19;
  iVar3 = asm_instruction_08(0x23,unaff_r25,0x47f);
  if ((bool)in_Z || in_V != in_N) {
    if (iVar3 < 0) {
      asm_instruction_08(2,in_r38,0x21);
      asm_instruction_08(3,in_r38,in_r33);
      func_0xbfd003a8(*(undefined4 *)(unaff_gp + 0x90));
      uVar2 = asm_instruction_08(0x22,uRam00000060,uRam00000060);
      cVar1 = ext_condition(0x1c);
      if (cVar1 != '\0') {
        func_0xbfcf9e44(uVar2);
      }
      do {
      } while( true );
    }
    if (iVar3 < 0) {
      asm_instruction_06(0x20,param_3,1);
      *(undefined2 **)(unaff_r14 + 0x70) = param_1 + -0x42;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1e);
    *(char *)(iVar4 + 0xc) = (char)iVar4;
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(4,in_r56,0xfffffd3f);
    func_0xbfd06454();
    *(undefined2 *)(in_r12 + 8) = param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0x23,in_r8,0x26);
  cVar1 = ext_condition(0x10);
  *(undefined1 *)(param_1 + -0x42) = unaff_r16;
  if (cVar1 == '\0') {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  asm_instruction_06(0x35,in_r34,0x2c);
  iVar4 = asm_instruction_05(0x2d,unaff_r21,in_r52);
  uVar2 = asm_instruction_08(0x23,param_2,0x400);
  if (-1 >= iVar4) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (-1 < iVar4) {
    func_0xbfd8b374(param_1 + -0x84,uVar2);
  }
  asm_instruction_05(0x12,in_r38,3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf4a30(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_r8;
  undefined4 uVar1;
  int unaff_r15;
  undefined4 unaff_r25;
  undefined4 in_blink;
  undefined4 in_r45;
  undefined1 in_N;
  bool in_V;
  
  if (!in_V) {
    in_blink = 0xbfcf4a36;
    func_0xbfde46b0(param_1,param_2,(int)*(short *)(unaff_r15 + 0x1a));
  }
  if ((bool)in_N) {
    in_blink = 0xbfcf4a3c;
    func_0xbfd77e34();
  }
  uVar1 = asm_instruction_06(4,in_r8,0x426);
  asm_instruction_08(0x24,unaff_r25,0x47f);
  asm_instruction_06(4,uVar1,0x326);
  asm_instruction_08(0x15,in_r45,in_blink);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf4ad8(int param_1)

{
  char cVar1;
  int in_r12;
  int unaff_r13;
  bool in_Z;
  
  if (unaff_r13 == 0) {
    *(int *)(param_1 + 0x3c) = param_1;
    if (!in_Z) {
      param_1 = func_0xbfd77f48();
    }
    asm_instruction_06(2,param_1,0x10);
  }
  else {
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (unaff_r13 != 0) {
      *(undefined2 *)(in_r12 + 0x20) = *(undefined2 *)(in_r12 + 0x20);
      FUN_ram_bfd0cd84();
      return;
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



void FUN_ram_bfcf4b0c(undefined4 param_1,undefined4 param_2)

{
  int in_r12;
  
  FUN_ram_bfd0cb22(param_1,param_2,*(undefined2 *)(in_r12 + 0x20));
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf4bf8(int param_1)

{
  undefined4 unaff_r19;
  
  *(undefined4 *)(param_1 + -0x290) = unaff_r19;
  *(undefined4 *)(param_1 + -0x390) = unaff_r19;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf4e04(void)

{
  undefined2 in_r3;
  int in_r12;
  
  *(undefined2 *)(in_r12 + 8) = in_r3;
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd0574a) overlaps instruction at (ram,0xbfd05748)
    */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf4f08(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int in_r7;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int *unaff_r16;
  int unaff_r17;
  int unaff_r20;
  int iVar7;
  undefined4 unaff_r21;
  int unaff_gp;
  undefined4 in_r36;
  undefined4 in_r37;
  undefined4 in_r49;
  int in_r54;
  undefined4 in_lp_count;
  bool in_Z;
  undefined1 uVar8;
  char in_N;
  undefined1 in_C;
  char in_V;
  undefined8 uVar9;
  
  if (!in_Z && in_V == in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar7 = unaff_r20 + 0x42;
  asm_instruction_05(0x2d,in_r37,unaff_r16);
  uVar5 = FUN_ram_bfd04940();
  while( true ) {
    in_r36 = asm_instruction_08(0x13,in_r36,0xfffffaf1);
    uVar9 = FUN_ram_bfd058c8(uVar5);
    iVar7 = iVar7 + 0x42;
    iVar6 = asm_instruction_05(0x2d,unaff_r13,unaff_r16);
    uVar8 = iVar6 == 0;
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
      asm_instruction_04(0x11,unaff_r21,in_r54);
      uVar2 = asm_instruction_08(0x23,(int)uVar9,(int)uVar9);
      asm_instruction_05(0x3d,in_r37,0xfffff8c3);
      if (!(bool)uVar8) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_06(0,uVar2,3);
      *(undefined2 *)(in_r12 + 6) = 0;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (unaff_r14 == 0) {
      while( true ) {
        if ((bool)in_C || (bool)uVar8) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        cVar1 = ext_condition(0x1e);
        if (cVar1 != '\0') {
          uVar9 = func_0xbfd66a48();
        }
        cVar1 = ext_condition(0x1c);
        if (cVar1 != '\0') {
          uVar9 = func_0xbfc13140();
        }
        uVar2 = (undefined4)((ulonglong)uVar9 >> 0x20);
        if (!(bool)in_C && !(bool)uVar8) break;
        *(int *)(unaff_r13 + 0x18) = in_r12;
        if (in_r7 == 0) {
          do {
          } while (unaff_r17 != in_r54);
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        puVar3 = (undefined1 *)asm_instruction_08(0x22,(int)uVar9,uVar2);
        *puVar3 = (char)puVar3;
        uVar4 = asm_instruction_08(0x22,puVar3,puVar3);
        uVar9 = CONCAT44(uVar2,uVar4);
        iVar6 = *(int *)(in_r12 + 0x78);
      }
      *(char *)(iVar6 + 0x50) = (char)uVar9;
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
    if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    FUN_ram_bfd0576c();
    if (!(bool)in_C && !(bool)uVar8) break;
    *unaff_r16 = iVar7;
    unaff_r16 = (int *)((int)unaff_r16 + 0x62);
    uVar5 = (uint)*(ushort *)(unaff_gp + 0xe8);
    if (!(bool)uVar8) {
      uVar5 = func_0xbfd2e344();
    }
    in_lp_count = asm_instruction_08(0x12,in_lp_count,in_r49);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcf5064) */
/* WARNING: Removing unreachable block (ram,0xbfcf5042) */

void FUN_ram_bfcf5030(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4)

{
  short sVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  undefined2 in_r9;
  int in_r12;
  int unaff_r14;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  undefined4 in_r37;
  int in_r48;
  bool in_N;
  bool in_V;
  
  if (in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_V != false) {
    do {
    } while (unaff_r14 != 0);
    uVar3 = asm_instruction_06(0x10,param_1,0x199);
    uVar2 = (undefined1)uVar3;
    sVar1 = *(short *)(in_r12 + 0x2e);
    uRam0000001f = param_4;
    if (!in_V) {
      uVar2 = func_0xbfde4cfc();
    }
    *(undefined1 *)(sVar1 + 5) = uVar2;
    asm_instruction_08(0x22,unaff_r25,0x4bf);
    *(undefined2 *)(in_r48 + -0x13c) = in_r9;
    asm_instruction_08(0x15,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Possible PIC construction at 0xbfcf5288: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0xbfcf528a) */
/* WARNING: Removing unreachable block (ram,0xbfc37d20) */
/* WARNING: Removing unreachable block (ram,0xbfcf52b0) */
/* WARNING: Removing unreachable block (ram,0xbfc5d2c0) */
/* WARNING: Removing unreachable block (ram,0xbfcf52b6) */

void FUN_ram_bfcf5214(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int in_r3;
  int iVar5;
  int unaff_r13;
  int unaff_r15;
  undefined4 in_r52;
  undefined4 in_lp_count;
  char in_Z;
  char in_N;
  char in_C;
  char in_V;
  undefined8 uVar6;
  
  FUN_ram_bfcf4408();
  if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf4410();
  if (in_N == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf4410();
  if ((bool)in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf441c();
  if ((bool)in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf4420();
  if (in_C == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar6 = func_0xbfcf4428();
  cVar1 = ext_condition(0x19);
  if ((int)((ulonglong)uVar6 >> 0x20) == 0) {
    if (cVar1 == '\0') {
      asm_instruction_06(0x14,(int)uVar6,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar5 = unaff_r15 + -1;
  while( true ) {
    uVar3 = (undefined4)uVar6;
    if ((bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if ((bool)in_V) break;
    asm_instruction_06(0x23,uVar3,0);
    asm_instruction_08(0x37,in_r52,0x2c);
    asm_instruction_06(2,uVar3,0);
    uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
    uVar6 = func_0xbfcf51f8(uVar3,(int)((ulonglong)uVar6 >> 0x20),uVar2);
    uVar3 = asm_instruction_08(0x37,in_lp_count,0x23);
    uVar6 = FUN_ram_bfcf5214((int)uVar6,(int)((ulonglong)uVar6 >> 0x20),uVar3);
    uVar3 = asm_instruction_08(0x37,in_lp_count,0x23);
                    /* WARNING: Call to offcut address within same function */
    uVar6 = func_0xbfcf522c((int)uVar6,(int)((ulonglong)uVar6 >> 0x20),uVar3);
    unaff_r13 = in_r3 << 4;
    iVar4 = asm_instruction_08(0x37,in_lp_count,0x23);
    in_Z = iVar4 == 0;
    in_N = iVar4 < 0;
  }
  if ((bool)in_N) {
    uVar3 = func_0xbfd228c4();
  }
  if (unaff_r13 == 0) {
    *(short *)(iVar5 + 8) = (short)in_r3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0x20,uVar3,0x18);
  if ((bool)in_Z || in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((bool)in_Z != false) {
    asm_instruction_06(0x20,uVar3,0x18);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf5260(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_lp_count;
  char cVar4;
  undefined8 uVar5;
  
  asm_instruction_06(2,param_1,0);
  uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
  uVar5 = func_0xbfcf51f8(param_1,param_2,uVar2);
  uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
  uVar5 = FUN_ram_bfcf5214((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar2);
  uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
  uVar5 = func_0xbfcf522c((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar2);
  uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
  uVar5 = func_0xbfcf5248((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar2);
  uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
  uVar5 = FUN_ram_bfcf5260((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar2);
  uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
                    /* WARNING: Call to offcut address within same function */
  uVar5 = func_0xbfcf527c((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar2);
  iVar3 = asm_instruction_08(0x37,&stack0x00000000,0x19);
  cVar4 = iVar3 == 0;
  FUN_ram_bfcf51f4((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),param_4 + 7);
  thunk_FUN_ram_bfd056fa();
  uVar5 = FUN_ram_bfcf5298();
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar4 != '\0') {
    FUN_ram_bfcf4f08((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),*(undefined2 *)((int)uVar5 + 0x28));
    FUN_ram_bfd0552a();
    return;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf5298(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_lp_count;
  char cVar4;
  undefined8 uVar5;
  
  uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
  uVar5 = func_0xbfcf527c(param_1,param_2,uVar2);
  iVar3 = asm_instruction_08(0x37,&stack0x00000000,0x19);
  cVar4 = iVar3 == 0;
  FUN_ram_bfcf51f4((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),param_4 + 7);
  thunk_FUN_ram_bfd056fa();
  uVar5 = FUN_ram_bfcf5298();
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar4 != '\0') {
    FUN_ram_bfcf4f08((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),*(undefined2 *)((int)uVar5 + 0x28));
    FUN_ram_bfd0552a();
    return;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf52c4(undefined4 param_1,uint param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  int extraout_r1;
  uint unaff_r13;
  int unaff_r15;
  int iVar3;
  undefined4 in_r52;
  undefined4 in_lp_count;
  char cVar4;
  bool in_Z;
  undefined8 uVar5;
  
  if (unaff_r15 == 0) {
    uVar2 = Auxregs319c;
    if (in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0x23,param_1,0);
    asm_instruction_08(0x37,in_r52,0x2c);
    asm_instruction_06(2,param_1,0);
    uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
    uVar5 = func_0xbfcf51f8(param_1,param_2 & ~unaff_r13,uVar2);
    uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
    uVar5 = FUN_ram_bfcf5214((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar2);
    uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
    uVar5 = func_0xbfcf522c((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar2);
    uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
                    /* WARNING: Call to offcut address within same function */
    uVar5 = func_0xbfcf5248((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar2);
    uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
    uVar5 = FUN_ram_bfcf5260((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar2);
    uVar2 = asm_instruction_08(0x37,in_lp_count,0x23);
                    /* WARNING: Call to offcut address within same function */
    uVar5 = func_0xbfcf527c((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar2);
    iVar3 = asm_instruction_08(0x37,&stack0x00000000,0x19);
    cVar4 = iVar3 == 0;
    FUN_ram_bfcf51f4((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),param_4 + 7);
    thunk_FUN_ram_bfd056fa();
    uVar5 = FUN_ram_bfcf5298();
    cVar1 = ext_condition(0x10);
    if (cVar1 == '\0') {
      if (cVar4 != '\0') {
        FUN_ram_bfcf4f08((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),
                         *(undefined2 *)((int)uVar5 + 0x28));
        FUN_ram_bfd0552a();
        return;
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  func_0xbfcf490c();
  cVar1 = ext_condition(0x11);
  cVar4 = ext_condition(0x11);
  if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x11);
  cVar4 = ext_condition(0x11);
  if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x15);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar2 = asm_instruction_06(0x1d,extraout_r1 << 7,0x408);
  func_0xbfcd3f84(uVar2);
  func_0xbfcf595c();
  cVar1 = ext_condition(0x1d);
  cVar4 = ext_condition(0x1d);
  if (cVar4 == '\0') {
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    cVar4 = ext_condition(0x1d);
    if (cVar4 == '\0') {
      if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf52f0(void)

{
  char cVar1;
  char cVar2;
  
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1d);
  cVar2 = ext_condition(0x1d);
  if (cVar2 == '\0') {
    if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf5368(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6)

{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  undefined1 unaff_r15;
  undefined4 unaff_r17;
  undefined4 in_r53;
  char in_Z;
  char in_N;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    param_1 = FUN_ram_bfcf9b68();
  }
  uVar3 = asm_instruction_06(0x1d,param_1,0x40a);
  asm_instruction_06(0x1d,uVar3,9);
  func_0xbfcf4e6c(uVar3);
  cVar1 = ext_condition(0x1d);
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1d);
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1d);
  if (in_N == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar3 = FUN_ram_bfcf4e04();
  if (in_N != '\0') {
    FUN_ram_bfcf49a0();
    if (in_Z != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined1 *)(param_3 + 0x19) = unaff_r15;
  uVar3 = asm_instruction_06(4,uVar3,0x5d0);
  asm_instruction_05(0x2d,param_6,in_r53);
  asm_instruction_08(0x23,unaff_r17,0x200);
  FUN_ram_bfd11714(uVar3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf5464(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  ushort uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined4 uVar6;
  int in_r7;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int unaff_r15;
  int *unaff_r16;
  int unaff_r17;
  int unaff_r20;
  undefined4 unaff_r21;
  int unaff_gp;
  undefined4 in_r36;
  undefined4 in_r37;
  undefined4 in_r49;
  int in_r54;
  undefined4 in_lp_count;
  undefined1 in_Z;
  undefined1 in_C;
  undefined8 uVar7;
  char cVar2;
  
  FUN_ram_bfcf4ad8();
  cVar1 = ext_condition(0x1d);
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 == '\0') {
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 == '\0') {
      cVar1 = ext_condition(0x15);
      if (cVar1 != '\0') {
        uVar3 = (ushort)*(byte *)(unaff_r13 + 4);
        if (unaff_r15 != -0x34) {
          uVar3 = *(ushort *)(unaff_gp + 0x1fa);
        }
        cVar1 = ext_condition(0x12);
        if (cVar1 != '\0') {
          func_0xbfc652d8(uVar3);
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      thunk_EXT_FUN_ram_bfce5e3e();
      uVar7 = func_0xbfd058d4();
      do {
        if (unaff_r14 == 0) {
          while( true ) {
            if ((bool)in_C || (bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            cVar1 = ext_condition(0x1e);
            if (cVar1 != '\0') {
              uVar7 = func_0xbfd66a48();
            }
            cVar1 = ext_condition(0x1c);
            if (cVar1 != '\0') {
              uVar7 = func_0xbfc13140();
            }
            uVar4 = (undefined4)((ulonglong)uVar7 >> 0x20);
            if (!(bool)in_C && !(bool)in_Z) break;
            *(int *)(unaff_r13 + 0x18) = in_r12;
            if (in_r7 == 0) {
              do {
              } while (unaff_r17 != in_r54);
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            puVar5 = (undefined1 *)asm_instruction_08(0x22,(int)uVar7,uVar4);
            *puVar5 = (char)puVar5;
            uVar6 = asm_instruction_08(0x22,puVar5,puVar5);
            uVar7 = CONCAT44(uVar4,uVar6);
            param_3 = *(int *)(in_r12 + 0x78);
          }
          *(char *)(param_3 + 0x50) = (char)uVar7;
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
          halt_unimplemented();
        }
        if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        FUN_ram_bfd0576c();
        if (!(bool)in_C && !(bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        *unaff_r16 = unaff_r20;
        unaff_r16 = (int *)((int)unaff_r16 + 0x62);
        if (!(bool)in_Z) {
          func_0xbfd2e344(*(undefined2 *)(unaff_gp + 0xe8));
        }
        in_lp_count = asm_instruction_08(0x12,in_lp_count,in_r49);
        in_r36 = asm_instruction_08(0x13,in_r36,0xfffffaf1);
        uVar7 = FUN_ram_bfd058c8();
        unaff_r20 = unaff_r20 + 0x42;
        param_3 = asm_instruction_05(0x2d,unaff_r13,unaff_r16);
        in_Z = param_3 == 0;
        cVar1 = ext_condition(0x1c);
      } while (cVar1 == '\0');
      asm_instruction_04(0x11,unaff_r21,in_r54);
      uVar4 = asm_instruction_08(0x23,(int)uVar7,(int)uVar7);
      asm_instruction_05(0x3d,in_r37,0xfffff8c3);
      if (!(bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_06(0,uVar4,3);
      *(undefined2 *)(in_r12 + 6) = 0;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Removing unreachable block (ram,0xbfcfd000) */

void FUN_ram_bfcf5594(undefined4 param_1,undefined4 param_2,int param_3,undefined2 param_4)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined1 extraout_r1;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int unaff_r15;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r51;
  undefined4 in_r56;
  char in_Z;
  char in_N;
  undefined1 in_C;
  char in_V;
  undefined8 uVar4;
  
  FUN_ram_bfcf5988();
  cVar2 = ext_condition(0x1e);
  if (cVar2 == '\0') {
    cVar2 = ext_condition(0x1d);
    if (cVar2 != '\0') {
      func_0xbfcecd98();
    }
    bVar1 = in_V == in_N;
    uVar3 = FUN_ram_bfcf56a0();
    if (bVar1) {
      *(char *)(param_3 + 0x19) = (char)unaff_r15;
      asm_instruction_06(4,uVar3,0x69c);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    func_0xbfcf5a98();
    if ((!(bool)in_V) && (FUN_ram_bfcfcda8(), !(bool)in_C && !(bool)in_Z)) {
      uVar3 = FUN_ram_bfcf8118();
      *(undefined1 *)(unaff_r14 + 0x1a) = extraout_r1;
      *(short *)(in_r12 + 4) = (short)uVar3;
      if ((bool)in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      FUN_ram_bfcf7c64(uVar3,unaff_r14 + -1);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
    FUN_ram_bfcf56ac();
    do {
    } while (unaff_r14 == 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
    *(short *)(in_r12 + 0x24) = (short)param_3;
  }
  cVar2 = ext_condition(0x12);
  uVar4 = FUN_ram_bfcfd050();
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
    asm_instruction_06(0x32,in_r56,0x3f);
    *(undefined2 *)(*(byte *)((ulonglong)uVar4 >> 0x20) + 6) = param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(short *)((int)uVar4 + 0x24) = (short)param_3;
  cVar2 = ext_condition(0x18);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r15 == 0) {
    asm_instruction_08(0x3e,unaff_r25,0x47f);
    asm_instruction_06(0x1e,in_r51,0x1d);
    FUN_ram_bfcfdae8(*(undefined2 *)(unaff_gp + 0x12));
    do {
    } while( true );
  }
  uRam0000000a = (char)*(ushort *)(unaff_gp + 0xf4);
  asm_instruction_06(0,param_3,(uint)*(ushort *)(unaff_gp + 0xf4));
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf55a4(void)

{
  undefined2 uVar1;
  undefined1 extraout_r1;
  int in_r12;
  int unaff_r14;
  undefined1 in_Z;
  undefined1 in_N;
  undefined1 in_C;
  undefined1 in_V;
  
  func_0xbfcf5a98();
  if ((!(bool)in_V) && (FUN_ram_bfcfcda8(), !(bool)in_C && !(bool)in_Z)) {
    uVar1 = FUN_ram_bfcf8118();
    *(undefined1 *)(unaff_r14 + 0x1a) = extraout_r1;
    *(undefined2 *)(in_r12 + 4) = uVar1;
    if (!(bool)in_N) {
      FUN_ram_bfcf7c64(uVar1,unaff_r14 + -1);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf56ac();
  do {
  } while (unaff_r14 == 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf55dc(void)

{
  undefined4 in_r4;
  
  asm_instruction_08(8,in_r4,0xf);
  FUN_ram_bfcf6020();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf55fc(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int in_r12;
  undefined4 in_r36;
  char in_N;
  char in_V;
  
  FUN_ram_bfcf52f0();
  cVar1 = ext_condition(0x10);
  *(short *)(param_3 + 0x20) = (short)in_r12;
  if (cVar1 != '\0') {
    *(short *)(in_r12 + 0x20) = (short)param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf4bf8();
  if (in_V != in_N) {
    thunk_FUN_ram_bfd09072();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    asm_instruction_08(0x37,in_r36,0x13);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



void FUN_ram_bfcf564c(void)

{
  thunk_FUN_ram_bfd058d8();
  thunk_FUN_ram_bfd15aba();
  return;
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcf56a0) */
/* WARNING: Removing unreachable block (ram,0xbfd05996) */
/* WARNING: Removing unreachable block (ram,0xbfd05998) */

void FUN_ram_bfcf5694(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf56a0(void)

{
  int unaff_r14;
  undefined4 uVar1;
  undefined4 in_r45;
  
  uVar1 = 0xbfcf56a2;
  func_0xbfcf57a0();
  do {
  } while (unaff_r14 == 0);
  asm_instruction_08(4,in_r45,uVar1);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf56ac(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                     undefined4 param_5)

{
  char cVar1;
  undefined1 in_r12;
  
  *(undefined1 *)(param_3 + 0x10) = in_r12;
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    asm_instruction_08(8,param_5,0xf);
    FUN_ram_bfcf60f4();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf5830(undefined4 param_1,int param_2)

{
  char cVar1;
  bool in_Z;
  bool in_C;
  
  if (param_2 == 0) {
    if (!in_C && !in_Z) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf49a4();
  cVar1 = ext_condition(0x11);
  FUN_ram_bfcf49ac();
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x12);
  FUN_ram_bfcf49b0();
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x13);
  func_0xbfcf49b8();
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x14);
  func_0xbfcf49bc();
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x15);
  FUN_ram_bfcf49c4();
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x16);
  FUN_ram_bfcf49c4();
  if (cVar1 == '\0') {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf5844(void)

{
  char cVar1;
  
  func_0xbfcf49b8();
  cVar1 = ext_condition(0x14);
  func_0xbfcf49bc();
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x15);
  FUN_ram_bfcf49c4();
  if (cVar1 == '\0') {
    cVar1 = ext_condition(0x16);
    FUN_ram_bfcf49c4();
    if (cVar1 == '\0') {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf5850(void)

{
  char cVar1;
  
  FUN_ram_bfcf49c4();
  cVar1 = ext_condition(0x16);
  FUN_ram_bfcf49c4();
  if (cVar1 == '\0') {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf59a6) overlaps instruction at (ram,0xbfcf59a2)
    */

void FUN_ram_bfcf5988(void)

{
  undefined4 in_r8;
  int unaff_r13;
  int iVar1;
  undefined4 unaff_r25;
  undefined4 uVar2;
  int unaff_gp;
  undefined4 in_r48;
  undefined4 in_mlo;
  undefined1 uVar3;
  undefined1 in_C;
  
  uVar2 = asm_instruction_08(0x22,unaff_r25,0x4bf);
  iVar1 = asm_instruction_06(2,in_r48,0x3d);
  uVar3 = iVar1 == 0;
  if (!(bool)in_C) {
    func_0xbfc4ddd0(*(undefined2 *)(unaff_gp + 6));
  }
  if (!(bool)uVar3) {
    func_0xbfd78bb4();
  }
  iVar1 = asm_instruction_06(2,in_r48,0x3d);
  if (unaff_r13 != 0) {
    if (iVar1 != 0) {
      func_0xbfdcade0(*(undefined2 *)(unaff_gp + 6));
    }
    asm_instruction_06(0,in_r8,*(undefined4 *)(unaff_gp + 0x110));
    iVar1 = asm_instruction_08(0x31,uVar2,0x4bf);
    if (!(bool)in_C && iVar1 != 0) {
      asm_instruction_06(0x31,in_r48,in_mlo);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  do {
  } while( true );
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf5dac(void)

{
  undefined4 unaff_r16;
  undefined4 in_r35;
  undefined4 in_r56;
  undefined1 in_Z;
  undefined1 in_C;
  undefined1 in_V;
  
  FUN_ram_bfcf5f1c();
  if (!(bool)in_C && !(bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(4,in_r56,0xfffff80d);
  if ((bool)in_V) {
    func_0xbfd791e8();
  }
  asm_instruction_06(0x27,unaff_r16,0x35);
  asm_instruction_06(0x10,in_r35,3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf5e38(void)

{
  char in_Z;
  
  if (in_Z != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcf5f0e) */
/* WARNING: Removing unreachable block (ram,0xbfcf5f1a) */

void FUN_ram_bfcf5f1c(uint param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int unaff_r13;
  int unaff_r14;
  int unaff_r15;
  int unaff_gp;
  undefined4 in_r52;
  undefined4 in_lp_count;
  undefined1 in_Z;
  undefined1 in_C;
  
  while( true ) {
    iVar3 = unaff_r14 >> 1;
    if (unaff_r15 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (!(bool)in_C && !(bool)in_Z) break;
    unaff_r13 = *(int *)(param_4 + 0x54);
    param_1 = (uint)*(byte *)(unaff_r13 + 10);
    if (unaff_r13 == 0) break;
    param_1 = *(uint *)(unaff_gp + 0x110);
    cVar1 = ext_condition(0x19);
    if (cVar1 != '\0') {
      param_1 = func_0xbfdd3388();
    }
    unaff_r15 = 0;
  }
  *(char *)(unaff_r14 + 0xe) = (char)param_4;
  *(char *)(unaff_r13 + 0xd) = (char)param_1;
  if (!(bool)in_C && !(bool)in_Z) {
    param_1 = func_0xbfdd2558();
  }
  uVar2 = asm_instruction_06(0x3d,param_1,0x7c0);
  asm_instruction_07(0x1d,in_r52,in_lp_count);
  *(char *)(iVar3 + 5) = (char)uVar2;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf6170) overlaps instruction at (ram,0xbfcf616c)
    */
/* WARNING: Removing unreachable block (ram,0xbfcf6168) */
/* WARNING: Removing unreachable block (ram,0xbfcf616c) */
/* WARNING: Removing unreachable block (ram,0xbfcf6178) */
/* WARNING: Removing unreachable block (ram,0xbfcf617a) */
/* WARNING: Removing unreachable block (ram,0xbfcf6148) */
/* WARNING: Removing unreachable block (ram,0xbfcf6170) */
/* WARNING: Removing unreachable block (ram,0xbfcf6172) */
/* WARNING: Removing unreachable block (ram,0xbfd7fe38) */
/* WARNING: Removing unreachable block (ram,0xbfd0f57a) */
/* WARNING: Removing unreachable block (ram,0xbfd0f51a) */
/* WARNING: Removing unreachable block (ram,0xbfd0f57c) */
/* WARNING: Removing unreachable block (ram,0xbfd0f550) */
/* WARNING: Removing unreachable block (ram,0xbfd0f582) */
/* WARNING: Removing unreachable block (ram,0xbfd0f58a) */
/* WARNING: Removing unreachable block (ram,0xbfd0f592) */
/* WARNING: Removing unreachable block (ram,0xbfcf614e) */
/* WARNING: Removing unreachable block (ram,0xbfcf621c) */
/* WARNING: Removing unreachable block (ram,0xbfcf615e) */

void FUN_ram_bfcf60f4(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  short sVar3;
  int in_r7;
  int in_r12;
  int unaff_r14;
  bool in_V;
  char cVar2;
  
  cVar1 = ext_condition(0x1d);
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 == '\0') {
    cVar2 = ext_condition(0x1d);
    if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar2 = ext_condition(0x12);
    if (cVar2 == '\0') {
      sVar3 = *(short *)(param_3 + 0x36);
      if (in_r7 == 0) {
        *(char *)(unaff_r14 + 0x16) = (char)param_1;
        *(short *)(in_r12 + 0x32) = (short)unaff_r14;
        if (!in_V) {
          func_0xbfce5df4(param_1,(int)sVar3);
        }
        func_0xbfcf5470();
        FUN_ram_bfd0f580();
        return;
      }
      asm_instruction_06(0x11,param_1,0x480);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf6184(void)

{
  undefined4 uVar1;
  int in_r12;
  int unaff_r13;
  undefined2 unaff_r14;
  undefined1 in_V;
  
  *(undefined2 *)(in_r12 + 0x32) = unaff_r14;
  uVar1 = func_0xbfcf5478();
  if ((unaff_r13 != 0) && ((bool)in_V)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  do {
    asm_instruction_06(0x1d,uVar1,0xf);
  } while (unaff_r13 != 0);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



void FUN_ram_bfcf62e0(void)

{
  undefined4 in_r4;
  code *UNRECOVERED_JUMPTABLE;
  
  asm_instruction_06(0x1d,in_r4,0xf);
                    /* WARNING: Could not recover jumptable at 0xbfcf62e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf6344(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  char cVar1;
  char cVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 in_r8;
  int in_r12;
  int unaff_r13;
  undefined4 unaff_r17;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  undefined4 uVar5;
  undefined4 unaff_fp;
  undefined4 in_r37;
  undefined4 in_r54;
  undefined4 in_r56;
  int iVar6;
  char in_Z;
  bool in_C;
  char in_V;
  
  asm_instruction_06(0x3d,param_3,in_r8);
  if (in_r12 != 0) {
    param_3 = asm_instruction_06(0,param_3,0);
  }
  iVar4 = asm_instruction_06(0x3d,param_3,0xd);
  puVar3 = (undefined1 *)asm_instruction_06(0x1d,param_1,0x310);
  if (in_C || (bool)in_Z) {
    *puVar3 = (char)iVar4;
    if (in_V == '\0') {
      cVar1 = ext_condition(0x10);
      if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar6 = asm_instruction_06(0x37,in_r56,0x3f);
      in_Z = iVar6 == 0;
      if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    else {
      puVar3 = (undefined1 *)func_0xbfcf559c();
      *puVar3 = (char)iVar4;
      if (in_V != '\0') {
        FUN_ram_bfcf55a4();
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
        halt_unimplemented();
      }
      cVar1 = ext_condition(0x10);
      if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    *(short *)(iVar4 + 0x22) = (short)unaff_r13;
    cVar1 = ext_condition(0x18);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (in_Z != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x1f,unaff_fp,2);
  cVar1 = ext_condition(0x15);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar5 = asm_instruction_05(0x31,unaff_r21,0xfffffc96);
  iVar4 = asm_instruction_05(0x18,param_2,param_2);
  asm_instruction_04(0x24,in_r37,unaff_r17);
  asm_instruction_05(0x12,param_2,0xfffffc01);
  *(undefined4 *)(iVar4 + 0x90) = in_r54;
  asm_instruction_08(0x13,unaff_r20,0x26);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0x31,uVar5,0xfffffd96);
  iVar4 = asm_instruction_08(0x13,param_5,0x34);
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (iVar4 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    cVar2 = ext_condition(0x1d);
    if (cVar2 == '\0') {
      if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf6370(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  char cVar1;
  char cVar2;
  undefined4 *unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  int iVar3;
  undefined4 in_r37;
  undefined4 in_r54;
  
  asm_instruction_04(0x24,in_r37,unaff_r17);
  asm_instruction_05(0x12,param_2,0xfffffc01);
  *unaff_r16 = in_r54;
  asm_instruction_08(0x13,unaff_r20,0x26);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0x31,unaff_r21,0xfffffd96);
  iVar3 = asm_instruction_08(0x13,param_5,0x34);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (iVar3 == 0) {
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    cVar2 = ext_condition(0x1d);
    if (cVar2 == '\0') {
      if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf639c(void)

{
  char cVar1;
  char cVar2;
  
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1d);
  cVar2 = ext_condition(0x1d);
  if (cVar2 == '\0') {
    if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf6740(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 extraout_r1;
  int in_r12;
  int unaff_r13;
  int unaff_r15;
  bool in_N;
  
  if (!in_N) {
    param_1 = func_0xbfcd5b80(param_1,unaff_r15 >> 5);
  }
  if (unaff_r13 == 0) {
    uVar2 = asm_instruction_06(0x3d,param_1,0xfffffa0d);
    FUN_ram_bfcf6740(uVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(in_r12 + 4) = param_4;
  FUN_ram_bfcf6760(param_1,unaff_r13);
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    asm_instruction_06(0x20,extraout_r1,extraout_r1);
    asm_instruction_06(0x20,extraout_r1,param_3);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf6a14(void)

{
  FUN_ram_bfcf6a14();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf6b98(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  int in_r12;
  undefined4 in_r44;
  int iVar1;
  
  asm_instruction_06(0x30,param_5,0);
  asm_instruction_06(0x10,param_5,0);
  iVar1 = asm_instruction_08(0x1a,in_r44,0xfffff8c1);
  if (-1 < iVar1) {
    *(undefined2 *)(in_r12 + 6) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf6ffc(void)

{
  undefined2 *in_mlo;
  undefined2 in_r61reserved;
  
  *in_mlo = in_r61reserved;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7008(void)

{
  char cVar1;
  
  cVar1 = ext_condition(0x13);
  if (cVar1 != '\0') {
    func_0xbfd6580c();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf72c6(void)

{
  char in_N;
  char in_V;
  
  if (in_V != in_N) {
    func_0xbfd57a64();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7854(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined1 unaff_r15;
  char in_V;
  
  *(undefined1 *)(param_3 + 0x19) = unaff_r15;
  if (in_V != '\0') {
    asm_instruction_06(4,param_1,0x69c);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7874(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7a54(undefined1 param_1)

{
  int in_r12;
  undefined4 unaff_r25;
  
  *(undefined1 *)(in_r12 + 0x12) = param_1;
  asm_instruction_08(0x33,unaff_r25,0x4bf);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7a90(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7b38(int param_1)

{
  char cVar1;
  int unaff_r18;
  undefined4 in_r56;
  char in_Z;
  
  if (in_Z == '\0') {
    *(int *)(param_1 + unaff_r18 + 0x3c) = param_1 + unaff_r18;
    func_0xbfd7b744();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0x11,in_r56,0xfffffd01);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7b50(int param_1)

{
  char cVar1;
  undefined1 unaff_r13;
  
  cVar1 = ext_condition(0x12);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x1b) = unaff_r13;
    cVar1 = ext_condition(0x13);
    if (cVar1 != '\0') {
      func_0xbfdd3f58();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_bfcf7c38(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar3;
  int unaff_r13;
  undefined4 in_r61reserved;
  undefined1 in_Z;
  undefined1 in_C;
  char cVar2;
  
  iVar3 = asm_instruction_06(0,(uint)*(byte *)(unaff_r13 + 0xf),0xfffff843);
  if (!(bool)in_Z) {
    iVar3 = func_0xbfc18840();
  }
  cVar1 = ext_condition(0x10);
  cVar2 = ext_condition(0x18);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (iVar3 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((bool)in_C || (bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0x27,in_r61reserved,param_3);
  cVar1 = ext_condition(0x14);
  if (cVar1 == '\0') {
    asm_instruction_06(0x20,_LAB_ram_bfcf7e08,3);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_bfcf7c64(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar3;
  undefined4 uVar4;
  int in_r12;
  int unaff_r13;
  int unaff_gp;
  undefined4 in_r61reserved;
  undefined1 in_Z;
  undefined1 in_C;
  char cVar2;
  
  uVar4 = asm_instruction_06(0,param_1,0xfffff843);
  if (!(bool)in_C && !(bool)in_Z) {
    *(char *)(in_r12 + 0x1c) = (char)unaff_r13;
    asm_instruction_06(0x20,uVar4,0x742);
    asm_instruction_06(0,(uint)*(ushort *)(unaff_gp + 0x26),0x143);
    *(short *)(in_r12 + 0x22) = (short)param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar3 = asm_instruction_06(0,(uint)*(byte *)(unaff_r13 + 0xf),0xfffff843);
  if (!(bool)in_Z) {
    iVar3 = func_0xbfc18840();
  }
  cVar1 = ext_condition(0x10);
  cVar2 = ext_condition(0x18);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (iVar3 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((bool)in_C || (bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0x27,in_r61reserved,param_3);
  cVar1 = ext_condition(0x14);
  if (cVar1 == '\0') {
    asm_instruction_06(0x20,_LAB_ram_bfcf7e08,3);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7cf0(void)

{
  undefined2 unaff_r13;
  int unaff_r14;
  
  *(undefined2 *)(unaff_r14 + 0x20) = unaff_r13;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7cf8(void)

{
  char cVar1;
  undefined2 in_r3;
  undefined4 in_r5;
  int in_r12;
  int unaff_r13;
  
  cVar1 = ext_condition(0x1c);
  if (cVar1 == '\0') {
    asm_instruction_05(0x2c,in_r5,0x5f6);
    do {
    } while (unaff_r13 != 0);
    *(undefined2 *)(in_r12 + 0x20) = in_r3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Removing unreachable block (ram,0xbfcf7d78) */

void FUN_ram_bfcf7d08(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     int param_5,undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  int unaff_r13;
  int unaff_r14;
  undefined4 in_r50;
  undefined1 in_Z;
  undefined1 in_N;
  
  asm_instruction_05(0x23,param_6,in_r50);
  *(short *)(unaff_r14 + 0x20) = (short)unaff_r13;
  cVar1 = ext_condition(0x1a);
  if (cVar1 != '\0') {
    param_1 = func_0xbfc90110();
  }
  if (!(bool)in_N && !(bool)in_Z) {
    param_1 = func_0xbfc52114();
  }
  if (unaff_r13 == 0) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  if (param_1 - param_5 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(int *)(param_1 + 0x3c) = param_1;
  if (param_1 != param_5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0xd,unaff_r14,0x11);
  asm_instruction_05(0x1d,param_7,param_4);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Removing unreachable block (ram,0xbfcf7d78) */

void FUN_ram_bfcf7d10(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     int param_5,undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  int unaff_r13;
  undefined4 unaff_r14;
  undefined1 in_Z;
  undefined1 in_N;
  
  cVar1 = ext_condition(0x1a);
  if (cVar1 != '\0') {
    param_1 = func_0xbfc90110();
  }
  if (!(bool)in_N && !(bool)in_Z) {
    param_1 = func_0xbfc52114();
  }
  if (unaff_r13 == 0) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  if (param_1 - param_5 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(int *)(param_1 + 0x3c) = param_1;
  if (param_1 != param_5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0xd,unaff_r14,0x11);
  asm_instruction_05(0x1d,param_7,param_4);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Removing unreachable block (ram,0xbfcf7d78) */

void FUN_ram_bfcf7d18(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     int param_5,undefined4 param_6,undefined4 param_7)

{
  int unaff_r13;
  undefined4 unaff_r14;
  
  if (unaff_r13 == 0) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  if (-1 < param_1 - param_5) {
    *(int *)(param_1 + 0x3c) = param_1;
    if (param_1 != param_5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_05(0xd,unaff_r14,0x11);
    asm_instruction_05(0x1d,param_7,param_4);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7d20(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 unaff_r14;
  char in_Z;
  char in_N;
  
  if (in_N != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(int *)(param_1 + 0x3c) = param_1;
  if (in_Z != '\0') {
    asm_instruction_05(0xd,unaff_r14,0x11);
    asm_instruction_05(0x1d,param_7,param_4);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7d28(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  char cVar1;
  int in_r7;
  uint uVar2;
  undefined2 unaff_r13;
  int unaff_r14;
  int unaff_gp;
  undefined1 in_Z;
  undefined1 in_N;
  
  *(undefined2 *)(unaff_r14 + 0x20) = unaff_r13;
  func_0xc08901a8();
  uVar2 = (uint)*(byte *)(in_r7 + 0x1f);
  if (!(bool)in_Z) {
    func_0xbfcd21c4();
  }
  *(undefined2 *)(uVar2 + 0x20) = param_3;
  func_0xbfcf7cd4();
  if ((bool)in_N) {
    func_0xbfc9013c();
  }
  cVar1 = ext_condition(0x12);
  if (cVar1 != '\0') {
    FUN_ram_bfd11140();
  }
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
    func_0xbfd3d9f4(unaff_gp + -0x3b8);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7ee8(undefined1 param_1)

{
  int iVar1;
  undefined4 *unaff_r13;
  int unaff_r14;
  undefined1 in_Z;
  char in_N;
  undefined8 uVar2;
  
  *(undefined1 *)(unaff_r14 + 4) = param_1;
  if (in_N != '\0') {
    uVar2 = func_0xbfcf70e0();
    iVar1 = (int)uVar2;
    if (!(bool)in_Z) {
      iVar1 = func_0xbfcd5354(iVar1,(int)((ulonglong)uVar2 >> 0x20),*unaff_r13);
    }
    *(int *)(iVar1 + 0x2f4) = iVar1;
    *(int *)(iVar1 + 0x2f4) = iVar1;
    do {
    } while (unaff_r14 != 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7f34(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  char cVar1;
  int in_r12;
  undefined1 in_Z;
  
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
    func_0xbfd21394();
  }
  if (!(bool)in_Z) {
    *(undefined2 *)(in_r12 + 8) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf7f70(void)

{
  undefined4 unaff_r13;
  
  asm_instruction_05(0x3d,unaff_r13,0x412);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf808c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  int iVar1;
  undefined4 in_r54;
  
  iVar1 = asm_instruction_08(0x23,param_1,param_1);
  asm_instruction_05(0xd,in_r54,0x37);
  *(undefined2 *)(iVar1 + 6) = param_4;
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf80bc(void)

{
  char cVar1;
  undefined4 unaff_r16;
  
  asm_instruction_06(0x25,unaff_r16,0);
  cVar1 = ext_condition(0x1c);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf8120) overlaps instruction at (ram,0xbfcf811e)
    */

void FUN_ram_bfcf80ec(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6)

{
  uint uVar1;
  undefined4 uVar2;
  int extraout_r1;
  undefined4 in_r9;
  int in_r12;
  int unaff_r13;
  int iVar3;
  undefined2 unaff_r15;
  undefined4 unaff_r17;
  uint unaff_r19;
  undefined4 unaff_r21;
  int unaff_r25;
  int unaff_gp;
  undefined4 in_r34;
  undefined4 in_r50;
  uint in_r56;
  undefined4 in_mmid;
  undefined4 in_r61reserved;
  char cVar4;
  undefined1 in_N;
  undefined1 in_C;
  char in_V;
  
  *(undefined4 *)(param_2 + 0x25) = param_1;
  asm_instruction_05(0x2d,unaff_r21,in_r61reserved);
  iVar3 = unaff_r13;
  if (unaff_r13 == 0) goto FUN_ram_bfcf8118;
  *(short *)(in_r12 + 0xc) = (short)param_3;
  cVar4 = ext_condition(0x1c);
  if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar3 = *(int *)(in_r12 + 0x70);
  if ((bool)in_C) {
    func_0xbfd7b540(unaff_gp + -0x38,unaff_r13);
    unaff_r13 = extraout_r1;
  }
  in_r56 = asm_instruction_06(0x25,in_r56,0xfffffb15);
  uVar1 = in_r56;
  do {
    in_N = (int)uVar1 < 0;
    uVar2 = asm_instruction_06(0x20,(uint)*(ushort *)(unaff_gp + 0x1c),3);
    if (iVar3 == 0) {
      cVar4 = ext_condition(0x1c);
      if (cVar4 != '\0') {
        halt_baddata();
      }
      if ((int)unaff_r19 <= unaff_r25) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    else {
      *(short *)(in_r12 + 8) = (short)param_3;
      FUN_ram_bfcf80ec(uVar2,unaff_r13);
FUN_ram_bfcf8118:
      if ((iVar3 == 0) && (!(bool)in_N)) {
        func_0xbfc90558();
      }
      cVar4 = ext_condition(0x1f);
      *(undefined2 *)(in_r12 + 6) = unaff_r15;
      if (cVar4 != '\0') {
        asm_instruction_08(0x17,param_6,0x38);
        asm_instruction_08(0x22,unaff_r17,0x3c0);
        asm_instruction_08(0x23,in_r9,0x4bf);
        iVar3 = asm_instruction_06(0x23,in_r56,0x12);
        cVar4 = iVar3 == 0;
        func_0xbfd0b85c();
        asm_instruction_08(0,in_r34,6);
        FUN_ram_bfd0a868();
        asm_instruction_08(8,in_mmid,0x31);
        if (cVar4 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        iVar3 = asm_instruction_08(0x10,in_r50,0x38);
        if (iVar3 == 0 || (bool)in_V != iVar3 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        func_0xbfd0b878();
        asm_instruction_08(0x10,in_mmid,0x32);
        asm_instruction_08(0x18,in_r50,0x36);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      cVar4 = ext_condition(0x1c);
      if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    unaff_r13 = *(int *)(in_r12 + 0x74);
    param_6 = asm_instruction_05(0x2d,param_6,0xc3);
    unaff_r19 = unaff_r19 & 0xfdffffff;
    if (unaff_r19 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar3 = unaff_r13;
    uVar1 = unaff_r19;
  } while ((bool)in_C || unaff_r19 == 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf8120) overlaps instruction at (ram,0xbfcf811e)
    */

void FUN_ram_bfcf8118(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  undefined4 in_r9;
  int in_r12;
  int iVar2;
  int unaff_r13;
  undefined2 unaff_r15;
  undefined4 unaff_r17;
  uint unaff_r19;
  int unaff_r25;
  int unaff_gp;
  undefined4 in_r34;
  undefined4 in_r50;
  undefined4 in_r56;
  undefined4 in_mmid;
  char cVar3;
  undefined1 in_N;
  undefined1 in_C;
  char in_V;
  
  do {
    if ((unaff_r13 == 0) && (!(bool)in_N)) {
      func_0xbfc90558();
    }
    cVar3 = ext_condition(0x1f);
    *(undefined2 *)(in_r12 + 6) = unaff_r15;
    if (cVar3 != '\0') {
      asm_instruction_08(0x17,param_6,0x38);
      asm_instruction_08(0x22,unaff_r17,0x3c0);
      asm_instruction_08(0x23,in_r9,0x4bf);
      iVar2 = asm_instruction_06(0x23,in_r56,0x12);
      cVar3 = iVar2 == 0;
      func_0xbfd0b85c();
      asm_instruction_08(0,in_r34,6);
      FUN_ram_bfd0a868();
      asm_instruction_08(8,in_mmid,0x31);
      if (cVar3 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar2 = asm_instruction_08(0x10,in_r50,0x38);
      if (iVar2 == 0 || (bool)in_V != iVar2 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      func_0xbfd0b878();
      asm_instruction_08(0x10,in_mmid,0x32);
      asm_instruction_08(0x18,in_r50,0x36);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar3 = ext_condition(0x1c);
    if (cVar3 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    while( true ) {
      unaff_r13 = *(int *)(in_r12 + 0x74);
      param_6 = asm_instruction_05(0x2d,param_6,0xc3);
      unaff_r19 = unaff_r19 & 0xfdffffff;
      in_N = (int)unaff_r19 < 0;
      if (unaff_r19 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (!(bool)in_C && unaff_r19 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      uVar1 = asm_instruction_06(0x20,(uint)*(ushort *)(unaff_gp + 0x1c),3);
      if (unaff_r13 != 0) break;
      cVar3 = ext_condition(0x1c);
      if (cVar3 != '\0') {
        halt_baddata();
      }
      if ((int)unaff_r19 <= unaff_r25) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    *(short *)(in_r12 + 8) = (short)param_3;
    FUN_ram_bfcf80ec(uVar1,unaff_r13);
  } while( true );
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd0b77a) overlaps instruction at (ram,0xbfd0b778)
    */

void FUN_ram_bfcf8178(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4,
                     int param_5,undefined4 param_6)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int in_r12;
  undefined4 unaff_r13;
  uint unaff_r14;
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  undefined4 unaff_r22;
  int unaff_gp;
  undefined4 in_r34;
  int in_r37;
  undefined4 in_r50;
  undefined4 in_r56;
  undefined4 in_mmid;
  undefined1 in_C;
  char in_V;
  
  do {
    if ((bool)in_C) {
      param_1 = func_0xbfd7b5b8();
    }
    in_r56 = asm_instruction_06(0x25,in_r56,0xfffffb15);
    uVar2 = asm_instruction_06(0x20,param_1,3);
    param_6 = asm_instruction_05(0x2d,param_6,0xc3);
    param_4 = param_4 & 0xfeffffff;
    cVar1 = ext_condition(0x1f);
    if (cVar1 != '\0') {
      asm_instruction_08(0x24,in_mmid,0x1f);
      asm_instruction_08(0x31,unaff_r17,0x3c0);
      func_0xbfd0a908(unaff_r14 - 1,*(undefined2 *)(unaff_r14 + 0xc),param_3,param_4);
      asm_instruction_08(0x20,unaff_r18,0x36);
      asm_instruction_06(0x1d,param_5,0x400);
      FUN_ram_bfd0a914();
      iVar3 = asm_instruction_08(0x20,in_r50,0x38);
      if (iVar3 == 0 || (bool)in_V != iVar3 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      FUN_ram_bfd0b920();
      asm_instruction_08(0x20,in_r34,6);
      cVar1 = *(char *)(*(ushort *)(unaff_gp + 0xc) + 0x1a);
      if (!(bool)in_V) {
        func_0xbfdfb3ac();
      }
      if (unaff_r14 != 0) {
        asm_instruction_08(0x1f,in_r37,0x570);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      do {
      } while (cVar1 == '\0');
      asm_instruction_08(0x17,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    param_1 = FUN_ram_bfcf8174(uVar2,unaff_r13);
    in_r37 = asm_instruction_05(0x2d,in_r37,0x1f0);
    unaff_r14 = (uint)*(ushort *)(in_r12 + 6);
    if (in_r37 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    param_5 = param_5 + -200;
  } while ((bool)in_C || in_r37 == 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf8458(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 extraout_r1;
  undefined4 in_r11;
  int unaff_gp;
  undefined1 in_Z;
  char in_N;
  undefined1 in_C;
  char in_V;
  
  FUN_ram_bfcf77cc(*(undefined4 *)(unaff_gp + 0x16c));
  if ((bool)in_Z || in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf7854();
  if (!(bool)in_C && !(bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar2 = asm_instruction_04(0x1d,in_r11,extraout_r1);
  FUN_ram_bfcf7b60(uVar2);
  cVar1 = ext_condition(0x12);
  FUN_ram_bfcf7ee8();
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x13);
  if (cVar1 == '\0') {
    FUN_ram_bfcf808c();
    cVar1 = ext_condition(0x1d);
    if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf85e8(void)

{
  int iVar1;
  undefined4 extraout_r1;
  int in_r3;
  undefined4 in_r11;
  undefined4 in_r12;
  undefined1 unaff_r13;
  int unaff_r14;
  undefined1 *puVar2;
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  undefined1 unaff_r20;
  int unaff_gp;
  undefined4 in_r36;
  byte in_r51;
  uint in_mhi;
  undefined4 in_lp_count;
  bool bVar3;
  undefined1 in_N;
  char cVar4;
  undefined1 in_C;
  
  cVar4 = ext_condition(0x17);
  if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = FUN_ram_bfcf7ce0();
  bVar3 = (in_mhi & ~(1 << (in_r51 & 0x1f))) == 0;
  if ((bool)in_N) {
    *(short *)(unaff_r14 + 6) = (short)iVar1;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((bool)in_C || bVar3) {
    asm_instruction_05(0xd,in_r12,unaff_r17);
    cVar4 = ext_condition(0x10);
    if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    puVar2 = (undefined1 *)asm_instruction_08(0,in_r36,unaff_r18);
    if (!(bool)in_C && !bVar3) {
      *(undefined1 *)(unaff_r14 + 0x12) = unaff_r13;
      *(short *)(*(ushort *)(unaff_r14 + 4) - 0xa4) = (short)unaff_r14;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *puVar2 = unaff_r20;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar4 = in_r3 - iVar1 < 0;
  func_0xbfcf79f0();
  if (cVar4 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(7,in_lp_count,0x22);
  cVar4 = ext_condition(0x1d);
  if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar4 = ext_condition(0x1d);
  if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar4 = ext_condition(0x1d);
  if (cVar4 == '\0') {
    FUN_ram_bfcf8e88();
    cVar4 = ext_condition(0x1d);
    if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar4 = ext_condition(0x1d);
    if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar4 = ext_condition(0x1d);
    if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar4 = ext_condition(0x14);
    if (cVar4 == '\0') {
      asm_instruction_04(0x1d,in_r11,extraout_r1);
      FUN_ram_bfcf9328(*(undefined1 *)(unaff_gp + -7));
      cVar4 = ext_condition(0x1d);
      if (cVar4 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf8610(void)

{
  char cVar1;
  undefined4 extraout_r1;
  undefined4 in_r8;
  undefined4 in_r11;
  int unaff_gp;
  
  asm_instruction_04(0x1d,in_r8,2);
  FUN_ram_bfcf8e88();
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x14);
  if (cVar1 == '\0') {
    asm_instruction_04(0x1d,in_r11,extraout_r1);
    FUN_ram_bfcf9328(*(undefined1 *)(unaff_gp + -7));
    cVar1 = ext_condition(0x1d);
    if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf8680(void)

{
  FUN_ram_bfcf8680();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



void FUN_ram_bfcf8694(void)

{
  FUN_ram_bfcf8694();
  FUN_ram_bfd090e6();
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf86c0(void)

{
  undefined4 in_r4;
  undefined4 in_r7;
  
  asm_instruction_08(1,in_r4,in_r7);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf8798(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf87bc(void)

{
  undefined4 in_r3;
  int in_r7;
  bool in_Z;
  char in_N;
  bool in_C;
  char in_V;
  
  if (!in_C && !in_Z) {
    thunk_EXT_FUN_ram_bff120fe(*(undefined4 *)(in_r7 + 0x70));
    return;
  }
  FUN_ram_bfcf7b38(in_r3);
  if (in_V == in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf885c(undefined2 param_1,undefined1 param_2)

{
  int in_r12;
  int unaff_r14;
  undefined4 in_r56;
  int iVar1;
  
  *(undefined1 *)(unaff_r14 + 0x1a) = param_2;
  iVar1 = asm_instruction_08(0x22,in_r56,0x38);
  *(char *)(unaff_r14 + 0x1a) = (char)unaff_r14 + -1;
  *(undefined2 *)(in_r12 + 4) = param_1;
  if (-1 < iVar1) {
    FUN_ram_bfcf7c64(param_1,unaff_r14 + -1);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf8b38(void)

{
  uint uVar1;
  undefined2 unaff_r14;
  undefined4 unaff_r20;
  int unaff_gp;
  
  uVar1 = (uint)*(ushort *)(unaff_gp + 8);
  *(undefined2 *)(uVar1 - 0x148) = unaff_r14;
  *(undefined2 *)(uVar1 - 0x1c8) = unaff_r14;
  *(undefined2 *)(uVar1 - 0xe4) = unaff_r14;
  *(undefined4 *)(uVar1 - 0xe4) = unaff_r20;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf8ba8(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int unaff_gp;
  
  cVar1 = ext_condition(0x1c);
  if (cVar1 == '\0') {
    asm_instruction_06(0,param_3,0);
    func_0xbfcf8c24(*(undefined2 *)(unaff_gp + 0x9a));
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



void FUN_ram_bfcf8c9c(void)

{
  FUN_ram_bfd10ec2();
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf8e88(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6)

{
  char cVar1;
  int unaff_r13;
  undefined2 unaff_r14;
  int unaff_r19;
  undefined4 unaff_r25;
  undefined4 uVar2;
  undefined4 in_r48;
  undefined4 uVar3;
  undefined4 in_r50;
  undefined4 in_r52;
  int iVar4;
  undefined1 in_r55;
  undefined4 in_r56;
  undefined4 in_mlo;
  undefined4 in_r61reserved;
  bool bVar5;
  
  asm_instruction_06(0x13,in_r50,0x3d);
  uVar2 = asm_instruction_08(0x31,unaff_r25,0x4bf);
  uVar3 = asm_instruction_06(0x11,in_r48,0x339);
  asm_instruction_08(0x25,uVar2,0x4bf);
  asm_instruction_06(0x25,in_r56,0x410);
  iVar4 = asm_instruction_07(0x1d,in_r52,in_r61reserved);
  bVar5 = iVar4 < 0;
  FUN_ram_bfcf8178(*(undefined1 *)(unaff_r13 + 0x1b));
  cVar1 = ext_condition(0x14);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!bVar5) {
    asm_instruction_04(0x2c,0xbfcf8ebc,0x1f);
    asm_instruction_06(0x31,uVar3,in_mlo);
    iVar4 = asm_instruction_05(0x3d,*(undefined4 *)(param_3 + 0x10),0xffffff21);
    *(undefined2 *)(*(int *)(iVar4 + 0x40) + -0xe4) = unaff_r14;
    FUN_ram_bfcf8044();
    asm_instruction_04(0x3c,param_6,0xc1);
    *(undefined1 *)(unaff_r19 + -0x70) = in_r55;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcf8f66) */
/* WARNING: Removing unreachable block (ram,0xbfcf8f6a) */

void FUN_ram_bfcf8f04(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7,uint param_8)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 extraout_r1;
  uint uVar3;
  int unaff_r13;
  int unaff_r14;
  uint unaff_r15;
  uint uVar4;
  int unaff_r19;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r38;
  undefined4 uVar5;
  int in_r48;
  int iVar6;
  undefined4 in_r52;
  undefined1 in_r55;
  undefined4 in_r56;
  undefined4 in_mlo;
  undefined4 in_r61reserved;
  bool bVar7;
  char in_V;
  undefined8 uVar8;
  
  uVar8 = CONCAT44(param_2,param_1);
  while( true ) {
    uVar2 = (undefined4)uVar8;
    cVar1 = ext_condition(0x1c);
    asm_instruction_08(2,in_r38,6);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (unaff_r14 == 0) break;
    *(undefined2 *)(in_r48 + -0x79) = (short)in_mlo;
    in_r48 = asm_instruction_06(0x27,(undefined2 *)(in_r48 + -0x79),in_mlo);
    do {
    } while (unaff_r14 == 0);
    uVar3 = (uint)*(byte *)((int)((ulonglong)uVar8 >> 0x20) + 0x13);
    if (in_r48 == 0 || (bool)in_V != in_r48 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar4 = unaff_r15 & 0x7ffff;
    if (unaff_r13 != 0) {
      uVar2 = *(undefined4 *)(unaff_gp + 0x110);
      uVar4 = param_8;
    }
    if (uVar4 != 0) {
      asm_instruction_08(0x22,in_r56,0x67f);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
    FUN_ram_bfcf80bc(uVar2);
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    unaff_r13 = *(int *)(uVar3 + 0x70);
    unaff_r25 = asm_instruction_08(0x32,unaff_r25,0x4bf);
    uVar8 = CONCAT44(extraout_r1,(uint)*(ushort *)(unaff_gp + 0xc0));
    cVar1 = ext_condition(0x12);
    if (cVar1 != '\0') {
      uVar8 = func_0xbfd5d3a0();
    }
    unaff_r15 = 0;
  }
  uVar5 = asm_instruction_06(0x11,in_r48,0x339);
  asm_instruction_08(0x25,unaff_r25,0x4bf);
  asm_instruction_06(0x25,in_r56,0x410);
  iVar6 = asm_instruction_07(0x1d,in_r52,in_r61reserved);
  bVar7 = iVar6 < 0;
  FUN_ram_bfcf8178(uVar2);
  cVar1 = ext_condition(0x14);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (bVar7) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_04(0x2c,0xbfcf8ebc,0x1f);
  asm_instruction_06(0x31,uVar5,in_mlo);
  iVar6 = asm_instruction_05(0x3d,*(undefined4 *)(param_3 + 0x10),0xffffff21);
  *(undefined2 *)(*(int *)(iVar6 + 0x40) + -0xe4) = 0;
  FUN_ram_bfcf8044();
  asm_instruction_04(0x3c,param_6,0xc1);
  *(undefined1 *)(unaff_r19 + -0x70) = in_r55;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf903c(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  uint extraout_r1;
  undefined4 extraout_r1_00;
  int iVar4;
  uint in_r7;
  uint uVar5;
  short sVar6;
  uint unaff_r13;
  int unaff_r14;
  uint unaff_r15;
  int unaff_r17;
  undefined4 unaff_r20;
  int unaff_r25;
  int unaff_gp;
  undefined2 *in_r48;
  int in_r52;
  undefined2 in_mlo;
  char in_Z;
  undefined1 in_C;
  undefined1 in_V;
  
  while( true ) {
    if (unaff_r15 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0,(uint)*(byte *)(unaff_gp + 0x84),0xf);
    thunk_FUN_ram_bfd090b8(*(undefined2 *)(param_3 + 6));
    iVar2 = asm_instruction_06(0,param_3,8);
    iVar4 = asm_instruction_06(0,param_3,0xc);
    if (in_r7 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    sVar1 = *(short *)(in_r52 + -0xda);
    sVar6 = (short)iVar4 + 2;
    if (unaff_r13 == 0) {
      uRam00000015 = (undefined1)iVar2;
      *(char *)(iVar2 + 0xd) = (char)iVar4;
      if (!(bool)in_V) {
        iVar2 = func_0xbfce8c34(iVar2,extraout_r1 & ~unaff_r13);
      }
      asm_instruction_06(0,iVar2,0x203);
      halt_baddata();
    }
    if ((bool)in_C || (bool)in_Z) break;
    iVar2 = *(int *)(iVar4 + 0x10);
    uVar5 = in_r7;
    thunk_EXT_FUN_ram_c055a1f0(*(undefined4 *)(unaff_r13 + 0x68));
    if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    FUN_ram_bfcf86e8();
    uVar3 = asm_instruction_06(0x12,iVar4,1);
    param_3 = DAT_ram_bfcf91d0;
                    /* WARNING: Call to offcut address within same function */
    func_0xbfcf9088(uVar3);
    *(short *)(unaff_r14 + 0x24) = sVar6;
    FUN_ram_bfcf903c();
    if (iVar2 == 0) {
      asm_instruction_08(0x22,unaff_r25,0x4bf);
      in_r48[-0x4f] = in_mlo;
      asm_instruction_08(0x23,extraout_r1_00,0x40);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if ((bool)in_Z) {
      func_0xbfcd34ac();
    }
    FUN_ram_bfcf9090();
    unaff_r13 = *(uint *)(param_4 + 0x60);
    unaff_r17 = asm_instruction_08(0x23,unaff_r17,0x3c0);
    *(undefined4 *)(int)sVar1 = unaff_r20;
    unaff_r15 = in_r7 & 0x7ffff;
    if (unaff_r17 != 0) {
      func_0xbfd7c42c(*(undefined2 *)(unaff_gp + 0xba));
    }
    in_r48 = in_r48 + -0x4f;
    *in_r48 = in_mlo;
    unaff_r25 = asm_instruction_08(0x22,unaff_r25,0x4bf);
    in_Z = unaff_r25 == 0;
    in_r7 = uVar5;
  }
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9090(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint extraout_r1;
  undefined4 extraout_r1_00;
  int iVar3;
  uint uVar4;
  uint in_r7;
  short sVar5;
  uint uVar6;
  int unaff_r13;
  int unaff_r14;
  uint unaff_r15;
  undefined4 *unaff_r16;
  int unaff_r17;
  undefined4 unaff_r20;
  int unaff_r25;
  int unaff_gp;
  undefined2 *in_r48;
  int in_r52;
  undefined2 in_mlo;
  char in_Z;
  undefined1 in_C;
  undefined1 in_V;
  
  while( true ) {
    FUN_ram_bfcf903c();
    if (unaff_r13 == 0) {
      asm_instruction_08(0x22,unaff_r25,0x4bf);
      in_r48[-0x4f] = in_mlo;
      asm_instruction_08(0x23,extraout_r1_00,0x40);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar4 = in_r7;
    if ((bool)in_Z) {
      func_0xbfcd34ac();
      uVar4 = in_r7;
    }
    FUN_ram_bfcf9090();
    uVar6 = *(uint *)(param_4 + 0x60);
    unaff_r17 = asm_instruction_08(0x23,unaff_r17,0x3c0);
    *unaff_r16 = unaff_r20;
    if (unaff_r17 != 0) {
      func_0xbfd7c42c(*(undefined2 *)(unaff_gp + 0xba));
    }
    in_r48 = in_r48 + -0x4f;
    *in_r48 = in_mlo;
    unaff_r25 = asm_instruction_08(0x22,unaff_r25,0x4bf);
    in_Z = unaff_r25 == 0;
    if ((unaff_r15 & 0x7ffff) != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0,(uint)*(byte *)(unaff_gp + 0x84),0xf);
    thunk_FUN_ram_bfd090b8(*(undefined2 *)(param_3 + 6));
    iVar1 = asm_instruction_06(0,param_3,8);
    iVar3 = asm_instruction_06(0,param_3,0xc);
    if (uVar4 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    unaff_r16 = (undefined4 *)(int)*(short *)(in_r52 + -0xda);
    sVar5 = (short)iVar3 + 2;
    if (uVar6 == 0) break;
    if ((bool)in_C || (bool)in_Z) {
      halt_baddata();
    }
    unaff_r13 = *(int *)(iVar3 + 0x10);
    in_r7 = uVar4;
    thunk_EXT_FUN_ram_c055a1f0(*(undefined4 *)(uVar6 + 0x68));
    if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    FUN_ram_bfcf86e8();
    uVar2 = asm_instruction_06(0x12,iVar3,1);
    param_3 = DAT_ram_bfcf91d0;
                    /* WARNING: Call to offcut address within same function */
    func_0xbfcf9088(uVar2);
    *(short *)(unaff_r14 + 0x24) = sVar5;
    unaff_r15 = uVar4;
  }
  uRam00000015 = (undefined1)iVar1;
  *(char *)(iVar1 + 0xd) = (char)iVar3;
  if (!(bool)in_V) {
    iVar1 = func_0xbfce8c34(iVar1,extraout_r1 & ~uVar6);
  }
  asm_instruction_06(0,iVar1,0x203);
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf913c(undefined4 param_1,undefined4 param_2)

{
  undefined4 unaff_r25;
  int in_r48;
  undefined4 in_r52;
  
  *(undefined4 *)(in_r48 + -0x100) = in_r52;
  asm_instruction_08(0x30,unaff_r25,0x4bf);
  asm_instruction_08(0x28,param_2,0xffffffef);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf91d4(void)

{
  bool in_N;
  
  if (!in_N) {
    FUN_ram_bfcf9364();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf92a8(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 in_r12;
  int unaff_r13;
  int unaff_r14;
  int unaff_r15;
  undefined4 unaff_r17;
  int iVar2;
  undefined4 unaff_r25;
  undefined4 in_r37;
  undefined4 in_r42;
  undefined4 in_r44;
  int in_r52;
  bool in_Z;
  bool in_C;
  bool in_V;
  
  if (unaff_r15 == 0) {
    asm_instruction_06(0x20,param_3,1);
    *(undefined4 *)(unaff_r14 + 0x70) = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x24,param_2,0xfffff803);
  uVar1 = asm_instruction_06(4,param_1,0xfffffa54);
  *(undefined4 *)(unaff_r14 + 0x58) = in_r12;
  do {
  } while (unaff_r14 != 0);
  if (!in_C && !in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(char *)(unaff_r13 + 8) = (char)uVar1;
  iVar2 = asm_instruction_08(0x31,unaff_r25,0x4bf);
  uVar1 = asm_instruction_08(0x22,*(undefined4 *)(in_r52 + -0xaf),*(undefined4 *)(in_r52 + -0xaf));
  if (iVar2 != 0 && in_V == iVar2 < 0) {
    asm_instruction_08(0x32,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!in_V) {
    func_0xbfc9c760(uVar1);
  }
  asm_instruction_04(0x3d,in_r42,1);
  asm_instruction_08(0x1f,in_r37,0xfffffa70);
  asm_instruction_05(0x24,in_r44,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9304(undefined4 param_1,uint param_2,undefined4 param_3,int param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7,int param_8)

{
  char cVar1;
  uint extraout_r1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r12;
  int iVar4;
  uint unaff_r13;
  int unaff_r14;
  int unaff_r15;
  undefined4 unaff_r17;
  undefined4 unaff_r25;
  undefined4 uVar5;
  int unaff_gp;
  undefined4 in_r37;
  undefined4 in_r42;
  undefined4 in_r44;
  undefined4 in_r48;
  int iVar6;
  undefined4 uVar7;
  undefined4 in_r50;
  int in_r52;
  undefined4 in_lp_count;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 in_C;
  undefined1 in_V;
  undefined4 in_stack_00000040;
  uint extraout_r1_00;
  
  iVar6 = asm_instruction_06(0x12,in_r48,0);
  uVar8 = iVar6 == 0;
  uVar9 = iVar6 < 0;
  if (!(bool)in_V) {
    param_1 = func_0xbfde8fa8(param_1,param_2 & ~unaff_r13);
  }
  if ((unaff_r15 != 0) && (param_1 = FUN_ram_bfcf8458(), (bool)in_C || (bool)uVar8)) {
    if ((bool)in_C || (bool)uVar8) {
      *(undefined4 *)(unaff_r14 + 0x58) = in_r12;
      do {
      } while (unaff_r14 != 0);
      if ((bool)in_C || (bool)uVar8) {
        *(char *)(unaff_r13 + 8) = (char)param_1;
        iVar6 = asm_instruction_08(0x31,unaff_r25,0x4bf);
        uVar3 = asm_instruction_08(0x22,*(undefined4 *)(in_r52 + -0xaf),
                                   *(undefined4 *)(in_r52 + -0xaf));
        if (iVar6 == 0 || (bool)in_V != iVar6 < 0) {
          if (!(bool)in_V) {
            func_0xbfc9c760(uVar3);
          }
          asm_instruction_04(0x3d,in_r42,1);
          asm_instruction_08(0x1f,in_r37,0xfffffa70);
          asm_instruction_05(0x24,in_r44,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        asm_instruction_08(0x32,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    else {
      asm_instruction_06(0x12,in_r8,0x20);
      if (!(bool)in_C && !(bool)uVar8) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf948c(param_1,(int)*(short *)(param_4 + 0x3a));
  if ((bool)uVar9) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_04(0x28,in_r37,param_7);
  iVar4 = asm_instruction_06(0x23,iVar6,0x35);
  if (iVar4 != 0) {
    cVar1 = ext_condition(0x18);
    if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf9304(*(undefined1 *)(unaff_r13 + 9));
  uVar5 = asm_instruction_08(0x24,unaff_r25,0x4bf);
  uVar7 = asm_instruction_06(4,iVar6,0x334);
  asm_instruction_07(0x1d,in_r52,in_lp_count);
  uVar3 = *(undefined4 *)(unaff_gp + 0x114);
  if (unaff_r14 != 0) {
    asm_instruction_07(0xe,in_r50,0x33a);
    asm_instruction_06(0x11,uVar7,0);
    uVar2 = extraout_r1 & ~unaff_r13;
    if (!(bool)in_V) {
      func_0xbfde8ff4();
      uVar2 = extraout_r1_00;
    }
    if (param_8 != 0) {
      asm_instruction_08(0x22,uVar5,0xffffffff);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_08(0x23,in_r9,0);
    uVar3 = in_stack_00000040;
    if (uVar2 == 0) {
      uVar3 = asm_instruction_08(0x24,0,0x40);
      FUN_ram_bfcf9578(in_stack_00000040,uVar3);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  *(undefined4 *)uVar3 = uVar3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9320(void)

{
  char cVar1;
  uint extraout_r1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 in_r6;
  int in_r7;
  undefined4 in_r9;
  int iVar4;
  uint unaff_r13;
  int unaff_r14;
  undefined4 unaff_r25;
  undefined4 uVar5;
  int unaff_gp;
  undefined4 in_r37;
  undefined4 in_r48;
  undefined4 uVar6;
  undefined4 in_r50;
  undefined4 in_r52;
  undefined4 in_lp_count;
  undefined1 in_V;
  undefined4 in_stack_00000040;
  uint extraout_r1_00;
  
  asm_instruction_04(0x28,in_r37,in_r6);
  iVar4 = asm_instruction_06(0x23,in_r48,0x35);
  if (iVar4 == 0) {
    FUN_ram_bfcf9304(*(undefined1 *)(unaff_r13 + 9));
    uVar5 = asm_instruction_08(0x24,unaff_r25,0x4bf);
    uVar6 = asm_instruction_06(4,in_r48,0x334);
    asm_instruction_07(0x1d,in_r52,in_lp_count);
    uVar3 = *(undefined4 *)(unaff_gp + 0x114);
    if (unaff_r14 != 0) {
      asm_instruction_07(0xe,in_r50,0x33a);
      asm_instruction_06(0x11,uVar6,0);
      uVar2 = extraout_r1 & ~unaff_r13;
      if (!(bool)in_V) {
        func_0xbfde8ff4();
        uVar2 = extraout_r1_00;
      }
      if (in_r7 != 0) {
        asm_instruction_08(0x22,uVar5,0xffffffff);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_08(0x23,in_r9,0);
      uVar3 = in_stack_00000040;
      if (uVar2 == 0) {
        uVar3 = asm_instruction_08(0x24,0,0x40);
        FUN_ram_bfcf9578(in_stack_00000040,uVar3);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    *(undefined4 *)uVar3 = uVar3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x18);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9328(void)

{
  char cVar1;
  uint extraout_r1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 in_r6;
  int in_r7;
  undefined4 in_r9;
  int iVar4;
  uint unaff_r13;
  int unaff_r14;
  undefined4 unaff_r25;
  undefined4 uVar5;
  int unaff_gp;
  undefined4 in_r37;
  undefined4 in_r48;
  undefined4 uVar6;
  undefined4 in_r50;
  undefined4 in_r52;
  undefined4 in_lp_count;
  undefined1 in_V;
  undefined4 in_stack_00000040;
  uint extraout_r1_00;
  
  asm_instruction_04(0x28,in_r37,in_r6);
  iVar4 = asm_instruction_06(0x23,in_r48,0x35);
  if (iVar4 == 0) {
    FUN_ram_bfcf9304();
    uVar5 = asm_instruction_08(0x24,unaff_r25,0x4bf);
    uVar6 = asm_instruction_06(4,in_r48,0x334);
    asm_instruction_07(0x1d,in_r52,in_lp_count);
    uVar3 = *(undefined4 *)(unaff_gp + 0x114);
    if (unaff_r14 != 0) {
      asm_instruction_07(0xe,in_r50,0x33a);
      asm_instruction_06(0x11,uVar6,0);
      uVar2 = extraout_r1 & ~unaff_r13;
      if (!(bool)in_V) {
        func_0xbfde8ff4();
        uVar2 = extraout_r1_00;
      }
      if (in_r7 != 0) {
        asm_instruction_08(0x22,uVar5,0xffffffff);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_08(0x23,in_r9,0);
      uVar3 = in_stack_00000040;
      if (uVar2 == 0) {
        uVar3 = asm_instruction_08(0x24,0,0x40);
        FUN_ram_bfcf9578(in_stack_00000040,uVar3);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    *(undefined4 *)uVar3 = uVar3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x18);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9364(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 in_r9;
  undefined4 in_stack_00000040;
  
  asm_instruction_08(0x23,in_r9,0);
  if (param_2 == 0) {
    uVar1 = asm_instruction_08(0x24,0,0x40);
    FUN_ram_bfcf9578(in_stack_00000040,uVar1);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined4 *)in_stack_00000040 = in_stack_00000040;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf937c(int param_1)

{
  bool in_Z;
  
  *(int *)(param_1 + 0x20) = param_1;
  if (!in_Z) {
    func_0xbfd7c820();
  }
  thunk_EXT_FUN_ram_bfee8820();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcf948c(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r17;
  undefined4 unaff_r25;
  int iVar3;
  bool in_C;
  
  uVar2 = *(undefined1 *)(unaff_r13 + 2);
  iVar3 = asm_instruction_08(0x31,unaff_r25,0x4bf);
  *(undefined4 *)(param_1 + -0x390) = unaff_r17;
  if (unaff_r14 == 0) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  if (!in_C && iVar3 != 0) {
    asm_instruction_06(0x3c,param_1,0x611);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x12);
  if (cVar1 != '\0') {
    FUN_ram_bfcfa108(param_1,uVar2);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf94e0(void)

{
  char cVar1;
  uint uVar2;
  int in_r7;
  int in_r12;
  int unaff_r13;
  undefined1 unaff_r15;
  undefined4 unaff_r17;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r48;
  undefined4 in_r56;
  int iVar3;
  undefined1 uVar4;
  char cVar5;
  char in_V;
  
  FUN_ram_bfcf9320();
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  asm_instruction_06(2,in_r48,8);
  func_0xbfcf8674(*(undefined2 *)(unaff_gp + 0xc));
  FUN_ram_bfcf94dc();
  iVar3 = asm_instruction_08(0x23,in_r56,0x27e);
  uVar4 = iVar3 == 0;
  cVar5 = iVar3 < 0;
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined1 *)(unaff_r13 + 0x19) = unaff_r15;
  uVar2 = (uint)*(ushort *)(unaff_gp + 0x1c4);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    uVar2 = func_0xbfcf20fc(uVar2,unaff_r13 + 2);
  }
  if (!(bool)uVar4 && in_V == cVar5) {
    FUN_ram_bfcf9648(uVar2 + 4);
    asm_instruction_08(0x22,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
    *(short *)(in_r12 + 8) = (short)*(undefined4 *)(in_r12 + 0x14);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined4 *)(in_r7 + 0xc3) = in_r48;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9560(int param_1,undefined4 param_2,undefined1 param_3)

{
  int unaff_r14;
  
  *(undefined1 *)(param_1 + 0xd) = param_3;
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9578(undefined4 param_1)

{
  short sVar1;
  undefined4 uVar2;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r17;
  
  sVar1 = *(short *)(unaff_r14 + 0xc);
  uVar2 = asm_instruction_06(4,param_1,0x408);
  *(char *)(unaff_r13 + 8) = (char)uVar2;
  asm_instruction_08(0x23,unaff_r17,0x200);
  FUN_ram_bfcf8690(uVar2,(int)sVar1);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9648(int param_1)

{
  int unaff_r13;
  undefined2 unaff_r21;
  undefined4 unaff_r25;
  int iVar1;
  bool in_Z;
  undefined1 uVar2;
  char in_N;
  char cVar3;
  char in_V;
  
  *(undefined2 *)(param_1 + -0x108) = unaff_r21;
  if (in_Z || in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = asm_instruction_08(0x23,unaff_r25,0x4bf);
  uVar2 = iVar1 == 0;
  cVar3 = iVar1 < 0;
  iVar1 = FUN_ram_bfcf9760();
  FUN_ram_bfcf8798(iVar1 + 4);
  if (!(bool)uVar2 && in_V == cVar3) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  do {
  } while (unaff_r13 == 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9674(void)

{
  int iVar1;
  undefined4 unaff_r17;
  
  iVar1 = FUN_ram_bfcf9780();
  asm_instruction_08(0x30,unaff_r17,0x200);
  FUN_ram_bfcf87bc(iVar1 + 4);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcf96b6) */

void FUN_ram_bfcf968c(int param_1,int param_2,undefined1 param_3)

{
  int unaff_r14;
  bool in_V;
  
  *(undefined1 *)(param_1 + 0xd) = param_3;
  if (unaff_r14 == 0) {
    *(undefined1 *)(param_1 + 0xd) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(char *)(param_2 + 0x18) = (char)unaff_r14;
  *(undefined1 *)(param_1 + 0xd) = param_3;
  if (!in_V) {
    func_0xbfde9294();
  }
  if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf885c();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9698(int param_1,undefined4 param_2,undefined1 param_3)

{
  int unaff_r14;
  
  *(undefined1 *)(param_1 + 0xd) = param_3;
  if (unaff_r14 != 0) {
    FUN_ram_bfcf885c();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf96e4(void)

{
  undefined4 in_r8;
  undefined4 unaff_r25;
  
  asm_instruction_08(0x23,unaff_r25,0x43f);
  asm_instruction_06(0x23,in_r8,0x1b);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9760(void)

{
  undefined4 in_r3;
  undefined4 in_r6;
  
  asm_instruction_05(0x1d,in_r6,in_r3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf981c) overlaps instruction at (ram,0xbfcf981a)
    */
/* WARNING: Removing unreachable block (ram,0xbfcf97ca) */
/* WARNING: Removing unreachable block (ram,0xbfcf97ce) */
/* WARNING: Removing unreachable block (ram,0xbfcf97d0) */

void FUN_ram_bfcf9780(uint param_1,uint param_2,int param_3,undefined4 param_4,undefined4 param_5,
                     undefined4 param_6,undefined4 param_7,int param_8)

{
  char cVar1;
  uint extraout_r1;
  int iVar2;
  undefined4 in_r12;
  uint uVar3;
  int iVar4;
  int unaff_r14;
  int unaff_r15;
  int unaff_r17;
  undefined4 unaff_r25;
  undefined4 uVar5;
  int unaff_gp;
  undefined4 in_r40;
  undefined4 in_r56;
  int iVar6;
  undefined4 in_mmid;
  undefined1 uVar7;
  undefined1 in_V;
  undefined8 uVar8;
  
  asm_instruction_05(0xd,in_r12,in_r40);
  uVar3 = *(uint *)(param_3 + 0x24);
  uVar5 = asm_instruction_08(0x31,unaff_r25,0x4bf);
  iVar6 = asm_instruction_06(0x11,in_r56,0xfffff80f);
  do {
    uVar8 = CONCAT44(param_2 & ~uVar3,param_1);
    iVar2 = param_8;
    if (!(bool)in_V) {
      uVar8 = func_0xbfde942c();
      iVar2 = param_8;
    }
    if (unaff_r15 == 0) {
      FUN_ram_bfd1214a();
      return;
    }
    uVar5 = asm_instruction_08(0x32,uVar5,0x4bf);
    iVar6 = asm_instruction_06(0x12,iVar6,0xf);
    uVar7 = iVar6 == 0;
    uVar8 = CONCAT44((uint)((ulonglong)uVar8 >> 0x20) & ~uVar3,(int)uVar8);
    if (!(bool)in_V) {
      uVar8 = func_0xbfde943c();
    }
    while( true ) {
      param_2 = (uint)((ulonglong)uVar8 >> 0x20);
      if (unaff_r15 != 0) {
        if (!(bool)uVar7) {
          func_0xbfc61c38((int)uVar8,(int)*(short *)(param_2 + 0x1a));
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      cVar1 = ext_condition(0x1c);
      param_8 = iVar2;
      if (cVar1 != '\0') {
        func_0xbfd22424();
        param_2 = extraout_r1;
        param_8 = iVar2;
      }
      iVar4 = *(int *)(param_3 + 0x10);
      param_1 = (uint)*(byte *)(iVar4 + 0xc);
      uVar8 = CONCAT44(param_2,param_1);
      if (iVar4 == 0) break;
      *(char *)(param_1 + 0xd) = (char)param_3;
      if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      unaff_r17 = asm_instruction_08(0x23,unaff_r17,0x3c0);
      uVar7 = unaff_r17 == 0;
      iVar2 = param_8;
      if ((bool)in_V) {
        uVar8 = func_0xbfc94438();
      }
      unaff_r15 = iVar2;
      if (iVar4 != 0) {
        *(int *)(iVar6 + -0xaf) = param_8;
        iVar6 = asm_instruction_06(0x14,in_mmid,0xf);
        if (param_8 == 0) {
          if (iVar6 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
        }
        else {
          asm_instruction_08(0x22,(uint)*(byte *)(unaff_gp + 0x85),0xfffffb06);
          asm_instruction_08(0x22,uVar5,0x4bf);
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    uVar3 = 0;
    if ((bool)uVar7) {
      asm_instruction_08(0x23,param_1,0x548);
      asm_instruction_05(0x3d,0,0x92);
      asm_instruction_05(0x1d,param_7,param_4);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  } while( true );
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf981c) overlaps instruction at (ram,0xbfcf981a)
    */
/* WARNING: Removing unreachable block (ram,0xbfcf97ca) */
/* WARNING: Removing unreachable block (ram,0xbfcf97ce) */
/* WARNING: Removing unreachable block (ram,0xbfcf97d0) */

void FUN_ram_bfcf9794(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7,int param_8)

{
  char cVar1;
  uint uVar2;
  int extraout_r1;
  int iVar3;
  uint unaff_r13;
  int iVar4;
  int unaff_r14;
  int unaff_r15;
  int unaff_r17;
  undefined4 unaff_r25;
  int unaff_gp;
  int in_r56;
  undefined4 in_mmid;
  int iVar5;
  undefined1 uVar6;
  undefined1 in_V;
  undefined8 uVar7;
  
  uVar7 = CONCAT44(param_2,param_1);
  do {
    if (unaff_r15 == 0) {
      FUN_ram_bfd1214a();
      return;
    }
    unaff_r25 = asm_instruction_08(0x32,unaff_r25,0x4bf);
    in_r56 = asm_instruction_06(0x12,in_r56,0xf);
    uVar6 = in_r56 == 0;
    uVar7 = CONCAT44((uint)((ulonglong)uVar7 >> 0x20) & ~unaff_r13,(int)uVar7);
    if (!(bool)in_V) {
      uVar7 = func_0xbfde943c();
    }
    while( true ) {
      iVar5 = (int)((ulonglong)uVar7 >> 0x20);
      if (unaff_r15 != 0) {
        if (!(bool)uVar6) {
          func_0xbfc61c38((int)uVar7,(int)*(short *)(iVar5 + 0x1a));
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      cVar1 = ext_condition(0x1c);
      iVar3 = param_8;
      if (cVar1 != '\0') {
        func_0xbfd22424();
        iVar5 = extraout_r1;
        iVar3 = param_8;
      }
      iVar4 = *(int *)(param_3 + 0x10);
      uVar2 = (uint)*(byte *)(iVar4 + 0xc);
      uVar7 = CONCAT44(iVar5,uVar2);
      param_8 = iVar3;
      if (iVar4 == 0) break;
      *(char *)(uVar2 + 0xd) = (char)param_3;
      if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      unaff_r17 = asm_instruction_08(0x23,unaff_r17,0x3c0);
      uVar6 = unaff_r17 == 0;
      if ((bool)in_V) {
        uVar7 = func_0xbfc94438();
      }
      unaff_r15 = param_8;
      if (iVar4 != 0) {
        *(int *)(in_r56 + -0xaf) = iVar3;
        iVar5 = asm_instruction_06(0x14,in_mmid,0xf);
        if (iVar3 == 0) {
          if (iVar5 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
        }
        else {
          asm_instruction_08(0x22,(uint)*(byte *)(unaff_gp + 0x85),0xfffffb06);
          asm_instruction_08(0x22,unaff_r25,0x4bf);
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    if ((bool)uVar6) {
      asm_instruction_08(0x23,uVar2,0x548);
      asm_instruction_05(0x3d,0,0x92);
      asm_instruction_05(0x1d,param_7,param_4);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    unaff_r13 = 0;
    if (!(bool)in_V) {
      uVar7 = func_0xbfde942c();
      param_8 = iVar3;
    }
  } while( true );
}



void FUN_ram_bfcf97c8(undefined2 param_1)

{
  int in_r7;
  int in_r12;
  int unaff_r15;
  
  if (unaff_r15 != 0) {
    do {
    } while (in_r7 != 0);
    *(undefined2 *)(in_r12 + 4) = param_1;
  }
  FUN_ram_bfd1214a();
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9890(void)

{
  undefined2 uVar1;
  undefined4 in_r4;
  int in_r12;
  uint unaff_r13;
  int unaff_r15;
  undefined4 unaff_r25;
  undefined4 uVar2;
  undefined4 in_r56;
  undefined4 uVar3;
  int iVar4;
  undefined4 in_mmid;
  undefined1 uVar5;
  undefined1 in_V;
  undefined8 uVar6;
  
  uVar2 = DAT_ram_bfcf996c;
  uVar6 = thunk_EXT_FUN_ram_bfd6a37c();
  uVar1 = (undefined2)uVar2;
  uVar2 = asm_instruction_08(0x34,unaff_r25,0x4bf);
  uVar3 = asm_instruction_06(0x14,in_r56,0xfffff80f);
  uVar6 = CONCAT44((uint)((ulonglong)uVar6 >> 0x20) & ~unaff_r13,(int)uVar6);
  if (!(bool)in_V) {
    uVar6 = func_0xbfde953c();
  }
  if (unaff_r15 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x33,uVar2,0x4bf);
  iVar4 = asm_instruction_06(0x13,uVar3,0xf);
  uVar5 = iVar4 == 0;
  if (!(bool)in_V) {
    func_0xbfde954c((int)uVar6,(uint)((ulonglong)uVar6 >> 0x20) & ~unaff_r13);
  }
  if (unaff_r15 != 0) {
    asm_instruction_06(0x1c,in_r4,10);
    asm_instruction_06(0x13,in_mmid,0xf);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!(bool)uVar5) {
    func_0xbfcd3d30();
  }
  *(undefined2 *)(in_r12 + 6) = uVar1;
  FUN_ram_bfd12116();
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9a1c(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 in_r10;
  int in_r12;
  
  *(undefined4 *)(param_3 + -0xc4) = in_r10;
  *(short *)(in_r12 + 0x22) = (short)(undefined4 *)(param_3 + -0xc4);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9ae8(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  undefined2 uVar3;
  int in_r12;
  undefined4 *puVar4;
  int unaff_r14;
  uint unaff_r15;
  uint uVar5;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r56;
  undefined4 uVar6;
  int iVar7;
  undefined4 in_mmid;
  undefined1 uVar8;
  undefined1 in_V;
  undefined8 uVar9;
  
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  puVar4 = *(undefined4 **)(param_3 + 0x24);
  uVar9 = FUN_ram_bfcf94e0(*(undefined1 *)(in_r12 + 3));
  uVar3 = (undefined2)*puVar4;
  cVar1 = ext_condition(0x11);
  uVar5 = unaff_r15 & 0x7ffff;
  if (cVar1 != '\0') {
    uVar9 = func_0xbfd7d154();
  }
  uVar6 = asm_instruction_06(0x11,in_r56,0xfffff80f);
  uVar9 = CONCAT44((uint)((ulonglong)uVar9 >> 0x20) & ~(uint)puVar4,(int)uVar9);
  if (!(bool)in_V) {
    uVar9 = func_0xbfde979c();
  }
  iVar2 = (int)uVar9;
  if (uVar5 != 0) {
    asm_instruction_08(0x32,unaff_r25,0x4bf);
    iVar7 = asm_instruction_06(0x12,uVar6,0xf);
    uVar8 = iVar7 == 0;
    if (!(bool)in_V) {
      iVar2 = func_0xbfde97ac(iVar2,(uint)((ulonglong)uVar9 >> 0x20) & ~(uint)puVar4);
    }
    if (uVar5 == 0) {
      *(char *)((int)puVar4 + 7) = (char)iVar2;
      cVar1 = ext_condition(0x13);
      if (cVar1 != '\0') {
        iVar2 = FUN_ram_bfcf2798();
      }
      if ((!(bool)uVar8) && (iVar2 = func_0xbfc5a7f0(), (bool)uVar8 == false)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      *(int *)(iVar2 + 0x3c) = iVar2;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    do {
    } while (puVar4 == (undefined4 *)0x0);
    *(uint *)(iVar7 + -0xaf) = uVar5;
    asm_instruction_06(0x11,in_mmid,0xfffff80f);
    asm_instruction_06(0x12,iVar7,0xf);
    uVar6 = *(undefined4 *)(unaff_gp + 0x114);
    if (uVar5 == 0) {
      *(undefined2 *)(*(int *)(unaff_r14 + 0x20) + 6) = uVar3;
      FUN_ram_bfd12352(uVar6);
      return;
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9b68(void)

{
  char cVar1;
  undefined4 *unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r20;
  int unaff_gp;
  
  asm_instruction_08(0x23,unaff_r17,0x3c0);
  *unaff_r16 = unaff_r20;
  FUN_ram_bfcf9be0(*(undefined2 *)(unaff_gp + 8));
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
    func_0xbfd3ffb8(unaff_gp + -0x160);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9be0(undefined4 param_1)

{
  char in_Z;
  char in_N;
  char in_V;
  
  if (in_V == in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_Z != '\0') {
    asm_instruction_06(0x20,param_1,3);
    asm_instruction_06(0x20,param_1,2);
    FUN_ram_bfd11cf4();
    return;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf9cce) overlaps instruction at (ram,0xbfcf9ccc)
    */
/* WARNING: Removing unreachable block (ram,0xbfcf9cfa) */

void FUN_ram_bfcf9c38(int param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5,
                     undefined4 param_6,undefined4 param_7,int param_8)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  undefined4 extraout_r1;
  undefined2 *puVar4;
  undefined1 uVar5;
  uint uVar6;
  int unaff_r13;
  int unaff_r14;
  int unaff_r16;
  ushort *unaff_r20;
  ushort *puVar7;
  undefined4 unaff_r25;
  undefined4 uVar8;
  int unaff_gp;
  undefined4 in_r48;
  undefined4 in_r50;
  ushort *in_r52;
  undefined4 in_lp_count;
  undefined1 in_C;
  undefined8 uVar9;
  
  puVar4 = *(undefined2 **)(param_4 + 4);
  uVar2 = *unaff_r20;
  *(char *)(param_1 + -0xa4) = (char)unaff_r13;
  *(char *)(param_1 + -0xa4) = (char)unaff_r13;
  *(short *)(param_1 + -0xa4) = (short)unaff_r13;
  puVar7 = unaff_r20 + 0xa0;
  *(short *)(param_1 + -0xa4) = (short)unaff_r13;
  uVar5 = (undefined1)*(undefined2 *)(unaff_r13 + 0x20);
  if (unaff_r14 == 0) {
    uVar8 = *(undefined4 *)(unaff_r13 + 0x74);
code_r0xbfcf9cb2:
    FUN_ram_bfcf9e20(param_1,uVar8);
    asm_instruction_05(0x2d,param_6,extraout_r1);
    *puVar4 = (short)(puVar7 + 0x28);
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    do {
      *(undefined1 *)(unaff_r13 + 0x1b) = uVar5;
      unaff_r25 = asm_instruction_08(0x24,unaff_r25,0x4bf);
    } while (unaff_r13 != 0);
    *(ushort **)(unaff_r16 + 0x1c0) = puVar7 + 0x28;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar8 = asm_instruction_08(0x22,unaff_r25,0x4bf);
  uVar6 = (uint)*in_r52;
  *(char *)(unaff_r13 + 0xf) = (char)param_1;
  unaff_r25 = asm_instruction_08(0x30,uVar8,0x4bf);
  uVar8 = asm_instruction_06(0x10,in_r48,0x334);
  asm_instruction_06(0x3c,param_1,0xfffff80d);
  asm_instruction_07(0x1d,in_r52 + -0x5f,in_lp_count);
  if (unaff_r14 == 0) {
    *(short *)(uVar6 + 4) = (short)puVar4;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_07(0xe,in_r50,0x1ba);
  uVar3 = (uint)*(ushort *)(unaff_gp + -0x1ca);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    uVar9 = func_0xbfd5b084(uVar3);
    param_2 = (undefined4)((ulonglong)uVar9 >> 0x20);
    uVar3 = (uint)uVar9;
  }
  uVar5 = (undefined1)uVar6;
  if (unaff_r13 != 0) {
    uVar3 = asm_instruction_06(0x3c,uVar3,0xfffff80d);
    puVar4 = *(undefined2 **)(param_3 + 0x34);
    if (param_8 != 0) {
      *(char *)(unaff_r13 + 0xd) = (char)puVar4;
      asm_instruction_06(0x10,uVar8,0x334);
      uVar9 = CONCAT44(param_2,(uint)*(ushort *)(unaff_gp + -0x1e2));
      cVar1 = ext_condition(0x10);
      if (cVar1 != '\0') {
        uVar9 = func_0xbfd2289c((uint)*(ushort *)(unaff_gp + -0x1e2));
      }
      uVar8 = (undefined4)((ulonglong)uVar9 >> 0x20);
      param_1 = (int)uVar9;
      puVar7 = unaff_r20 + 200;
      asm_instruction_05(0x2d,(uint)uVar2,puVar7);
      if ((bool)in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      goto code_r0xbfcf9cb2;
    }
  }
  asm_instruction_05(0x3d,unaff_r13,0x411);
                    /* WARNING: Could not recover jumptable at 0xbfcf9cac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(unaff_r20 + 0xd8))(uVar3);
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9d0c(undefined4 param_1)

{
  char cVar1;
  undefined1 uVar2;
  short sVar3;
  int in_r10;
  undefined1 in_r12;
  int iVar4;
  int unaff_r13;
  int unaff_r14;
  undefined2 *unaff_r16;
  undefined4 unaff_r17;
  undefined2 unaff_r20;
  int unaff_gp;
  short in_r32;
  int in_r34;
  undefined4 in_r48;
  bool in_N;
  undefined1 in_C;
  
  if (!in_N) {
    param_1 = func_0xbfd7cfbc();
  }
  *(undefined1 *)(unaff_r14 + 0x10) = in_r12;
  iVar4 = asm_instruction_06(0x23,in_r48,0x2e);
  if (unaff_r14 != 0) {
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_08(0x23,unaff_r17,0x3c0);
    *unaff_r16 = unaff_r20;
    sVar3 = (short)unaff_r13 + in_r32 * 4;
    if (in_r34 <= in_r10) {
      *(int *)(unaff_r14 + 0x58) = iVar4;
      asm_instruction_06(4,param_1,0x680);
      cVar1 = ext_condition(0x10);
      if (cVar1 != '\0') {
        func_0xbfd22a4c(*(undefined2 *)(unaff_gp + 0x70));
      }
      uVar2 = *(undefined1 *)(unaff_r13 + 6);
      *(short *)(iVar4 + 4) = sVar3;
      FUN_ram_bfd11f30(uVar2);
      return;
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((bool)in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9e20(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  undefined4 extraout_r1;
  undefined4 uVar4;
  int in_r12;
  undefined4 unaff_r13;
  int iVar5;
  int unaff_gp;
  uint in_r37;
  byte in_r51;
  
  asm_instruction_06(4,param_1,0x680);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar5 = asm_instruction_05(0x2d,unaff_r13,0xfffffc21);
  if (-1 < (int)(in_r37 & 1 << (in_r51 & 0x1f))) {
    func_0xbfd44230(*(undefined1 *)(iVar5 + 5));
    param_2 = extraout_r1;
  }
  uVar4 = asm_instruction_08(0x24,param_2,0xc0);
  asm_instruction_05(0x1d,0xa6963084,0x1f);
  cVar1 = ext_condition(0x18);
  cVar2 = ext_condition(0x10);
  if ((cVar2 != '\0') && (func_0xbfd22a4c(unaff_gp + -0x18,uVar4), cVar1 != '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar3 = *(undefined1 *)(iVar5 + 6);
  *(undefined2 *)(in_r12 + 4) = param_4;
  FUN_ram_bfd11f30(uVar3);
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9f10(void)

{
  char cVar1;
  undefined2 uVar2;
  int unaff_r13;
  undefined4 *unaff_r16;
  undefined4 unaff_r17;
  undefined4 uVar3;
  int iVar4;
  undefined4 unaff_r20;
  int unaff_gp;
  undefined1 in_C;
  
  uVar3 = asm_instruction_08(0x22,unaff_r17,0x3c0);
  *unaff_r16 = unaff_r20;
  uVar2 = *(undefined2 *)(unaff_gp + 0xf4);
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    uVar2 = func_0xbfd22b18(uVar2,*(undefined4 *)(unaff_r13 + 0x74));
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(char *)(unaff_r13 + 8) = (char)uVar2;
  iVar4 = asm_instruction_08(0x22,uVar3,0x3c0);
  *(undefined4 *)((int)unaff_r16 + 0x62) = unaff_r20;
  *(char *)(unaff_r16 + 0x19) = (char)unaff_r20;
  if (-1 < iVar4) {
    func_0xbfcd5334(*(undefined2 *)(unaff_gp + 0xda));
  }
  *(undefined4 *)((int)unaff_r16 + 0x66) = unaff_r20;
  if ((unaff_r13 == 0) && (cVar1 = ext_condition(0x10), cVar1 != '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!(bool)in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcf9fdc(void)

{
  char in_Z;
  
  if (in_Z != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcfa0ac(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  undefined4 in_r9;
  undefined4 in_ilink1;
  undefined4 in_blink;
  bool in_Z;
  char in_N;
  char in_V;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x14);
  if (cVar1 != '\0') {
    if (in_V == in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (!in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!in_Z) {
    cVar1 = ext_condition(0x18);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(undefined4 *)(param_2 + 1) = param_5;
    if (!in_Z) {
      asm_instruction_07(1,param_3,param_5);
      if (in_V == in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_07(0x31,in_ilink1,param_7);
      asm_instruction_07(0x31,in_blink,param_7);
      asm_instruction_08(0x11,in_r9,param_5);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcfa108(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                     int param_5,undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  undefined4 in_r9;
  undefined4 unaff_fp;
  undefined4 in_ilink1;
  undefined4 in_blink;
  bool in_Z;
  
  if (in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x12);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x16);
  if (cVar1 == '\0') {
    if (in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1a);
    if (cVar1 == '\0') {
      *(int *)(param_4 + 1) = param_5;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_07(0x31,unaff_fp,param_7);
    asm_instruction_07(0x31,in_ilink1,param_7);
    asm_instruction_07(0x31,in_blink,param_7);
    asm_instruction_08(0x11,in_r9,param_5);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  *(undefined4 *)(param_5 + 0x81) = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcfa2d8) */

void FUN_ram_bfcfa2d4(void)

{
                    /* WARNING: Do nothing block with infinite loop */
                    /* WARNING: Bad instruction - Truncating control flow here */
  do {
  } while( true );
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfa36c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,int param_6)

{
  int unaff_r14;
  undefined4 in_r53;
  undefined4 in_r56;
  char in_N;
  
  *(undefined4 *)(param_6 + 0xa4) = param_3;
  if (in_N != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0x21,(undefined4 *)(param_6 + 0xa4),in_r53);
  asm_instruction_06(0x20,in_r56,0x3f);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfa4b0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined2 *in_r12;
  
  cVar1 = ext_condition(0x11);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1c);
  if (cVar1 == '\0') {
    FUN_ram_bfd126c6(*in_r12,param_2,param_3,in_r12[2]);
    return;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfac0c(undefined4 param_1)

{
  asm_instruction_08(0x23,param_1,param_1);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfae24(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6)

{
  char cVar1;
  int in_r12;
  undefined1 unaff_r13;
  undefined4 unaff_r16;
  undefined4 unaff_r21;
  int unaff_gp;
  undefined4 in_r42;
  undefined4 in_r55;
  
  FUN_ram_bfcfb328(*(undefined4 *)(unaff_gp + -0xa8),param_2,param_3,0xbb);
  *(undefined1 *)(in_r12 + 0x1c) = unaff_r13;
  asm_instruction_06(0x18,in_r42,0x31);
  asm_instruction_08(0x1f,param_6,in_r55);
  asm_instruction_07(0x19,unaff_r21,0x2f);
  asm_instruction_06(0x2c,unaff_r16,0x65b);
  cVar1 = ext_condition(0x1e);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfb040(void)

{
  undefined4 in_r53;
  
  asm_instruction_04(0x2f,in_r53,8);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfb0f4(void)

{
  FUN_ram_bfcfb040();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfb12c(undefined4 param_1,int param_2,undefined1 param_3)

{
  undefined1 unaff_r13;
  int unaff_r14;
  undefined4 in_r56;
  
  *(undefined1 *)(unaff_r14 + 0x13) = param_3;
  *(undefined1 *)(param_2 + 0x1c) = unaff_r13;
  asm_instruction_08(0x32,0xbfcfb134,0xfffffa7f);
  asm_instruction_06(0x35,in_r56,0x708);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcfb180(int param_1,undefined4 param_2,int param_3,int param_4)

{
  char cVar1;
  undefined1 uVar2;
  short sVar3;
  undefined4 uVar4;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r25;
  bool in_V;
  
  if (unaff_r13 == 0) {
    asm_instruction_08(0x22,unaff_r25,0xffffffff);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(char *)(param_1 + 0xd) = (char)param_3;
  if (unaff_r14 != 0) {
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
      func_0xbfd23de8(param_1,param_3 + param_4);
    }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  uVar4 = asm_instruction_08(0x22,param_1,0xc0);
  sVar3 = *(short *)(unaff_r13 + 0x1c);
  if (!in_V) {
    func_0xbfdeadb4(uVar4);
  }
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    func_0xbfd23db8();
  }
  uVar2 = *(undefined1 *)(sVar3 + 5);
  *(undefined1 *)(sVar3 + 0x1f) = uVar2;
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    func_0xbfd23dd0(uVar2,param_3 + param_4);
  }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfb2ca) overlaps instruction at (ram,0xbfcfb2c8)
    */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcfb278(undefined1 *param_1,undefined4 param_2,uint param_3,undefined2 param_4)

{
  char cVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined1 extraout_r1;
  int in_r12;
  int unaff_r13;
  undefined1 uVar4;
  undefined4 unaff_r19;
  int unaff_gp;
  undefined4 in_r33;
  int in_r56;
  undefined1 in_Z;
  undefined1 in_C;
  
  uVar3 = *(undefined1 *)(unaff_r13 + 5);
  uVar4 = (undefined1)unaff_r19;
  if (*(int *)(param_3 + 0x68) == 0) goto code_r0xbfcfb2b4;
  param_1 = (undefined1 *)(uint)*(byte *)(unaff_r13 + 0x1d);
  if (unaff_r13 == 0) {
    *(undefined2 *)(in_r12 + 4) = param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  param_3 = (uint)*(ushort *)(in_r12 + 0x20);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((bool)in_C == false) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 == 0) {
    do {
      do {
        asm_instruction_06(0,param_1,0xfffffa03);
        uVar3 = *(undefined1 *)(unaff_r13 + 0x15);
        *(undefined1 *)(param_3 + 0xc) = uVar3;
        param_1 = (undefined1 *)(in_r12 - 6);
        if (!(bool)in_C && !(bool)in_Z) {
          param_1 = (undefined1 *)func_0xbfc15760();
          uVar3 = extraout_r1;
        }
        in_r56 = asm_instruction_08(0x30,in_r56,0xfffffcbf);
        in_Z = in_r56 == 0;
        if (!(bool)in_C && !(bool)in_Z) {
          *(undefined1 *)(param_3 + 0xc) = uVar3;
          param_1 = (undefined1 *)asm_instruction_06(0,param_1,0xfffffa43);
          if ((*(int *)(param_3 + 0x68) == 0) ||
             (uVar3 = *(undefined1 *)(unaff_r13 + 1), *(int *)(param_3 + 0x68) == 0)) {
LAB_ram_bfcfb32e:
            param_1[-0xa4] = uVar4;
            param_1[-0x148] = uVar4;
            asm_instruction_05(0x37,unaff_r13,in_r33);
            *(undefined4 *)(param_3 - 0xe4) = unaff_r19;
            if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            *(short *)(in_r12 + 6) = (short)(undefined4 *)(param_3 - 0xe4);
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
          bVar2 = *(byte *)(unaff_r13 + 0x19);
          while (*(int *)(param_3 + 0x68) == 0) {
            if (!(bool)in_C && !(bool)in_Z) {
              *(undefined1 *)(param_3 + 0xc) = uVar3;
              param_1 = (undefined1 *)asm_instruction_06(0,(uint)bVar2,0xfffff983);
              if (in_r12 == 0) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
                halt_unimplemented();
              }
              if (!(bool)in_C && !(bool)in_Z) {
                *(undefined1 *)(param_3 + 0xc) = *(undefined1 *)(unaff_r13 + 0x18);
                asm_instruction_06(0,param_1,0xfffffa03);
                    /* WARNING: Bad instruction - Truncating control flow here */
                halt_baddata();
              }
              goto LAB_ram_bfcfb32e;
            }
          }
          param_1 = (undefined1 *)(uint)*(byte *)(unaff_r13 + 0xf);
          if (unaff_r13 != 0) {
            *(short *)(in_r12 + 0x22) = (short)param_3;
            cVar1 = ext_condition(0x1c);
            if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            goto LAB_ram_bfcfb32e;
          }
          cVar1 = ext_condition(0x1c);
          if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
code_r0xbfcfb2b4:
          if (unaff_r13 != 0) {
            param_1 = param_1 + -0xa4;
            *param_1 = uVar4;
          }
        }
        param_1 = param_1 + -0xa4;
        *param_1 = uVar4;
        if (unaff_r13 != 0) {
          *(short *)(in_r12 + 6) = (short)param_3;
          cVar1 = ext_condition(0x1c);
          if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
        }
      } while (in_r12 == 0);
      if ((bool)in_C || (bool)in_Z) goto LAB_ram_bfcfb2a0;
      *(undefined1 *)(param_3 + 0xc) = uVar3;
    } while( true );
  }
  param_3 = (uint)*(ushort *)(in_r12 + 0x20);
  param_1 = (undefined1 *)(uint)*(ushort *)(unaff_gp + 0x10);
  if ((bool)in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    param_1 = (undefined1 *)func_0xbfc5be9c();
  }
LAB_ram_bfcfb2a0:
  if ((bool)in_C || (bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(short *)(param_1 + 0x20) = (short)param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfb328(int param_1,undefined4 param_2,int param_3)

{
  int in_r12;
  int unaff_r13;
  undefined4 unaff_r19;
  undefined4 in_r33;
  
  *(char *)(param_1 + -0xa4) = (char)unaff_r19;
  *(char *)(param_1 + -0x148) = (char)unaff_r19;
  asm_instruction_05(0x37,unaff_r13,in_r33);
  *(undefined4 *)(param_3 + -0xe4) = unaff_r19;
  if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(short *)(in_r12 + 6) = (short)(undefined4 *)(param_3 + -0xe4);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfb370(undefined4 param_1,undefined1 param_2,int param_3)

{
  int in_r12;
  int unaff_r13;
  undefined4 in_r56;
  int iVar1;
  bool in_C;
  
  iVar1 = asm_instruction_08(0x30,in_r56,0xfffffcbf);
  if (!in_C && iVar1 != 0) {
    *(undefined1 *)(param_3 + 0xc) = param_2;
    asm_instruction_06(0,in_r12 + -6,0xfffffa43);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
    *(short *)(in_r12 + 6) = (short)param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfb3cc(void)

{
  bool in_Z;
  char in_N;
  char in_V;
  
  if (!in_Z && in_V == in_N) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfb6d0(undefined1 param_1)

{
  char cVar1;
  int unaff_r13;
  
  *(undefined1 *)(unaff_r13 + 3) = param_1;
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfb94c(undefined4 param_1)

{
  int unaff_r13;
  int unaff_r15;
  undefined2 *unaff_r16;
  undefined4 unaff_r17;
  undefined4 uVar1;
  undefined2 unaff_r20;
  undefined4 unaff_r25;
  undefined4 in_blink;
  bool in_Z;
  bool in_N;
  
  asm_instruction_06(0x23,param_1,0x30);
  if (!in_N && !in_Z) {
    in_blink = 0xbfcfb956;
    param_1 = func_0xbfc58c00(param_1,*(undefined4 *)(unaff_r15 + 0x40));
  }
  uVar1 = asm_instruction_08(0x22,unaff_r17,0x3c0);
  *(char *)(unaff_r13 + 0xb) = (char)param_1;
  asm_instruction_08(0x22,uVar1,0x3c0);
  *unaff_r16 = unaff_r20;
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  asm_instruction_08(0x1f,unaff_r13,0xfffff8a1);
  asm_instruction_05(0x3d,in_blink,0x13);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfba94) overlaps instruction at (ram,0xbfcfba92)
    */

void FUN_ram_bfcfba30(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int in_r6;
  int in_r7;
  int iVar2;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r17;
  int iVar3;
  undefined4 unaff_r25;
  int unaff_gp;
  int in_r33;
  undefined4 in_r48;
  undefined4 in_r50;
  undefined4 in_mlo;
  undefined1 uVar4;
  char cVar5;
  undefined1 uVar6;
  undefined1 in_C;
  
  iVar2 = asm_instruction_06(0x31,in_r50,in_mlo);
  uVar4 = iVar2 == 0;
  uVar6 = iVar2 < 0;
  uVar1 = (uint)*(byte *)(param_1 + 0x11);
  iVar3 = in_r7;
  if (!(bool)in_C && !(bool)uVar4) {
    uVar1 = func_0xbfcd8ec4();
  }
  if (!(bool)in_C && !(bool)uVar4) {
    uVar1 = func_0xbfcd8ed0(uVar1,(int)*(short *)(in_r7 + 0x20));
  }
  *(char *)(unaff_r13 + 0xe) = (char)unaff_r14;
  if (iVar3 == 0) {
    *(uint *)(iVar2 + 0x20) = uVar1;
    if (!(bool)uVar6) {
      func_0xbfd7eeec();
    }
  }
  else {
    *(uint *)(uVar1 + 0x3c) = uVar1;
    if (in_r6 <= in_r33) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar3 = asm_instruction_08(0x22,unaff_r17,0x3c0);
    uVar4 = iVar3 == 0;
    *(uint *)(param_3 + 0x74) = uVar1;
    if (unaff_r13 != 0) {
      uVar1 = *(uint *)(unaff_gp + 0x110);
    }
    if (!(bool)in_C && !(bool)uVar4) {
      func_0xbfdd8f74(uVar1);
    }
    cVar5 = ext_condition(0x10);
    if (cVar5 != '\0') {
      func_0xbfd7efa8();
    }
    if (!(bool)in_C && !(bool)uVar4) {
      asm_instruction_06(0x30,in_r48,in_mlo);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar5 = ext_condition(0x10);
    if (cVar5 != '\0') {
      func_0xbfd7ef7c();
    }
    if (!(bool)in_C && !(bool)uVar4) {
      asm_instruction_06(0x30,in_r48,in_mlo);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar3 = unaff_r14 + -5;
    iVar2 = asm_instruction_08(0x30,unaff_r25,0x4bf);
    if (!(bool)in_C && iVar2 != 0) {
      iVar2 = asm_instruction_06(0x30,in_r48,in_mlo);
      cVar5 = iVar2 == 0;
      iVar2 = FUN_ram_bfcfac0c();
      *(short *)(iVar3 + 4) = (short)iVar2;
      *(int *)(iVar2 + 0x3c) = iVar2;
      if (cVar5 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfbeac(void)

{
  undefined1 in_r3;
  int in_r35;
  
  *(undefined1 *)(in_r35 + 0x50) = in_r3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcfbf4e) */
/* WARNING: Removing unreachable block (ram,0xbfcfbf56) */
/* WARNING: Removing unreachable block (ram,0xbfcfbf58) */
/* WARNING: Removing unreachable block (ram,0xbfcfbf5e) */
/* WARNING: Removing unreachable block (ram,0xbfd2c752) */

void FUN_ram_bfcfbf30(undefined4 param_1,undefined4 param_2,undefined1 *param_3)

{
  char cVar1;
  int iVar2;
  undefined2 unaff_r13;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    iVar2 = asm_instruction_08(0x23,param_1,param_1);
    *(undefined2 *)(iVar2 + -0xa4) = unaff_r13;
    *param_3 = (char)unaff_r13;
    do {
    } while( true );
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfc100(void)

{
  char cVar1;
  
  cVar1 = ext_condition(0x12);
  if (cVar1 != '\0') {
    FUN_ram_bfd16900();
    FUN_ram_bfd16900();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfc118(undefined4 param_1,undefined4 param_2,undefined1 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int unaff_r13;
  undefined4 unaff_r17;
  int unaff_gp;
  undefined4 in_ilink1;
  int iVar2;
  char in_V;
  
  asm_instruction_06(0x10,param_4,0x3c);
  FUN_ram_bfcfc120();
  uVar1 = asm_instruction_05(0x30,param_4,param_4);
  iVar2 = asm_instruction_06(0x10,unaff_r17,0x2f);
  if (iVar2 != 0 && (bool)in_V == iVar2 < 0) {
    *(undefined1 *)(unaff_gp + -0x18) = param_3;
    *(short *)(unaff_r13 + 0x18) = (short)uVar1;
    FUN_ram_bfd14a9e(unaff_gp + -0x28,unaff_r13);
    return;
  }
  asm_instruction_05(0x2d,in_ilink1,unaff_r13);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfc120(undefined4 param_1,undefined4 param_2,undefined1 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int unaff_r13;
  undefined4 unaff_r17;
  int unaff_gp;
  undefined4 in_ilink1;
  int iVar2;
  char in_V;
  
  uVar1 = asm_instruction_05(0x30,param_4,param_4);
  iVar2 = asm_instruction_06(0x10,unaff_r17,0x2f);
  if (iVar2 != 0 && (bool)in_V == iVar2 < 0) {
    *(undefined1 *)(unaff_gp + -0x18) = param_3;
    *(short *)(unaff_r13 + 0x18) = (short)uVar1;
    FUN_ram_bfd14a9e(unaff_gp + -0x28,unaff_r13);
    return;
  }
  asm_instruction_05(0x2d,in_ilink1,unaff_r13);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfc140(undefined2 param_1,int param_2,undefined4 param_3,short param_4,
                     undefined4 param_5,undefined4 param_6)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 extraout_r1;
  undefined1 *puVar3;
  int in_r12;
  int unaff_r13;
  undefined1 unaff_r14;
  int unaff_r15;
  undefined4 unaff_r17;
  int iVar4;
  int unaff_gp;
  undefined4 in_r50;
  undefined4 in_mlo;
  char in_N;
  char cVar5;
  char in_V;
  
  asm_instruction_05(0x10,unaff_r17,0x2c);
  if (in_V == in_N) {
    iVar4 = asm_instruction_05(0x27,param_6,in_r50);
    if (param_2 != 0) {
      if (unaff_r15 != 0) {
        *(char *)(param_2 + 2) = (char)in_r12;
        if (iVar4 != 0) {
          func_0xbfc65b68(param_2 + 5);
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      FUN_ram_bfd16360();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0x10,param_2,1);
  param_4 = param_4 + -0x70;
  iVar4 = asm_instruction_06(0x20,in_mlo,0xbfcfc150);
  cVar5 = iVar4 < 0;
  cVar1 = ext_condition(0x1a);
  if (cVar1 != '\0') {
    param_1 = func_0xbfc94594();
  }
  if (unaff_r13 == 0) {
    func_0xbfd5e598();
    FUN_ram_bfcfc158();
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(unaff_r13 + 0xc) = param_1;
  FUN_ram_bfcfc140();
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar2 = *(undefined2 *)(unaff_gp + -0x184);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  puVar3 = (undefined1 *)asm_instruction_05(9,param_3,extraout_r1);
  *(short *)(in_r12 + 4) = param_4;
  FUN_ram_bfcfc178(uVar2);
  *puVar3 = unaff_r14;
  if (in_V != cVar5) {
    func_0xbfc645a0(*(undefined2 *)(unaff_gp + -0x180));
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfc158(undefined2 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 extraout_r1;
  undefined1 *puVar3;
  int in_r12;
  int unaff_r13;
  undefined1 unaff_r14;
  int unaff_gp;
  char in_N;
  char in_V;
  
  if (unaff_r13 == 0) {
    func_0xbfd5e598();
    FUN_ram_bfcfc158();
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(unaff_r13 + 0xc) = param_1;
  FUN_ram_bfcfc140();
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar2 = *(undefined2 *)(unaff_gp + -0x184);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  puVar3 = (undefined1 *)asm_instruction_05(9,param_3,extraout_r1);
  *(undefined2 *)(in_r12 + 4) = param_4;
  FUN_ram_bfcfc178(uVar2);
  *puVar3 = unaff_r14;
  if (in_V != in_N) {
    func_0xbfc645a0(*(undefined2 *)(unaff_gp + -0x180));
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfc178(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 extraout_r1;
  undefined1 *puVar3;
  int in_r12;
  int unaff_r13;
  undefined1 unaff_r14;
  int unaff_r15;
  int unaff_gp;
  char in_N;
  char in_V;
  
  *(char *)(unaff_r15 + 0x14) = (char)param_1;
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(short *)(unaff_r13 + 0xc) = (short)param_1;
  FUN_ram_bfcfc140(param_1,unaff_r13);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar2 = *(undefined2 *)(unaff_gp + -0x184);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  puVar3 = (undefined1 *)asm_instruction_05(9,param_3,extraout_r1);
  *(undefined2 *)(in_r12 + 4) = param_4;
  FUN_ram_bfcfc178(uVar2);
  *puVar3 = unaff_r14;
  if (in_V != in_N) {
    func_0xbfc645a0(*(undefined2 *)(unaff_gp + -0x180));
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfdb40) overlaps instruction at (ram,0xbfcfdb3e)
    */

void FUN_ram_bfcfc2d4(undefined4 *param_1,undefined4 param_2,int param_3,int param_4)

{
  char cVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  int in_r7;
  uint unaff_r13;
  int unaff_r14;
  undefined4 unaff_r25;
  undefined4 uVar5;
  undefined4 in_r32;
  undefined4 uVar6;
  undefined4 in_r38;
  undefined4 in_r52;
  int iVar7;
  undefined4 uVar8;
  undefined4 in_r56;
  undefined4 in_lp_count;
  undefined1 uVar9;
  char in_C;
  undefined1 in_V;
  undefined8 uVar10;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_C != '\0') {
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar3 = asm_instruction_08(0x28,*param_1,*param_1);
    asm_instruction_06(3,in_r56,0x3f);
    FUN_ram_bfd16760(uVar3);
    uVar3 = FUN_ram_bfd16760();
    asm_instruction_05(0x30,uVar3,0x441);
    cVar1 = ext_condition(0x10);
    if (cVar1 == '\0') {
      cVar1 = ext_condition(0x11);
      if (in_C == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (cVar1 == '\0') {
                    /* WARNING: Call to offcut address within same function */
        func_0xbfcfc30c(*(undefined2 *)(param_3 + 0x20));
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0x3d,param_1,0xfffffe04);
  iVar7 = asm_instruction_07(0x1d,in_r52,in_lp_count);
  uVar9 = iVar7 == 0;
  if (!(bool)in_V) {
    func_0xbfded790(unaff_r14 + -5,(int)unaff_r13 >> 6 & ~unaff_r13);
  }
  if (in_r7 != 0) {
                    /* WARNING: Call to offcut address within same function */
    uVar10 = func_0xbfcfdb6c();
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (!(bool)in_C && !(bool)uVar9) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (!(bool)in_V) {
      func_0xbfded7b0((int)uVar10,(uint)((ulonglong)uVar10 >> 0x20) & ~unaff_r13);
    }
    if (in_r7 != 0) {
      bVar2 = *(byte *)(param_4 + 9);
      iVar4 = bVar2 - 5;
      if (!(bool)uVar9) {
        iVar4 = func_0xbfd19f1c();
      }
      uVar5 = asm_instruction_08(0x25,unaff_r25,0x43f);
      uVar6 = asm_instruction_06(0x25,in_r32,0x6bb);
      uVar8 = asm_instruction_07(0x1d,iVar7,in_lp_count);
      uVar3 = asm_instruction_06(0x1d,iVar4,0xfffffa80);
      asm_instruction_08(0x25,uVar5,0x43f);
      in_r32 = asm_instruction_06(0x25,uVar6,0xfffffebb);
      uVar5 = asm_instruction_07(0x1d,uVar8,in_lp_count);
      uVar3 = asm_instruction_06(0x1d,uVar3,0x604);
      iVar7 = asm_instruction_07(0x1d,uVar5,in_lp_count);
      if (!(bool)in_V) {
        func_0xbfded7f4(uVar3);
      }
      unaff_r14 = (int)(uint)bVar2 >> 5;
    }
    asm_instruction_07(0x1d,iVar7,0x3c);
    iVar7 = asm_instruction_06(0x3d,unaff_r14 + -5,0x604);
    *(short *)(iVar7 + 0x1c) = (short)iVar7;
  }
  asm_instruction_05(0x1f,in_r38,0xfffff906);
  func_0xbfb58168();
  asm_instruction_06(4,in_r32,0x237);
  cVar1 = ext_condition(0x15);
  if (cVar1 != '\0') {
    func_0xbfd0b7a0();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfc8c8(void)

{
  undefined4 in_r10;
  int unaff_gp;
  undefined4 in_ilink1;
  
  asm_instruction_06(0,in_r10,in_ilink1);
  func_0xbfcfd140(*(undefined2 *)(unaff_gp + 0x18));
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfc994) overlaps instruction at (ram,0xbfcfc992)
    */

void FUN_ram_bfcfc98c(undefined4 param_1,undefined1 param_2)

{
  int unaff_r13;
  int unaff_r14;
  int unaff_r15;
  bool in_Z;
  bool in_N;
  
  if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r15 == 0) {
    *(undefined1 *)(unaff_r13 + 0x16) = param_2;
  }
  if (in_Z != false) {
    if (in_N || in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfc9c0(undefined4 param_1)

{
  char cVar1;
  ushort uVar3;
  undefined1 uVar4;
  int unaff_r14;
  undefined4 unaff_r18;
  int unaff_gp;
  char in_Z;
  char cVar2;
  
  asm_instruction_08(3,param_1,0);
  cVar1 = ext_condition(0x1c);
  cVar2 = ext_condition(0x10);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar3 = *(ushort *)(unaff_gp + 0x2a);
  *(undefined4 *)(uint)uVar3 = unaff_r18;
  if (in_Z != '\0') {
    uVar4 = func_0xbfcfc908((undefined4 *)(uint)uVar3 + -0x21);
    *(undefined1 *)(unaff_r14 + 0xd) = uVar4;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfc9d0(void)

{
  ushort uVar1;
  undefined1 uVar2;
  int unaff_r14;
  undefined4 unaff_r18;
  int unaff_gp;
  char in_Z;
  
  uVar1 = *(ushort *)(unaff_gp + 0x2a);
  *(undefined4 *)(uint)uVar1 = unaff_r18;
  if (in_Z != '\0') {
    uVar2 = func_0xbfcfc908((undefined4 *)(uint)uVar1 + -0x21);
    *(undefined1 *)(unaff_r14 + 0xd) = uVar2;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfca80(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  char cVar1;
  undefined4 in_r7;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined1 in_Z;
  char cVar2;
  
  if (unaff_r14 == 0) {
    if (unaff_r13 != 0) {
      *(undefined2 *)(in_r12 + 6) = param_3;
    }
    FUN_ram_bfd14a74();
    return;
  }
  *(undefined4 *)(unaff_r14 + 0x54) = in_r7;
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    param_1 = func_0xbfd5de84();
  }
  cVar1 = ext_condition(0x12);
  cVar2 = in_Z;
  if ((cVar1 != '\0') && (func_0xbfc94e90(param_1,*(undefined2 *)(unaff_r14 + 0xc)), !(bool)in_Z)) {
    func_0xbfc94e90();
  }
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfcb80(void)

{
  undefined4 in_r48;
  
  asm_instruction_06(0x25,in_r48,in_r48);
  FUN_ram_bfcfcdfc();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfcb8c(void)

{
  undefined4 in_r5;
  undefined4 in_r33;
  undefined4 in_r43;
  undefined4 in_r54;
  
  asm_instruction_08(0x20,in_r54,in_r5);
  asm_instruction_04(0x39,in_r33,0x18);
  asm_instruction_08(0xc,in_r33,0x21);
  asm_instruction_08(0x1f,in_r43,0x3d);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfcbc4(void)

{
  undefined4 in_r33;
  undefined4 in_r56;
  
  asm_instruction_07(0x30,in_r56,in_r33);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfcc64(undefined4 param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 in_r9;
  undefined1 in_r12;
  int unaff_r14;
  char in_N;
  char in_C;
  char in_V;
  undefined8 uVar2;
  undefined4 in_stack_00000000;
  
  asm_instruction_06(0x15,param_4,param_1);
  cVar1 = ext_condition(0x15);
  if ((cVar1 == '\0') ||
     (uVar2 = func_0xbfd6307c(), param_2 = (undefined1 *)((ulonglong)uVar2 >> 0x20), in_V == in_N))
  {
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
      asm_instruction_05(0x1f,param_3,0x1a);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x10);
    if (cVar1 == '\0') {
      asm_instruction_06(0x15,param_4,param_2);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x12);
  if (cVar1 != '\0') {
    *param_2 = in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x13);
  if (cVar1 != '\0') {
    cVar1 = ext_condition(0x15);
    if (cVar1 != '\0') {
      func_0xbfd4d0ec();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_C != '\0') {
    asm_instruction_06(0x15,param_4,(int)uVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r14 != 0) {
    asm_instruction_08(0x27,in_r9,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0,param_2,in_stack_00000000);
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    asm_instruction_06(0x3d,param_2,0x502);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Possible PIC construction at 0xbfcfd616: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0xbfcfd618) */

void FUN_ram_bfcfcda8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 in_r7;
  char in_C;
  
  cVar1 = ext_condition(0x12);
  if (cVar1 == '\0') {
    cVar1 = ext_condition(0x13);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (in_C != '\0') {
      asm_instruction_06(0x15,param_4,param_1);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  else {
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  asm_instruction_06(0x38,in_r7,param_3);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfcdfc(void)

{
  bool in_Z;
  bool in_N;
  
  if (in_N || in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Removing unreachable block (ram,0xbfcfd000) */

void FUN_ram_bfcfd050(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  char cVar1;
  int in_r12;
  int unaff_r13;
  int unaff_r15;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r51;
  undefined4 in_r56;
  undefined8 uVar2;
  
  if (unaff_r13 != 0) {
    *(short *)(in_r12 + 0x24) = (short)param_3;
  }
  cVar1 = ext_condition(0x12);
  uVar2 = FUN_ram_bfcfd050();
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
    asm_instruction_06(0x32,in_r56,0x3f);
    *(undefined2 *)(*(byte *)((ulonglong)uVar2 >> 0x20) + 6) = param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(short *)((int)uVar2 + 0x24) = (short)param_3;
  cVar1 = ext_condition(0x18);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r15 == 0) {
    asm_instruction_08(0x3e,unaff_r25,0x47f);
    asm_instruction_06(0x1e,in_r51,0x1d);
    FUN_ram_bfcfdae8(*(undefined2 *)(unaff_gp + 0x12));
    do {
    } while( true );
  }
  uRam0000000a = (char)*(ushort *)(unaff_gp + 0xf4);
  asm_instruction_06(0,param_3,(uint)*(ushort *)(unaff_gp + 0xf4));
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfd098(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  char cVar1;
  uint uVar2;
  undefined2 uVar3;
  int in_r7;
  undefined4 in_r8;
  int iVar4;
  int unaff_r13;
  int unaff_r14;
  uint unaff_r15;
  undefined4 unaff_r17;
  undefined4 uVar5;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r43;
  undefined4 in_r48;
  undefined4 in_r51;
  undefined4 in_r56;
  undefined1 in_Z;
  undefined1 in_C;
  undefined1 in_V;
  undefined8 uVar6;
  
  uVar6 = CONCAT44(param_2,param_1);
  if ((bool)in_C) {
    uVar6 = func_0xbfd80528(param_1,param_2,param_3);
  }
  iVar4 = (int)uVar6;
  if (!(bool)in_C && !(bool)in_Z) {
    asm_instruction_06(0x25,in_r48,0x21e);
    uVar5 = asm_instruction_08(0x33,unaff_r17,0);
    iVar4 = *(int *)(unaff_r14 + 0x60);
    if ((unaff_r15 & 0x3ffff) != 0) {
      asm_instruction_08(0x33,uVar5,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0,in_r56,0x3f);
    uVar2 = (uint)*(byte *)((ulonglong)uVar6 >> 0x20);
    uVar3 = *(undefined2 *)(unaff_r13 + 0x24);
    if (!(bool)in_V) {
      uVar2 = func_0xbfc17558();
    }
    if (unaff_r13 == 0) {
      asm_instruction_08(0x23,uVar5,0);
      asm_instruction_06(3,in_r8,0x20);
      *(short *)(iVar4 + 0x20) = (short)iVar4;
      asm_instruction_08(0x23,unaff_r25,0x4bf);
      if ((bool)in_V) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_06(0x23,in_r56,0x13);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (in_r7 == 0) {
      *(undefined2 *)(uVar2 + 0x24) = uVar3;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_04(0x3d,in_r43,uVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(int *)(iVar4 + 0x73) = iVar4;
  if (unaff_r13 != 0) {
    asm_instruction_06(0x1e,in_r51,0x1d);
    FUN_ram_bfcfdae8(*(undefined2 *)(unaff_gp + 0x12));
    do {
    } while (unaff_r13 == 0);
    asm_instruction_06(0x12,in_r56,0x3f);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(int *)(iVar4 + 0x73) = iVar4;
  *(undefined2 *)(iVar4 + 4) = param_4;
  if ((bool)in_C != false) {
    cVar1 = ext_condition(0x14);
    if (cVar1 != '\0') {
      FUN_ram_bfcfda0c();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfd0b0(undefined4 param_1,byte *param_2)

{
  uint uVar1;
  undefined2 uVar2;
  int in_r7;
  undefined4 in_r8;
  int in_r12;
  int unaff_r13;
  int unaff_r15;
  undefined4 unaff_r17;
  undefined4 unaff_r25;
  undefined4 in_r43;
  undefined4 in_r56;
  undefined1 in_V;
  
  if (unaff_r15 != 0) {
    asm_instruction_08(0x33,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0,in_r56,0x3f);
  uVar1 = (uint)*param_2;
  uVar2 = *(undefined2 *)(unaff_r13 + 0x24);
  if (!(bool)in_V) {
    uVar1 = func_0xbfc17558();
  }
  if (unaff_r13 != 0) {
    if (in_r7 != 0) {
      asm_instruction_04(0x3d,in_r43,uVar1);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(undefined2 *)(uVar1 + 0x24) = uVar2;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x23,unaff_r17,0);
  asm_instruction_06(3,in_r8,0x20);
  *(short *)(in_r12 + 0x20) = (short)in_r12;
  asm_instruction_08(0x23,unaff_r25,0x4bf);
  if (!(bool)in_V) {
    asm_instruction_06(0x23,in_r56,0x13);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfd138) overlaps instruction at (ram,0xbfcfd136)
    */
/* WARNING: Removing unreachable block (ram,0xbfcfd1bc) */

void FUN_ram_bfcfd134(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
                     int param_5,undefined4 param_6,int param_7)

{
  uint uVar1;
  uint unaff_r13;
  int unaff_r14;
  int iVar2;
  int in_r56;
  bool bVar3;
  char cVar4;
  char in_V;
  
  uVar1 = unaff_r13 & 0xffff;
  if (param_7 < in_r56) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar2 = asm_instruction_05(0x21,param_6,(int)*(short *)(param_5 + -0xa4));
  bVar3 = iVar2 == 0;
  cVar4 = iVar2 < 0;
  if (unaff_r13 == 0) {
    if (unaff_r14 != 0) {
      ext_condition(0x1f);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar4 = ext_condition(0x10);
    if (cVar4 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(uVar1 + 0x22) = param_3;
  if (!bVar3) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcfc2d4();
  if (bVar3 || in_V != cVar4) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(uVar1 + 0x22) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void thunk_EXT_FUN_ram_c037e28e(void)

{
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfd544(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 unaff_r25;
  undefined4 in_r48;
  int in_r50;
  undefined2 in_mlo;
  char in_V;
  
  if (in_V != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  asm_instruction_06(0,param_3,0x40);
  *(undefined2 *)(in_r50 + -0x7e) = in_mlo;
  asm_instruction_06(2,in_r48,0x39);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfd5ac(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6)

{
  int unaff_r13;
  
  asm_instruction_06(0x23,param_6,param_3);
  if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(3,param_6,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfd5d0(void)

{
  undefined4 in_r5;
  
  asm_instruction_06(3,in_r5,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfd688(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    asm_instruction_06(0x3d,param_2,0xfffffd02);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfd86c(void)

{
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfda0c(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined2 uVar5;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r25;
  undefined4 in_r32;
  undefined4 in_r52;
  undefined4 in_lp_count;
  undefined1 in_Z;
  char in_N;
  undefined1 in_C;
  char in_V;
  
  *(short *)(param_3 + 0x12) = (short)unaff_r13;
  if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcfcb80(*(undefined1 *)(unaff_r13 + 7));
  uVar5 = (undefined2)param_3;
  uVar2 = *(undefined4 *)(in_r12 + 0x60);
  *(char *)(unaff_r13 + 0x14) = (char)param_4;
  if (unaff_r14 == 0) {
    asm_instruction_08(0x25,unaff_r25,0x43f);
    asm_instruction_06(0x25,in_r32,0xfffffb37);
    asm_instruction_07(0x1d,in_r52,in_lp_count);
    FUN_ram_bfcfcc64(uVar2);
    *(undefined2 *)(in_r12 + 6) = uVar5;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcfcb8c();
  iVar3 = *(int *)(in_r12 + 0x60);
  if (!(bool)in_Z && in_V == in_N) {
    FUN_ram_bfcfdb94();
    uVar4 = (uint)*(ushort *)(*(int *)(in_r12 + 0x60) + 0x34);
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
      uVar4 = func_0xbfd2deac();
    }
    uVar2 = *(undefined4 *)(param_4 + 0x28);
    *(uint *)(uVar4 + 0x20) = uVar4;
    if (!(bool)in_Z) {
      func_0xbfd80e34(uVar4,uVar2);
    }
    FUN_ram_bfcfcbc4();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!(bool)in_C && !(bool)in_Z) {
    *(char *)(iVar3 + 0xd) = (char)param_3;
    uVar2 = asm_instruction_06(0,iVar3,0x504);
    func_0xbfd0d404(uVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfdb40) overlaps instruction at (ram,0xbfcfdb3e)
    */

void FUN_ram_bfcfdae8(undefined4 param_1,uint param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint unaff_r13;
  int unaff_r14;
  int unaff_r15;
  undefined4 unaff_r25;
  undefined4 uVar5;
  undefined4 in_r32;
  undefined4 uVar6;
  undefined4 in_r38;
  undefined4 in_r52;
  int iVar7;
  undefined4 uVar8;
  undefined4 in_lp_count;
  undefined1 uVar9;
  undefined1 in_C;
  undefined1 in_V;
  undefined8 uVar10;
  
  iVar7 = asm_instruction_07(0x1d,in_r52,in_lp_count);
  uVar9 = iVar7 == 0;
  if ((bool)in_V == false) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!(bool)in_V) {
    func_0xbfded790(unaff_r14 + -5,param_2 & ~unaff_r13);
  }
  if (unaff_r15 != 0) {
                    /* WARNING: Call to offcut address within same function */
    uVar10 = func_0xbfcfdb6c();
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (!(bool)in_C && !(bool)uVar9) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (!(bool)in_V) {
      func_0xbfded7b0((int)uVar10,(uint)((ulonglong)uVar10 >> 0x20) & ~unaff_r13);
    }
    if (unaff_r15 != 0) {
      bVar2 = *(byte *)(param_4 + 9);
      iVar3 = bVar2 - 5;
      if (!(bool)uVar9) {
        iVar3 = func_0xbfd19f1c();
      }
      uVar5 = asm_instruction_08(0x25,unaff_r25,0x43f);
      uVar6 = asm_instruction_06(0x25,in_r32,0x6bb);
      uVar8 = asm_instruction_07(0x1d,iVar7,in_lp_count);
      uVar4 = asm_instruction_06(0x1d,iVar3,0xfffffa80);
      asm_instruction_08(0x25,uVar5,0x43f);
      in_r32 = asm_instruction_06(0x25,uVar6,0xfffffebb);
      uVar5 = asm_instruction_07(0x1d,uVar8,in_lp_count);
      uVar4 = asm_instruction_06(0x1d,uVar4,0x604);
      iVar7 = asm_instruction_07(0x1d,uVar5,in_lp_count);
      if (!(bool)in_V) {
        func_0xbfded7f4(uVar4);
      }
      unaff_r14 = (int)(uint)bVar2 >> 5;
    }
    asm_instruction_07(0x1d,iVar7,0x3c);
    iVar7 = asm_instruction_06(0x3d,unaff_r14 + -5,0x604);
    *(short *)(iVar7 + 0x1c) = (short)iVar7;
  }
  asm_instruction_05(0x1f,in_r38,0xfffff906);
  func_0xbfb58168();
  asm_instruction_06(4,in_r32,0x237);
  cVar1 = ext_condition(0x15);
  if (cVar1 != '\0') {
    func_0xbfd0b7a0();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcfdb94(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  ushort uVar3;
  int in_r12;
  undefined4 unaff_r13;
  int iVar4;
  undefined4 unaff_r18;
  undefined4 unaff_fp;
  undefined4 in_ilink1;
  undefined4 in_r36;
  undefined4 in_r53;
  char in_N;
  bool in_V;
  
  uVar2 = asm_instruction_06(0x1d,param_1,5);
  cVar1 = ext_condition(0x10);
  uVar3 = (ushort)*(byte *)(param_4 + 0x10);
  if (cVar1 == '\0') {
    if (in_N != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!in_V) {
    asm_instruction_08(0x10,uVar2,0xfffffa04);
    asm_instruction_08(0x10,unaff_fp,in_r36);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  asm_instruction_05(0x2d,in_ilink1,unaff_r18);
  FUN_ram_bfd16228(uVar2,unaff_r13);
  asm_instruction_05(0x3d,in_r53,0x234);
  iVar4 = asm_instruction_08(0x3f,unaff_r13,0xffffff11);
  if (iVar4 != 0) {
    *(ushort *)(in_r12 + 6) = uVar3;
  }
  cVar1 = ext_condition(0x1c);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfdd0e) overlaps instruction at (ram,0xbfcfdd0c)
    */
/* WARNING: Removing unreachable block (ram,0xbfcfdc8a) */

void FUN_ram_bfcfdc50(uint param_1,uint param_2,int param_3,int param_4,undefined4 param_5,
                     undefined4 param_6,int param_7,uint param_8)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  short sVar4;
  undefined4 uVar5;
  uint extraout_r1;
  uint extraout_r1_00;
  uint uVar6;
  int in_r12;
  uint unaff_r13;
  uint uVar7;
  uint uVar8;
  int unaff_r25;
  int unaff_gp;
  undefined4 in_r32;
  undefined4 in_r37;
  int in_r52;
  undefined4 in_r56;
  int iVar9;
  undefined4 in_mmid;
  undefined4 in_lp_count;
  undefined1 in_Z;
  undefined1 in_C;
  char in_V;
  undefined8 uVar10;
  uint extraout_r1_01;
  
code_r0xbfcfdc50:
  if (!(bool)in_C && !(bool)in_Z) {
    param_1 = func_0xbfddb0e0(param_1,param_2);
  }
code_r0xbfcfdc54:
  uVar7 = (uint)*(ushort *)(unaff_r13 + 0x3a);
  uVar8 = param_8;
  if (param_8 == 0) {
LAB_ram_bfcfdc80:
    *(short *)(in_r12 + 4) = (short)param_4;
    uVar10 = FUN_ram_bfcfdc50(param_1);
    if (param_3 != 0) {
      do {
        param_2 = (uint)((ulonglong)uVar10 >> 0x20);
        asm_instruction_06(0,(int)uVar10,param_3);
        unaff_r25 = asm_instruction_08(0x33,unaff_r25,0x43f);
        in_Z = unaff_r25 == 0;
        in_r32 = asm_instruction_06(0x33,in_r32,0x33c);
        uVar8 = (uint)*(ushort *)(unaff_r13 + 0x3a);
        if (param_8 == 0) {
          *(char *)(uVar8 + 0xc) = (char)param_3;
          if (!(bool)in_V) {
            func_0xbfded900();
            param_2 = extraout_r1_00;
          }
code_r0xbfcfdc44:
          param_1 = uVar8 - 5;
          param_4 = in_r12 >> 5;
          in_r12 = *(int *)(uVar8 + 0x20);
          param_2 = param_2 & ~unaff_r13;
          if (param_8 == 0) {
            asm_instruction_06(0x3d,param_3,3);
            asm_instruction_06(0x15,in_r32,in_lp_count);
            if (!(bool)in_C && !(bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            cVar1 = ext_condition(0x10);
            if (cVar1 != '\0') {
              halt_baddata();
            }
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
          goto code_r0xbfcfdc50;
        }
        param_1 = asm_instruction_06(0x1d,uVar7 - 5,0xfffffb40);
        unaff_r25 = asm_instruction_08(0x32,unaff_r25,0x43f);
        in_Z = unaff_r25 == 0;
        in_r32 = asm_instruction_06(0x32,in_r32,0xfffffb3c);
        uVar7 = (uint)*(ushort *)(unaff_r13 + 0x3a);
        if (param_8 == 0) goto FUN_ram_bfcfdc50_2;
        param_2 = uVar7 - 5;
        asm_instruction_06(0x3d,param_1,0xfffffe04);
        in_r52 = asm_instruction_07(0x1d,in_r52,in_lp_count);
        in_Z = in_r52 == 0;
        uVar10 = CONCAT44(param_2,uVar7 - 5);
        if (uVar7 == 0) {
          param_7 = asm_instruction_07(10,param_7,0x133);
          uVar8 = 0;
          uRam0000000c = (char)param_3;
          goto code_r0xbfcfdc44;
        }
        if (param_8 != 0) {
          uVar5 = asm_instruction_06(0x1d,uVar7 - 5,0xfffffe04);
          uVar5 = asm_instruction_06(0x3d,uVar5,0x606);
          iVar9 = asm_instruction_07(0x1d,in_r52,in_lp_count);
          if (!(bool)in_C && iVar9 != 0) {
            *(short *)(uVar7 + 0x11) = (short)in_r12;
            uVar5 = asm_instruction_06(0x1d,uVar5,0xfffffe05);
            *(char *)(unaff_r13 + 6) = (char)uVar5;
            cVar1 = ext_condition(0x10);
            if (cVar1 != '\0') {
              FUN_ram_bfd169e4();
              param_2 = extraout_r1;
            }
            asm_instruction_08(0x1f,in_r37,0xfffff973);
            *(short *)(param_2 + 0x16) = (short)in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
          if (unaff_r13 == 0) {
            asm_instruction_06(0x3d,uVar5,5);
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
      } while( true );
    }
    *(short *)(in_r12 + 0x20) = (short)uVar10;
    if (!(bool)in_C && !(bool)in_Z) {
      uVar10 = func_0xbfdda15c();
    }
    uVar3 = (undefined1)uVar10;
    uVar6 = (uint)((ulonglong)uVar10 >> 0x20) & ~unaff_r13;
    if (!(bool)in_V) {
      uVar3 = func_0xbfded970();
      uVar6 = extraout_r1_01;
    }
    if (uVar8 == 0x4030237c) {
      cVar1 = ext_condition(0x10);
      uVar8 = 0;
      if (cVar1 != '\0') {
        halt_baddata();
      }
      goto code_r0xbfcfdd1c;
    }
    if (param_8 == 0) {
      FUN_ram_bfcfdc88(uVar7 - 5);
code_r0xbfcfdd06:
      func_0xbfd5f144();
      uVar5 = func_0xbfd5f144();
      asm_instruction_06(0x1d,uVar5,0xfffffe05);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    param_1 = *(ushort *)(unaff_r13 + 0x3a) - 5;
    if (*(ushort *)(unaff_r13 + 0x3a) == 0) {
      asm_instruction_07(10,param_7,0x133);
      uRam0000000c = (undefined1)param_3;
      sVar4 = -5;
      if (param_8 != 0) {
        if (!(bool)in_C && !(bool)in_Z) {
          func_0xbfddb18c(0xfffffffb,uVar6 & ~unaff_r13);
        }
        if (param_8 != 0) goto code_r0xbfcfdd06;
        uVar8 = (uint)*(ushort *)(unaff_gp + 8);
        do {
          if (!(bool)in_Z) {
            uVar8 = func_0xbfc9616c(uVar8);
          }
        } while (unaff_r13 == 0);
        sVar4 = (short)unaff_gp + -0x2a0;
      }
      *(short *)(param_3 + 4) = sVar4;
      asm_instruction_08(0x35,in_r37,6);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar8 = param_8;
    if (in_V == '\0') {
      iVar9 = asm_instruction_06(0x25,in_r56,0x10a);
      if ((param_8 & 0x7ffff) == 0) {
        if (iVar9 == 0) {
          asm_instruction_06(0x20,(uint)*(ushort *)(unaff_gp + 0xe),2);
          *(short *)(in_r12 + 0xc) = (short)in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
      }
      else {
        asm_instruction_08(0x25,unaff_r25,0x4bf);
        asm_instruction_06(0x25,iVar9,0x40a);
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  else {
    uVar8 = param_8 + 0xbfcfdc58;
    if (param_3 == 0) {
      param_1 = (uint)*(byte *)(unaff_gp + 0x44);
      param_3 = (int)uVar7 >> 5;
      uVar7 = uVar7 - 5;
      unaff_r25 = asm_instruction_08(0x26,unaff_r25,0x43f);
code_r0xbfcfdcaa:
      in_r32 = asm_instruction_06(6,in_r32,in_mmid);
      unaff_r25 = asm_instruction_08(0x27,unaff_r25,0x43f);
      in_Z = unaff_r25 == 0;
      if (!(bool)in_C && !(bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      goto LAB_ram_bfcfdc80;
    }
    param_1 = FUN_ram_bfd168ec(param_1);
    if (0x39 < param_7) {
      asm_instruction_06(0x1d,param_3,4);
      if (unaff_r13 == 0) {
        cVar1 = ext_condition(0x10);
        if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      uVar8 = uVar8 & 0x1ffff;
      goto code_r0xbfcfdcaa;
    }
  }
  uVar3 = (undefined1)param_1;
  cVar1 = ext_condition(0x17);
  cVar2 = ext_condition(0x10);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
code_r0xbfcfdd1c:
  *(undefined1 *)(uVar8 + 9) = uVar3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
FUN_ram_bfcfdc50_2:
  in_r12 = uVar7 - 5;
  goto code_r0xbfcfdc54;
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfdd0e) overlaps instruction at (ram,0xbfcfdd0c)
    */

void FUN_ram_bfcfdc88(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  char cVar3;
  short sVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 in_r6;
  uint in_r7;
  int in_r12;
  uint unaff_r13;
  int unaff_r14;
  int unaff_r15;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r37;
  undefined4 in_r56;
  int iVar7;
  undefined1 in_Z;
  undefined1 in_C;
  char in_V;
  undefined8 uVar8;
  char cVar2;
  uint extraout_r1;
  
  uVar8 = CONCAT44(param_2,param_1);
  if (param_3 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(short *)(in_r12 + 0x20) = (short)param_1;
  if (!(bool)in_C && !(bool)in_Z) {
    uVar8 = func_0xbfdda15c();
  }
  cVar3 = (char)uVar8;
  uVar6 = (uint)((ulonglong)uVar8 >> 0x20) & ~unaff_r13;
  if (!(bool)in_V) {
    cVar3 = func_0xbfded970();
    uVar6 = extraout_r1;
  }
  if (unaff_r15 == 0) {
    cVar1 = ext_condition(0x10);
    in_r7 = 0;
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  else {
    if (in_r7 == 0) {
      FUN_ram_bfcfdc88(unaff_r14 + -5);
code_r0xbfcfdd06:
      func_0xbfd5f144();
      uVar5 = func_0xbfd5f144();
      asm_instruction_06(0x1d,uVar5,0xfffffe05);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar3 = (char)*(short *)(unaff_r13 + 0x3a) + -5;
    if (*(short *)(unaff_r13 + 0x3a) == 0) {
      asm_instruction_07(10,in_r6,0x133);
      uRam0000000c = (undefined1)param_3;
      sVar4 = -5;
      if (in_r7 != 0) {
        if (!(bool)in_C && !(bool)in_Z) {
          func_0xbfddb18c(0xfffffffb,uVar6 & ~unaff_r13);
        }
        if (in_r7 != 0) goto code_r0xbfcfdd06;
        uVar6 = (uint)*(ushort *)(unaff_gp + 8);
        do {
          if (!(bool)in_Z) {
            uVar6 = func_0xbfc9616c(uVar6);
          }
        } while (unaff_r13 == 0);
        sVar4 = (short)unaff_gp + -0x2a0;
      }
      *(short *)(param_3 + 4) = sVar4;
      asm_instruction_08(0x35,in_r37,6);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (in_V == '\0') {
      iVar7 = asm_instruction_06(0x25,in_r56,0x10a);
      if ((in_r7 & 0x7ffff) == 0) {
        if (iVar7 == 0) {
          asm_instruction_06(0x20,(uint)*(ushort *)(unaff_gp + 0xe),2);
          *(short *)(in_r12 + 0xc) = (short)in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
      }
      else {
        asm_instruction_08(0x25,unaff_r25,0x4bf);
        asm_instruction_06(0x25,iVar7,0x40a);
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x17);
    cVar2 = ext_condition(0x10);
    if (cVar2 != '\0') {
      halt_baddata();
    }
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  *(char *)(in_r7 + 9) = cVar3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfdd34(undefined4 param_1,undefined4 param_2,int param_3)

{
  short unaff_gp;
  undefined4 in_r37;
  
  *(short *)(param_3 + 4) = unaff_gp + -0x2a0;
  asm_instruction_08(0x35,in_r37,6);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



void FUN_ram_bfcfde1c(undefined4 param_1,undefined4 param_2)

{
  int in_r12;
  
  FUN_ram_bfd15e4c(param_1,param_2,*(undefined2 *)(in_r12 + 0x22));
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfdeb4(undefined4 param_1,undefined4 param_2)

{
  FUN_ram_bfcfdeb4(param_1,param_2,0xb9665);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfdf58) overlaps instruction at (ram,0xbfcfdf56)
    */

void FUN_ram_bfcfdf3c(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int unaff_r14;
  int *unaff_r16;
  int unaff_r20;
  uint unaff_r21;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 uVar4;
  undefined4 in_r37;
  uint uVar5;
  undefined4 in_r49;
  char in_r52;
  byte bVar6;
  
  if (unaff_r14 != 0) {
    asm_instruction_08(0x22,unaff_r25,0x4bf);
    bVar6 = in_r52 + 0x42;
    *unaff_r16 = unaff_r20;
    uVar2 = (uint)*(ushort *)(unaff_gp + 0xb6);
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
      uVar2 = func_0xbfd26b4c();
    }
    uVar5 = unaff_r21 ^ 1 << (bVar6 & 0x1f);
    uVar3 = asm_instruction_08(0x22,uVar2,0x541);
    asm_instruction_05(0x2d,in_r37,in_r49);
    uVar4 = 0xbfcfdf64;
    FUN_ram_bfcfe0d0(uVar3);
    unaff_r16[0x14] = unaff_r20 + 0x50;
    asm_instruction_08(0x35,uVar5,uVar4);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfdf58) overlaps instruction at (ram,0xbfcfdf56)
    */
/* WARNING: Removing unreachable block (ram,0xbfcfdf40) */
/* WARNING: Removing unreachable block (ram,0xbfcfdf4e) */
/* WARNING: Removing unreachable block (ram,0xbfcfdf52) */

void FUN_ram_bfcfdfa0(void)

{
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r17;
  bool in_V;
  
  if (unaff_r14 == 0) {
    if (!in_V) {
      func_0xbfdedb38();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  do {
  } while (unaff_r13 == 0);
  func_0xbfcfe114();
  asm_instruction_08(0x22,unaff_r17,0x200);
  FUN_ram_bfcfd134();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfe0d0(undefined1 param_1,undefined4 param_2,undefined2 param_3)

{
  char cVar1;
  int in_r12;
  int unaff_r14;
  undefined4 unaff_r25;
  undefined4 in_r50;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    asm_instruction_08(0x32,unaff_r25,0x4bf);
    *(undefined1 *)(unaff_r14 + 0xc) = param_1;
    asm_instruction_06(0x12,in_r50,6);
    *(undefined2 *)(in_r12 + 6) = param_3;
    FUN_ram_bfd1613c();
    return;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfe0f4(void)

{
  int in_r12;
  int unaff_r14;
  int unaff_r15;
  undefined4 unaff_r25;
  undefined4 unaff_fp;
  undefined4 in_r40;
  undefined4 in_r48;
  
  asm_instruction_08(0x25,unaff_r25,0x4bf);
  thunk_EXT_FUN_ram_c037e28e();
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(8,in_r48,in_r40);
  if (unaff_r15 == 0) {
    *(undefined2 *)(in_r12 + 0x10) = 0;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0x37,unaff_fp,3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfe138(undefined4 param_1)

{
  int iVar1;
  int unaff_r13;
  undefined2 unaff_r14;
  undefined4 unaff_fp;
  undefined4 in_r48;
  undefined4 in_mhi;
  bool in_Z;
  bool in_C;
  char in_V;
  
  if (in_C || in_Z) {
    asm_instruction_06(0x25,in_r48,in_mhi);
    asm_instruction_05(0x37,unaff_fp,3);
  }
  else {
    *(undefined2 *)(unaff_r13 + 0x1a) = unaff_r14;
    iVar1 = asm_instruction_06(0x1c,param_1,0x712);
    if (!in_C && iVar1 != 0) {
      asm_instruction_05(0x31,0xbfcfe144,0xfffffcb2);
      if (in_V != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfe1d8(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfe310(undefined4 param_1,undefined4 param_2,int param_3)

{
  int in_r12;
  int unaff_r14;
  undefined1 unaff_r15;
  undefined4 unaff_r17;
  bool in_V;
  
  *(undefined1 *)(in_r12 + 0x15) = unaff_r15;
  asm_instruction_06(0x12,param_3,8);
  asm_instruction_08(0x30,unaff_r17,0x200);
  asm_instruction_08(0x31,(uint)*(ushort *)(unaff_r14 + 0xc),1);
  if (!in_V) {
    func_0xbfdedf2c(unaff_r14 + -1,(int)*(short *)(*(short *)(param_3 + 0x3a) + 0xc));
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfe3d4(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfe3e8(int param_1,uint param_2,int param_3,int param_4,undefined4 param_5)

{
  byte bVar1;
  short sVar2;
  undefined4 extraout_r1;
  undefined4 uVar3;
  undefined4 extraout_r1_00;
  undefined4 uVar4;
  undefined1 uVar5;
  int iVar6;
  int unaff_r13;
  int unaff_r14;
  int unaff_r17;
  int unaff_gp;
  int in_r36;
  undefined4 in_r56;
  int iVar7;
  undefined1 in_Z;
  undefined1 uVar8;
  undefined1 in_N;
  char cVar9;
  undefined1 in_C;
  char in_V;
  
  *(char *)(param_1 + 0xd) = (char)param_3;
  if (unaff_r14 != 0) {
    param_2 = (uint)*(ushort *)(unaff_r14 + 0xc);
    param_1 = unaff_r14 + -1;
    unaff_r17 = asm_instruction_08(0x30,unaff_r17,0x200);
    in_Z = unaff_r17 == 0;
    in_N = unaff_r17 < 0;
  }
  sVar2 = *(short *)(param_3 + 0x3a);
  cVar9 = ext_condition(0x10);
  if (cVar9 != '\0') {
    param_1 = FUN_ram_bfcf6ffc(param_1,param_2);
  }
  *(char *)(unaff_r13 + 0xd) = (char)param_1;
  if ((bool)in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar4 = asm_instruction_06(0x1d,param_5,0x400);
  if ((bool)in_C || (bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  bVar1 = *(byte *)(param_1 + 0x1a);
  asm_instruction_06(0x20,param_1,0xfffffa0f);
  iVar7 = asm_instruction_08(0x22,in_r56,0x3f);
  *(char *)(param_4 + 0x15) = (char)sVar2;
  if (sVar2 != 0) {
    if (iVar7 != 0) {
      func_0xbfd8181c(*(undefined2 *)(unaff_gp + 0x16c));
    }
    FUN_ram_bfcfd5ac();
    iVar6 = asm_instruction_08(0,DAT_ram_bfcfe634,iVar7);
    uVar8 = iVar6 == 0;
    cVar9 = iVar6 < 0;
    uVar3 = asm_instruction_08(0x24,extraout_r1,0x200);
    asm_instruction_08(0x1c,uVar4,1);
    iVar7 = FUN_ram_bfcfe5c0(DAT_ram_bfcfe634,uVar3);
    uVar5 = (undefined1)iVar6;
    FUN_ram_bfcfd544(iVar7 + 4);
    if (!(bool)uVar8 && in_V == cVar9) {
      asm_instruction_08(0x22,unaff_r17,0x200);
      FUN_ram_bfcfd5d0();
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar4 = asm_instruction_06(4,(uint)*(byte *)(bVar1 + 8),0xfffffb44);
    uVar3 = asm_instruction_08(0x24,extraout_r1_00,0x100);
    uVar4 = asm_instruction_06(4,uVar4,0xfffffb48);
    *(undefined1 *)(in_r36 + 0x1b) = uVar5;
    if (!(bool)uVar8) {
      func_0xbfc68894(uVar4,uVar3);
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfe540(int param_1,undefined4 param_2,int param_3,undefined4 param_4,
                     undefined4 param_5)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined4 in_r8;
  undefined4 in_r12;
  int unaff_r14;
  undefined4 in_r24;
  undefined4 in_r56;
  int iVar4;
  bool in_Z;
  undefined1 uVar5;
  bool in_C;
  undefined1 in_V;
  ulonglong uVar6;
  
  uVar3 = asm_instruction_06(0x1d,param_5,0x600);
  if (in_C || in_Z) {
    param_1 = unaff_r14 + -1;
    asm_instruction_08(0x22,(uint)*(ushort *)(unaff_r14 + 0xc),0xfffff802);
  }
  else {
    asm_instruction_06(0x20,in_r24,0xfffffc1a);
    *(char *)(*(byte *)(param_1 + 0x1a) + 0x10) = (char)param_1;
    uVar3 = asm_instruction_06(0x1d,uVar3,0x400);
    if (!in_C && !in_Z) {
      asm_instruction_06(0x20,param_1,0xfffffa0f);
      iVar4 = asm_instruction_08(0x22,in_r56,0x3f);
      uVar5 = iVar4 < 0;
      uVar6 = (ulonglong)CONCAT24(*(undefined2 *)(unaff_r14 + 0xc),unaff_r14 + -1);
      uVar2 = *(undefined2 *)(*(byte *)(param_1 + 0x1a) + 0x1c);
      cVar1 = ext_condition(0x1e);
      if (cVar1 != '\0') {
        uVar6 = func_0xbfc9e168(unaff_r14 + -1,*(undefined2 *)(unaff_r14 + 0xc));
      }
      *(char *)(unaff_r14 + 1) = (char)uVar2;
      if (!(bool)in_V) {
        uVar6 = func_0xbfdee16c();
      }
      iVar4 = (int)uVar6;
      if (!(bool)in_V) {
        iVar4 = func_0xbfdee170(iVar4,(int)(uVar6 >> 0x20),param_3 + unaff_r14 * 8);
      }
      *(int *)(iVar4 + 0x20) = iVar4;
      if (!(bool)uVar5) {
        func_0xbfd81978();
      }
      FUN_ram_bfcfd688();
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  asm_instruction_06(2,param_3,in_r12);
  asm_instruction_06(0x22,param_3,in_r8);
  if (!(bool)in_V) {
    func_0xbfdee12c(param_1,(int)*(short *)(*(short *)(param_3 + 0x3a) + 0xc),param_3,param_4,uVar3)
    ;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcfe5c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  char cVar1;
  int in_r12;
  uint uVar2;
  undefined4 unaff_r13;
  
  cVar1 = ext_condition(0x1b);
  uVar2 = (uint)*(ushort *)(in_r12 + 6);
  if (cVar1 != '\0') {
    param_1 = func_0xbfcda9c0();
  }
  asm_instruction_06(0x22,param_1,0);
  *(undefined2 *)(uVar2 + 4) = param_4;
  FUN_ram_bfd1662c(param_1,unaff_r13);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfec1c(void)

{
  FUN_ram_bfcfde1c();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfec74(void)

{
  char cVar1;
  int unaff_gp;
  
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    FUN_ram_bfcf7874(*(undefined2 *)(unaff_gp + 0xf4));
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfed40(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  int unaff_r13;
  int unaff_r14;
  undefined4 *unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r20;
  undefined4 unaff_r22;
  int unaff_gp;
  undefined4 in_r37;
  undefined4 in_r50;
  undefined4 in_r52;
  undefined4 in_lp_count;
  
  iVar2 = asm_instruction_06(0x3c,param_1,0xb);
  asm_instruction_07(0x1d,in_r52,in_lp_count);
  if (unaff_r13 == 0) {
    while (iVar2 == 0) {
      iVar2 = FUN_ram_bfcfef2c();
    }
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
      thunk_FUN_ram_bfcf7a90(*(undefined2 *)(unaff_gp + -0x1bc));
    }
  }
  else {
    if (unaff_r14 != 0) {
      cVar1 = ext_condition(0x18);
      if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_07(0xe,in_r50,0x13a);
      func_0xbfcfedc8();
      func_0xbfcfedcc();
      asm_instruction_08(0x22,unaff_r17,0x3c0);
      *unaff_r16 = unaff_r20;
      asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    func_0xbfcfdf1c();
  }
  asm_instruction_08(0x22,unaff_r17,0x200);
  FUN_ram_bfcfdf3c(*(undefined1 *)(unaff_r13 + 10));
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfed5c(void)

{
  undefined4 *unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r20;
  undefined4 unaff_r22;
  undefined4 in_r37;
  
  FUN_ram_bfcfedcc();
  asm_instruction_08(0x22,unaff_r17,0x3c0);
  *unaff_r16 = unaff_r20;
  asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfed90(void)

{
  undefined1 in_r12;
  int unaff_r13;
  undefined4 unaff_r17;
  undefined4 in_r34;
  undefined4 in_r56;
  
  *(undefined1 *)(unaff_r13 + 0xd) = in_r12;
  asm_instruction_08(0x23,unaff_r17,0x200);
  FUN_ram_bfcfdfa0();
  asm_instruction_08(0,in_r56,in_r34);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfedcc(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     int param_5)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  int in_r12;
  uint unaff_r13;
  undefined4 unaff_r17;
  undefined4 unaff_r25;
  undefined4 in_r33;
  undefined4 in_r56;
  bool in_C;
  
  do {
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    while( true ) {
      uVar2 = *(undefined1 *)(unaff_r13 + 0x1f);
      iVar4 = asm_instruction_06(0x1c,param_5,0xfffff991);
      *(short *)(in_r12 + 4) = (short)*(undefined4 *)(in_r12 + 0x20);
      cVar1 = ext_condition(0x1c);
      if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (in_C || iVar4 == 0) {
        asm_instruction_08(0x22,unaff_r17,0x200);
        FUN_ram_bfcfdf3c(*(undefined1 *)(unaff_r13 + 10),uVar2,param_3,
                         *(undefined4 *)(in_r12 + 0x20));
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      param_1 = asm_instruction_06(0x1c,param_1,0xfffffa11);
      param_5 = asm_instruction_06(0x1c,iVar4,0xfffffa11);
      if (in_C || param_5 == 0) break;
      unaff_r13 = (uint)*(byte *)(param_1 + 0x1a);
      asm_instruction_06(0x20,param_1,0xfffffd07);
      param_1 = (uint)*(byte *)(unaff_r13 + 0xd);
      unaff_r25 = asm_instruction_08(0x22,unaff_r25,0x4bf);
      param_5 = asm_instruction_06(0x1c,param_5,0xfffffa11);
      if (!in_C && param_5 != 0) {
        uVar3 = asm_instruction_06(0x20,param_1,0xfffff83e);
        asm_instruction_08(0x22,uVar3,1);
        asm_instruction_06(0x1c,param_5,0xfffffa11);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    asm_instruction_08(0,in_r56,in_r33);
    if (unaff_r13 == 0) {
      param_5 = param_5 + -0xa4;
    }
    *(short *)(in_r12 + 4) = (short)param_1;
  } while( true );
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfee04(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 in_r4;
  
  uVar1 = asm_instruction_06(0x20,param_1,0xfffff83e);
  asm_instruction_08(0x22,uVar1,1);
  asm_instruction_06(0x1c,in_r4,0xfffffa11);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcfedf6) overlaps instruction at (ram,0xbfcfedf4)
    */

void FUN_ram_bfcfee48(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     int param_5,undefined4 param_6)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 in_r8;
  int in_r12;
  uint uVar5;
  int unaff_r14;
  undefined4 unaff_r17;
  int unaff_r25;
  undefined4 uVar6;
  undefined4 in_r33;
  int iVar7;
  undefined4 in_r56;
  bool bVar8;
  undefined1 in_C;
  undefined1 in_V;
  
  uVar3 = FUN_ram_bfcfee04();
  while( true ) {
    asm_instruction_07(0x1c,uVar3,unaff_r17);
    param_5 = asm_instruction_06(0x1c,param_5,0xfffff991);
    unaff_r25 = asm_instruction_08(0x22,unaff_r25,0x4bf);
    if (!(bool)in_C && unaff_r25 != 0) break;
    if (!(bool)in_V) {
      func_0xbfceec28();
    }
    uVar4 = asm_instruction_06(0x20,in_r8,0x20e);
    uVar3 = (uint)*(ushort *)(in_r12 + 4);
    cVar1 = ext_condition(0x1f);
    param_5 = asm_instruction_06(0x1c,param_5,0xfffffa11);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if ((bool)in_C || param_5 == 0) goto LAB_ram_bfcfee0c;
    in_r8 = asm_instruction_06(0x20,uVar4,0xfffffc1d);
    in_r56 = asm_instruction_08(0x22,in_r56,0x3f);
  }
  uVar5 = (uint)*(byte *)(*(byte *)(unaff_r14 + 0xb) + 0x1a);
  uVar4 = asm_instruction_06(0x20,(uint)*(byte *)(unaff_r14 + 0xb),0xfffff893);
  uVar6 = asm_instruction_08(0x22,unaff_r25,0x4bf);
  iVar7 = asm_instruction_07(0x1c,uVar4,unaff_r17);
  bVar8 = iVar7 == 0;
  uVar3 = func_0xbfcfdf70(uVar4,*(undefined1 *)(uVar5 + 0x1d));
  if (unaff_r14 == 0) {
    asm_instruction_05(0x21,param_6,0x6f7);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  if (!(bool)in_C && !bVar8) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  while( true ) {
    uVar6 = asm_instruction_08(0x22,uVar6,0x4bf);
    param_5 = asm_instruction_06(0x1c,param_5,0xfffffa11);
    if (!(bool)in_C && param_5 != 0) break;
    while( true ) {
      uVar2 = *(undefined1 *)(uVar5 + 0x1f);
      iVar7 = asm_instruction_06(0x1c,param_5,0xfffff991);
      *(short *)(in_r12 + 4) = (short)*(undefined4 *)(in_r12 + 0x20);
      cVar1 = ext_condition(0x1c);
      if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if ((bool)in_C || iVar7 == 0) {
        asm_instruction_08(0x22,unaff_r17,0x200);
        FUN_ram_bfcfdf3c(*(undefined1 *)(uVar5 + 10),uVar2,param_3,*(undefined4 *)(in_r12 + 0x20));
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      uVar3 = asm_instruction_06(0x1c,uVar3,0xfffffa11);
      param_5 = asm_instruction_06(0x1c,iVar7,0xfffffa11);
      if (!(bool)in_C && param_5 != 0) break;
      asm_instruction_08(0,in_r56,in_r33);
      if (uVar5 == 0) {
        param_5 = param_5 + -0xa4;
      }
      *(short *)(in_r12 + 4) = (short)uVar3;
      cVar1 = ext_condition(0x1c);
      if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    uVar5 = (uint)*(byte *)(uVar3 + 0x1a);
    asm_instruction_06(0x20,uVar3,0xfffffd07);
    uVar3 = (uint)*(byte *)(uVar5 + 0xd);
  }
  uVar4 = asm_instruction_06(0x20,uVar3,0xfffff83e);
  asm_instruction_08(0x22,uVar4,1);
LAB_ram_bfcfee0c:
  asm_instruction_06(0x1c,param_5,0xfffffa11);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcfef2c(int param_1)

{
  undefined4 in_r34;
  undefined4 in_r56;
  
  *(int *)(param_1 + 0x20) = param_1;
  FUN_ram_bfcfe138();
  asm_instruction_08(0,in_r56,in_r34);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcff318(void)

{
  int unaff_r14;
  
  if (unaff_r14 == 0) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfcff3f0(void)

{
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd02eac) overlaps instruction at (ram,0xbfd02eaa)
    */

void FUN_ram_bfcff66c(uint param_1,int param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  int extraout_r1;
  int extraout_r1_00;
  undefined4 in_r8;
  undefined2 uVar3;
  int unaff_r14;
  undefined4 unaff_r17;
  int unaff_r25;
  int unaff_gp;
  int in_r48;
  int iVar4;
  undefined4 in_mlo;
  char in_Z;
  undefined1 uVar5;
  bool bVar6;
  char in_N;
  undefined1 uVar7;
  undefined1 in_C;
  
  if (in_N != '\0') {
    *(char *)(unaff_r25 + 0x50) = (char)unaff_r17;
    cVar1 = ext_condition(0x16);
    if (cVar1 != '\0') {
      *(short *)(param_3 + 0x14) = (short)param_2;
      cVar1 = ext_condition(0x1d);
      if (cVar1 != '\0') {
        func_0xbfc25820();
      }
      asm_instruction_08(0x22,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_07(0x29,param_1,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
LAB_ram_bfd02e8c:
  if ((bool)in_C || (bool)in_Z) {
    asm_instruction_06(0x31,in_r48,in_mlo);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar4 = asm_instruction_06(0x31,in_r48,in_mlo);
  asm_instruction_08(0x22,param_1,0xfffffd80);
  if ((bool)in_C || iVar4 == 0) {
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(uint *)(*(ushort *)(unaff_r14 + 4) + 0x20) = (uint)*(ushort *)(unaff_r14 + 4);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar3 = (undefined2)unaff_r14;
  *(undefined2 *)(param_2 + 0x1e) = uVar3;
  in_r48 = asm_instruction_06(0x12,iVar4,0x339);
  uVar5 = in_r48 == 0;
  uVar7 = in_r48 < 0;
  do {
    in_r8 = asm_instruction_06(0,in_r8,DAT_ram_bfd02fa8);
    if (!(bool)uVar7 && !(bool)uVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (!(bool)uVar5) {
      func_0xbfdd80a8(DAT_ram_bfd02fa8);
      param_2 = extraout_r1;
    }
    while( true ) {
      param_1 = (uint)*(byte *)(unaff_gp + 100);
      if ((bool)in_C || (bool)uVar5) {
        in_r8 = asm_instruction_06(0,in_r8,param_1);
        if ((bool)uVar7) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        unaff_r25 = asm_instruction_08(0x32,unaff_r25,0x4bf);
        in_Z = unaff_r25 == 0;
        goto LAB_ram_bfd02e8c;
      }
      in_r48 = asm_instruction_06(0x32,in_r48,in_mlo);
      in_Z = in_r48 == 0;
      param_1 = asm_instruction_08(0x22,param_1,0xfffff900);
      if ((bool)in_C || (bool)in_Z) goto LAB_ram_bfd02e8c;
      *(undefined2 *)(param_2 + 0x1e) = uVar3;
      in_r48 = asm_instruction_06(0x12,in_r48,0x339);
      uVar5 = in_r48 == 0;
      uVar7 = in_r48 < 0;
      func_0xbfd174e4();
      in_r8 = asm_instruction_06(0,in_r8,(uint)*(byte *)(unaff_gp + 100));
      param_2 = extraout_r1_00;
      if ((bool)in_C || (bool)uVar5) break;
      in_r48 = asm_instruction_06(0x32,in_r48,in_mlo);
      uVar5 = in_r48 == 0;
      uVar7 = in_r48 < 0;
      uVar2 = asm_instruction_08(0x22,(uint)*(byte *)(unaff_gp + 100),0x500);
      if (!(bool)in_C && !(bool)uVar5) {
        *(undefined2 *)(extraout_r1_00 + 0x1e) = uVar3;
        iVar4 = asm_instruction_06(0x12,in_r48,0x339);
        bVar6 = iVar4 == 0;
        FUN_ram_bfd020a4(uVar2);
        cVar1 = ext_condition(0x11);
        if (bVar6) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        func_0xbfd020ac();
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
  } while( true );
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd0205c) overlaps instruction at (ram,0xbfd0205a)
    */

void FUN_ram_bfcff738(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  uint uVar4;
  int extraout_r1;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 in_r8;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  undefined4 unaff_r25;
  int iVar7;
  int unaff_gp;
  uint in_r36;
  uint in_r47;
  undefined4 in_r48;
  undefined4 uVar8;
  undefined4 in_r54;
  undefined4 in_r56;
  int iVar9;
  undefined4 in_mlo;
  bool bVar10;
  char cVar11;
  bool bVar12;
  undefined1 in_C;
  char in_V;
  undefined4 *in_stack_00000000;
  
  uVar5 = DAT_ram_bfcffae0;
  iVar9 = asm_instruction_06(0x25,in_r56,0xfffffc12);
  bVar10 = iVar9 == 0;
  bVar12 = iVar9 < 0;
  if (in_r36 < in_r47) {
    *(int *)(in_r12 + 0x78) = unaff_r13;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar6 = *(undefined4 *)(param_5 + 0x53);
  uVar3 = asm_instruction_08(0x22,param_1,param_2);
  if (bVar10 || (bool)in_V != bVar12) {
    uVar8 = asm_instruction_06(0x32,in_r48,in_mlo);
    *(char *)(unaff_r13 + 0x12) = (char)uVar3;
    uVar3 = asm_instruction_08(0x22,unaff_r25,0x4bf);
    asm_instruction_06(2,uVar8,0x39);
    func_0xc0302a04(*in_stack_00000000);
    uVar5 = asm_instruction_08(0x23,uVar6,0x26);
    asm_instruction_08(0x23,uVar5,0x26);
    func_0xbfd16508(*(undefined2 *)(extraout_r1 + 0x18));
    asm_instruction_06(0x20,param_3,0);
    asm_instruction_06(0,in_r8,0);
    iVar9 = asm_instruction_08(0x34,uVar3,0x4bf);
    if ((bool)in_C || iVar9 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0x32,uVar8,in_mlo);
    *(undefined1 *)(unaff_r13 + 0xf) = *(undefined1 *)(unaff_gp + 100);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar4 = (uint)*(ushort *)(in_r12 + 4);
  if (bVar10 || (bool)in_V != bVar12) {
    uVar2 = *(undefined2 *)(uVar4 + 8);
    iVar9 = *(int *)(unaff_gp + 0x110);
    *(undefined4 *)(iVar9 + -0xe4) = unaff_r20;
    iVar7 = asm_instruction_08(0x22,unaff_r25,0x4bf);
    cVar11 = iVar7 == 0;
    FUN_ram_bfd0096c(iVar9,uVar2);
    if (cVar11 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar11 = ext_condition(0x11);
  *(char *)(param_4 + 0x10) = (char)*(ushort *)(in_r12 + 4);
  if (cVar11 != '\0') {
    if (bVar10 || (bool)in_V != bVar12) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar5 = 0xbfd0486c;
    iVar9 = FUN_ram_bfd04974();
    *(short *)(iVar9 + -0xa4) = (short)unaff_r20;
    *(short *)(param_3 + 0x12) = (short)unaff_r13;
    if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(short *)(in_r12 + 4) = (short)iVar9;
    if (unaff_r14 == 0) {
      asm_instruction_06(0x20,iVar9,uVar5);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar11 = ext_condition(0x10);
  if (cVar11 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar9 = asm_instruction_05(0x1d,in_r54,in_r54);
  if (iVar9 == 0) {
    uVar4 = func_0xbfcdbc68();
  }
  cVar11 = ext_condition(0x10);
  if (cVar11 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar9 = asm_instruction_08(0x26,uVar4,uVar4);
  asm_instruction_05(0x2d,unaff_r21,unaff_r25);
  *(char *)((unaff_r13 >> 6) + 0x17) = (char)uVar5;
  uVar5 = asm_instruction_05(0xd,unaff_r14,1);
  cVar11 = ext_condition(0x19);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar11 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(short *)(iVar9 + 0x2c) = (short)uVar5;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcff80c(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  char cVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined4 uVar4;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined1 unaff_r15;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  undefined4 unaff_r25;
  int iVar5;
  int unaff_gp;
  undefined4 in_r54;
  int iVar6;
  bool in_Z;
  char cVar7;
  char in_N;
  char in_V;
  
  asm_instruction_08(0x22,param_1,param_2);
  uVar3 = (uint)*(ushort *)(in_r12 + 4);
  if (in_Z || in_V != in_N) {
    uVar2 = *(undefined2 *)(uVar3 + 8);
    iVar6 = *(int *)(unaff_gp + 0x110);
    *(undefined4 *)(iVar6 + -0xe4) = unaff_r20;
    iVar5 = asm_instruction_08(0x22,unaff_r25,0x4bf);
    cVar7 = iVar5 == 0;
    FUN_ram_bfd0096c(iVar6,uVar2);
    if (cVar7 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar7 = ext_condition(0x11);
  *(char *)(param_4 + 0x10) = (char)*(ushort *)(in_r12 + 4);
  if (cVar7 != '\0') {
    if (in_Z || in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar4 = 0xbfd0486c;
    iVar6 = FUN_ram_bfd04974();
    *(short *)(iVar6 + -0xa4) = (short)unaff_r20;
    *(short *)(param_3 + 0x12) = (short)unaff_r13;
    if (unaff_r14 != 0) {
      *(short *)(in_r12 + 4) = (short)iVar6;
      if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_06(0x20,iVar6,uVar4);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar7 = ext_condition(0x10);
  if (cVar7 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar6 = asm_instruction_05(0x1d,in_r54,in_r54);
  if (iVar6 == 0) {
    uVar3 = func_0xbfcdbc68();
  }
  cVar7 = ext_condition(0x10);
  if (cVar7 == '\0') {
    iVar6 = asm_instruction_08(0x26,uVar3,uVar3);
    asm_instruction_05(0x2d,unaff_r21,unaff_r25);
    *(undefined1 *)((unaff_r13 >> 6) + 0x17) = unaff_r15;
    uVar4 = asm_instruction_05(0xd,unaff_r14,1);
    cVar7 = ext_condition(0x19);
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (cVar7 == '\0') {
      *(short *)(iVar6 + 0x2c) = (short)uVar4;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcff834(int param_1)

{
  char cVar1;
  undefined4 uVar3;
  int unaff_r13;
  undefined4 unaff_r14;
  undefined1 unaff_r15;
  undefined4 unaff_r21;
  undefined4 unaff_r25;
  char cVar2;
  
  asm_instruction_05(0x2d,unaff_r21,unaff_r25);
  *(undefined1 *)((unaff_r13 >> 6) + 0x17) = unaff_r15;
  uVar3 = asm_instruction_05(0xd,unaff_r14,1);
  cVar1 = ext_condition(0x19);
  cVar2 = ext_condition(0x10);
  if (cVar2 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 == '\0') {
    *(short *)(param_1 + 0x2c) = (short)uVar3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcff8e0(void)

{
  char cVar1;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcff9b4(void)

{
  undefined4 unaff_r25;
  bool in_Z;
  bool in_C;
  
  if (in_C || in_Z) {
    asm_instruction_08(0x30,unaff_r25,0x4bf);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcffaa4(int param_1)

{
  undefined4 unaff_r18;
  undefined2 unaff_r21;
  undefined4 unaff_r25;
  undefined4 in_r48;
  
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  asm_instruction_07(2,in_r48,param_1);
  *(undefined4 *)(param_1 + -0xe4) = unaff_r18;
  *(undefined2 *)(param_1 + -0xe4) = unaff_r21;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcffac4(undefined4 param_1)

{
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int unaff_gp;
  
  *(char *)(unaff_r13 + 0x14) = (char)*(undefined4 *)(in_r12 + 0x18);
  if (unaff_r14 != 0) {
    asm_instruction_06(0,param_1,7);
  }
  asm_instruction_07(0x1c,(uint)*(ushort *)(unaff_gp + 0x122),0xc);
  FUN_ram_bfcfec1c((uint)*(ushort *)(unaff_gp + 0x122));
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcffc24(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcffd2c(void)

{
  char in_N;
  char in_V;
  
  if (in_N == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcffdf4(undefined4 param_1)

{
  int unaff_r13;
  
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0,param_1,0xf);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcffe50(void)

{
  char cVar1;
  
  FUN_ram_bfcffe48();
  FUN_ram_bfcffe4c();
  FUN_ram_bfcffe50();
  cVar1 = ext_condition(0x1b);
  if (cVar1 != '\0') {
    func_0xbfd97a54();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfcffe32) */

void FUN_ram_bfcffe94(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 in_r35;
  undefined4 in_r48;
  undefined8 uVar2;
  
  ext_condition(0x14);
  iVar1 = *(int *)(param_3 + 0x70);
  FUN_ram_bfcff66c();
  *(char *)(param_3 + 0x1f) = (char)iVar1;
  uVar2 = func_0xbfcd45bc();
  do {
  } while ((int)((ulonglong)uVar2 >> 0x20) != 0);
  *(int *)((int)uVar2 + 0x28) = iVar1;
  if (iVar1 == 0) {
    asm_instruction_07(0x24,in_r35,in_r48);
    uRam0000000a = 0;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfcffeb8(void)

{
  char cVar1;
  undefined4 unaff_fp;
  
  cVar1 = ext_condition(0x10);
  asm_instruction_06(0x31,unaff_fp,0x10);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00048(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd00180(undefined4 param_1,undefined4 param_2,int param_3,uint param_4,
                     undefined4 param_5,undefined4 param_6)

{
  short sVar1;
  undefined4 uVar2;
  undefined4 extraout_r1;
  undefined2 uVar3;
  uint uVar4;
  undefined4 in_r11;
  int in_r12;
  int unaff_r13;
  undefined4 unaff_r18;
  int iVar5;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r40;
  undefined4 in_r48;
  int in_r56;
  bool bVar6;
  undefined1 uVar7;
  char cVar8;
  undefined1 in_V;
  
  asm_instruction_08(0x3a,unaff_r25,0x47f);
  iVar5 = asm_instruction_06(0x1a,in_r11,0x3e);
  bVar6 = iVar5 == 0;
  cVar8 = iVar5 < 0;
  asm_instruction_08(0x1a,param_6,0x30);
  uVar2 = func_0xbfcdbdcc();
  uVar3 = (undefined2)param_4;
  if ((bool)in_V) {
    uVar7 = *(undefined1 *)(unaff_r13 + 0xb);
    *(undefined2 *)(in_r12 + 4) = uVar3;
    FUN_ram_bfd12b32(uVar7);
    return;
  }
  if (bVar6 || in_V != cVar8) {
    if (!bVar6) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    while (unaff_r13 != 0) {
      in_r56 = asm_instruction_06(0x2b,in_r56,0xfffffc12);
      bVar6 = in_r56 == 0;
      cVar8 = in_r56 < 0;
    }
    *(undefined2 *)(in_r12 + 4) = uVar3;
    if (bVar6 || in_V != cVar8) {
      cVar8 = ext_condition(0x12);
      if (cVar8 != '\0') {
        func_0xbfcea5dc(uVar2,unaff_r13 + 2);
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(in_r12 + 4) = uVar3;
  FUN_ram_bfd00180();
  FUN_ram_bfd005b8();
  cVar8 = ext_condition(0x19);
  iVar5 = asm_instruction_04(0x1d,in_r40,0);
  uVar7 = iVar5 == 0;
  bVar6 = iVar5 < 0;
  if (cVar8 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar4 = param_4;
  func_0xbfcff638();
  if (bVar6) {
    sVar1 = *(short *)(unaff_r13 + 0x1c);
    if (!(bool)in_V) {
      func_0xbfdeadb4();
    }
    cVar8 = ext_condition(0x1c);
    if (cVar8 != '\0') {
      func_0xbfd23db8();
    }
    uVar7 = *(undefined1 *)(sVar1 + 5);
    *(undefined1 *)(sVar1 + 0x1f) = uVar7;
    cVar8 = ext_condition(0x1c);
    if (cVar8 != '\0') {
      func_0xbfd23dd0(uVar7,param_3 + uVar4);
    }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  if (bVar6) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (bVar6) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcff748();
  if (bVar6) {
    *(undefined4 *)((((int)((uint)(in_r12 << 1) >> 5) >> 5) - 9U | 0x2000) + 8) = extraout_r1;
    if (!(bool)uVar7) {
      func_0xbfd7ee84(unaff_gp + -0x138,extraout_r1,param_4,uVar4 & 0xff);
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!bVar6) {
    cVar8 = ext_condition(0x19);
    if (cVar8 == '\0') {
      asm_instruction_06(0x39,uVar4,unaff_r18);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(4,in_r48,0xfffffb06);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd0019c(undefined4 param_1,undefined4 param_2,int param_3,uint param_4)

{
  char cVar1;
  short sVar2;
  undefined4 extraout_r1;
  uint uVar3;
  int in_r12;
  int unaff_r13;
  undefined4 unaff_r18;
  int unaff_gp;
  undefined4 in_r40;
  int iVar4;
  undefined4 in_r48;
  undefined1 uVar5;
  bool bVar6;
  undefined1 in_V;
  
  FUN_ram_bfd00180();
  FUN_ram_bfd005b8();
  cVar1 = ext_condition(0x19);
  iVar4 = asm_instruction_04(0x1d,in_r40,0);
  uVar5 = iVar4 == 0;
  bVar6 = iVar4 < 0;
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar3 = param_4;
  func_0xbfcff638();
  if (bVar6) {
    sVar2 = *(short *)(unaff_r13 + 0x1c);
    if (!(bool)in_V) {
      func_0xbfdeadb4();
    }
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
      func_0xbfd23db8();
    }
    uVar5 = *(undefined1 *)(sVar2 + 5);
    *(undefined1 *)(sVar2 + 0x1f) = uVar5;
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
      func_0xbfd23dd0(uVar5,param_3 + uVar3);
    }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  if (bVar6) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!bVar6) {
    FUN_ram_bfcff748();
    if (bVar6) {
      *(undefined4 *)((((int)((uint)(in_r12 << 1) >> 5) >> 5) - 9U | 0x2000) + 8) = extraout_r1;
      if (!(bool)uVar5) {
        func_0xbfd7ee84(unaff_gp + -0x138,extraout_r1,param_4,uVar3 & 0xff);
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (!bVar6) {
      cVar1 = ext_condition(0x19);
      if (cVar1 == '\0') {
        asm_instruction_06(0x39,uVar3,unaff_r18);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(4,in_r48,0xfffffb06);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd002ec(void)

{
  char cVar1;
  int unaff_gp;
  undefined4 in_r49;
  undefined1 in_V;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcffaa4();
  cVar1 = ext_condition(0x18);
  if (cVar1 != '\0') {
    func_0xc071e7fc();
    func_0xc031c7d8();
    if ((bool)in_V) {
      func_0xbfd1efa4(unaff_gp + -0x78);
    }
    asm_instruction_08(0x29,in_r49,0x67b);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    cVar1 = ext_condition(0x10);
    if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00340(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00474(void)

{
  char cVar1;
  int unaff_r13;
  undefined4 uVar2;
  int unaff_gp;
  undefined4 in_r33;
  undefined4 in_r38;
  
  uVar2 = asm_instruction_08(2,in_r38,0x21);
  asm_instruction_08(3,in_r38,in_r33);
  FUN_ram_bfcff60c(*(undefined4 *)(unaff_gp + 0x94));
  asm_instruction_08(0x22,uVar2,0xffffffff);
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    func_0xbfcf90ac(*(undefined1 *)(unaff_r13 + 0x11));
  }
  *(char *)(unaff_r13 + 3) = (char)*(undefined4 *)(unaff_r13 + 0x50);
  FUN_ram_bfd00624();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00540(undefined4 param_1)

{
  undefined4 in_r8;
  undefined4 uVar1;
  undefined4 in_r9;
  
  asm_instruction_04(0x3d,in_r9,param_1);
  uVar1 = asm_instruction_04(0x3d,in_r8,0);
  uVar1 = asm_instruction_04(0x3d,uVar1,0xfffff900);
  asm_instruction_04(0x3d,uVar1,0);
  asm_instruction_04(0x3d,uVar1,param_1);
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd005b8(void)

{
  char cVar1;
  int unaff_r13;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r33;
  undefined4 in_r38;
  
  asm_instruction_08(2,in_r38,0x21);
  asm_instruction_08(3,in_r38,in_r33);
  FUN_ram_bfcff738(*(undefined4 *)(unaff_gp + 0x90));
  asm_instruction_08(0x22,unaff_r25,0xffffffff);
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    FUN_ram_bfcf91d4(*(undefined1 *)(unaff_r13 + 0x11));
  }
  *(char *)(unaff_r13 + 3) = (char)*(undefined4 *)(unaff_r13 + 0x50);
  do {
  } while (unaff_r13 == 0);
  FUN_ram_bfd00750();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00624(void)

{
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00750(void)

{
  char cVar1;
  int unaff_r13;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r33;
  undefined4 in_r38;
  
  asm_instruction_08(2,in_r38,0x21);
  asm_instruction_08(3,in_r38,in_r33);
  FUN_ram_bfcff8e0(*(undefined4 *)(unaff_gp + 0x90));
  asm_instruction_08(0x22,unaff_r25,0xffffffff);
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    FUN_ram_bfcf937c(*(undefined1 *)(unaff_r13 + 0x11));
  }
  *(char *)(unaff_r13 + 3) = (char)*(undefined4 *)(unaff_r13 + 0x50);
  do {
  } while (unaff_r13 == 0);
  thunk_FUN_ram_bfd007f0();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00784(undefined1 param_1)

{
  int unaff_r13;
  
  *(undefined1 *)(unaff_r13 + 3) = param_1;
  do {
  } while (unaff_r13 == 0);
  thunk_FUN_ram_bfd007f0();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd007f0(void)

{
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00828(void)

{
  char cVar1;
  int unaff_r13;
  undefined4 uVar2;
  int unaff_gp;
  undefined4 in_r33;
  undefined4 in_r38;
  
  uVar2 = asm_instruction_08(2,in_r38,0x21);
  asm_instruction_08(3,in_r38,in_r33);
  FUN_ram_bfcff9b4(*(undefined4 *)(unaff_gp + 0x94));
  asm_instruction_08(0x22,uVar2,0xffffffff);
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    FUN_ram_bfcf9454(*(undefined1 *)(unaff_r13 + 0x11));
  }
  *(char *)(unaff_r13 + 3) = (char)*(undefined4 *)(unaff_r13 + 0x50);
  func_0xbfd009cc();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0085c(void)

{
  func_0xbfd009cc();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd008cc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0096c(void)

{
  FUN_ram_bfd00adc();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00980(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint in_r5;
  int iVar3;
  int iVar4;
  int unaff_r13;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r25;
  undefined4 in_r52;
  int in_r53;
  uint in_r56;
  undefined1 uVar5;
  bool in_V;
  bool bVar6;
  
  uVar5 = (in_r5 & (uint)(1 << ((byte)in_r52 & 0x1f)) >> 1) != 0;
  asm_instruction_05(8,in_r53,in_r56);
  if (!in_V) {
    func_0xbfd5ae2c(param_1,param_1 + 3);
  }
  uVar1 = in_r56 & 0x3f;
  if ((in_r56 & 0x20) == 0) {
    iVar3 = in_r53 << uVar1;
    if (iVar3 >> uVar1 == in_r53) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
      if (in_r53 < 0) {
        iVar3 = -0x80000000;
      }
      else {
        iVar3 = 0x7fffffff;
      }
    }
  }
  else {
    iVar3 = in_r53 >> 0x40 - uVar1;
    bVar6 = false;
  }
  if (bVar6 == iVar3 < 0) {
    func_0xbfd5ae3c(*(undefined1 *)(unaff_r13 + 6));
  }
  iVar4 = asm_instruction_05(0xe,in_r53,in_r56);
  if ((bool)uVar5 || iVar4 == 0) {
    func_0xbfd5ae48(*(undefined1 *)(unaff_r13 + 6));
  }
  asm_instruction_08(0x22,unaff_r17,0x3c0);
  uVar2 = asm_instruction_06(2,unaff_r16,0x20);
  asm_instruction_05(0x22,iVar3,in_r52);
  iVar3 = asm_instruction_08(0x22,unaff_r25,0xffffffff);
  if (iVar3 != 0) {
    func_0xbfd83dc8(uVar2);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00adc(void)

{
  char cVar1;
  ushort *puVar2;
  ushort *puVar3;
  undefined4 in_r9;
  undefined4 uVar4;
  int unaff_r14;
  undefined4 unaff_r25;
  int iVar5;
  char in_N;
  char in_V;
  
  if (in_V != in_N) {
    func_0xbfcdcadc(DAT_ram_bfd00c1c);
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    func_0xbfca1784();
  }
  if (!(bool)in_V) {
    func_0xbfc1aae8();
  }
  cVar1 = ext_condition(0x10);
  puVar2 = DAT_ram_bfd00c2c;
  if (cVar1 != '\0') {
    puVar2 = (ushort *)func_0xbfca1798();
  }
  puVar3 = puVar2 + -0x80;
  iVar5 = asm_instruction_08(0x22,unaff_r25,0xffffffff);
  if (unaff_r14 != 0) {
    if (iVar5 != 0) {
      func_0xbfd83fa8(puVar3);
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar4 = asm_instruction_04(0x3d,in_r9,0x101);
  asm_instruction_04(0x3d,uVar4,0);
  asm_instruction_04(0x3d,uVar4,puVar3);
  uVar4 = asm_instruction_04(0x3d,(uint)*puVar2,0);
  uVar4 = asm_instruction_04(0x3d,uVar4,0xfffff900);
  asm_instruction_04(0x3d,uVar4,0);
  asm_instruction_04(0x3d,uVar4,puVar3);
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00d44(void)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_r13;
  int unaff_gp;
  undefined4 in_r33;
  undefined4 in_r38;
  
  asm_instruction_08(3,in_r38,in_r33);
  FUN_ram_bfcffeb8(*(undefined4 *)(unaff_gp + 0x15c));
  uVar2 = asm_instruction_08(0x22,*(undefined4 *)(unaff_r13 + 0x60),
                             *(undefined4 *)(unaff_r13 + 0x60));
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    FUN_ram_bfcf9954(uVar2);
  }
  *(char *)(unaff_r13 + 3) = (char)*(undefined4 *)(unaff_r13 + 0x50);
  do {
  } while (unaff_r13 == 0);
  FUN_ram_bfd00ed0();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00e08(void)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_r13;
  undefined4 in_r33;
  undefined4 in_r38;
  
  asm_instruction_08(2,in_r38,0x21);
  asm_instruction_08(3,in_r38,in_r33);
  func_0xbfcfff80();
  uVar2 = asm_instruction_08(0x22,*(undefined4 *)(unaff_r13 + 0x60),
                             *(undefined4 *)(unaff_r13 + 0x60));
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    FUN_ram_bfcf9a1c(uVar2);
  }
  *(char *)(unaff_r13 + 3) = (char)*(undefined4 *)(unaff_r13 + 0x50);
  FUN_ram_bfd00f94();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00ed0(void)

{
  char cVar1;
  int unaff_r13;
  undefined4 uVar2;
  int unaff_gp;
  undefined4 in_r33;
  undefined4 in_r38;
  
  uVar2 = asm_instruction_08(2,in_r38,0x21);
  asm_instruction_08(3,in_r38,in_r33);
  FUN_ram_bfd00048(*(undefined4 *)(unaff_gp + 0x90));
  asm_instruction_08(0x22,uVar2,0xffffffff);
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    FUN_ram_bfcf9ae8(*(undefined1 *)(unaff_r13 + 0x11));
  }
  *(char *)(unaff_r13 + 3) = (char)*(undefined4 *)(unaff_r13 + 0x50);
  FUN_ram_bfd01060();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd00f94(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd01060(void)

{
  undefined4 in_r37;
  
  asm_instruction_05(0x3c,in_r37,0x2f);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd011b4(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd01284(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd013c0(void)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_r13;
  int unaff_gp;
  undefined4 in_r33;
  undefined4 in_r38;
  
  asm_instruction_08(2,in_r38,0x21);
  asm_instruction_08(3,in_r38,in_r33);
  FUN_ram_bfd00540(*(undefined4 *)(unaff_gp + 0x90));
  uVar2 = asm_instruction_08(0x22,*(undefined4 *)(unaff_r13 + 0x60),
                             *(undefined4 *)(unaff_r13 + 0x60));
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    FUN_ram_bfcf9fdc(uVar2);
  }
  *(char *)(unaff_r13 + 3) = (char)*(undefined4 *)(unaff_r13 + 0x50);
  do {
  } while (unaff_r13 == 0);
  FUN_ram_bfd01558();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0148c(void)

{
  char cVar1;
  int unaff_r13;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r33;
  undefined4 in_r38;
  
  asm_instruction_08(2,in_r38,0x21);
  asm_instruction_08(3,in_r38,in_r33);
  func_0xbfd0060c(*(undefined4 *)(unaff_gp + 0x90));
  asm_instruction_08(0x22,unaff_r25,0xffffffff);
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    FUN_ram_bfcfa0ac(*(undefined1 *)(unaff_r13 + 0x11));
  }
  *(char *)(unaff_r13 + 3) = (char)*(undefined4 *)(unaff_r13 + 0x50);
  func_0xbfd01624();
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd014f0(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd01558(void)

{
  bool in_Z;
  char in_N;
  char in_V;
  
  if (!in_Z && in_V == in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd016d6) overlaps instruction at (ram,0xbfd016d4)
    */

void FUN_ram_bfd016ac(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 extraout_r1;
  undefined2 extraout_r1_00;
  undefined2 uVar3;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r54;
  int in_r55;
  undefined4 in_r56;
  bool in_Z;
  bool bVar4;
  char cVar5;
  undefined1 in_C;
  char in_V;
  undefined6 uVar6;
  
  uVar1 = asm_instruction_08(0x22,param_1,param_4);
  if (!(bool)in_C && !in_Z) {
    iVar2 = asm_instruction_06(0x1c,uVar1,0xfffffc90);
    bVar4 = iVar2 == 0;
    cVar5 = iVar2 < 0;
    uVar6 = FUN_ram_bfd00828(iVar2,*(undefined2 *)(unaff_r14 + 0xc));
    uVar3 = (undefined2)((uint6)uVar6 >> 0x20);
    *(char *)(unaff_r13 + 10) = (char)uVar6;
    if (bVar4 || in_V != cVar5) {
      cVar5 = ext_condition(0x10);
      if (cVar5 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      cVar5 = ext_condition(0x1d);
      if (cVar5 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar1 = asm_instruction_08(0x30,unaff_r25,0x4bf);
    if (unaff_r13 == 0) {
      func_0xbfd00814();
      uVar3 = extraout_r1_00;
    }
    else {
      *(short *)((int)uVar6 + -0xa4) = (short)unaff_r17;
      *(undefined4 *)(in_r55 + -0x3d) = in_r56;
      cVar5 = ext_condition(0x10);
      if (cVar5 != '\0') {
        FUN_ram_bfcfa2d4(*(undefined2 *)(unaff_gp + 0x176));
        uVar3 = extraout_r1;
      }
    }
    if (unaff_r14 == 0) {
      asm_instruction_05(0x26,unaff_r13,unaff_r16);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar2 = asm_instruction_08(0x22,uVar1,0x4bf);
    if ((bool)in_C || iVar2 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(undefined2 *)(unaff_r13 + 0x38) = uVar3;
    asm_instruction_06(2,in_r54,param_7);
    cVar5 = ext_condition(0x10);
    if (cVar5 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar5 = ext_condition(0x1c);
    if (cVar5 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_08(0x22,unaff_r17,0x200);
    FUN_ram_bfd00784(*(undefined2 *)(in_r12 + 0x20),*(undefined4 *)(in_r12 + 0x70));
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0196c(void)

{
  int iVar1;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined4 in_ilink2;
  undefined4 in_r56;
  char in_V;
  
  if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r14 != 0) {
    *(short *)(in_r12 + 4) = (short)in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(2,in_r56,0x43f);
  iVar1 = asm_instruction_05(0xd,in_ilink2,2);
  if (iVar1 == 0 || (bool)in_V != iVar1 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd019d4(void)

{
  int in_r12;
  undefined4 in_r50;
  bool in_Z;
  
  if (!in_Z) {
    func_0xbfd02e34();
  }
  asm_instruction_05(0x10,in_r50,0x39);
  *(short *)(in_r12 + 10) = (short)in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd01ba0(void)

{
  char cVar1;
  undefined4 in_r32;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    asm_instruction_06(0x23,in_r32,9);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd01d14(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  char cVar1;
  undefined4 in_r8;
  undefined4 in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r17;
  int iVar2;
  undefined4 unaff_r25;
  undefined4 in_mmid;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 in_C;
  
  *(char *)(unaff_r13 + 0x13) = (char)param_1;
  asm_instruction_06(0x12,in_mmid,8);
  asm_instruction_08(0x30,unaff_r25,0x4bf);
  iVar2 = asm_instruction_06(0x10,in_mmid,in_r8);
  uVar3 = iVar2 == 0;
  uVar4 = iVar2 < 0;
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    param_1 = func_0xbfd1b390();
  }
  if (!(bool)in_C && !(bool)uVar3) {
    func_0xbfd02bc0();
    cVar1 = ext_condition(0x10);
    if (cVar1 == '\0') {
      *(undefined2 *)(unaff_r14 + 0x20) = param_3;
      FUN_ram_bfd01d14(in_r12);
      if (!(bool)uVar4 && !(bool)uVar3) {
        func_0xbfc9a1c4();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_07(0x1c,param_1,unaff_r17);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd01d40(void)

{
  char cVar1;
  int in_r12;
  undefined4 in_r36;
  undefined4 in_mlo;
  
  asm_instruction_05(0xd,in_r36,in_mlo);
  FUN_ram_bfd02be0();
  cVar1 = ext_condition(0x19);
  if (cVar1 != '\0') {
    func_0xbfc5a948(in_r12 + -6);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd01d6c(void)

{
  int unaff_r13;
  undefined4 in_r56;
  
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0x20,in_r56,0x3e);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd01d78(undefined4 param_1)

{
  asm_instruction_06(0,param_1,3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd01e1c(void)

{
  undefined4 unaff_r25;
  undefined4 in_r40;
  
  asm_instruction_06(2,in_r40,0x2f);
  asm_instruction_08(0x22,unaff_r25,0x43f);
  asm_instruction_06(2,in_r40,0x2c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd01e40(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd020a4(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 in_r8;
  undefined4 uVar1;
  int unaff_r13;
  int iVar2;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r48;
  undefined4 in_mlo;
  undefined1 in_Z;
  undefined1 in_C;
  
  if (!(bool)in_Z) {
    func_0xbfdd72a4();
  }
  uVar1 = asm_instruction_06(0,in_r8,0);
  if (!(bool)in_C && !(bool)in_Z) {
    asm_instruction_06(0x32,in_r48,in_mlo);
    uVar1 = asm_instruction_08(0x31,(uint)*(byte *)(unaff_gp + 100),0xc0);
    *(char *)(*(int *)(param_3 + 0x10) + 0x1a) = (char)uVar1;
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  if (!(bool)in_Z) {
    func_0xbfdd727c();
  }
  asm_instruction_06(0x20,param_3,0);
  asm_instruction_06(0,uVar1,0);
  iVar2 = asm_instruction_08(0x34,unaff_r25,0x4bf);
  if (!(bool)in_C && iVar2 != 0) {
    asm_instruction_06(0x32,in_r48,in_mlo);
    *(undefined1 *)(unaff_r13 + 0xf) = *(undefined1 *)(unaff_gp + 100);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd023e0(int param_1,undefined4 param_2,undefined2 param_3)

{
  int in_r12;
  
  *(undefined2 *)(in_r12 + 6) = param_3;
  *(int *)(param_1 + 0x3c) = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd02438(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int in_r12;
  undefined4 unaff_r13;
  undefined4 unaff_r17;
  undefined4 uVar1;
  
  uVar1 = asm_instruction_08(0x22,unaff_r17,0x3c0);
  asm_instruction_05(0x2d,unaff_r13,uVar1);
  *(undefined2 *)(in_r12 + 6) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd02444(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int in_r12;
  
  *(undefined2 *)(in_r12 + 6) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0244c(int param_1,undefined4 param_2,int param_3,undefined1 param_4)

{
  int in_r12;
  undefined4 uVar1;
  int unaff_r13;
  undefined4 uVar2;
  undefined4 unaff_r17;
  undefined2 unaff_r18;
  bool in_Z;
  bool in_C;
  
  if ((unaff_r13 != 0) && (in_C || in_Z)) {
    uVar1 = *(undefined4 *)(in_r12 + 0x24);
    *(short *)(in_r12 + 6) = (short)param_3;
    *(int *)(param_1 + 0x3c) = param_1;
    if (in_Z != false) {
      uVar2 = asm_instruction_08(0x30,unaff_r17,0x3c0);
      asm_instruction_05(0x2d,uVar1,uVar2);
      *(short *)(in_r12 + 6) = (short)param_3;
      *(int *)(param_1 + 0x3c) = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined1 *)(param_3 + 0xb) = param_4;
  *(undefined2 *)(param_1 + -0xa4) = unaff_r18;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0260c(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r24;
  undefined1 in_Z;
  char in_N;
  undefined1 in_C;
  char in_V;
  
  asm_instruction_08(0x10,in_r24,param_2);
  uVar2 = FUN_ram_bfd0260c();
  uVar2 = asm_instruction_06(0x1e,uVar2,0x740);
  iVar3 = FUN_ram_bfd01808(uVar2);
  if (in_N != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_V != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((bool)in_C || (bool)in_Z) {
    iVar3 = asm_instruction_08(0x22,iVar3,param_4);
  }
  else {
    cVar1 = ext_condition(0x10);
    if (cVar1 == '\0') {
      cVar1 = ext_condition(0x13);
      if (cVar1 == '\0') {
        cVar1 = ext_condition(0x16);
        if (cVar1 == '\0') {
          cVar1 = ext_condition(0x17);
          if (cVar1 == '\0') {
            cVar1 = ext_condition(0x1c);
            if (cVar1 != '\0') {
              halt_baddata();
            }
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
        }
        else {
          iVar3 = asm_instruction_08(0x22,iVar3,0x340);
        }
        *(short *)(iVar3 + 0x28) = (short)iVar3;
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      goto LAB_ram_bfd038e4;
    }
  }
  asm_instruction_06(0x10,param_7,0);
LAB_ram_bfd038e4:
  *(undefined2 *)(iVar3 + 0x24) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd026f8(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  undefined4 in_r9;
  int unaff_r13;
  int unaff_r15;
  undefined4 in_r37;
  undefined4 in_r43;
  char in_Z;
  
  if (unaff_r15 != 0) {
    asm_instruction_04(0x3d,in_r43,in_r9);
    asm_instruction_08(0x1f,in_r37,0x175);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(param_3 + 0x22) = 0;
  cVar1 = ext_condition(0x18);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_Z != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd02800(undefined1 param_1,undefined2 param_2,undefined4 param_3,undefined2 param_4,
                     int param_5)

{
  char cVar1;
  uint uVar2;
  undefined2 in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined1 uVar3;
  undefined4 uVar4;
  undefined4 unaff_r25;
  int unaff_gp;
  int iVar5;
  undefined4 in_r56;
  bool in_Z;
  char in_N;
  char in_V;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined1 *)(unaff_r13 + 9) = param_1;
  uVar4 = *(undefined4 *)(param_5 + 0x5d);
  *(undefined2 *)(unaff_r14 + 0x20) = in_r12;
  cVar1 = ext_condition(0x12);
  if (cVar1 == '\0') {
    *(undefined2 *)(unaff_r14 + 4) = param_2;
    cVar1 = ext_condition(0x1d);
    if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar2 = (uint)*(ushort *)(unaff_gp + 8);
  uVar3 = (undefined1)uVar4;
  *(undefined1 *)(uVar2 - 0xe4) = uVar3;
  *(undefined1 *)(uVar2 - 0xa4) = uVar3;
  *(undefined2 *)(uVar2 + 4) = param_4;
  if (in_V != in_N) {
    asm_instruction_08(0x23,unaff_r25,0x4bf);
    iVar5 = asm_instruction_06(0x23,in_r56,0);
    if (iVar5 < 0) {
      *(undefined1 *)(uVar2 - 0xa4) = uVar3;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd028ec(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_gp;
  undefined4 in_r37;
  undefined4 in_r43;
  bool in_C;
  
  cVar1 = ext_condition(0x12);
  if (cVar1 != '\0') {
    if (in_C) {
      func_0xbfd1f784();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x32,param_1,0x80);
  uVar2 = FUN_ram_bfd02a6c(*(undefined2 *)(unaff_gp + 4));
  asm_instruction_04(0x3d,in_r43,uVar2);
  asm_instruction_08(0x1f,in_r37,0xfffff870);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd02a6c(void)

{
  char cVar1;
  undefined2 in_r3;
  undefined4 in_r4;
  int in_r12;
  int unaff_r14;
  undefined4 unaff_r17;
  undefined4 in_ilink1;
  
  *(undefined2 *)(in_r12 + 2) = in_r3;
  asm_instruction_06(0x1d,in_r4,0x400);
  asm_instruction_08(0x22,unaff_r17,0);
  func_0xbfd01c00(unaff_r14 + -1);
  cVar1 = ext_condition(0x19);
  asm_instruction_05(0x3f,in_ilink1,0xfffff8c1);
  if (cVar1 != '\0') {
    FUN_ram_bfd0de7c();
  }
  FUN_ram_bfd02a68();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd02b04(undefined4 param_1,undefined1 *param_2)

{
  undefined1 unaff_r13;
  undefined4 unaff_r22;
  undefined4 in_r37;
  
  *param_2 = unaff_r13;
  asm_instruction_08(0x26,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd02b6c(undefined4 param_1,undefined4 param_2)

{
  int unaff_r13;
  undefined4 unaff_r14;
  undefined4 unaff_r17;
  
  *(short *)(unaff_r13 + 8) = (short)param_1;
  FUN_ram_bfd02b04(param_1,param_2,unaff_r14);
  asm_instruction_08(0x23,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_bfd02be0(void)

{
  undefined4 unaff_r13;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined1 in_Z;
  char in_N;
  char in_V;
  
  FUN_ram_bfd01d6c(unaff_gp + -0x20,unaff_r13);
  if ((bool)in_Z || in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfd02d74();
  FUN_ram_bfd01d78();
  if ((bool)in_Z || in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfd02d80();
  asm_instruction_08(0x30,unaff_r25,0x4bf);
  FUN_ram_bfd01d40();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd02d80(int param_1,uint param_2,uint param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint unaff_r13;
  int unaff_r14;
  uint unaff_r18;
  int in_ilink2;
  bool in_C;
  
  if (in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x12);
  if (cVar1 == '\0') {
    if (param_3 == unaff_r18) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r18 < param_3) {
    uVar2 = asm_instruction_06(0,param_1,param_3);
    uVar3 = asm_instruction_08(0x22,param_2 & ~unaff_r13,0x40);
    asm_instruction_06(2,uVar2,4);
    FUN_ram_bfd077e0(uVar2,uVar3);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r14 + in_ilink2 == 0) {
    *(short *)(param_1 + 10) = (short)param_3;
    if (param_3 == unaff_r18) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd03334(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 in_r12;
  int unaff_r14;
  undefined4 unaff_r21;
  undefined4 in_r52;
  
  *(short *)(param_1 + -0xa4) = (short)in_r12;
  *(short *)(param_1 + -0x148) = (short)in_r12;
  *(undefined4 *)(param_1 + -0x148) = in_r12;
  uVar2 = asm_instruction_05(0x2a,unaff_r21,in_r52);
  *(char *)(unaff_r14 + 5) = (char)uVar2;
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    func_0xbfd2bf58(param_1 + -0x1ec);
  }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd03350(void)

{
  char cVar1;
  undefined1 in_r7;
  int unaff_r14;
  
  *(undefined1 *)(unaff_r14 + 5) = in_r7;
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    func_0xbfd2bf58();
  }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd03768(void)

{
  undefined2 in_r12;
  int unaff_r13;
  undefined4 unaff_r14;
  undefined4 in_blink;
  undefined4 in_r45;
  
  *(undefined2 *)(unaff_r13 + 0x2a) = in_r12;
  asm_instruction_05(0xd,unaff_r14,0x21);
  *(undefined2 *)(unaff_r13 + 0x2a) = in_r12;
  asm_instruction_05(0xd,unaff_r14,0x21);
  *(undefined2 *)(unaff_r13 + 0x2a) = in_r12;
  asm_instruction_05(0xd,unaff_r14,0x21);
  *(undefined2 *)(unaff_r13 + 0x2a) = in_r12;
  asm_instruction_05(0xd,unaff_r14,0x21);
  *(undefined2 *)(unaff_r13 + 0x2a) = in_r12;
  asm_instruction_05(0xd,0xa1bc185c,0x1f);
  asm_instruction_08(0x15,in_r45,in_blink);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd037bc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd03a1c(void)

{
  int unaff_r14;
  
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd03a50(void)

{
  char cVar1;
  undefined4 in_blink;
  undefined4 in_r45;
  bool in_V;
  
  if (!in_V) {
    in_blink = 0xbfd03a54;
    func_0xbfc1df30();
  }
  cVar1 = ext_condition(0x14);
  if (cVar1 != '\0') {
    in_blink = 0xbfd03a58;
    func_0xbfce0ee4();
  }
  asm_instruction_08(0x35,in_r45,in_blink);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd03a9c(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 in_r4;
  undefined4 in_r5;
  undefined4 in_r10;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r17;
  int in_r48;
  undefined4 in_r50;
  undefined4 in_r52;
  char in_V;
  
  asm_instruction_06(0x10,in_r10,0x94);
  if (in_V != '\0') {
    asm_instruction_08(0,param_1,in_r4);
    asm_instruction_06(0x10,in_r50,0xfffffc2c);
    *(short *)(in_r12 + 4) = (short)unaff_r13;
    uVar1 = FUN_ram_bfd03a50(param_1,unaff_r13 + 2);
    asm_instruction_06(0x27,uVar1,4);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0x20,in_r5,in_r52);
  uVar1 = asm_instruction_08(0x22,unaff_r17,0);
  puVar2 = (undefined4 *)asm_instruction_06(0,param_1,0x1c2);
  if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_r12 <= in_r48) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *puVar2 = uVar1;
  if (unaff_r13 == 0) {
    asm_instruction_08(0x22,uVar1,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd03dc8(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd04510(int param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4,
                     undefined4 param_5,undefined4 param_6)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 unaff_r17;
  undefined4 in_r37;
  undefined4 *in_r52;
  
  uVar2 = *in_r52;
  asm_instruction_05(0x34,param_6,0xfffffa76);
  *(undefined2 *)(param_1 + 0x20) = param_4;
  cVar1 = ext_condition(0x19);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0xd,uVar2,unaff_r17);
  asm_instruction_05(0x31,in_r37,0xfffff8c3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd04560(undefined4 param_1)

{
  undefined2 unaff_r16;
  undefined2 *in_r48;
  
  *in_r48 = unaff_r16;
  asm_instruction_08(0x23,param_1,0);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd04614(undefined1 param_1)

{
  uint extraout_r1;
  uint uVar1;
  int in_r4;
  int in_r7;
  undefined4 in_r8;
  uint unaff_r13;
  int unaff_r14;
  uint unaff_r15;
  int unaff_gp;
  undefined4 uVar2;
  undefined4 in_r50;
  undefined4 in_mhi;
  undefined4 in_r61reserved;
  undefined1 in_V;
  uint extraout_r1_00;
  
  asm_instruction_06(0x10,in_r50,in_r61reserved);
  uVar2 = *(undefined4 *)(in_r4 + 0x50);
  *(undefined1 *)(unaff_r13 + 4) = param_1;
  asm_instruction_06(0,in_mhi,0x3f);
  FUN_ram_bfd04614(*(undefined2 *)(unaff_gp + 0x164));
  uVar1 = extraout_r1 & ~unaff_r13;
  if (!(bool)in_V) {
    func_0xbfdf42d0(unaff_r14 >> 7);
    uVar1 = extraout_r1_00;
  }
  do {
  } while ((unaff_r15 & 0x7ffff) == 0);
  if (!(bool)in_V) {
    func_0xbfdf42d8(unaff_r14 + -5,uVar1 & ~unaff_r13);
  }
  if ((unaff_r15 & 0x7ffff) != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0,in_r8,uVar2);
  *(ushort *)(in_r7 + -1) = (ushort)*(byte *)(unaff_gp + 0xe4);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd04940(undefined4 param_1,undefined4 param_2,undefined1 param_3)

{
  char cVar1;
  int in_r12;
  
  *(undefined1 *)(in_r12 + 10) = param_3;
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    func_0xbfcf5540();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd04974(void)

{
  bool in_N;
  
  if (!in_N) {
    func_0xbfc6d174();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd04ae0(uint param_1,int param_2,uint param_3,undefined4 param_4,int param_5,
                     undefined4 param_6,uint param_7,int param_8)

{
  char cVar1;
  undefined8 uVar2;
  undefined2 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 extraout_r1;
  uint uVar6;
  uint uVar7;
  undefined4 in_r8;
  undefined4 uVar8;
  int in_r12;
  int unaff_r13;
  uint uVar9;
  int unaff_r14;
  ushort uVar10;
  undefined4 unaff_r19;
  undefined4 unaff_r25;
  int iVar11;
  int unaff_gp;
  undefined4 in_r33;
  uint in_r36;
  undefined4 in_r37;
  undefined4 in_r42;
  undefined4 in_r48;
  undefined2 *puVar12;
  undefined4 uVar13;
  int in_r50;
  int in_r52;
  uint in_r54;
  int in_r56;
  undefined4 in_mlo;
  undefined4 in_lp_count;
  undefined1 uVar14;
  bool in_N;
  undefined1 in_C;
  undefined1 in_V;
  undefined8 uVar15;
  
  uVar8 = asm_instruction_06(0,in_r8,0);
  if (in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar11 = asm_instruction_08(0x31,unaff_r25,0x4bf);
  if ((bool)in_C || iVar11 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar10 = *(ushort *)(param_1 + 8);
  puVar12 = (undefined2 *)asm_instruction_06(0x31,in_r48,in_mlo);
  uVar14 = puVar12 == (undefined2 *)0x0;
  puVar3 = puVar12;
  do {
    *(char *)(unaff_r13 + 0x1b) = (char)param_2;
    iVar5 = asm_instruction_08(0x23,param_2,1);
    if ((bool)in_C || (bool)uVar14) {
      if (uVar10 != 0) {
        if ((int)puVar3 < 0) {
          func_0xbfc5ebcc(param_1);
        }
        do {
          if ((in_r54 & 0x80000) == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
            halt_baddata();
          }
        } while (unaff_r13 == 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      *(int *)(*(ushort *)(unaff_gp + 0x30) - 0xe4) = unaff_r14;
      iVar11 = asm_instruction_08(0x22,iVar11,0x4bf);
      if (!(bool)in_C && iVar11 != 0) {
        *(char *)(in_r12 + 0x17) = (char)iVar5;
        asm_instruction_06(2,in_r52,0xfffffe86);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (unaff_r14 != 0) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
        halt_unimplemented();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(short *)(iVar5 + 0x1e) = (short)unaff_r14;
    uVar13 = asm_instruction_06(0x11,puVar12,0x339);
    asm_instruction_08(2,param_1,0);
    param_2 = asm_instruction_08(0x23,iVar5,1);
    iVar5 = asm_instruction_06(0x31,uVar13,in_mlo);
    puVar3 = (undefined2 *)asm_instruction_06(0x20,in_r56,0x3e);
    uVar14 = puVar3 == (undefined2 *)0x0;
    uVar10 = (ushort)*(byte *)(param_2 + 0x13);
    uVar7 = (uint)*(byte *)((int)puVar3 + 0x11);
    puVar12 = (undefined2 *)(iVar5 + -0xef);
    *puVar12 = (short)in_mlo;
    in_r12 = param_3 + 2;
    param_1 = (uint)*(byte *)(unaff_gp + 0xa4);
  } while ((bool)in_C || (bool)uVar14);
  uVar9 = *(uint *)(param_3 + 0x10);
  uVar8 = asm_instruction_06(0,uVar8,0);
  uVar15 = CONCAT44(param_2,*(undefined4 *)(uVar7 + 0x40));
  if (!(bool)in_V) {
    uVar15 = func_0xbfdf47bc(*(undefined4 *)(uVar7 + 0x40));
  }
  if (unaff_r14 != 0) goto LAB_ram_bfd04b60;
  while (uVar13 = (undefined4)((ulonglong)uVar15 >> 0x20),
        param_3 = asm_instruction_06(0x3d,param_3,0x600), in_r36 < param_7) {
    puVar12 = (undefined2 *)asm_instruction_06(0x25,puVar12,0x439);
    in_r52 = asm_instruction_07(0x1d,in_r52,in_lp_count);
    uVar14 = in_r52 == 0;
    *(short *)(in_r12 + 6) = (short)param_3;
    if (!(bool)in_V) {
      func_0xbfdf47d8();
      uVar13 = extraout_r1;
    }
    in_r12 = unaff_r14 >> 5;
    uVar13 = asm_instruction_08(0x23,uVar13,1);
    in_r56 = *(int *)(param_5 + 0x5d);
    *(uint *)(uint)*(byte *)(uVar9 + 0xd) = (uint)*(byte *)(uVar9 + 0xd);
    uVar15 = CONCAT44(uVar13,(uint)*(byte *)(unaff_gp + 0xad));
LAB_ram_bfd04b60:
    if (unaff_r14 != 0) {
      asm_instruction_08(0x23,(int)((ulonglong)uVar15 >> 0x20),1);
      asm_instruction_08(0x22,iVar11,0xffffffff);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
LAB_ram_bfd04bcc:
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    uVar15 = func_0xbfd1e060((int)uVar15);
  }
LAB_ram_bfd04bd4:
  in_r33 = asm_instruction_08(0x25,in_r33,0);
  do {
    uVar2 = uVar15;
    if (!(bool)in_C && !(bool)uVar14) {
      param_3 = (uint)*(ushort *)((int)((ulonglong)uVar15 >> 0x20) + uVar7);
      asm_instruction_06(0,(int)uVar15,7);
LAB_ram_bfd04be0:
      *(char *)(uVar9 + 0x1a) = (char)param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    while (uVar6 = (uint)((ulonglong)uVar2 >> 0x20), uVar13 = (undefined4)uVar2, uVar9 != 0) {
      *(undefined2 *)((int)puVar12 + -0xaf) = (short)in_mlo;
      puVar12 = (undefined2 *)asm_instruction_06(0x31,(undefined2 *)((int)puVar12 + -0xaf),in_mlo);
      if (uVar9 == 0) goto LAB_ram_bfd04be0;
      uVar7 = (uint)*(byte *)(uVar6 + 0x11);
      if (uVar9 != 0) {
        uVar13 = *(undefined4 *)(unaff_gp + 0x110);
      }
      uVar15 = CONCAT44(uVar6,uVar13);
      if (!(bool)in_C && puVar12 != (undefined2 *)0x0) {
        uVar9 = *(uint *)(param_3 + 0x10);
        uVar8 = asm_instruction_06(0,uVar8,uVar13);
        in_r56 = asm_instruction_08(0x22,in_r56,0xfffff97f);
        uVar14 = in_r56 == 0;
        goto LAB_ram_bfd04bcc;
      }
      puVar12 = (undefined2 *)asm_instruction_06(0x11,puVar12,0x339);
      uVar14 = puVar12 == (undefined2 *)0x0;
      do {
        *(undefined1 *)(uVar9 + 0x1a) = *(undefined1 *)(uVar9 + 7);
      } while (param_3 != 0xfffffffe);
      uVar4 = (uint)*(ushort *)(unaff_gp + 0x96);
      if (param_5 == in_r50) {
        param_3 = (uint)*(ushort *)(uVar6 + uVar7);
        uVar13 = asm_instruction_06(0,uVar4,7);
        asm_instruction_08(0x22,uVar13,0x6c0);
        break;
      }
      uVar2 = CONCAT44(uVar6 & ~uVar9,uVar4);
      uVar15 = CONCAT44(uVar6 & ~uVar9,uVar4);
      if (param_8 == 0) goto LAB_ram_bfd04bd4;
    }
    iVar5 = *(int *)(unaff_r14 + 0x20);
    while( true ) {
      uVar15 = CONCAT44(uVar6,*(undefined4 *)(uVar7 + 0x40));
      cVar1 = ext_condition(0x14);
      if (cVar1 != '\0') {
        uVar15 = func_0xbfd1dffc();
      }
      uVar6 = (uint)((ulonglong)uVar15 >> 0x20);
      iVar11 = asm_instruction_08(0x25,iVar11,0x4bf);
      puVar12 = (undefined2 *)asm_instruction_06(0x25,puVar12,0x439);
      uVar14 = puVar12 == (undefined2 *)0x0;
      if ((bool)in_C || (bool)uVar14) break;
      iVar5 = asm_instruction_07(0x1d,iVar5,unaff_r19);
      cVar1 = ext_condition(0x10);
      if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      *(short *)(iVar5 + 6) = (short)param_3;
      iVar5 = unaff_r14 >> 1;
      puVar12 = *(undefined2 **)(param_5 + 0x5d);
      *(uint *)(*(byte *)(uVar9 + 9) + 0x174) = (uint)*(byte *)(uVar9 + 9);
      uVar15 = CONCAT44(uVar6,(uint)*(byte *)(unaff_gp + 0x87));
      if (unaff_r14 != 0) {
        iVar11 = unaff_r14 + -5;
        *(byte *)(uVar9 + 0x1a) = *(byte *)(unaff_gp + 0x87);
        cVar1 = ext_condition(0x11);
        if (cVar1 != '\0') {
          uVar15 = func_0xbfd1d830();
        }
        uVar8 = (undefined4)uVar15;
        asm_instruction_04(0x3d,in_r42,(int)((ulonglong)uVar15 >> 0x20));
        asm_instruction_08(0x1f,in_r37,0xfffffc70);
        *(undefined4 *)(iVar11 + 0x20) = uVar8;
        *(undefined4 *)uVar8 = uVar8;
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
    }
  } while( true );
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd0553e) overlaps instruction at (ram,0xbfd0553a)
    */

void FUN_ram_bfd0552a(void)

{
  char cVar1;
  uint extraout_r1;
  uint uVar2;
  int in_r3;
  uint unaff_r13;
  char unaff_r14;
  int unaff_r15;
  undefined1 in_Z;
  undefined1 in_V;
  uint extraout_r1_00;
  
  cVar1 = FUN_ram_bfd05970();
  if ((bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_r3 == 0) {
    cVar1 = unaff_r14 + -4;
    uVar2 = extraout_r1 & ~unaff_r13;
    if (!(bool)in_V) {
      cVar1 = func_0xbfdf51d8();
      uVar2 = extraout_r1_00;
    }
  }
  else {
    uVar2 = extraout_r1 & ~unaff_r13;
  }
  if (unaff_r15 != 0) {
    cVar1 = ext_condition(0x1d);
    if (cVar1 != '\0') {
      func_0xbfd4b190();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(char *)(uVar2 + 0x18) = cVar1;
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd056fa(void)

{
  int unaff_r14;
  
  do {
  } while (unaff_r14 == 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd0576c(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  int iVar5;
  int in_r7;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int *unaff_r16;
  int unaff_r17;
  int unaff_r20;
  undefined4 unaff_r21;
  int unaff_gp;
  undefined4 in_r36;
  undefined4 in_r37;
  undefined4 in_r49;
  int in_r54;
  undefined4 in_lp_count;
  undefined1 in_Z;
  undefined1 in_C;
  undefined8 uVar6;
  
  while( true ) {
    if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    FUN_ram_bfd0576c();
    if (!(bool)in_C && !(bool)in_Z) break;
    *unaff_r16 = unaff_r20;
    unaff_r16 = (int *)((int)unaff_r16 + 0x62);
    if (!(bool)in_Z) {
      func_0xbfd2e344(*(undefined2 *)(unaff_gp + 0xe8));
    }
    in_lp_count = asm_instruction_08(0x12,in_lp_count,in_r49);
    in_r36 = asm_instruction_08(0x13,in_r36,0xfffffaf1);
    uVar6 = FUN_ram_bfd058c8();
    unaff_r20 = unaff_r20 + 0x42;
    iVar5 = asm_instruction_05(0x2d,unaff_r13,unaff_r16);
    in_Z = iVar5 == 0;
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
      asm_instruction_04(0x11,unaff_r21,in_r54);
      uVar2 = asm_instruction_08(0x23,(int)uVar6,(int)uVar6);
      asm_instruction_05(0x3d,in_r37,0xfffff8c3);
      if (!(bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_06(0,uVar2,3);
      *(undefined2 *)(in_r12 + 6) = 0;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (unaff_r14 == 0) {
      while( true ) {
        if ((bool)in_C || (bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        cVar1 = ext_condition(0x1e);
        if (cVar1 != '\0') {
          uVar6 = func_0xbfd66a48();
        }
        cVar1 = ext_condition(0x1c);
        if (cVar1 != '\0') {
          uVar6 = func_0xbfc13140();
        }
        uVar2 = (undefined4)((ulonglong)uVar6 >> 0x20);
        if (!(bool)in_C && !(bool)in_Z) break;
        *(int *)(unaff_r13 + 0x18) = in_r12;
        if (in_r7 == 0) {
          do {
          } while (unaff_r17 != in_r54);
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        puVar3 = (undefined1 *)asm_instruction_08(0x22,(int)uVar6,uVar2);
        *puVar3 = (char)puVar3;
        uVar4 = asm_instruction_08(0x22,puVar3,puVar3);
        uVar6 = CONCAT44(uVar2,uVar4);
        iVar5 = *(int *)(in_r12 + 0x78);
      }
      *(char *)(iVar5 + 0x50) = (char)uVar6;
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd05822(undefined4 param_1)

{
  char cVar1;
  undefined4 in_r37;
  undefined4 in_r43;
  
  cVar1 = ext_condition(0x16);
  if (cVar1 != '\0') {
    param_1 = func_0xbfd1e428();
  }
  asm_instruction_04(0x3d,in_r43,param_1);
  asm_instruction_08(0x1f,in_r37,0x770);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd058b0(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                     undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r12;
  int unaff_r13;
  int unaff_r14;
  int iVar4;
  char cVar5;
  
  iVar3 = *(int *)(param_4 + 0x40);
  asm_instruction_06(0x3c,param_5,0xd);
  iVar4 = asm_instruction_07(0x1c,(uint)*(byte *)(unaff_r14 + 0xb),unaff_r13);
  cVar5 = iVar4 == 0;
  uVar2 = asm_instruction_06(2,(uint)*(byte *)(unaff_r14 + 0xb),0x644);
  *(undefined4 *)(unaff_r14 + 0x58) = in_r12;
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    func_0xbfd6e564(uVar2,param_2,param_3,*(undefined4 *)(iVar3 + 0x48));
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar5 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd058c8(void)

{
  char cVar1;
  int unaff_r13;
  char in_Z;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_Z != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd05970(void)

{
  int extraout_r1;
  
  FUN_ram_bfd04ae0();
  *(char *)(extraout_r1 + 0x12) = (char)extraout_r1;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd05d78(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  bool in_Z;
  
  asm_instruction_06(0,param_2,0);
  asm_instruction_06(0x20,param_2,1);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    if (!in_Z) {
      func_0xbfd3f9e4();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd05d9c(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int unaff_r13;
  
  uVar1 = asm_instruction_08(0x2c,(uint)*(ushort *)(param_4 + param_3),0x140);
  *(short *)(unaff_r13 + 6) = (short)param_3;
  FUN_ram_bfd05d78(uVar1);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd062b8(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int in_r12;
  undefined2 unaff_r13;
  int unaff_r14;
  undefined2 unaff_r15;
  undefined4 unaff_r19;
  undefined4 in_blink;
  undefined4 in_r45;
  undefined4 in_r53;
  undefined4 in_r55;
  bool in_Z;
  bool in_C;
  
  puVar1 = (undefined4 *)asm_instruction_06(0,param_1,0xfffffd83);
  if (!in_C && !in_Z) {
    *(undefined2 *)(param_4 + 8) = unaff_r15;
    uVar2 = asm_instruction_06(0,puVar1,0x742);
    asm_instruction_06(0,uVar2,0x6c3);
    asm_instruction_08(0x24,in_r45,in_blink);
    *(undefined2 *)(unaff_r14 + 0x20) = unaff_r13;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *puVar1 = unaff_r19;
  *(undefined2 *)(puVar1 + -0xab) = unaff_r15;
  asm_instruction_05(0x2d,in_r53,in_r55);
  *(short *)(in_r12 + 4) = (short)param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd064d0(undefined4 param_1,undefined1 param_2)

{
  undefined2 uVar1;
  int unaff_r14;
  int unaff_gp;
  bool in_V;
  
  uVar1 = *(undefined2 *)(unaff_gp + 8);
  *(undefined1 *)(unaff_r14 + 8) = param_2;
  if (!in_V) {
    func_0xbfdf60d0(uVar1);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd064e8(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r50;
  undefined4 in_mlo;
  
  asm_instruction_06(0,param_3,0);
  asm_instruction_08(0x31,unaff_r25,0x4bf);
  iVar2 = asm_instruction_06(0x11,in_r50,in_mlo);
  cVar1 = ext_condition(0x1e);
  if (cVar1 != '\0') {
    func_0xbfda34c4(*(undefined4 *)(unaff_gp + 0x2c4));
  }
  FUN_ram_bfd064fc(*(undefined2 *)(iVar2 + 0x24));
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd06544(void)

{
  char cVar1;
  undefined4 in_r8;
  undefined4 unaff_r16;
  bool in_N;
  
  cVar1 = ext_condition(0x16);
  if (in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (cVar1 == '\0') {
    asm_instruction_06(0,in_r8,unaff_r16);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0654c(void)

{
  undefined4 in_r8;
  undefined4 unaff_r16;
  
  asm_instruction_06(0,in_r8,unaff_r16);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfd065f0) */

void FUN_ram_bfd065c0(void)

{
  undefined4 uVar1;
  undefined4 extraout_r1;
  undefined2 in_r3;
  int in_r4;
  undefined4 in_r8;
  int in_r12;
  int unaff_r14;
  undefined4 unaff_r16;
  int unaff_gp;
  undefined4 in_mmid;
  undefined1 in_Z;
  undefined1 uVar2;
  undefined1 in_N;
  undefined8 uVar3;
  undefined4 extraout_r1_00;
  
  func_0xbfd06554();
  uVar2 = in_N;
  uVar1 = func_0xbfc731c0();
  if ((bool)in_N) {
    uVar1 = func_0xbfc731c0();
  }
  uVar1 = asm_instruction_06(0,uVar1,0x1c2);
  *(short *)(in_r12 + 4) = (short)in_r12;
  FUN_ram_bfd06544(uVar1);
  asm_instruction_06(0,in_r8,unaff_r16);
  FUN_ram_bfd058b0(*(undefined4 *)(in_r4 + 0x96));
  if ((bool)uVar2) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar2 = in_Z;
  func_0xbfd882d0();
  uVar1 = extraout_r1;
  if (!(bool)in_Z) {
    func_0xbfd882d0();
    uVar1 = extraout_r1_00;
  }
  uVar3 = CONCAT44(uVar1,unaff_gp + -0xbc);
  if (!(bool)uVar2) {
    uVar3 = func_0xbfd2f9e8(unaff_gp + -0xbc);
  }
  if (unaff_r14 == 0) {
    func_0xc0188218((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),0xfffffffc);
    func_0xc0188218();
    func_0xbf29f224();
    asm_instruction_06(0x20,in_mmid,0xffffffff);
    uRam0000002e = in_r3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd06898(int param_1,undefined1 param_2)

{
  char cVar1;
  undefined1 extraout_r1;
  undefined1 extraout_r1_00;
  int iVar2;
  int unaff_r14;
  undefined4 unaff_r16;
  undefined2 *puVar3;
  undefined4 unaff_r17;
  int unaff_r20;
  int unaff_gp;
  undefined4 in_r38;
  undefined4 in_r39;
  undefined4 in_r54;
  undefined1 in_C;
  
  while( true ) {
    asm_instruction_05(0x2d,in_r39,0x30);
    cVar1 = ext_condition(0x10);
    *(int *)(param_1 + 0x3c) = param_1;
    if (cVar1 != '\0') {
      param_1 = func_0xbfd89c9c();
      param_2 = extraout_r1;
    }
    iVar2 = asm_instruction_05(0xd,in_r54,0x3a);
    if (!(bool)in_C && iVar2 != 0) break;
    iVar2 = asm_instruction_05(0xd,in_r38,0x30);
    unaff_r17 = asm_instruction_08(0x30,unaff_r17,0x3c0);
    unaff_r20 = *(ushort *)(iVar2 + 0x90) + 0xd0;
    asm_instruction_05(0xd,in_r54,0x3a);
  }
  puVar3 = (undefined2 *)asm_instruction_06(0x10,unaff_r16,unaff_r20 + 0x90);
  *puVar3 = (short)(unaff_r20 + 0x90);
  cVar1 = ext_condition(0x10);
  *(uint *)(*(ushort *)(unaff_gp + 0x14) + 0x3c) = (uint)*(ushort *)(unaff_gp + 0x14);
  if (cVar1 != '\0') {
    func_0xbfd89cb8();
    param_2 = extraout_r1_00;
  }
  *(undefined1 *)(unaff_r14 + 8) = param_2;
  asm_instruction_05(0xd,unaff_r14,0x21);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd068c0(undefined4 param_1,undefined1 param_2)

{
  int unaff_r14;
  
  *(undefined1 *)(unaff_r14 + 8) = param_2;
  asm_instruction_05(0xd,unaff_r14,0x21);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd06b08(void)

{
  char cVar1;
  
  cVar1 = ext_condition(0x1c);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd06eee) overlaps instruction at (ram,0xbfd06eec)
    */

void FUN_ram_bfd06eec(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int in_r9;
  int in_r10;
  int in_r12;
  uint unaff_r13;
  undefined1 *unaff_r16;
  undefined1 *puVar4;
  undefined4 unaff_r17;
  undefined1 uVar5;
  undefined4 unaff_r20;
  undefined4 in_r24;
  undefined4 unaff_r25;
  int unaff_gp;
  int in_r33;
  int in_r34;
  int in_r48;
  undefined1 uVar6;
  undefined1 in_C;
  undefined1 in_V;
  undefined8 uVar7;
  undefined8 uVar8;
  
  uVar7 = CONCAT44(param_2,param_1);
  while( true ) {
    unaff_r20 = asm_instruction_05(0x1d,unaff_r20,0x472);
    unaff_r25 = asm_instruction_08(0x30,unaff_r25,0x4bf);
    in_r48 = asm_instruction_06(0x10,in_r48,0xfffffa00);
    uVar6 = in_r48 == 0;
    uVar3 = (uint)((ulonglong)uVar7 >> 0x20) & ~unaff_r13;
    uVar8 = CONCAT44(uVar3,(int)uVar7);
    if (!(bool)in_V) {
      uVar8 = FUN_ram_bfcf6b98((int)uVar7,uVar3);
    }
    uVar2 = asm_instruction_06(0,(int)uVar8,param_5);
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar2 = asm_instruction_06(0x20,uVar2,4);
    uVar5 = (undefined1)unaff_r20;
    if (!(bool)in_C && !(bool)uVar6) break;
    *unaff_r16 = uVar5;
    unaff_r16[0x62] = uVar5;
    *(short *)(unaff_r16 + 0xc4) = (short)unaff_r20;
    unaff_r16 = unaff_r16 + 0x126;
    uVar7 = CONCAT44((int)((ulonglong)uVar8 >> 0x20),(uint)*(ushort *)(unaff_gp + 0x4a));
    if (!(bool)uVar6) {
      uVar7 = func_0xbfd332e4();
    }
    *(char *)(in_r12 + 0x11) = (char)in_r12;
  }
  puVar4 = (undefined1 *)asm_instruction_08(0x2c,in_r24,param_4);
  asm_instruction_06(0x30,in_r48,0);
  cVar1 = ext_condition(0x10);
  asm_instruction_08(0x22,unaff_r17,0x3c0);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *puVar4 = uVar5;
  if (in_r34 <= in_r10) {
    *(short *)(puVar4 + 0x82) = (short)unaff_r20;
    if (in_r33 <= in_r9) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(char *)(unaff_r13 + 0x1b) = (char)uVar2 + '(';
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x22,unaff_r25,0x4bf);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd06f10(char param_1)

{
  char cVar1;
  int in_r9;
  int in_r10;
  int unaff_r13;
  undefined1 *unaff_r16;
  undefined4 unaff_r17;
  undefined2 unaff_r20;
  undefined4 unaff_r25;
  int in_r33;
  int in_r34;
  undefined4 in_r48;
  
  asm_instruction_06(0x30,in_r48,0);
  cVar1 = ext_condition(0x10);
  asm_instruction_08(0x22,unaff_r17,0x3c0);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *unaff_r16 = (char)unaff_r20;
  if (in_r34 <= in_r10) {
    *(undefined2 *)(unaff_r16 + 0x82) = unaff_r20;
    if (in_r33 <= in_r9) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(char *)(unaff_r13 + 0x1b) = param_1 + '(';
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x22,unaff_r25,0x4bf);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd072d0(void)

{
  ext_condition(0x1c);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd07338(void)

{
  undefined4 unaff_r17;
  undefined4 in_ilink1;
  int iVar1;
  
  iVar1 = asm_instruction_05(0x3f,in_ilink1,0xfffff8c1);
  func_0xbfd07320();
  if (iVar1 < 0) {
    asm_instruction_08(0x22,unaff_r17,0x200);
    FUN_ram_bfd064cc();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd07340(void)

{
  undefined4 unaff_r17;
  
  func_0xbfd07320();
  asm_instruction_08(0x22,unaff_r17,0x200);
  FUN_ram_bfd064cc();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd073e0(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int in_r12;
  int unaff_r14;
  undefined4 unaff_r22;
  undefined1 in_r32;
  undefined4 in_r37;
  bool in_Z;
  bool in_C;
  
  if (!in_C && !in_Z) {
    *(undefined1 *)(unaff_r14 + 0xf0) = in_r32;
    asm_instruction_08(0x17,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(in_r12 + 6) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd074b0(int param_1,int param_2)

{
  char cVar1;
  undefined4 unaff_r13;
  int unaff_r14;
  undefined4 unaff_r18;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r32;
  int iVar2;
  undefined4 in_r56;
  bool in_C;
  
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  iVar2 = asm_instruction_06(2,in_r56,0x14);
  param_2 = param_2 + -1;
  if (in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(2,unaff_r13,unaff_r18);
  if (iVar2 != 0) {
    do {
      asm_instruction_07(0x3d,param_1,0);
      in_r32 = asm_instruction_06(0,in_r32,0xfffff838);
      asm_instruction_07(0x1d,param_1,0x480);
      param_2 = param_2 + 2;
      param_1 = *(int *)(unaff_gp + 0x114);
      *(int *)(param_1 + 500) = param_1;
    } while (unaff_r14 == 0);
    cVar1 = ext_condition(0x19);
    if (cVar1 != '\0') {
      func_0xbfc9f8e0(param_1,param_2);
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0761c(undefined4 param_1,int param_2)

{
  char cVar1;
  int in_r12;
  undefined4 in_r56;
  
  *(undefined4 *)(*(byte *)(param_2 + 0x10) + 0xd1) = param_1;
  asm_instruction_06(0,in_r56,0x3e);
  FUN_ram_bfd06898(*(undefined1 *)(in_r12 + 10));
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd07890) overlaps instruction at (ram,0xbfd0788e)
    */
/* WARNING: Removing unreachable block (ram,0xbfd0786a) */
/* WARNING: Removing unreachable block (ram,0xbfd07882) */
/* WARNING: Removing unreachable block (ram,0xbfd07852) */
/* WARNING: Removing unreachable block (ram,0xbfd0789a) */
/* WARNING: Removing unreachable block (ram,0xbfd078a0) */
/* WARNING: Removing unreachable block (ram,0xbfd078a6) */
/* WARNING: Removing unreachable block (ram,0xbfd8ac90) */
/* WARNING: Removing unreachable block (ram,0xbfd078ae) */
/* WARNING: Removing unreachable block (ram,0xbfb64712) */

void FUN_ram_bfd077e0(undefined4 param_1)

{
  bool bVar1;
  undefined2 uVar2;
  undefined1 uVar3;
  int iVar4;
  int extraout_r1;
  int extraout_r1_00;
  undefined1 *puVar5;
  undefined4 in_r5;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  uint unaff_r15;
  undefined4 unaff_r16;
  int iVar6;
  undefined4 in_r24;
  undefined4 unaff_r25;
  undefined4 uVar7;
  int unaff_gp;
  undefined4 in_blink;
  undefined4 in_r32;
  uint in_r36;
  undefined4 in_r40;
  undefined4 in_r45;
  undefined4 in_r48;
  undefined4 in_r56;
  char cVar8;
  char in_V;
  
  iVar4 = asm_instruction_06(0x23,param_1,10);
  if (iVar4 == 0) {
    uVar7 = asm_instruction_08(0x23,unaff_r25,0x47f);
    asm_instruction_06(0x23,in_r24,0x18);
    uVar7 = asm_instruction_08(0x23,uVar7,0x47f);
    asm_instruction_06(0x23,in_r32,0x2f);
    uVar7 = asm_instruction_08(0x23,uVar7,0x47f);
    in_r5 = asm_instruction_06(0x23,in_r48,0x27);
    uVar7 = asm_instruction_08(0x23,uVar7,0x47f);
    asm_instruction_06(0x23,in_r32,0x2d);
    uVar7 = asm_instruction_08(0x23,uVar7,0x47f);
    asm_instruction_06(0x23,in_r56,0x27);
    uVar7 = asm_instruction_08(0x23,uVar7,0x47f);
    asm_instruction_06(0x23,in_r24,0x2f);
    uVar7 = asm_instruction_08(0x23,uVar7,0x47f);
    asm_instruction_06(0x23,in_r48,0x38);
    unaff_r25 = asm_instruction_08(0x23,uVar7,0x47f);
  }
  asm_instruction_06(0x23,unaff_r16,0x23);
  if (iVar4 == 0) {
    uVar7 = asm_instruction_08(0x23,unaff_r25,0x47f);
    asm_instruction_06(0x23,in_r24,0x32);
    iVar4 = asm_instruction_08(0x23,uVar7,0x47f);
    asm_instruction_06(0x23,in_r24,0x38);
    cVar8 = iVar4 < 0;
    FUN_ram_bfd079d0();
    if (cVar8 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0x23,in_r32,0x2e);
                    /* WARNING: Bad instruction - Truncating control flow here */
    func_0xbfd079dc();
    if (cVar8 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0x23,in_r48,2);
    FUN_ram_bfd079e8();
    if (cVar8 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0x23,in_r40,0x3c);
                    /* WARNING: Bad instruction - Truncating control flow here */
    func_0xbfd079f4();
    if (cVar8 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0x23,in_r48,0x22);
    FUN_ram_bfd07a00();
    if (cVar8 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0x23,in_r32,8);
    FUN_ram_bfd07a0c();
    bVar1 = in_V == '\0';
    func_0xbfd20fe0();
    if (bVar1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (0x13 < in_r36) {
      *(char *)(unaff_r13 + 8) = (char)in_r12;
      asm_instruction_08(0x23,iVar4,0x43f);
      iVar6 = asm_instruction_06(0x23,unaff_r16,1);
      uVar3 = (undefined1)*(undefined2 *)(unaff_gp + 0x14);
      iVar4 = extraout_r1;
      if (-1 < iVar6) {
        uVar3 = func_0xbfd20d68();
        iVar4 = extraout_r1_00;
      }
      if (unaff_r14 == 0) {
        *(undefined1 *)((unaff_r15 & 0x3ffff) + 5) = uVar3;
        asm_instruction_04(0x26,in_r5,unaff_gp);
        uVar2 = *(undefined2 *)(unaff_gp + 0xe);
        puVar5 = (undefined1 *)(iVar4 << 1);
        *(short *)(in_r12 + 4) = (short)in_r12;
        FUN_ram_bfd07928(uVar2,unaff_r13 * 0x10);
        uVar3 = (undefined1)in_r12;
        func_0xbfd68558();
        *puVar5 = uVar3;
        if (in_V == '\0') {
          FUN_ram_bfcf72c6();
          return;
        }
        func_0xbfd07ad4();
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  else {
    asm_instruction_08(0x15,in_r45,in_blink);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd07928(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  undefined1 uVar2;
  int extraout_r1;
  undefined1 *puVar3;
  undefined4 in_r5;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int unaff_r15;
  int unaff_gp;
  bool in_N;
  char in_V;
  
  uVar2 = (undefined1)*(undefined2 *)(unaff_gp + 0x14);
  if (!in_N) {
    uVar2 = func_0xbfd20d68();
    param_2 = extraout_r1;
  }
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined1 *)(unaff_r15 + 5) = uVar2;
  asm_instruction_04(0x26,in_r5,unaff_gp);
  uVar1 = *(undefined2 *)(unaff_gp + 0xe);
  puVar3 = (undefined1 *)(param_2 << 1);
  *(short *)(in_r12 + 4) = (short)in_r12;
  FUN_ram_bfd07928(uVar1,unaff_r13 * 0x10);
  uVar2 = (undefined1)in_r12;
  func_0xbfd68558();
  *puVar3 = uVar2;
  if (in_V != '\0') {
    func_0xbfd07ad4();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfcf72c6();
  return;
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd079d0(void)

{
  char cVar1;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd079e8(void)

{
  bool in_N;
  
  if (!in_N) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd07a00(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd07a0c(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd07a84(undefined4 param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  int unaff_r15;
  undefined4 in_blink;
  undefined4 in_r45;
  bool in_C;
  
  if (!in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r15 != 0) {
    iVar1 = asm_instruction_06(0,param_1,0x203);
    asm_instruction_08(0x35,in_r45,in_blink);
    *(undefined1 *)(iVar1 + 0xd) = param_3;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd07aec(void)

{
  undefined4 extraout_r1;
  undefined4 uVar1;
  
  func_0xbfd2278c();
  func_0xc03209f0();
  uVar1 = asm_instruction_06(0x20,extraout_r1,0x400);
  asm_instruction_06(0,uVar1,0x180);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd07c3c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  int in_r12;
  undefined4 uVar2;
  bool in_Z;
  bool in_C;
  
  uVar2 = asm_instruction_06(0x20,param_1,0x16);
  asm_instruction_06(0x20,param_1,0x16);
  *(short *)(in_r12 + 4) = (short)param_4;
  if (in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x24,param_2,0x40);
  if (!in_C && !in_Z) {
    *(char *)(param_4 + 0x1b) = (char)uVar2;
    asm_instruction_06(4,param_1,0xfffffb40);
    cVar1 = ext_condition(0x10);
    if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd07c7c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 in_r7;
  int unaff_gp;
  bool in_Z;
  
  uVar2 = asm_instruction_08(0x24,param_2,0x80);
  uVar1 = asm_instruction_06(4,(uint)*(ushort *)(unaff_gp + 0xe),0xfffffb44);
  uVar2 = asm_instruction_08(0x24,uVar2,0x100);
  uVar1 = asm_instruction_06(4,uVar1,0xfffffb48);
  *(undefined1 *)(param_4 + 0x1b) = in_r7;
  if (!in_Z) {
    func_0xbfc68894(uVar1,uVar2);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd07cb4(void)

{
  undefined2 in_r3;
  int in_r12;
  bool in_C;
  
  *(undefined2 *)(in_r12 + 4) = in_r3;
  if (!in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd07d18(void)

{
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd080d8(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int unaff_r14;
  undefined4 unaff_r18;
  undefined4 uVar4;
  int unaff_gp;
  undefined4 in_r34;
  undefined4 in_r42;
  undefined4 in_r56;
  undefined4 in_mmid;
  
  asm_instruction_08(0x14,in_r34,0x3b0);
  uVar3 = asm_instruction_08(0x23,param_2,0x400);
  asm_instruction_08(0x23,in_r56,0x57f);
  func_0xbfd073a4(param_1,uVar3);
  uVar3 = asm_instruction_08(0x1c,in_mmid,0x433);
  asm_instruction_08(0x20,uVar3,0xfffffa1f);
  cVar1 = ext_condition(0x15);
  if (cVar1 != '\0') {
    func_0xbfd21518();
  }
  uVar3 = FUN_ram_bfd07338(*(undefined2 *)(unaff_gp + 0x6a));
  uVar4 = asm_instruction_08(0x20,unaff_r18,0x139);
  uVar3 = asm_instruction_08(0x24,uVar3,0);
  uVar2 = FUN_ram_bfd07340(uVar3);
  asm_instruction_08(0x1c,uVar4,0x79);
  *(undefined1 *)(unaff_r14 + 0x1d) = uVar2;
  FUN_ram_bfd072cc();
  asm_instruction_08(0x20,in_r42,0xfffff8c1);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd082b8(undefined4 param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  uint extraout_r1;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint extraout_r1_02;
  undefined4 in_r8;
  uint unaff_r13;
  uint unaff_r15;
  undefined4 unaff_r16;
  int unaff_gp;
  undefined4 in_r48;
  int iVar2;
  int in_r50;
  undefined4 in_mlo;
  undefined4 in_mmid;
  int iVar3;
  undefined1 uVar4;
  undefined1 in_C;
  undefined1 in_V;
  undefined8 uVar5;
  
  iVar2 = asm_instruction_06(0x12,in_r48,0x339);
  uVar4 = iVar2 == 0;
  param_2 = param_2 & ~unaff_r13;
  if (!(bool)in_V) {
    func_0xbfdf7f5c();
    param_2 = extraout_r1;
  }
  if ((unaff_r15 & 0x7ffff) == 0) goto LAB_ram_bfd082f4;
  *(short *)(in_r50 + -0x8e) = (short)in_mlo;
  if (!(bool)uVar4) {
    func_0xbfddd4c8();
    param_2 = extraout_r1_00;
  }
  do {
  } while (unaff_r13 == 0);
  uVar1 = *(uint *)(unaff_gp + 0x110);
  in_r8 = asm_instruction_06(0,in_r8,uVar1);
  if ((bool)in_C || (bool)uVar4) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  do {
    uVar5 = CONCAT44(param_2,uVar1);
    unaff_r13 = *(uint *)(param_3 + 0x10);
    iVar2 = asm_instruction_06(0x32,iVar2,in_mlo);
    *(char *)(unaff_r13 + 0xc) = (char)uVar1;
    uVar1 = (uint)*(ushort *)(param_2 + param_4);
    if (!(bool)in_V) {
      uVar5 = FUN_ram_bfcf7f70();
    }
    param_2 = (uint)((ulonglong)uVar5 >> 0x20);
    asm_instruction_06(0,(int)uVar5,7);
    param_3 = asm_instruction_06(0,uVar1,(uint)*(byte *)(unaff_r13 + 8));
LAB_ram_bfd082f4:
    if (!(bool)in_C) {
      func_0xbfca0f84();
      param_2 = extraout_r1_01;
    }
    iVar3 = asm_instruction_06(0x20,in_mmid,0x3f);
    uVar4 = iVar3 == 0;
    if (!(bool)uVar4) {
      func_0xbfddd4fc();
      param_2 = extraout_r1_02;
    }
    uVar1 = (uint)*(byte *)(unaff_gp + 0xc4);
    in_r8 = asm_instruction_06(0,in_r8,unaff_r16);
  } while ((bool)in_C || (bool)uVar4);
  asm_instruction_06(0x32,iVar2,in_mlo);
  *(char *)(unaff_r13 + 0x10) = (char)param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd08318(void)

{
  char cVar1;
  char cVar2;
  int in_r4;
  undefined4 in_r8;
  int in_r12;
  int unaff_r14;
  undefined4 unaff_r16;
  undefined4 in_r50;
  int iVar3;
  undefined1 uVar4;
  undefined1 in_V;
  undefined8 uVar5;
  
  iVar3 = asm_instruction_06(0x12,in_r50,0x339);
  uVar4 = iVar3 == 0;
  cVar1 = ext_condition(0x11);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x11);
  cVar2 = ext_condition(0x15);
  if (cVar2 == '\0') {
    if (cVar1 != '\0') {
      func_0xbfd357bc(*(undefined2 *)(in_r12 + 0x2a),*(undefined4 *)(in_r4 + 0x54));
    }
    uVar5 = FUN_ram_bfd082b8();
    if (!(bool)in_V) {
      func_0xbfdf7f34((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),unaff_r14 + -4);
    }
    cVar1 = ext_condition(0x19);
    if (cVar1 != '\0') {
      func_0xbfc62fcc();
    }
    asm_instruction_06(0,in_r8,unaff_r16);
    if (!(bool)uVar4) {
      func_0xbfddd544();
    }
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
      func_0xbfc63040();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0866c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4,
                     undefined4 param_5,undefined4 param_6)

{
  char cVar1;
  undefined4 uVar2;
  int in_r12;
  int unaff_r13;
  undefined4 unaff_r17;
  undefined4 in_r52;
  bool in_V;
  undefined8 uVar3;
  
  uVar3 = CONCAT44(param_2,param_1);
  uVar2 = *(undefined4 *)(unaff_r13 + 0x30);
  *(undefined2 *)(in_r12 + 0x2a) = param_4;
  if (!in_V) {
    uVar3 = func_0xbfdf8270(param_1,param_2,uVar2);
  }
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    uVar3 = func_0xbfd31278();
  }
  asm_instruction_05(0x24,param_6,in_r52);
  asm_instruction_08(0x23,unaff_r17,0x200);
  FUN_ram_bfd07794((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),*(undefined4 *)(unaff_r13 + 0x68));
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd088f0(void)

{
  int unaff_r13;
  
  *(char *)(unaff_r13 + 0x1c) = (char)unaff_r13;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd08936) overlaps instruction at (ram,0xbfd08932)
    */

void FUN_ram_bfd08904(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_r13;
  int unaff_r14;
  undefined1 in_Z;
  undefined1 in_C;
  char in_V;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    param_1 = func_0xbfdacd04();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((bool)in_C || (bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(char *)(unaff_r13 + 0x1c) = (char)unaff_r13;
  uVar2 = asm_instruction_06(0x20,param_1,0x584);
  uVar2 = FUN_ram_bfd07a84(uVar2);
  uVar2 = asm_instruction_08(0x22,uVar2,0x6c1);
  func_0xbedf8740(uVar2);
  if ((unaff_r14 != 0) && (in_V == '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((unaff_r14 != 0) && (in_V == '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((unaff_r14 != 0) && (cVar1 = ext_condition(0x10), cVar1 != '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(char *)(unaff_r13 + 0x1c) = (char)unaff_r13;
  asm_instruction_05(0x2f,0x857440a2,0x731);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd08936) overlaps instruction at (ram,0xbfd08932)
    */

void FUN_ram_bfd08914(void)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_r13;
  int unaff_r14;
  char in_V;
  
  uVar2 = FUN_ram_bfd07a84();
  uVar2 = asm_instruction_08(0x22,uVar2,0x6c1);
  func_0xbedf8740(uVar2);
  if ((unaff_r14 != 0) && (in_V == '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((unaff_r14 != 0) && (in_V == '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((unaff_r14 != 0) && (cVar1 = ext_condition(0x10), cVar1 != '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(char *)(unaff_r13 + 0x1c) = (char)unaff_r13;
  asm_instruction_05(0x2f,0x857440a2,0x731);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd08974(undefined4 param_1,undefined1 param_2)

{
  undefined4 uVar1;
  undefined1 extraout_r1;
  undefined1 extraout_r1_00;
  undefined1 *unaff_r13;
  int unaff_r14;
  char in_V;
  
  if (in_V != '\0') {
    if (unaff_r14 != 0) {
      param_1 = FUN_ram_bfd07aec();
      param_2 = extraout_r1;
    }
    unaff_r13[8] = param_2;
    unaff_r13[0x1c] = (char)unaff_r13;
    if (!(bool)in_V) {
      param_1 = FUN_ram_bfcf8610();
    }
    uVar1 = asm_instruction_06(0x20,param_1,4);
    func_0xbfd07afc(uVar1);
    *unaff_r13 = extraout_r1_00;
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd089a0(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  undefined4 unaff_r13;
  undefined4 in_r50;
  
  asm_instruction_06(0x12,in_r50,0x39);
  iVar2 = asm_instruction_06(0x20,param_3,4);
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    iVar2 = FUN_ram_bfd01e40(iVar2,*(undefined2 *)(param_3 + 8));
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    *(undefined4 *)(iVar2 + 0x10) = unaff_r13;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd08a56) overlaps instruction at (ram,0xbfd08a54)
    */

void FUN_ram_bfd08a3c(void)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r18;
  undefined4 uVar4;
  int unaff_gp;
  undefined4 in_r34;
  undefined4 in_r42;
  undefined4 in_r56;
  undefined4 in_mmid;
  undefined8 uVar5;
  
  uVar3 = FUN_ram_bfd07c7c();
  uVar4 = asm_instruction_08(0x20,unaff_r18,0x79);
  uVar3 = asm_instruction_08(0x24,uVar3,uVar3);
  if (unaff_r13 != 0) {
    FUN_ram_bfd089b8(uVar3);
  }
  uVar5 = FUN_ram_bfd08c08();
  asm_instruction_08(0x14,in_r34,0x3b0);
  uVar3 = asm_instruction_08(0x23,(int)((ulonglong)uVar5 >> 0x20),0x400);
  asm_instruction_08(0x23,in_r56,0x67f);
  FUN_ram_bfd07d18((int)uVar5,uVar3);
  uVar3 = asm_instruction_08(0x1c,in_mmid,0x433);
  asm_instruction_08(0x20,uVar3,0xfffffa1f);
  cVar1 = ext_condition(0x14);
  if (cVar1 != '\0') {
    func_0xbfd21e88();
  }
  uVar3 = func_0xbfd07ca8(*(undefined2 *)(unaff_gp + 0x68));
  uVar4 = asm_instruction_08(0x20,uVar4,0x139);
  uVar3 = asm_instruction_08(0x24,uVar3,uVar3);
  uVar2 = FUN_ram_bfd07cb4(uVar3);
  asm_instruction_08(0x1c,uVar4,0x79);
  *(undefined1 *)(unaff_r14 + 0x1c) = uVar2;
  FUN_ram_bfd07c3c();
  asm_instruction_08(0x20,in_r42,0xfffff8c1);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd08bf0) overlaps instruction at (ram,0xbfd08bee)
    */

void FUN_ram_bfd08bbc(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                     undefined4 param_5,undefined4 param_6,uint param_7)

{
  char cVar1;
  undefined4 extraout_r1;
  uint uVar2;
  undefined4 in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r19;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 uVar3;
  uint in_r36;
  undefined4 in_r37;
  undefined4 uVar4;
  undefined4 in_r45;
  undefined4 in_r48;
  int iVar5;
  undefined1 in_C;
  char in_V;
  uint extraout_r1_00;
  
  while( true ) {
    if (param_7 <= in_r36) {
      asm_instruction_05(0x32,param_6,0x5b7);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar5 = asm_instruction_06(0x25,in_r48,0x439);
    if (!(bool)in_C && iVar5 != 0) {
      asm_instruction_07(0x1d,in_r12,unaff_r19);
      *(char *)(unaff_r13 + 0x1a) = (char)param_1;
      if (in_V == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      uVar3 = 0xbfd08bd6;
      func_0xbfd217d0();
      ext_condition(0x14);
      uVar4 = asm_instruction_08(0x1f,in_r37,0x670);
      asm_instruction_08(0x3f,uVar4,0xfffffc7f);
      uVar2 = (uint)*(ushort *)(unaff_r14 + 0xc);
      if (!(bool)in_V) {
        uVar3 = 0xbfd08bea;
        func_0xbfdf88e8(*(undefined1 *)(unaff_gp + -0x19));
        uVar2 = extraout_r1_00;
      }
      *(short *)(uVar2 + 0x10) = (short)uVar2;
      if (in_V != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_08(0x15,in_r45,uVar3);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar5 = asm_instruction_06(0x14,iVar5,0x43d);
    if ((bool)in_C || iVar5 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    param_2 = asm_instruction_08(0x25,param_2,0);
    unaff_r25 = asm_instruction_08(0x24,unaff_r25,0x4bf);
    *(undefined1 *)(unaff_r13 + 0x1a) = *(undefined1 *)(unaff_r13 + 7);
    do {
      cVar1 = ext_condition(0x14);
      if (cVar1 != '\0') {
        func_0xbfca0fa8();
        param_2 = extraout_r1;
      }
    } while (unaff_r13 == 0);
    in_r48 = asm_instruction_06(4,iVar5,0x43d);
    param_1 = *(undefined4 *)(param_4 + 0x40);
    if (unaff_r14 != 0) break;
    *(char *)(unaff_r13 + 0x15) = (char)param_4;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd08c08(undefined4 param_1)

{
  uint uVar1;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int unaff_gp;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 in_r37;
  undefined4 in_r45;
  char in_V;
  uint extraout_r1;
  
  if (unaff_r14 == 0) {
    asm_instruction_08(0x22,param_1,0xfffff941);
    *(uint *)(uint)*(ushort *)(in_r12 + 0x12) = (uint)*(ushort *)(in_r12 + 0x12);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(char *)(unaff_r13 + 0x1a) = (char)param_1;
  uVar2 = 0xbfd08bd6;
  func_0xbfd217d0();
  ext_condition(0x14);
  uVar3 = asm_instruction_08(0x1f,in_r37,0x670);
  asm_instruction_08(0x3f,uVar3,0xfffffc7f);
  uVar1 = (uint)*(ushort *)(unaff_r14 + 0xc);
  if (!(bool)in_V) {
    uVar2 = 0xbfd08bea;
    func_0xbfdf88e8(*(undefined1 *)(unaff_gp + -0x19));
    uVar1 = extraout_r1;
  }
  *(short *)(uVar1 + 0x10) = (short)uVar1;
  if (in_V != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x15,in_r45,uVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd08c60(void)

{
  undefined4 in_r5;
  
  asm_instruction_05(0x34,in_r5,0x377);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd08fa8(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd08fe0) overlaps instruction at (ram,0xbfd08fde)
    */

void FUN_ram_bfd08fd0(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  undefined4 in_r8;
  int in_r12;
  int iVar2;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  int unaff_r25;
  int unaff_gp;
  undefined4 in_ilink2;
  undefined4 in_r37;
  int in_r38;
  undefined4 in_r43;
  int iVar3;
  undefined2 *puVar4;
  undefined4 in_r55;
  undefined4 uVar5;
  undefined4 in_mlo;
  undefined4 in_mmid;
  undefined1 uVar6;
  undefined1 in_C;
  char in_V;
  
  uVar5 = asm_instruction_06(0x1d,in_r55,0x7a);
  do {
    in_r37 = asm_instruction_08(0x3f,in_r37,0x57f);
    iVar3 = asm_instruction_04(0x3d,in_r43,param_1);
    uVar6 = iVar3 == 0;
    if (!(bool)in_C) {
      func_0xbfd26de0();
    }
    if (in_r38 != 6) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    while( true ) {
      puVar4 = (undefined2 *)(iVar3 + -0x4f);
      *puVar4 = (short)in_mlo;
      if (!(bool)uVar6) {
        func_0xbfdde22c();
      }
      param_3 = asm_instruction_06(0,param_3,0x40);
      in_r8 = asm_instruction_06(0,in_r8,(uint)*(byte *)(unaff_gp + 0x84));
      if ((bool)in_C || (bool)uVar6) break;
      iVar2 = *(int *)(param_3 + 0x10);
      iVar3 = asm_instruction_06(0x31,puVar4,in_mlo);
      *(ushort *)(in_r12 + 4) = (ushort)*(byte *)(unaff_gp + 0x84);
      if (iVar3 != 0) {
        func_0xbfdde208();
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      in_r8 = asm_instruction_06(0,in_r8,unaff_r16);
      if (!(bool)in_C && iVar3 != 0) {
        asm_instruction_06(0x31,0,in_mlo);
        func_0xbedf8e5c(*(undefined1 *)(iVar2 + 7));
        cVar1 = ext_condition(0x11);
        if (cVar1 != '\0') {
          func_0xbfca1cb0();
        }
        asm_instruction_06(0,in_mmid,0x3f);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      unaff_r25 = asm_instruction_08(0x31,unaff_r25,0x4bf);
      uVar6 = unaff_r25 == 0;
      func_0xc0b266a4();
    }
    asm_instruction_05(0x2d,in_ilink2,unaff_r17);
    param_1 = FUN_ram_bfd08fa8();
    uVar5 = asm_instruction_06(0x1d,uVar5,0x7a);
    if (in_V == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  } while( true );
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09068(undefined4 param_1)

{
  undefined4 in_r8;
  undefined4 uVar1;
  uint unaff_r20;
  int unaff_gp;
  undefined1 in_Z;
  
  uVar1 = asm_instruction_06(0,in_r8,param_1);
  if (!(bool)in_Z) {
    func_0xbfdde26c();
  }
  do {
    if (!(bool)in_Z) {
      func_0xbfdde274(*(undefined4 *)(unaff_gp + 0x110));
    }
    uVar1 = asm_instruction_06(0,uVar1,(uint)*(byte *)(unaff_gp + 0x84));
  } while ((unaff_r20 & 0x100000) != 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09072(void)

{
  undefined4 in_r8;
  uint unaff_r20;
  int unaff_gp;
  undefined1 in_Z;
  
  do {
    if (!(bool)in_Z) {
      func_0xbfdde274(*(undefined4 *)(unaff_gp + 0x110));
    }
    in_r8 = asm_instruction_06(0,in_r8,(uint)*(byte *)(unaff_gp + 0x84));
  } while ((unaff_r20 & 0x100000) != 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Possible PIC construction at 0xbfd090c6: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0xbfd090c8) */

void FUN_ram_bfd090b8(void)

{
  undefined4 in_r12;
  int unaff_r14;
  undefined2 unaff_r15;
  int unaff_gp;
  
  *(undefined2 *)(unaff_r14 + 0x20) = unaff_r15;
  FUN_ram_bfd09068(in_r12);
  do {
    func_0xbfd6dd10(*(undefined2 *)(unaff_gp + 8));
  } while( true );
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd090e6(void)

{
  char cVar1;
  undefined4 *puVar2;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r23;
  undefined4 unaff_r25;
  undefined4 uVar3;
  undefined4 in_r50;
  char in_N;
  char in_V;
  
  puVar2 = (undefined4 *)FUN_ram_bfd090c4();
  cVar1 = ext_condition(0x1c);
  if (unaff_r13 != 0) {
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *puVar2 = unaff_r23;
    puVar2 = puVar2 + -0x29;
  }
  if (unaff_r14 != 0) {
    if (in_V == in_N) {
      func_0xbfce5598();
    }
    cVar1 = ext_condition(0x13);
    if (cVar1 != '\0') {
      func_0xbfd8c5a0();
    }
    do {
    } while (in_r12 != 0);
    uVar3 = asm_instruction_08(0x34,unaff_r25,0x4bf);
    asm_instruction_06(0x14,in_r50,0xfffffc09);
    asm_instruction_08(0x30,uVar3,0x4bf);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x12);
  if (cVar1 != '\0') {
    func_0xbfd09de0(puVar2);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09184(void)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined2 in_r9;
  int unaff_r13;
  undefined1 unaff_r15;
  int unaff_gp;
  undefined4 in_r48;
  undefined2 *in_r50;
  
  asm_instruction_06(2,in_r48,8);
  uVar2 = *(undefined2 *)(unaff_gp + 0x1c);
  *in_r50 = in_r9;
  FUN_ram_bfd08318(uVar2);
  uVar3 = FUN_ram_bfd09184();
  asm_instruction_08(0x23,uVar3,0x200);
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    *(undefined1 *)(unaff_r13 + 0x19) = unaff_r15;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09364(void)

{
  int unaff_r13;
  
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd09650) overlaps instruction at (ram,0xbfd0964e)
    */

void FUN_ram_bfd093bc(void)

{
  char cVar1;
  short sVar2;
  ushort uVar3;
  undefined4 in_r5;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r25;
  undefined4 uVar4;
  int unaff_gp;
  undefined4 in_r53;
  undefined4 in_r56;
  undefined4 uVar5;
  int iVar6;
  undefined4 in_mmid;
  undefined1 in_Z;
  bool in_C;
  
  if (in_C) {
    func_0xbfd271c0();
  }
  func_0xc018ca64();
  func_0xbfd084cc();
  if (!(bool)in_Z) {
    asm_instruction_08(0x22,in_r53,in_mmid);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x18);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x23,in_r5,0x30);
  sVar2 = *(short *)(unaff_r13 + 0x2a);
  uVar4 = asm_instruction_08(0x25,unaff_r25,0x4bf);
  uVar3 = *(ushort *)(unaff_gp + 0x56);
  uVar5 = asm_instruction_06(0x25,in_r56,0xfffff80e);
  if (sVar2 != 0) {
    uVar4 = asm_instruction_08(0x25,uVar4,0x4bf);
    uVar3 = *(ushort *)(unaff_gp + 0x4a);
  }
  uVar5 = asm_instruction_06(0x25,uVar5,0xfffffb0e);
  if (sVar2 != 0) {
    uVar4 = asm_instruction_08(0x25,uVar4,0x4bf);
    uVar3 = *(ushort *)(unaff_gp + 0x3e);
  }
  uVar5 = asm_instruction_06(0x25,uVar5,0xfffffc0e);
  if (sVar2 != 0) {
    uVar4 = asm_instruction_08(0x25,uVar4,0x4bf);
    uVar3 = *(ushort *)(unaff_gp + 0x32);
  }
  uVar5 = asm_instruction_06(0x25,uVar5,0xfffffd0e);
  if (sVar2 != 0) {
    uVar4 = asm_instruction_08(0x25,uVar4,0x4bf);
    uVar3 = *(ushort *)(unaff_gp + 0x26);
  }
  uVar5 = asm_instruction_06(0x25,uVar5,0xfffffe0e);
  if (sVar2 != 0) {
    uVar4 = asm_instruction_08(0x25,uVar4,0x4bf);
    uVar3 = *(ushort *)(unaff_gp + 0x1a);
  }
  uVar5 = asm_instruction_06(0x25,uVar5,0xffffff0e);
  if (sVar2 != 0) {
    uVar4 = asm_instruction_08(0x25,uVar4,0x4bf);
    uVar3 = *(ushort *)(unaff_gp + 0xe);
  }
  iVar6 = asm_instruction_06(0x25,uVar5,0xfffff90e);
  if (sVar2 == 0) {
    if (iVar6 == 0) {
      *(undefined2 *)(uVar3 + 6) = *(undefined2 *)(unaff_r14 + 10);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  else {
    asm_instruction_08(0x25,uVar4,0x4bf);
    asm_instruction_06(0x25,iVar6,0xfffffa0e);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09594(void)

{
  int iVar1;
  undefined2 in_r12;
  undefined4 in_r37;
  undefined4 in_r56;
  
  asm_instruction_08(0x1f,in_r37,0x670);
  iVar1 = func_0xbfddd1dc();
  asm_instruction_06(0x23,in_r56,0x2c);
  *(undefined2 *)(iVar1 + 6) = in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd097e4(int param_1,undefined4 param_2)

{
  undefined4 in_r5;
  undefined4 in_lp_count;
  bool in_Z;
  char in_N;
  char in_V;
  
  if (!in_Z && in_V == in_N) {
    *(undefined4 *)(param_1 + 0x62) = in_r5;
    FUN_ram_bfd08974();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x23,param_2,0x200);
  asm_instruction_08(0x1c,in_lp_count,0x21);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09820(undefined4 param_1,undefined4 param_2,undefined1 param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int unaff_r14;
  undefined4 unaff_r17;
  char in_V;
  
  iVar3 = FUN_ram_bfd097e4();
  *(char *)(param_4 + 0x15) = (char)unaff_r14;
  if (unaff_r14 == 0) {
    if (in_V != '\0') {
      uVar2 = asm_instruction_06(0x10,iVar3,0x198);
      asm_instruction_08(0x22,unaff_r17,0x200);
      func_0xbfd089d4(uVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined1 *)(iVar3 + 0xd) = param_3;
  if (unaff_r14 != 0) {
    asm_instruction_08(0x22,unaff_r17,0x200);
    FUN_ram_bfd08a3c();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1c);
  if (cVar1 == '\0') {
    FUN_ram_bfd099d4();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd099d4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 in_r37;
  char in_Z;
  
  asm_instruction_05(0x2d,in_r37,param_4);
  if (in_Z != '\0') {
    *(int *)(param_1 + 0x20) = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09b3c(undefined2 *param_1)

{
  int in_r12;
  undefined2 unaff_r13;
  int unaff_r14;
  
  if (unaff_r14 != 0) {
    *(short *)(in_r12 + 6) = (short)in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *param_1 = unaff_r13;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09c18(void)

{
  bool in_C;
  
  if (in_C) {
    func_0xbfd2727c();
  }
  func_0xc0b26220();
  func_0xc0b26220();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09c6c(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09d14(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6)

{
  int unaff_r13;
  undefined4 unaff_r25;
  int unaff_gp;
  
  asm_instruction_08(0x22,param_6,0x30);
  do {
  } while (*(short *)(unaff_r13 + 0x1e) == 0);
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  *(undefined2 *)(*(ushort *)(unaff_gp + 0x94) + 4) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09e08(uint param_1)

{
  char cVar1;
  int iVar2;
  int unaff_r13;
  int unaff_r14;
  int unaff_gp;
  undefined4 in_r33;
  
  iVar2 = param_1 << 6;
  if (unaff_r14 != 0) {
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
      func_0xbfd32aa8((uint)*(ushort *)(unaff_gp + 0x24),(int)*(short *)(unaff_r14 + 0xe),
                      (uint)*(ushort *)(unaff_gp + 0x24) << 6);
    }
    asm_instruction_05(0x2d,unaff_r13,in_r33);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
    do {
    } while (unaff_r13 == 0);
    param_1 = (uint)*(ushort *)(unaff_gp + 0x6a);
  }
  func_0xbfd09fb8(param_1,(int)*(short *)(unaff_r14 + 0xe),iVar2,
                  *(short *)(unaff_r14 + 0x22) + -0xb0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd09f08) overlaps instruction at (ram,0xbfd09f06)
    */

void FUN_ram_bfd09f04(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7,uint param_8)

{
  char cVar1;
  undefined4 uVar2;
  int extraout_r1;
  int extraout_r1_00;
  uint uVar3;
  int in_r12;
  int iVar4;
  int unaff_r13;
  int unaff_r14;
  uint unaff_r15;
  int iVar5;
  int unaff_r25;
  int unaff_gp;
  undefined4 in_r48;
  undefined4 in_r52;
  undefined4 in_r53;
  undefined4 in_mlo;
  undefined4 in_mmid;
  undefined1 uVar6;
  bool bVar7;
  undefined1 in_C;
  char in_V;
  undefined8 uVar8;
  int in_stack_00000040;
  
code_r0xbfd09f04:
  *(char *)(in_r12 + 0x15) = (char)unaff_r15;
  func_0xbfd1e30c(*(undefined2 *)(unaff_gp + 0x68),param_2);
  iVar5 = extraout_r1_00;
  do {
    iVar4 = param_3 + 2;
    uVar8 = CONCAT44(iVar5,(uint)*(byte *)(unaff_gp + 0x44));
    if (unaff_r15 == 0) {
      if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
code_r0xbfd09f22:
      *(char *)(unaff_r13 + 0x16) = (char)iVar5;
      cVar1 = ext_condition(0x11);
      if (cVar1 != '\0') {
        uVar8 = func_0xbfd32b64();
      }
      uVar3 = (uint)((ulonglong)uVar8 >> 0x20);
      iVar5 = (int)uVar8;
      if (unaff_r14 == 0) {
        iVar5 = asm_instruction_08(0x22,unaff_r25,0x4bf);
        uVar6 = iVar5 == 0;
        if ((bool)in_C) {
          func_0xbfd26cc4(0xad16ee4c);
        }
        uVar2 = FUN_ram_bfd08fd0();
        if (!(bool)uVar6) {
          asm_instruction_08(0x22,in_r53,in_mmid);
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        asm_instruction_08(0x22,uVar2,0xfffffb80);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    else {
      unaff_r25 = asm_instruction_08(0x31,unaff_r25,0x4bf);
      if (!(bool)in_C && unaff_r25 != 0) {
        unaff_r15 = (uint)*(ushort *)(*(byte *)(unaff_gp + 0x44) + 8);
        in_r48 = asm_instruction_06(0x31,in_r48,in_mlo);
        goto code_r0xbfd09f22;
      }
      if (iVar5 == 0) break;
      uVar3 = (uint)*(byte *)(unaff_r13 + 0x11);
      iVar5 = in_stack_00000040;
    }
    iVar4 = asm_instruction_05(0x21,param_6,in_r52);
    bVar7 = iVar4 == 0;
    uVar2 = func_0xbfd1e36c(iVar5,uVar3);
    do {
      if (unaff_r13 != 0) {
        uVar2 = *(undefined4 *)(unaff_gp + 0x110);
      }
    } while (unaff_r15 == 0);
    if (!(bool)in_C && !bVar7) {
      asm_instruction_06(0x31,in_r48,in_mlo);
      *(char *)(unaff_r13 + 0x16) = (char)uVar2;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x14);
    func_0xbfd1e30c();
    iVar5 = extraout_r1;
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  } while( true );
  asm_instruction_06(0x20,param_3,unaff_r15);
  *(undefined4 *)(param_3 + 0x24) = 0;
  iVar5 = in_stack_00000040;
  if ((bool)in_V != unaff_r25 < 0) {
    iVar5 = func_0xbfc642f4();
  }
  param_2 = asm_instruction_06(0,param_3,0);
  *(char *)(iVar5 + 0xd) = (char)param_3;
  in_r12 = iVar4 >> 6;
  unaff_r15 = param_8;
  goto code_r0xbfd09f04;
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09f5c(void)

{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  int unaff_r13;
  char unaff_gp;
  char in_Z;
  undefined1 in_V;
  
  uVar3 = asm_instruction_08(0x23,(uint)*(byte *)(unaff_r13 + 0xf),0xc0);
  *(char *)(unaff_r13 + 0x1a) = (char)uVar3;
  cVar2 = ext_condition(0x11);
  if (cVar2 != '\0') {
    func_0xbfca2368();
  }
  cVar2 = ext_condition(0x1d);
  if (cVar2 != '\0') {
    func_0xbfd32bac();
  }
  FUN_ram_bfd09f5c();
  if (in_Z != '\0') {
    cVar2 = unaff_gp + -0x28;
    if ((bool)in_V) {
      cVar2 = func_0xbfc65378();
    }
    cVar1 = ext_condition(0x10);
    if (cVar1 == '\0') {
      *(char *)(unaff_r13 + 0x1a) = cVar2;
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd09fe4(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 in_r12;
  undefined4 unaff_r20;
  char in_V;
  
  uVar1 = asm_instruction_08(0x12,param_1,param_1);
  asm_instruction_08(0x10,uVar1,uVar1);
  if (in_V == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_V != '\0') {
    asm_instruction_07(0x1a,in_r12,unaff_r20);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0a094(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 unaff_r25;
  undefined4 in_mmid;
  
  FUN_ram_bfd09f04();
  asm_instruction_06(0x20,param_3,0x3c0);
  asm_instruction_06(0,in_mmid,0x3f);
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    asm_instruction_08(0x22,unaff_r25,0x4bf);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0a3fc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0a620(undefined4 param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  uint uVar2;
  int extraout_r1;
  uint unaff_r13;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r40;
  undefined4 in_r53;
  undefined1 uVar3;
  
  if (param_2 != 0) {
    asm_instruction_08(0x22,unaff_r25,0x4bf);
                    /* WARNING: Call to offcut address within same function */
    func_0xbfd0a630(unaff_gp + -0xdc);
    uVar3 = unaff_r13 < 0x44;
    asm_instruction_08(0x22,extraout_r1 << 2,extraout_r1 << 2);
    asm_instruction_08(0x22,in_r53,in_r40);
    uVar2 = (uint)*(ushort *)(unaff_gp + 8);
    cVar1 = ext_condition(0x13);
    if (cVar1 != '\0') {
      uVar2 = func_0xbfddca38();
    }
    *(uint *)(param_3 + 0x82) = uVar2;
    *(uint *)(param_4 + 0x68) = unaff_r13;
    if ((bool)uVar3) {
      func_0xbfcaa2c4();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0a68c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7,int param_8)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r25;
  int iVar5;
  undefined4 in_r48;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined8 uVar8;
  
  uVar4 = (uint)*(ushort *)(in_r12 + 0x20);
  cVar1 = ext_condition(0x1c);
  if (cVar1 == '\0') {
    uVar2 = *(undefined4 *)(param_4 + 0x30);
    *(char *)(uVar4 + 5) = (char)param_8;
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
      uVar8 = func_0xbfc64b48(uVar2);
      param_2 = (undefined4)((ulonglong)uVar8 >> 0x20);
      uVar2 = (undefined4)uVar8;
    }
    iVar5 = asm_instruction_08(0x22,unaff_r25,0x4bf);
    uVar6 = iVar5 == 0;
    uVar7 = iVar5 < 0;
    uVar3 = asm_instruction_08(0x31,param_2,0x40);
    asm_instruction_06(0x31,uVar4,param_5);
    *(int *)(*(int *)(unaff_r14 + 0x48) + 0x78) = param_4;
    if (param_8 != 0) {
      FUN_ram_bfd09820(uVar2,uVar3);
    }
    func_0xbfca2cf4(*(undefined1 *)(unaff_r13 + 0x14));
    if (!(bool)uVar7 && !(bool)uVar6) {
      func_0xbfca2cf4();
    }
    asm_instruction_06(2,in_r48,0x2d);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0a698(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7,int param_8)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r25;
  int iVar3;
  undefined4 in_r48;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined8 uVar6;
  
  uVar6 = CONCAT44(param_2,param_1);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    uVar6 = func_0xbfc64b48();
  }
  iVar3 = asm_instruction_08(0x22,unaff_r25,0x4bf);
  uVar4 = iVar3 == 0;
  uVar5 = iVar3 < 0;
  uVar2 = asm_instruction_08(0x31,(int)((ulonglong)uVar6 >> 0x20),0x40);
  asm_instruction_06(0x31,param_3,param_5);
  *(undefined4 *)(*(int *)(unaff_r14 + 0x48) + 0x78) = param_4;
  if (param_8 != 0) {
    FUN_ram_bfd09820((int)uVar6,uVar2);
  }
  func_0xbfca2cf4(*(undefined1 *)(unaff_r13 + 0x14));
  if (!(bool)uVar5 && !(bool)uVar4) {
    func_0xbfca2cf4();
  }
  asm_instruction_06(2,in_r48,0x2d);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0a720(void)

{
  int iVar1;
  undefined4 in_r53;
  
  iVar1 = asm_instruction_08(4,in_r53,0x39);
  if (iVar1 != 0) {
    func_0xbfd8dbc8();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0a868(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     int param_5)

{
  uint uVar1;
  undefined4 uVar2;
  int unaff_r13;
  int unaff_r14;
  int iVar3;
  undefined4 unaff_r17;
  bool in_Z;
  bool in_C;
  
  asm_instruction_08(0x22,param_1,param_1);
  if (!in_C && !in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar2 = *(undefined4 *)(unaff_r13 + 0x10);
  iVar3 = asm_instruction_08(0x22,unaff_r17,0);
  uVar1 = (uint)*(byte *)(unaff_r14 + 8);
  *(uint *)uVar1 = uVar1;
  if (iVar3 != 0) {
    func_0xbfd8dc88(uVar1,param_2,uVar2,param_4,param_5 + -100);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0a86c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     int param_5)

{
  uint uVar1;
  undefined4 uVar2;
  int unaff_r13;
  int unaff_r14;
  int iVar3;
  undefined4 unaff_r17;
  bool in_Z;
  bool in_C;
  
  if (!in_C && !in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar2 = *(undefined4 *)(unaff_r13 + 0x10);
  iVar3 = asm_instruction_08(0x22,unaff_r17,0);
  uVar1 = (uint)*(byte *)(unaff_r14 + 8);
  *(uint *)uVar1 = uVar1;
  if (iVar3 != 0) {
    func_0xbfd8dc88(uVar1,param_2,uVar2,param_4,param_5 + -100);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0a898(void)

{
  ext_condition(0x10);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0a914(undefined1 param_1)

{
  char cVar1;
  int extraout_r1;
  undefined4 in_r8;
  int in_r12;
  uint unaff_r13;
  int unaff_r15;
  undefined4 unaff_r16;
  undefined4 in_r32;
  undefined4 in_r37;
  undefined4 in_r53;
  undefined4 in_r61reserved;
  undefined1 in_Z;
  
  asm_instruction_06(0x10,unaff_r16,in_r61reserved);
  *(undefined1 *)(unaff_r15 + 7) = param_1;
  asm_instruction_05(0x2d,in_r53,0xfffff834);
  *(short *)(in_r12 + 4) = (short)in_r12;
  func_0xbfd0a908();
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 == 0) {
    unaff_r13 = (uint)*(byte *)(extraout_r1 + 1);
  }
  if (unaff_r13 != 0) {
    cVar1 = ext_condition(0x15);
    asm_instruction_08(0x1f,in_r37,0x570);
    if (cVar1 != '\0') {
      func_0xbfd94cf8();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!(bool)in_Z) {
    func_0xbfddfb34();
  }
  asm_instruction_06(0,in_r8,in_r32);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0ab74(void)

{
  uint uVar1;
  undefined4 uVar2;
  int in_r3;
  undefined4 in_r4;
  int in_r12;
  undefined1 unaff_r13;
  int unaff_r14;
  undefined1 unaff_r15;
  int unaff_gp;
  int iVar3;
  char in_V;
  
  *(char *)(in_r3 + 0x11) = (char)in_r12;
  *(undefined1 *)(in_r3 + 0x15) = unaff_r15;
  *(undefined1 *)(in_r3 + 3) = unaff_r13;
  *(undefined1 *)(in_r3 + 0xd) = unaff_r15;
  *(undefined1 *)(in_r3 + 0x15) = unaff_r15;
  *(undefined1 *)(in_r3 + 0x1d) = unaff_r15;
  *(char *)(in_r3 + 0x1f) = (char)in_r12;
  iVar3 = asm_instruction_06(0x1c,in_r4,0xf);
  if (iVar3 != 0 && (bool)in_V == iVar3 < 0) {
    asm_instruction_07(0x1c,(uint)*(ushort *)(unaff_gp + 0x62),0xf);
    uVar1 = (uint)*(ushort *)(unaff_gp + 0x44);
    if (unaff_r14 != 0) {
      uVar1 = FUN_ram_bfd09d14(uVar1,*(undefined1 *)(in_r12 + 0xc));
    }
    uVar2 = asm_instruction_08(0x22,uVar1,0);
    *(short *)(unaff_r14 + 4) = (short)uVar2;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0ae36(undefined2 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined2 in_r12;
  undefined4 unaff_r25;
  undefined4 in_r38;
  bool in_Z;
  char in_N;
  char in_V;
  
  uVar2 = asm_instruction_08(4,in_r38,unaff_r25);
  cVar1 = ext_condition(0x1d);
  *param_1 = in_r12;
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  param_1[-0x3f] = (short)uVar2;
  if (in_Z || in_V != in_N) {
    param_1[-0x42] = in_r12;
    param_1[-0x94] = in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0affa(void)

{
  undefined4 unaff_r17;
  
  asm_instruction_08(0x22,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0b14c(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 unaff_r25;
  int unaff_gp;
  
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    func_0xbfd3b54c();
  }
  iVar3 = *(int *)(param_3 + 0x60);
  cVar1 = ext_condition(0x1c);
  uVar2 = *(undefined2 *)(unaff_gp + 0x26);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(short *)(param_4 + 0x1a) = (short)iVar3;
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    func_0xbfd33d5c(uVar2);
  }
  if (iVar3 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x22,unaff_r25,0x4bf);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd0b1a0(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int in_r12;
  int unaff_r13;
  undefined4 unaff_r20;
  undefined4 unaff_r25;
  undefined4 uVar1;
  undefined4 in_r36;
  undefined4 in_r48;
  undefined4 in_r52;
  undefined4 in_r56;
  undefined4 in_mlo;
  
  if (unaff_r13 != 0) {
    *(undefined2 *)(in_r12 + 8) = param_3;
    asm_instruction_06(0x13,in_r56,7);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar1 = asm_instruction_08(0x22,unaff_r25,0x4bf);
  asm_instruction_06(0x22,in_r52,0x39);
  asm_instruction_08(0x33,in_r36,0x52);
  asm_instruction_08(0x30,unaff_r20,0x3d);
  asm_instruction_07(2,in_r48,in_mlo);
  asm_instruction_08(0x24,uVar1,0x4bf);
  asm_instruction_06(4,in_r56,0xfffffe07);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0b5f4(void)

{
  undefined4 in_r8;
  int unaff_r13;
  undefined4 in_blink;
  undefined4 in_r45;
  
  asm_instruction_06(0x20,in_r8,0x1d);
  asm_instruction_08(4,in_r45,in_blink);
  *(undefined4 *)(unaff_r13 + 0x18) = *(undefined4 *)(unaff_r13 + 0x70);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0b86c(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 unaff_r25;
  undefined4 in_blink;
  int in_r50;
  undefined4 in_r53;
  undefined4 in_r56;
  bool in_Z;
  undefined1 in_C;
  
  sVar1 = *(short *)(param_4 + 0x14);
  asm_instruction_08(0x30,unaff_r25,0x4bf);
  if (!in_Z) {
    in_blink = 0xbfd0b876;
    param_1 = func_0xbfd27c6c();
  }
  *(undefined2 *)(in_r50 + -0x30) = (short)in_r53;
  iVar3 = asm_instruction_06(0x10,(undefined2 *)(in_r50 + -0x30),in_r53);
  *(undefined4 *)(param_3 + 0xb0) = param_1;
  *(char *)(param_3 + 0x90) = (char)param_1;
  if (!(bool)in_C && iVar3 != 0) {
    sVar2 = *(short *)(param_4 + 0x3a);
    *(char *)(param_3 + 0x70) = (char)param_1;
    do {
      do {
      } while (sVar2 == 0);
    } while (sVar1 != 0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0,in_r56,in_blink);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0b8e0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int in_r12;
  int unaff_gp;
  
  FUN_ram_bfd0b86c(param_1,param_2,*(undefined2 *)(in_r12 + 6));
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    asm_instruction_06(0x25,unaff_gp + -0x2c,0xfffffa00);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0b920(void)

{
  char cVar1;
  undefined1 in_r3;
  int iVar2;
  int in_r12;
  uint uVar3;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r16;
  undefined4 unaff_r25;
  undefined4 uVar4;
  int unaff_gp;
  undefined4 in_blink;
  int in_r35;
  undefined4 in_r45;
  undefined4 in_r56;
  
  uVar4 = asm_instruction_08(0x22,unaff_r25,0x4bf);
  iVar2 = asm_instruction_06(2,in_r56,0x13);
  if (iVar2 != 0) {
    in_blink = 0xbfd0b92e;
    func_0xbfd28728(*(undefined1 *)(unaff_r13 + 8));
  }
  if (unaff_r14 == 0) {
    uVar3 = (uint)*(byte *)(in_r12 + 6);
    uVar4 = asm_instruction_08(0x24,uVar4,0x43f);
    cVar1 = ext_condition(0x1c);
    asm_instruction_08(0x24,uVar4,0x43f);
    if (cVar1 == '\0') {
      asm_instruction_06(4,unaff_r16,0x500);
      asm_instruction_08(0x24,in_r45,in_blink);
      cVar1 = ext_condition(0x11);
      if (cVar1 != '\0') {
        func_0xbfda3d70(*(undefined2 *)(unaff_gp + 0x1e));
      }
      cVar1 = ext_condition(0x10);
      if (cVar1 != '\0') {
        FUN_ram_bfd0d750();
      }
      *(undefined1 *)(in_r35 + 0x50) = in_r3;
      *(short *)(uVar3 + 6) = (short)unaff_r13;
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0b97a(undefined4 param_1)

{
  char cVar1;
  int in_r7;
  int in_r12;
  int unaff_r13;
  undefined4 unaff_r22;
  undefined4 unaff_r23;
  int unaff_gp;
  undefined4 in_ilink1;
  undefined4 in_r37;
  undefined1 in_Z;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined4 *)(in_r7 + 0x30) = param_1;
  asm_instruction_04(0x26,unaff_r23,0x10);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
    FUN_ram_bfd0bad8();
    cVar1 = ext_condition(0x12);
    if (cVar1 != '\0') {
      asm_instruction_05(0x3d,in_ilink1,0xc2);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x1c);
    if (cVar1 == '\0') {
      FUN_ram_bfd0bb10(unaff_gp + -0x80,unaff_r13,*(undefined4 *)(in_r12 + 0x40));
      asm_instruction_08(0x24,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (!(bool)in_Z) {
      func_0xbfc24d98();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0b9b6(void)

{
  undefined4 unaff_r13;
  undefined4 unaff_r16;
  bool in_C;
  
  if (!in_C) {
    asm_instruction_05(0x21,unaff_r13,unaff_r16);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0b9ca(undefined2 param_1)

{
  undefined4 in_r4;
  int unaff_r14;
  
  asm_instruction_06(0x3d,in_r4,0);
  *(undefined2 *)(unaff_r14 + 5) = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0b9de(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  int in_r12;
  int unaff_r13;
  undefined4 in_r52;
  char in_Z;
  
  if (unaff_r13 == 0) {
    *(undefined2 *)(in_r12 + 0x22) = param_4;
    if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(0x22,in_r52,0x39);
  }
  asm_instruction_08(0x23,param_1,param_1);
  asm_instruction_06(2,in_r52,0x339);
  FUN_ram_bfd0b5f4(DAT_ram_bfd0bc04);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0ba6a(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int in_r12;
  undefined4 in_r53;
  
  asm_instruction_05(0x3d,in_r53,0xb4);
  *(undefined2 *)(in_r12 + 6) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0bad8(undefined4 param_1)

{
  asm_instruction_08(0x23,param_1,param_1);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0bb10(void)

{
  undefined1 *unaff_r16;
  undefined1 unaff_r20;
  undefined4 unaff_r22;
  undefined4 in_r37;
  
  *unaff_r16 = unaff_r20;
  asm_instruction_08(0x17,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0bb7c(void)

{
  bool in_V;
  
  if (in_V) {
    func_0xbfc66074();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c008(int param_1)

{
  int unaff_r13;
  undefined4 *unaff_r16;
  undefined4 *puVar1;
  undefined4 unaff_r20;
  undefined4 unaff_r22;
  undefined4 in_r37;
  
  *(int *)(param_1 + 0x3c) = param_1;
  do {
    puVar1 = unaff_r16;
    *puVar1 = unaff_r20;
    unaff_r16 = (undefined4 *)((int)puVar1 + 2);
  } while (unaff_r13 != 0);
  puVar1[0x19] = unaff_r20;
  asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c024(undefined4 param_1)

{
  int unaff_r13;
  undefined4 unaff_r17;
  
  asm_instruction_08(0x22,param_1,param_1);
  do {
  } while (unaff_r13 == 0);
  asm_instruction_08(0x22,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c034(void)

{
  char in_Z;
  
  if (in_Z != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c084(undefined1 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int unaff_r13;
  undefined4 unaff_r17;
  undefined4 uVar2;
  
  *(int *)(param_3 + 0x7c) = param_3;
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
    param_1 = func_0xbfd34c88();
  }
  *(undefined1 *)(unaff_r13 + 0x10) = param_1;
  uVar2 = asm_instruction_08(0x22,unaff_r17,0);
  asm_instruction_08(0x22,uVar2,0x200);
  FUN_ram_bfd0b1a0();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c190(void)

{
  FUN_ram_bfd0b300();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c26e(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined1 unaff_r15;
  
  *(undefined1 *)(param_3 + 0x19) = unaff_r15;
  asm_instruction_06(4,param_1,0xfffffa44);
  func_0xbfd0c070(DAT_ram_bfd0c438);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_bfd0c2c4(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  undefined4 extraout_r1;
  undefined4 in_r8;
  int unaff_r13;
  undefined4 unaff_r14;
  int unaff_r15;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  int iVar4;
  undefined4 in_r37;
  int in_r48;
  undefined2 *puVar5;
  undefined4 in_mlo;
  undefined1 uVar6;
  char in_C;
  undefined1 in_V;
  undefined8 uVar7;
  
  iVar4 = asm_instruction_08(0x27,unaff_r25,0x4bf);
  uVar6 = iVar4 == 0;
  puVar5 = (undefined2 *)(in_r48 + -0xf9);
  *puVar5 = (short)in_mlo;
  if (!(bool)uVar6) {
    func_0xbfde14cc();
    param_2 = extraout_r1;
  }
  uVar3 = _DAT_ram_bfd0c368;
  asm_instruction_06(0,in_r8,0);
  if (!(bool)in_C && !(bool)uVar6) {
    asm_instruction_06(0x27,puVar5,in_mlo);
    asm_instruction_08(0x17,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  sVar2 = *(short *)(unaff_r15 + 0x26);
  uVar7 = CONCAT44(param_2,(int)sVar2);
  if ((bool)in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined4 *)(unaff_r13 + 0x44) = unaff_r14;
  if (!(bool)in_V) {
    uVar7 = FUN_ram_bfcfbeac((int)sVar2,param_2,uVar3);
  }
  if (in_C == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x17);
  if (cVar1 != '\0') {
    func_0xbfd96748((int)uVar7,(int)((ulonglong)uVar7 >> 0x20),0x30c082a4);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c354(void)

{
  int unaff_r14;
  
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c3a8(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfd0c370) */
/* WARNING: Removing unreachable block (ram,0xbfd0c340) */
/* WARNING: Removing unreachable block (ram,0xbfd0c374) */

void FUN_ram_bfd0c3bc(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  char cVar1;
  uint uVar2;
  int unaff_r13;
  undefined4 unaff_r25;
  undefined4 uVar3;
  undefined4 in_r48;
  undefined4 in_r52;
  undefined4 in_lp_count;
  
  asm_instruction_06(0x25,in_r48,0x334);
  asm_instruction_07(0x1d,in_r52,in_lp_count);
  uVar3 = asm_instruction_08(0x22,unaff_r25,0x4bf);
  uVar2 = (uint)*(byte *)(unaff_r13 + 7);
  *(undefined2 *)(uVar2 + 4) = param_3;
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x22,uVar3,0x4bf);
  *(short *)(uVar2 - 0x1c8) = (short)unaff_r13;
  if (unaff_r13 != 0) {
    *(short *)(uVar2 - 0x148) = (short)unaff_r13;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x12);
  if (cVar1 != '\0') {
    uVar2 = func_0xbfde1578();
  }
  func_0xc018c7cc(uVar2);
  FUN_ram_bfd0c2c4();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c494(void)

{
  undefined4 in_r6;
  undefined4 in_r50;
  
  asm_instruction_06(0x14,in_r50,0);
  asm_instruction_06(0x32,in_r6,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c608(undefined1 param_1)

{
  int unaff_r13;
  
  *(undefined1 *)(unaff_r13 + 0x13) = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd0c62c) overlaps instruction at (ram,0xbfd0c62a)
    */

void FUN_ram_bfd0c620(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  char cVar1;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  bool in_Z;
  
  if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((unaff_r14 != 0) && (cVar1 = ext_condition(0x18), cVar1 != '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(in_r12 + 6) = param_3;
  if (!in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0c664(undefined2 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 in_r10;
  undefined4 unaff_r21;
  undefined4 unaff_r25;
  undefined4 uVar1;
  int in_r48;
  undefined4 in_r50;
  undefined4 in_mmid;
  
  *(undefined2 *)(in_r48 + -0x1e0) = param_1;
  uVar1 = asm_instruction_08(0x30,unaff_r25,0x3ff);
  asm_instruction_06(0x10,in_r10,unaff_r21);
  asm_instruction_06(0,param_3,0);
  asm_instruction_06(0x20,param_3,4);
  uVar1 = asm_instruction_08(0x33,uVar1,0x4bf);
  asm_instruction_06(0x33,in_r50,6);
  asm_instruction_08(0x36,uVar1,0x4bf);
  asm_instruction_06(0x12,in_mmid,0xffffffff);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0ca64(void)

{
  undefined4 in_r10;
  undefined4 unaff_r17;
  
  asm_instruction_08(0x34,unaff_r17,0x200);
  asm_instruction_06(0x14,in_r10,0xc);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0cb22(undefined4 param_1)

{
  int iVar1;
  bool in_C;
  undefined8 uVar2;
  
  iVar1 = asm_instruction_06(0,param_1,3);
  if (!in_C) {
    iVar1 = FUN_ram_bfd0f8a4();
  }
  asm_instruction_06(0x18,iVar1 * 2,0x35);
  uVar2 = FUN_ram_bfd0f878(iVar1 * 2);
  asm_instruction_06(0x1c,(int)((ulonglong)uVar2 >> 0x20),0x713);
  asm_instruction_08(0x25,(int)uVar2,(int)uVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0cd18(void)

{
  char cVar1;
  int in_r3;
  undefined4 unaff_r25;
  undefined4 in_r48;
  undefined4 in_r52;
  
  if (in_r3 == 0) {
    cVar1 = ext_condition(0x1a);
    asm_instruction_06(0x10,in_r52,6);
    if (cVar1 != '\0') {
      func_0xbfc2799c();
    }
    asm_instruction_08(0x22,unaff_r25,0x4bf);
    asm_instruction_06(0x31,in_r52,6);
    asm_instruction_07(0x22,in_r48,6);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0cd24(void)

{
  undefined4 unaff_r25;
  undefined4 in_r48;
  undefined4 in_r52;
  
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  asm_instruction_06(0x31,in_r52,6);
  asm_instruction_07(0x22,in_r48,6);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd0cd94(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 unaff_r25;
  undefined4 in_r32;
  undefined4 in_r50;
  undefined4 in_r53;
  bool in_Z;
  bool in_C;
  
  if (in_C || in_Z) {
    FUN_ram_bfd0cd18();
    if (in_Z != false) {
      thunk_EXT_FUN_ram_c0474de2();
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(4,in_r32,0);
  uVar2 = asm_instruction_06(0x20,param_3,0xffffffc3);
  func_0xbfd2939c(param_1,*(undefined2 *)(param_3 + 8),uVar2);
  uVar2 = asm_instruction_08(0x33,unaff_r25,0x4bf);
  asm_instruction_06(0x33,in_r50,0x35);
  asm_instruction_08(0x36,uVar2,0x4bf);
  asm_instruction_06(0x16,in_r50,in_r53);
  FUN_ram_bfd0cd24();
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0cefc(void)

{
  undefined4 unaff_r17;
  
  asm_instruction_08(0x22,unaff_r17,0x200);
  FUN_ram_bfd0c008();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0cf08(void)

{
  char cVar1;
  int in_r12;
  int unaff_r13;
  int unaff_gp;
  undefined8 uVar2;
  
  uVar2 = FUN_ram_bfd0cf7c(*(undefined2 *)(unaff_gp + 8));
  uVar2 = FUN_ram_bfd0d080((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),
                           *(undefined4 *)(unaff_r13 + 0x10));
  FUN_ram_bfd0c084((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),*(undefined4 *)(unaff_r13 + 0x10));
  cVar1 = ext_condition(0x1c);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
    *(undefined2 *)(in_r12 + 6) = *(undefined2 *)(in_r12 + 0x20);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0cf7c(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 in_r8;
  int in_r12;
  int unaff_r14;
  undefined4 unaff_r17;
  bool in_Z;
  char in_N;
  char in_V;
  
  uVar2 = asm_instruction_08(0x23,param_1,param_2);
  uVar2 = asm_instruction_08(0x24,uVar2,param_2);
  *(short *)(in_r12 + 6) = (short)in_r12;
  if (param_2 == 0) {
    asm_instruction_08(0x22,unaff_r17,0x200);
    asm_instruction_06(2,in_r8,0xc);
    cVar1 = ext_condition(0x18);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  else {
    if (in_Z || in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x10);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(char *)(unaff_r14 + 0xc) = (char)uVar2;
    if (in_N == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (param_2 != 0) {
      if (in_Z || in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      cVar1 = ext_condition(0x10);
      if (cVar1 == '\0') {
        cVar1 = ext_condition(0x15);
        if (cVar1 == '\0') {
          asm_instruction_08(0x22,uVar2,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0d080(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int unaff_r13;
  undefined4 unaff_r17;
  undefined4 in_r24;
  bool in_Z;
  char in_N;
  char in_V;
  
  asm_instruction_06(0,in_r24,0x3a);
  uVar1 = asm_instruction_07(3,param_1,0x10);
  asm_instruction_06(0,param_2,uVar1);
  if (!in_Z && in_V == in_N) {
    if (!in_Z && in_V == in_N) {
      func_0xbfc77498();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 == 0) {
    asm_instruction_08(0x22,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0d4c8(void)

{
  FUN_ram_bfd0c608();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0d648(void)

{
  int unaff_r13;
  int unaff_gp;
  
  do {
  } while (unaff_r13 == 0);
  FUN_ram_bfd0c840(*(undefined2 *)(unaff_gp + 0x72));
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0d7b0(void)

{
  char cVar1;
  undefined1 in_r3;
  int unaff_r13;
  int unaff_r14;
  bool in_Z;
  char in_N;
  
  *(undefined1 *)(unaff_r13 + 7) = in_r3;
  if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_N == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x18);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_bfd0d898(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int in_r12;
  int unaff_r13;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  int iVar1;
  undefined4 in_r37;
  bool in_Z;
  char in_N;
  bool in_C;
  char in_V;
  
  iVar1 = asm_instruction_08(0x30,unaff_r25,0x4bf);
  if (!in_Z && in_V == in_N) {
    FUN_ram_bfd0ca64(_FUN_ram_bfd0d898,param_2);
    *(undefined2 *)(in_r12 + 6) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_C || iVar1 == 0) {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
  do {
  } while (unaff_r13 == 0);
  asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd0deb0) overlaps instruction at (ram,0xbfd0deae)
    */
/* WARNING: Removing unreachable block (ram,0xbfd0de84) */

void FUN_ram_bfd0de7c(void)

{
  int iVar1;
  int in_r6;
  undefined4 in_r9;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r25;
  undefined4 in_r33;
  undefined4 in_r38;
  int iVar2;
  undefined4 in_r48;
  int in_r52;
  undefined4 in_mmid;
  bool bVar3;
  char in_V;
  
  iVar2 = asm_instruction_08(0,unaff_r16,in_mmid);
  bVar3 = iVar2 < 0;
  if (unaff_r13 == 0) {
    asm_instruction_05(0x1a,in_r38,3);
    if (!bVar3) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (unaff_r14 != 0) {
      asm_instruction_08(0x22,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  else {
    in_V = SCARRY4(in_r6,0x38);
    in_r48 = asm_instruction_06(3,in_r48,0x13b);
    ext_condition(0x1a);
    asm_instruction_08(0x25,DAT_ram_bfd0e10c,DAT_ram_bfd0e10c);
    in_r52 = asm_instruction_06(3,in_r52,0x13b);
    bVar3 = in_r52 < 0;
    iVar2 = in_r52;
  }
  if (iVar2 == 0 || (bool)in_V != bVar3) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (iVar2 != 0 && (bool)in_V == bVar3) {
    iVar2 = asm_instruction_07(3,in_r48,0x13b);
    if (unaff_r13 == 0) {
      asm_instruction_07(0xc,unaff_r25,in_r33);
      if (unaff_r14 != 0) {
        *(undefined4 *)(iVar2 + -0xbd) = in_r9;
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    else {
      iVar1 = asm_instruction_06(3,in_r52,0x3b);
      if (iVar1 == 0 || (bool)in_V != iVar1 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_07(3,iVar2,0x3b);
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0df10(void)

{
  undefined4 in_r11;
  
  asm_instruction_08(0x10,in_r11,0x14);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0dfa0(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd0e012) overlaps instruction at (ram,0xbfd0e00e)
    */

void FUN_ram_bfd0dfbc(void)

{
  char cVar1;
  undefined2 in_r3;
  int in_r12;
  int unaff_r13;
  
  if (&stack0x00000000 == (undefined1 *)0x1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfd0dfa0();
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    *(char *)(in_r12 + 0x17) = (char)in_r12;
    if (&stack0x00000000 != (undefined1 *)0x12) {
      FUN_ram_bfd0dfbc();
      if (unaff_r13 == 0) {
        *(undefined2 *)(in_r12 + 8) = in_r3;
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(char *)(unaff_r13 + 0x14) = (char)in_r3;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0e552(void)

{
  undefined4 in_r4;
  int unaff_r14;
  undefined4 in_r37;
  undefined4 in_r47;
  
  asm_instruction_06(0x1d,in_r4,0x400);
  if (unaff_r14 != 0) {
    asm_instruction_04(0x11,in_r37,in_r47);
    asm_instruction_08(0x1f,in_r37,0x470);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0e5a2(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *unaff_r13;
  int unaff_gp;
  bool in_Z;
  char in_N;
  bool in_C;
  char in_V;
  
  uVar1 = *unaff_r13;
  if (!in_Z && in_V == in_N) {
    if (!in_C) {
      func_0xbfd9f1e4(param_1,param_2,uVar1);
    }
    asm_instruction_07(0x1d,uVar1,*(undefined4 *)(unaff_gp + 0x198));
    ext_condition(0x15);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0e5b8(void)

{
  bool in_Z;
  char in_N;
  char in_V;
  
  if (!in_Z && in_V == in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0ea30(void)

{
  short in_r12;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  undefined4 in_r37;
  int in_r48;
  
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  *(short *)(in_r48 + -0x13c) = in_r12 + -4;
  asm_instruction_08(0x15,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0ea38(undefined2 param_1)

{
  undefined4 unaff_r22;
  undefined4 in_r37;
  int in_r48;
  
  *(undefined2 *)(in_r48 + -0x13c) = param_1;
  asm_instruction_08(0x15,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0ee84(int param_1)

{
  undefined4 in_r4;
  int unaff_fp;
  int iVar1;
  bool in_Z;
  
  if (!in_Z) {
    param_1 = func_0xbfd38284();
  }
  iVar1 = asm_instruction_06(0x3c,in_r4,0xf);
  if (iVar1 != 0) {
    func_0xbfd93420(param_1 + unaff_fp);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0f2fc(void)

{
  undefined2 in_r3;
  int in_r12;
  
  *(undefined2 *)(in_r12 + 4) = in_r3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0f3b0(void)

{
  int unaff_r15;
  undefined1 in_N;
  
  func_0xbfd0f640();
  thunk_EXT_FUN_ram_bee2eb5c();
  if (!(bool)in_N) {
    FUN_ram_bfd0f3ac(*(undefined1 *)(unaff_r15 + 7));
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0f4c4(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0f580(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  int unaff_r13;
  undefined2 unaff_r15;
  undefined4 unaff_r22;
  bool in_Z;
  bool in_C;
  
  if (in_C || in_Z) {
    asm_instruction_06(0x22,param_5,1);
    asm_instruction_08(0x23,param_5,0xfffffa38);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(param_1 + 0x22) = unaff_r15;
  asm_instruction_07(2,param_1,param_2);
  if (unaff_r13 != 0) {
    *(undefined4 *)(param_1 + -0x290) = unaff_r22;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0f878(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 unaff_r25;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r48;
  ushort *in_r54;
  
  uVar2 = asm_instruction_08(0x22,unaff_r25,0x4bf);
  iVar3 = asm_instruction_08(0x22,uVar2,0x4bf);
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    uVar2 = asm_instruction_08(0x24,(uint)*in_r54,0);
    *(short *)(param_2 + 0x36) = (short)uVar2;
    if (iVar3 != 0) {
      func_0xbfd2bc94();
    }
    uVar2 = asm_instruction_08(0x22,iVar3,0x43f);
    asm_instruction_06(2,in_r48,4);
    asm_instruction_08(0x24,uVar2,0x43f);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0f938(void)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 in_r6;
  int unaff_r13;
  undefined4 unaff_r25;
  undefined4 uVar3;
  int unaff_gp;
  int in_r48;
  undefined4 in_r52;
  int iVar4;
  undefined4 in_r61reserved;
  undefined1 in_Z;
  undefined1 uVar5;
  char in_N;
  char in_V;
  
  uVar2 = *(undefined2 *)(unaff_gp + 0x20);
  *(undefined4 *)(in_r48 + -0x278) = in_r6;
  if ((bool)in_Z) {
    func_0xbfcebd80(uVar2);
  }
  if ((bool)in_Z || in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar3 = asm_instruction_08(0x24,unaff_r25,0x4bf);
  *(undefined4 *)(in_r48 + -0x2f0) = in_r6;
  asm_instruction_08(0x22,uVar3,0x4bf);
  asm_instruction_06(2,in_r52,6);
  iVar4 = asm_instruction_07(3,in_r48,6);
  uVar5 = iVar4 == 0;
  cVar1 = ext_condition(0x15);
  asm_instruction_08(4,in_r61reserved,0x1f);
  if (cVar1 != '\0') {
    func_0xbfdaf55c();
  }
  if (!(bool)uVar5) {
    func_0xbfc3076c();
  }
  if (!(bool)in_V) {
    if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_06(4,in_r52,0x780);
    asm_instruction_07(3,in_r48,0xfffffe86);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd0fc5c) overlaps instruction at (ram,0xbfd0fc56)
    */

void FUN_ram_bfd0fc50(void)

{
  undefined2 in_r3;
  int in_r12;
  int unaff_r15;
  undefined4 in_r53;
  bool in_Z;
  bool in_C;
  
  if (!in_C && !in_Z) {
    func_0xbfded0d0();
  }
  if (unaff_r15 != 0) {
    asm_instruction_08(0x22,in_r53,0xad13ed81);
  }
  *(undefined2 *)(in_r12 + 4) = in_r3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0fda8(undefined4 param_1,undefined1 param_2)

{
  int iVar1;
  undefined4 *in_r32;
  undefined4 in_r48;
  bool in_N;
  
  iVar1 = asm_instruction_06(3,param_1,0x1c0);
  *(undefined1 *)(iVar1 + 0x18) = param_2;
  if (!in_N) {
    *in_r32 = in_r48;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd0fe40(undefined4 param_1)

{
  int unaff_r13;
  undefined1 *unaff_r16;
  undefined1 unaff_r20;
  undefined4 in_r42;
  
  *unaff_r16 = unaff_r20;
  asm_instruction_04(0x3d,in_r42,param_1);
  *(short *)(unaff_r13 + 10) = (short)unaff_r13;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Instruction at (ram,0xbfd10138) overlaps instruction at (ram,0xbfd10136)
    */
/* WARNING: Removing unreachable block (ram,0xbfd100ea) */
/* WARNING: Removing unreachable block (ram,0xbfc22526) */
/* WARNING: Removing unreachable block (ram,0xbfd64178) */

void FUN_ram_bfd100b8(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int unaff_r14;
  undefined1 unaff_r15;
  undefined4 unaff_r17;
  int unaff_gp;
  uint in_r38;
  undefined4 in_r48;
  char in_Z;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 in_C;
  char cVar7;
  char in_V;
  char cVar8;
  undefined8 uVar9;
  
  uVar9 = CONCAT44(param_2,param_1);
  if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar4 = asm_instruction_06(2,in_r48,0x2e);
  uVar5 = iVar4 == 0;
  if (unaff_r14 == 0) {
    if ((bool)uVar5 || (bool)in_V != iVar4 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    while( true ) {
      uVar3 = asm_instruction_08(0x24,(int)((ulonglong)uVar9 >> 0x20),0x600);
      if ((bool)in_C || (bool)uVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      *(undefined1 *)(param_3 + 0x19) = unaff_r15;
      uVar2 = asm_instruction_06(4,(int)uVar9,0xfffffa4c);
      uVar9 = CONCAT44(uVar3,uVar2);
      cVar8 = ext_condition(0x10);
      if (cVar8 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      uVar6 = uVar3 == in_r38;
      in_C = uVar3 < in_r38;
      cVar8 = SBORROW4(uVar3,in_r38);
      if (!(bool)uVar5) {
        uVar9 = FUN_ram_bfd10aa4(uVar2);
      }
      iVar4 = asm_instruction_08(0x24,(int)((ulonglong)uVar9 >> 0x20),0x80);
      if (!(bool)in_C && !(bool)uVar6) {
        *(undefined1 *)(param_3 + 0x19) = unaff_r15;
        asm_instruction_06(4,(int)uVar9,0xfffffa44);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
        halt_unimplemented();
      }
      *(undefined1 *)(param_3 + 0x19) = unaff_r15;
      if (cVar8 == '\0') {
        cVar8 = iVar4 + -0x38 < 0;
        cVar7 = SBORROW4(iVar4,0x38);
        uRam00000003 = 0;
        if (!(bool)cVar7) {
          func_0xbfdef5e4(*(undefined2 *)(unaff_gp + 0xf2));
        }
        if (cVar7 != cVar8) {
          func_0xbfc19de8();
        }
        asm_instruction_08(0x22,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_06(4,(int)uVar9,0xfffffa54);
      cVar8 = ext_condition(0x10);
      if (cVar8 != '\0') break;
      iVar1 = asm_instruction_05(0xc,iVar4,0x26);
      uVar9 = CONCAT44(iVar4,iVar1);
      uVar5 = iVar1 == 0;
      if (!(bool)uVar6) {
        uVar9 = FUN_ram_bfd10a8c();
      }
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar8 = ext_condition(0x10);
  if (cVar8 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (iVar4 >= 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd10324(undefined1 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4,
                     int param_5)

{
  int unaff_r13;
  undefined4 unaff_r17;
  
  asm_instruction_08(4,unaff_r13,0x11);
  *(undefined1 *)(unaff_r13 + 0xf) = param_2;
  asm_instruction_08(0x22,(int)*(char *)(param_5 + -0xa4),0x4bf);
  *(undefined1 *)(unaff_r13 + 8) = param_1;
  asm_instruction_08(0x22,unaff_r17,0x200);
  FUN_ram_bfd0f4c4();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd10378(void)

{
  ushort uVar1;
  undefined4 in_r11;
  undefined4 unaff_r22;
  int unaff_gp;
  undefined4 in_r37;
  
  uVar1 = *(ushort *)(unaff_gp + 0xe);
  *(undefined4 *)(uVar1 - 0x290) = in_r11;
  *(undefined4 *)(uVar1 - 0x210) = in_r11;
  asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd103a4) overlaps instruction at (ram,0xbfd103a2)
    */

void FUN_ram_bfd10398(int param_1,undefined4 param_2,undefined2 param_3)

{
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int unaff_gp;
  int in_r53;
  bool in_Z;
  char in_N;
  char in_V;
  
  if (unaff_r13 == 0) {
    if (!in_Z && in_V == in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
code_r0xbfd103a8:
    *(int *)(param_1 + 0x5d) = param_1;
    *(char *)(param_1 + 0xbd) = (char)param_1;
    if (unaff_r13 == 0) goto LAB_ram_bfd103c0;
    param_1 = *(int *)(unaff_gp + 0x110);
    in_r12 = unaff_r14 << 1;
  }
  else {
    *(int *)(param_1 + 0x5d) = param_1;
    if (unaff_r13 != 0) goto code_r0xbfd103a8;
  }
  *(char *)(in_r53 + -0xdc) = (char)param_1;
LAB_ram_bfd103c0:
  *(undefined2 *)(in_r12 + 6) = param_3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd10428(void)

{
  undefined4 unaff_r13;
  undefined4 in_r24;
  undefined4 in_r33;
  undefined4 in_r56;
  undefined4 uVar1;
  
  uVar1 = asm_instruction_08(0x22,in_r56,0x3f);
  asm_instruction_05(0x2d,unaff_r13,in_r33);
  asm_instruction_08(0x22,uVar1,0xfffffc7f);
  asm_instruction_05(0x2d,unaff_r13,in_r24);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd104e0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 in_r42;
  undefined1 in_N;
  char in_V;
  
  uVar2 = asm_instruction_08(6,param_1,0);
  if (in_V != '\0') {
    cVar1 = ext_condition(0x1f);
    if (cVar1 != '\0') {
      func_0xbfd9b8e8(uVar2);
    }
    asm_instruction_08(0x10,in_r42,0x204);
    if ((bool)in_N) {
      FUN_ram_bfd1192c();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd1050c(void)

{
  char cVar1;
  
  cVar1 = ext_condition(0x12);
  if (cVar1 == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd105d4(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  int in_r12;
  int unaff_r14;
  uint unaff_r20;
  undefined4 unaff_r21;
  undefined4 uVar4;
  uint in_r32;
  uint in_r36;
  undefined4 in_r37;
  undefined4 in_r42;
  undefined1 in_N;
  bool in_V;
  
  bVar2 = *(byte *)(param_1 + 0x1a);
  if ((unaff_r20 & 0x100000) == 0) {
    if (!in_V) {
      param_1 = func_0xbfd22a1c();
    }
    uVar4 = asm_instruction_05(0x22,unaff_r21,0x176);
    asm_instruction_05(0x24,uVar4,0xf6);
    asm_instruction_05(0x26,in_r37,0xfffff8c3);
    *(int *)param_1 = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar4 = asm_instruction_06(3,param_3,0);
  if (in_r32 <= in_r36) {
    uVar3 = (uint)*(byte *)(bVar2 + 7);
    *(char *)(uVar3 + 0xd) = (char)param_3;
    if (!in_V) {
      uVar3 = func_0xbfe001dc();
    }
    if (unaff_r14 != 0) {
      do {
      } while (bVar2 == 0);
      asm_instruction_04(0x3d,in_r42,1);
      asm_instruction_08(0x1f,in_r37,0xfffffe70);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    cVar1 = ext_condition(0x10);
    *(uint *)uVar3 = uVar3;
    if (cVar1 != '\0') {
      func_0xbfd93bdc();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfd104e0(*(undefined1 *)(in_r12 + 0xd),param_2,param_3,uVar4);
  cVar1 = ext_condition(0x1f);
  if (cVar1 != '\0') {
    func_0xbfd9b920();
  }
  if ((bool)in_N) {
    func_0xbfd3a964();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd10860(undefined4 param_1)

{
  undefined4 uVar1;
  int unaff_r13;
  bool in_Z;
  bool in_C;
  
  if (!in_C && !in_Z) {
    uVar1 = asm_instruction_06(0x10,param_1,0xfffffc08);
    *(char *)(unaff_r13 + 8) = (char)uVar1;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  FUN_ram_bfd0f938();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd108e0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 unaff_r22;
  int unaff_gp;
  undefined4 in_r37;
  
  uVar2 = func_0xbfd110e8();
  uVar2 = asm_instruction_08(0x25,uVar2,uVar2);
  FUN_ram_bfd109f4(uVar2);
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    func_0xbfd296f0(*(undefined2 *)(unaff_gp + 4));
  }
  asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd10a8c(void)

{
  undefined4 unaff_r22;
  undefined4 in_r37;
  
  FUN_ram_bfd10bfc();
  asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd10aa4(undefined4 param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  undefined4 uVar2;
  int unaff_r13;
  undefined4 unaff_r25;
  bool in_C;
  bool in_V;
  
  if (!in_C) {
    *(int *)(param_3 + 0x10) = param_3;
    bVar1 = *(byte *)(unaff_r13 + 9);
    if (!in_V) {
      func_0xbfe006ac();
    }
    asm_instruction_08(0x23,unaff_r25,0x47f);
    uVar2 = func_0xc015af30();
    asm_instruction_06(0x23,uVar2,0x31);
    *(char *)(bVar1 + 0x18) = (char)uVar2;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd10bfc(undefined4 param_1)

{
  undefined4 uVar1;
  int in_r7;
  int unaff_r14;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  int iVar2;
  undefined4 in_r32;
  undefined4 in_r37;
  undefined4 in_r48;
  undefined1 in_Z;
  char in_N;
  undefined1 in_C;
  
  asm_instruction_08(2,param_1,0);
  uVar1 = FUN_ram_bfd0fe40();
  if (in_N == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0,in_r32,uVar1);
  if (in_r7 == 0) {
    iVar2 = asm_instruction_08(0x24,unaff_r25,0x4bf);
    in_Z = iVar2 == 0;
  }
  if ((bool)in_C || (bool)in_Z) {
    uVar1 = asm_instruction_07(0x10,uVar1,uVar1);
    if ((bool)in_C) {
      func_0xbfd94078();
    }
    asm_instruction_06(0x25,uVar1,699);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar2 = asm_instruction_06(4,in_r48,0xfffffd3b);
  if (-1 < iVar2) {
    func_0xbfd2987c(uVar1,*(undefined2 *)(*(ushort *)(unaff_r14 + 0x34) + 0xc));
  }
  asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd11040(undefined4 param_1)

{
  int unaff_r14;
  bool in_C;
  
  if (unaff_r14 != 0) {
    if (in_C) {
      func_0xbfda8ce4();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(0,param_1,0xfffffe02);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd11140(int param_1,undefined4 param_2,int param_3,undefined2 param_4)

{
  char cVar1;
  uint uVar2;
  undefined2 uVar3;
  undefined4 in_r10;
  int in_r12;
  int unaff_r13;
  undefined4 in_r56;
  int iVar4;
  bool in_C;
  undefined8 uVar5;
  
  uVar5 = CONCAT44(param_2,param_1);
  iVar4 = asm_instruction_06(0x22,in_r56,0x3e);
  *(undefined2 *)(param_1 + 6) = param_4;
  if (iVar4 < 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
    *(undefined2 *)(in_r12 + 4) = param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(in_r12 + 4) = param_4;
  if (in_C) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar3 = *(undefined2 *)(param_3 + 0x16);
  cVar1 = ext_condition(0x12);
  if (cVar1 != '\0') {
    uVar5 = func_0xbfd63d54();
  }
  *(undefined2 *)((int)uVar5 + 4) = uVar3;
  uVar2 = (uint)bRam00000005;
  asm_instruction_06(0,in_r56,0x14);
  *(char *)((int)((ulonglong)uVar5 >> 0x20) + 0x12) = (char)uVar3;
  *(undefined4 *)(uVar2 - 0xa4) = in_r10;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd11394(void)

{
  int iVar1;
  undefined1 in_Z;
  char in_N;
  char in_V;
  
  iVar1 = func_0xbfd1051c();
  if (!(bool)in_Z && in_V == in_N) {
    func_0xbfd11524(iVar1 + 4);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd1147c(void)

{
  char cVar1;
  int unaff_r13;
  
  cVar1 = ext_condition(0x1e);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd1161c(int param_1,undefined4 param_2,undefined1 param_3)

{
  undefined4 in_r37;
  bool in_Z;
  bool in_C;
  
  if (!in_C && !in_Z) {
    *(undefined1 *)(param_1 + 0xd) = param_3;
    asm_instruction_06(0,param_1,0xfffffe83);
    asm_instruction_08(0x1f,in_r37,0x370);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd116c8(void)

{
  undefined4 in_r50;
  
  asm_instruction_07(0xe,in_r50,0xfffff87a);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd11714(void)

{
  int in_r48;
  undefined2 in_mlo;
  
  *(undefined2 *)(in_r48 + -0xb0) = in_mlo;
  FUN_ram_bfd10860();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd117c4(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 in_r38;
  
  uVar2 = asm_instruction_08(0x26,param_1,0x40);
  uVar2 = asm_instruction_08(0x25,uVar2,uVar2);
  cVar1 = ext_condition(0x1c);
  asm_instruction_04(0xb,in_r38,6);
  if (cVar1 == '\0') {
    FUN_ram_bfd108e0(uVar2);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd11a3e(void)

{
  char cVar1;
  int unaff_r13;
  undefined4 unaff_r22;
  undefined4 in_blink;
  undefined4 in_r37;
  undefined4 in_r39;
  undefined4 in_r45;
  undefined4 in_r48;
  undefined4 in_mlo;
  bool in_Z;
  bool in_C;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (&stack0x00000000 != (undefined1 *)0x3) {
    if (unaff_r13 != 0) {
      asm_instruction_08(0x35,in_r45,in_blink);
      asm_instruction_07(0x22,in_r39,0x570);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!in_C && !in_Z) {
    asm_instruction_06(0x30,in_r48,in_mlo);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd11bb6) overlaps instruction at (ram,0xbfd11bb4)
    */
/* WARNING: Removing unreachable block (ram,0xbfd11bb4) */
/* WARNING: Removing unreachable block (ram,0xbfd11ba0) */
/* WARNING: Removing unreachable block (ram,0xbfd11ba2) */
/* WARNING: Removing unreachable block (ram,0xbfd11b92) */
/* WARNING: Removing unreachable block (ram,0xbfc2cda4) */

void FUN_ram_bfd11b20(int param_1)

{
  undefined4 in_r9;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int unaff_r15;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  int iVar1;
  undefined4 in_r37;
  undefined4 in_r48;
  undefined4 in_mlo;
  char in_N;
  bool in_C;
  char in_V;
  
  if (unaff_r15 != 0) {
    iVar1 = asm_instruction_08(0x30,unaff_r25,0x4bf);
    if (!in_C && iVar1 != 0) {
      asm_instruction_06(0x30,in_r48,in_mlo);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (unaff_r14 == 0) {
      asm_instruction_08(0x26,iVar1,0x4bf);
      iVar1 = asm_instruction_06(6,in_r48,in_r9);
      if (in_C || iVar1 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_06(0x20,param_1,0x13);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_08(0x37,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (in_V == in_N) {
    asm_instruction_06(0x20,param_1,2);
    *(undefined2 *)(in_r12 + 8) = *(undefined2 *)(param_1 + 8);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd11d64(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined1 in_r7;
  undefined4 in_r11;
  undefined2 unaff_r21;
  undefined4 unaff_r25;
  int unaff_gp;
  int in_r48;
  undefined1 in_Z;
  char in_N;
  char in_C;
  char in_V;
  undefined8 uVar4;
  
  uVar4 = CONCAT44(param_2,param_1);
  if (in_C == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!(bool)in_V) {
    uVar4 = FUN_ram_bfd0196c();
  }
  iVar2 = (int)uVar4;
  *(undefined4 *)(iVar2 + -0xe4) = in_r11;
  if (in_V == in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x24,(int)((ulonglong)uVar4 >> 0x20),2);
  if ((bool)in_C || (bool)in_Z) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined1 *)(*(ushort *)(iVar2 + 4) + 0x19) = in_r7;
  asm_instruction_06(4,iVar2,0xfffff85c);
  uVar1 = *(ushort *)(unaff_gp + 8);
  *(undefined2 *)(uVar1 - 0xa4) = unaff_r21;
  puVar3 = (undefined2 *)(uVar1 - 0x148);
  *puVar3 = unaff_r21;
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  *(short *)(in_r48 + -0x13c) = (short)puVar3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd11ed8(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  undefined1 unaff_r15;
  undefined4 unaff_r22;
  undefined4 in_r37;
  undefined4 in_r56;
  bool in_Z;
  bool in_C;
  
  if (!in_C && !in_Z) {
    *(undefined1 *)(param_3 + 0x19) = unaff_r15;
    asm_instruction_06(4,param_1,0xfffffa44);
    asm_instruction_08(0x22,in_r56,0xfffffbbf);
    asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1b);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd11f30(void)

{
  int unaff_r13;
  undefined4 unaff_r22;
  undefined4 in_r37;
  
  if (unaff_r13 == 0) {
    func_0xbfd11f04();
  }
  do {
  } while (unaff_r13 == 0);
  asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd11f94(void)

{
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  undefined4 in_r37;
  bool in_C;
  
  if (in_C) {
    func_0xbfd2e5d8(DAT_ram_bfd11fd4);
  }
  asm_instruction_08(0x31,unaff_r17,0x3c0);
  asm_instruction_06(0x11,unaff_r18,0x514);
  asm_instruction_05(0x31,in_r37,0xfffff8c3);
  FUN_ram_bfd11f94();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd12116(void)

{
  int unaff_r14;
  undefined4 unaff_r22;
  undefined4 in_r37;
  
  do {
  } while (unaff_r14 != 0);
  asm_instruction_08(0x24,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Removing unreachable block (ram,0xbfd121fc) */
/* WARNING: Removing unreachable block (ram,0xbfd12182) */
/* WARNING: Removing unreachable block (ram,0xbfd1220c) */
/* WARNING: Removing unreachable block (ram,0xbfd1220e) */
/* WARNING: Removing unreachable block (ram,0xbfd12212) */
/* WARNING: Removing unreachable block (ram,0xbfd121a4) */
/* WARNING: Removing unreachable block (ram,0xbfd121a6) */
/* WARNING: Removing unreachable block (ram,0xbfd121f8) */
/* WARNING: Removing unreachable block (ram,0xbfd12204) */
/* WARNING: Removing unreachable block (ram,0xbfd1220a) */
/* WARNING: Removing unreachable block (ram,0xbfd1221c) */
/* WARNING: Removing unreachable block (ram,0xbfd12220) */
/* WARNING: Removing unreachable block (ram,0xbfd121bc) */
/* WARNING: Removing unreachable block (ram,0xbfd121e4) */

void FUN_ram_bfd1214a(undefined1 param_1,undefined4 param_2,int param_3,undefined1 param_4)

{
  int in_r7;
  int unaff_r13;
  int unaff_r14;
  int unaff_r15;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  undefined4 in_blink;
  undefined4 in_r34;
  undefined4 in_r37;
  undefined4 in_r45;
  undefined4 in_r48;
  undefined4 in_r52;
  undefined4 uVar1;
  int iVar2;
  undefined4 in_r56;
  undefined4 in_lp_count;
  
  if (unaff_r15 == 0) {
    asm_instruction_08(0x1f,in_r37,0x570);
    func_0xc099c5b0();
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  uVar1 = asm_instruction_07(0x1d,in_r52,in_lp_count);
  if (unaff_r14 != 0) {
    if (unaff_r14 == 0) {
      asm_instruction_08(0x15,in_r45,in_blink);
      asm_instruction_07(0xe,in_r34,0x470);
      uVar1 = asm_instruction_06(0x11,in_r48,0x334);
      in_r48 = asm_instruction_06(0x30,uVar1,0x13d);
      param_4 = (undefined1)*(undefined4 *)(param_3 + 0x34);
      if (in_r7 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    *(undefined1 *)(unaff_r13 + 0xd) = param_4;
    asm_instruction_06(0x11,in_r48,0x334);
    asm_instruction_08(0x15,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined1 *)(unaff_r13 + 0xf) = param_1;
  asm_instruction_08(0x30,unaff_r25,0x4bf);
  asm_instruction_06(0x11,in_r48,0x334);
  asm_instruction_06(0x30,in_r56,0xfffff80e);
  iVar2 = asm_instruction_07(0x1d,uVar1,0x3c);
  if (-1 < iVar2) {
    (*(code *)0x23)();
    return;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd12228(undefined4 param_1,undefined4 param_2,undefined1 param_3)

{
  undefined4 in_r8;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  int iVar1;
  int unaff_gp;
  undefined4 in_r37;
  undefined4 in_r48;
  undefined4 in_mlo;
  undefined1 uVar2;
  bool in_C;
  undefined1 in_V;
  
  asm_instruction_06(0,in_r8,*(undefined4 *)(unaff_gp + 0x110));
  iVar1 = asm_instruction_08(0x31,unaff_r25,0x4bf);
  uVar2 = iVar1 < 0;
  if (!in_C && iVar1 != 0) {
    asm_instruction_06(0x31,in_r48,in_mlo);
    asm_instruction_08(0x22,*(undefined4 *)(unaff_gp + 0x110),0x480);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar1 = func_0xc0c2c6f0();
  *(undefined1 *)(iVar1 + 0xd) = param_3;
  if (!(bool)in_V) {
    func_0xbfe01e44();
  }
  if (unaff_r14 == 0) {
    if ((bool)uVar2) {
      func_0xbfd42820();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  do {
  } while (unaff_r13 == 0);
  asm_instruction_08(0x28,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd122f2(void)

{
  undefined4 unaff_r17;
  
  asm_instruction_08(0x22,unaff_r17,0x200);
  FUN_ram_bfd1147c();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd12352(void)

{
  undefined4 in_r37;
  int in_r48;
  undefined4 in_r52;
  
  *(undefined4 *)(in_r48 + -0x9e) = in_r52;
  asm_instruction_08(0x3f,in_r37,0xfffffd7f);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd12540(void)

{
  undefined2 in_r3;
  int in_r12;
  int unaff_r13;
  bool in_N;
  
  if (in_N) {
    func_0xbfd25344();
  }
  do {
  } while (unaff_r13 != 0);
  *(undefined2 *)(in_r12 + 4) = in_r3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd1264c(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfd126d8) */

void FUN_ram_bfd126c6(undefined1 param_1)

{
  char cVar1;
  undefined1 in_r9;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  undefined4 in_r37;
  int in_r48;
  
  *(undefined1 *)(unaff_r13 + 7) = param_1;
  if (unaff_r14 == 0) {
    do {
    } while (unaff_r13 != 0);
    asm_instruction_08(0x22,unaff_r25,0x4bf);
    *(undefined1 *)(in_r48 + -0x9e) = in_r9;
    asm_instruction_08(0x39,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd12b50) overlaps instruction at (ram,0xbfd12b4e)
    */

void FUN_ram_bfd12b32(undefined4 param_1,undefined4 param_2,int param_3,undefined1 param_4)

{
  char cVar1;
  int unaff_r13;
  int unaff_r14;
  int unaff_r15;
  undefined4 unaff_r22;
  int unaff_gp;
  undefined4 in_r37;
  undefined4 in_r54;
  char in_Z;
  
  param_3 = param_3 + 2;
  if (unaff_r15 != 0) {
    param_3 = *(ushort *)(*(byte *)(unaff_gp + 0x24) + 8) - 5;
    asm_instruction_08(0x22,(uint)*(byte *)(unaff_gp + 0x24),0x4c0);
  }
  *(undefined1 *)(unaff_r14 + 0x1f) = param_4;
  if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (unaff_r13 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x13,param_3,0x761);
  if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_05(0xd,in_r54,0x3c);
  asm_instruction_08(0x19,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfd13008) */
/* WARNING: Removing unreachable block (ram,0xbfd13016) */
/* WARNING: Removing unreachable block (ram,0xbfd1301e) */
/* WARNING: Removing unreachable block (ram,0xbfd13026) */
/* WARNING: Removing unreachable block (ram,0xbfcef01c) */

void FUN_ram_bfd12f0c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4,
                     undefined4 param_5,undefined4 param_6)

{
  char cVar1;
  byte bVar2;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int unaff_gp;
  int in_r38;
  undefined4 in_r48;
  int in_r52;
  undefined4 in_r56;
  undefined1 in_V;
  
  asm_instruction_07(0x1c,param_1,10);
  asm_instruction_08(0x30,in_r56,0xfffffdff);
  cVar1 = ext_condition(0x11);
  asm_instruction_08(0x24,param_6,0x38);
  if (cVar1 != '\0') {
    func_0xbfdb2b18(unaff_gp + -0x70);
    param_2 = extraout_r1;
  }
  func_0xbfd2f564(param_2);
  bVar2 = *(byte *)(unaff_r13 + 0x19);
  if (in_r52 == in_r38) {
    asm_instruction_08(0x23,(uint)bVar2,(uint)bVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_06(6,in_r48,in_r52);
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0,extraout_r1_00,0x33);
  *(byte *)(unaff_r13 + 0x10) = bVar2;
  if (unaff_r13 != 0) {
    *(char *)(unaff_r13 + 0x14) = (char)param_4;
    if (!(bool)in_V) {
      func_0xbfe02c00();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(in_r12 + 8) = param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd12f98(void)

{
  int unaff_gp;
  bool in_Z;
  
  if (in_Z) {
    func_0xbfced3dc(*(undefined2 *)(unaff_gp + 4));
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd13122(void)

{
  undefined4 unaff_r13;
  
  asm_instruction_08(0x3f,unaff_r13,0x111);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd13154(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  char cVar1;
  undefined4 in_r6;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  uint unaff_r15;
  uint uVar2;
  undefined4 unaff_r22;
  undefined4 in_r32;
  undefined4 in_r33;
  undefined4 in_r36;
  undefined4 in_r37;
  undefined4 in_r50;
  
  if (unaff_r14 == 0) {
    if (unaff_r15 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    uVar2 = 0;
  }
  else {
    cVar1 = ext_condition(0x10);
    uVar2 = unaff_r15 & 0x7ffff;
    if (cVar1 != '\0') {
      func_0xbfd9663c();
    }
    in_r32 = asm_instruction_06(0x10,in_r50,in_r6);
  }
  *(char *)(unaff_r13 + 0xe) = (char)in_r12;
  asm_instruction_08(0x12,in_r36,in_r32);
  asm_instruction_05(0x22,in_r37,in_r33);
  if (unaff_r14 == 0) {
    *(undefined2 *)(in_r12 + 6) = param_3;
    cVar1 = ext_condition(0x1c);
    if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if ((unaff_r14 == 0) && (uVar2 == 0)) {
    asm_instruction_08(6,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd13512(void)

{
  int unaff_r13;
  undefined4 unaff_r16;
  undefined4 uVar1;
  undefined4 unaff_r25;
  
  uVar1 = asm_instruction_06(0x25,unaff_r16,0xfffffc0a);
  asm_instruction_08(0x25,unaff_r25,0x43f);
  asm_instruction_06(0x25,uVar1,0x503);
  if (unaff_r13 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd13768(int param_1)

{
  undefined2 in_r12;
  undefined4 unaff_r13;
  
  asm_instruction_07(0x1c,param_1,unaff_r13);
  *(undefined2 *)(param_1 + -0xe4) = in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd13b28(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 extraout_r1;
  int in_r12;
  int unaff_r13;
  int unaff_r14;
  int iVar1;
  undefined4 unaff_r17;
  undefined4 unaff_r21;
  undefined4 unaff_r25;
  undefined4 uVar2;
  undefined4 in_r38;
  undefined4 in_r48;
  undefined4 uVar3;
  undefined4 in_r52;
  bool in_V;
  
  *(short *)(unaff_r13 + 0x1a) = (short)unaff_r13;
  if (unaff_r14 != 0) {
    asm_instruction_05(0xd,in_r38,param_7);
    uVar2 = asm_instruction_08(0x24,unaff_r25,0x4bf);
    uVar3 = asm_instruction_06(4,in_r48,0x334);
    asm_instruction_08(0x25,uVar2,0x4bf);
    asm_instruction_06(0x25,uVar3,0x375);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(in_r12 + 2) = param_4;
  if (!in_V) {
    func_0xbfe038ac();
    param_2 = extraout_r1;
  }
  asm_instruction_06(0x3d,param_5,0);
  asm_instruction_08(0x24,unaff_r17,0);
  iVar1 = asm_instruction_05(0x21,unaff_r21,in_r52);
  if (iVar1 < 0) {
    func_0xbfd0c6fc(param_2);
  }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd13e50(void)

{
  char cVar1;
  undefined4 in_r37;
  undefined4 in_r47;
  
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 == '\0') {
    asm_instruction_05(0x2f,in_r37,in_r47);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Instruction at (ram,0xbfd13ec2) overlaps instruction at (ram,0xbfd13ec0)
    */

void FUN_ram_bfd13f28(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined1 extraout_r1;
  undefined1 extraout_r1_00;
  undefined1 extraout_r1_01;
  undefined1 uVar3;
  undefined4 uVar4;
  int unaff_r13;
  int unaff_r14;
  undefined1 unaff_r16;
  undefined2 unaff_r17;
  undefined2 unaff_r19;
  int unaff_r25;
  int unaff_gp;
  undefined4 in_r38;
  uint in_r39;
  undefined4 in_r45;
  undefined4 in_r47;
  bool bVar5;
  char in_Z;
  char cVar6;
  undefined1 in_C;
  char in_V;
  
  asm_instruction_05(0x3f,in_r45,0xfffff801);
  FUN_ram_bfd13f28(*(undefined2 *)(unaff_gp + 8));
  cVar6 = ext_condition(0x1e);
  uVar3 = extraout_r1_00;
  if (unaff_r14 == 0) {
    if (cVar6 != '\0') {
      func_0xbfdee3b0();
      uVar3 = extraout_r1_01;
    }
    cVar6 = ext_condition(0x10);
    if (cVar6 != '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(undefined1 *)(param_4 + 0x1c) = uVar3;
    if (in_Z == '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  while( true ) {
    uVar4 = asm_instruction_08(2,in_r38,0x30);
    func_0xbfd74b40(*(undefined2 *)(unaff_gp + 10),uVar3,param_3,uVar4);
    uVar4 = asm_instruction_08(0x1f,in_r39 & ~(1 << ((byte)in_r47 & 0x1f)),0x370);
    unaff_r25 = asm_instruction_08(0x22,unaff_r25,0x4bf);
    bVar5 = unaff_r25 == 0;
    cVar6 = unaff_r25 < 0;
    func_0xbfd13098();
    if (unaff_r14 == 0) {
      asm_instruction_05(0x34,uVar4,0xfffff8c3);
      if (bVar5 == false) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
      halt_unimplemented();
    }
    puVar1 = (undefined2 *)(uint)*(byte *)(unaff_gp + -0x1b);
    if ((bool)in_C || bVar5) break;
    asm_instruction_07(0x2e,unaff_r13,0x20);
    while (unaff_r13 == 0) {
      puVar1 = puVar1 + -0x72;
      *puVar1 = unaff_r17;
    }
    *puVar1 = unaff_r17;
    uVar3 = extraout_r1;
    if (unaff_r13 != 0) {
      *(undefined1 *)(puVar1 + -0x52) = unaff_r16;
      puVar2 = puVar1 + -0xa4;
      if (unaff_r13 != 0) {
        puVar2 = puVar1 + -0xf6;
        *puVar2 = unaff_r17;
        if (bVar5 || in_V != cVar6) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
      }
      *puVar2 = unaff_r19;
      asm_instruction_08(0x22,unaff_r25,0x4bf);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd13f6c(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd1400c(int param_1)

{
  int unaff_r13;
  bool in_N;
  
  *(char *)(param_1 + 0x18) = (char)param_1;
  *(char *)(unaff_r13 + 7) = (char)param_1;
  if (!in_N) {
    func_0xbfd6e12c();
  }
  FUN_ram_bfd13154();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd14058(void)

{
  undefined4 uVar1;
  int in_r12;
  undefined2 unaff_r15;
  
  *(undefined2 *)(in_r12 + 4) = unaff_r15;
  uVar1 = FUN_ram_bfd1400c();
  asm_instruction_07(0x28,uVar1,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd1467c(int param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r16;
  undefined4 unaff_r22;
  undefined4 unaff_r25;
  undefined4 in_r37;
  int in_r48;
  undefined4 in_r56;
  int iVar2;
  bool in_Z;
  bool in_C;
  char in_V;
  
  if (unaff_r13 != 0) {
    *(undefined4 *)(in_r48 + 0x50) = unaff_r16;
    *(undefined1 *)(param_1 + 0xd) = param_3;
    do {
    } while (unaff_r14 == 0);
    *(undefined4 *)(in_r48 + 0x60) = unaff_r16;
    if (in_C || in_Z) {
      asm_instruction_06(0x20,param_1,0x82);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar1 = asm_instruction_06(0,param_1,0xfffffe2e);
    if (unaff_r13 != 0) {
      *(undefined4 *)(in_r48 + 0xb0) = unaff_r16;
      *(short *)(in_r48 + 0x70) = (short)unaff_r16;
      asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    asm_instruction_08(0x25,unaff_r25,0x4bf);
    iVar2 = asm_instruction_06(0x25,in_r56,0xfffffc12);
    *(int *)(iVar1 + 0x60) = iVar1;
    if (iVar2 == 0 || (bool)in_V != iVar2 < 0) {
      func_0xbfd2db94();
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd1488a) overlaps instruction at (ram,0xbfd14888)
    */

void FUN_ram_bfd14884(int param_1,undefined4 param_2,undefined2 param_3)

{
  int in_r12;
  int unaff_r13;
  undefined4 unaff_r17;
  
  if (unaff_r13 != 0) {
    *(undefined2 *)(in_r12 + 6) = param_3;
    *(int *)(param_1 + 0x20) = param_1;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  asm_instruction_08(0x22,unaff_r17,0x200);
  func_0xbfd13a94();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd149e8(undefined4 param_1)

{
  int unaff_r14;
  undefined4 unaff_r17;
  undefined4 uVar1;
  
  asm_instruction_08(0x22,param_1,0x480);
  uVar1 = asm_instruction_08(0x23,unaff_r17,0x200);
  asm_instruction_08(0x22,uVar1,0x200);
  func_0xbfd13b7c(*(undefined1 *)(unaff_r14 + 0xb));
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd14a20(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 in_r37;
  
  FUN_ram_bfd13b28();
  asm_instruction_05(0x22,in_r37,param_3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd14a74(void)

{
  undefined4 in_r4;
  int iVar1;
  int unaff_gp;
  undefined4 in_r37;
  bool bVar2;
  
  asm_instruction_08(0x3f,in_r37,0xfffffc7f);
  asm_instruction_07(0x1d,(uint)*(byte *)(unaff_gp + -0x19),(uint)*(byte *)(unaff_gp + -0x19));
  iVar1 = asm_instruction_06(0x1c,in_r4,0x291);
  bVar2 = iVar1 == 0;
  FUN_ram_bfd14884(DAT_ram_bfd14c90);
  if (bVar2) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd1510c(void)

{
  undefined4 uVar1;
  int unaff_r14;
  int unaff_gp;
  bool in_N;
  
  do {
  } while (unaff_r14 != 0);
  uVar1 = asm_instruction_06(0x10,(uint)*(ushort *)(unaff_gp + 8),0x10);
  if (in_N) {
    func_0xbfd9f5b4(uVar1);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd1583c(void)

{
  undefined4 in_r8;
  undefined4 unaff_r22;
  undefined4 in_r37;
  
  asm_instruction_06(0,in_r8,0);
  asm_instruction_08(4,in_r37,unaff_r22);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0xbfd15820) */

void FUN_ram_bfd15864(void)

{
  char cVar1;
  undefined1 uVar2;
  int in_r12;
  int unaff_r13;
  int iVar3;
  int unaff_r14;
  int unaff_r15;
  undefined4 unaff_r16;
  undefined4 unaff_r25;
  undefined4 uVar4;
  undefined4 in_r53;
  undefined4 uVar5;
  
  *(short *)(in_r12 + 4) = (short)unaff_r13;
  FUN_ram_bfd1583c();
  iVar3 = unaff_r13 * 4;
  uVar5 = asm_instruction_08(0x1f,in_r53,0x7b4);
  uVar4 = asm_instruction_08(0x23,unaff_r25,0x43f);
  asm_instruction_06(0x23,unaff_r16,0x3f);
  do {
  } while (iVar3 == 0);
  if (unaff_r14 == 0) {
    cVar1 = ext_condition(0x10);
    if (cVar1 == '\0') {
      uVar2 = *(undefined1 *)(unaff_r15 + 4);
      uVar5 = asm_instruction_08(0x1f,uVar5,0xfffffbb4);
      *(short *)(in_r12 + 4) = (short)iVar3;
      FUN_ram_bfd15864(uVar2,iVar3 + -6);
      asm_instruction_08(0x1f,uVar5,0xfffff934);
      asm_instruction_08(0x22,uVar4,0x4bf);
      SUB_ram_00000009 = FUN_ram_bfd14a20();
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd15a18(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  char in_N;
  char in_V;
  
  if (in_V != in_N) {
    param_1 = func_0xbfc31c4c();
  }
  cVar1 = ext_condition(0x13);
  uVar2 = asm_instruction_08(0x23,param_1,param_1);
  if (cVar1 != '\0') {
    func_0xbfde8e5c(uVar2);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd15a88(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  undefined2 in_r12;
  undefined2 unaff_r15;
  undefined4 in_r37;
  bool in_Z;
  char in_N;
  char in_V;
  
  if (in_Z || in_V != in_N) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (param_2 == 0) {
    asm_instruction_06(0x1c,param_5,0x16);
    asm_instruction_05(0x21,in_r37,param_4);
    *(undefined2 *)(param_1 + 0x22) = unaff_r15;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  *(undefined2 *)(param_3 + 0x22) = in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd15aba(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                     undefined4 param_5)

{
  undefined1 in_r9;
  undefined2 in_r12;
  int unaff_r14;
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r37;
  int in_r48;
  
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  *(undefined1 *)(in_r48 + -0x9e) = in_r9;
  asm_instruction_08(0x3f,in_r37,0xfffffd7f);
  asm_instruction_06(0x1c,param_5,0x712);
  asm_instruction_08(0x24,(uint)*(byte *)(unaff_gp + -0x1b),(uint)*(byte *)(unaff_gp + -0x1b));
  *(undefined2 *)(param_3 + 0x22) = in_r12;
  if (unaff_r14 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd15af4(undefined4 param_1)

{
  asm_instruction_06(0x20,param_1,3);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd15c74(void)

{
  undefined2 in_r3;
  int in_r12;
  int unaff_r13;
  
  do {
  } while (unaff_r13 != 0);
  *(undefined2 *)(in_r12 + 10) = in_r3;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd15e4c(void)

{
  int in_r12;
  undefined4 unaff_r13;
  undefined4 unaff_r17;
  undefined4 unaff_r22;
  undefined4 in_r37;
  
  asm_instruction_04(0x11,in_r37,unaff_r22);
  asm_instruction_08(0x22,unaff_r17,0x3c0);
  asm_instruction_05(0x3d,unaff_r13,0x92);
  *(short *)(in_r12 + 6) = (short)in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd15fb8(void)

{
  undefined4 in_r3;
  undefined4 unaff_r15;
  
  asm_instruction_04(0x31,unaff_r15,0x23);
  FUN_ram_bfd15fb8();
  asm_instruction_05(0x10,in_r3,0x2e);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfd160ce) overlaps instruction at (ram,0xbfd160cc)
    */
/* WARNING: Removing unreachable block (ram,0xbfd160cc) */
/* WARNING: Removing unreachable block (ram,0xbfd3d10c) */
/* WARNING: Removing unreachable block (ram,0xbfd160d0) */
/* WARNING: Removing unreachable block (ram,0xbfd160d4) */
/* WARNING: Removing unreachable block (ram,0xbfd39910) */

void FUN_ram_bfd1613c(undefined4 param_1,undefined4 param_2)

{
  undefined4 extraout_r1;
  undefined4 in_r6;
  int iVar1;
  int unaff_r14;
  undefined4 in_mmid;
  
  if (unaff_r14 == 0) {
    iVar1 = asm_instruction_05(0x18,in_r6,in_mmid);
    if (-1 < iVar1) {
      func_0xbfd76d80();
      param_2 = extraout_r1;
    }
    asm_instruction_05(0x37,param_2,param_2);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  func_0xbfd170c0();
  FUN_ram_bfd16d88();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd16228(void)

{
  int unaff_r14;
  
  if (unaff_r14 != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd16270(void)

{
  undefined4 unaff_r25;
  int unaff_gp;
  undefined4 in_r48;
  
  FUN_ram_bfd162e0(*(undefined1 *)(unaff_gp + -0x1b));
  asm_instruction_08(0x23,unaff_r25,0x4bf);
  asm_instruction_07(3,in_r48,0x39);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd162e0(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  int unaff_r13;
  undefined4 unaff_r16;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined2 unaff_r18;
  undefined4 unaff_r20;
  
  *(int *)(param_1 + 0x3c) = param_1;
  puVar3 = (undefined4 *)asm_instruction_06(0x22,unaff_r16,0x14);
  iVar1 = FUN_ram_bfd164d4();
  puVar2 = (undefined2 *)(iVar1 + -0xe4);
  *puVar2 = unaff_r18;
  do {
    puVar4 = puVar3;
    *puVar4 = unaff_r20;
    puVar3 = (undefined4 *)((int)puVar4 + 2);
  } while (unaff_r13 != 0);
  puVar4[0x19] = unaff_r20;
  asm_instruction_08(0x3f,0,0x711);
  asm_instruction_08(0x22,puVar2,puVar2);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd16360(void)

{
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd164d4(undefined1 param_1,undefined4 param_2)

{
  int extraout_r1;
  undefined1 in_r12;
  int unaff_r13;
  int unaff_r14;
  undefined4 unaff_r25;
  undefined4 in_r37;
  
  *(undefined1 *)(unaff_r13 + 10) = param_1;
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  func_0xbfd155e4(param_1,param_2,param_2);
  if (unaff_r14 == 0) {
    asm_instruction_05(0x21,in_r37,param_2);
    *(undefined1 *)(extraout_r1 + 0x18) = in_r12;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */

void FUN_ram_bfd1662c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  int in_r12;
  undefined4 unaff_r13;
  undefined4 unaff_r25;
  undefined4 in_r56;
  
  asm_instruction_08(0x22,unaff_r25,0x4bf);
  asm_instruction_06(2,in_r56,0xb);
  asm_instruction_06(0x22,param_1,0);
  *(undefined2 *)(in_r12 + 4) = param_4;
  FUN_ram_bfd1662c(param_1,unaff_r13);
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
  halt_unimplemented();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd16760(void)

{
  int unaff_r13;
  undefined4 unaff_r17;
  
  if (unaff_r13 == 0) {
    asm_instruction_08(0x22,unaff_r17,0);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd167bc(undefined4 param_1,undefined1 *param_2,undefined4 param_3,int param_4)

{
  undefined1 uVar1;
  undefined2 in_r8;
  undefined4 in_r9;
  undefined4 unaff_r25;
  undefined4 uVar2;
  undefined4 in_blink;
  int in_r48;
  undefined4 in_r53;
  bool in_Z;
  
  if (in_Z) {
    asm_instruction_07(0x3d,in_blink,0x47f);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (in_Z != false) {
    uVar1 = *param_2;
    asm_instruction_08(0x3f,in_r53,0x74);
    uVar2 = asm_instruction_08(0x23,unaff_r25,0x4bf);
    *(undefined2 *)(in_r48 + -0xbd) = in_r8;
    asm_instruction_08(0x23,uVar2,0x4bf);
    *(undefined1 *)(param_4 + 0x1d) = uVar1;
    *(undefined4 *)(in_r48 + -0xbd) = in_r9;
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
    halt_unimplemented();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd16900(void)

{
  int unaff_r14;
  undefined4 in_r61reserved;
  undefined1 in_Z;
  char in_N;
  char in_V;
  
  FUN_ram_bfd15a88();
  do {
  } while (unaff_r14 == 0);
  if (!(bool)in_Z && in_V == in_N) {
    asm_instruction_08(0x1f,in_r61reserved,0xfffff8a1);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */

void FUN_ram_bfd169e4(int param_1)

{
  bool in_Z;
  
  *(int *)(param_1 + 0x20) = param_1;
  if (!in_Z) {
    func_0xbfd99e84();
  }
  FUN_ram_bfd15b74();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0xbfcf0fe6) overlaps instruction at (ram,0xbfcf0fe4)
    */
/* WARNING: Removing unreachable block (ram,0xbfcf0fb2) */
/* WARNING: Removing unreachable block (ram,0xbfcf0faa) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_bfd16d88(undefined4 param_1,int param_2,undefined4 param_3,int param_4,
                     undefined4 param_5)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  ushort *puVar4;
  int in_r12;
  int unaff_r13;
  int iVar5;
  int unaff_r14;
  undefined1 *unaff_r16;
  int unaff_r20;
  int unaff_r25;
  int unaff_gp;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  undefined1 *puVar33;
  undefined4 in_ilink1;
  undefined4 in_ilink2;
  undefined4 uVar34;
  int in_r48;
  undefined4 in_lp_count;
  undefined4 in_r61reserved;
  undefined1 in_Z;
  undefined1 uVar35;
  undefined1 in_N;
  undefined1 in_V;
  undefined8 uVar36;
  
  while( true ) {
    uVar36 = CONCAT44(param_2,param_1);
    if (!(bool)in_V) {
      uVar36 = func_0xbfcc6a2c();
    }
    param_1 = (undefined4)uVar36;
    if (unaff_r14 != 0) break;
    *(undefined4 *)(in_r48 + -0x3f8) = in_lp_count;
    unaff_r25 = asm_instruction_08(0x22,unaff_r25,0x4bf);
    in_Z = unaff_r25 == 0;
    in_N = unaff_r25 < 0;
    unaff_r13 = asm_instruction_08(0x1f,unaff_r13,0xa0);
    param_2 = (int)((ulonglong)uVar36 >> 0x20) + 0x2c;
  }
  if (unaff_r14 == 0) {
    asm_instruction_08(0x1f,*(undefined4 *)(in_r12 + 0x30),0x720);
    uVar34 = *(undefined4 *)(in_r12 + 0x30);
    cVar1 = ext_condition(0x1f);
    if (cVar1 != '\0') {
      uVar36 = func_0xbfda2200();
    }
    *(int *)uVar36 = (int)unaff_r16;
    asm_instruction_08(0x1f,uVar34,0x720);
    puVar4 = *(ushort **)(param_4 + 0x50);
    asm_instruction_08(0x1f,in_r61reserved,0x720);
    uVar3 = (uint)*puVar4;
    if (!(bool)in_V) {
      uVar3 = func_0xbfcc6a18(uVar3,(int)((ulonglong)uVar36 >> 0x20),uRam00000018);
    }
    if (!(bool)in_V) {
      uVar3 = func_0xbfcc6a1c();
    }
    uVar34 = asm_instruction_05(0x27,uVar3,0x32);
    if (!(bool)in_V) {
      func_0xbfcc6a24(uVar34);
    }
    puVar4[3] = (ushort)_DAT_ram_bfd171c8;
    cVar1 = ext_condition(0x1f);
    if (cVar1 != '\0') {
      func_0xbfda2230();
    }
    func_0xbfd17274();
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  cVar1 = ext_condition(0x10);
  if (cVar1 != '\0') {
    param_1 = func_0xbfcf3234();
  }
  sVar2 = *(short *)(unaff_r14 + 0x2c);
  if (!(bool)in_V) {
    func_0xbfcc6a3c(param_1,*(undefined1 *)((int)sVar2 + 4));
  }
  uVar34 = 0xbfd16da6;
  uVar36 = FUN_ram_bfd15fb4();
  uVar3 = (uint)uVar36;
  if (!(bool)in_Z) {
    iVar5 = asm_instruction_08(0x1f,unaff_r13,0x721);
    asm_instruction_08(0x1f,in_ilink1,0x721);
    if (iVar5 != 0) {
      asm_instruction_08(0x1f,iVar5,0x721);
      *(undefined4 *)(in_r12 + 0x40) = _DAT_ram_bfd17160;
      *(char *)((int)((ulonglong)uVar36 >> 0x20) + 0x18) = (char)unaff_r14;
      if (!(bool)in_V) {
        func_0xbfcc69c8();
      }
      if (!(bool)in_V) {
        func_0xbfcc69d0();
      }
      if (!(bool)in_V) {
        func_0xbfcc69d4();
      }
      cVar1 = ext_condition(0x1f);
      if (cVar1 != '\0') {
        func_0xbfda21dc();
      }
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (!(bool)in_N && !(bool)in_Z) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e18);
  if (0 < iVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar6 = asm_instruction_08(0x35,&stack0x00000000,0xbfcf0e20);
  if (0 < iVar6) {
    halt_baddata();
  }
  iVar7 = asm_instruction_08(0x35,iVar6,0xbfcf0e28);
  if (0 < iVar7) {
    halt_baddata();
  }
  iVar8 = asm_instruction_08(0x35,iVar7,0xbfcf0e30);
  if (0 < iVar8) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e38);
  if (0 < iVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e48);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar9 = asm_instruction_08(0x35,iVar8,0xbfcf0e50);
  if (0 < iVar9) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar10 = asm_instruction_08(0x35,iVar9,0xbfcf0e58);
  if (((0 < iVar10) || (iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e60), 0 < iVar5)) ||
     (iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e68), 0 < iVar5)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar11 = asm_instruction_08(0x35,iVar10,0xbfcf0e70);
  if (0 < iVar11) {
    halt_baddata();
  }
  iVar12 = asm_instruction_08(0x35,iVar11,0xbfcf0e78);
  if (0 < iVar12) {
    halt_baddata();
  }
  iVar13 = asm_instruction_08(0x35,iVar12,0xbfcf0e80);
  if (0 < iVar13) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e88);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e90);
  if (0 < iVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0e98);
  if (0 < iVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ea0);
  if ((0 < iVar5) || (iVar14 = asm_instruction_08(0x35,iVar13,0xbfcf0ea8), 0 < iVar14)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar15 = asm_instruction_08(0x35,iVar14,0xbfcf0eb0);
  if (0 < iVar15) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar16 = asm_instruction_08(0x35,iVar15,0xbfcf0eb8);
  if (0 < iVar16) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0ec0);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar17 = asm_instruction_08(0x35,iVar16,0xbfcf0ec8);
  if (0 < iVar17) {
    halt_baddata();
  }
  iVar18 = asm_instruction_08(0x35,iVar17,0xbfcf0ed0);
  if (0 < iVar18) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar19 = asm_instruction_08(0x35,iVar18,0xbfcf0ed8);
  if (0 < iVar19) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar20 = asm_instruction_08(0x35,iVar19,0xbfcf0ee0);
  if ((0 < iVar20) || (iVar21 = asm_instruction_08(0x35,iVar20,0xbfcf0ee8), 0 < iVar21)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar22 = asm_instruction_08(0x35,iVar21,0xbfcf0ef0);
  if (0 < iVar22) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar23 = asm_instruction_08(0x35,iVar22,0xbfcf0ef8);
  if (0 < iVar23) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f00);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f08);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f10);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f18);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar24 = asm_instruction_08(0x35,iVar23,0xbfcf0f20);
  if (0 < iVar24) {
    halt_baddata();
  }
  iVar25 = asm_instruction_08(0x35,iVar24,0xbfcf0f28);
  if (0 < iVar25) {
    halt_baddata();
  }
  iVar26 = asm_instruction_08(0x35,iVar25,0xbfcf0f30);
  if (0 < iVar26) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f38);
  if (0 < iVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f40);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f48);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f50);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f58);
  if (0 < iVar5) {
    halt_baddata();
  }
  iVar27 = asm_instruction_08(0x35,iVar26,0xbfcf0f60);
  if (0 < iVar27) {
    halt_baddata();
  }
  iVar28 = asm_instruction_08(0x35,iVar27,0xbfcf0f68);
  if (0 < iVar28) {
    halt_baddata();
  }
  iVar29 = asm_instruction_08(0x35,iVar28,0xbfcf0f70);
  if (0 < iVar29) {
    halt_baddata();
  }
  iVar30 = asm_instruction_08(0x35,iVar29,0xbfcf0f78);
  if (0 < iVar30) {
    halt_baddata();
  }
  iVar31 = asm_instruction_08(0x35,iVar30,0xbfcf0f80);
  if (0 < iVar31) {
    halt_baddata();
  }
  iVar32 = asm_instruction_08(0x35,iVar31,0xbfcf0f88);
  if (0 < iVar32) {
    halt_baddata();
  }
  puVar33 = (undefined1 *)asm_instruction_08(0x35,iVar32,0xbfcf0f90);
  if (0 < (int)puVar33) {
    halt_baddata();
  }
  iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0f98);
  if (0 < iVar5) {
    halt_baddata();
  }
  do {
    puVar33 = (undefined1 *)asm_instruction_08(0x35,puVar33,0xbfcf0fa0);
    if (0 < (int)puVar33) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar5 = asm_instruction_08(0x2b,in_ilink1,0xbfcf0fa8);
    if (0 < iVar5) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar5 = asm_instruction_05(0x1b,uVar34,0xbfcf0fb0);
    uVar35 = iVar5 < 0;
    if (0 < iVar5) {
      halt_baddata();
    }
  } while (((int)sVar2 & 0x1ffffU) != 0);
  if (in_V != uVar35) {
    if ((bool)uVar35) {
      func_0xbfccd3bc(uVar3,0xbb);
    }
LAB_ram_bfcf1fc2:
    *(short *)(in_r12 + 4) = (short)param_4;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  cVar1 = ext_condition(0x1b);
  if (cVar1 != '\0') {
    if (unaff_r13 != 0) {
      *unaff_r16 = (char)unaff_r20;
      if (unaff_r13 != 0) {
        *(short *)(unaff_r16 + 0x50) = (short)unaff_r20;
        uVar3 = (uint)*(ushort *)(unaff_gp + 0x154);
        cVar1 = ext_condition(0x10);
        if (cVar1 != '\0') {
          uVar3 = func_0xbfd1b3d4(uVar3);
        }
        asm_instruction_06(0x20,uVar3,3);
        *(short *)(in_r12 + 8) = (short)param_4;
        FUN_ram_bfd09fe4();
        return;
      }
      asm_instruction_05(0xd,in_ilink2,1);
      uVar34 = asm_instruction_08(0x12,uVar3,uVar3);
      asm_instruction_08(0x10,uVar34,uVar34);
      if ((bool)in_V == false) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if ((bool)in_V == false) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      asm_instruction_07(0x1a,in_r12,unaff_r20 + 0x90);
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    goto LAB_ram_bfcf1fc2;
  }
  cVar1 = ext_condition(0x15);
  if (cVar1 == '\0') {
    cVar1 = ext_condition(0x16);
    if (cVar1 == '\0') {
      cVar1 = ext_condition(0x17);
      if (cVar1 == '\0') {
        if (((bool)in_V == false) && (cVar1 = ext_condition(0x15), cVar1 != '\0')) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        if (iVar5 == 0) {
          *(short *)(in_r12 + 0xc) = (short)unaff_r13;
          asm_instruction_08(0x23,unaff_r25,0x47f);
          FUN_ram_bfd0affa();
          return;
        }
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      goto LAB_ram_bfcf27de;
    }
    *(short *)(param_4 + 2) = (short)in_r12;
  }
  else {
    asm_instruction_07(0x1d,param_5,in_r48);
    uVar3 = (uint)*(ushort *)(unaff_gp + -0xb4);
    *(short *)(param_4 + 2) = (short)in_r12;
    if (!(bool)in_V) {
      uVar3 = func_0xbfde23d4(uVar3);
    }
  }
  cVar1 = ext_condition(0x1d);
  if (cVar1 != '\0') {
    uVar3 = func_0xbfd22bd8();
  }
LAB_ram_bfcf27de:
  asm_instruction_06(0x3c,uVar3,0x16);
  if ((bool)uVar35) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


