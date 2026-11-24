_BOOL8 __fastcall sub_5E30(unsigned __int8 *a1, __int64 a2, int a3, __int16 *a4)
{
  unsigned __int64 v4; // r8
  int v7; // ecx
  unsigned __int8 *v8; // rdx
  int v9; // r15d
  unsigned int v10; // r9d
  __int64 v11; // r10
  __int64 v12; // r13
  unsigned __int64 v13; // rax
  unsigned __int8 *v15; // rsi
  __int16 v16; // ax
  __int16 v17; // ax
  unsigned __int64 v18; // rax
  __int64 v19; // rcx
  unsigned __int8 *j; // rdx
  unsigned __int8 *v21; // rcx
  unsigned __int64 v22; // rax
  __int64 v23; // rcx
  int v24; // edx
  unsigned __int8 *v25; // rax
  unsigned __int64 v26; // rdx
  unsigned __int8 v27; // cl
  __int16 v28; // r8
  unsigned __int8 *v29; // r9
  unsigned __int8 v30; // si
  unsigned __int8 *v31; // rax
  unsigned __int8 v32; // cl
  int v33; // esi
  __int16 v34; // cx
  unsigned __int64 v35; // rsi
  unsigned __int8 *v36; // rcx
  int v37; // r8d
  __int64 v38; // r9
  __int16 v39; // ax
  unsigned __int8 *v40; // rcx
  unsigned __int8 v41; // al
  char v42; // r10
  int v43; // r8d
  int v44; // r9d
  unsigned __int64 v45; // rax
  unsigned __int8 *v46; // rcx
  __int64 v47; // r8
  unsigned __int8 *v48; // rsi
  unsigned __int8 *v49; // rcx
  unsigned __int8 v50; // al
  unsigned __int8 *i; // rsi

  v4 = (unsigned __int64)&a1[a2];
  *(_DWORD *)a4 = 0;
  v7 = a3 == 0 ? 20 : 24;
  if ( a1 >= &a1[a2] )
    return a3 != 0;
  v8 = a1;
  v9 = 0;
  v10 = 7;
  v11 = 0x100003600LL;
  v12 = 0x800000015LL;
LABEL_3:
  v13 = *v8;
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
          goto LABEL_57;
        case 24:
        case 25:
          goto LABEL_35;
        case 26:
          goto LABEL_34;
        case 27:
          goto LABEL_67;
        case 28:
        case 29:
          goto LABEL_16;
        case 30:
          goto LABEL_46;
        case 31:
          goto LABEL_74;
        default:
          goto LABEL_80;
      }
    }
    return 1LL;
  }
  switch ( v7 )
  {
    case 21:
LABEL_6:
      if ( (unsigned __int8)((v13 | 0x20) - 97) > 0x19u )
        goto LABEL_7;
      if ( !v10 )
        goto LABEL_129;
      v15 = v8;
      v16 = 1;
      v7 = 21;
      v10 = 0;
      goto LABEL_22;
    case 22:
      goto LABEL_11;
    case 23:
      goto LABEL_57;
    case 24:
    case 25:
      break;
    case 26:
      goto LABEL_34;
    case 27:
      goto LABEL_67;
    case 28:
    case 29:
      goto LABEL_16;
    case 30:
      goto LABEL_46;
    case 31:
      goto LABEL_74;
    default:
      if ( (_BYTE)v13 == 47 || (_BYTE)v13 == 42 )
      {
        if ( v10 != 3 )
        {
          a4[8] = (_WORD)v8 - (_WORD)a1;
          a4[9] = 1;
          v17 = *a4 | 8;
          *a4 = v17;
          if ( v4 <= (unsigned __int64)(v8 + 1) )
            goto LABEL_23;
          v13 = v8[1];
          if ( (unsigned __int8)v13 > 0x20u || !_bittest64(&v11, v13) )
          {
            ++v8;
            v10 = 3;
            goto LABEL_67;
          }
          return 1LL;
        }
        ++a4[9];
        if ( v4 > (unsigned __int64)(v8 + 1) )
        {
          v13 = v8[1];
          if ( (unsigned __int8)v13 > 0x20u || !_bittest64(&v11, v13) )
          {
            ++v8;
            goto LABEL_67;
          }
          return 1LL;
        }
        goto LABEL_128;
      }
LABEL_80:
      if ( (unsigned __int8)((v13 | 0x20) - 97) > 0x19u )
        return 1LL;
      if ( v10 )
      {
        v21 = v8 + 1;
        a4[2] = (_WORD)v8 - (_WORD)a1;
        a4[3] = 1;
        v17 = *a4 | 1;
        *a4 = v17;
        if ( v4 <= (unsigned __int64)(v8 + 1) )
          goto LABEL_23;
      }
      else
      {
        v21 = v8 + 1;
        ++a4[3];
        if ( v4 <= (unsigned __int64)(v8 + 1) )
          goto LABEL_128;
      }
      v13 = v8[1];
      if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
        return 1LL;
      if ( (unsigned __int8)((v13 | 0x20) - 97) <= 0x19u )
      {
        while ( 1 )
        {
          v8 = v21 + 1;
          ++a4[3];
          if ( v4 <= (unsigned __int64)(v21 + 1) )
            goto LABEL_128;
          LOBYTE(v13) = v21[1];
          if ( (unsigned __int8)v13 <= 0x20u )
            return 1LL;
          if ( (unsigned __int8)((v13 | 0x20) - 97) > 0x19u )
            break;
LABEL_129:
          v21 = v8;
        }
        v10 = 0;
      }
      else
      {
        v8 = v21;
        v10 = 0;
      }
LABEL_7:
      if ( (_BYTE)v13 != 58 )
        return 1LL;
      if ( v4 <= (unsigned __int64)(v8 + 1) )
        goto LABEL_128;
      LOBYTE(v13) = v8[1];
      if ( (unsigned __int8)v13 <= 0x20u )
        return 1LL;
      ++v8;
LABEL_11:
      if ( (_BYTE)v13 != 47 )
        return 1LL;
      if ( v4 <= (unsigned __int64)(v8 + 1) )
        goto LABEL_128;
      LOBYTE(v13) = v8[1];
      if ( (unsigned __int8)v13 <= 0x20u )
        return 1LL;
      ++v8;
LABEL_57:
      if ( (_BYTE)v13 != 47 )
        return 1LL;
      if ( v4 <= (unsigned __int64)(v8 + 1) )
        goto LABEL_128;
      v13 = v8[1];
      if ( (unsigned __int8)v13 <= 0x20u )
      {
        if ( _bittest64(&v11, v13) )
          return 1LL;
      }
      ++v8;
      break;
  }
