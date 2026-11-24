__int64 __fastcall sub_25B0(unsigned __int16 *a1, unsigned __int64 a2, char *a3, __int64 a4)
{
  unsigned __int64 v5; // r8
  unsigned int v6; // r13d
  unsigned __int64 v7; // rdx
  unsigned __int16 *v8; // r15
  __int64 result; // rax
  unsigned int v10; // r11d
  char *v11; // rax
  unsigned __int8 *v12; // r14
  unsigned __int8 *v13; // r12
  unsigned __int8 *v14; // r15
  unsigned int v15; // r14d
  __int64 v16; // r9
  unsigned __int64 v18; // rbx
  unsigned int (__fastcall *v19)(unsigned __int16 *, unsigned __int64, unsigned __int64, __int64, unsigned __int64, char *); // rax
  unsigned __int8 *v20; // r12
  char v21; // al
  char v22; // dl
  int v23; // edx
  __int64 v24; // rax
  _BOOL4 v25; // edx
  int v26; // edx
  __int64 (__fastcall *v27)(unsigned __int16 *, char *, signed __int64); // rax
  int v28; // eax
  __int64 (__fastcall *v29)(unsigned __int16 *, char *, signed __int64); // rax
  int v30; // eax
  __int64 (__fastcall *v31)(unsigned __int16 *, char *, signed __int64); // rax
  int v32; // eax
  __int64 (__fastcall *v33)(unsigned __int16 *, char *, signed __int64); // rax
  int v34; // eax
  __int64 (__fastcall *v35)(unsigned __int16 *, char *, signed __int64); // rcx
  int v36; // eax
  int v37; // eax
  __int64 v38; // rax
  __int64 v39; // rax
  int v40; // eax
  char v41; // al
  int v42; // eax
  __int16 v43; // ax
  __int16 v44; // dx
  bool v45; // zf
  unsigned __int8 v46; // al
  int v47; // eax
  unsigned __int8 *v48; // rbx
  unsigned __int8 v49; // al
  char v50; // dl
  unsigned __int8 *v51; // r12
  unsigned int v52; // r13d
  unsigned __int64 v53; // rax
  unsigned __int64 v54; // rax
  int v55; // eax
  unsigned int v56; // eax
  unsigned __int8 v57; // dl
  int v58; // eax
  unsigned __int8 *v59; // rax
  unsigned int v60; // eax
  unsigned int v61; // eax
  __int64 v62; // rax
  __int64 v63; // rax
  int v64; // edi
  unsigned __int64 v65; // rax
  unsigned __int64 v66; // rax
  unsigned __int16 *v67; // rax
  unsigned __int8 *v68; // r12
  __int64 v69; // rax
  char v70; // al
  unsigned __int16 v71; // ax
  __int16 v72; // ax
  char v73; // al
  char v74; // dl
  signed __int64 v75; // rdx
  unsigned __int8 *v76; // rdx
  __int64 v77; // rax
  int v78; // ecx
  int v79; // eax
  int v80; // ecx
  int v81; // eax
  int v82; // ecx
  int v83; // eax
  char v84; // al
  int v85; // ecx
  int v86; // eax
  int v87; // ecx
  int v88; // eax
  char v89; // al
  unsigned __int8 v90; // bl
  char v91; // al
  char v92; // al
  unsigned __int8 v93; // bl
  char v94; // al
  unsigned __int8 v95; // bl
  unsigned __int64 v96; // rax
  char v97; // al
  unsigned __int8 v98; // bl
  char v99; // al
  unsigned __int8 *v100; // rax
  char v101; // al
  unsigned __int8 v102; // bl
  char v103; // al
  unsigned __int8 *v104; // rax
  unsigned int v105; // eax
  char v106; // al
  unsigned __int8 v107; // bl
  unsigned int v108; // edx
  __int16 v109; // ax
  char v110; // al
  char v111; // al
  unsigned int v112; // eax
  unsigned int v113; // eax
  __int64 v114; // r9
  unsigned __int8 *v115; // r12
  __int64 v116; // rdx
  __int64 (__fastcall *v117)(unsigned __int16 *, unsigned __int64, __int64, __int64, unsigned __int64, __int64); // rax
  int v118; // eax
  char v119; // al
  char *v120; // r9
  unsigned __int8 *v121; // r12
  unsigned int *v122; // r15
  unsigned int v123; // eax
  int v124; // r10d
  __int64 v125; // rax
  __int64 (__fastcall *v126)(unsigned __int16 *); // rcx
  int v127; // eax
  unsigned int v128; // eax
  unsigned int v129; // eax
  __int16 v130; // ax
  unsigned __int8 v131; // al
  __int64 v132; // rax
  unsigned int v133; // eax
  int v134; // ebx
  char v135; // dl
  char *v136; // rdi
  __int64 (__fastcall *v137)(unsigned __int16 *, char *, unsigned __int64, __int64); // rax
  char *v138; // rsi
  unsigned int v139; // edx
  int v140; // eax
  unsigned int v141; // eax
  int v142; // eax
  char v143; // al
  char v144; // al
  char v145; // al
  char v146; // al
  char v147; // al
  char v148; // al
  char v149; // al
  char v150; // al
  char v151; // al
  char v152; // al
  char v153; // al
  char v154; // al
  char v155; // al
  char v156; // al
  char v157; // al
  char v158; // al
  unsigned int v159; // eax
  char v160; // al
  unsigned __int8 *v161; // rdi
  int v162; // eax
  char v163; // al
  char v164; // al
  char v165; // al
  unsigned __int16 v166; // ax
  int v167; // eax
  char v168; // al
  char v169; // al
  char v170; // al
  char v171; // al
  char v172; // al
  char v173; // al
  char v174; // al
  __int64 v175; // [rsp+0h] [rbp-88h]
  char v176; // [rsp+0h] [rbp-88h]
  __int64 v177; // [rsp+0h] [rbp-88h]
  unsigned __int64 *v178; // [rsp+8h] [rbp-80h]
  unsigned __int8 v179; // [rsp+10h] [rbp-78h]
  char *v180; // [rsp+10h] [rbp-78h]
  char *v181; // [rsp+10h] [rbp-78h]
  char *v182; // [rsp+10h] [rbp-78h]
  char *v183; // [rsp+10h] [rbp-78h]
  char *v184; // [rsp+10h] [rbp-78h]
  char *v185; // [rsp+18h] [rbp-70h]
  char *v186; // [rsp+18h] [rbp-70h]
  char *v187; // [rsp+18h] [rbp-70h]
  char *v188; // [rsp+20h] [rbp-68h]
  char *v189; // [rsp+28h] [rbp-60h]
  char *v190; // [rsp+30h] [rbp-58h]
  char *v191; // [rsp+38h] [rbp-50h]
  char *v192; // [rsp+40h] [rbp-48h]
  unsigned int v193; // [rsp+48h] [rbp-40h]
  __int64 v194; // [rsp+48h] [rbp-40h]
  unsigned __int8 *v195; // [rsp+48h] [rbp-40h]

  v5 = *((unsigned __int8 *)a1 + 23);
  v6 = *((_DWORD *)a1 + 1);
  v178 = (unsigned __int64 *)a2;
  v175 = a4;
  v179 = *((_BYTE *)a1 + 3) >> 7;
  v7 = (*(_DWORD *)a1 >> 10) & 0x7F;
  if ( (v5 & 0x7F) != 0 )
    return 0LL;
  v8 = a1;
  if ( !a4 )
  {
    if ( ((*(_DWORD *)a1 >> 10) & 0x7F) != 0x3F )
    {
      if ( ((*(_DWORD *)a1 >> 10) & 0x7Fu) <= 0x3F )
      {
        result = 0LL;
        if ( ((*(_DWORD *)a1 >> 10) & 0x7F) == 4 )
          return result;
        if ( ((*(_DWORD *)a1 >> 10) & 0x7Fu) <= 4 )
        {
          if ( ((((*(_DWORD *)a1 >> 10) & 0x7F) + 127) & 0x7Fu) <= 1 )
            return result;
        }
        else if ( ((*(_DWORD *)a1 >> 10) & 0x7F) == 0x12 )
        {
          return result;
        }
      }
      *((_BYTE *)a1 + 23) = *((_BYTE *)a1 + 23) & 0x80 | 0xB;
      return 1LL;
    }
    v19 = *(unsigned int (__fastcall **)(unsigned __int16 *, unsigned __int64, unsigned __int64, __int64, unsigned __int64, char *))(a2 + 56);
    if ( v19 && v19(a1, a2, v7, a4, v5, a3) )
    {
      v106 = *((_BYTE *)a1 + 23);
      *((_DWORD *)a1 + 1) = v6;
      *((_BYTE *)a1 + 23) = v106 & 0x80 | 7;
      return 0LL;
    }
    return 0LL;
  }
  v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
  if ( v10 == 45 )
  {
    v192 = a3;
    v191 = 0LL;
    v189 = 0LL;
    v185 = 0LL;
  }
  else if ( ((*(_DWORD *)a1 >> 10) & 0x7F) == 0x32 )
  {
    v185 = a3;
    v191 = 0LL;
    v189 = 0LL;
    v192 = 0LL;
  }
  else if ( ((*(_DWORD *)a1 >> 10) & 0x7F) == 0x10 )
  {
    v191 = a3;
    v10 = 16;
    v189 = 0LL;
    v185 = 0LL;
    v192 = 0LL;
  }
  else
  {
    v185 = 0LL;
    v11 = 0LL;
    v7 = (((*(_DWORD *)a1 >> 10) & 0x7F) + 107) & 0x7F;
    v191 = 0LL;
    v192 = 0LL;
    if ( (unsigned __int8)v7 < 0xBu )
      v11 = a3;
    v189 = v11;
  }
  v12 = (unsigned __int8 *)&a3[a4];
  if ( a3 == &a3[a4] )
  {
    v188 = 0LL;
    v25 = 0;
LABEL_42:
    if ( v25 + (v192 != 0LL) - ((v185 == 0LL) - 1) - ((v189 == 0LL) - 1) - ((v191 == 0LL) - 1) > 1 )
      __assert_fail(
        "((header_field_mark ? 1 : 0) + (header_value_mark ? 1 : 0) + (url_mark ? 1 : 0) + (body_mark ? 1 : 0) + (status_"
        "mark ? 1 : 0)) <= 1",
        "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
        0x810u,
        "http_parser_execute");
    if ( (v5 & 0x7F) != 0 )
      __assert_fail(
        "HTTP_PARSER_ERRNO(parser) == HPE_OK",
        "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
        0x816u,
        "http_parser_execute");
    LOBYTE(v26) = v10 & 0x7F;
    if ( v192 )
    {
      v27 = (__int64 (__fastcall *)(unsigned __int16 *, char *, signed __int64))v178[3];
      if ( v27 )
      {
        v180 = a3;
        *(_DWORD *)v8 = *(_DWORD *)v8 & 0xFFFE03FF | ((v10 & 0x7F) << 10);
        v28 = v27(v8, v192, v12 - (unsigned __int8 *)v192);
        a3 = v180;
        if ( v28 )
        {
          v147 = *((_BYTE *)v8 + 23);
          *((_DWORD *)v8 + 1) = v6;
          *((_BYTE *)v8 + 23) = v147 & 0x80 | 3;
        }
        v26 = (*(_DWORD *)v8 >> 10) & 0x7F;
        if ( (*((_BYTE *)v8 + 23) & 0x7F) != 0 )
          return v12 - (unsigned __int8 *)a3;
      }
    }
    if ( v185 )
    {
      v29 = (__int64 (__fastcall *)(unsigned __int16 *, char *, signed __int64))v178[4];
      if ( v29 )
      {
        v181 = a3;
        *(_DWORD *)v8 = *(_DWORD *)v8 & 0xFFFE03FF | ((v26 & 0x7F) << 10);
        v30 = v29(v8, v185, v12 - (unsigned __int8 *)v185);
        a3 = v181;
        if ( v30 )
        {
          v150 = *((_BYTE *)v8 + 23);
          *((_DWORD *)v8 + 1) = v6;
          *((_BYTE *)v8 + 23) = v150 & 0x80 | 4;
        }
        v26 = (*(_DWORD *)v8 >> 10) & 0x7F;
        if ( (*((_BYTE *)v8 + 23) & 0x7F) != 0 )
          return v12 - (unsigned __int8 *)a3;
      }
    }
    if ( v189 )
    {
      v31 = (__int64 (__fastcall *)(unsigned __int16 *, char *, signed __int64))v178[1];
      if ( v31 )
      {
        v182 = a3;
        *(_DWORD *)v8 = *(_DWORD *)v8 & 0xFFFE03FF | ((v26 & 0x7F) << 10);
        v32 = v31(v8, v189, v12 - (unsigned __int8 *)v189);
        a3 = v182;
        if ( v32 )
        {
          v151 = *((_BYTE *)v8 + 23);
          *((_DWORD *)v8 + 1) = v6;
          *((_BYTE *)v8 + 23) = v151 & 0x80 | 2;
        }
        v26 = (*(_DWORD *)v8 >> 10) & 0x7F;
        if ( (*((_BYTE *)v8 + 23) & 0x7F) != 0 )
          return v12 - (unsigned __int8 *)a3;
      }
    }
    if ( v188 )
    {
      v33 = (__int64 (__fastcall *)(unsigned __int16 *, char *, signed __int64))v178[6];
      if ( v33 )
      {
        v183 = a3;
        *(_DWORD *)v8 = *(_DWORD *)v8 & 0xFFFE03FF | ((v26 & 0x7F) << 10);
        v34 = v33(v8, v188, v12 - (unsigned __int8 *)v188);
        a3 = v183;
        if ( v34 )
        {
          v152 = *((_BYTE *)v8 + 23);
          *((_DWORD *)v8 + 1) = v6;
          *((_BYTE *)v8 + 23) = v152 & 0x80 | 6;
        }
        v26 = (*(_DWORD *)v8 >> 10) & 0x7F;
        if ( (*((_BYTE *)v8 + 23) & 0x7F) != 0 )
          return v12 - (unsigned __int8 *)a3;
      }
    }
    if ( !v191 )
      goto LABEL_69;
    v184 = a3;
    v35 = (__int64 (__fastcall *)(unsigned __int16 *, char *, signed __int64))v178[2];
    if ( !v35 )
      goto LABEL_69;
    *(_DWORD *)v8 = ((v26 & 0x7F) << 10) | *(_DWORD *)v8 & 0xFFFE03FF;
    v36 = v35(v8, v191, v12 - (unsigned __int8 *)v191);
    a3 = v184;
    if ( v36 )
    {
      v153 = *((_BYTE *)v8 + 23);
      *((_DWORD *)v8 + 1) = v6;
      *((_BYTE *)v8 + 23) = v153 & 0x80 | 8;
    }
    v26 = (*(_DWORD *)v8 >> 10) & 0x7F;
    if ( (*((_BYTE *)v8 + 23) & 0x7F) != 0 )
      return v12 - (unsigned __int8 *)a3;
LABEL_69:
    v37 = *(_DWORD *)v8;
    *((_DWORD *)v8 + 1) = v6;
    *(_DWORD *)v8 = ((v26 & 0x7F) << 10) | v37 & 0xFFFE03FF;
    return v175;
  }
  v188 = 0LL;
  v13 = (unsigned __int8 *)&a3[a4];
  v14 = (unsigned __int8 *)a3;
  v190 = a3;
  v15 = *((_DWORD *)a1 + 1);
  v16 = *((unsigned __int8 *)a1 + 23);
  while ( 2 )
  {
    v18 = (unsigned int)(char)*v14;
    if ( v10 <= 0x3A && dword_B010 < ++v15 )
    {
      v20 = v14;
      v8 = a1;
      a3 = v190;
      v6 = v15;
      *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xC;
      v21 = v10 & 0x7F;
      goto LABEL_29;
    }
LABEL_21:
    switch ( v10 )
    {
      case 1u:
        if ( (_BYTE)v18 == 13 || (_BYTE)v18 == 10 )
        {
          ++v14;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xD;
        v21 = 1;
        goto LABEL_29;
      case 2u:
        if ( (_BYTE)v18 == 13 || (_BYTE)v18 == 10 )
        {
          ++v14;
        }
        else
        {
          *a1 &= 0xFC03u;
          *((_QWORD *)a1 + 1) = -1LL;
          if ( (_BYTE)v18 == 72 )
          {
            if ( (v16 & 0x7F) != 0 )
              __assert_fail(
                "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x2E0u,
                "http_parser_execute");
            v7 = *v178;
            if ( *v178 )
            {
              v159 = *(_DWORD *)a1 & 0xFFFE03FF;
              BYTE1(v159) |= 0xCu;
              *(_DWORD *)a1 = v159;
              if ( ((unsigned int (__fastcall *)(unsigned __int16 *))v7)(a1) )
              {
                v173 = *((_BYTE *)a1 + 23);
                *((_DWORD *)a1 + 1) = v15;
                *((_BYTE *)a1 + 23) = v173 & 0x80 | 1;
              }
              v16 = *((unsigned __int8 *)a1 + 23);
              v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
              if ( (v16 & 0x7F) != 0 )
                goto LABEL_481;
              ++v14;
            }
            else
            {
              ++v14;
              v10 = 3;
            }
          }
          else
          {
            *(_BYTE *)a1 &= 0xFCu;
LABEL_293:
            *a1 &= 0xFC03u;
            *((_QWORD *)a1 + 1) = -1LL;
            if ( (unsigned __int8)((v18 | 0x20) - 97) > 0x19u )
            {
LABEL_448:
              v20 = v14;
              v8 = a1;
              a3 = v190;
              v6 = v15;
              *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x10;
              v21 = 18;
              goto LABEL_29;
            }
            v70 = *((_BYTE *)a1 + 3);
            *((_BYTE *)a1 + 22) = 0;
            *((_BYTE *)a1 + 3) = v70 & 0x80 | 1;
            switch ( (char)v18 )
            {
              case 'A':
                *((_BYTE *)a1 + 22) = 19;
                goto LABEL_450;
              case 'B':
                *((_BYTE *)a1 + 22) = 16;
                goto LABEL_450;
              case 'C':
                *((_BYTE *)a1 + 22) = 5;
                goto LABEL_450;
              case 'D':
                goto LABEL_450;
              case 'G':
                *((_BYTE *)a1 + 22) = 1;
                goto LABEL_450;
              case 'H':
                *((_BYTE *)a1 + 22) = 2;
                goto LABEL_450;
              case 'L':
                *((_BYTE *)a1 + 22) = 9;
                goto LABEL_450;
              case 'M':
                *((_BYTE *)a1 + 22) = 10;
                goto LABEL_450;
              case 'N':
                *((_BYTE *)a1 + 22) = 25;
                goto LABEL_450;
              case 'O':
                *((_BYTE *)a1 + 22) = 6;
                goto LABEL_450;
              case 'P':
                *((_BYTE *)a1 + 22) = 3;
                goto LABEL_450;
              case 'R':
                *((_BYTE *)a1 + 22) = 20;
                goto LABEL_450;
              case 'S':
                *((_BYTE *)a1 + 22) = 26;
                goto LABEL_450;
              case 'T':
                *((_BYTE *)a1 + 22) = 7;
                goto LABEL_450;
              case 'U':
                *((_BYTE *)a1 + 22) = 15;
LABEL_450:
                if ( (v16 & 0x7F) != 0 )
                  __assert_fail(
                    "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                    "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                    0x3BEu,
                    "http_parser_execute");
                v7 = *v178;
                if ( *v178 )
                {
                  v112 = *(_DWORD *)a1 & 0xFFFE03FF;
                  BYTE1(v112) |= 0x4Cu;
                  *(_DWORD *)a1 = v112;
                  if ( ((unsigned int (__fastcall *)(unsigned __int16 *))v7)(a1) )
                  {
                    v158 = *((_BYTE *)a1 + 23);
                    *((_DWORD *)a1 + 1) = v15;
                    *((_BYTE *)a1 + 23) = v158 & 0x80 | 1;
                  }
                  v16 = *((unsigned __int8 *)a1 + 23);
                  v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
                  if ( (v16 & 0x7F) != 0 )
                    goto LABEL_481;
                  ++v14;
                }
                else
                {
                  ++v14;
                  v10 = 19;
                }
                break;
              default:
                goto LABEL_448;
            }
          }
        }
        goto LABEL_39;
      case 3u:
        if ( (_BYTE)v18 == 84 )
        {
          ++v14;
          v10 = 6;
          *(_BYTE *)a1 = *(_BYTE *)a1 & 0xFC | 1;
          goto LABEL_39;
        }
        if ( (_BYTE)v18 == 69 )
        {
          v42 = *(_DWORD *)a1;
          *((_BYTE *)a1 + 22) = 2;
          ++v14;
          v10 = 19;
          *(_DWORD *)a1 = v42 & 0x80FFFFFC | 0x2000000;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1C;
        v21 = 3;
        goto LABEL_29;
      case 4u:
        if ( (_BYTE)v18 == 13 || (_BYTE)v18 == 10 )
        {
          ++v14;
        }
        else
        {
          *a1 &= 0xFC03u;
          *((_QWORD *)a1 + 1) = -1LL;
          if ( (_BYTE)v18 != 72 )
          {
            v20 = v14;
            v8 = a1;
            a3 = v190;
            v6 = v15;
            *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1C;
            v21 = 4;
            goto LABEL_29;
          }
          if ( (v16 & 0x7F) != 0 )
            __assert_fail(
              "HTTP_PARSER_ERRNO(parser) == HPE_OK",
              "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
              0x309u,
              "http_parser_execute");
          v7 = *v178;
          if ( *v178 )
          {
            v56 = *(_DWORD *)a1 & 0xFFFE03FF;
            BYTE1(v56) |= 0x14u;
            *(_DWORD *)a1 = v56;
            if ( ((unsigned int (__fastcall *)(unsigned __int16 *))v7)(a1) )
            {
              v155 = *((_BYTE *)a1 + 23);
              *((_DWORD *)a1 + 1) = v15;
              *((_BYTE *)a1 + 23) = v155 & 0x80 | 1;
            }
            v16 = *((unsigned __int8 *)a1 + 23);
            v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
            if ( (v16 & 0x7F) != 0 )
              goto LABEL_481;
            ++v14;
          }
          else
          {
            ++v14;
            v10 = 5;
          }
        }
        goto LABEL_39;
      case 5u:
        if ( (_BYTE)v18 != 84 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 5;
          goto LABEL_29;
        }
        ++v14;
        v10 = 6;
        goto LABEL_39;
      case 6u:
        if ( (_BYTE)v18 != 84 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 6;
          goto LABEL_29;
        }
        ++v14;
        v10 = 7;
        goto LABEL_39;
      case 7u:
        if ( (_BYTE)v18 != 80 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 7;
          goto LABEL_29;
        }
        ++v14;
        v10 = 8;
        goto LABEL_39;
      case 8u:
        if ( (_BYTE)v18 != 47 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 8;
          goto LABEL_29;
        }
        ++v14;
        v10 = 9;
        goto LABEL_39;
      case 9u:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          ++v14;
          v10 = 10;
          a1[8] = v18 - 48;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xE;
        v21 = 9;
        goto LABEL_29;
      case 0xAu:
        if ( (_BYTE)v18 == 46 )
        {
          ++v14;
          v10 = 11;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xE;
        v21 = 10;
        goto LABEL_29;
      case 0xBu:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          ++v14;
          v10 = 12;
          a1[9] = v18 - 48;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xE;
        v21 = 11;
        goto LABEL_29;
      case 0xCu:
        if ( (_BYTE)v18 == 32 )
        {
          ++v14;
          v10 = 13;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xE;
        v21 = 12;
        goto LABEL_29;
      case 0xDu:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          ++v14;
          v10 = 14;
          a1[10] = (char)v18 - 48;
        }
        else
        {
          if ( (_BYTE)v18 != 32 )
          {
            v20 = v14;
            v8 = a1;
            a3 = v190;
            v6 = v15;
            *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xF;
            v21 = 13;
            goto LABEL_29;
          }
          ++v14;
        }
        goto LABEL_39;
      case 0xEu:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          v166 = 10 * a1[10] + v18 - 48;
          a1[10] = v166;
          if ( v166 > 0x3E7u )
          {
LABEL_79:
            v20 = v14;
            v8 = a1;
            a3 = v190;
            v6 = v15;
            *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xF;
            v21 = 14;
            goto LABEL_29;
          }
          ++v14;
          goto LABEL_39;
        }
        if ( (_BYTE)v18 != 13 )
        {
          if ( (_BYTE)v18 == 32 )
          {
            ++v14;
            v10 = 15;
            goto LABEL_39;
          }
          if ( (_BYTE)v18 != 10 )
            goto LABEL_79;
          *((_BYTE *)a1 + 3) &= 0x80u;
          if ( !v191 )
            v191 = (char *)v14;
          goto LABEL_589;
        }
        if ( v191 )
        {
          *((_BYTE *)a1 + 3) &= 0x80u;
        }
        else
        {
LABEL_577:
          v191 = (char *)v14;
LABEL_307:
          *((_BYTE *)a1 + 3) &= 0x80u;
          if ( (_BYTE)v18 != 13 )
          {
            if ( (_BYTE)v18 != 10 )
            {
              ++v14;
              v10 = 16;
              goto LABEL_39;
            }
LABEL_309:
            if ( (_BYTE)v18 != 13 )
            {
              if ( (_BYTE)v18 != 10 )
              {
                ++v14;
                v10 = 16;
                goto LABEL_39;
              }
LABEL_589:
              if ( (v16 & 0x7F) != 0 )
                __assert_fail(
                  "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                  "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                  0x38Du,
                  "http_parser_execute");
              if ( v191 )
              {
                a4 = v178[2];
                if ( a4 )
                {
                  v133 = *(_DWORD *)a1 & 0xFFFE03FF;
                  BYTE1(v133) |= 0xB0u;
                  *(_DWORD *)a1 = v133;
                  a2 = (unsigned __int64)v191;
                  if ( ((unsigned int (__fastcall *)(unsigned __int16 *, char *, signed __int64))a4)(
                         a1,
                         v191,
                         v14 - (unsigned __int8 *)v191) )
                  {
                    v169 = *((_BYTE *)a1 + 23);
                    *((_DWORD *)a1 + 1) = v15;
                    *((_BYTE *)a1 + 23) = v169 & 0x80 | 8;
                  }
                  v16 = *((unsigned __int8 *)a1 + 23);
                  v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
                  if ( (v16 & 0x7F) != 0 )
                    goto LABEL_481;
                  v191 = 0LL;
                  ++v14;
                }
                else
                {
                  v191 = 0LL;
                  ++v14;
                  v10 = 44;
                }
              }
              else
              {
                ++v14;
                v10 = 44;
              }
              goto LABEL_39;
            }
          }
        }
        if ( (v16 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x387u,
            "http_parser_execute");
        if ( v191 )
        {
          a4 = v178[2];
          if ( a4 )
          {
            v128 = *(_DWORD *)a1 & 0xFFFE03FF;
            BYTE1(v128) |= 0x44u;
            *(_DWORD *)a1 = v128;
            a2 = (unsigned __int64)v191;
            if ( ((unsigned int (__fastcall *)(unsigned __int16 *, char *, signed __int64))a4)(
                   a1,
                   v191,
                   v14 - (unsigned __int8 *)v191) )
            {
              v164 = *((_BYTE *)a1 + 23);
              *((_DWORD *)a1 + 1) = v15;
              *((_BYTE *)a1 + 23) = v164 & 0x80 | 8;
            }
            v16 = *((unsigned __int8 *)a1 + 23);
            v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
            if ( (v16 & 0x7F) != 0 )
              goto LABEL_481;
            v191 = 0LL;
            ++v14;
          }
          else
          {
            v191 = 0LL;
            ++v14;
            v10 = 17;
          }
        }
        else
        {
          ++v14;
          v10 = 17;
        }
        goto LABEL_39;
      case 0xFu:
        if ( v191 )
          goto LABEL_307;
        goto LABEL_577;
      case 0x10u:
        goto LABEL_309;
      case 0x11u:
        if ( (_BYTE)v18 != 10 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 17;
          goto LABEL_29;
        }
        ++v14;
        v10 = 44;
        goto LABEL_39;
      case 0x12u:
        if ( (_BYTE)v18 != 13 && (_BYTE)v18 != 10 )
          goto LABEL_293;
        ++v14;
        goto LABEL_39;
      case 0x13u:
        if ( !(_BYTE)v18 )
          goto LABEL_563;
        a2 = (unsigned __int64)off_ACA0[*((unsigned __int8 *)a1 + 22)];
        v57 = *((_BYTE *)a1 + 3) & 0x7F;
        a4 = *(unsigned __int8 *)(a2 + v57);
        if ( (_BYTE)v18 == 32 )
        {
          if ( (_BYTE)a4 )
          {
            if ( (_BYTE)a4 != 32 )
              goto LABEL_563;
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
LABEL_563:
            v20 = v14;
            v8 = a1;
            a3 = v190;
            v6 = v15;
            *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x10;
            v21 = 19;
            goto LABEL_29;
          }
          a4 = v57 << 8;
          v58 = v18 | a4 | (*((unsigned __int8 *)a1 + 22) << 16);
          if ( v58 == 655695 )
          {
            *((_BYTE *)a1 + 22) = 11;
          }
          else if ( v58 > 655695 )
          {
            if ( v58 == 983635 )
            {
              *((_BYTE *)a1 + 22) = 27;
            }
            else if ( v58 <= 983635 )
            {
              if ( v58 == 787536 )
              {
                *((_BYTE *)a1 + 22) = 13;
              }
              else if ( v58 <= 787536 )
              {
                if ( v58 == 655937 )
                {
                  *((_BYTE *)a1 + 22) = 21;
                }
                else
                {
                  if ( v58 != 656193 )
                    goto LABEL_563;
                  *((_BYTE *)a1 + 22) = 30;
                }
              }
              else
              {
                if ( v58 != 983618 )
                  goto LABEL_563;
                *((_BYTE *)a1 + 22) = 18;
              }
            }
            else if ( v58 == 1704261 )
            {
              *((_BYTE *)a1 + 22) = 14;
            }
            else if ( v58 <= 1704261 )
            {
              if ( v58 == 983881 )
              {
                *((_BYTE *)a1 + 22) = 32;
              }
              else
              {
                if ( v58 != 1311298 )
                  goto LABEL_563;
                *((_BYTE *)a1 + 22) = 17;
              }
            }
            else
            {
              if ( v58 != 1704271 )
                goto LABEL_563;
              *((_BYTE *)a1 + 22) = 33;
            }
          }
          else if ( v58 == 328008 )
          {
            *((_BYTE *)a1 + 22) = 22;
          }
          else if ( v58 <= 328008 )
          {
            if ( v58 == 196949 )
            {
              *((_BYTE *)a1 + 22) = 4;
            }
            else if ( v58 <= 196949 )
            {
              if ( v58 == 196929 )
              {
                *((_BYTE *)a1 + 22) = 28;
              }
              else
              {
                if ( v58 != 196946 )
                  goto LABEL_563;
                *((_BYTE *)a1 + 22) = 12;
              }
            }
            else
            {
              if ( v58 != 262738 )
                goto LABEL_563;
              *((_BYTE *)a1 + 22) = 29;
            }
          }
          else if ( v58 == 655661 )
          {
            *((_BYTE *)a1 + 22) = 24;
          }
          else if ( v58 <= 655661 )
          {
            if ( v58 == 328272 )
            {
              *((_BYTE *)a1 + 22) = 8;
            }
            else
            {
              if ( v58 != 590153 )
                goto LABEL_563;
              *((_BYTE *)a1 + 22) = 31;
            }
          }
          else
          {
            if ( v58 != 655685 )
              goto LABEL_563;
            *((_BYTE *)a1 + 22) = 23;
          }
        }
        ++v14;
        v7 = (v57 + 1) & 0x7F;
        *((_BYTE *)a1 + 3) = v7 | *((_BYTE *)a1 + 3) & 0x80;
        goto LABEL_39;
      case 0x14u:
        if ( (_BYTE)v18 == 32 )
        {
          ++v14;
        }
        else
        {
          v59 = (unsigned __int8 *)v189;
          if ( !v189 )
            v59 = v14;
          v189 = (char *)v59;
          if ( *((_BYTE *)a1 + 22) == 5 )
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
          v10 = sub_2240(v10, a2, v7, a4, v5, v16);
          if ( v10 == 1 )
            goto LABEL_470;
          ++v14;
        }
        goto LABEL_39;
      case 0x15u:
      case 0x16u:
      case 0x17u:
      case 0x18u:
        if ( (unsigned __int8)v18 > 0x20u )
          goto LABEL_73;
        v38 = 0x100002400LL;
        if ( !_bittest64(&v38, v18) )
        {
          v39 = 0x100003200LL;
          if ( _bittest64(&v39, v18) )
            goto LABEL_470;
LABEL_73:
          a2 = (unsigned int)(char)v18;
          v10 = sub_2240(v10, a2, v7, a4, v5, v16);
          if ( v10 == 1 )
          {
LABEL_470:
            v20 = v14;
            v8 = a1;
            a3 = v190;
            v6 = v15;
            *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x11;
            v21 = 1;
            goto LABEL_29;
          }
          ++v14;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x11;
        v21 = v10 & 0x7F;
        goto LABEL_29;
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
            *((_DWORD *)a1 + 4) = 589824;
            v10 = 43;
            break;
          case 0x20:
            if ( (v16 & 0x7F) != 0 )
              __assert_fail(
                "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x42Cu,
                "http_parser_execute");
            if ( v189 )
            {
              a4 = v178[1];
              if ( a4 )
              {
                v129 = *(_DWORD *)a1 & 0xFFFE03FF;
                BYTE1(v129) |= 0x80u;
                *(_DWORD *)a1 = v129;
                a2 = (unsigned __int64)v189;
                if ( ((unsigned int (__fastcall *)(unsigned __int16 *, char *, signed __int64))a4)(
                       a1,
                       v189,
                       v14 - (unsigned __int8 *)v189) )
                {
                  v163 = *((_BYTE *)a1 + 23);
                  *((_DWORD *)a1 + 1) = v15;
                  *((_BYTE *)a1 + 23) = v163 & 0x80 | 2;
                }
                v16 = *((unsigned __int8 *)a1 + 23);
                v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
                if ( (v16 & 0x7F) != 0 )
                  goto LABEL_481;
                v189 = 0LL;
                ++v14;
              }
              else
              {
                v189 = 0LL;
                ++v14;
                v10 = 32;
              }
            }
            else
            {
              ++v14;
              v10 = 32;
            }
            goto LABEL_39;
          case 0xA:
            *((_DWORD *)a1 + 4) = 589824;
            v10 = 44;
            break;
          default:
            if ( (unsigned __int8)v18 <= 0x20u )
            {
              v24 = 0x100003200LL;
              if ( _bittest64(&v24, v18) )
                goto LABEL_470;
            }
            a2 = (unsigned int)(char)v18;
            v10 = sub_2240(v10, a2, v7, a4, v5, v16);
            if ( v10 == 1 )
              goto LABEL_470;
            ++v14;
            goto LABEL_39;
        }
        if ( (v16 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x435u,
            "http_parser_execute");
        if ( v189 )
        {
          a4 = v178[1];
          if ( a4 )
          {
            *(_DWORD *)a1 = ((v10 & 0x7F) << 10) | *(_DWORD *)a1 & 0xFFFE03FF;
            a2 = (unsigned __int64)v189;
            if ( ((unsigned int (__fastcall *)(unsigned __int16 *, char *, signed __int64))a4)(
                   a1,
                   v189,
                   v14 - (unsigned __int8 *)v189) )
            {
              v165 = *((_BYTE *)a1 + 23);
              *((_DWORD *)a1 + 1) = v15;
              *((_BYTE *)a1 + 23) = v165 & 0x80 | 2;
            }
            v16 = *((unsigned __int8 *)a1 + 23);
            v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
            if ( (v16 & 0x7F) != 0 )
              goto LABEL_481;
            v189 = 0LL;
            ++v14;
          }
          else
          {
            v189 = 0LL;
            ++v14;
          }
        }
        else
        {
          ++v14;
        }
        goto LABEL_39;
      case 0x20u:
        switch ( (_BYTE)v18 )
        {
          case 'H':
            ++v14;
            v10 = 33;
            break;
          case 'I':
            if ( *((_BYTE *)a1 + 22) != 33 )
            {
LABEL_88:
              v20 = v14;
              v8 = a1;
              a3 = v190;
              v6 = v15;
              *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1C;
              v21 = 32;
              goto LABEL_29;
            }
            ++v14;
            v10 = 37;
            break;
          case ' ':
            ++v14;
            break;
          default:
            goto LABEL_88;
        }
        goto LABEL_39;
      case 0x21u:
        if ( (_BYTE)v18 != 84 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 33;
          goto LABEL_29;
        }
        ++v14;
        v10 = 34;
        goto LABEL_39;
      case 0x22u:
        if ( (_BYTE)v18 == 84 )
        {
          ++v14;
          v10 = 35;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
        v21 = 34;
        goto LABEL_29;
      case 0x23u:
        if ( (_BYTE)v18 != 80 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 35;
          goto LABEL_29;
        }
        ++v14;
        v10 = 36;
        goto LABEL_39;
      case 0x24u:
        if ( (_BYTE)v18 != 47 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 36;
          goto LABEL_29;
        }
        ++v14;
        v10 = 39;
        goto LABEL_39;
      case 0x25u:
        if ( (_BYTE)v18 != 67 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 37;
          goto LABEL_29;
        }
        ++v14;
        v10 = 38;
        goto LABEL_39;
      case 0x26u:
        if ( (_BYTE)v18 == 69 )
        {
          ++v14;
          v10 = 36;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
        v21 = 38;
        goto LABEL_29;
      case 0x27u:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          ++v14;
          v10 = 40;
          a1[8] = v18 - 48;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xE;
        v21 = 39;
        goto LABEL_29;
      case 0x28u:
        if ( (_BYTE)v18 == 46 )
        {
          ++v14;
          v10 = 41;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xE;
        v21 = 40;
        goto LABEL_29;
      case 0x29u:
        if ( (unsigned __int8)(v18 - 48) <= 9u )
        {
          ++v14;
          v10 = 42;
          a1[9] = v18 - 48;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xE;
        v21 = 41;
        goto LABEL_29;
      case 0x2Au:
        if ( (_BYTE)v18 == 13 )
        {
          ++v14;
          v10 = 43;
        }
        else
        {
          if ( (_BYTE)v18 != 10 )
          {
            v20 = v14;
            v8 = a1;
            a3 = v190;
            v6 = v15;
            *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xE;
            v21 = 42;
            goto LABEL_29;
          }
          ++v14;
          v10 = 44;
        }
        goto LABEL_39;
      case 0x2Bu:
        if ( (_BYTE)v18 == 10 )
        {
          ++v14;
          v10 = 44;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x17;
        v21 = 43;
        goto LABEL_29;
      case 0x2Cu:
        goto LABEL_134;
      case 0x2Du:
        v193 = dword_B010;
        if ( v14 != v13 )
        {
          v5 = (unsigned int)dword_B010;
          v48 = v14;
          a2 = (unsigned __int64)byte_7B60;
          while ( 1 )
          {
            v49 = *v48;
            if ( *v48 == 32 )
              break;
            v50 = byte_7B60[v49];
            if ( !v50 )
              break;
            a4 = *((unsigned __int8 *)a1 + 2);
            if ( (unsigned __int8)a4 > 0x1Du )
LABEL_365:
              __assert_fail(
                "0 && \"Unknown header_state\"",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x551u,
                "http_parser_execute");
            switch ( *((_BYTE *)a1 + 2) >> 1 )
            {
              case 0:
                v75 = v13 - v48;
                if ( v13 - v48 > (unsigned __int64)v193 )
                  v75 = v193;
                v76 = &v48[v75];
                do
                {
                  if ( ++v48 >= v76 )
                    break;
                  v77 = *v48;
                  if ( (_BYTE)v77 == 32 )
                    break;
                }
                while ( byte_7B60[v77] );
                break;
              case 1:
                ++v48;
                a1[1] = a1[1] & 0x8001 | (4 * (v50 == 111)) | (((*((_BYTE *)a1 + 3) + 1) & 0x7F) << 8);
                break;
              case 2:
                v73 = *((_BYTE *)a1 + 3);
                a4 = (v73 + 1) & 0x7F;
                v45 = v50 == 110;
                v74 = *((_BYTE *)a1 + 2);
                *((_BYTE *)a1 + 3) = a4 | v73 & 0x80;
                ++v48;
                *((_BYTE *)a1 + 2) = v74 & 1 | (6 * v45);
                break;
              case 3:
                v84 = *((_BYTE *)a1 + 3);
                ++v48;
                a4 = (v84 + 1) & 0x7F;
                *((_BYTE *)a1 + 3) = a4 | v84 & 0x80;
                if ( v50 == 110 )
                {
                  *((_BYTE *)a1 + 2) = a1[1] & 1 | 8;
                }
                else if ( v50 == 116 )
                {
                  *((_BYTE *)a1 + 2) = a1[1] & 1 | 0xC;
                }
                else
                {
LABEL_345:
                  *((_BYTE *)a1 + 2) &= 1u;
                }
                break;
              case 4:
                v82 = *((unsigned __int8 *)a1 + 3);
                ++v48;
                v83 = ((_BYTE)v82 + 1) & 0x7F;
                a4 = v83 | v82 & 0xFFFFFF80;
                *((_BYTE *)a1 + 3) = a4;
                if ( (unsigned __int8)v83 > 0xAu || aProxyConnectio[(v83 & 0x7F) + 6] != v50 )
                  goto LABEL_345;
                a4 &= 0x7Fu;
                if ( (_BYTE)a4 == 9 )
                  goto LABEL_349;
                break;
              case 5:
                v80 = *((unsigned __int8 *)a1 + 3);
                ++v48;
                v81 = ((_BYTE)v80 + 1) & 0x7F;
                a4 = v81 | v80 & 0xFFFFFF80;
                *((_BYTE *)a1 + 3) = a4;
                if ( (unsigned __int8)v81 > 0x10u || aProxyConnectio[v81 & 0x7F] != v50 )
                  goto LABEL_345;
                a4 &= 0x7Fu;
                if ( (_BYTE)a4 == 15 )
LABEL_349:
                  *((_BYTE *)a1 + 2) = a1[1] & 1 | 0x12;
                break;
              case 6:
                v78 = *((unsigned __int8 *)a1 + 3);
                ++v48;
                v79 = ((_BYTE)v78 + 1) & 0x7F;
                a4 = v79 | v78 & 0xFFFFFF80;
                *((_BYTE *)a1 + 3) = a4;
                if ( (unsigned __int8)v79 > 0xEu || aContentLength[v79 & 0x7F] != v50 )
                  goto LABEL_345;
                a4 &= 0x7Fu;
                if ( (_BYTE)a4 == 13 )
                  *((_BYTE *)a1 + 2) = a1[1] & 1 | 0x14;
                break;
              case 7:
                v87 = *((unsigned __int8 *)a1 + 3);
                ++v48;
                v88 = ((_BYTE)v87 + 1) & 0x7F;
                a4 = v88 | v87 & 0xFFFFFF80;
                *((_BYTE *)a1 + 3) = a4;
                if ( (unsigned __int8)v88 > 0x11u || aTransferEncodi[v88 & 0x7F] != v50 )
                  goto LABEL_345;
                a4 &= 0x7Fu;
                if ( (_BYTE)a4 == 16 )
                  *((_BYTE *)a1 + 2) = a1[1] & 1 | 0x1A;
                break;
              case 8:
                v85 = *((unsigned __int8 *)a1 + 3);
                ++v48;
                v86 = ((_BYTE)v85 + 1) & 0x7F;
                a4 = v86 | v85 & 0xFFFFFF80;
                *((_BYTE *)a1 + 3) = a4;
                if ( (unsigned __int8)v86 > 7u || aUpgrade[v86 & 0x7F] != v50 )
                  goto LABEL_345;
                a4 &= 0x7Fu;
                if ( (_BYTE)a4 == 6 )
                  *((_BYTE *)a1 + 2) = a1[1] & 1 | 0x1C;
                break;
              case 9:
              case 10:
              case 13:
              case 14:
                *((_BYTE *)a1 + 2) &= 1u;
                ++v48;
                break;
              case 11:
              case 12:
                goto LABEL_365;
            }
            if ( v13 == v48 )
              goto LABEL_151;
          }
          if ( v13 == v48 )
          {
LABEL_151:
            LOBYTE(v5) = v16;
            a3 = v190;
            LODWORD(v51) = (_DWORD)v14;
            v8 = a1;
            v52 = v15;
            goto LABEL_152;
          }
          v7 = v48 - v14;
          v15 += (_DWORD)v48 - (_DWORD)v14;
          if ( v193 >= v15 )
          {
            if ( v49 != 58 )
            {
              v8 = a1;
              a3 = v190;
              v6 = v15;
              v20 = v48;
              *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x18;
              v21 = 45;
              goto LABEL_29;
            }
            if ( (v16 & 0x7F) != 0 )
              __assert_fail(
                "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x560u,
                "http_parser_execute");
            v14 = v48 + 1;
            v10 = 46;
            if ( v192 )
            {
              a4 = v178[3];
              if ( a4 )
              {
                v113 = *(_DWORD *)a1 & 0xFFFE03FF;
                BYTE1(v113) |= 0xB8u;
                *(_DWORD *)a1 = v113;
                a2 = (unsigned __int64)v192;
                if ( ((unsigned int (__fastcall *)(unsigned __int16 *, char *, signed __int64, __int64, _QWORD))a4)(
                       a1,
                       v192,
                       v48 - (unsigned __int8 *)v192,
                       a4,
                       v193) )
                {
                  v157 = *((_BYTE *)a1 + 23);
                  *((_DWORD *)a1 + 1) = v15;
                  *((_BYTE *)a1 + 23) = v157 & 0x80 | 3;
                }
                v16 = *((unsigned __int8 *)a1 + 23);
                v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
                if ( (v16 & 0x7F) != 0 )
                  return v48 - (unsigned __int8 *)v190 + 1;
                v192 = 0LL;
                v14 = v48 + 1;
              }
              else
              {
                v192 = 0LL;
                v14 = v48 + 1;
                v10 = 46;
              }
            }
            goto LABEL_39;
          }
          v8 = a1;
          a3 = v190;
          v6 = v15;
          v20 = v48;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xC;
          v21 = 45;
LABEL_29:
          v22 = *((_BYTE *)v8 + 23);
          if ( (v22 & 0x7F) == 0 )
            *((_BYTE *)v8 + 23) = v22 & 0x80 | 0x20;
          v23 = *(_DWORD *)v8;
          *((_DWORD *)v8 + 1) = v6;
          *(_DWORD *)v8 = v23 & 0xFFFE03FF | ((v21 & 0x7F) << 10);
          return v20 - (unsigned __int8 *)a3;
        }
        v51 = v14;
        LOBYTE(v5) = v16;
        v8 = a1;
        a3 = v190;
        v52 = v15;
        v48 = v51;
LABEL_152:
        v6 = (_DWORD)v48 - 1 - (_DWORD)v51 + v52;
        if ( v193 < v6 )
        {
          v20 = v48 - 1;
          v21 = 45;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xC;
          goto LABEL_29;
        }
        v12 = v48;
LABEL_41:
        v25 = v188 != 0LL;
        goto LABEL_42;
      case 0x2Eu:
        switch ( (_BYTE)v18 )
        {
          case 0x20:
          case 9:
            ++v14;
            break;
          case 0xD:
            ++v14;
            v10 = 47;
            break;
          case 0xA:
            ++v14;
            v10 = 48;
            break;
          default:
            LOBYTE(v40) = *((_BYTE *)a1 + 2);
            goto LABEL_96;
        }
        goto LABEL_39;
      case 0x2Fu:
        if ( (_BYTE)v18 == 10 )
        {
          ++v14;
          v10 = 48;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
        v21 = 47;
        goto LABEL_29;
      case 0x30u:
        if ( (_BYTE)v18 == 32 || (_BYTE)v18 == 9 )
        {
          ++v14;
          v10 = 46;
          goto LABEL_39;
        }
        switch ( ((*((_BYTE *)a1 + 2) >> 1) + 118) & 0x7F )
        {
          case 0:
            v20 = v14;
            v8 = a1;
            a3 = v190;
            v6 = v15;
            *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x19;
            v21 = 48;
            goto LABEL_29;
          case 0xB:
            *a1 |= 4u;
            goto LABEL_417;
          case 0xC:
            *a1 |= 8u;
            goto LABEL_417;
          case 0xD:
            *a1 |= 0x10u;
            goto LABEL_417;
          case 0xE:
            *a1 |= 0x20u;
            goto LABEL_417;
          default:
LABEL_417:
            v104 = (unsigned __int8 *)v185;
            if ( !v185 )
              v104 = v14;
            v186 = (char *)v104;
            if ( (v16 & 0x7F) != 0 )
              __assert_fail(
                "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x6D8u,
                "http_parser_execute");
            a4 = v178[4];
            if ( a4 )
            {
              v105 = *(_DWORD *)a1 & 0xFFFE03FF;
              BYTE1(v105) |= 0xB0u;
              *(_DWORD *)a1 = v105;
              a2 = (unsigned __int64)v186;
              if ( ((unsigned int (__fastcall *)(unsigned __int16 *, char *, signed __int64))a4)(
                     a1,
                     v186,
                     v14 - (unsigned __int8 *)v186) )
              {
                v148 = *((_BYTE *)a1 + 23);
                *((_DWORD *)a1 + 1) = v15;
                *((_BYTE *)a1 + 23) = v148 & 0x80 | 4;
              }
              v16 = *((unsigned __int8 *)a1 + 23);
              v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
              if ( (v16 & 0x7F) != 0 )
                return v14 - (unsigned __int8 *)v190;
              v185 = 0LL;
            }
            else
            {
              v185 = 0LL;
LABEL_134:
              if ( (_BYTE)v18 == 13 )
              {
                ++v14;
                v10 = 57;
                goto LABEL_39;
              }
              if ( (_BYTE)v18 != 10 )
              {
                if ( (_BYTE)v18 == 32 || (v160 = byte_7B60[(unsigned __int8)v18]) == 0 )
                {
                  v20 = v14;
                  v8 = a1;
                  a3 = v190;
                  v6 = v15;
                  *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x18;
                  v21 = 44;
                  goto LABEL_29;
                }
                v161 = (unsigned __int8 *)v192;
                if ( !v192 )
                  v161 = v14;
                *((_BYTE *)a1 + 3) &= 0x80u;
                ++v14;
                v192 = (char *)v161;
                if ( v160 == 116 )
                {
                  v10 = 45;
                  *((_BYTE *)a1 + 2) = a1[1] & 1 | 0xE;
                }
                else if ( v160 > 116 )
                {
                  if ( v160 != 117 )
                    goto LABEL_763;
                  v10 = 45;
                  *((_BYTE *)a1 + 2) = a1[1] & 1 | 0x10;
                }
                else if ( v160 == 99 )
                {
                  v10 = 45;
                  *((_BYTE *)a1 + 2) = a1[1] & 1 | 2;
                }
                else
                {
                  if ( v160 == 112 )
                  {
                    v10 = 45;
                    *((_BYTE *)a1 + 2) = a1[1] & 1 | 0xA;
                    goto LABEL_39;
                  }
LABEL_763:
                  *((_BYTE *)a1 + 2) &= 1u;
                  v10 = 45;
                }
LABEL_39:
                if ( v13 == v14 )
                {
                  LOBYTE(v5) = v16;
                  a3 = v190;
                  v8 = a1;
                  v6 = v15;
                  v12 = v13;
                  goto LABEL_41;
                }
                continue;
              }
LABEL_136:
              v47 = *a1 >> 2;
              if ( (v47 & 0x10) == 0 )
              {
                if ( (*a1 & 4) != 0 && (v47 & 0x80u) != 0 )
                {
                  v20 = v14;
                  v8 = a1;
                  a3 = v190;
                  v6 = v15;
                  *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1A;
                  v21 = 57;
                  goto LABEL_29;
                }
                if ( ((*a1 >> 2) & 0x28) == 0x28 )
                {
                  v47 = 1;
                  if ( (*(_BYTE *)a1 & 3) != 0 )
                    LOBYTE(v47) = a1[10] == 101;
                }
                else
                {
                  LOBYTE(v47) = *((_BYTE *)a1 + 22) == 5;
                }
                v116 = (unsigned int)(v47 << 7);
                *((_BYTE *)a1 + 23) = ((_BYTE)v47 << 7) | *((_BYTE *)a1 + 23) & 0x7F;
                v117 = (__int64 (__fastcall *)(unsigned __int16 *, unsigned __int64, __int64, __int64, unsigned __int64, __int64))v178[5];
                if ( !v117 )
                  goto LABEL_528;
                v118 = v117(a1, a2, v116, a4, v5, v16);
                if ( v118 != 1 )
                {
                  if ( v118 != 2 )
                  {
                    if ( v118 )
                    {
                      v119 = *((_BYTE *)a1 + 23);
                      v120 = v190;
                      *((_DWORD *)a1 + 1) = v15;
                      v121 = v14;
                      v122 = (unsigned int *)a1;
                      *((_BYTE *)a1 + 23) = v119 & 0x80 | 5;
LABEL_497:
                      v123 = *v122 & 0xFFFE03FF;
                      BYTE1(v123) |= 0xE8u;
                      *v122 = v123;
                      return v121 - (unsigned __int8 *)v120;
                    }
LABEL_528:
                    v16 = *((unsigned __int8 *)a1 + 23);
                    if ( (v16 & 0x7F) != 0 )
                    {
                      v121 = v14;
                      *((_DWORD *)a1 + 1) = v15;
                      v120 = v190;
                      v122 = (unsigned int *)a1;
                      goto LABEL_497;
                    }
LABEL_313:
                    v71 = *a1;
                    *((_DWORD *)a1 + 1) = 0;
                    v7 = 1LL;
                    v72 = v71 >> 2;
                    a4 = v72 & 1;
                    if ( (v72 & 1) == 0 )
                      v7 = (unsigned __int64)(*((_QWORD *)a1 + 1) - 1LL) <= 0xFFFFFFFFFFFFFFFDLL;
                    if ( (v16 & 0x80u) == 0LL )
                    {
                      if ( (v72 & 0x40) != 0 )
                      {
                        if ( (unsigned int)sub_2520(a1, a2, v7, a4, v5, v16) )
                          v10 = (*(_BYTE *)a1 & 3) == 0 ? 18 : 4;
                        if ( (_BYTE)v16 )
                          __assert_fail(
                            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                            0x736u,
                            "http_parser_execute");
                        v7 = v178[7];
                        if ( v7 )
                        {
                          *(_DWORD *)a1 = ((v10 & 0x7F) << 10) | *(_DWORD *)a1 & 0xFFFE03FF;
                          if ( ((unsigned int (__fastcall *)(unsigned __int16 *))v7)(a1) )
                          {
                            v156 = *((_BYTE *)a1 + 23);
                            *((_DWORD *)a1 + 1) = 0;
                            *((_BYTE *)a1 + 23) = v156 & 0x80 | 7;
                          }
                          v16 = *((unsigned __int8 *)a1 + 23);
                          v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
                          if ( (v16 & 0x7F) != 0 )
                            goto LABEL_481;
                          ++v14;
                          v15 = 0;
                        }
                        else
                        {
                          ++v14;
                          v15 = 0;
                        }
                        goto LABEL_39;
                      }
                      goto LABEL_524;
                    }
                    if ( *((_BYTE *)a1 + 22) != 5 && (v72 & 0x40) == 0 && (_DWORD)v7 )
                    {
LABEL_524:
                      if ( (_BYTE)a4 )
                      {
                        ++v14;
                        v15 = 0;
                        v10 = 53;
                      }
                      else
                      {
                        v132 = *((_QWORD *)a1 + 1);
                        if ( v132 )
                        {
                          if ( v132 == -1 )
                          {
                            if ( (unsigned int)sub_24C0(a1, a2, v7) )
                            {
                              ++v14;
                              v15 = 0;
                              v10 = 63;
                            }
                            else
                            {
                              v162 = sub_2520(a1, a2, v7, a4, v5, v16);
                              v10 = 1;
                              if ( v162 )
                                v10 = (*(_BYTE *)a1 & 3) == 0 ? 18 : 4;
                              if ( (v16 & 0x7F) != 0 )
                                __assert_fail(
                                  "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                                  "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                                  0x746u,
                                  "http_parser_execute");
                              a4 = v178[7];
                              if ( a4 )
                              {
                                *(_DWORD *)a1 = ((v10 & 0x7F) << 10) | *(_DWORD *)a1 & 0xFFFE03FF;
                                if ( ((unsigned int (__fastcall *)(unsigned __int16 *))a4)(a1) )
                                {
                                  v174 = *((_BYTE *)a1 + 23);
                                  *((_DWORD *)a1 + 1) = 0;
                                  *((_BYTE *)a1 + 23) = v174 & 0x80 | 7;
                                }
                                v16 = *((unsigned __int8 *)a1 + 23);
                                v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
                                if ( (v16 & 0x7F) != 0 )
                                  goto LABEL_481;
                                ++v14;
                                v15 = 0;
                              }
                              else
                              {
                                ++v14;
                                v15 = 0;
                              }
                            }
                          }
                          else
                          {
                            ++v14;
                            v15 = 0;
                            v10 = 62;
                          }
                        }
                        else
                        {
                          if ( (unsigned int)sub_2520(a1, a2, v7, a4, v5, v16) )
                            v10 = (*(_BYTE *)a1 & 3) == 0 ? 18 : 4;
                          if ( (v16 & 0x7F) != 0 )
                            __assert_fail(
                              "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                              "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                              0x73Eu,
                              "http_parser_execute");
                          v7 = v178[7];
                          if ( v7 )
                          {
                            *(_DWORD *)a1 = ((v10 & 0x7F) << 10) | *(_DWORD *)a1 & 0xFFFE03FF;
                            if ( ((unsigned int (__fastcall *)(unsigned __int16 *))v7)(a1) )
                            {
                              v171 = *((_BYTE *)a1 + 23);
                              *((_DWORD *)a1 + 1) = 0;
                              *((_BYTE *)a1 + 23) = v171 & 0x80 | 7;
                            }
                            v16 = *((unsigned __int8 *)a1 + 23);
                            v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
                            if ( (v16 & 0x7F) != 0 )
                              goto LABEL_481;
                            ++v14;
                            v15 = 0;
                          }
                          else
                          {
                            ++v14;
                            v15 = 0;
                          }
                        }
                      }
                      goto LABEL_39;
                    }
                    v176 = v16;
                    v115 = v14;
                    v124 = sub_2520(a1, a2, v7, a4, v5, v190);
                    v125 = 1LL;
                    if ( v124 )
                      v125 = (*(_BYTE *)a1 & 3) == 0 ? 18 : 4;
                    if ( (v176 & 0x7F) != 0 )
                      __assert_fail(
                        "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                        "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                        0x730u,
                        "http_parser_execute");
                    v126 = (__int64 (__fastcall *)(unsigned __int16 *))v178[7];
                    if ( !v126 )
                      goto LABEL_540;
                    v177 = v114;
                    *(_DWORD *)a1 = ((v125 & 0x7F) << 10) | *(_DWORD *)a1 & 0xFFFE03FF;
                    v127 = v126(a1);
                    v114 = v177;
                    if ( v127 )
                    {
                      v172 = *((_BYTE *)a1 + 23);
                      *((_DWORD *)a1 + 1) = 0;
                      *((_BYTE *)a1 + 23) = v172 & 0x80 | 7;
                    }
                    v125 = (*(_DWORD *)a1 >> 10) & 0x7F;
                    if ( (*((_BYTE *)a1 + 23) & 0x7F) == 0 )
                    {
LABEL_540:
                      *(_QWORD *)a1 = *(_QWORD *)a1 & 0xFFFE03FFLL | (v125 << 10) & 0xFFFFFFFF0001FC00LL;
                      return (__int64)&v14[-v114 + 1];
                    }
                    return (__int64)&v115[-v114 + 1];
                  }
                  *((_BYTE *)a1 + 23) |= 0x80u;
                }
                *a1 |= 0x100u;
                goto LABEL_528;
              }
              if ( (v16 & 0x7F) != 0 )
                __assert_fail(
                  "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                  "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                  0x6E4u,
                  "http_parser_execute");
              v7 = v178[9];
              if ( !v7 )
              {
                a4 = (__int64)v14;
LABEL_660:
                v14 = (unsigned __int8 *)a4;
                if ( (unsigned int)sub_2520(a1, a2, v7, a4, v5, v16) )
                {
LABEL_298:
                  v10 = (*(_BYTE *)a1 & 3) == 0 ? 18 : 4;
LABEL_299:
                  if ( (v16 & 0x7F) != 0 )
                    __assert_fail(
                      "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                      "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                      0x77Eu,
                      "http_parser_execute");
                }
                v7 = v178[7];
                if ( !v7 )
                  goto LABEL_304;
                *(_DWORD *)a1 = ((v10 & 0x7F) << 10) | *(_DWORD *)a1 & 0xFFFE03FF;
                if ( ((unsigned int (__fastcall *)(unsigned __int16 *))v7)(a1) )
                {
                  v144 = *((_BYTE *)a1 + 23);
                  *((_DWORD *)a1 + 1) = v15;
                  *((_BYTE *)a1 + 23) = v144 & 0x80 | 7;
                }
                v16 = *((unsigned __int8 *)a1 + 23);
                v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
                if ( (v16 & 0x7F) == 0 )
                {
LABEL_304:
                  if ( (v16 & 0x80u) != 0LL )
                  {
                    v167 = *(_DWORD *)a1;
                    *((_DWORD *)a1 + 1) = v15;
                    *(_DWORD *)a1 = ((v10 & 0x7F) << 10) | v167 & 0xFFFE03FF;
                    return v14 - (unsigned __int8 *)v190 + 1;
                  }
                  ++v14;
                  goto LABEL_39;
                }
LABEL_481:
                v114 = (__int64)v190;
                v115 = v14;
                return (__int64)&v115[-v114 + 1];
              }
              *(_DWORD *)a1 = *(_DWORD *)a1 & 0xFFFE03FF | 0x10000;
              if ( ((unsigned int (__fastcall *)(unsigned __int16 *))v7)(a1) )
              {
                v154 = *((_BYTE *)a1 + 23);
                *((_DWORD *)a1 + 1) = v15;
                *((_BYTE *)a1 + 23) = v154 & 0x80 | 0xA;
              }
              v16 = *((unsigned __int8 *)a1 + 23);
              v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
              if ( (v16 & 0x7F) != 0 )
                return v14 - (unsigned __int8 *)v190;
              v18 = 10LL;
            }
            break;
        }
        goto LABEL_21;
      case 0x31u:
        v41 = *((_BYTE *)a1 + 2) >> 1;
        goto LABEL_326;
      case 0x32u:
        a2 = (unsigned int)dword_B010;
        v64 = *((_BYTE *)a1 + 2) >> 1;
        if ( v14 == v13 )
          goto LABEL_260;
        v5 = (unsigned __int64)v14;
        a4 = v179 ^ 1u;
        while ( 2 )
        {
          v18 = (unsigned int)*(char *)v5;
          if ( *(_BYTE *)v5 != 13 )
          {
            if ( *(_BYTE *)v5 != 10 )
            {
              if ( *(_BYTE *)v5 != 9 && v179 != 1 && (*(_BYTE *)v5 <= 0x1Fu || *(_BYTE *)v5 == 127) )
              {
LABEL_626:
                v8 = a1;
                a3 = v190;
                v6 = v15;
                v20 = (unsigned __int8 *)v5;
                *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x18;
                v21 = 50;
                goto LABEL_29;
              }
              v7 = (unsigned int)v18 | 0x20;
              switch ( v64 )
              {
                case 0:
                  v100 = &v13[-v5];
                  if ( (unsigned __int64)&v13[-v5] > (unsigned int)a2 )
                    v100 = (unsigned __int8 *)(unsigned int)a2;
                  v7 = (unsigned __int64)&v100[v5];
                  if ( (unsigned __int8 *)v5 == &v100[v5] )
                    goto LABEL_407;
                  while ( 2 )
                  {
                    if ( (_BYTE)v18 != 9 && v179 != 1 && ((unsigned __int8)v18 <= 0x1Fu || (_BYTE)v18 == 127) )
                      goto LABEL_626;
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
LABEL_407:
                  if ( (unsigned __int8 *)v5 == v13 )
                    goto LABEL_260;
LABEL_379:
                  ++v5;
                  goto LABEL_259;
                case 9:
                case 13:
                  __assert_fail(
                    "0 && \"Shouldn't get here.\"",
                    "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                    0x5F1u,
                    "http_parser_execute");
                case 10:
                  if ( *(_BYTE *)v5 != 32 )
                    goto LABEL_386;
                  goto LABEL_379;
                case 11:
                  if ( *(_BYTE *)v5 == 32 )
                  {
                    ++v5;
                    v64 = 12;
                  }
                  else
                  {
LABEL_386:
                    v95 = *(_BYTE *)v5 - 48;
                    if ( v95 > 9u || (v96 = *((_QWORD *)a1 + 1), v7 = (char)v95 + 10 * v96, v96 > 0x1999999999999998LL) )
                    {
                      v8 = a1;
                      a3 = v190;
                      v6 = v15;
                      v20 = (unsigned __int8 *)v5;
                      *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x19;
                      *((_BYTE *)v8 + 2) = v8[1] & 1 | 0x16;
                      v21 = 50;
                      goto LABEL_29;
                    }
                    *((_QWORD *)a1 + 1) = v7;
                    ++v5;
                    v64 = 11;
                  }
LABEL_259:
                  if ( v13 != (unsigned __int8 *)v5 )
                    continue;
LABEL_260:
                  v7 = a1[1] & 1;
                  *((_BYTE *)a1 + 2) = v7 | (2 * v64);
                  break;
                case 12:
                  if ( *(_BYTE *)v5 == 32 )
                    goto LABEL_379;
                  v8 = a1;
                  a3 = v190;
                  v6 = v15;
                  v20 = (unsigned __int8 *)v5;
                  *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x19;
                  *((_BYTE *)v8 + 2) = v8[1] & 1 | 0x18;
                  v21 = 50;
                  goto LABEL_29;
                case 15:
                  v92 = *((_BYTE *)a1 + 3);
                  ++v5;
                  v93 = (v92 + 1) & 0x7F;
                  v94 = v93 | v92 & 0x80;
                  *((_BYTE *)a1 + 3) = v94;
                  if ( v93 <= 7u && aChunked[v93 & 0x7F] == (_BYTE)v7 )
                  {
                    if ( (v94 & 0x7F) == 6 )
                      v64 = 21;
                  }
                  else
                  {
                    v64 = 0;
                  }
                  goto LABEL_259;
                case 16:
                  ++v5;
                  v64 = 17;
                  if ( ((unsigned __int8)v18 | 0x20) != 0x6B )
                  {
                    v64 = 18;
                    if ( ((unsigned __int8)v18 | 0x20) != 0x63 )
                    {
                      v64 = 19;
                      if ( ((unsigned __int8)v18 | 0x20) != 0x75 )
                      {
                        if ( ((unsigned __int8)v18 | 0x20) == 0x20
                          || (v64 = 20, !byte_7B60[(unsigned __int8)v18 | 0x20]) )
                        {
                          v64 = 16 * (((unsigned __int8)v18 | 0x20) == 32);
                        }
                      }
                    }
                  }
                  goto LABEL_259;
                case 17:
                  v89 = *((_BYTE *)a1 + 3);
                  ++v5;
                  v90 = (v89 + 1) & 0x7F;
                  v91 = v90 | v89 & 0x80;
                  *((_BYTE *)a1 + 3) = v91;
                  if ( v90 > 0xAu || aKeepAlive[v90 & 0x7F] != (_BYTE)v7 )
                    goto LABEL_368;
                  if ( (v91 & 0x7F) == 9 )
                    v64 = 22;
                  goto LABEL_259;
                case 18:
                  v101 = *((_BYTE *)a1 + 3);
                  ++v5;
                  v102 = (v101 + 1) & 0x7F;
                  v103 = v102 | v101 & 0x80;
                  *((_BYTE *)a1 + 3) = v103;
                  if ( v102 > 5u || aClose[v102 & 0x7F] != (_BYTE)v7 )
                    goto LABEL_368;
                  if ( (v103 & 0x7F) == 4 )
                    v64 = 23;
                  goto LABEL_259;
                case 19:
                  v97 = *((_BYTE *)a1 + 3);
                  ++v5;
                  v98 = (v97 + 1) & 0x7F;
                  v99 = v98 | v97 & 0x80;
                  *((_BYTE *)a1 + 3) = v99;
                  if ( v98 <= 7u && aUpgrade[v98 & 0x7F] == (_BYTE)v7 )
                  {
                    if ( (v99 & 0x7F) == 6 )
                      v64 = 24;
                  }
                  else
                  {
LABEL_368:
                    v64 = 20;
                  }
                  goto LABEL_259;
                case 20:
                  ++v5;
                  if ( (_BYTE)v18 == 44 )
                  {
                    *((_BYTE *)a1 + 3) &= 0x80u;
                    v64 = 16;
                  }
                  goto LABEL_259;
                case 21:
                  ++v5;
                  if ( (_BYTE)v18 != 32 )
                    v64 = 0;
                  goto LABEL_259;
                case 22:
                case 23:
                case 24:
                  ++v5;
                  if ( (_BYTE)v18 == 44 )
                  {
                    v130 = *a1 >> 2;
                    if ( v64 == 22 )
                    {
                      v131 = v130 | 2;
                    }
                    else
                    {
                      v131 = v130 | 8;
                      if ( v64 == 23 )
                        v131 = (*a1 >> 2) | 4;
                    }
                    v64 = 16;
                    v7 = (4 * v131) | *(_DWORD *)a1 & 0x80FFFC03;
                    *(_DWORD *)a1 = v7;
                  }
                  else if ( (_BYTE)v18 != 32 )
                  {
                    v64 = 20;
                  }
                  goto LABEL_259;
                default:
                  ++v5;
                  v64 = 0;
                  goto LABEL_259;
              }
LABEL_261:
              v5 = (unsigned __int64)(v13 - 1);
LABEL_262:
              v15 += v5 - (_DWORD)v14;
              if ( v15 <= (unsigned int)a2 )
              {
                v14 = (unsigned __int8 *)(v5 + 1);
                goto LABEL_39;
              }
              v8 = a1;
              a3 = v190;
              v6 = v15;
              v20 = (unsigned __int8 *)v5;
              *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xC;
              v21 = v10 & 0x7F;
              goto LABEL_29;
            }
            v15 += v5 - (_DWORD)v14;
            if ( (unsigned int)a2 < v15 )
            {
              v8 = a1;
              a3 = v190;
              v6 = v15;
              v20 = (unsigned __int8 *)v5;
              *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0xC;
              v21 = 52;
              goto LABEL_29;
            }
            *((_BYTE *)a1 + 2) = (2 * v64) | a1[1] & 1;
            if ( (v16 & 0x7F) != 0 )
              __assert_fail(
                "HTTP_PARSER_ERRNO(parser) == HPE_OK",
                "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
                0x5CEu,
                "http_parser_execute");
            if ( !v185 )
            {
              v14 = (unsigned __int8 *)(v5 + 1);
              v10 = 51;
              goto LABEL_39;
            }
            a4 = v178[4];
            if ( !a4 )
            {
              v185 = 0LL;
              v14 = (unsigned __int8 *)(v5 + 1);
              v10 = 51;
              goto LABEL_39;
            }
            v141 = *(_DWORD *)a1 & 0xFFFE03FF;
            BYTE1(v141) |= 0xD0u;
            *(_DWORD *)a1 = v141;
            a2 = (unsigned __int64)v185;
            v195 = (unsigned __int8 *)v5;
            v142 = ((__int64 (__fastcall *)(unsigned __int16 *, char *, unsigned __int64))a4)(
                     a1,
                     v185,
                     v5 - (_QWORD)v185);
            v5 = (unsigned __int64)v195;
            if ( v142 )
            {
              v168 = *((_BYTE *)a1 + 23);
              *((_DWORD *)a1 + 1) = v15;
              *((_BYTE *)a1 + 23) = v168 & 0x80 | 4;
            }
            v16 = *((unsigned __int8 *)a1 + 23);
            v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
            if ( (v16 & 0x7F) != 0 )
              return v195 - (unsigned __int8 *)v190;
            v185 = 0LL;
            v14 = v195;
            goto LABEL_21;
          }
          break;
        }
        v134 = v64 & 0x7F;
        v135 = (2 * v64) | a1[1] & 1;
        *((_BYTE *)a1 + 2) = v135;
        if ( (v16 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x5C6u,
            "http_parser_execute");
        v136 = v185;
        if ( !v185
          || (v137 = (__int64 (__fastcall *)(unsigned __int16 *, char *, unsigned __int64, __int64))v178[4]) == 0LL )
        {
          v10 = 52;
LABEL_606:
          v185 = 0LL;
          v7 = (2 * v134) | v135 & 1u;
          *((_BYTE *)a1 + 2) = v7;
          if ( (unsigned __int8 *)v5 != v13 )
            goto LABEL_262;
          goto LABEL_261;
        }
        v138 = v185;
        v139 = *(_DWORD *)a1 & 0xFFFE03FF;
        BYTE1(v139) |= 0xD0u;
        *(_DWORD *)a1 = v139;
        v187 = (char *)v5;
        v140 = v137(a1, v138, v5 - (_QWORD)v136, a4);
        v5 = (unsigned __int64)v187;
        if ( v140 )
        {
          v170 = *((_BYTE *)a1 + 23);
          *((_DWORD *)a1 + 1) = v15;
          *((_BYTE *)a1 + 23) = v170 & 0x80 | 4;
        }
        v16 = *((unsigned __int8 *)a1 + 23);
        v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
        if ( (v16 & 0x7F) == 0 )
        {
          a2 = (unsigned int)dword_B010;
          v135 = *((_BYTE *)a1 + 2);
          goto LABEL_606;
        }
        return v187 - v190 + 1;
      case 0x33u:
        v40 = *((unsigned __int8 *)a1 + 2);
        if ( (_BYTE)v18 == 32 || (_BYTE)v18 == 9 )
        {
          v7 = v40 & 0xFFFFFFFE;
          if ( (v40 & 0xFE) == 0x16 )
          {
            *((_BYTE *)a1 + 2) = v40 & 1 | 0x18;
            *((_BYTE *)a1 + 3) &= 0x80u;
            if ( !v185 )
              v185 = (char *)v14;
LABEL_443:
            ++v14;
            v10 = 50;
          }
          else
          {
LABEL_96:
            v41 = (unsigned __int8)v40 >> 1;
LABEL_326:
            a2 = (unsigned __int64)v185;
            if ( !v185 )
              a2 = (unsigned __int64)v14;
            *((_BYTE *)a1 + 3) &= 0x80u;
            v7 = (unsigned int)v18 | 0x20;
            v185 = (char *)a2;
            switch ( (v41 + 119) & 0x7F )
            {
              case 0:
                ++v14;
                v111 = a1[1] & 1;
                if ( ((unsigned __int8)v18 | 0x20) == 0x6B )
                {
                  v10 = 50;
                  *((_BYTE *)a1 + 2) = v111 | 0x22;
                }
                else if ( ((unsigned __int8)v18 | 0x20) == 0x63 )
                {
                  v10 = 50;
                  *((_BYTE *)a1 + 2) = v111 | 0x24;
                }
                else
                {
                  v10 = 50;
                  if ( ((unsigned __int8)v18 | 0x20) == 0x75 )
                    *((_BYTE *)a1 + 2) = v111 | 0x26;
                  else
                    *((_BYTE *)a1 + 2) = v111 | 0x28;
                }
                goto LABEL_39;
              case 1:
                v107 = v18 - 48;
                if ( v107 > 9u )
                {
                  v20 = v14;
                  v8 = a1;
                  a3 = v190;
                  v6 = v15;
                  *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x19;
                  v21 = 50;
                  goto LABEL_29;
                }
                v108 = *a1;
                v109 = *a1 >> 2;
                if ( (v109 & 0x80u) != 0 )
                {
                  v20 = v14;
                  v8 = a1;
                  a3 = v190;
                  v6 = v15;
                  *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1A;
                  v21 = 50;
                  goto LABEL_29;
                }
                LOWORD(v108) = v108 & 0xFC03;
                ++v14;
                *((_QWORD *)a1 + 1) = (char)v107;
                v10 = 50;
                v7 = (4 * ((unsigned __int8)v109 | 0x80)) | v108;
                v110 = *((_BYTE *)a1 + 2);
                *a1 = v7;
                *((_BYTE *)a1 + 2) = v110 & 1 | 0x16;
                break;
              case 3:
              case 7:
                goto LABEL_443;
              case 4:
                ++v14;
                if ( ((unsigned __int8)v18 | 0x20) == 0x63 )
                {
                  v10 = 50;
                  *((_BYTE *)a1 + 2) = a1[1] & 1 | 0x1E;
                }
                else
                {
                  *((_BYTE *)a1 + 2) &= 1u;
                  v10 = 50;
                }
                goto LABEL_39;
              case 5:
                *((_BYTE *)a1 + 2) &= 1u;
                ++v14;
                v10 = 50;
                *a1 |= 0x80u;
                goto LABEL_39;
              default:
                *((_BYTE *)a1 + 2) &= 1u;
                ++v14;
                v10 = 50;
                goto LABEL_39;
            }
          }
          goto LABEL_39;
        }
        v46 = (unsigned __int8)v40 >> 1;
        if ( v46 == 23 )
        {
          *a1 |= 0x10u;
        }
        else if ( v46 > 0x17u )
        {
          if ( v46 == 24 )
            *a1 |= 0x20u;
        }
        else if ( v46 == 21 )
        {
          *a1 |= 4u;
        }
        else if ( v46 == 22 )
        {
          *a1 |= 8u;
        }
        goto LABEL_134;
      case 0x34u:
        if ( (_BYTE)v18 == 10 )
        {
          ++v14;
          v10 = 51;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x17;
        v21 = 52;
        goto LABEL_29;
      case 0x35u:
        if ( v15 != 1 )
          __assert_fail(
            "nread == 1",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x787u,
            "http_parser_execute");
        if ( (*(_BYTE *)a1 & 4) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x788u,
            "http_parser_execute");
        v69 = byte_7A60[(unsigned __int8)v18];
        if ( (_BYTE)v69 != 0xFF )
        {
          *((_QWORD *)a1 + 1) = v69;
          ++v14;
          v10 = 54;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = 1;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1B;
        v21 = 53;
        goto LABEL_29;
      case 0x36u:
        if ( (*(_BYTE *)a1 & 4) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x799u,
            "http_parser_execute");
        if ( (_BYTE)v18 == 13 )
        {
          ++v14;
          v10 = 56;
          goto LABEL_39;
        }
        v7 = (unsigned __int64)byte_7A60;
        v62 = byte_7A60[(unsigned __int8)v18];
        if ( (_BYTE)v62 == 0xFF )
        {
          if ( (_BYTE)v18 != 59 && (_BYTE)v18 != 32 )
          {
            v20 = v14;
            v8 = a1;
            a3 = v190;
            v6 = v15;
            *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1B;
            v21 = 54;
            goto LABEL_29;
          }
          ++v14;
          v10 = 55;
          goto LABEL_39;
        }
        v7 = *((_QWORD *)a1 + 1);
        v63 = 16 * v7 + v62;
        a4 = 0xFFFFFFFFFFFFFFELL;
        if ( v7 <= 0xFFFFFFFFFFFFFFELL )
        {
          *((_QWORD *)a1 + 1) = v63;
          ++v14;
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x19;
        v21 = 54;
        goto LABEL_29;
      case 0x37u:
        if ( (*(_BYTE *)a1 & 4) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7BCu,
            "http_parser_execute");
        ++v14;
        if ( (_BYTE)v18 == 13 )
          v10 = 56;
        goto LABEL_39;
      case 0x38u:
        v43 = *a1;
        v44 = *a1 >> 2;
        if ( (*a1 & 4) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7C7u,
            "http_parser_execute");
        if ( (_BYTE)v18 == 10 )
        {
          v45 = *((_QWORD *)a1 + 1) == 0LL;
          *((_DWORD *)a1 + 1) = 0;
          v10 = 59;
          if ( v45 )
          {
            v10 = 44;
            *a1 = (4 * ((unsigned __int8)v44 | 0x10)) | v43 & 0xFC03;
          }
          if ( (v16 & 0x7F) != 0 )
            __assert_fail(
              "HTTP_PARSER_ERRNO(parser) == HPE_OK",
              "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
              0x7D3u,
              "http_parser_execute");
          v7 = v178[8];
          if ( v7 )
          {
            *(_DWORD *)a1 = ((v10 & 0x7F) << 10) | *(_DWORD *)a1 & 0xFFFE03FF;
            if ( ((unsigned int (__fastcall *)(unsigned __int16 *))v7)(a1) )
            {
              v145 = *((_BYTE *)a1 + 23);
              *((_DWORD *)a1 + 1) = 0;
              *((_BYTE *)a1 + 23) = v145 & 0x80 | 9;
            }
            v16 = *((unsigned __int8 *)a1 + 23);
            v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
            if ( (v16 & 0x7F) != 0 )
              goto LABEL_481;
            ++v14;
            v15 = 0;
          }
          else
          {
            ++v14;
            v15 = 0;
          }
          goto LABEL_39;
        }
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
        v21 = 56;
        goto LABEL_29;
      case 0x39u:
        if ( (_BYTE)v18 == 10 )
          goto LABEL_136;
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
        v21 = 57;
        goto LABEL_29;
      case 0x3Au:
        if ( (_BYTE)v18 == 10 )
          goto LABEL_313;
        v20 = v14;
        v8 = a1;
        a3 = v190;
        v6 = v15;
        *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
        v21 = 58;
        goto LABEL_29;
      case 0x3Bu:
        v65 = *((_QWORD *)a1 + 1);
        v7 = v13 - v14;
        if ( v13 - v14 > v65 )
          v7 = *((_QWORD *)a1 + 1);
        if ( (*(_BYTE *)a1 & 4) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7DCu,
            "http_parser_execute");
        a4 = v65 - 1;
        if ( v65 - 1 > 0xFFFFFFFFFFFFFFFDLL )
          __assert_fail(
            "parser->content_length != 0 && parser->content_length != ULLONG_MAX",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7DDu,
            "http_parser_execute");
        a2 = (unsigned __int64)v188;
        if ( !v188 )
          a2 = (unsigned __int64)v14;
        v66 = v65 - v7;
        v14 += v7;
        *((_QWORD *)a1 + 1) = v66;
        v188 = (char *)a2;
        if ( !v66 )
          v10 = 60;
        goto LABEL_39;
      case 0x3Cu:
        if ( (*(_BYTE *)a1 & 4) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7EFu,
            "http_parser_execute");
        if ( *((_QWORD *)a1 + 1) )
          __assert_fail(
            "parser->content_length == 0",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7F0u,
            "http_parser_execute");
        if ( (_BYTE)v18 != 13 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 60;
          goto LABEL_29;
        }
        if ( (v16 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7F3u,
            "http_parser_execute");
        if ( v188 )
        {
          a4 = v178[6];
          if ( a4 )
          {
            v60 = *(_DWORD *)a1 & 0xFFFE03FF;
            BYTE1(v60) |= 0xF4u;
            *(_DWORD *)a1 = v60;
            a2 = (unsigned __int64)v188;
            if ( ((unsigned int (__fastcall *)(unsigned __int16 *, char *, signed __int64))a4)(
                   a1,
                   v188,
                   v14 - (unsigned __int8 *)v188) )
            {
              v149 = *((_BYTE *)a1 + 23);
              *((_DWORD *)a1 + 1) = v15;
              *((_BYTE *)a1 + 23) = v149 & 0x80 | 6;
            }
            v16 = *((unsigned __int8 *)a1 + 23);
            v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
            if ( (v16 & 0x7F) != 0 )
              goto LABEL_481;
            v188 = 0LL;
            ++v14;
          }
          else
          {
            v188 = 0LL;
            ++v14;
            v10 = 61;
          }
        }
        else
        {
          ++v14;
          v10 = 61;
        }
        goto LABEL_39;
      case 0x3Du:
        if ( (*(_BYTE *)a1 & 4) == 0 )
          __assert_fail(
            "parser->flags & F_CHUNKED",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7F7u,
            "http_parser_execute");
        if ( (_BYTE)v18 != 10 )
        {
          v20 = v14;
          v8 = a1;
          a3 = v190;
          v6 = v15;
          *((_BYTE *)v8 + 23) = *((_BYTE *)v8 + 23) & 0x80 | 0x1E;
          v21 = 61;
          goto LABEL_29;
        }
        *((_DWORD *)a1 + 1) = 0;
        if ( (v16 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x7FCu,
            "http_parser_execute");
        v7 = v178[9];
        if ( v7 )
        {
          v61 = *(_DWORD *)a1 & 0xFFFE03FF;
          BYTE1(v61) |= 0xD4u;
          *(_DWORD *)a1 = v61;
          if ( ((unsigned int (__fastcall *)(unsigned __int16 *))v7)(a1) )
          {
            v143 = *((_BYTE *)a1 + 23);
            *((_DWORD *)a1 + 1) = 0;
            *((_BYTE *)a1 + 23) = v143 & 0x80 | 0xA;
          }
          v16 = *((unsigned __int8 *)a1 + 23);
          v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
          if ( (v16 & 0x7F) != 0 )
            goto LABEL_481;
          ++v14;
          v15 = 0;
        }
        else
        {
          ++v14;
          v15 = 0;
          v10 = 53;
        }
        goto LABEL_39;
      case 0x3Eu:
        v53 = *((_QWORD *)a1 + 1);
        v7 = v13 - v14;
        if ( v13 - v14 > v53 )
          v7 = *((_QWORD *)a1 + 1);
        if ( v53 - 1 > 0xFFFFFFFFFFFFFFFDLL )
          __assert_fail(
            "parser->content_length != 0 && parser->content_length != ULLONG_MAX",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x756u,
            "http_parser_execute");
        a2 = (unsigned __int64)v188;
        a4 = (__int64)&v14[v7 - 1];
        if ( !v188 )
          a2 = (unsigned __int64)v14;
        v54 = v53 - v7;
        *((_QWORD *)a1 + 1) = v54;
        v188 = (char *)a2;
        if ( v54 )
        {
          v14 += v7;
          goto LABEL_39;
        }
        if ( (v16 & 0x7F) != 0 )
          __assert_fail(
            "HTTP_PARSER_ERRNO(parser) == HPE_OK",
            "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
            0x76Eu,
            "http_parser_execute");
        v5 = v178[6];
        if ( !v5 )
        {
          v188 = 0LL;
          goto LABEL_660;
        }
        *(_DWORD *)a1 = *(_DWORD *)a1 & 0xFFFE03FF | 0x10000;
        v194 = (__int64)&v14[v7 - 1];
        v55 = ((__int64 (__fastcall *)(unsigned __int16 *, unsigned __int64, unsigned __int8 *))v5)(
                a1,
                a2,
                &v14[v7 - a2]);
        a4 = v194;
        if ( v55 )
        {
          v146 = *((_BYTE *)a1 + 23);
          *((_DWORD *)a1 + 1) = v15;
          *((_BYTE *)a1 + 23) = v146 & 0x80 | 6;
        }
        v16 = *((unsigned __int8 *)a1 + 23);
        v10 = (*(_DWORD *)a1 >> 10) & 0x7F;
        if ( (v16 & 0x7F) != 0 )
          return v194 - (_QWORD)v190;
        v188 = 0LL;
        v14 = (unsigned __int8 *)v194;
        goto LABEL_21;
      case 0x3Fu:
        v67 = a1;
        v6 = v15;
        v12 = v13;
        v68 = v14;
        v8 = v67;
        LOBYTE(v5) = v16;
        a3 = v190;
        if ( v188 )
          v68 = (unsigned __int8 *)v188;
        v188 = (char *)v68;
        goto LABEL_41;
      case 0x40u:
        if ( (unsigned int)sub_2520(a1, a2, v7, a4, v5, v16) )
          goto LABEL_298;
        goto LABEL_299;
      default:
        __assert_fail(
          "0 && \"unhandled state\"",
          "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
          0x800u,
          "http_parser_execute");
    }
  }
}
