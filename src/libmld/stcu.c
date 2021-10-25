#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libmld.h"

#if 0
__asm__(R""(
.macro glabel label
    .global \label
    .balign 4
    \label:
.endm

.rdata
RO_1000EA20:
    # 00488434 st_extstradd
    .asciz "st_extstradd: you didn't initialize with cuinit or readst\n"

RO_1000EA5C:
    # 00488434 st_extstradd
    .asciz "st_extstradd: argument is nil\n"

RO_1000EA7C:
    # 00488590 st_idn_dn
    .asciz "st_idn_dn: you didn't initialize with cuinit or readst\n"

RO_1000EAB4:
    # 004886A8 st_idn_rndx
    .asciz "st_idn_rndx: you didn't initialize with cuinit or readst\n"

RO_1000EAF0:
    # 004887CC st_rndx_idn
    .asciz "st_rndx_idn: idn (%d) greater than max (%d)\n"

RO_1000EB20:
    # 004887CC st_rndx_idn
    .asciz "st_rndx_idn: old interface can't put rfd(%d) into rndx, use st_pdn_idn instead\n"

RO_1000EB70:
    # 004888DC st_setidn
    .asciz "st_setidn: idnsrc (%d) or idndest (%d) out of range\n"

RO_1000EBA8:
    # 00488984 st_pext_dn
    .asciz "st_pext_dn: rfd field (%d) isn't equal to ST_EXTIFD(%d)\n"

RO_1000EBE4:
    # 00488984 st_pext_dn
    .asciz "st_pext_dn: index out of range (%d)\n"

RO_1000EC0C:
    # 10011940
    .asciz "libmld"

.data
# 10011940
glabel st_errname
    # 00488A48 st_setmsgname
    # 00488AF0 st_error
    # 0048A430 _md_st_internal
    # 0048A4EC _md_st_error
    # 0048AD70 st_internal
    # 00491FD0 st_warning
    .word RO_1000EC0C
    .type st_errname, @object
    .size st_errname, .-st_errname # 4




.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

.text
)"");
#endif

char *st_errname = "libmld";

void st_setchdr(CHDRR *pchdr) {
    st_pchdr = pchdr;
}

/*
0040BCA0 path_blockno
0048C56C st_file_idn
*/
CHDRR *st_currentpchdr(void) {
    return st_pchdr;
}

#define NULLp1 ((void*)1)
#define NULLn1 ((void*)-1)
/*
0042EB10 incorp_feedback
*/
void st_free(void) {
    if (st_pchdr != NULL) {
        if (st_pchdr->pdn != NULL && st_pchdr->pdn != NULLn1 && st_pchdr->pdn != NULLp1) {
            free(st_pchdr->pdn);
        }
        if (st_pchdr->pext != NULL && st_pchdr->pext != NULLn1 && st_pchdr->pext != NULLp1) {
            free(st_pchdr->pext);
        }
        if (st_pchdr->pssext != NULL && st_pchdr->pssext != NULLn1 && st_pchdr->pssext != NULLp1) {
            free(st_pchdr->pssext);
        }
        if (st_pchdr->pfd != NULL && st_pchdr->pfd != NULLn1 && st_pchdr->pfd != NULLp1) {
            free(st_pchdr->pfd);
        }
        if (st_pchdr->pcfd != NULL && st_pchdr->pcfd != NULLn1 && st_pchdr->pcfd != NULLp1) {
            free(st_pchdr->pcfd);
        }
        if (st_pchdr->psym != NULL && st_pchdr->psym != NULLn1 && st_pchdr->psym != NULLp1) {
            free(st_pchdr->psym);
        }
        if (st_pchdr->paux != NULL && st_pchdr->paux != NULLn1 && st_pchdr->paux != NULLp1) {
            free(st_pchdr->paux);
        }
        if (st_pchdr->popt != NULL && st_pchdr->popt != NULLn1 && st_pchdr->popt != NULLp1) {
            free(st_pchdr->popt);
        }
        if (st_pchdr->ppd != NULL && st_pchdr->ppd != NULLn1 && st_pchdr->ppd != NULLp1) {
            free(st_pchdr->ppd);
        }
        if (st_pchdr->pline != NULL && st_pchdr->pline != NULLn1 && st_pchdr->pline != NULLp1) {
            free(st_pchdr->pline);
        }
        if (st_pchdr->pss != NULL && st_pchdr->pss != NULLn1 && st_pchdr->pss != NULLp1) {
            free(st_pchdr->pss);
        }
        if (st_pchdr->prfd != NULL && st_pchdr->prfd != NULLn1 && st_pchdr->prfd != NULLp1) {
            free(st_pchdr->prfd);
        }
        bzero(st_pchdr, 0x60);
    }
}

