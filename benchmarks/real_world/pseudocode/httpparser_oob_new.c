__int64 __fastcall sub_5E10(unsigned __int8 *a1, unsigned __int64 a2, int a3, __int16 *a4)
{
  unsigned __int64 v5; // r9
  int v7; // ecx
  unsigned int v9; // r10d
  unsigned __int8 *v10; // rsi
  __int64 v11; // r11
  __int64 v12; // r15
  unsigned __int64 v13; // rdx
  unsigned int v14; // r8d
  unsigned __int8 *v16; // r8
  __int16 v17; // dx
  __int16 v18; // dx
  __int64 v19; // rcx
  __int64 v20; // rsi
  char *v21; // r8
  char *v22; // rcx
  unsigned __int64 v23; // rdx
  unsigned __int8 *v24; // rcx
  unsigned __int8 *i; // rsi
  unsigned __int8 *v26; // rcx
  unsigned __int64 v27; // rdx
  __int64 v28; // rcx
  __int64 v29; // rsi
  int v30; // ecx
  unsigned __int8 *v31; // rdx
  unsigned __int64 v32; // rcx
  unsigned __int8 v33; // si
  __int16 v34; // r9
  unsigned __int8 *v35; // r10
  unsigned __int8 v36; // r8
  unsigned __int8 *v37; // rdx
  unsigned __int8 v38; // si
  int v39; // r8d
  __int16 v40; // si
  unsigned __int64 v41; // r8
  unsigned __int8 *v42; // rsi
  int v43; // r9d
  __int64 v44; // r10
  __int16 v45; // dx
  unsigned __int8 *v46; // r8
  unsigned __int8 v47; // dl
  char v48; // r11
  int v49; // r9d
  int v50; // r10d
  unsigned __int64 v51; // rdx
  unsigned __int8 *v52; // r8
  __int64 v53; // r9
  unsigned __int8 *v54; // rsi
  unsigned __int8 *v55; // r8
  unsigned __int8 v56; // dl
  unsigned __int8 *j; // rsi
  int v58; // [rsp+Ch] [rbp-3Ch]

  v5 = (unsigned __int64)&a1[a2];
  *(_DWORD *)a4 = 0;
  v58 = 0;
  v7 = a3 == 0 ? 20 : 24;
  if ( a1 >= &a1[a2] )
    return a3 != 0;
  v9 = 7;
  v10 = a1;
  v11 = 0x100003600LL;
  v12 = 0x2C007FF200000000LL;
  do
  {
    v13 = *v10;
    if ( (unsigned __int8)v13 <= 0x20u )
    {
      if ( !_bittest64(&v11, v13) )
      {
        switch ( v7 )
        {
          case 21:
            goto LABEL_6;
          case 22:
            goto LABEL_11;
          case 23:
            goto LABEL_64;
          case 24:
          case 25:
            goto LABEL_42;
          case 26:
            goto LABEL_41;
          case 27:
            goto LABEL_74;
          case 28:
          case 29:
            goto LABEL_17;
          case 30:
            goto LABEL_53;
          case 31:
            goto LABEL_81;
          default:
            goto LABEL_87;
        }
      }
      return 1;
    }
    switch ( v7 )
    {
      case 21:
LABEL_6:
        if ( (unsigned __int8)((v13 | 0x20) - 97) > 0x19u )
          goto LABEL_7;
        if ( !v9 )
          goto LABEL_140;
        v16 = v10;
        v17 = 1;
        v7 = 21;
        v9 = 0;
        goto LABEL_23;
      case 22:
        goto LABEL_11;
      case 23:
        goto LABEL_64;
      case 24:
      case 25:
        goto LABEL_42;
      case 26:
        goto LABEL_41;
      case 27:
        goto LABEL_74;
      case 28:
      case 29:
        goto LABEL_17;
      case 30:
        goto LABEL_53;
      case 31:
        goto LABEL_81;
      default:
        if ( (_BYTE)v13 != 47 && (_BYTE)v13 != 42 )
        {
LABEL_87:
          if ( (unsigned __int8)((v13 | 0x20) - 97) > 0x19u )
            return 1;
          if ( v9 )
          {
            v26 = v10 + 1;
            a4[2] = (_WORD)v10 - (_WORD)a1;
            a4[3] = 1;
            v18 = *a4 | 1;
            *a4 = v18;
            if ( v5 <= (unsigned __int64)(v10 + 1) )
              goto LABEL_24;
          }
          else
          {
            v26 = v10 + 1;
            ++a4[3];
            if ( v5 <= (unsigned __int64)(v10 + 1) )
              goto LABEL_139;
          }
          v13 = v10[1];
          if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
            return 1;
          if ( (unsigned __int8)((v13 | 0x20) - 97) <= 0x19u )
          {
            while ( 1 )
            {
              v10 = v26 + 1;
              ++a4[3];
              if ( v5 <= (unsigned __int64)(v26 + 1) )
                goto LABEL_139;
              LOBYTE(v13) = v26[1];
              if ( (unsigned __int8)v13 <= 0x20u )
                return 1;
              if ( (unsigned __int8)((v13 | 0x20) - 97) > 0x19u )
                break;
LABEL_140:
              v26 = v10;
            }
            v9 = 0;
          }
          else
          {
            v10 = v26;
            v9 = 0;
          }
LABEL_7:
          if ( (_BYTE)v13 != 58 )
            return 1;
          if ( v5 > (unsigned __int64)(v10 + 1) )
          {
            LOBYTE(v13) = v10[1];
            if ( (unsigned __int8)v13 <= 0x20u )
              return 1;
            ++v10;
LABEL_11:
            if ( (_BYTE)v13 != 47 )
              return 1;
            if ( v5 > (unsigned __int64)(v10 + 1) )
            {
              LOBYTE(v13) = v10[1];
              if ( (unsigned __int8)v13 <= 0x20u )
                return 1;
              ++v10;
LABEL_64:
              if ( (_BYTE)v13 != 47 )
                return 1;
              if ( v5 > (unsigned __int64)(v10 + 1) )
              {
                v13 = v10[1];
                if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
                  return 1;
                ++v10;
                while ( 1 )
                {
LABEL_42:
                  ++v10;
                  while ( 1 )
                  {
                    v16 = v10 - 1;
                    if ( (_BYTE)v13 == 47 )
                    {
                      if ( v9 != 3 )
                      {
                        a4[9] = 1;
                        a4[8] = (_WORD)v16 - (_WORD)a1;
                        v18 = *a4 | 8;
                        *a4 = v18;
                        if ( v5 <= (unsigned __int64)v10 )
                          goto LABEL_24;
                        v13 = *v10;
                        if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
                          return 1;
                        v9 = 3;
                        goto LABEL_74;
                      }
                      ++a4[9];
                      if ( v5 > (unsigned __int64)v10 )
                      {
                        v13 = *v10;
                        if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
                          return 1;
                        goto LABEL_74;
                      }
                      goto LABEL_139;
                    }
                    if ( (_BYTE)v13 == 63 )
                    {
                      if ( v5 > (unsigned __int64)v10 )
                      {
                        v13 = *v10;
                        if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
                          return 1;
                        goto LABEL_17;
                      }
                      goto LABEL_139;
                    }
                    if ( (_BYTE)v13 == 64 )
                      break;
                    if ( (unsigned __int8)((v13 | 0x20) - 97) > 0x19u && (unsigned __int8)(v13 - 48) > 9u )
                    {
                      if ( (char)v13 > 61 )
                      {
                        v27 = (unsigned int)(v13 - 91);
                        if ( (unsigned __int8)v27 > 0x23u )
                          return 1;
                        v28 = 0x800000015LL;
                        if ( !_bittest64(&v28, v27) )
                          return 1;
                      }
                      else if ( (char)v13 <= 32 || !_bittest64(&v12, v13) )
                      {
                        return 1;
                      }
                    }
                    if ( v9 != 1 )
                    {
                      v17 = 2;
                      v7 = 25;
                      v9 = 1;
                      goto LABEL_23;
                    }
                    ++a4[5];
                    if ( v5 <= (unsigned __int64)v10 )
                      goto LABEL_139;
                    v13 = *v10;
                    if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
                      return 1;
                    ++v10;
                    v9 = 1;
                  }
                  if ( v9 == 1 )
                  {
                    ++a4[5];
                    if ( v5 <= (unsigned __int64)v10 )
                    {
                      v58 = 1;
                      v18 = *a4;
                      goto LABEL_24;
                    }
                    v13 = *v10;
                    if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
                      return 1;
                    v58 = 1;
                  }
                  else
                  {
                    *a4 |= 2u;
                    a4[5] = 1;
                    a4[4] = (_WORD)v16 - (_WORD)a1;
                    if ( v5 <= (unsigned __int64)v10 )
                    {
                      v58 = 1;
                      goto LABEL_100;
                    }
                    v13 = *v10;
                    if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
                      return 1;
                    v58 = 1;
                    v9 = 1;
                  }
LABEL_41:
                  if ( (_BYTE)v13 == 64 )
                    return 1;
                }
              }
            }
          }
LABEL_139:
          v18 = *a4;
          goto LABEL_24;
        }
        if ( v9 == 3 )
        {
          ++a4[9];
          if ( v5 > (unsigned __int64)(v10 + 1) )
          {
            v13 = v10[1];
            if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
              return 1;
            ++v10;
            goto LABEL_74;
          }
          goto LABEL_139;
        }
        a4[9] = 1;
        a4[8] = (_WORD)v10 - (_WORD)a1;
        v18 = *a4 | 8;
        *a4 = v18;
        if ( v5 <= (unsigned __int64)(v10 + 1) )
          goto LABEL_24;
        v13 = v10[1];
        if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
          return 1;
        ++v10;
        v9 = 3;
LABEL_74:
        while ( ((1 << (v13 & 7)) & byte_7360[(unsigned __int8)v13 >> 3]) != 0 )
        {
          if ( v9 != 3 )
          {
            v16 = v10;
            v17 = 8;
            v7 = 27;
            v9 = 3;
            goto LABEL_23;
          }
          ++v10;
          ++a4[9];
          if ( v5 <= (unsigned __int64)v10 )
            goto LABEL_139;
          v13 = *v10;
          if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
            return 1;
        }
        if ( (_BYTE)v13 == 35 )
        {
          if ( v5 > (unsigned __int64)(v10 + 1) )
          {
            v13 = v10[1];
            if ( (unsigned __int8)v13 > 0x20u || !_bittest64(&v11, v13) )
            {
              ++v10;
              goto LABEL_53;
            }
            return 1;
          }
          goto LABEL_139;
        }
        if ( (_BYTE)v13 != 63 )
          return 1;
        if ( v5 <= (unsigned __int64)(v10 + 1) )
          goto LABEL_139;
        v13 = v10[1];
        if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
          return 1;
        ++v10;
LABEL_17:
        ++v10;
        break;
    }
    while ( 1 )
    {
      v16 = v10 - 1;
      if ( ((1 << (v13 & 7)) & byte_7360[(unsigned __int8)v13 >> 3]) != 0 )
        goto LABEL_21;
      if ( (_BYTE)v13 == 35 )
        break;
      if ( (_BYTE)v13 != 63 )
        return 1;
LABEL_21:
      if ( v9 != 4 )
      {
        v17 = 16;
        v7 = 29;
        v9 = 4;
        goto LABEL_23;
      }
      ++a4[11];
      if ( v5 <= (unsigned __int64)v10 )
        goto LABEL_139;
      v13 = *v10;
      if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
        return 1;
      ++v10;
      v9 = 4;
    }
    if ( v5 <= (unsigned __int64)v10 )
      goto LABEL_139;
    v13 = *v10;
    if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
      return 1;
LABEL_53:
    if ( ((1 << (v13 & 7)) & byte_7360[(unsigned __int8)v13 >> 3]) != 0 )
    {
      if ( v9 != 5 )
      {
        v24 = v10 + 1;
        a4[13] = 1;
        a4[12] = (_WORD)v10 - (_WORD)a1;
        v18 = *a4 | 0x20;
        *a4 = v18;
        if ( (unsigned __int64)(v10 + 1) < v5 )
          goto LABEL_58;
        break;
      }
LABEL_134:
      ++a4[13];
      if ( v5 > (unsigned __int64)(v10 + 1) )
      {
        v13 = v10[1];
        if ( (unsigned __int8)v13 > 0x20u || !_bittest64(&v11, v13) )
        {
          ++v10;
          goto LABEL_81;
        }
        return 1;
      }
      goto LABEL_139;
    }
    if ( (_BYTE)v13 == 35 )
    {
      if ( (unsigned __int64)++v10 >= v5 )
        goto LABEL_139;
      v13 = *v10;
      if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
        return 1;
      goto LABEL_53;
    }
    if ( (_BYTE)v13 != 63 )
      return 1;
    if ( v9 == 5 )
      goto LABEL_134;
    v24 = v10 + 1;
    a4[13] = 1;
    a4[12] = (_WORD)v10 - (_WORD)a1;
    v18 = *a4 | 0x20;
    *a4 = v18;
    if ( v5 <= (unsigned __int64)(v10 + 1) )
      break;
LABEL_58:
    v13 = v10[1];
    if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
      return 1;
    v10 = v24;
    v9 = 5;
LABEL_81:
    for ( i = v10 + 1; ; ++i )
    {
      v16 = i - 1;
      if ( ((1 << (v13 & 7)) & byte_7360[(unsigned __int8)v13 >> 3]) == 0 && (_BYTE)v13 != 35 && (_BYTE)v13 != 63 )
        return 1;
      if ( v9 != 5 )
        break;
      ++a4[13];
      if ( v5 <= (unsigned __int64)i )
        goto LABEL_139;
      v13 = *i;
      if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
        return 1;
      v9 = 5;
    }
    v17 = 32;
    v7 = 31;
    v9 = 5;
LABEL_23:
    v18 = *a4 | v17;
    a4[2 * v9 + 2] = (_WORD)v16 - (_WORD)a1;
    a4[2 * v9 + 3] = 1;
    v10 = v16 + 1;
    *a4 = v18;
  }
  while ( (unsigned __int64)(v16 + 1) < v5 );
LABEL_24:
  if ( (v18 & 3) == 1 )
    return 1;
  if ( (v18 & 2) == 0 )
    goto LABEL_26;
LABEL_100:
  v29 = (unsigned __int16)a4[4];
  v30 = (unsigned __int16)a4[5];
  a4[5] = 0;
  v31 = &a1[v29];
  v32 = (unsigned __int64)&a1[(int)v29 + v30];
  if ( v58 )
  {
    if ( v32 <= (unsigned __int64)v31 )
      return 1;
    v41 = *v31;
    v42 = &a1[v29];
    v43 = 2;
    v44 = 0x2C007FF200000000LL;
    while ( (_BYTE)v41 != 64 )
    {
      if ( (unsigned __int8)((v41 | 0x20) - 97) > 0x19u && (unsigned __int8)(v41 - 48) > 9u )
      {
        if ( (char)v41 > 61 )
        {
          if ( (_BYTE)v41 != 95 && (_BYTE)v41 != 126 )
            return 1;
        }
        else if ( (char)v41 <= 32 || !_bittest64(&v44, v41) )
        {
          return 1;
        }
      }
      if ( v43 == 3 )
      {
        ++v42;
        ++a4[15];
        if ( v42 == (unsigned __int8 *)v32 )
          return 1;
      }
      else
      {
        v45 = (__int16)v42++;
        *a4 |= 0x40u;
        a4[14] = v45 - (_WORD)a1;
        a4[15] = 1;
        if ( v42 == (unsigned __int8 *)v32 )
          return 1;
      }
      v41 = *v42;
      v43 = 3;
    }
    v31 = v42 + 1;
    if ( (unsigned __int64)(v42 + 1) >= v32 )
      return 1;
    v33 = v42[1];
LABEL_103:
    if ( v33 != 91 )
    {
      if ( (unsigned __int8)((v33 | 0x20) - 97) > 0x19u
        && (unsigned __int8)(v33 - 48) > 9u
        && (unsigned __int8)(v33 - 45) > 1u )
      {
        return 1;
      }
      v34 = 1 - (_WORD)v31;
      a4[4] = (_WORD)v31 - (_WORD)a1;
      while ( 1 )
      {
        v35 = v31 + 1;
        a4[5] = v34 + (_WORD)v31;
        if ( (unsigned __int64)(v31 + 1) >= v32 )
          goto LABEL_168;
        v36 = v31[1];
        if ( (unsigned __int8)((v36 | 0x20) - 97) > 0x19u
          && (unsigned __int8)(v36 - 48) > 9u
          && (unsigned __int8)(v36 - 45) > 1u )
        {
          if ( v36 == 58 )
          {
            v37 = v31 + 2;
            if ( (unsigned __int64)v37 < v32 )
            {
              v38 = v35[1];
              goto LABEL_115;
            }
          }
          return 1;
        }
        ++v31;
      }
    }
    v46 = v31 + 1;
    if ( (unsigned __int64)(v31 + 1) >= v32 )
      return 1;
    v47 = v31[1];
    if ( (unsigned __int8)(v47 - 48) <= 9u )
    {
      v49 = 1;
    }
    else
    {
      v48 = 0;
      v49 = 0;
      v50 = 5;
LABEL_195:
      if ( (unsigned __int8)((v47 | 0x20) - 97) > 5u && v47 != 58 && v47 != 46 )
      {
        if ( v47 != 37 )
          return 1;
        if ( !v48 )
          return 1;
        a4[5] = v49 + 1;
        if ( v32 <= (unsigned __int64)(v46 + 1) )
          return 1;
        v51 = v46[1];
        v52 = v46 + 2;
        v53 = 0x3FF602000000000LL;
        do
        {
          if ( (unsigned __int8)((v51 | 0x20) - 97) > 0x19u )
          {
            if ( (char)v51 > 57 )
            {
              if ( (_BYTE)v51 != 95 && (_BYTE)v51 != 126 )
                return 1;
            }
            else if ( (char)v51 <= 36 || !_bittest64(&v53, v51) )
            {
              return 1;
            }
          }
          ++a4[5];
          v54 = v52;
          if ( (unsigned __int64)v52 >= v32 )
            return 1;
          v51 = *v52++;
        }
        while ( (_BYTE)v51 != 93 );
        v55 = v54 + 1;
        if ( (unsigned __int64)(v54 + 1) >= v32 )
          goto LABEL_168;
        v56 = v54[1];
        goto LABEL_210;
      }
      ++v49;
      if ( v50 == 7 )
      {
        for ( j = v46; ; j = v46 )
        {
LABEL_218:
          ++v46;
          a4[5] = v49;
          if ( (unsigned __int64)v46 >= v32 )
            return 1;
          v47 = j[1];
          if ( v47 == 93 )
            break;
          if ( (unsigned __int8)(v47 - 48) > 9u )
          {
            v48 = 1;
            v50 = 7;
            goto LABEL_195;
          }
          ++v49;
        }
        v55 = j + 2;
        if ( (unsigned __int64)(j + 2) >= v32 )
        {
LABEL_168:
          v18 = *a4;
LABEL_26:
          if ( a3 )
          {
            if ( v18 != 6 )
              return 1;
          }
          else
          {
            v14 = 0;
            if ( (v18 & 4) == 0 )
              return v14;
          }
          v19 = (unsigned __int16)a4[6];
          v20 = (unsigned __int16)a4[7];
          v21 = (char *)&a1[v19 + v20];
          if ( (int)(v20 + (unsigned __int16)a4[6]) > a2 )
            __assert_fail(
              "off + len <= buflen && \"Port number overflow\"",
              "/mnt/disk4/patch_viewer_bench/http-parser/http_parser.c",
              0x94Cu,
              "http_parser_parse_url");
          v22 = (char *)&a1[v19];
          if ( v21 <= v22 )
          {
            LOWORD(v23) = 0;
          }
          else
          {
            v23 = *v22 - 48;
            if ( v23 > 0xFFFF )
              return 1;
            while ( v21 != ++v22 )
            {
              v23 = *v22 - 48 + 10 * v23;
              if ( v23 > 0xFFFF )
                return 1;
            }
          }
          a4[1] = v23;
          return 0;
        }
        v56 = j[2];
LABEL_210:
        if ( v56 == 58 )
        {
          v37 = v55 + 1;
          if ( (unsigned __int64)(v55 + 1) < v32 )
          {
            v38 = v55[1];
LABEL_115:
            v39 = 11;
            while ( (unsigned __int8)(v38 - 48) <= 9u )
            {
              if ( v39 == 12 )
              {
                ++v37;
                ++a4[7];
                if ( (unsigned __int64)v37 >= v32 )
                  goto LABEL_168;
              }
              else
              {
                v40 = (__int16)v37++;
                *a4 |= 4u;
                a4[6] = v40 - (_WORD)a1;
                a4[7] = 1;
                if ( (unsigned __int64)v37 >= v32 )
                  goto LABEL_168;
              }
              v38 = *v37;
              v39 = 12;
            }
          }
        }
        return 1;
      }
    }
    j = v46;
    a4[4] = (_WORD)v46 - (_WORD)a1;
    goto LABEL_218;
  }
  if ( v32 > (unsigned __int64)v31 )
  {
    v33 = *v31;
    goto LABEL_103;
  }
  return 1;
}
