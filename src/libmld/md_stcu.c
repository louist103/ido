#include <stdlib.h> /* calloc */
#include <string.h> /* bzero */
#include "libmld.h"

/*
00488120 st_setchdr
00488138 st_currentpchdr
00488150 st_free
00488434 st_extstradd
00488550 st_str_extiss
00488590 st_idn_dn
004886A8 st_idn_rndx
004887CC st_rndx_idn
004888DC st_setidn
00488984 st_pext_dn
00488A2C st_iextmax
00488C00 st_ifdmax
00488C1C st_setfd
00488C8C st_fdadd
0048932C st_auxadd
00489458 st_pdadd
004895E4 st_lineadd
0048970C st_stradd
004898C0 st_paux_ifd_iaux
004899B0 st_pline_ifd_iline
00489AA0 st_str_iss
00489CA0 st_symadd
00489F38 st_ifd_pcfd
00489FC4 st_pcfd_ifd
0048A06C st_psym_ifd_isym
0048A194 st_paux_iaux
0048A260 st_str_ifd_iss
0048A330 st_ppd_ifd_isym
0048A5A8 _md_st_str_extiss
0048A5E8 _md_st_str_iss
0048A698 _md_st_iextmax
0048A850 _md_st_ifdmax
0048A86C _md_st_setfd
0048A8E0 st_cuinit
0048A954 st_extadd
0048AB3C st_pext_iext
0048ABB0 st_idn_index_fext
0048ACEC st_pdn_idn
0048D0E0 st_readst
0048E1D8 st_writest
*/
CHDRR *st_pchdr;

CHDRR *st_cuinit(void) {
    st_pchdr = calloc(sizeof(CHDRR), 1);
    if (st_pchdr == NULL) {
        _md_st_error("st_cuinit: cannot allocate current chdr\n");
    }
    st_pchdr->cdn = 2;
    return st_pchdr;
}

/*
0040BCA0 path_blockno
0048A06C st_psym_ifd_isym
0048BA18 st_procend
0048BC7C st_procbegin
0048C0B0 st_psym_idn_offset
0048C2E0 st_fixextindex
0048C394 st_fixextsc
0048C410 st_pdadd_idn
0048C494 st_fixiss
*/
EXTR *st_pext_iext(int index) {
    if (index < 0 || st_pchdr->cext < index) {
        _md_st_internal("st_pext_iext: index out of range (%d)\n", index);
    }

    return &st_pchdr->pext[index];
}

/*
0048AE84 st_filebegin
0048B83C st_blockend
0048BA18 st_procend
*/
int st_idn_index_fext(int index, int fext) {
    DNR dn;

    if (st_pchdr == NULL) {
        _md_st_internal("st_idn_index_fext: you didn't initialize with cuinit or readst\n");
    }

    if (st_pchdr->cdn >= st_pchdr->cdnMax) {
        st_pchdr->pdn = _md_st_malloc(st_pchdr->pdn, &st_pchdr->cdnMax, sizeof(DNR), 16 * sizeof(DNR));
    }

    if (st_pchdr->cdnMax == 0) {
        bzero(st_pchdr->pdn, 2 * sizeof(DNR));
    }

    dn.index = index;
    if (fext != 0) {
        dn.rfd = ST_EXTIFD;
    } else {
        dn.rfd = _md_st_currentifd();
    }

    st_pchdr->pdn[st_pchdr->cdn].rfd = dn.rfd;
    st_pchdr->pdn[st_pchdr->cdn].index = dn.index;
    return st_pchdr->cdn++;
}

/*
0040BCA0 path_blockno
0048B2F0 st_fileend
0048BA18 st_procend
0048BC7C st_procbegin
0048BE8C st_sym_idn
0048BF74 st_str_idn
0048C008 st_fglobal_idn
0048C0B0 st_psym_idn_offset
0048C2E0 st_fixextindex
0048C394 st_fixextsc
0048C410 st_pdadd_idn
0048C494 st_fixiss
0048C520 st_changedn
0048CFAC st_auxrndxadd_idn
*/
DNR* st_pdn_idn(int idn) {
    if ((idn < 0) || (st_pchdr->cdn < idn)) {
        _md_st_internal("st_pdn_idn: idn (%d) less than 0 or greater than max (%d)\n", idn, st_pchdr->cdn);
    }
    return &st_pchdr->pdn[idn];
}