#if 0
__asm__(R""(
.set noat
.set noreorder

glabel st_extstradd
    .ent st_extstradd
/* 00488434 3C1C0FB9 */  .cpload $t9
/* 00488438 279C1E5C */  
/* 0048843C 0399E021 */  
/* 00488440 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 00488444 AFB10018 */  sw    $s1, 0x18($sp)
/* 00488448 8F918CB8 */  lw     $s1, %got(st_pchdr)($gp)
/* 0048844C AFBF0024 */  sw    $ra, 0x24($sp)
/* 00488450 AFBC0020 */  sw    $gp, 0x20($sp)
/* 00488454 8E2E0000 */  lw    $t6, ($s1)
/* 00488458 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0048845C AFB00014 */  sw    $s0, 0x14($sp)
/* 00488460 15C00006 */  bnez  $t6, .L0048847C
/* 00488464 AFA40028 */   sw    $a0, 0x28($sp)
/* 00488468 8F9987F0 */  lw    $t9, %call16(st_internal)($gp)
/* 0048846C 8F848044 */  lw    $a0, %got(RO_1000EA20)($gp)
/* 00488470 0320F809 */  jalr  $t9
/* 00488474 2484EA20 */   addiu $a0, %lo(RO_1000EA20) # addiu $a0, $a0, -0x15e0
/* 00488478 8FBC0020 */  lw    $gp, 0x20($sp)
.L0048847C:
/* 0048847C 8FAF0028 */  lw    $t7, 0x28($sp)
/* 00488480 15E00006 */  bnez  $t7, .L0048849C
/* 00488484 00000000 */   nop   
/* 00488488 8F998788 */  lw    $t9, %call16(st_error)($gp)
/* 0048848C 8F848044 */  lw    $a0, %got(RO_1000EA5C)($gp)
/* 00488490 0320F809 */  jalr  $t9
/* 00488494 2484EA5C */   addiu $a0, %lo(RO_1000EA5C) # addiu $a0, $a0, -0x15a4
/* 00488498 8FBC0020 */  lw    $gp, 0x20($sp)
.L0048849C:
/* 0048849C 8F9980C0 */  lw    $t9, %call16(strlen)($gp)
/* 004884A0 8FA40028 */  lw    $a0, 0x28($sp)
/* 004884A4 0320F809 */  jalr  $t9
/* 004884A8 00000000 */   nop   
/* 004884AC 8E300000 */  lw    $s0, ($s1)
/* 004884B0 8FBC0020 */  lw    $gp, 0x20($sp)
/* 004884B4 24520001 */  addiu $s2, $v0, 1
/* 004884B8 8E030028 */  lw    $v1, 0x28($s0)
/* 004884BC 8E18002C */  lw    $t8, 0x2c($s0)
/* 004884C0 0062C821 */  addu  $t9, $v1, $v0
/* 004884C4 0338082A */  slt   $at, $t9, $t8
/* 004884C8 14200011 */  bnez  $at, .L00488510
/* 004884CC 00000000 */   nop   
.L004884D0:
/* 004884D0 8F9987B0 */  lw    $t9, %call16(st_malloc)($gp)
/* 004884D4 8E040024 */  lw    $a0, 0x24($s0)
/* 004884D8 2605002C */  addiu $a1, $s0, 0x2c
/* 004884DC 24060001 */  li    $a2, 1
/* 004884E0 0320F809 */  jalr  $t9
/* 004884E4 24070200 */   li    $a3, 512
/* 004884E8 8E280000 */  lw    $t0, ($s1)
/* 004884EC 8FBC0020 */  lw    $gp, 0x20($sp)
/* 004884F0 AD020024 */  sw    $v0, 0x24($t0)
/* 004884F4 8E300000 */  lw    $s0, ($s1)
/* 004884F8 8E030028 */  lw    $v1, 0x28($s0)
/* 004884FC 8E09002C */  lw    $t1, 0x2c($s0)
/* 00488500 00725021 */  addu  $t2, $v1, $s2
/* 00488504 012A082A */  slt   $at, $t1, $t2
/* 00488508 1420FFF1 */  bnez  $at, .L004884D0
/* 0048850C 00000000 */   nop   
.L00488510:
/* 00488510 8F9980C4 */  lw    $t9, %call16(strcpy)($gp)
/* 00488514 8E0B0024 */  lw    $t3, 0x24($s0)
/* 00488518 8FA50028 */  lw    $a1, 0x28($sp)
/* 0048851C 0320F809 */  jalr  $t9
/* 00488520 01632021 */   addu  $a0, $t3, $v1
/* 00488524 8E300000 */  lw    $s0, ($s1)
/* 00488528 8FBC0020 */  lw    $gp, 0x20($sp)
/* 0048852C 8E020028 */  lw    $v0, 0x28($s0)
/* 00488530 00526021 */  addu  $t4, $v0, $s2
/* 00488534 AE0C0028 */  sw    $t4, 0x28($s0)
/* 00488538 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0048853C 8FB2001C */  lw    $s2, 0x1c($sp)
/* 00488540 8FB10018 */  lw    $s1, 0x18($sp)
/* 00488544 8FB00014 */  lw    $s0, 0x14($sp)
/* 00488548 03E00008 */  jr    $ra
/* 0048854C 27BD0028 */   addiu $sp, $sp, 0x28
    .type st_extstradd, @function
    .size st_extstradd, .-st_extstradd
    .end st_extstradd

glabel st_str_extiss
    .ent st_str_extiss
    # 0048BC7C st_procbegin
/* 00488550 3C1C0FB9 */  .cpload $t9
/* 00488554 279C1D40 */  
/* 00488558 0399E021 */  
/* 0048855C 0480000A */  bltz  $a0, .L00488588
/* 00488560 00001025 */   move  $v0, $zero
/* 00488564 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 00488568 8C630000 */  lw    $v1, ($v1)
/* 0048856C 8C6E0028 */  lw    $t6, 0x28($v1)
/* 00488570 008E082A */  slt   $at, $a0, $t6
/* 00488574 10200004 */  beqz  $at, .L00488588
/* 00488578 00000000 */   nop   
/* 0048857C 8C6F0024 */  lw    $t7, 0x24($v1)
/* 00488580 03E00008 */  jr    $ra
/* 00488584 01E41021 */   addu  $v0, $t7, $a0

.L00488588:
/* 00488588 03E00008 */  jr    $ra
/* 0048858C 00000000 */   nop   
    .type st_str_extiss, @function
    .size st_str_extiss, .-st_str_extiss
    .end st_str_extiss

glabel st_idn_dn
    .ent st_idn_dn
    # 0048B2F0 st_fileend
    # 0048B490 st_textblock
    # 0048B590 _sgi_st_blockbegin
    # 0048B6E8 st_blockbegin
/* 00488590 3C1C0FB9 */  .cpload $t9
/* 00488594 279C1D00 */  
/* 00488598 0399E021 */  
/* 0048859C 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 004885A0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 004885A4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 004885A8 8C630000 */  lw    $v1, ($v1)
/* 004885AC AFBC0018 */  sw    $gp, 0x18($sp)
/* 004885B0 AFA40028 */  sw    $a0, 0x28($sp)
/* 004885B4 14600008 */  bnez  $v1, .L004885D8
/* 004885B8 AFA5002C */   sw    $a1, 0x2c($sp)
/* 004885BC 8F9987F0 */  lw    $t9, %call16(st_internal)($gp)
/* 004885C0 8F848044 */  lw    $a0, %got(RO_1000EA7C)($gp)
/* 004885C4 0320F809 */  jalr  $t9
/* 004885C8 2484EA7C */   addiu $a0, %lo(RO_1000EA7C) # addiu $a0, $a0, -0x1584
/* 004885CC 8FBC0018 */  lw    $gp, 0x18($sp)
/* 004885D0 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 004885D4 8C630000 */  lw    $v1, ($v1)
.L004885D8:
/* 004885D8 8C620040 */  lw    $v0, 0x40($v1)
/* 004885DC 8C6E003C */  lw    $t6, 0x3c($v1)
/* 004885E0 24650040 */  addiu $a1, $v1, 0x40
/* 004885E4 24060008 */  li    $a2, 8
/* 004885E8 01C2082A */  slt   $at, $t6, $v0
/* 004885EC 1420000D */  bnez  $at, .L00488624
/* 004885F0 00404025 */   move  $t0, $v0
/* 004885F4 8F9987B0 */  lw    $t9, %call16(st_malloc)($gp)
/* 004885F8 8C640038 */  lw    $a0, 0x38($v1)
/* 004885FC AFA20024 */  sw    $v0, 0x24($sp)
/* 00488600 0320F809 */  jalr  $t9
/* 00488604 24070080 */   li    $a3, 128
/* 00488608 8FBC0018 */  lw    $gp, 0x18($sp)
/* 0048860C 8FA80024 */  lw    $t0, 0x24($sp)
/* 00488610 8F8F8CB8 */  lw     $t7, %got(st_pchdr)($gp)
/* 00488614 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 00488618 8DEF0000 */  lw    $t7, ($t7)
/* 0048861C ADE20038 */  sw    $v0, 0x38($t7)
/* 00488620 8C630000 */  lw    $v1, ($v1)
.L00488624:
/* 00488624 5500000A */  bnezl $t0, .L00488650
/* 00488628 8C69003C */   lw    $t1, 0x3c($v1)
/* 0048862C 8F9980BC */  lw    $t9, %call16(bzero)($gp)
/* 00488630 8C640038 */  lw    $a0, 0x38($v1)
/* 00488634 24050010 */  li    $a1, 16
/* 00488638 0320F809 */  jalr  $t9
/* 0048863C 00000000 */   nop   
/* 00488640 8FBC0018 */  lw    $gp, 0x18($sp)
/* 00488644 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 00488648 8C630000 */  lw    $v1, ($v1)
/* 0048864C 8C69003C */  lw    $t1, 0x3c($v1)
.L00488650:
/* 00488650 8C790038 */  lw    $t9, 0x38($v1)
/* 00488654 8FB80028 */  lw    $t8, 0x28($sp)
/* 00488658 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 0048865C 000950C0 */  sll   $t2, $t1, 3
/* 00488660 032A5821 */  addu  $t3, $t9, $t2
/* 00488664 AD780000 */  sw    $t8, ($t3)
/* 00488668 8C630000 */  lw    $v1, ($v1)
/* 0048866C 8FAC002C */  lw    $t4, 0x2c($sp)
/* 00488670 8C6E003C */  lw    $t6, 0x3c($v1)
/* 00488674 8C6D0038 */  lw    $t5, 0x38($v1)
/* 00488678 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 0048867C 000E78C0 */  sll   $t7, $t6, 3
/* 00488680 01AF4821 */  addu  $t1, $t5, $t7
/* 00488684 AD2C0004 */  sw    $t4, 4($t1)
/* 00488688 8C630000 */  lw    $v1, ($v1)
/* 0048868C 8C62003C */  lw    $v0, 0x3c($v1)
/* 00488690 24590001 */  addiu $t9, $v0, 1
/* 00488694 AC79003C */  sw    $t9, 0x3c($v1)
/* 00488698 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0048869C 27BD0028 */  addiu $sp, $sp, 0x28
/* 004886A0 03E00008 */  jr    $ra
/* 004886A4 00000000 */   nop   
    .type st_idn_dn, @function
    .size st_idn_dn, .-st_idn_dn
    .end st_idn_dn

glabel st_idn_rndx
    .ent st_idn_rndx
/* 004886A8 3C1C0FB9 */  .cpload $t9
/* 004886AC 279C1BE8 */  
/* 004886B0 0399E021 */  
/* 004886B4 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 004886B8 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 004886BC AFBF001C */  sw    $ra, 0x1c($sp)
/* 004886C0 8C630000 */  lw    $v1, ($v1)
/* 004886C4 AFBC0018 */  sw    $gp, 0x18($sp)
/* 004886C8 AFA40028 */  sw    $a0, 0x28($sp)
/* 004886CC 54600009 */  bnezl $v1, .L004886F4
/* 004886D0 8C620040 */   lw    $v0, 0x40($v1)
/* 004886D4 8F9987F0 */  lw    $t9, %call16(st_internal)($gp)
/* 004886D8 8F848044 */  lw    $a0, %got(RO_1000EAB4)($gp)
/* 004886DC 0320F809 */  jalr  $t9
/* 004886E0 2484EAB4 */   addiu $a0, %lo(RO_1000EAB4) # addiu $a0, $a0, -0x154c
/* 004886E4 8FBC0018 */  lw    $gp, 0x18($sp)
/* 004886E8 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 004886EC 8C630000 */  lw    $v1, ($v1)
/* 004886F0 8C620040 */  lw    $v0, 0x40($v1)
.L004886F4:
/* 004886F4 8C6E003C */  lw    $t6, 0x3c($v1)
/* 004886F8 24650040 */  addiu $a1, $v1, 0x40
/* 004886FC 24060008 */  li    $a2, 8
/* 00488700 01C2082A */  slt   $at, $t6, $v0
/* 00488704 1420000D */  bnez  $at, .L0048873C
/* 00488708 00404025 */   move  $t0, $v0
/* 0048870C 8F9987B0 */  lw    $t9, %call16(st_malloc)($gp)
/* 00488710 8C640038 */  lw    $a0, 0x38($v1)
/* 00488714 AFA20024 */  sw    $v0, 0x24($sp)
/* 00488718 0320F809 */  jalr  $t9
/* 0048871C 24070080 */   li    $a3, 128
/* 00488720 8FBC0018 */  lw    $gp, 0x18($sp)
/* 00488724 8FA80024 */  lw    $t0, 0x24($sp)
/* 00488728 8F8F8CB8 */  lw     $t7, %got(st_pchdr)($gp)
/* 0048872C 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 00488730 8DEF0000 */  lw    $t7, ($t7)
/* 00488734 ADE20038 */  sw    $v0, 0x38($t7)
/* 00488738 8C630000 */  lw    $v1, ($v1)
.L0048873C:
/* 0048873C 5500000A */  bnezl $t0, .L00488768
/* 00488740 8C69003C */   lw    $t1, 0x3c($v1)
/* 00488744 8F9980BC */  lw    $t9, %call16(bzero)($gp)
/* 00488748 8C640038 */  lw    $a0, 0x38($v1)
/* 0048874C 24050010 */  li    $a1, 16
/* 00488750 0320F809 */  jalr  $t9
/* 00488754 00000000 */   nop   
/* 00488758 8FBC0018 */  lw    $gp, 0x18($sp)
/* 0048875C 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 00488760 8C630000 */  lw    $v1, ($v1)
/* 00488764 8C69003C */  lw    $t1, 0x3c($v1)
.L00488768:
/* 00488768 8FA60028 */  lw    $a2, 0x28($sp)
/* 0048876C 8C790038 */  lw    $t9, 0x38($v1)
/* 00488770 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 00488774 000950C0 */  sll   $t2, $t1, 3
/* 00488778 0006C502 */  srl   $t8, $a2, 0x14
/* 0048877C 032A5821 */  addu  $t3, $t9, $t2
/* 00488780 AD780000 */  sw    $t8, ($t3)
/* 00488784 8C630000 */  lw    $v1, ($v1)
/* 00488788 3C01000F */  lui   $at, 0xf
/* 0048878C 3421FFFF */  ori   $at, $at, 0xffff
/* 00488790 8C6E003C */  lw    $t6, 0x3c($v1)
/* 00488794 8C6D0038 */  lw    $t5, 0x38($v1)
/* 00488798 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 0048879C 000E78C0 */  sll   $t7, $t6, 3
/* 004887A0 00C16024 */  and   $t4, $a2, $at
/* 004887A4 01AF4821 */  addu  $t1, $t5, $t7
/* 004887A8 AD2C0004 */  sw    $t4, 4($t1)
/* 004887AC 8C630000 */  lw    $v1, ($v1)
/* 004887B0 8C62003C */  lw    $v0, 0x3c($v1)
/* 004887B4 24590001 */  addiu $t9, $v0, 1
/* 004887B8 AC79003C */  sw    $t9, 0x3c($v1)
/* 004887BC 8FBF001C */  lw    $ra, 0x1c($sp)
/* 004887C0 27BD0028 */  addiu $sp, $sp, 0x28
/* 004887C4 03E00008 */  jr    $ra
/* 004887C8 00000000 */   nop   
    .type st_idn_rndx, @function
    .size st_idn_rndx, .-st_idn_rndx
    .end st_idn_rndx

glabel st_rndx_idn
    .ent st_rndx_idn
/* 004887CC 3C1C0FB9 */  .cpload $t9
/* 004887D0 279C1AC4 */  
/* 004887D4 0399E021 */  
/* 004887D8 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 004887DC 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 004887E0 AFBF001C */  sw    $ra, 0x1c($sp)
/* 004887E4 8C630000 */  lw    $v1, ($v1)
/* 004887E8 AFBC0018 */  sw    $gp, 0x18($sp)
/* 004887EC AFA40030 */  sw    $a0, 0x30($sp)
/* 004887F0 8C66003C */  lw    $a2, 0x3c($v1)
/* 004887F4 00A03825 */  move  $a3, $a1
/* 004887F8 00A6082A */  slt   $at, $a1, $a2
/* 004887FC 5420000B */  bnezl $at, .L0048882C
/* 00488800 8C6E0038 */   lw    $t6, 0x38($v1)
/* 00488804 8F9987F0 */  lw    $t9, %call16(st_internal)($gp)
/* 00488808 8F848044 */  lw    $a0, %got(RO_1000EAF0)($gp)
/* 0048880C AFA70034 */  sw    $a3, 0x34($sp)
/* 00488810 0320F809 */  jalr  $t9
/* 00488814 2484EAF0 */   addiu $a0, %lo(RO_1000EAF0) # addiu $a0, $a0, -0x1510
/* 00488818 8FBC0018 */  lw    $gp, 0x18($sp)
/* 0048881C 8FA70034 */  lw    $a3, 0x34($sp)
/* 00488820 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 00488824 8C630000 */  lw    $v1, ($v1)
/* 00488828 8C6E0038 */  lw    $t6, 0x38($v1)
.L0048882C:
/* 0048882C 000730C0 */  sll   $a2, $a3, 3
/* 00488830 01C67821 */  addu  $t7, $t6, $a2
/* 00488834 8DE50000 */  lw    $a1, ($t7)
/* 00488838 2CA10FFF */  sltiu $at, $a1, 0xfff
/* 0048883C 5420000E */  bnezl $at, .L00488878
/* 00488840 97AB002C */   lhu   $t3, 0x2c($sp)
/* 00488844 8F9987F0 */  lw    $t9, %call16(st_internal)($gp)
/* 00488848 8F848044 */  lw    $a0, %got(RO_1000EB20)($gp)
/* 0048884C AFA60024 */  sw    $a2, 0x24($sp)
/* 00488850 0320F809 */  jalr  $t9
/* 00488854 2484EB20 */   addiu $a0, %lo(RO_1000EB20) # addiu $a0, $a0, -0x14e0
/* 00488858 8FBC0018 */  lw    $gp, 0x18($sp)
/* 0048885C 8FA60024 */  lw    $a2, 0x24($sp)
/* 00488860 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 00488864 8C630000 */  lw    $v1, ($v1)
/* 00488868 8C780038 */  lw    $t8, 0x38($v1)
/* 0048886C 0306C821 */  addu  $t9, $t8, $a2
/* 00488870 8F250000 */  lw    $a1, ($t9)
/* 00488874 97AB002C */  lhu   $t3, 0x2c($sp)
.L00488878:
/* 00488878 00055100 */  sll   $t2, $a1, 4
/* 0048887C 3C01000F */  lui   $at, 0xf
/* 00488880 316C000F */  andi  $t4, $t3, 0xf
/* 00488884 014C6825 */  or    $t5, $t2, $t4
/* 00488888 A7AD002C */  sh    $t5, 0x2c($sp)
/* 0048888C 8C6E0038 */  lw    $t6, 0x38($v1)
/* 00488890 8FA8002C */  lw    $t0, 0x2c($sp)
/* 00488894 3421FFFF */  ori   $at, $at, 0xffff
/* 00488898 01C67821 */  addu  $t7, $t6, $a2
/* 0048889C 8DF80004 */  lw    $t8, 4($t7)
/* 004888A0 27AE002C */  addiu $t6, $sp, 0x2c
/* 004888A4 8FAD0030 */  lw    $t5, 0x30($sp)
/* 004888A8 0301C824 */  and   $t9, $t8, $at
/* 004888AC 03284826 */  xor   $t1, $t9, $t0
/* 004888B0 00095B00 */  sll   $t3, $t1, 0xc
/* 004888B4 000B5302 */  srl   $t2, $t3, 0xc
/* 004888B8 01486026 */  xor   $t4, $t2, $t0
/* 004888BC AFAC002C */  sw    $t4, 0x2c($sp)
/* 004888C0 8DD80000 */  lw    $t8, ($t6)
/* 004888C4 ADB80000 */  sw    $t8, ($t5)
/* 004888C8 8FBF001C */  lw    $ra, 0x1c($sp)
/* 004888CC 8FA20030 */  lw    $v0, 0x30($sp)
/* 004888D0 27BD0030 */  addiu $sp, $sp, 0x30
/* 004888D4 03E00008 */  jr    $ra
/* 004888D8 00000000 */   nop   
    .type st_rndx_idn, @function
    .size st_rndx_idn, .-st_rndx_idn
    .end st_rndx_idn

glabel st_setidn
    .ent st_setidn
    # 0048BA18 st_procend
/* 004888DC 3C1C0FB9 */  .cpload $t9
/* 004888E0 279C19B4 */  
/* 004888E4 0399E021 */  
/* 004888E8 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 004888EC AFBF001C */  sw    $ra, 0x1c($sp)
/* 004888F0 AFBC0018 */  sw    $gp, 0x18($sp)
/* 004888F4 0480000B */  bltz  $a0, .L00488924
/* 004888F8 00803025 */   move  $a2, $a0
/* 004888FC 04A00009 */  bltz  $a1, .L00488924
/* 00488900 00000000 */   nop   
/* 00488904 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 00488908 8C630000 */  lw    $v1, ($v1)
/* 0048890C 8C62003C */  lw    $v0, 0x3c($v1)
/* 00488910 0082082A */  slt   $at, $a0, $v0
/* 00488914 10200003 */  beqz  $at, .L00488924
/* 00488918 00A2082A */   slt   $at, $a1, $v0
/* 0048891C 5420000D */  bnezl $at, .L00488954
/* 00488920 8C620038 */   lw    $v0, 0x38($v1)
.L00488924:
/* 00488924 8F9987F0 */  lw    $t9, %call16(st_internal)($gp)
/* 00488928 8F848044 */  lw    $a0, %got(RO_1000EB70)($gp)
/* 0048892C AFA50024 */  sw    $a1, 0x24($sp)
/* 00488930 AFA60020 */  sw    $a2, 0x20($sp)
/* 00488934 0320F809 */  jalr  $t9
/* 00488938 2484EB70 */   addiu $a0, %lo(RO_1000EB70) # addiu $a0, $a0, -0x1490
/* 0048893C 8FBC0018 */  lw    $gp, 0x18($sp)
/* 00488940 8FA50024 */  lw    $a1, 0x24($sp)
/* 00488944 8FA60020 */  lw    $a2, 0x20($sp)
/* 00488948 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 0048894C 8C630000 */  lw    $v1, ($v1)
/* 00488950 8C620038 */  lw    $v0, 0x38($v1)
.L00488954:
/* 00488954 0005C0C0 */  sll   $t8, $a1, 3
/* 00488958 000670C0 */  sll   $t6, $a2, 3
/* 0048895C 0058C821 */  addu  $t9, $v0, $t8
/* 00488960 8F290000 */  lw    $t1, ($t9)
/* 00488964 004E7821 */  addu  $t7, $v0, $t6
/* 00488968 ADE90000 */  sw    $t1, ($t7)
/* 0048896C 8F280004 */  lw    $t0, 4($t9)
/* 00488970 ADE80004 */  sw    $t0, 4($t7)
/* 00488974 8FBF001C */  lw    $ra, 0x1c($sp)
/* 00488978 27BD0020 */  addiu $sp, $sp, 0x20
/* 0048897C 03E00008 */  jr    $ra
/* 00488980 00000000 */   nop   
    .type st_setidn, @function
    .size st_setidn, .-st_setidn
    .end st_setidn

glabel st_pext_dn
    .ent st_pext_dn
/* 00488984 3C1C0FB9 */  .cpload $t9
/* 00488988 279C190C */  
/* 0048898C 0399E021 */  
/* 00488990 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 00488994 3C017FFF */  lui   $at, 0x7fff
/* 00488998 AFA50024 */  sw    $a1, 0x24($sp)
/* 0048899C 3421FFFF */  ori   $at, $at, 0xffff
/* 004889A0 00802825 */  move  $a1, $a0
/* 004889A4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 004889A8 AFBC0018 */  sw    $gp, 0x18($sp)
/* 004889AC 10810008 */  beq   $a0, $at, .L004889D0
/* 004889B0 AFA40020 */   sw    $a0, 0x20($sp)
/* 004889B4 8F9987F0 */  lw    $t9, %call16(st_internal)($gp)
/* 004889B8 8F848044 */  lw    $a0, %got(RO_1000EBA8)($gp)
/* 004889BC 3C067FFF */  lui   $a2, 0x7fff
/* 004889C0 34C6FFFF */  ori   $a2, $a2, 0xffff
/* 004889C4 0320F809 */  jalr  $t9
/* 004889C8 2484EBA8 */   addiu $a0, %lo(RO_1000EBA8) # addiu $a0, $a0, -0x1458
/* 004889CC 8FBC0018 */  lw    $gp, 0x18($sp)
.L004889D0:
/* 004889D0 8FA50024 */  lw    $a1, 0x24($sp)
/* 004889D4 04A00007 */  bltz  $a1, .L004889F4
/* 004889D8 00000000 */   nop   
/* 004889DC 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 004889E0 8C630000 */  lw    $v1, ($v1)
/* 004889E4 8C6E001C */  lw    $t6, 0x1c($v1)
/* 004889E8 01C5082A */  slt   $at, $t6, $a1
/* 004889EC 5020000A */  beql  $at, $zero, .L00488A18
/* 004889F0 8FBF001C */   lw    $ra, 0x1c($sp)
.L004889F4:
/* 004889F4 8F9987F0 */  lw    $t9, %call16(st_internal)($gp)
/* 004889F8 8F848044 */  lw    $a0, %got(RO_1000EBE4)($gp)
/* 004889FC 0320F809 */  jalr  $t9
/* 00488A00 2484EBE4 */   addiu $a0, %lo(RO_1000EBE4) # addiu $a0, $a0, -0x141c
/* 00488A04 8FBC0018 */  lw    $gp, 0x18($sp)
/* 00488A08 8FA50024 */  lw    $a1, 0x24($sp)
/* 00488A0C 8F838CB8 */  lw     $v1, %got(st_pchdr)($gp)
/* 00488A10 8C630000 */  lw    $v1, ($v1)
/* 00488A14 8FBF001C */  lw    $ra, 0x1c($sp)
.L00488A18:
/* 00488A18 8C6F0018 */  lw    $t7, 0x18($v1)
/* 00488A1C 0005C100 */  sll   $t8, $a1, 4
/* 00488A20 27BD0020 */  addiu $sp, $sp, 0x20
/* 00488A24 03E00008 */  jr    $ra
/* 00488A28 01F81021 */   addu  $v0, $t7, $t8
    .type st_pext_dn, @function
    .size st_pext_dn, .-st_pext_dn
    .end st_pext_dn
)"");
#endif

/*
0040BCA0 path_blockno
*/
int st_iextmax(void) {
    return st_pchdr->cext;
}

// unused
void st_setmsgname(const char *name) {
    st_errname = malloc(strlen(name) + 1);
    if (st_errname == NULL) {
        fprintf(stderr, "libmld: Internal: cannot allocate to initialize component name for libmld errors\n");
        exit(1);
    }
    strcpy(st_errname, name);
}