LABEL_35:
  ++v8;
  while ( 1 )
  {
    v15 = v8 - 1;
    if ( (_BYTE)v13 == 47 )
    {
      if ( v10 != 3 )
      {
        a4[9] = 1;
        a4[8] = (_WORD)v15 - (_WORD)a1;
        v17 = *a4 | 8;
        *a4 = v17;
        if ( v4 <= (unsigned __int64)v8 )
          goto LABEL_23;
        v13 = *v8;
        if ( (unsigned __int8)v13 > 0x20u || !_bittest64(&v11, v13) )
        {
          v10 = 3;
          goto LABEL_67;
        }
        return 1LL;
      }
      ++a4[9];
      if ( v4 > (unsigned __int64)v8 )
      {
        v13 = *v8;
        if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
          return 1LL;
LABEL_67:
        while ( ((1 << (v13 & 7)) & byte_7340[(unsigned __int8)v13 >> 3]) != 0 )
        {
          if ( v10 != 3 )
          {
            v15 = v8;
            v16 = 8;
            v7 = 27;
            v10 = 3;
            goto LABEL_22;
          }
          ++v8;
          ++a4[9];
          if ( v4 <= (unsigned __int64)v8 )
            goto LABEL_128;
          v13 = *v8;
          if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
            return 1LL;
        }
        if ( (_BYTE)v13 == 35 )
        {
          if ( v4 > (unsigned __int64)(v8 + 1) )
          {
            v13 = v8[1];
            if ( (unsigned __int8)v13 > 0x20u || !_bittest64(&v11, v13) )
            {
              ++v8;
              goto LABEL_46;
            }
            return 1LL;
          }
        }
        else
        {
          if ( (_BYTE)v13 != 63 )
            return 1LL;
          if ( v4 > (unsigned __int64)(v8 + 1) )
          {
            v13 = v8[1];
            if ( (unsigned __int8)v13 > 0x20u || !_bittest64(&v11, v13) )
            {
              ++v8;
              goto LABEL_16;
            }
            return 1LL;
          }
        }
      }
LABEL_128:
      v17 = *a4;
      goto LABEL_23;
    }
    if ( (_BYTE)v13 == 63 )
      break;
    if ( (_BYTE)v13 == 64 )
    {
      if ( v10 != 1 )
      {
        *a4 |= 2u;
        a4[4] = (_WORD)v15 - (_WORD)a1;
        a4[5] = 1;
        if ( v4 > (unsigned __int64)v8 )
        {
          v13 = *v8;
          if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
            return 1LL;
          v9 = 1;
          v10 = 1;
          goto LABEL_34;
        }
        v9 = 1;
LABEL_93:
        v23 = (unsigned __int16)a4[4];
        v24 = (unsigned __int16)a4[5];
        a4[5] = 0;
        v25 = &a1[v23];
        v26 = (unsigned __int64)&a1[(int)v23 + v24];
        if ( v9 )
        {
          if ( v26 <= (unsigned __int64)v25 )
            return 1LL;
          v35 = *v25;
          v36 = &a1[v23];
          v37 = 2;
          v38 = 0x2C007FF200000000LL;
          while ( (_BYTE)v35 != 64 )
          {
            if ( (unsigned __int8)((v35 | 0x20) - 97) > 0x19u && (unsigned __int8)(v35 - 48) > 9u )
            {
              if ( (char)v35 > 61 )
              {
                if ( (_BYTE)v35 != 95 && (_BYTE)v35 != 126 )
                  return 1LL;
              }
              else if ( (char)v35 <= 32 || !_bittest64(&v38, v35) )
              {
                return 1LL;
              }
            }
            if ( v37 == 3 )
            {
              ++v36;
              ++a4[15];
              if ( v36 == (unsigned __int8 *)v26 )
                return 1LL;
            }
            else
            {
              v39 = (__int16)v36++;
              *a4 |= 0x40u;
              a4[14] = v39 - (_WORD)a1;
              a4[15] = 1;
              if ( v36 == (unsigned __int8 *)v26 )
                return 1LL;
            }
            v35 = *v36;
            v37 = 3;
          }
          v25 = v36 + 1;
          if ( (unsigned __int64)(v36 + 1) >= v26 )
            return 1LL;
          v27 = v36[1];
        }
        else
        {
          if ( v26 <= (unsigned __int64)v25 )
            return 1LL;
          v27 = *v25;
        }
        if ( v27 != 91 )
        {
          if ( (unsigned __int8)((v27 | 0x20) - 97) > 0x19u
            && (unsigned __int8)(v27 - 48) > 9u
            && (unsigned __int8)(v27 - 45) > 1u )
          {
            return 1LL;
          }
          v28 = 1 - (_WORD)v25;
          a4[4] = (_WORD)v25 - (_WORD)a1;
          while ( 1 )
          {
            v29 = v25 + 1;
            a4[5] = v28 + (_WORD)v25;
            if ( (unsigned __int64)(v25 + 1) >= v26 )
              goto LABEL_157;
            v30 = v25[1];
            if ( (unsigned __int8)((v30 | 0x20) - 97) > 0x19u
              && (unsigned __int8)(v30 - 48) > 9u
              && (unsigned __int8)(v30 - 45) > 1u )
            {
              if ( v30 == 58 )
              {
                v31 = v25 + 2;
                if ( (unsigned __int64)v31 < v26 )
                {
                  v32 = v29[1];
                  goto LABEL_108;
                }
              }
              return 1LL;
            }
            ++v25;
          }
        }
        v40 = v25 + 1;
        if ( (unsigned __int64)(v25 + 1) >= v26 )
          return 1LL;
        v41 = v25[1];
        if ( (unsigned __int8)(v41 - 48) <= 9u )
        {
          v43 = 1;
        }
        else
        {
          v42 = 0;
          v43 = 0;
          v44 = 5;
LABEL_185:
          if ( (unsigned __int8)((v41 | 0x20) - 97) > 5u && v41 != 58 && v41 != 46 )
          {
            if ( v41 != 37 )
              return 1LL;
            if ( !v42 )
              return 1LL;
            a4[5] = v43 + 1;
            if ( v26 <= (unsigned __int64)(v40 + 1) )
              return 1LL;
            v45 = v40[1];
            v46 = v40 + 2;
            v47 = 0x3FF602000000000LL;
            do
            {
              if ( (unsigned __int8)((v45 | 0x20) - 97) > 0x19u )
              {
                if ( (char)v45 > 57 )
                {
                  if ( (_BYTE)v45 != 95 && (_BYTE)v45 != 126 )
                    return 1LL;
                }
                else if ( (char)v45 <= 36 || !_bittest64(&v47, v45) )
                {
                  return 1LL;
                }
              }
              ++a4[5];
              v48 = v46;
              if ( (unsigned __int64)v46 >= v26 )
                return 1LL;
              v45 = *v46++;
            }
            while ( (_BYTE)v45 != 93 );
            v49 = v48 + 1;
            if ( (unsigned __int64)(v48 + 1) >= v26 )
              goto LABEL_157;
            v50 = v48[1];
            goto LABEL_200;
          }
          ++v43;
          if ( v44 == 7 )
          {
            for ( i = v40; ; i = v40 )
            {
LABEL_208:
              ++v40;
              a4[5] = v43;
              if ( (unsigned __int64)v40 >= v26 )
                return 1LL;
              v41 = i[1];
              if ( v41 == 93 )
                break;
              if ( (unsigned __int8)(v41 - 48) > 9u )
              {
                v42 = 1;
                v44 = 7;
                goto LABEL_185;
              }
              ++v43;
            }
            v49 = i + 2;
            if ( (unsigned __int64)(i + 2) >= v26 )
            {
LABEL_157:
              v17 = *a4;
              goto LABEL_25;
            }
            v50 = i[2];
LABEL_200:
            if ( v50 == 58 )
            {
              v31 = v49 + 1;
              if ( (unsigned __int64)(v49 + 1) < v26 )
              {
                v32 = v49[1];
LABEL_108:
                v33 = 11;
                while ( (unsigned __int8)(v32 - 48) <= 9u )
                {
                  if ( v33 == 12 )
                  {
                    ++v31;
                    ++a4[7];
                    if ( (unsigned __int64)v31 >= v26 )
                      goto LABEL_157;
                  }
                  else
                  {
                    v34 = (__int16)v31++;
                    *a4 |= 4u;
                    a4[6] = v34 - (_WORD)a1;
                    a4[7] = 1;
                    if ( (unsigned __int64)v31 >= v26 )
                      goto LABEL_157;
                  }
                  v32 = *v31;
                  v33 = 12;
                }
              }
            }
            return 1LL;
          }
        }
        i = v40;
        a4[4] = (_WORD)v40 - (_WORD)a1;
        goto LABEL_208;
      }
      ++a4[5];
      if ( v4 <= (unsigned __int64)v8 )
      {
        v17 = *a4;
        v9 = 1;
        goto LABEL_23;
      }
      v13 = *v8;
      if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
        return 1LL;
      v9 = 1;
LABEL_34:
      if ( (_BYTE)v13 == 64 )
        return 1LL;
      goto LABEL_35;
    }
    if ( (unsigned __int8)((v13 | 0x20) - 97) > 0x19u && (unsigned __int8)(v13 - 48) > 9u )
    {
      if ( (char)v13 > 61 )
      {
        v22 = (unsigned int)(v13 - 91);
        if ( (unsigned __int8)v22 > 0x23u || !_bittest64(&v12, v22) )
          return 1LL;
      }
      else
      {
        if ( (char)v13 <= 32 )
          return 1LL;
        v19 = 0x2C007FF200000000LL;
        if ( !_bittest64(&v19, v13) )
          return 1LL;
      }
    }
    if ( v10 != 1 )
    {
      v16 = 2;
      v7 = 25;
      v10 = 1;
LABEL_22:
      v17 = *a4 | v16;
      a4[2 * v10 + 2] = (_WORD)v15 - (_WORD)a1;
      a4[2 * v10 + 3] = 1;
      v8 = v15 + 1;
      *a4 = v17;
      if ( (unsigned __int64)(v15 + 1) >= v4 )
        goto LABEL_23;
      goto LABEL_3;
    }
    ++a4[5];
    if ( v4 <= (unsigned __int64)v8 )
      goto LABEL_128;
    v13 = *v8;
    if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
      return 1LL;
    ++v8;
    v10 = 1;
  }
  if ( v4 <= (unsigned __int64)v8 )
    goto LABEL_128;
  v13 = *v8;
  if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
    return 1LL;