#if 0
__asm__(R""(
.macro glabel label
    .global \label
    .balign 4
    \label:
.endm
.rdata
RO_1000F07C:
    # 0048A954 st_extadd
    .asciz "st_extadd: you didn't initialize with cuinit or readst\n"


.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.text
glabel st_extadd
    .ent st_extadd
/* 0048A954 3C1C0FB9 */  .cpload $t9
/* 0048A958 279CF93C */  
/* 0048A95C 0399E021 */  
/* 0048A960 8F888CB8 */  lw     $t0, %got(st_pchdr)($gp)
/* 0048A964 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0048A968 AFB00014 */  sw    $s0, 0x14($sp)
/* 0048A96C 8D080000 */  lw    $t0, ($t0)
/* 0048A970 00E08025 */  move  $s0, $a3
/* 0048A974 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0048A978 AFBC0018 */  sw    $gp, 0x18($sp)
/* 0048A97C AFA40028 */  sw    $a0, 0x28($sp)
/* 0048A980 AFA5002C */  sw    $a1, 0x2c($sp)
/* 0048A984 15000008 */  bnez  $t0, .L0048A9A8
/* 0048A988 AFA60030 */   sw    $a2, 0x30($sp)
/* 0048A98C 8F9987D0 */  lw    $t9, %call16(_md_st_internal)($gp)
/* 0048A990 8F848044 */  lw    $a0, %got(RO_1000F07C)($gp)
/* 0048A994 0320F809 */  jalr  $t9
/* 0048A998 2484F07C */   addiu $a0, %lo(RO_1000F07C) # addiu $a0, $a0, -0xf84
/* 0048A99C 8FBC0018 */  lw    $gp, 0x18($sp)
/* 0048A9A0 8F888CB8 */  lw     $t0, %got(st_pchdr)($gp)
/* 0048A9A4 8D080000 */  lw    $t0, ($t0)
.L0048A9A8:
/* 0048A9A8 8D04001C */  lw    $a0, 0x1c($t0)
/* 0048A9AC 8D0E0020 */  lw    $t6, 0x20($t0)
/* 0048A9B0 25050020 */  addiu $a1, $t0, 0x20
/* 0048A9B4 008E082A */  slt   $at, $a0, $t6
/* 0048A9B8 5420000E */  bnezl $at, .L0048A9F4
/* 0048A9BC 8D180018 */   lw    $t8, 0x18($t0)
/* 0048A9C0 8F9987E0 */  lw    $t9, %call16(_md_st_malloc)($gp)
/* 0048A9C4 8D040018 */  lw    $a0, 0x18($t0)
/* 0048A9C8 24060010 */  li    $a2, 16
/* 0048A9CC 0320F809 */  jalr  $t9
/* 0048A9D0 24070020 */   li    $a3, 32
/* 0048A9D4 8FBC0018 */  lw    $gp, 0x18($sp)
/* 0048A9D8 8F8F8CB8 */  lw     $t7, %got(st_pchdr)($gp)
/* 0048A9DC 8F888CB8 */  lw     $t0, %got(st_pchdr)($gp)
/* 0048A9E0 8DEF0000 */  lw    $t7, ($t7)
/* 0048A9E4 ADE20018 */  sw    $v0, 0x18($t7)
/* 0048A9E8 8D080000 */  lw    $t0, ($t0)
/* 0048A9EC 8D04001C */  lw    $a0, 0x1c($t0)
/* 0048A9F0 8D180018 */  lw    $t8, 0x18($t0)
.L0048A9F4:
/* 0048A9F4 0004C900 */  sll   $t9, $a0, 4
/* 0048A9F8 03191821 */  addu  $v1, $t8, $t9
/* 0048A9FC 8F9987DC */  lw    $t9, %call16(_md_st_currentifd)($gp)
/* 0048AA00 AFA30024 */  sw    $v1, 0x24($sp)
/* 0048AA04 0320F809 */  jalr  $t9
/* 0048AA08 00000000 */   nop   
/* 0048AA0C 8FA30024 */  lw    $v1, 0x24($sp)
/* 0048AA10 8FBC0018 */  lw    $gp, 0x18($sp)
/* 0048AA14 3C01000F */  lui   $at, 0xf
/* 0048AA18 90690000 */  lbu   $t1, ($v1)
/* 0048AA1C A4620002 */  sh    $v0, 2($v1)
/* 0048AA20 3421FFFF */  ori   $at, $at, 0xffff
/* 0048AA24 312BFF7F */  andi  $t3, $t1, 0xff7f
/* 0048AA28 316D00BF */  andi  $t5, $t3, 0xbf
/* 0048AA2C 31AF00DF */  andi  $t7, $t5, 0xdf
/* 0048AA30 A06B0000 */  sb    $t3, ($v1)
/* 0048AA34 31F900EF */  andi  $t9, $t7, 0xef
/* 0048AA38 A06D0000 */  sb    $t5, ($v1)
/* 0048AA3C A06F0000 */  sb    $t7, ($v1)
/* 0048AA40 332900F7 */  andi  $t1, $t9, 0xf7
/* 0048AA44 A0790000 */  sb    $t9, ($v1)
/* 0048AA48 A0690000 */  sb    $t1, ($v1)
/* 0048AA4C 946A0000 */  lhu   $t2, ($v1)
/* 0048AA50 9069000C */  lbu   $t1, 0xc($v1)
/* 0048AA54 314BF800 */  andi  $t3, $t2, 0xf800
/* 0048AA58 A46B0000 */  sh    $t3, ($v1)
/* 0048AA5C 8FAC0028 */  lw    $t4, 0x28($sp)
/* 0048AA60 312AFF03 */  andi  $t2, $t1, 0xff03
/* 0048AA64 AC6C0004 */  sw    $t4, 4($v1)
/* 0048AA68 8FAD002C */  lw    $t5, 0x2c($sp)
/* 0048AA6C AC6D0008 */  sw    $t5, 8($v1)
/* 0048AA70 8FAF0030 */  lw    $t7, 0x30($sp)
/* 0048AA74 00106940 */  sll   $t5, $s0, 5
/* 0048AA78 31AE03E0 */  andi  $t6, $t5, 0x3e0
/* 0048AA7C 000FC880 */  sll   $t9, $t7, 2
/* 0048AA80 032A5825 */  or    $t3, $t9, $t2
/* 0048AA84 A06B000C */  sb    $t3, 0xc($v1)
/* 0048AA88 946F000C */  lhu   $t7, 0xc($v1)
/* 0048AA8C 31F8FC1F */  andi  $t8, $t7, 0xfc1f
/* 0048AA90 01D84825 */  or    $t1, $t6, $t8
/* 0048AA94 A469000C */  sh    $t1, 0xc($v1)
/* 0048AA98 9079000D */  lbu   $t9, 0xd($v1)
/* 0048AA9C 332AFFEF */  andi  $t2, $t9, 0xffef
/* 0048AAA0 A06A000D */  sb    $t2, 0xd($v1)
/* 0048AAA4 8FAB0038 */  lw    $t3, 0x38($sp)
/* 0048AAA8 8C62000C */  lw    $v0, 0xc($v1)
/* 0048AAAC 01616024 */  and   $t4, $t3, $at
/* 0048AAB0 01826826 */  xor   $t5, $t4, $v0
/* 0048AAB4 000D7B00 */  sll   $t7, $t5, 0xc
/* 0048AAB8 000F7302 */  srl   $t6, $t7, 0xc
/* 0048AABC 24010012 */  li    $at, 18
/* 0048AAC0 01C2C026 */  xor   $t8, $t6, $v0
/* 0048AAC4 12010013 */  beq   $s0, $at, .L0048AB14
/* 0048AAC8 AC78000C */   sw    $t8, 0xc($v1)
/* 0048AACC 24010011 */  li    $at, 17
/* 0048AAD0 12010010 */  beq   $s0, $at, .L0048AB14
/* 0048AAD4 00000000 */   nop   
/* 0048AAD8 1200000E */  beqz  $s0, .L0048AB14
/* 0048AADC 24010006 */   li    $at, 6
/* 0048AAE0 1201000C */  beq   $s0, $at, .L0048AB14
/* 0048AAE4 24010015 */   li    $at, 21
/* 0048AAE8 1201000A */  beq   $s0, $at, .L0048AB14
/* 0048AAEC 00000000 */   nop   
/* 0048AAF0 8F9987BC */  lw    $t9, %call16(st_pcfd_ifd)($gp)
/* 0048AAF4 94640002 */  lhu   $a0, 2($v1)
/* 0048AAF8 0320F809 */  jalr  $t9
/* 0048AAFC 00000000 */   nop   
/* 0048AB00 8C430000 */  lw    $v1, ($v0)
/* 0048AB04 8FBC0018 */  lw    $gp, 0x18($sp)
/* 0048AB08 9069003C */  lbu   $t1, 0x3c($v1)
/* 0048AB0C 3139FFFB */  andi  $t9, $t1, 0xfffb
/* 0048AB10 A079003C */  sb    $t9, 0x3c($v1)
.L0048AB14:
/* 0048AB14 8F888CB8 */  lw     $t0, %got(st_pchdr)($gp)
/* 0048AB18 8D080000 */  lw    $t0, ($t0)
/* 0048AB1C 8D02001C */  lw    $v0, 0x1c($t0)
/* 0048AB20 244A0001 */  addiu $t2, $v0, 1
/* 0048AB24 AD0A001C */  sw    $t2, 0x1c($t0)
/* 0048AB28 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0048AB2C 8FB00014 */  lw    $s0, 0x14($sp)
/* 0048AB30 27BD0028 */  addiu $sp, $sp, 0x28
/* 0048AB34 03E00008 */  jr    $ra
/* 0048AB38 00000000 */   nop   
    .type st_extadd, @function
    .size st_extadd, .-st_extadd
    .end st_extadd)"");
