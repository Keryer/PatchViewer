__int64 __fastcall sub_25E0(unsigned int *a1, unsigned __int64 a2, char *a3, __int64 a4)
{
  unsigned __int64 v5; // r8
  unsigned int v6; // r13d
  unsigned __int64 v7; // rdx
  unsigned int *v8; // r15
  __int64 result; // rax
  unsigned int v10; // r11d
  char *v11; // rax
  unsigned __int8 *v12; // r14
  unsigned __int8 *v13; // r12
  unsigned int v14; // r15d
  unsigned __int8 *v15; // r13
  __int64 v17; // r9
  unsigned __int64 v18; // rbx
  unsigned int (__fastcall *v19)(unsigned int *, unsigned __int64, unsigned __int64, __int64, unsigned __int64, char *); // rax
  unsigned __int8 *v20; // r12
  char v21; // al
  char v22; // dl
  __int16 v23; // dx
  bool v24; // dl
  bool v25; // bp
  bool v26; // bl
  bool v27; // r12
  __int16 v28; // cx
  __int64 (__fastcall *v29)(unsigned int *, char *, signed __int64); // rax
  int v30; // eax
  __int64 (__fastcall *v31)(unsigned int *, char *, signed __int64); // rax
  int v32; // eax
  __int64 (__fastcall *v33)(unsigned int *, char *, signed __int64); // rax
  int v34; // eax
  __int64 (__fastcall *v35)(unsigned int *, char *, signed __int64); // r8
  int v36; // eax
  __int64 (__fastcall *v37)(unsigned int *, char *, signed __int64); // r8
  int v38; // eax
  __int16 v39; // ax
  __int64 v40; // rax
  __int64 v41; // rax
  int v42; // eax
  char v43; // al
  unsigned int v44; // eax
  __int16 v45; // ax
  bool v46; // zf
  unsigned __int8 v47; // al
  __int16 v48; // ax
  __int16 v49; // ax
  unsigned __int8 *v50; // rbx
  unsigned __int8 v51; // al
  char v52; // dl
  unsigned __int8 *v53; // r12
  unsigned int v54; // r13d
  unsigned __int64 v55; // rax
  unsigned __int64 v56; // rax
  __int16 v57; // ax
  int v58; // eax
  unsigned __int8 v59; // dl
  int v60; // eax
  unsigned __int8 *v61; // rax
  __int16 v62; // ax
  __int16 v63; // ax
  __int64 v64; // rax
  __int64 v65; // rax
  int v66; // edi
  unsigned __int64 v67; // rax
  unsigned __int64 v68; // rax
  __int64 v69; // rax
  unsigned int *v70; // rax
  unsigned __int8 *v71; // r12
  char v72; // al
  unsigned int v73; // eax
  signed __int64 v74; // rdx
  unsigned __int8 *v75; // rdx
  __int64 v76; // rax
  int v77; // ecx
  int v78; // eax
  int v79; // ecx
  int v80; // eax
  int v81; // ecx
  int v82; // eax
  int v83; // ecx
  int v84; // eax
  char v85; // al
  char v86; // al
  char v87; // dl
  int v88; // ecx
  int v89; // eax
  char v90; // al
  unsigned __int8 v91; // bl
  char v92; // al
  char v93; // al
  unsigned __int8 v94; // bl
  char v95; // al
  char v96; // al
  unsigned __int8 v97; // bl
  char v98; // al
  unsigned __int8 *v99; // rax
  unsigned __int8 v100; // bl
  unsigned __int64 v101; // rax
  char v102; // al
  unsigned __int8 v103; // bl
  char v104; // al
  unsigned __int8 *v105; // rax
  __int16 v106; // ax
  char v107; // al
  char v108; // al
  unsigned __int8 v109; // bl
  __int16 v110; // ax
  char v111; // al
  char v112; // al
  __int16 v113; // ax
  __int64 v114; // r9
  unsigned __int8 *v115; // r12
  int v116; // eax
  __int64 v117; // rdx
  __int64 (__fastcall *v118)(unsigned int *, unsigned __int64, __int64, __int64, unsigned __int64, __int64); // rax
  int v119; // eax
  char v120; // al
  unsigned __int8 *v121; // r12
  char *v122; // r9
  unsigned int *v123; // r15
  char v124; // al
  __int16 v125; // ax
  unsigned int *v126; // r15
  int v127; // r10d
  __int16 v128; // ax
  __int64 (__fastcall *v129)(unsigned int *); // rcx
  int v130; // eax
  __int16 v131; // dx
  __int16 v132; // ax
  __int16 v133; // dx
  unsigned int v134; // r13d
  __int16 v135; // ax
  __int16 v136; // ax
  __int16 v137; // ax
  __int16 v138; // ax
  __int16 v139; // ax
  int v140; // eax
  int v141; // ebx
  char v142; // dl
  char *v143; // rdi
  __int64 (__fastcall *v144)(unsigned int *, char *, unsigned __int64, __int64); // rax
  char *v145; // rsi
  __int16 v146; // dx
  int v147; // eax
  char v148; // al
  __int64 v149; // rax
  char v150; // al
  char v151; // al
  char v152; // al
  char v153; // al
  char v154; // al
  char v155; // al
  char v156; // al
  char v157; // al
  char v158; // al
  char v159; // al
  char v160; // al
  char v161; // al
  char v162; // al
  char v163; // al
  char v164; // al
  char v165; // al
  char v166; // al
  char v167; // al
  char v168; // al
  unsigned __int16 v169; // ax
  char v170; // al
  unsigned __int8 *v171; // rdi
  char v172; // al
  char v173; // al
  __int16 v174; // ax
  char v175; // al
  int v176; // eax
  char v177; // al
  char v178; // al
  char v179; // al
  char v180; // al
  __int64 v181; // [rsp+8h] [rbp-90h]
  char v182; // [rsp+8h] [rbp-90h]
  __int64 v183; // [rsp+8h] [rbp-90h]
  unsigned __int64 *v184; // [rsp+10h] [rbp-88h]
  unsigned __int8 v185; // [rsp+18h] [rbp-80h]
  char *v186; // [rsp+18h] [rbp-80h]
  char *v187; // [rsp+18h] [rbp-80h]
  char *v188; // [rsp+18h] [rbp-80h]
  char *v189; // [rsp+18h] [rbp-80h]
  char *v190; // [rsp+18h] [rbp-80h]
  char *v191; // [rsp+20h] [rbp-78h]
  char *v192; // [rsp+20h] [rbp-78h]
  char *v193; // [rsp+20h] [rbp-78h]
  char *v194; // [rsp+28h] [rbp-70h]
  char *v195; // [rsp+30h] [rbp-68h]
  char *v196; // [rsp+38h] [rbp-60h]
  char *v197; // [rsp+40h] [rbp-58h]
  char *v198; // [rsp+48h] [rbp-50h]
  unsigned int v199; // [rsp+58h] [rbp-40h]
  __int64 v200; // [rsp+58h] [rbp-40h]
  unsigned __int8 *v201; // [rsp+58h] [rbp-40h]

  v5 = *((unsigned __int8 *)a1 + 31);
  v6 = a1[2];
  v184 = (unsigned __int64 *)a2;
  v181 = a4;
  v185 = *((_BYTE *)a1 + 2) >> 7;
  v7 = (*(_WORD *)a1 >> 2) & 0x7F;
  if ( (v5 & 0x7F) != 0 )
    return 0LL;
  v8 = a1;
  if ( !a4 )
  {
    if ( ((*(_WORD *)a1 >> 2) & 0x7F) != 0x3F )
    {
      if ( ((*(_WORD *)a1 >> 2) & 0x7Fu) <= 0x3F )
      {
        result = 0LL;
        if ( ((*(_WORD *)a1 >> 2) & 0x7F) == 4 )
          return result;
        if ( ((*(_WORD *)a1 >> 2) & 0x7Fu) <= 4 )
        {
          if ( ((((*(_WORD *)a1 >> 2) & 0x7F) + 127) & 0x7Fu) <= 1 )
            return result;
        }
        else if ( ((*(_WORD *)a1 >> 2) & 0x7F) == 0x12 )
        {
          return result;
        }
      }
      *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xB;
      return 1LL;
    }
    v19 = *(unsigned int (__fastcall **)(unsigned int *, unsigned __int64, unsigned __int64, __int64, unsigned __int64, char *))(a2 + 56);
    if ( v19 && v19(a1, a2, v7, a4, v5, a3) )
    {
      v107 = *((_BYTE *)a1 + 31);
      a1[2] = v6;
      *((_BYTE *)a1 + 31) = v107 & 0x80 | 7;
      return 0LL;
    }
    return 0LL;
  }
  v10 = (*(_WORD *)a1 >> 2) & 0x7F;
  if ( v10 == 45 )
  {
    v198 = a3;
    v197 = 0LL;
    v196 = 0LL;
    v191 = 0LL;
  }
  else if ( ((*(_WORD *)a1 >> 2) & 0x7F) == 0x32 )
  {
    v191 = a3;
    v197 = 0LL;
    v196 = 0LL;
    v198 = 0LL;
  }
  else if ( ((*(_WORD *)a1 >> 2) & 0x7F) == 0x10 )
  {
    v197 = a3;
    v10 = 16;
    v196 = 0LL;
    v191 = 0LL;
    v198 = 0LL;
  }
  else
  {
    v191 = 0LL;
    v11 = 0LL;
    v7 = (((*(_WORD *)a1 >> 2) & 0x7F) + 107) & 0x7F;
    v197 = 0LL;
    v198 = 0LL;
    if ( (unsigned __int8)v7 < 0xBu )
      v11 = a3;
    v196 = v11;
  }
  v12 = (unsigned __int8 *)&a3[a4];
  if ( a3 == &a3[a4] )
  {
    v194 = 0LL;
    v24 = v198 != 0LL;
    v25 = v191 != 0LL;
    v26 = v196 != 0LL;
    v27 = v197 != 0LL;
LABEL_42:
    if ( (v5 & 0x7F) != 0 )
      __assert_fail(
        "HTTP_PARSER_ERRNO(parser) == HPE_OK",
        "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
        0x853u,
        "http_parser_execute");
    LOBYTE(v28) = v10 & 0x7F;
    if ( v24 )
    {
      v29 = (__int64 (__fastcall *)(unsigned int *, char *, signed __int64))v184[3];
      if ( v29 )
      {
        v186 = a3;
        *(_WORD *)v8 = (4 * (v10 & 0x7F)) | *(_WORD *)v8 & 0xFE03;
        v30 = v29(v8, v198, v12 - (unsigned __int8 *)v198);
        a3 = v186;
        if ( v30 )
        {
          v154 = *((_BYTE *)v8 + 31);
          v8[2] = v6;
          *((_BYTE *)v8 + 31) = v154 & 0x80 | 3;
        }
        v28 = (*(_WORD *)v8 >> 2) & 0x7F;
        if ( (*((_BYTE *)v8 + 31) & 0x7F) != 0 )
          return v12 - (unsigned __int8 *)a3;
      }
    }
    if ( v25 )
    {
      v31 = (__int64 (__fastcall *)(unsigned int *, char *, signed __int64))v184[4];
      if ( v31 )
      {
        v187 = a3;
        *(_WORD *)v8 = (4 * (v28 & 0x7F)) | *(_WORD *)v8 & 0xFE03;
        v32 = v31(v8, v191, v12 - (unsigned __int8 *)v191);
        a3 = v187;
        if ( v32 )
        {
          v156 = *((_BYTE *)v8 + 31);
          v8[2] = v6;
          *((_BYTE *)v8 + 31) = v156 & 0x80 | 4;
        }
        v28 = (*(_WORD *)v8 >> 2) & 0x7F;
        if ( (*((_BYTE *)v8 + 31) & 0x7F) != 0 )
          return v12 - (unsigned __int8 *)a3;
      }
    }
    if ( v26 )
    {
      v33 = (__int64 (__fastcall *)(unsigned int *, char *, signed __int64))v184[1];
      if ( v33 )
      {
        v188 = a3;
        *(_WORD *)v8 = (4 * (v28 & 0x7F)) | *(_WORD *)v8 & 0xFE03;
        v34 = v33(v8, v196, v12 - (unsigned __int8 *)v196);
        a3 = v188;
        if ( v34 )
        {
          v158 = *((_BYTE *)v8 + 31);
          v8[2] = v6;
          *((_BYTE *)v8 + 31) = v158 & 0x80 | 2;
        }
        v28 = (*(_WORD *)v8 >> 2) & 0x7F;
        if ( (*((_BYTE *)v8 + 31) & 0x7F) != 0 )
          return v12 - (unsigned __int8 *)a3;
      }
    }
    if ( v194 )
    {
      v35 = (__int64 (__fastcall *)(unsigned int *, char *, signed __int64))v184[6];
      if ( v35 )
      {
        v189 = a3;
        *(_WORD *)v8 = (4 * (v28 & 0x7F)) | *(_WORD *)v8 & 0xFE03;
        v36 = v35(v8, v194, v12 - (unsigned __int8 *)v194);
        a3 = v189;
        if ( v36 )
        {
          v159 = *((_BYTE *)v8 + 31);
          v8[2] = v6;
          *((_BYTE *)v8 + 31) = v159 & 0x80 | 6;
        }
        v28 = (*(_WORD *)v8 >> 2) & 0x7F;
        if ( (*((_BYTE *)v8 + 31) & 0x7F) != 0 )
          return v12 - (unsigned __int8 *)a3;
      }
    }
    if ( !v27 )
      goto LABEL_68;
    v190 = a3;
    v37 = (__int64 (__fastcall *)(unsigned int *, char *, signed __int64))v184[2];
    if ( !v37 )
      goto LABEL_68;
    *(_WORD *)v8 = (4 * (v28 & 0x7F)) | *(_WORD *)v8 & 0xFE03;
    v38 = v37(v8, v197, v12 - (unsigned __int8 *)v197);
    a3 = v190;
    if ( v38 )
    {
      v160 = *((_BYTE *)v8 + 31);
      v8[2] = v6;
      *((_BYTE *)v8 + 31) = v160 & 0x80 | 8;
    }
    v28 = (*(_WORD *)v8 >> 2) & 0x7F;
    if ( (*((_BYTE *)v8 + 31) & 0x7F) != 0 )
      return v12 - (unsigned __int8 *)a3;
LABEL_68:
    v39 = *(_WORD *)v8;
    v8[2] = v6;
    *(_WORD *)v8 = (4 * (v28 & 0x7F)) | v39 & 0xFE03;
    return v181;
  }
  v195 = a3;
  v13 = (unsigned __int8 *)&a3[a4];
  v194 = 0LL;
  v14 = a1[2];
  v15 = (unsigned __int8 *)a3;
  v17 = *((unsigned __int8 *)a1 + 31);
  while ( 2 )
  {
    v18 = (unsigned int)(char)*v15;
    if ( v10 <= 0x3A && dword_B010 < ++v14 )
    {
      a3 = v195;
      v20 = v15;
      v6 = v14;
      v8 = a1;
      *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xC;
      v21 = v10 & 0x7F;
      goto LABEL_29;
    }
LABEL_21:
    switch ( v10 )
    {
      case 1u:
        if ( (_BYTE)v18 == 13 || (_BYTE)v18 == 10 )
        {
          ++v15;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xD;
        v21 = 1;
        goto LABEL_29;
      case 2u:
        if ( (_BYTE)v18 == 13 || (_BYTE)v18 == 10 )
        {
          ++v15;
        }
        else
        {
          *((_QWORD *)a1 + 2) = -1LL;
          *((_WORD *)a1 + 2) = 0;
          if ( (_BYTE)v18 == 72 )
          {
            if ( (v17 & 0x7F) != 0 )
              __assert_fail(
                "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x2E3u,
                "http_parser_execute");
            v7 = *v184;
            if ( *v184 )
            {
              *(_WORD *)a1 = *(_WORD *)a1 & 0xFE03 | 0xC;
              if ( ((unsigned int (__fastcall *)(unsigned int *))v7)(a1) )
              {
                v179 = *((_BYTE *)a1 + 31);
                a1[2] = v14;
                *((_BYTE *)a1 + 31) = v179 & 0x80 | 1;
              }
              v17 = *((unsigned __int8 *)a1 + 31);
              v10 = (*(_WORD *)a1 >> 2) & 0x7F;
              if ( (v17 & 0x7F) != 0 )
                goto LABEL_481;
              ++v15;
            }
            else
            {
              ++v15;
              v10 = 3;
            }
          }
          else
          {
            *(_BYTE *)a1 &= 0xFCu;
LABEL_287:
            a4 = 0LL;
            *((_QWORD *)a1 + 2) = -1LL;
            *((_WORD *)a1 + 2) = 0;
            if ( (unsigned __int8)((v18 | 0x20) - 97) > 0x19u )
            {
LABEL_444:
              a3 = v195;
              v20 = v15;
              v6 = v14;
              v8 = a1;
              *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x10;
              v21 = 18;
              goto LABEL_29;
            }
            v72 = *((_BYTE *)a1 + 2);
            *((_BYTE *)a1 + 30) = 0;
            *((_BYTE *)a1 + 2) = v72 & 0x80 | 1;
            switch ( (char)v18 )
            {
              case 'A':
                *((_BYTE *)a1 + 30) = 19;
                goto LABEL_450;
              case 'B':
                *((_BYTE *)a1 + 30) = 16;
                goto LABEL_450;
              case 'C':
                *((_BYTE *)a1 + 30) = 5;
                goto LABEL_450;
              case 'D':
                goto LABEL_450;
              case 'G':
                *((_BYTE *)a1 + 30) = 1;
                goto LABEL_450;
              case 'H':
                *((_BYTE *)a1 + 30) = 2;
                goto LABEL_450;
              case 'L':
                *((_BYTE *)a1 + 30) = 9;
                goto LABEL_450;
              case 'M':
                *((_BYTE *)a1 + 30) = 10;
                goto LABEL_450;
              case 'N':
                *((_BYTE *)a1 + 30) = 25;
                goto LABEL_450;
              case 'O':
                *((_BYTE *)a1 + 30) = 6;
                goto LABEL_450;
              case 'P':
                *((_BYTE *)a1 + 30) = 3;
                goto LABEL_450;
              case 'R':
                *((_BYTE *)a1 + 30) = 20;
                goto LABEL_450;
              case 'S':
                *((_BYTE *)a1 + 30) = 26;
                goto LABEL_450;
              case 'T':
                *((_BYTE *)a1 + 30) = 7;
                goto LABEL_450;
              case 'U':
                *((_BYTE *)a1 + 30) = 15;
LABEL_450:
                if ( (v17 & 0x7F) != 0 )
                  __assert_fail(
                    "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                    "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                    0x3C1u,
                    "http_parser_execute");
                v7 = *v184;
                if ( *v184 )
                {
                  *(_WORD *)a1 = *(_WORD *)a1 & 0xFE03 | 0x4C;
                  if ( ((unsigned int (__fastcall *)(unsigned int *))v7)(a1) )
                  {
                    v164 = *((_BYTE *)a1 + 31);
                    a1[2] = v14;
                    *((_BYTE *)a1 + 31) = v164 & 0x80 | 1;
                  }
                  v17 = *((unsigned __int8 *)a1 + 31);
                  v10 = (*(_WORD *)a1 >> 2) & 0x7F;
                  if ( (v17 & 0x7F) != 0 )
                    goto LABEL_481;
                  ++v15;
                }
                else
                {
                  ++v15;
                  v10 = 19;
                }
                break;
              default:
                goto LABEL_444;
            }
          }
        }
        goto LABEL_39;
      case 3u:
        if ( (_BYTE)v18 == 84 )
        {
          ++v15;
          v10 = 6;
          *(_BYTE *)a1 = *(_BYTE *)a1 & 0xFC | 1;
          goto LABEL_39;
        }
        if ( (_BYTE)v18 == 69 )
        {
          v44 = *a1;
          *((_BYTE *)a1 + 30) = 2;
          ++v15;
          v10 = 19;
          *a1 = v44 & 0xFF80FFFC | 0x20000;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1D;
        v21 = 3;
        goto LABEL_29;
      case 4u:
        if ( (_BYTE)v18 == 13 || (_BYTE)v18 == 10 )
        {
          ++v15;
        }
        else
        {
          a2 = 0LL;
          *((_QWORD *)a1 + 2) = -1LL;
          *((_WORD *)a1 + 2) = 0;
          if ( (_BYTE)v18 != 72 )
          {
            a3 = v195;
            v20 = v15;
            v6 = v14;
            v8 = a1;
            *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1D;
            v21 = 4;
            goto LABEL_29;
          }
          if ( (v17 & 0x7F) != 0 )
            __assert_fail(
              "HTTP_PARSER_ERRNO(parser) == HPE_OK",
              "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
              0x30Cu,
              "http_parser_execute");
          v7 = *v184;
          if ( *v184 )
          {
            *(_WORD *)a1 = *(_WORD *)a1 & 0xFE03 | 0x14;
            if ( ((unsigned int (__fastcall *)(unsigned int *))v7)(a1) )
            {
              v162 = *((_BYTE *)a1 + 31);
              a1[2] = v14;
              *((_BYTE *)a1 + 31) = v162 & 0x80 | 1;
            }
            v17 = *((unsigned __int8 *)a1 + 31);
            v10 = (*(_WORD *)a1 >> 2) & 0x7F;
            if ( (v17 & 0x7F) != 0 )
              goto LABEL_481;
            ++v15;
          }
          else
          {
            ++v15;
            v10 = 5;
          }
        }
        goto LABEL_39;
      case 5u:
        if ( (_BYTE)v18 != 84 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 5;
          goto LABEL_29;
        }
        ++v15;
        v10 = 6;
        goto LABEL_39;
      case 6u:
        if ( (_BYTE)v18 != 84 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 6;
          goto LABEL_29;
        }
        ++v15;
        v10 = 7;
        goto LABEL_39;
      case 7u:
        if ( (_BYTE)v18 != 80 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 7;
          goto LABEL_29;
        }
        ++v15;
        v10 = 8;
        goto LABEL_39;
      case 8u:
        if ( (_BYTE)v18 != 47 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 8;
          goto LABEL_29;
        }
        ++v15;
        v10 = 9;
        goto LABEL_39;
      case 9u:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          ++v15;
          v10 = 10;
          *((_WORD *)a1 + 12) = v18 - 48;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xE;
        v21 = 9;
        goto LABEL_29;
      case 0xAu:
        if ( (_BYTE)v18 == 46 )
        {
          ++v15;
          v10 = 11;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xE;
        v21 = 10;
        goto LABEL_29;
      case 0xBu:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          ++v15;
          v10 = 12;
          *((_WORD *)a1 + 13) = v18 - 48;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xE;
        v21 = 11;
        goto LABEL_29;
      case 0xCu:
        if ( (_BYTE)v18 == 32 )
        {
          ++v15;
          v10 = 13;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xE;
        v21 = 12;
        goto LABEL_29;
      case 0xDu:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          ++v15;
          v10 = 14;
          *((_WORD *)a1 + 14) = (char)v18 - 48;
        }
        else
        {
          if ( (_BYTE)v18 != 32 )
          {
            a3 = v195;
            v20 = v15;
            v6 = v14;
            v8 = a1;
            *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xF;
            v21 = 13;
            goto LABEL_29;
          }
          ++v15;
        }
        goto LABEL_39;
      case 0xEu:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          v169 = 10 * *((_WORD *)a1 + 14) + v18 - 48;
          *((_WORD *)a1 + 14) = v169;
          if ( v169 > 0x3E7u )
          {
LABEL_78:
            a3 = v195;
            v20 = v15;
            v6 = v14;
            v8 = a1;
            *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xF;
            v21 = 14;
            goto LABEL_29;
          }
          ++v15;
          goto LABEL_39;
        }
        if ( (_BYTE)v18 != 13 )
        {
          if ( (_BYTE)v18 == 32 )
          {
            ++v15;
            v10 = 15;
            goto LABEL_39;
          }
          if ( (_BYTE)v18 != 10 )
            goto LABEL_78;
          *((_BYTE *)a1 + 2) &= 0x80u;
          if ( !v197 )
            v197 = (char *)v15;
          goto LABEL_589;
        }
        if ( v197 )
        {
          *((_BYTE *)a1 + 2) &= 0x80u;
        }
        else
        {
LABEL_576:
          v197 = (char *)v15;
LABEL_305:
          *((_BYTE *)a1 + 2) &= 0x80u;
          if ( (_BYTE)v18 != 13 )
          {
            if ( (_BYTE)v18 != 10 )
            {
              ++v15;
              v10 = 16;
              goto LABEL_39;
            }
LABEL_307:
            if ( (_BYTE)v18 != 13 )
            {
              if ( (_BYTE)v18 != 10 )
              {
                ++v15;
                v10 = 16;
                goto LABEL_39;
              }
LABEL_589:
              if ( (v17 & 0x7F) != 0 )
                __assert_fail(
                  "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                  "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                  0x390u,
                  "http_parser_execute");
              if ( v197 )
              {
                a4 = v184[2];
                if ( a4 )
                {
                  v138 = *(_WORD *)a1 & 0xFE03;
                  LOBYTE(v138) = *(_BYTE *)a1 & 3 | 0xB0;
                  *(_WORD *)a1 = v138;
                  a2 = (unsigned __int64)v197;
                  if ( ((unsigned int (__fastcall *)(unsigned int *, char *, signed __int64))a4)(
                         a1,
                         v197,
                         v15 - (unsigned __int8 *)v197) )
                  {
                    v172 = *((_BYTE *)a1 + 31);
                    a1[2] = v14;
                    *((_BYTE *)a1 + 31) = v172 & 0x80 | 8;
                  }
                  v17 = *((unsigned __int8 *)a1 + 31);
                  v10 = (*(_WORD *)a1 >> 2) & 0x7F;
                  if ( (v17 & 0x7F) != 0 )
                    goto LABEL_481;
                  v197 = 0LL;
                  ++v15;
                }
                else
                {
                  v197 = 0LL;
                  ++v15;
                  v10 = 44;
                }
              }
              else
              {
                ++v15;
                v10 = 44;
              }
              goto LABEL_39;
            }
          }
        }
        if ( (v17 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x38Au,
            "http_parser_execute");
        if ( v197 )
        {
          a4 = v184[2];
          if ( a4 )
          {
            *(_WORD *)a1 = *(_WORD *)a1 & 0xFE03 | 0x44;
            a2 = (unsigned __int64)v197;
            if ( ((unsigned int (__fastcall *)(unsigned int *, char *, signed __int64))a4)(
                   a1,
                   v197,
                   v15 - (unsigned __int8 *)v197) )
            {
              v168 = *((_BYTE *)a1 + 31);
              a1[2] = v14;
              *((_BYTE *)a1 + 31) = v168 & 0x80 | 8;
            }
            v17 = *((unsigned __int8 *)a1 + 31);
            v10 = (*(_WORD *)a1 >> 2) & 0x7F;
            if ( (v17 & 0x7F) != 0 )
              goto LABEL_481;
            v197 = 0LL;
            ++v15;
          }
          else
          {
            v197 = 0LL;
            ++v15;
            v10 = 17;
          }
        }
        else
        {
          ++v15;
          v10 = 17;
        }
        goto LABEL_39;
      case 0xFu:
        if ( v197 )
          goto LABEL_305;
        goto LABEL_576;
      case 0x10u:
        goto LABEL_307;
      case 0x11u:
        if ( (_BYTE)v18 != 10 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 17;
          goto LABEL_29;
        }
        ++v15;
        v10 = 44;
        goto LABEL_39;
      case 0x12u:
        if ( (_BYTE)v18 != 13 && (_BYTE)v18 != 10 )
          goto LABEL_287;
        ++v15;
        goto LABEL_39;
      case 0x13u:
        if ( !(_BYTE)v18 )
          goto LABEL_566;
        a2 = (unsigned __int64)off_ACA0[*((unsigned __int8 *)a1 + 30)];
        v59 = *((_BYTE *)a1 + 2) & 0x7F;
        a4 = *(unsigned __int8 *)(a2 + v59);
        if ( (_BYTE)v18 == 32 )
        {
          if ( (_BYTE)a4 )
          {
            if ( (_BYTE)a4 != 32 )
              goto LABEL_566;
          }
          else
          {
            v10 = 20;
          }
        }
        else if ( (_BYTE)a4 != (_BYTE)v18 )
        {
          if ( (unsigned __int8)(v18 - 65) > 0x19u && (_BYTE)v18 != 45 )
          {
LABEL_566:
            a3 = v195;
            v20 = v15;
            v6 = v14;
            v8 = a1;
            *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x10;
            v21 = 19;
            goto LABEL_29;
          }
          a4 = v59 << 8;
          v60 = v18 | a4 | (*((unsigned __int8 *)a1 + 30) << 16);
          if ( v60 == 655695 )
          {
            *((_BYTE *)a1 + 30) = 11;
          }
          else if ( v60 > 655695 )
          {
            if ( v60 == 983635 )
            {
              *((_BYTE *)a1 + 30) = 27;
            }
            else if ( v60 <= 983635 )
            {
              if ( v60 == 787536 )
              {
                *((_BYTE *)a1 + 30) = 13;
              }
              else if ( v60 <= 787536 )
              {
                if ( v60 == 655937 )
                {
                  *((_BYTE *)a1 + 30) = 21;
                }
                else
                {
                  if ( v60 != 656193 )
                    goto LABEL_566;
                  *((_BYTE *)a1 + 30) = 30;
                }
              }
              else
              {
                if ( v60 != 983618 )
                  goto LABEL_566;
                *((_BYTE *)a1 + 30) = 18;
              }
            }
            else if ( v60 == 1704261 )
            {
              *((_BYTE *)a1 + 30) = 14;
            }
            else if ( v60 <= 1704261 )
            {
              if ( v60 == 983881 )
              {
                *((_BYTE *)a1 + 30) = 32;
              }
              else
              {
                if ( v60 != 1311298 )
                  goto LABEL_566;
                *((_BYTE *)a1 + 30) = 17;
              }
            }
            else
            {
              if ( v60 != 1704271 )
                goto LABEL_566;
              *((_BYTE *)a1 + 30) = 33;
            }
          }
          else if ( v60 == 328008 )
          {
            *((_BYTE *)a1 + 30) = 22;
          }
          else if ( v60 <= 328008 )
          {
            if ( v60 == 196949 )
            {
              *((_BYTE *)a1 + 30) = 4;
            }
            else if ( v60 <= 196949 )
            {
              if ( v60 == 196929 )
              {
                *((_BYTE *)a1 + 30) = 28;
              }
              else
              {
                if ( v60 != 196946 )
                  goto LABEL_566;
                *((_BYTE *)a1 + 30) = 12;
              }
            }
            else
            {
              if ( v60 != 262738 )
                goto LABEL_566;
              *((_BYTE *)a1 + 30) = 29;
            }
          }
          else if ( v60 == 655661 )
          {
            *((_BYTE *)a1 + 30) = 24;
          }
          else if ( v60 <= 655661 )
          {
            if ( v60 == 328272 )
            {
              *((_BYTE *)a1 + 30) = 8;
            }
            else
            {
              if ( v60 != 590153 )
                goto LABEL_566;
              *((_BYTE *)a1 + 30) = 31;
            }
          }
          else
          {
            if ( v60 != 655685 )
              goto LABEL_566;
            *((_BYTE *)a1 + 30) = 23;
          }
        }
        ++v15;
        v7 = (v59 + 1) & 0x7F;
        *((_BYTE *)a1 + 2) = v7 | *((_BYTE *)a1 + 2) & 0x80;
        goto LABEL_39;
      case 0x14u:
        if ( (_BYTE)v18 == 32 )
        {
          ++v15;
        }
        else
        {
          v61 = (unsigned __int8 *)v196;
          if ( !v196 )
            v61 = v15;
          v196 = (char *)v61;
          if ( *((_BYTE *)a1 + 30) == 5 )
            v10 = 24;
          if ( (char)v18 > 10 )
          {
            if ( (unsigned __int8)(v18 - 12) <= 1u )
              goto LABEL_470;
          }
          else if ( (char)v18 > 8 )
          {
            goto LABEL_470;
          }
          a2 = (unsigned int)(char)v18;
          v10 = sub_2250(v10, a2, v7, a4, v5, v17);
          if ( v10 == 1 )
            goto LABEL_470;
          ++v15;
        }
        goto LABEL_39;
      case 0x15u:
      case 0x16u:
      case 0x17u:
      case 0x18u:
        if ( (unsigned __int8)v18 > 0x20u )
          goto LABEL_72;
        v40 = 0x100002400LL;
        if ( _bittest64(&v40, v18) )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x11;
          v21 = v10 & 0x7F;
          goto LABEL_29;
        }
        v41 = 0x100003200LL;
        if ( _bittest64(&v41, v18) )
          goto LABEL_470;
LABEL_72:
        a2 = (unsigned int)(char)v18;
        v10 = sub_2250(v10, a2, v7, a4, v5, v17);
        if ( v10 == 1 )
        {
LABEL_470:
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x11;
          v21 = 1;
          goto LABEL_29;
        }
        ++v15;
        goto LABEL_39;
      case 0x19u:
      case 0x1Au:
      case 0x1Bu:
      case 0x1Cu:
      case 0x1Du:
      case 0x1Eu:
      case 0x1Fu:
        switch ( (_BYTE)v18 )
        {
          case 0xD:
            a1[6] = 589824;
            v10 = 43;
            break;
          case 0x20:
            if ( (v17 & 0x7F) != 0 )
              __assert_fail(
                "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x42Fu,
                "http_parser_execute");
            if ( v196 )
            {
              a4 = v184[1];
              if ( a4 )
              {
                v135 = *(_WORD *)a1 & 0xFE03;
                LOBYTE(v135) = *(_BYTE *)a1 & 3 | 0x80;
                *(_WORD *)a1 = v135;
                a2 = (unsigned __int64)v196;
                if ( ((unsigned int (__fastcall *)(unsigned int *, char *, signed __int64))a4)(
                       a1,
                       v196,
                       v15 - (unsigned __int8 *)v196) )
                {
                  v167 = *((_BYTE *)a1 + 31);
                  a1[2] = v14;
                  *((_BYTE *)a1 + 31) = v167 & 0x80 | 2;
                }
                v17 = *((unsigned __int8 *)a1 + 31);
                v10 = (*(_WORD *)a1 >> 2) & 0x7F;
                if ( (v17 & 0x7F) != 0 )
                  goto LABEL_481;
                v196 = 0LL;
                ++v15;
              }
              else
              {
                v196 = 0LL;
                ++v15;
                v10 = 32;
              }
            }
            else
            {
              ++v15;
              v10 = 32;
            }
            goto LABEL_39;
          case 0xA:
            a1[6] = 589824;
            v10 = 44;
            break;
          default:
            if ( (char)v18 > 10 )
            {
              if ( (unsigned __int8)(v18 - 12) <= 1u )
                goto LABEL_470;
            }
            else if ( (_BYTE)v18 == 9 )
            {
              goto LABEL_470;
            }
            a2 = (unsigned int)(char)v18;
            v10 = sub_2250(v10, a2, v7, a4, v5, v17);
            if ( v10 == 1 )
              goto LABEL_470;
            ++v15;
            goto LABEL_39;
        }
        if ( (v17 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x438u,
            "http_parser_execute");
        if ( v196 )
        {
          a4 = v184[1];
          if ( a4 )
          {
            *(_WORD *)a1 = (4 * (v10 & 0x7F)) | *(_WORD *)a1 & 0xFE03;
            a2 = (unsigned __int64)v196;
            if ( ((unsigned int (__fastcall *)(unsigned int *, char *, signed __int64))a4)(
                   a1,
                   v196,
                   v15 - (unsigned __int8 *)v196) )
            {
              v166 = *((_BYTE *)a1 + 31);
              a1[2] = v14;
              *((_BYTE *)a1 + 31) = v166 & 0x80 | 2;
            }
            v17 = *((unsigned __int8 *)a1 + 31);
            v10 = (*(_WORD *)a1 >> 2) & 0x7F;
            if ( (v17 & 0x7F) != 0 )
              goto LABEL_481;
            v196 = 0LL;
            ++v15;
          }
          else
          {
            v196 = 0LL;
            ++v15;
          }
        }
        else
        {
          ++v15;
        }
        goto LABEL_39;
      case 0x20u:
        switch ( (_BYTE)v18 )
        {
          case 'H':
            ++v15;
            v10 = 33;
            break;
          case 'I':
            if ( *((_BYTE *)a1 + 30) != 33 )
            {
LABEL_87:
              a3 = v195;
              v20 = v15;
              v6 = v14;
              v8 = a1;
              *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1D;
              v21 = 32;
              goto LABEL_29;
            }
            ++v15;
            v10 = 37;
            break;
          case ' ':
            ++v15;
            break;
          default:
            goto LABEL_87;
        }
        goto LABEL_39;
      case 0x21u:
        if ( (_BYTE)v18 != 84 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 33;
          goto LABEL_29;
        }
        ++v15;
        v10 = 34;
        goto LABEL_39;
      case 0x22u:
        if ( (_BYTE)v18 != 84 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 34;
          goto LABEL_29;
        }
        ++v15;
        v10 = 35;
        goto LABEL_39;
      case 0x23u:
        if ( (_BYTE)v18 != 80 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 35;
          goto LABEL_29;
        }
        ++v15;
        v10 = 36;
        goto LABEL_39;
      case 0x24u:
        if ( (_BYTE)v18 != 47 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 36;
          goto LABEL_29;
        }
        ++v15;
        v10 = 39;
        goto LABEL_39;
      case 0x25u:
        if ( (_BYTE)v18 != 67 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 37;
          goto LABEL_29;
        }
        ++v15;
        v10 = 38;
        goto LABEL_39;
      case 0x26u:
        if ( (_BYTE)v18 != 69 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 38;
          goto LABEL_29;
        }
        ++v15;
        v10 = 36;
        goto LABEL_39;
      case 0x27u:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          ++v15;
          v10 = 40;
          *((_WORD *)a1 + 12) = v18 - 48;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xE;
        v21 = 39;
        goto LABEL_29;
      case 0x28u:
        if ( (_BYTE)v18 == 46 )
        {
          ++v15;
          v10 = 41;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xE;
        v21 = 40;
        goto LABEL_29;
      case 0x29u:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          ++v15;
          v10 = 42;
          *((_WORD *)a1 + 13) = v18 - 48;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xE;
        v21 = 41;
        goto LABEL_29;
      case 0x2Au:
        if ( (_BYTE)v18 == 13 )
        {
          ++v15;
          v10 = 43;
        }
        else
        {
          if ( (_BYTE)v18 != 10 )
          {
            a3 = v195;
            v20 = v15;
            v6 = v14;
            v8 = a1;
            *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xE;
            v21 = 42;
            goto LABEL_29;
          }
          ++v15;
          v10 = 44;
        }
        goto LABEL_39;
      case 0x2Bu:
        if ( (_BYTE)v18 == 10 )
        {
          ++v15;
          v10 = 44;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x17;
        v21 = 43;
        goto LABEL_29;
      case 0x2Cu:
        goto LABEL_133;
      case 0x2Du:
        v199 = dword_B010;
        if ( v15 != v13 )
        {
          v5 = (unsigned int)dword_B010;
          v50 = v15;
          a2 = (unsigned __int64)byte_7B60;
          while ( 1 )
          {
            v51 = *v50;
            if ( *v50 == 32 )
              break;
            v52 = byte_7B60[v51];
            if ( !v52 )
              break;
            a4 = *((unsigned __int8 *)a1 + 1);
            if ( (unsigned __int8)a4 > 0x1Du )
LABEL_364:
              __assert_fail(
                "0 && \"Unknown header_state\"",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x555u,
                "http_parser_execute");
            switch ( *((_BYTE *)a1 + 1) >> 1 )
            {
              case 0:
                v74 = v13 - v50;
                if ( v13 - v50 > (unsigned __int64)v199 )
                  v74 = v199;
                v75 = &v50[v74];
                do
                {
                  if ( ++v50 >= v75 )
                    break;
                  v76 = *v50;
                  if ( (_BYTE)v76 == 32 )
                    break;
                }
                while ( byte_7B60[v76] );
                break;
              case 1:
                ++v50;
                *a1 = *a1 & 0xFF8001FF | ((v52 == 111) << 10) | (((*((_BYTE *)a1 + 2) + 1) & 0x7F) << 16);
                break;
              case 2:
                v86 = *((_BYTE *)a1 + 2);
                a4 = (v86 + 1) & 0x7F;
                v46 = v52 == 110;
                v87 = *((_BYTE *)a1 + 1);
                *((_BYTE *)a1 + 2) = a4 | v86 & 0x80;
                ++v50;
                *((_BYTE *)a1 + 1) = v87 & 1 | (6 * v46);
                break;
              case 3:
                v85 = *((_BYTE *)a1 + 2);
                ++v50;
                a4 = (v85 + 1) & 0x7F;
                *((_BYTE *)a1 + 2) = a4 | v85 & 0x80;
                if ( v52 == 110 )
                {
                  *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 8;
                }
                else if ( v52 == 116 )
                {
                  *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 0xC;
                }
                else
                {
LABEL_343:
                  *((_BYTE *)a1 + 1) &= 1u;
                }
                break;
              case 4:
                v83 = *((unsigned __int8 *)a1 + 2);
                ++v50;
                v84 = ((_BYTE)v83 + 1) & 0x7F;
                a4 = v84 | v83 & 0xFFFFFF80;
                *((_BYTE *)a1 + 2) = a4;
                if ( (unsigned __int8)v84 > 0xAu || aProxyConnectio[(v84 & 0x7F) + 6] != v52 )
                  goto LABEL_343;
                a4 &= 0x7Fu;
                if ( (_BYTE)a4 == 9 )
                  goto LABEL_351;
                break;
              case 5:
                v81 = *((unsigned __int8 *)a1 + 2);
                ++v50;
                v82 = ((_BYTE)v81 + 1) & 0x7F;
                a4 = v82 | v81 & 0xFFFFFF80;
                *((_BYTE *)a1 + 2) = a4;
                if ( (unsigned __int8)v82 > 0x10u || aProxyConnectio[v82 & 0x7F] != v52 )
                  goto LABEL_343;
                a4 &= 0x7Fu;
                if ( (_BYTE)a4 == 15 )
LABEL_351:
                  *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 0x12;
                break;
              case 6:
                v79 = *((unsigned __int8 *)a1 + 2);
                ++v50;
                v80 = ((_BYTE)v79 + 1) & 0x7F;
                a4 = v80 | v79 & 0xFFFFFF80;
                *((_BYTE *)a1 + 2) = a4;
                if ( (unsigned __int8)v80 > 0xEu || aContentLength[v80 & 0x7F] != v52 )
                  goto LABEL_343;
                a4 &= 0x7Fu;
                if ( (_BYTE)a4 == 13 )
                  *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 0x14;
                break;
              case 7:
                v77 = *((unsigned __int8 *)a1 + 2);
                ++v50;
                v78 = ((_BYTE)v77 + 1) & 0x7F;
                a4 = v78 | v77 & 0xFFFFFF80;
                *((_BYTE *)a1 + 2) = a4;
                if ( (unsigned __int8)v78 > 0x11u || aTransferEncodi[v78 & 0x7F] != v52 )
                  goto LABEL_343;
                a4 &= 0x7Fu;
                if ( (_BYTE)a4 == 16 )
                {
                  v148 = *((_BYTE *)a1 + 1);
                  *((_WORD *)a1 + 2) |= 0x100u;
                  *((_BYTE *)a1 + 1) = v148 & 1 | 0x1A;
                }
                break;
              case 8:
                v88 = *((unsigned __int8 *)a1 + 2);
                ++v50;
                v89 = ((_BYTE)v88 + 1) & 0x7F;
                a4 = v89 | v88 & 0xFFFFFF80;
                *((_BYTE *)a1 + 2) = a4;
                if ( (unsigned __int8)v89 > 7u || aUpgrade[v89 & 0x7F] != v52 )
                  goto LABEL_343;
                a4 &= 0x7Fu;
                if ( (_BYTE)a4 == 6 )
                  *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 0x1C;
                break;
              case 9:
              case 10:
              case 13:
              case 14:
                *((_BYTE *)a1 + 1) &= 1u;
                ++v50;
                break;
              case 11:
              case 12:
                goto LABEL_364;
            }
            if ( v50 == v13 )
              goto LABEL_150;
          }
          if ( v50 == v13 )
          {
LABEL_150:
            LOBYTE(v5) = v17;
            a3 = v195;
            LODWORD(v53) = (_DWORD)v15;
            v54 = v14;
            v8 = a1;
            goto LABEL_151;
          }
          v7 = v50 - v15;
          v14 += (_DWORD)v50 - (_DWORD)v15;
          if ( v199 >= v14 )
          {
            if ( v51 != 58 )
            {
              a3 = v195;
              v6 = v14;
              v20 = v50;
              v8 = a1;
              *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x18;
              v21 = 45;
              goto LABEL_29;
            }
            if ( (v17 & 0x7F) != 0 )
              __assert_fail(
                "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x564u,
                "http_parser_execute");
            v15 = v50 + 1;
            v10 = 46;
            if ( v198 )
            {
              a4 = v184[3];
              if ( a4 )
              {
                v113 = *(_WORD *)a1 & 0xFE03;
                LOBYTE(v113) = *(_BYTE *)a1 & 3 | 0xB8;
                *(_WORD *)a1 = v113;
                a2 = (unsigned __int64)v198;
                if ( ((unsigned int (__fastcall *)(unsigned int *, char *, signed __int64, __int64, _QWORD))a4)(
                       a1,
                       v198,
                       v50 - (unsigned __int8 *)v198,
                       a4,
                       v199) )
                {
                  v165 = *((_BYTE *)a1 + 31);
                  a1[2] = v14;
                  *((_BYTE *)a1 + 31) = v165 & 0x80 | 3;
                }
                v17 = *((unsigned __int8 *)a1 + 31);
                v10 = (*(_WORD *)a1 >> 2) & 0x7F;
                if ( (v17 & 0x7F) != 0 )
                  return v50 - (unsigned __int8 *)v195 + 1;
                v198 = 0LL;
                v15 = v50 + 1;
              }
              else
              {
                v198 = 0LL;
                v15 = v50 + 1;
                v10 = 46;
              }
            }
            goto LABEL_39;
          }
          a3 = v195;
          v6 = v14;
          v20 = v50;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xC;
          v21 = 45;
LABEL_29:
          v22 = *((_BYTE *)v8 + 31);
          if ( (v22 & 0x7F) == 0 )
            *((_BYTE *)v8 + 31) = v22 & 0x80 | 0x21;
          v23 = *(_WORD *)v8;
          v8[2] = v6;
          *(_WORD *)v8 = v23 & 0xFE03 | (4 * (v21 & 0x7F));
          return v20 - (unsigned __int8 *)a3;
        }
        v53 = v15;
        LOBYTE(v5) = v17;
        v54 = v14;
        a3 = v195;
        v8 = a1;
        v50 = v53;
LABEL_151:
        v6 = (_DWORD)v50 - 1 - (_DWORD)v53 + v54;
        if ( v199 < v6 )
        {
          v20 = v50 - 1;
          v21 = 45;
          *((_BYTE *)v8 + 31) = *((_BYTE *)v8 + 31) & 0x80 | 0xC;
          goto LABEL_29;
        }
        v12 = v50;
LABEL_41:
        v24 = v198 != 0LL;
        v25 = v191 != 0LL;
        v26 = v196 != 0LL;
        v27 = v197 != 0LL;
        if ( (v197 != 0LL) + (v196 != 0LL) + (v198 != 0LL) + (v191 != 0LL) - ((v194 == 0LL) - 1) > 1 )
          __assert_fail(
            "((header_field_mark ? 1 : 0) + (header_value_mark ? 1 : 0) + (url_mark ? 1 : 0) + (body_mark ? 1 : 0) + (sta"
            "tus_mark ? 1 : 0)) <= 1",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x84Du,
            "http_parser_execute");
        goto LABEL_42;
      case 0x2Eu:
        switch ( (_BYTE)v18 )
        {
          case 0x20:
          case 9:
            ++v15;
            break;
          case 0xD:
            ++v15;
            v10 = 47;
            break;
          case 0xA:
            ++v15;
            v10 = 48;
            break;
          default:
            LOBYTE(v42) = *((_BYTE *)a1 + 1);
            goto LABEL_95;
        }
        goto LABEL_39;
      case 0x2Fu:
        if ( (_BYTE)v18 != 10 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 47;
          goto LABEL_29;
        }
        ++v15;
        v10 = 48;
        goto LABEL_39;
      case 0x30u:
        if ( (_BYTE)v18 == 32 || (_BYTE)v18 == 9 )
        {
          ++v15;
          v10 = 46;
          goto LABEL_39;
        }
        switch ( ((*((_BYTE *)a1 + 1) >> 1) + 118) & 0x7F )
        {
          case 0:
            a3 = v195;
            v20 = v15;
            v6 = v14;
            v8 = a1;
            *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x19;
            v21 = 48;
            goto LABEL_29;
          case 0xD:
            *((_WORD *)a1 + 2) |= 1u;
            goto LABEL_420;
          case 0xE:
            *((_WORD *)a1 + 2) |= 2u;
            goto LABEL_420;
          case 0xF:
            *((_WORD *)a1 + 2) |= 4u;
            goto LABEL_420;
          case 0x10:
            *((_WORD *)a1 + 2) |= 8u;
            goto LABEL_420;
          default:
LABEL_420:
            v105 = (unsigned __int8 *)v191;
            if ( !v191 )
              v105 = v15;
            v192 = (char *)v105;
            if ( (v17 & 0x7F) != 0 )
              __assert_fail(
                "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x6F9u,
                "http_parser_execute");
            a4 = v184[4];
            if ( a4 )
            {
              v106 = *(_WORD *)a1 & 0xFE03;
              LOBYTE(v106) = *(_BYTE *)a1 & 3 | 0xB0;
              *(_WORD *)a1 = v106;
              a2 = (unsigned __int64)v192;
              if ( ((unsigned int (__fastcall *)(unsigned int *, char *, signed __int64))a4)(
                     a1,
                     v192,
                     v15 - (unsigned __int8 *)v192) )
              {
                v155 = *((_BYTE *)a1 + 31);
                a1[2] = v14;
                *((_BYTE *)a1 + 31) = v155 & 0x80 | 4;
              }
              v17 = *((unsigned __int8 *)a1 + 31);
              v10 = (*(_WORD *)a1 >> 2) & 0x7F;
              if ( (v17 & 0x7F) != 0 )
                return v15 - (unsigned __int8 *)v195;
              v191 = 0LL;
            }
            else
            {
              v191 = 0LL;
LABEL_133:
              if ( (_BYTE)v18 == 13 )
              {
                ++v15;
                v10 = 57;
                goto LABEL_39;
              }
              if ( (_BYTE)v18 != 10 )
              {
                if ( (_BYTE)v18 == 32 || (v170 = byte_7B60[(unsigned __int8)v18]) == 0 )
                {
                  a3 = v195;
                  v20 = v15;
                  v6 = v14;
                  v8 = a1;
                  *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x18;
                  v21 = 44;
                  goto LABEL_29;
                }
                v171 = (unsigned __int8 *)v198;
                if ( !v198 )
                  v171 = v15;
                *((_BYTE *)a1 + 2) &= 0x80u;
                ++v15;
                v198 = (char *)v171;
                if ( v170 == 116 )
                {
                  v10 = 45;
                  *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 0xE;
                }
                else if ( v170 > 116 )
                {
                  if ( v170 != 117 )
                    goto LABEL_780;
                  v10 = 45;
                  *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 0x10;
                }
                else if ( v170 == 99 )
                {
                  v10 = 45;
                  *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 2;
                }
                else
                {
                  if ( v170 == 112 )
                  {
                    v10 = 45;
                    *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 0xA;
                    goto LABEL_39;
                  }
LABEL_780:
                  *((_BYTE *)a1 + 1) &= 1u;
                  v10 = 45;
                }
LABEL_39:
                if ( v15 == v13 )
                {
                  LOBYTE(v5) = v17;
                  a3 = v195;
                  v6 = v14;
                  v8 = a1;
                  v12 = v13;
                  goto LABEL_41;
                }
                continue;
              }
LABEL_135:
              v48 = *((_WORD *)a1 + 2);
              if ( (v48 & 0x10) == 0 )
              {
                if ( (v48 & 0x180) == 0x180 && (!v185 || (v48 & 1) != 0) )
                {
                  a3 = v195;
                  v20 = v15;
                  v6 = v14;
                  v8 = a1;
                  *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1A;
                  v21 = 57;
                  goto LABEL_29;
                }
                v116 = v48 & 0x28;
                if ( (_WORD)v116 == 40 )
                {
                  v116 = 1;
                  if ( (*(_BYTE *)a1 & 3) != 0 )
                    LOBYTE(v116) = *((_WORD *)a1 + 14) == 101;
                }
                else
                {
                  LOBYTE(v116) = *((_BYTE *)a1 + 30) == 5;
                }
                v117 = (unsigned int)(v116 << 7);
                *((_BYTE *)a1 + 31) = ((_BYTE)v116 << 7) | *((_BYTE *)a1 + 31) & 0x7F;
                v118 = (__int64 (__fastcall *)(unsigned int *, unsigned __int64, __int64, __int64, unsigned __int64, __int64))v184[5];
                if ( !v118 )
                  goto LABEL_540;
                v119 = v118(a1, a2, v117, a4, v5, v17);
                if ( v119 != 1 )
                {
                  if ( v119 != 2 )
                  {
                    if ( v119 )
                    {
                      v120 = *((_BYTE *)a1 + 31);
                      v121 = v15;
                      v122 = v195;
                      a1[2] = v14;
                      v123 = a1;
                      v124 = v120 & 0x80 | 5;
                      goto LABEL_496;
                    }
LABEL_540:
                    v17 = *((unsigned __int8 *)a1 + 31);
                    if ( (v17 & 0x7F) != 0 )
                    {
                      v121 = v15;
                      v134 = v14;
                      v122 = v195;
                      v123 = a1;
                      a1[2] = v134;
                      goto LABEL_497;
                    }
LABEL_311:
                    v73 = *((unsigned __int16 *)a1 + 2);
                    a1[2] = 0;
                    v7 = 1LL;
                    a4 = v73;
                    LOWORD(a4) = v73 & 1;
                    if ( (v73 & 1) == 0 )
                      v7 = (unsigned __int64)(*((_QWORD *)a1 + 2) - 1LL) <= 0xFFFFFFFFFFFFFFFDLL;
                    if ( (v17 & 0x80u) == 0LL )
                    {
                      if ( (v73 & 0x40) != 0 )
                      {
                        if ( (unsigned int)sub_2540(a1, a2, v7, a4, v5, v17) )
                          v10 = (*(_BYTE *)a1 & 3) == 0 ? 18 : 4;
                        if ( (_BYTE)v17 )
                          __assert_fail(
                            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                            0x75Cu,
                            "http_parser_execute");
                        a4 = v184[7];
                        if ( a4 )
                        {
                          *(_WORD *)a1 = (4 * (v10 & 0x7F)) | *(_WORD *)a1 & 0xFE03;
                          if ( ((unsigned int (__fastcall *)(unsigned int *))a4)(a1) )
                          {
                            v161 = *((_BYTE *)a1 + 31);
                            a1[2] = 0;
                            *((_BYTE *)a1 + 31) = v161 & 0x80 | 7;
                          }
                          v17 = *((unsigned __int8 *)a1 + 31);
                          v10 = (*(_WORD *)a1 >> 2) & 0x7F;
                          if ( (v17 & 0x7F) != 0 )
                            goto LABEL_481;
                          ++v15;
                          v14 = 0;
                        }
                        else
                        {
                          ++v15;
                          v14 = 0;
                        }
                        goto LABEL_39;
                      }
LABEL_524:
                      if ( (v73 & 1) != 0 )
                      {
                        ++v15;
                        v14 = 0;
                        v10 = 53;
                        goto LABEL_39;
                      }
                      if ( (v73 & 0x100) == 0 )
                      {
                        v149 = *((_QWORD *)a1 + 2);
                        if ( v149 )
                        {
                          if ( v149 == -1 )
                          {
                            if ( (unsigned int)sub_24D0(a1, a2, v7) )
                            {
                              ++v15;
                              v14 = 0;
                              v10 = 63;
                            }
                            else
                            {
                              v176 = sub_2540(a1, a2, v7, a4, v5, v17);
                              v10 = 1;
                              if ( v176 )
                                v10 = (*(_BYTE *)a1 & 3) == 0 ? 18 : 4;
                              if ( (v17 & 0x7F) != 0 )
                                __assert_fail(
                                  "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                                  "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                                  0x783u,
                                  "http_parser_execute");
                              a4 = v184[7];
                              if ( a4 )
                              {
                                *(_WORD *)a1 = (4 * (v10 & 0x7F)) | *(_WORD *)a1 & 0xFE03;
                                if ( ((unsigned int (__fastcall *)(unsigned int *))a4)(a1) )
                                {
                                  v180 = *((_BYTE *)a1 + 31);
                                  a1[2] = 0;
                                  *((_BYTE *)a1 + 31) = v180 & 0x80 | 7;
                                }
                                v17 = *((unsigned __int8 *)a1 + 31);
                                v10 = (*(_WORD *)a1 >> 2) & 0x7F;
                                if ( (v17 & 0x7F) != 0 )
                                  goto LABEL_481;
                                ++v15;
                                v14 = 0;
                              }
                              else
                              {
                                ++v15;
                                v14 = 0;
                              }
                            }
                          }
                          else
                          {
                            ++v15;
                            v14 = 0;
                            v10 = 62;
                          }
                        }
                        else
                        {
                          if ( (unsigned int)sub_2540(a1, a2, v7, a4, v5, v17) )
                            v10 = (*(_BYTE *)a1 & 3) == 0 ? 18 : 4;
                          if ( (v17 & 0x7F) != 0 )
                            __assert_fail(
                              "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                              "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                              0x77Bu,
                              "http_parser_execute");
                          a4 = v184[7];
                          if ( a4 )
                          {
                            *(_WORD *)a1 = (4 * (v10 & 0x7F)) | *(_WORD *)a1 & 0xFE03;
                            if ( ((unsigned int (__fastcall *)(unsigned int *))a4)(a1) )
                            {
                              v177 = *((_BYTE *)a1 + 31);
                              a1[2] = 0;
                              *((_BYTE *)a1 + 31) = v177 & 0x80 | 7;
                            }
                            v17 = *((unsigned __int8 *)a1 + 31);
                            v10 = (*(_WORD *)a1 >> 2) & 0x7F;
                            if ( (v17 & 0x7F) != 0 )
                              goto LABEL_481;
                            ++v15;
                            v14 = 0;
                          }
                          else
                          {
                            ++v15;
                            v14 = 0;
                          }
                        }
                        goto LABEL_39;
                      }
                      if ( (*(_BYTE *)a1 & 3) != 0 || v185 )
                      {
                        ++v15;
                        v14 = 0;
                        v10 = 63;
                        goto LABEL_39;
                      }
                      v122 = v195;
                      v121 = v15;
                      v123 = a1;
                      v124 = *((_BYTE *)a1 + 31) & 0x80 | 0x1C;
LABEL_496:
                      *((_BYTE *)v123 + 31) = v124;
LABEL_497:
                      v125 = *(_WORD *)v123 & 0xFE03;
                      LOBYTE(v125) = v125 | 0xE8;
                      *(_WORD *)v123 = v125;
                      return v121 - (unsigned __int8 *)v122;
                    }
                    if ( *((_BYTE *)a1 + 30) != 5 && (v73 & 0x40) == 0 && (_DWORD)v7 )
                      goto LABEL_524;
                    v182 = v17;
                    v115 = v15;
                    v126 = a1;
                    v127 = sub_2540(a1, a2, v7, a4, v5, v195);
                    LOBYTE(v128) = 1;
                    if ( v127 )
                      LOBYTE(v128) = (*(_BYTE *)a1 & 3) == 0 ? 18 : 4;
                    if ( (v182 & 0x7F) != 0 )
                      __assert_fail(
                        "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                        "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                        0x756u,
                        "http_parser_execute");
                    v129 = (__int64 (__fastcall *)(unsigned int *))v184[7];
                    if ( !v129 )
                      goto LABEL_536;
                    v183 = v114;
                    *(_WORD *)a1 = (4 * (v128 & 0x7F)) | *(_WORD *)a1 & 0xFE03;
                    v130 = v129(a1);
                    v114 = v183;
                    if ( v130 )
                    {
                      v178 = *((_BYTE *)a1 + 31);
                      a1[2] = 0;
                      *((_BYTE *)a1 + 31) = v178 & 0x80 | 7;
                    }
                    v128 = (*(_WORD *)a1 >> 2) & 0x7F;
                    if ( (*((_BYTE *)a1 + 31) & 0x7F) == 0 )
                    {
LABEL_536:
                      v131 = *(_WORD *)a1;
                      a1[2] = 0;
                      v132 = 4 * (v128 & 0x7F);
                      v133 = v131 & 0xFE03;
                      goto LABEL_537;
                    }
                    return (__int64)&v115[-v114 + 1];
                  }
                  *((_BYTE *)a1 + 31) |= 0x80u;
                }
                *((_WORD *)a1 + 2) |= 0x40u;
                goto LABEL_540;
              }
              if ( (v17 & 0x7F) != 0 )
                __assert_fail(
                  "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                  "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                  0x705u,
                  "http_parser_execute");
              v7 = v184[9];
              if ( !v7 )
              {
                a4 = (__int64)v15;
LABEL_676:
                v15 = (unsigned __int8 *)a4;
                if ( (unsigned int)sub_2540(a1, a2, v7, a4, v5, v17) )
                {
LABEL_296:
                  v10 = (*(_BYTE *)a1 & 3) == 0 ? 18 : 4;
LABEL_297:
                  if ( (v17 & 0x7F) != 0 )
                    __assert_fail(
                      "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                      "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                      0x7BBu,
                      "http_parser_execute");
                }
                v7 = v184[7];
                if ( !v7 )
                  goto LABEL_302;
                *(_WORD *)a1 = (4 * (v10 & 0x7F)) | *(_WORD *)a1 & 0xFE03;
                if ( ((unsigned int (__fastcall *)(unsigned int *))v7)(a1) )
                {
                  v152 = *((_BYTE *)a1 + 31);
                  a1[2] = v14;
                  *((_BYTE *)a1 + 31) = v152 & 0x80 | 7;
                }
                v17 = *((unsigned __int8 *)a1 + 31);
                v10 = (*(_WORD *)a1 >> 2) & 0x7F;
                if ( (v17 & 0x7F) == 0 )
                {
LABEL_302:
                  if ( (v17 & 0x80u) == 0LL )
                  {
                    ++v15;
                    goto LABEL_39;
                  }
                  v174 = *(_WORD *)a1;
                  v115 = v15;
                  a1[2] = v14;
                  v114 = (__int64)v195;
                  v126 = a1;
                  v133 = 4 * (v10 & 0x7F);
                  v132 = v174 & 0xFE03;
LABEL_537:
                  *(_WORD *)v126 = v133 | v132;
                  return (__int64)&v115[-v114 + 1];
                }
LABEL_481:
                v114 = (__int64)v195;
                v115 = v15;
                return (__int64)&v115[-v114 + 1];
              }
              v49 = *(_WORD *)a1 & 0xFE03;
              HIBYTE(v49) |= 1u;
              *(_WORD *)a1 = v49;
              if ( ((unsigned int (__fastcall *)(unsigned int *))v7)(a1) )
              {
                v163 = *((_BYTE *)a1 + 31);
                a1[2] = v14;
                *((_BYTE *)a1 + 31) = v163 & 0x80 | 0xA;
              }
              v17 = *((unsigned __int8 *)a1 + 31);
              v10 = (*(_WORD *)a1 >> 2) & 0x7F;
              if ( (v17 & 0x7F) != 0 )
                return v15 - (unsigned __int8 *)v195;
              v18 = 10LL;
            }
            break;
        }
        goto LABEL_21;
      case 0x31u:
        v43 = *((_BYTE *)a1 + 1) >> 1;
        goto LABEL_325;
      case 0x32u:
        a2 = (unsigned int)dword_B010;
        v66 = *((_BYTE *)a1 + 1) >> 1;
        if ( v15 == v13 )
          goto LABEL_259;
        v5 = (unsigned __int64)v15;
        a4 = v185 ^ 1u;
        while ( 2 )
        {
          v18 = (unsigned int)*(char *)v5;
          if ( *(_BYTE *)v5 != 13 )
          {
            if ( *(_BYTE *)v5 != 10 )
            {
              if ( *(_BYTE *)v5 != 9 && v185 != 1 && (*(_BYTE *)v5 <= 0x1Fu || *(_BYTE *)v5 == 127) )
              {
LABEL_632:
                a3 = v195;
                v6 = v14;
                v20 = (unsigned __int8 *)v5;
                v8 = a1;
                *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x18;
                v21 = 50;
                goto LABEL_29;
              }
              v7 = (unsigned int)v18 | 0x20;
              switch ( v66 )
              {
                case 0:
                  v99 = &v13[-v5];
                  if ( (unsigned __int64)&v13[-v5] > (unsigned int)a2 )
                    v99 = (unsigned __int8 *)(unsigned int)a2;
                  v7 = (unsigned __int64)&v99[v5];
                  if ( (unsigned __int8 *)v5 == &v99[v5] )
                    goto LABEL_410;
                  while ( 2 )
                  {
                    if ( (_BYTE)v18 != 9 && v185 != 1 && ((unsigned __int8)v18 <= 0x1Fu || (_BYTE)v18 == 127) )
                      goto LABEL_632;
                    if ( v7 == v5 + 1 )
                    {
                      v5 = v7;
                    }
                    else
                    {
                      LOBYTE(v18) = *(_BYTE *)(v5 + 1);
                      if ( (_BYTE)v18 != 13 && (_BYTE)v18 != 10 )
                      {
                        ++v5;
                        continue;
                      }
                    }
                    break;
                  }
LABEL_410:
                  if ( (unsigned __int8 *)v5 == v13 )
                    goto LABEL_259;
LABEL_394:
                  ++v5;
                  goto LABEL_258;
                case 9:
                case 13:
                  __assert_fail(
                    "0 && \"Shouldn't get here.\"",
                    "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                    0x5F9u,
                    "http_parser_execute");
                case 10:
                  if ( *(_BYTE *)v5 != 32 )
                    goto LABEL_413;
                  goto LABEL_394;
                case 11:
                  if ( *(_BYTE *)v5 == 32 )
                  {
                    ++v5;
                    v66 = 12;
                  }
                  else
                  {
LABEL_413:
                    v100 = *(_BYTE *)v5 - 48;
                    if ( v100 > 9u
                      || (v101 = *((_QWORD *)a1 + 2), v7 = (char)v100 + 10 * v101, v101 > 0x1999999999999998LL) )
                    {
                      a3 = v195;
                      v6 = v14;
                      v20 = (unsigned __int8 *)v5;
                      v8 = a1;
                      *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x19;
                      *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 0x16;
                      v21 = 50;
                      goto LABEL_29;
                    }
                    *((_QWORD *)a1 + 2) = v7;
                    ++v5;
                    v66 = 11;
                  }
LABEL_258:
                  if ( (unsigned __int8 *)v5 != v13 )
                    continue;
LABEL_259:
                  v7 = *((_BYTE *)a1 + 1) & 1;
                  *((_BYTE *)a1 + 1) = v7 | (2 * v66);
                  break;
                case 12:
                  if ( *(_BYTE *)v5 == 32 )
                    goto LABEL_394;
                  a3 = v195;
                  v6 = v14;
                  v20 = (unsigned __int8 *)v5;
                  v8 = a1;
                  *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x19;
                  *((_BYTE *)a1 + 1) = *((_BYTE *)a1 + 1) & 1 | 0x18;
                  v21 = 50;
                  goto LABEL_29;
                case 15:
                  ++v5;
                  if ( ((unsigned __int8)v18 | 0x20) == 0x63 )
                  {
                    v66 = 16;
                  }
                  else if ( ((unsigned __int8)v18 | 0x20) != 0x20 )
                  {
                    v7 = (unsigned __int8)v18 | 0x20u;
                    v66 = byte_7B60[(unsigned __int8)v7] != 0 ? 0x11 : 0;
                  }
                  goto LABEL_258;
                case 16:
                  v102 = *((_BYTE *)a1 + 2);
                  ++v5;
                  v103 = (v102 + 1) & 0x7F;
                  v104 = v103 | v102 & 0x80;
                  *((_BYTE *)a1 + 2) = v104;
                  if ( v103 <= 7u && aChunked[v103 & 0x7F] == (_BYTE)v7 )
                  {
                    if ( (v104 & 0x7F) == 6 )
                      v66 = 23;
                  }
                  else
                  {
                    v66 = 17;
                  }
                  goto LABEL_258;
                case 17:
                  ++v5;
                  if ( (_BYTE)v18 == 44 )
                  {
                    *((_BYTE *)a1 + 2) &= 0x80u;
                    v66 = 15;
                  }
                  goto LABEL_258;
                case 18:
                  ++v5;
                  switch ( (unsigned __int8)v18 | 0x20 )
                  {
                    case 'k':
                      v66 = 19;
                      break;
                    case 'c':
                      v66 = 20;
                      break;
                    case 'u':
                      v66 = 21;
                      break;
                    default:
                      if ( ((unsigned __int8)v18 | 0x20) != 0x20 )
                      {
                        v7 = (unsigned __int8)v18 | 0x20u;
                        v66 = byte_7B60[(unsigned __int8)v7] != 0 ? 0x16 : 0;
                      }
                      break;
                  }
                  goto LABEL_258;
                case 19:
                  v96 = *((_BYTE *)a1 + 2);
                  ++v5;
                  v97 = (v96 + 1) & 0x7F;
                  v98 = v97 | v96 & 0x80;
                  *((_BYTE *)a1 + 2) = v98;
                  if ( v97 > 0xAu || aKeepAlive[v97 & 0x7F] != (_BYTE)v7 )
                    goto LABEL_372;
                  if ( (v98 & 0x7F) == 9 )
                    v66 = 24;
                  goto LABEL_258;
                case 20:
                  v93 = *((_BYTE *)a1 + 2);
                  ++v5;
                  v94 = (v93 + 1) & 0x7F;
                  v95 = v94 | v93 & 0x80;
                  *((_BYTE *)a1 + 2) = v95;
                  if ( v94 > 5u || aClose[v94 & 0x7F] != (_BYTE)v7 )
                    goto LABEL_372;
                  if ( (v95 & 0x7F) == 4 )
                    v66 = 25;
                  goto LABEL_258;
                case 21:
                  v90 = *((_BYTE *)a1 + 2);
                  ++v5;
                  v91 = (v90 + 1) & 0x7F;
                  v92 = v91 | v90 & 0x80;
                  *((_BYTE *)a1 + 2) = v92;
                  if ( v91 <= 7u && aUpgrade[v91 & 0x7F] == (_BYTE)v7 )
                  {
                    if ( (v92 & 0x7F) == 6 )
                      v66 = 26;
                  }
                  else
                  {
LABEL_372:
                    v66 = 22;
                  }
                  goto LABEL_258;
                case 22:
                  ++v5;
                  if ( (_BYTE)v18 == 44 )
                    goto LABEL_369;
                  goto LABEL_258;
                case 23:
                  ++v5;
                  if ( (_BYTE)v18 != 32 )
                    v66 = 17;
                  goto LABEL_258;
                case 24:
                case 25:
                case 26:
                  ++v5;
                  if ( (_BYTE)v18 == 44 )
                  {
                    v136 = *((_WORD *)a1 + 2);
                    if ( v66 == 24 )
                    {
                      v137 = v136 | 2;
                    }
                    else
                    {
                      v137 = v136 | 8;
                      v7 = *((unsigned __int16 *)a1 + 2) | 4u;
                      if ( v66 == 25 )
                        v137 = *((_WORD *)a1 + 2) | 4;
                    }
                    *((_WORD *)a1 + 2) = v137;
LABEL_369:
                    *((_BYTE *)a1 + 2) &= 0x80u;
                    v66 = 18;
                  }
                  else if ( (_BYTE)v18 != 32 )
                  {
                    v66 = 22;
                  }
                  goto LABEL_258;
                default:
                  ++v5;
                  v66 = 0;
                  goto LABEL_258;
              }
LABEL_260:
              v5 = (unsigned __int64)(v13 - 1);
LABEL_261:
              v14 += v5 - (_DWORD)v15;
              if ( v14 <= (unsigned int)a2 )
              {
                v15 = (unsigned __int8 *)(v5 + 1);
                goto LABEL_39;
              }
              a3 = v195;
              v6 = v14;
              v20 = (unsigned __int8 *)v5;
              v8 = a1;
              *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xC;
              v21 = v10 & 0x7F;
              goto LABEL_29;
            }
            v14 += v5 - (_DWORD)v15;
            if ( v14 > (unsigned int)a2 )
            {
              a3 = v195;
              v6 = v14;
              v20 = (unsigned __int8 *)v5;
              v8 = a1;
              *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0xC;
              v21 = 52;
              goto LABEL_29;
            }
            *((_BYTE *)a1 + 1) = (2 * v66) | *((_BYTE *)a1 + 1) & 1;
            if ( (v17 & 0x7F) != 0 )
              __assert_fail(
                "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x5D6u,
                "http_parser_execute");
            if ( !v191 )
            {
              v15 = (unsigned __int8 *)(v5 + 1);
              v10 = 51;
              goto LABEL_39;
            }
            a4 = v184[4];
            if ( !a4 )
            {
              v191 = 0LL;
              v15 = (unsigned __int8 *)(v5 + 1);
              v10 = 51;
              goto LABEL_39;
            }
            v139 = *(_WORD *)a1 & 0xFE03;
            LOBYTE(v139) = *(_BYTE *)a1 & 3 | 0xD0;
            *(_WORD *)a1 = v139;
            a2 = (unsigned __int64)v191;
            v201 = (unsigned __int8 *)v5;
            v140 = ((__int64 (__fastcall *)(unsigned int *, char *, unsigned __int64))a4)(a1, v191, v5 - (_QWORD)v191);
            v5 = (unsigned __int64)v201;
            if ( v140 )
            {
              v175 = *((_BYTE *)a1 + 31);
              a1[2] = v14;
              *((_BYTE *)a1 + 31) = v175 & 0x80 | 4;
            }
            v17 = *((unsigned __int8 *)a1 + 31);
            v10 = (*(_WORD *)a1 >> 2) & 0x7F;
            if ( (v17 & 0x7F) != 0 )
              return v201 - (unsigned __int8 *)v195;
            v191 = 0LL;
            v15 = v201;
            goto LABEL_21;
          }
          break;
        }
        v141 = v66 & 0x7F;
        v142 = (2 * v66) | *((_BYTE *)a1 + 1) & 1;
        *((_BYTE *)a1 + 1) = v142;
        if ( (v17 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x5CEu,
            "http_parser_execute");
        v143 = v191;
        if ( !v191 || (v144 = (__int64 (__fastcall *)(unsigned int *, char *, unsigned __int64, __int64))v184[4]) == 0LL )
        {
          v10 = 52;
LABEL_614:
          v191 = 0LL;
          v7 = (2 * v141) | v142 & 1u;
          *((_BYTE *)a1 + 1) = v7;
          if ( (unsigned __int8 *)v5 != v13 )
            goto LABEL_261;
          goto LABEL_260;
        }
        v145 = v191;
        v146 = *(_WORD *)a1 & 0xFE03;
        LOBYTE(v146) = v146 | 0xD0;
        *(_WORD *)a1 = v146;
        v193 = (char *)v5;
        v147 = v144(a1, v145, v5 - (_QWORD)v143, a4);
        v5 = (unsigned __int64)v193;
        if ( v147 )
        {
          v173 = *((_BYTE *)a1 + 31);
          a1[2] = v14;
          *((_BYTE *)a1 + 31) = v173 & 0x80 | 4;
        }
        v17 = *((unsigned __int8 *)a1 + 31);
        v10 = (*(_WORD *)a1 >> 2) & 0x7F;
        if ( (v17 & 0x7F) == 0 )
        {
          a2 = (unsigned int)dword_B010;
          v142 = *((_BYTE *)a1 + 1);
          goto LABEL_614;
        }
        return v193 - v195 + 1;
      case 0x33u:
        v42 = *((unsigned __int8 *)a1 + 1);
        if ( (_BYTE)v18 == 32 || (_BYTE)v18 == 9 )
        {
          v7 = v42 & 0xFFFFFFFE;
          if ( (v42 & 0xFE) == 0x16 )
          {
            *((_BYTE *)a1 + 1) = v42 & 1 | 0x18;
            *((_BYTE *)a1 + 2) &= 0x80u;
            if ( !v191 )
              v191 = (char *)v15;
LABEL_433:
            ++v15;
            v10 = 50;
          }
          else
          {
LABEL_95:
            v43 = (unsigned __int8)v42 >> 1;
LABEL_325:
            a2 = (unsigned __int64)v191;
            if ( !v191 )
              a2 = (unsigned __int64)v15;
            *((_BYTE *)a1 + 2) &= 0x80u;
            v7 = (unsigned int)v18 | 0x20;
            v191 = (char *)a2;
            switch ( (v43 + 119) & 0x7F )
            {
              case 0:
                ++v15;
                v108 = *((_BYTE *)a1 + 1) & 1;
                if ( ((unsigned __int8)v18 | 0x20) == 0x6B )
                {
                  v10 = 50;
                  *((_BYTE *)a1 + 1) = v108 | 0x26;
                }
                else if ( ((unsigned __int8)v18 | 0x20) == 0x63 )
                {
                  v10 = 50;
                  *((_BYTE *)a1 + 1) = v108 | 0x28;
                }
                else
                {
                  v10 = 50;
                  if ( ((unsigned __int8)v18 | 0x20) == 0x75 )
                    *((_BYTE *)a1 + 1) = v108 | 0x2A;
                  else
                    *((_BYTE *)a1 + 1) = v108 | 0x2C;
                }
                goto LABEL_39;
              case 1:
                v109 = v18 - 48;
                if ( v109 > 9u )
                {
                  a3 = v195;
                  v20 = v15;
                  v6 = v14;
                  v8 = a1;
                  *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x19;
                  v21 = 50;
                  goto LABEL_29;
                }
                v110 = *((_WORD *)a1 + 2);
                if ( (v110 & 0x80u) != 0 )
                {
                  a3 = v195;
                  v20 = v15;
                  v6 = v14;
                  v8 = a1;
                  *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1A;
                  v21 = 50;
                  goto LABEL_29;
                }
                LOBYTE(v110) = v110 | 0x80;
                ++v15;
                v10 = 50;
                *((_WORD *)a1 + 2) = v110;
                v111 = *((_BYTE *)a1 + 1);
                *((_QWORD *)a1 + 2) = (char)v109;
                *((_BYTE *)a1 + 1) = v111 & 1 | 0x16;
                break;
              case 3:
              case 6:
              case 9:
                goto LABEL_433;
              case 4:
                ++v15;
                v112 = *((_BYTE *)a1 + 1) & 1;
                v10 = 50;
                if ( ((unsigned __int8)v18 | 0x20) == 0x63 )
                  *((_BYTE *)a1 + 1) = v112 | 0x20;
                else
                  *((_BYTE *)a1 + 1) = v112 | 0x22;
                goto LABEL_39;
              case 5:
                *((_WORD *)a1 + 2) |= 0x20u;
                ++v15;
                v10 = 50;
                *((_BYTE *)a1 + 1) &= 1u;
                goto LABEL_39;
              default:
                *((_BYTE *)a1 + 1) &= 1u;
                ++v15;
                v10 = 50;
                goto LABEL_39;
            }
          }
          goto LABEL_39;
        }
        v47 = (unsigned __int8)v42 >> 1;
        if ( v47 == 25 )
        {
          *((_WORD *)a1 + 2) |= 4u;
        }
        else if ( v47 > 0x19u )
        {
          if ( v47 == 26 )
            *((_WORD *)a1 + 2) |= 8u;
        }
        else if ( v47 == 23 )
        {
          *((_WORD *)a1 + 2) |= 1u;
        }
        else if ( v47 == 24 )
        {
          *((_WORD *)a1 + 2) |= 2u;
        }
        goto LABEL_133;
      case 0x34u:
        if ( (_BYTE)v18 == 10 )
        {
          ++v15;
          v10 = 51;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x17;
        v21 = 52;
        goto LABEL_29;
      case 0x35u:
        if ( v14 != 1 )
          __assert_fail(
            "nread == 1",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7C4u,
            "http_parser_execute");
        if ( (a1[1] & 1) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7C5u,
            "http_parser_execute");
        v69 = byte_7A60[(unsigned __int8)v18];
        if ( (_BYTE)v69 != 0xFF )
        {
          *((_QWORD *)a1 + 2) = v69;
          ++v15;
          v10 = 54;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = 1;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1B;
        v21 = 53;
        goto LABEL_29;
      case 0x36u:
        if ( (a1[1] & 1) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7D6u,
            "http_parser_execute");
        if ( (_BYTE)v18 == 13 )
        {
          ++v15;
          v10 = 56;
          goto LABEL_39;
        }
        v7 = (unsigned __int64)byte_7A60;
        v64 = byte_7A60[(unsigned __int8)v18];
        if ( (_BYTE)v64 == 0xFF )
        {
          if ( (_BYTE)v18 != 59 && (_BYTE)v18 != 32 )
          {
            a3 = v195;
            v20 = v15;
            v6 = v14;
            v8 = a1;
            *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1B;
            v21 = 54;
            goto LABEL_29;
          }
          ++v15;
          v10 = 55;
          goto LABEL_39;
        }
        v7 = *((_QWORD *)a1 + 2);
        v65 = 16 * v7 + v64;
        a4 = 0xFFFFFFFFFFFFFFELL;
        if ( v7 <= 0xFFFFFFFFFFFFFFELL )
        {
          *((_QWORD *)a1 + 2) = v65;
          ++v15;
          goto LABEL_39;
        }
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x19;
        v21 = 54;
        goto LABEL_29;
      case 0x37u:
        if ( (a1[1] & 1) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7F9u,
            "http_parser_execute");
        ++v15;
        if ( (_BYTE)v18 == 13 )
          v10 = 56;
        goto LABEL_39;
      case 0x38u:
        v45 = *((_WORD *)a1 + 2);
        if ( (v45 & 1) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x804u,
            "http_parser_execute");
        if ( (_BYTE)v18 != 10 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 56;
          goto LABEL_29;
        }
        v46 = *((_QWORD *)a1 + 2) == 0LL;
        a1[2] = 0;
        v10 = 59;
        if ( v46 )
        {
          v10 = 44;
          *((_WORD *)a1 + 2) = v45 | 0x10;
        }
        if ( (v17 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x810u,
            "http_parser_execute");
        v7 = v184[8];
        if ( v7 )
        {
          *(_WORD *)a1 = (4 * (v10 & 0x7F)) | *(_WORD *)a1 & 0xFE03;
          if ( ((unsigned int (__fastcall *)(unsigned int *))v7)(a1) )
          {
            v151 = *((_BYTE *)a1 + 31);
            a1[2] = 0;
            *((_BYTE *)a1 + 31) = v151 & 0x80 | 9;
          }
          v17 = *((unsigned __int8 *)a1 + 31);
          v10 = (*(_WORD *)a1 >> 2) & 0x7F;
          if ( (v17 & 0x7F) != 0 )
            goto LABEL_481;
          ++v15;
          v14 = 0;
        }
        else
        {
          ++v15;
          v14 = 0;
        }
        goto LABEL_39;
      case 0x39u:
        if ( (_BYTE)v18 == 10 )
          goto LABEL_135;
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
        v21 = 57;
        goto LABEL_29;
      case 0x3Au:
        if ( (_BYTE)v18 == 10 )
          goto LABEL_311;
        a3 = v195;
        v20 = v15;
        v6 = v14;
        v8 = a1;
        *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
        v21 = 58;
        goto LABEL_29;
      case 0x3Bu:
        v67 = *((_QWORD *)a1 + 2);
        v7 = v13 - v15;
        if ( v13 - v15 > v67 )
          v7 = *((_QWORD *)a1 + 2);
        if ( (a1[1] & 1) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x819u,
            "http_parser_execute");
        a4 = v67 - 1;
        if ( v67 - 1 > 0xFFFFFFFFFFFFFFFDLL )
          __assert_fail(
            "parser->content_length != 0 && parser->content_length != ULLONG_MAX",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x81Au,
            "http_parser_execute");
        a2 = (unsigned __int64)v194;
        if ( !v194 )
          a2 = (unsigned __int64)v15;
        v68 = v67 - v7;
        v15 += v7;
        *((_QWORD *)a1 + 2) = v68;
        v194 = (char *)a2;
        if ( !v68 )
          v10 = 60;
        goto LABEL_39;
      case 0x3Cu:
        if ( (a1[1] & 1) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x82Cu,
            "http_parser_execute");
        if ( *((_QWORD *)a1 + 2) )
          __assert_fail(
            "parser->content_length == 0",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x82Du,
            "http_parser_execute");
        if ( (_BYTE)v18 != 13 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 60;
          goto LABEL_29;
        }
        if ( (v17 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x830u,
            "http_parser_execute");
        if ( v194 )
        {
          a4 = v184[6];
          if ( a4 )
          {
            v62 = *(_WORD *)a1 & 0xFE03;
            LOBYTE(v62) = *(_BYTE *)a1 & 3 | 0xF4;
            *(_WORD *)a1 = v62;
            a2 = (unsigned __int64)v194;
            if ( ((unsigned int (__fastcall *)(unsigned int *, char *, signed __int64))a4)(
                   a1,
                   v194,
                   v15 - (unsigned __int8 *)v194) )
            {
              v157 = *((_BYTE *)a1 + 31);
              a1[2] = v14;
              *((_BYTE *)a1 + 31) = v157 & 0x80 | 6;
            }
            v17 = *((unsigned __int8 *)a1 + 31);
            v10 = (*(_WORD *)a1 >> 2) & 0x7F;
            if ( (v17 & 0x7F) != 0 )
              goto LABEL_481;
            v194 = 0LL;
            ++v15;
          }
          else
          {
            v194 = 0LL;
            ++v15;
            v10 = 61;
          }
        }
        else
        {
          ++v15;
          v10 = 61;
        }
        goto LABEL_39;
      case 0x3Du:
        if ( (a1[1] & 1) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x834u,
            "http_parser_execute");
        if ( (_BYTE)v18 != 10 )
        {
          a3 = v195;
          v20 = v15;
          v6 = v14;
          v8 = a1;
          *((_BYTE *)a1 + 31) = *((_BYTE *)a1 + 31) & 0x80 | 0x1F;
          v21 = 61;
          goto LABEL_29;
        }
        a1[2] = 0;
        if ( (v17 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x839u,
            "http_parser_execute");
        v7 = v184[9];
        if ( v7 )
        {
          v63 = *(_WORD *)a1 & 0xFE03;
          LOBYTE(v63) = *(_BYTE *)a1 & 3 | 0xD4;
          *(_WORD *)a1 = v63;
          if ( ((unsigned int (__fastcall *)(unsigned int *))v7)(a1) )
          {
            v150 = *((_BYTE *)a1 + 31);
            a1[2] = 0;
            *((_BYTE *)a1 + 31) = v150 & 0x80 | 0xA;
          }
          v17 = *((unsigned __int8 *)a1 + 31);
          v10 = (*(_WORD *)a1 >> 2) & 0x7F;
          if ( (v17 & 0x7F) != 0 )
            goto LABEL_481;
          ++v15;
          v14 = 0;
        }
        else
        {
          ++v15;
          v14 = 0;
          v10 = 53;
        }
        goto LABEL_39;
      case 0x3Eu:
        v55 = *((_QWORD *)a1 + 2);
        v7 = v13 - v15;
        if ( v13 - v15 > v55 )
          v7 = *((_QWORD *)a1 + 2);
        if ( v55 - 1 > 0xFFFFFFFFFFFFFFFDLL )
          __assert_fail(
            "parser->content_length != 0 && parser->content_length != ULLONG_MAX",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x793u,
            "http_parser_execute");
        a2 = (unsigned __int64)v194;
        a4 = (__int64)&v15[v7 - 1];
        if ( !v194 )
          a2 = (unsigned __int64)v15;
        v56 = v55 - v7;
        *((_QWORD *)a1 + 2) = v56;
        v194 = (char *)a2;
        if ( v56 )
        {
          v15 += v7;
          goto LABEL_39;
        }
        if ( (v17 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7ABu,
            "http_parser_execute");
        v5 = v184[6];
        if ( !v5 )
        {
          v194 = 0LL;
          goto LABEL_676;
        }
        v57 = *(_WORD *)a1 & 0xFE03;
        HIBYTE(v57) |= 1u;
        *(_WORD *)a1 = v57;
        v200 = (__int64)&v15[v7 - 1];
        v58 = ((__int64 (__fastcall *)(unsigned int *, unsigned __int64, unsigned __int8 *))v5)(a1, a2, &v15[v7 - a2]);
        a4 = v200;
        if ( v58 )
        {
          v153 = *((_BYTE *)a1 + 31);
          a1[2] = v14;
          *((_BYTE *)a1 + 31) = v153 & 0x80 | 6;
        }
        v17 = *((unsigned __int8 *)a1 + 31);
        v10 = (*(_WORD *)a1 >> 2) & 0x7F;
        if ( (v17 & 0x7F) != 0 )
          return v200 - (_QWORD)v195;
        v194 = 0LL;
        v15 = (unsigned __int8 *)v200;
        goto LABEL_21;
      case 0x3Fu:
        v70 = a1;
        v12 = v13;
        v71 = v15;
        v6 = v14;
        v8 = v70;
        LOBYTE(v5) = v17;
        a3 = v195;
        if ( v194 )
          v71 = (unsigned __int8 *)v194;
        v194 = (char *)v71;
        goto LABEL_41;
      case 0x40u:
        if ( (unsigned int)sub_2540(a1, a2, v7, a4, v5, v17) )
          goto LABEL_296;
        goto LABEL_297;
      default:
        __assert_fail(
          "0 && \"unhandled state\"",
          "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
          0x83Du,
          "http_parser_execute");
    }
  }
}
