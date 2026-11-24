__int64 __fastcall sub_8F00(_BYTE *a1, __m128i *a2, int a3, int a4)
{
  int v4; // ebp
  unsigned __int16 *v6; // r13
  __m128i *v7; // r14
  char *v8; // rsi
  unsigned int v9; // r10d
  unsigned int v10; // eax
  size_t v11; // rdx
  unsigned __int8 *v12; // rbx
  __m128i *v13; // r11
  __m128i *v14; // r9
  unsigned __int8 *v15; // r15
  unsigned __int16 *v16; // rsi
  unsigned __int64 v17; // rdi
  unsigned __int64 v18; // rax
  char v19; // r10
  const __m128i *v20; // r8
  __int64 v21; // r10
  __int64 result; // rax
  __int64 v23; // r10
  __m128i v24; // xmm0
  __m128i v25; // xmm7
  char *v26; // rdx
  __int64 v27; // r10
  __int64 *v28; // rax
  unsigned __int64 v29; // rdi
  __int64 *v30; // rax
  __int64 v31; // rdx
  __m128i v32; // xmm4
  __int64 v33; // rsi
  __int64 v34; // rdx
  const __m128i *v35; // rax
  __int64 v36; // rdx
  char *v37; // r8
  __m128i v38; // xmm6
  __int64 *v39; // rax
  unsigned __int64 v40; // rdi
  __int64 *v41; // rax
  __int64 v42; // rdx
  unsigned __int16 *v43; // rbx
  unsigned __int64 v44; // r15
  __int64 v45; // rax
  __int64 v46; // r10
  __int64 v47; // rcx
  __int64 v48; // rsi
  __int64 v49; // rdx
  _DWORD *v50; // rdx
  _DWORD *v51; // rdx
  __int64 v52; // rcx
  unsigned __int64 v53; // [rsp+0h] [rbp-58h]
  __int64 v54; // [rsp+10h] [rbp-48h]

  if ( !a1 || a4 < 0 )
    return 0xFFFFFFFFLL;
  v4 = (int)a1;
  v6 = (unsigned __int16 *)&a1[a3];
  v7 = (__m128i *)((char *)a2 + a4);
  if ( !a4 )
  {
    result = 0xFFFFFFFFLL;
    if ( a3 == 1 )
      return (unsigned int)-(*a1 != 0);
    return result;
  }
  if ( a3 <= 0 )
    return 0xFFFFFFFFLL;
  v8 = a1 + 1;
  v9 = (unsigned __int8)*a1;
  v10 = v9 >> 4;
  v11 = v9 >> 4;
  if ( a4 > 63 && v8 <= (char *)v6 - 17 )
  {
    v12 = a1;
    v13 = v7 - 4;
    v14 = a2;
    v53 = (unsigned __int64)v6 - 15;
    v15 = (unsigned __int8 *)(v6 - 3);
    while ( 1 )
    {
      if ( v10 == 15 )
      {
        if ( v53 <= (unsigned __int64)v8 )
          goto LABEL_96;
        v34 = v12[1];
        v35 = (const __m128i *)(v12 + 2);
        if ( v34 == 255 )
        {
          while ( v53 > (unsigned __int64)v35 )
          {
            v48 = v35->m128i_u8[0];
            v35 = (const __m128i *)((char *)v35 + 1);
            v34 += v48;
            if ( v48 != 255 )
            {
              if ( v34 != -1 )
                goto LABEL_49;
              break;
            }
          }
LABEL_91:
          LODWORD(v12) = (_DWORD)v35;
          return (unsigned int)~((_DWORD)v12 - v4);
        }
LABEL_49:
        v36 = v34 + 15;
        v37 = &v14->m128i_i8[v36];
        if ( __CFADD__(v36, v14) )
          goto LABEL_91;
        v16 = (unsigned __int16 *)((char *)v35->m128i_u16 + v36);
        if ( __CFADD__(v35, v36) )
          goto LABEL_91;
        v17 = (unsigned __int64)v14->m128i_u64 + v36;
        if ( v37 > (char *)v13 || v16 > v6 - 32 )
          goto LABEL_109;
        do
        {
          v38 = _mm_loadu_si128(v35);
          v14 += 4;
          v35 += 4;
          v14[-4] = v38;
          v14[-3] = _mm_loadu_si128(v35 - 3);
          v14[-2] = _mm_loadu_si128(v35 - 2);
          v14[-1] = _mm_loadu_si128(v35 - 1);
        }
        while ( v37 > (char *)v14 );
      }
      else
      {
        v16 = (unsigned __int16 *)&v8[v11];
        v17 = (unsigned __int64)v14->m128i_u64 + v11;
        *v14 = _mm_loadu_si128((const __m128i *)(v12 + 1));
      }
      v18 = *v16;
      v19 = v9 & 0xF;
      v12 = (unsigned __int8 *)(v16 + 1);
      v20 = (const __m128i *)(v17 - v18);
      if ( v19 == 15 )
      {
        if ( v12 >= v15 )
          return (unsigned int)~((_DWORD)v12 - v4);
        v23 = *((unsigned __int8 *)v16 + 2);
        v12 = (unsigned __int8 *)v16 + 3;
        if ( v23 == 255 )
        {
          while ( v15 != v12 )
          {
            v33 = *v12++;
            v23 += v33;
            if ( v33 != 255 )
            {
              if ( v23 != -1 )
                goto LABEL_18;
              return (unsigned int)~((_DWORD)v12 - v4);
            }
          }
          return (unsigned int)~((_DWORD)v12 - v4);
        }
LABEL_18:
        if ( v17 > v17 + v23 + 15 )
          return (unsigned int)~((_DWORD)v12 - v4);
        v21 = v23 + 19;
        v14 = (__m128i *)(v17 + v21);
        if ( v17 + v21 >= (unsigned __int64)v13 )
          goto LABEL_32;
      }
      else
      {
        v21 = (unsigned __int8)(v19 + 4);
        v14 = (__m128i *)(v17 + v21);
        if ( v17 + v21 >= (unsigned __int64)v13 )
          goto LABEL_32;
        if ( v18 > 7 )
        {
          if ( a2 > v20 )
            return (unsigned int)~((_DWORD)v12 - v4);
          *(_QWORD *)v17 = v20->m128i_i64[0];
          *(_QWORD *)(v17 + 8) = v20->m128i_i64[1];
          *(_WORD *)(v17 + 16) = v20[1].m128i_i16[0];
          goto LABEL_24;
        }
      }
      if ( a2 > v20 )
        return (unsigned int)~((_DWORD)v12 - v4);
      if ( v18 <= 0xF )
      {
        switch ( (_WORD)v18 )
        {
          case 2:
            LOWORD(v54) = v20->m128i_i16[0];
            WORD1(v54) = v20->m128i_i16[0];
            HIDWORD(v54) = v54;
            break;
          case 4:
            LODWORD(v54) = v20->m128i_i32[0];
            HIDWORD(v54) = v20->m128i_i32[0];
            break;
          case 1:
            v54 = 0x101010101010101LL * v20->m128i_u8[0];
            break;
          default:
            if ( v18 <= 7 )
            {
              *(_DWORD *)v17 = 0;
              *(_BYTE *)v17 = v20->m128i_i8[0];
              *(_BYTE *)(v17 + 1) = v20->m128i_i8[1];
              *(_BYTE *)(v17 + 2) = v20->m128i_i8[2];
              *(_BYTE *)(v17 + 3) = v20->m128i_i8[3];
              v51 = (__int32 *)((char *)v20->m128i_i32 + dword_E040[v18]);
              *(_DWORD *)(v17 + 4) = *v51;
              v39 = (__int64 *)((char *)v51 - dword_E020[v18]);
            }
            else
            {
              *(_QWORD *)v17 = v20->m128i_i64[0];
              v39 = &v20->m128i_i64[1];
            }
            v40 = v17 + 16;
            *(_QWORD *)(v40 - 8) = *v39;
            if ( v40 < (unsigned __int64)v14 )
            {
              v41 = v39 + 1;
              do
              {
                v42 = *v41;
                v40 += 8LL;
                ++v41;
                *(_QWORD *)(v40 - 8) = v42;
              }
              while ( v40 < (unsigned __int64)v14 );
            }
            goto LABEL_24;
        }
        do
        {
          v17 += 8LL;
          *(_QWORD *)(v17 - 8) = v54;
        }
        while ( v17 < (unsigned __int64)v14 );
      }
      else if ( v18 <= 0x3F )
      {
        do
        {
          v32 = _mm_loadu_si128(v20);
          v17 += 32LL;
          v20 += 2;
          *(__m128i *)(v17 - 32) = v32;
          *(__m128i *)(v17 - 16) = _mm_loadu_si128(v20 - 1);
        }
        while ( v17 < (unsigned __int64)v14 );
      }
      else
      {
        do
        {
          v24 = _mm_loadu_si128(v20);
          v17 += 64LL;
          v20 += 4;
          *(__m128i *)(v17 - 64) = v24;
          *(__m128i *)(v17 - 48) = _mm_loadu_si128(v20 - 3);
          *(__m128i *)(v17 - 32) = _mm_loadu_si128(v20 - 2);
          *(__m128i *)(v17 - 16) = _mm_loadu_si128(v20 - 1);
        }
        while ( v17 < (unsigned __int64)v14 );
      }
LABEL_24:
      v8 = (char *)(v12 + 1);
      v9 = *v12;
      v10 = v9 >> 4;
      v11 = v9 >> 4;
      if ( v12 + 1 > (unsigned __int8 *)v6 - 17 )
        goto LABEL_25;
    }
  }
  v12 = a1;
  v14 = a2;
  while ( 1 )
  {
LABEL_25:
    if ( v10 == 15 )
    {
LABEL_92:
      if ( (char *)v6 - 15 <= v8 )
        goto LABEL_96;
      v49 = v12[1];
      v8 = (char *)(v12 + 2);
      if ( v49 == 255 )
      {
        v12 += 2;
        while ( (char *)v6 - 15 > (char *)v12 )
        {
          v52 = *v12++;
          v49 += v52;
          if ( v52 != 255 )
          {
            if ( v49 == -1 )
              return (unsigned int)~((_DWORD)v12 - v4);
            v8 = (char *)v12;
            goto LABEL_94;
          }
        }
        return (unsigned int)~((_DWORD)v12 - v4);
      }
LABEL_94:
      v11 = v49 + 15;
      v44 = (unsigned __int64)v14->m128i_u64 + v11;
      if ( __CFADD__(v11, v14) )
        goto LABEL_96;
      v43 = (unsigned __int16 *)&v8[v11];
      if ( __CFADD__(v11, v8) )
        goto LABEL_96;
    }
    else
    {
      if ( v6 - 8 > (unsigned __int16 *)v8 )
      {
        while ( &v7[-2] >= v14 )
        {
          v25 = _mm_loadu_si128((const __m128i *)(v12 + 1));
          v17 = (unsigned __int64)v14->m128i_u64 + v11;
          v26 = &v8[v11];
          v27 = v9 & 0xF;
          v12 = (unsigned __int8 *)(v26 + 2);
          *v14 = v25;
          v18 = *(unsigned __int16 *)v26;
          v20 = (const __m128i *)(v17 - v18);
          if ( v27 == 15 )
            goto LABEL_80;
          if ( v18 <= 7 )
            goto LABEL_79;
          if ( a2 > v20 )
            goto LABEL_31;
          v8 = v26 + 3;
          v14 = (__m128i *)(v17 + v27 + 4);
          *(_QWORD *)v17 = v20->m128i_i64[0];
          *(_QWORD *)(v17 + 8) = v20->m128i_i64[1];
          *(_WORD *)(v17 + 16) = v20[1].m128i_i16[0];
          v9 = (unsigned __int8)v26[2];
          v11 = v9 >> 4;
          if ( (_DWORD)v11 == 15 )
            goto LABEL_92;
          if ( v6 - 8 <= (unsigned __int16 *)v8 )
            break;
        }
      }
      v43 = (unsigned __int16 *)&v8[v11];
      v44 = (unsigned __int64)v14->m128i_u64 + v11;
    }
    v17 = v44;
    if ( v44 > (unsigned __int64)v7[-1].m128i_u64 + 4 || v43 > v6 - 4 )
      break;
    do
    {
      v45 = *(_QWORD *)v8;
      v14 = (__m128i *)((char *)v14 + 8);
      v8 += 8;
      v14[-1].m128i_i64[1] = v45;
    }
    while ( v44 > (unsigned __int64)v14 );
    v18 = *v43;
    v27 = v9 & 0xF;
    v12 = (unsigned __int8 *)(v43 + 1);
    v20 = (const __m128i *)(v44 - v18);
LABEL_79:
    if ( v27 == 15 )
    {
LABEL_80:
      if ( v6 - 3 <= (unsigned __int16 *)v12 )
        return (unsigned int)~((_DWORD)v12 - v4);
      v46 = *v12++;
      if ( v46 == 255 )
      {
        while ( v6 - 3 != (unsigned __int16 *)v12 )
        {
          v47 = *v12++;
          v46 += v47;
          if ( v47 != 255 )
          {
            if ( v46 == -1 )
              return (unsigned int)~((_DWORD)v12 - v4);
            goto LABEL_82;
          }
        }
        return (unsigned int)~((_DWORD)v12 - v4);
      }
LABEL_82:
      v27 = v46 + 15;
      if ( __CFADD__(v27, v17) )
        return (unsigned int)~((_DWORD)v12 - v4);
    }
LABEL_31:
    v21 = v27 + 4;
LABEL_32:
    if ( a2 > v20 )
      return (unsigned int)~((_DWORD)v12 - v4);
    v14 = (__m128i *)(v17 + v21);
    if ( v17 + v21 > (unsigned __int64)&v7[-1].m128i_u64[1] + 3 )
      return (unsigned int)~((_DWORD)v12 - v4);
    if ( v14 > (__m128i *)((char *)v7[-1].m128i_i64 + 4) )
    {
      v14 = (__m128i *)sub_13C0(v17, v20, v21);
      if ( v7 == v14 )
        return (unsigned int)((_DWORD)v14 - (_DWORD)a2);
LABEL_109:
      v8 = (char *)(v12 + 1);
      v9 = *v12;
      v10 = v9 >> 4;
      v11 = v9 >> 4;
    }
    else
    {
      if ( v18 <= 7 )
      {
        *(_DWORD *)v17 = 0;
        *(_BYTE *)v17 = v20->m128i_i8[0];
        *(_BYTE *)(v17 + 1) = v20->m128i_i8[1];
        *(_BYTE *)(v17 + 2) = v20->m128i_i8[2];
        *(_BYTE *)(v17 + 3) = v20->m128i_i8[3];
        v50 = (__int32 *)((char *)v20->m128i_i32 + dword_E040[v18]);
        *(_DWORD *)(v17 + 4) = *v50;
        v28 = (__int64 *)((char *)v50 - dword_E020[v18]);
      }
      else
      {
        *(_QWORD *)v17 = v20->m128i_i64[0];
        v28 = &v20->m128i_i64[1];
      }
      v29 = v17 + 16;
      v8 = (char *)(v12 + 1);
      *(_QWORD *)(v29 - 8) = *v28;
      if ( (unsigned __int64)v14 > v29 )
      {
        v30 = v28 + 1;
        do
        {
          v31 = *v30;
          v29 += 8LL;
          ++v30;
          *(_QWORD *)(v29 - 8) = v31;
        }
        while ( (unsigned __int64)v14 > v29 );
      }
      v9 = *v12;
      v10 = v9 >> 4;
      v11 = v9 >> 4;
    }
  }
  if ( (unsigned __int64)v7 < v44 || v6 != v43 )
  {
LABEL_96:
    LODWORD(v12) = (_DWORD)v8;
    return (unsigned int)~((_DWORD)v12 - v4);
  }
  memmove(v14, v8, v11);
  LODWORD(v14) = v44;
  return (unsigned int)((_DWORD)v14 - (_DWORD)a2);
}