#endif

/* I have no idea whats going on here 
int st_extadd(int iss, int value, int st, int sc, int index) {
    void* sp24;

    int temp_v0;
    int temp_v0_2;
    char temp_t3;
    char temp_t5;
    char temp_t7;
    char temp_t9;
    pEXTR* pExt;
    void* temp_v1_2;

    if (st_pchdr == NULL) {
        _md_st_internal("st_extadd: you didn't initialize with cuinit or readst\n");
    }
    if (st_pchdr->cext >= st_pchdr->cextMax) {
        st_pchdr->pext = _md_st_malloc(st_pchdr->pext, st_pchdr + 0x20, 0x10, 0x20);
    }
    pExt = &st_pchdr->pext[st_pchdr->cext]);
    pExt->unk2 = _md_st_currentifd(st_pchdr->cext);
    temp_t3 = pExt->unk0 & 0xFF7F;
    temp_t5 = temp_t3 & 0xBF;
    temp_t7 = temp_t5 & 0xDF;
    pExt->unk0 = temp_t3;
    temp_t9 = temp_t7 & 0xEF;
    pExt->unk0 = temp_t5;
    pExt->unk0 = temp_t7;
    pExt->unk0 = temp_t9;
    pExt->unk0 = (char) (temp_t9 & 0xF7);
    pExt->unk0 = (s16) ((u16) temp_v1->unk0 & 0xF800);
    pExt->unk4 = iss;
    pExt->unk8 = value;
    pExt->unkC = (char) ((st * 4) | (pExt->unkC & 0xFF03));
    pExt->unkC = (s16) (((sc << 5) & 0x3E0) | ((u16) temp_v1->unkC & 0xFC1F));
    pExt->unkD = (char) (pExt->unkD & 0xFFEF);
    temp_v0_2 = (int) pExt->unkC;
    pExt->unkC = (int) (((u32) (((index & 0xFFFFF) ^ temp_v0_2) << 0xC) >> 0xC) ^ temp_v0_2);
    if ((sc != 0x12) && (sc != 0x11) && (sc != 0) && (sc != 6) && (sc != 0x15)) {
        temp_v1_2 = st_pcfd_ifd((int) pExt->unk2)->pfd;
        temp_v1_2->unk3C = (char) (temp_v1_2->unk3C & 0xFFFB);
    }
    st_pchdr = st_pchdr;
    temp_v0 = st_pchdr->cext;
    st_pchdr->cext = temp_v0 + 1;
    return temp_v0;
}*/
