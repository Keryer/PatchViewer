__int64 __fastcall sub_8EF0(_BYTE *a1, __m128i *a2, int a3, int a4)
{
  unsigned __int8 *v4; // rbx
  unsigned __int16 *v6; // r12
  __m128i *v7; // r13
  unsigned __int64 v8; // rsi
  _QWORD *v9; // r9
  unsigned int v10; // eax
  unsigned int v11; // edi
  size_t v12; // rdx
  __m128i *v13; // r8
  unsigned __int64 v14; // r15
  __m128i *v15; // r11
  unsigned __int8 *v16; // r14
  unsigned __int16 *v17; // r9
  unsigned __int64 v18; // rdi
  unsigned __int64 v19; // rcx
  char v20; // al
  const __m128i *v21; // rsi
  __int64 v22; // rax
  __int64 result; // rax
  __m128i v24; // xmm7
  unsigned __int16 *v25; // rdx
  __int64 v26; // rax
  __int64 *v27; // rax
  unsigned __int64 v28; // rdi
  __int64 *v29; // rax
  __int64 v30; // rdx
  __int64 v31; // rax
  __m128i v32; // xmm0
  __int64 v33; // rdi
  const __m128i *v34; // rdx
  __int64 v35; // rdi
  char *v36; // rcx
  __m128i v37; // xmm6
  __m128i v38; // xmm4
  __int64 v39; // r8
  __int64 v40; // rcx
  __int64 *v41; // rax
  unsigned __int64 v42; // rdi
  __int64 *v43; // rax
  __int64 v44; // rdx
  unsigned __int16 *v45; // rbx
  unsigned __int64 v46; // r14
  __int64 v47; // rdx
  __int64 v48; // rax
  __int64 v49; // r8
  _DWORD *v50; // rax
  _DWORD *v51; // rax
  __int64 v52; // rdx
  __int64 v53; // rsi
  __int64 v54; // [rsp+10h] [rbp-48h]

  if ( !a1 || a4 < 0 )
    return 0xFFFFFFFFLL;
  v4 = a1;
  v6 = (unsigned __int16 *)&a1[a3];
  v7 = (__m128i *)((char *)a2 + a4);
  if ( !a4 )
  {
    if ( a3 == 1 )
      return (unsigned int)-(*a1 != 0);
    result = 4294967294LL;
    if ( a3 <= 1 )
      return 0xFFFFFFFFLL;
    return result;
  }
  if ( a3 <= 0 )
    return 0xFFFFFFFFLL;
  v8 = (unsigned __int64)(a1 + 1);
  v9 = a1 + 1;
  v10 = (unsigned __int8)*a1;
  v11 = v10 >> 4;
  v12 = v10 >> 4;
  if ( a4 <= 63 )
  {
    v13 = a2;
    goto LABEL_16;
  }
  v13 = a2;
  if ( v8 > (unsigned __int64)v6 - 17 )
    goto LABEL_16;
  v14 = (unsigned __int64)v6 - 15;
  v15 = v7 - 4;
  v16 = (unsigned __int8 *)(v6 - 3);
  if ( v11 == 15 )
    goto LABEL_42;
LABEL_8:
  v17 = (unsigned __int16 *)(v8 + v12);
  v18 = (unsigned __int64)v13->m128i_u64 + v12;
  *v13 = _mm_loadu_si128((const __m128i *)(v4 + 1));
  while ( 1 )
  {
    v19 = *v17;
    v20 = v10 & 0xF;
    v4 = (unsigned __int8 *)(v17 + 1);
    v21 = (const __m128i *)(v18 - v19);
    if ( v20 == 15 )
    {
      if ( v4 >= v16 )
        return 0xFFFFFFFFLL;
      v31 = *((unsigned __int8 *)v17 + 2);
      v4 = (unsigned __int8 *)v17 + 3;
      if ( v31 == 255 )
      {
        do
        {
          if ( v16 == v4 )
            return 0xFFFFFFFFLL;
          v39 = *v4++;
          v31 += v39;
        }
        while ( v39 == 255 );
        if ( v31 == -1 )
          return 0xFFFFFFFFLL;
      }
      if ( v18 > v18 + v31 + 15 )
        return 0xFFFFFFFFLL;
      v22 = v31 + 19;
      v13 = (__m128i *)(v18 + v22);
      if ( v18 + v22 >= (unsigned __int64)v15 )
        goto LABEL_23;
    }
    else
    {
      v22 = (unsigned __int8)(v20 + 4);
      v13 = (__m128i *)(v18 + v22);
      if ( v18 + v22 >= (unsigned __int64)v15 )
        goto LABEL_23;
      if ( v19 > 7 )
      {
        if ( a2 > v21 )
          return 4294967293LL;
        *(_QWORD *)v18 = v21->m128i_i64[0];
        *(_QWORD *)(v18 + 8) = v21->m128i_i64[1];
        *(_WORD *)(v18 + 16) = v21[1].m128i_i16[0];
        goto LABEL_40;
      }
    }
    if ( a2 > v21 )
      return 4294967293LL;
    if ( v19 > 0xF )
    {
      if ( v19 <= 0x3F )
      {
        do
        {
          v38 = _mm_loadu_si128(v21);
          v18 += 32LL;
          v21 += 2;
          *(__m128i *)(v18 - 32) = v38;
          *(__m128i *)(v18 - 16) = _mm_loadu_si128(v21 - 1);
        }
        while ( v18 < (unsigned __int64)v13 );
      }
      else
      {
        do
        {
          v32 = _mm_loadu_si128(v21);
          v18 += 64LL;
          v21 += 4;
          *(__m128i *)(v18 - 64) = v32;
          *(__m128i *)(v18 - 48) = _mm_loadu_si128(v21 - 3);
          *(__m128i *)(v18 - 32) = _mm_loadu_si128(v21 - 2);
          *(__m128i *)(v18 - 16) = _mm_loadu_si128(v21 - 1);
        }
        while ( v18 < (unsigned __int64)v13 );
      }
      goto LABEL_40;
    }
    switch ( (_WORD)v19 )
    {
      case 2:
        LOWORD(v54) = v21->m128i_i16[0];
        WORD1(v54) = v21->m128i_i16[0];
        HIDWORD(v54) = v54;
        goto LABEL_98;
      case 4:
        LODWORD(v54) = v21->m128i_i32[0];
        HIDWORD(v54) = v21->m128i_i32[0];
        goto LABEL_98;
      case 1:
        v54 = 0x101010101010101LL * v21->m128i_u8[0];
        do
        {
LABEL_98:
          v18 += 8LL;
          *(_QWORD *)(v18 - 8) = v54;
        }
        while ( v18 < (unsigned __int64)v13 );
        goto LABEL_40;
    }
    if ( v19 <= 7 )
    {
      *(_DWORD *)v18 = 0;
      *(_BYTE *)v18 = v21->m128i_i8[0];
      *(_BYTE *)(v18 + 1) = v21->m128i_i8[1];
      *(_BYTE *)(v18 + 2) = v21->m128i_i8[2];
      *(_BYTE *)(v18 + 3) = v21->m128i_i8[3];
      v50 = (__int32 *)((char *)v21->m128i_i32 + dword_E040[v19]);
      *(_DWORD *)(v18 + 4) = *v50;
      v41 = (__int64 *)((char *)v50 - dword_E020[v19]);
    }
    else
    {
      *(_QWORD *)v18 = v21->m128i_i64[0];
      v41 = &v21->m128i_i64[1];
    }
    v42 = v18 + 16;
    *(_QWORD *)(v42 - 8) = *v41;
    if ( v42 < (unsigned __int64)v13 )
    {
      v43 = v41 + 1;
      do
      {
        v44 = *v43;
        v42 += 8LL;
        ++v43;
        *(_QWORD *)(v42 - 8) = v44;
      }
      while ( v42 < (unsigned __int64)v13 );
    }
LABEL_40:
    v8 = (unsigned __int64)(v4 + 1);
    v9 = v4 + 1;
    v10 = *v4;
    v11 = v10 >> 4;
    v12 = v10 >> 4;
    if ( v4 + 1 > (unsigned __int8 *)v6 - 17 )
      goto LABEL_16;
    if ( v11 != 15 )
      goto LABEL_8;
LABEL_42:
    if ( v14 <= v8 )
      return 0xFFFFFFFFLL;
    v33 = v4[1];
    v34 = (const __m128i *)(v4 + 2);
    if ( v33 == 255 )
    {
      do
      {
        if ( v14 <= (unsigned __int64)v34 )
          return 0xFFFFFFFFLL;
        v40 = v34->m128i_u8[0];
        v34 = (const __m128i *)((char *)v34 + 1);
        v33 += v40;
      }
      while ( v40 == 255 );
      if ( v33 == -1 )
        return 0xFFFFFFFFLL;
    }
    v35 = v33 + 15;
    v36 = &v13->m128i_i8[v35];
    if ( __CFADD__(v35, v13) )
      return 0xFFFFFFFFLL;
    v17 = (unsigned __int16 *)((char *)v34->m128i_u16 + v35);
    if ( __CFADD__(v34, v35) )
      return 0xFFFFFFFFLL;
    v18 = (unsigned __int64)v13->m128i_u64 + v35;
    if ( v36 > (char *)v15 || v17 > v6 - 32 )
      break;
    do
    {
      v37 = _mm_loadu_si128(v34);
      v13 += 4;
      v34 += 4;
      v13[-4] = v37;
      v13[-3] = _mm_loadu_si128(v34 - 3);
      v13[-2] = _mm_loadu_si128(v34 - 2);
      v13[-1] = _mm_loadu_si128(v34 - 1);
    }
    while ( v36 > (char *)v13 );
  }
  v9 = (_QWORD *)v8;
  v10 = *v4;
  v11 = v10 >> 4;
  v12 = v10 >> 4;
  while ( 1 )
  {
LABEL_16:
    if ( v11 == 15 )
    {
LABEL_105:
      if ( (char *)v6 - 15 <= (char *)v9 )
        return 0xFFFFFFFFLL;
      v52 = v4[1];
      v9 = v4 + 2;
      if ( v52 == 255 )
      {
        while ( (char *)v6 - 15 > (char *)v9 )
        {
          v53 = *(unsigned __int8 *)v9;
          v9 = (_QWORD *)((char *)v9 + 1);
          v52 += v53;
          if ( v53 != 255 )
          {
            if ( v52 != -1 )
              goto LABEL_107;
            return 0xFFFFFFFFLL;
          }
        }
        return 0xFFFFFFFFLL;
      }
LABEL_107:
      v12 = v52 + 15;
      v46 = (unsigned __int64)v13->m128i_u64 + v12;
      if ( __CFADD__(v12, v13) )
        return 0xFFFFFFFFLL;
      v45 = (unsigned __int16 *)((char *)v9 + v12);
      if ( __CFADD__(v12, v9) )
        return 0xFFFFFFFFLL;
    }
    else
    {
      if ( v6 - 8 > (unsigned __int16 *)v9 )
      {
        while ( &v7[-2] >= v13 )
        {
          v24 = _mm_loadu_si128((const __m128i *)(v4 + 1));
          v18 = (unsigned __int64)v13->m128i_u64 + v12;
          v25 = (unsigned __int16 *)((char *)v9 + v12);
          v26 = v10 & 0xF;
          v4 = (unsigned __int8 *)(v25 + 1);
          *v13 = v24;
          v19 = *v25;
          v21 = (const __m128i *)(v18 - v19);
          if ( v26 == 15 )
            goto LABEL_82;
          if ( v19 <= 7 )
            goto LABEL_81;
          if ( a2 > v21 )
            goto LABEL_22;
          v9 = (_QWORD *)((char *)v25 + 3);
          v13 = (__m128i *)(v18 + v26 + 4);
          *(_QWORD *)v18 = v21->m128i_i64[0];
          *(_QWORD *)(v18 + 8) = v21->m128i_i64[1];
          *(_WORD *)(v18 + 16) = v21[1].m128i_i16[0];
          v10 = *((unsigned __int8 *)v25 + 2);
          v12 = v10 >> 4;
          if ( (_DWORD)v12 == 15 )
            goto LABEL_105;
          if ( v6 - 8 <= (unsigned __int16 *)v9 )
            break;
        }
      }
      v45 = (unsigned __int16 *)((char *)v9 + v12);
      v46 = (unsigned __int64)v13->m128i_u64 + v12;
    }
    v18 = v46;
    if ( v46 > (unsigned __int64)v7[-1].m128i_u64 + 4 || v45 > v6 - 4 )
      break;
    do
    {
      v47 = *v9;
      v13 = (__m128i *)((char *)v13 + 8);
      ++v9;
      v13[-1].m128i_i64[1] = v47;
    }
    while ( v46 > (unsigned __int64)v13 );
    v19 = *v45;
    v4 = (unsigned __int8 *)(v45 + 1);
    v26 = v10 & 0xF;
    v21 = (const __m128i *)(v46 - v19);
LABEL_81:
    if ( v26 == 15 )
    {
LABEL_82:
      if ( v6 - 3 <= (unsigned __int16 *)v4 )
        return 0xFFFFFFFFLL;
      v48 = *v4++;
      if ( v48 == 255 )
      {
        while ( v6 - 3 != (unsigned __int16 *)v4 )
        {
          v49 = *v4++;
          v48 += v49;
          if ( v49 != 255 )
          {
            if ( v48 != -1 )
              goto LABEL_84;
            return 0xFFFFFFFFLL;
          }
        }
        return 0xFFFFFFFFLL;
      }
LABEL_84:
      v26 = v48 + 15;
      if ( __CFADD__(v26, v18) )
        return 0xFFFFFFFFLL;
    }
LABEL_22:
    v22 = v26 + 4;
LABEL_23:
    if ( a2 > v21 )
      return 4294967293LL;
    v13 = (__m128i *)(v18 + v22);
    if ( v18 + v22 > (unsigned __int64)&v7[-1].m128i_u64[1] + 3 )
      return 4294967294LL;
    if ( v13 > (__m128i *)((char *)v7[-1].m128i_i64 + 4) )
    {
      v13 = (__m128i *)sub_13C0(v18, v21, v22);
      if ( v7 == v13 )
        return (unsigned int)((_DWORD)v13 - (_DWORD)a2);
      v9 = v4 + 1;
      v10 = *v4;
      v11 = v10 >> 4;
      v12 = v10 >> 4;
    }
    else
    {
      if ( v19 <= 7 )
      {
        *(_DWORD *)v18 = 0;
        *(_BYTE *)v18 = v21->m128i_i8[0];
        *(_BYTE *)(v18 + 1) = v21->m128i_i8[1];
        *(_BYTE *)(v18 + 2) = v21->m128i_i8[2];
        *(_BYTE *)(v18 + 3) = v21->m128i_i8[3];
        v51 = (__int32 *)((char *)v21->m128i_i32 + dword_E040[v19]);
        *(_DWORD *)(v18 + 4) = *v51;
        v27 = (__int64 *)((char *)v51 - dword_E020[v19]);
      }
      else
      {
        *(_QWORD *)v18 = v21->m128i_i64[0];
        v27 = &v21->m128i_i64[1];
      }
      v28 = v18 + 16;
      v9 = v4 + 1;
      *(_QWORD *)(v28 - 8) = *v27;
      if ( (unsigned __int64)v13 > v28 )
      {
        v29 = v27 + 1;
        do
        {
          v30 = *v29;
          v28 += 8LL;
          ++v29;
          *(_QWORD *)(v28 - 8) = v30;
        }
        while ( (unsigned __int64)v13 > v28 );
      }
      v10 = *v4;
      v11 = v10 >> 4;
      v12 = v10 >> 4;
    }
  }
  if ( v6 != v45 )
  {
    if ( v6 < v45 )
      return 0xFFFFFFFFLL;
LABEL_75:
    if ( v46 <= (unsigned __int64)v7[-1].m128i_u64 + 4 )
      return 0xFFFFFFFFLL;
    return 4294967294LL;
  }
  if ( (unsigned __int64)v7 < v46 )
    goto LABEL_75;
  memmove(v13, v9, v12);
  LODWORD(v13) = v46;
  return (unsigned int)((_DWORD)v13 - (_DWORD)a2);
}