LABEL_16:
  ++v8;
  while ( 2 )
  {
    v15 = v8 - 1;
    if ( ((1 << (v13 & 7)) & byte_7340[(unsigned __int8)v13 >> 3]) != 0 )
    {
LABEL_20:
      if ( v10 != 4 )
      {
        v16 = 16;
        v7 = 29;
        v10 = 4;
        goto LABEL_22;
      }
      ++a4[11];
      if ( v4 <= (unsigned __int64)v8 )
        goto LABEL_128;
      v13 = *v8;
      if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
        return 1LL;
      ++v8;
      v10 = 4;
      continue;
    }
    break;
  }
  if ( (_BYTE)v13 != 35 )
  {
    if ( (_BYTE)v13 != 63 )
      return 1LL;
    goto LABEL_20;
  }
  if ( v4 <= (unsigned __int64)v8 )
    goto LABEL_128;
  v13 = *v8;
  if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
    return 1LL;
  while ( 1 )
  {
LABEL_46:
    if ( ((1 << (v13 & 7)) & byte_7340[(unsigned __int8)v13 >> 3]) != 0 )
      goto LABEL_49;
    if ( (_BYTE)v13 != 35 )
      break;
    if ( (unsigned __int64)++v8 >= v4 )
      goto LABEL_128;
    v13 = *v8;
    if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
      return 1LL;
  }
  if ( (_BYTE)v13 != 63 )
    return 1LL;
LABEL_49:
  if ( v10 == 5 )
  {
    ++a4[13];
    if ( v4 > (unsigned __int64)(v8 + 1) )
    {
      v13 = v8[1];
      if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
        return 1LL;
      ++v8;
LABEL_74:
      for ( j = v8 + 1; ; ++j )
      {
        v15 = j - 1;
        if ( ((1 << (v13 & 7)) & byte_7340[(unsigned __int8)v13 >> 3]) == 0 && (_BYTE)v13 != 35 && (_BYTE)v13 != 63 )
          return 1LL;
        if ( v10 != 5 )
          break;
        ++a4[13];
        if ( v4 <= (unsigned __int64)j )
          goto LABEL_128;
        v13 = *j;
        if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
          return 1LL;
        v10 = 5;
      }
      v16 = 32;
      v7 = 31;
      v10 = 5;
      goto LABEL_22;
    }
    goto LABEL_128;
  }
  a4[13] = 1;
  a4[12] = (_WORD)v8 - (_WORD)a1;
  v17 = *a4 | 0x20;
  *a4 = v17;
  if ( v4 > (unsigned __int64)(v8 + 1) )
  {
    v13 = v8[1];
    if ( (unsigned __int8)v13 <= 0x20u && _bittest64(&v11, v13) )
      return 1LL;
    ++v8;
    v10 = 5;
    goto LABEL_74;
  }
LABEL_23:
  if ( (v17 & 3) == 1 )
    return 1LL;
  if ( (v17 & 2) != 0 )
    goto LABEL_93;
LABEL_25:
  if ( a3 )
  {
    if ( v17 != 6 )
      return 1LL;
LABEL_27:
    v18 = strtoul((const char *)&a1[(unsigned __int16)a4[6]], 0LL, 10);
    if ( v18 > 0xFFFF )
      return 1LL;
    a4[1] = v18;
    return 0LL;
  }
  else
  {
    if ( (v17 & 4) != 0 )
      goto LABEL_27;
    return 0LL;
  }
}
