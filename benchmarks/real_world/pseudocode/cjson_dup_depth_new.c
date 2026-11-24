_OWORD *__fastcall sub_4820(__int64 a1, unsigned __int64 a2, int a3)
{
  unsigned __int64 v4; // r13
  _OWORD *v6; // rax
  _OWORD *v7; // r12
  int v8; // eax
  __int64 v9; // xmm0_8
  void *v10; // rdi
  int v11; // eax
  __int64 v12; // rax
  void *v13; // rdi
  _QWORD *v14; // rbx
  __int64 v15; // rax
  _QWORD *v16; // rbp
  __int64 v17; // rdx
  __int64 v18; // rax

  if ( !a1 )
    return 0LL;
  v4 = a2;
  v6 = off_8010(0x40uLL);
  v7 = v6;
  if ( !v6 )
    return 0LL;
  *v6 = 0LL;
  v6[1] = 0LL;
  v6[2] = 0LL;
  v6[3] = 0LL;
  v8 = *(_DWORD *)(a1 + 24);
  v9 = *(_QWORD *)(a1 + 48);
  v10 = *(void **)(a1 + 32);
  BYTE1(v8) &= ~1u;
  *((_DWORD *)v7 + 6) = v8;
  v11 = *(_DWORD *)(a1 + 40);
  *((_QWORD *)v7 + 6) = v9;
  *((_DWORD *)v7 + 10) = v11;
  if ( v10 )
  {
    v12 = sub_1AA0(v10);
    *((_QWORD *)v7 + 4) = v12;
    if ( !v12 )
      goto LABEL_20;
  }
  v13 = *(void **)(a1 + 56);
  if ( !v13 )
    goto LABEL_8;
  if ( (*(_BYTE *)(a1 + 25) & 2) != 0 )
  {
    *((_QWORD *)v7 + 7) = v13;
    goto LABEL_8;
  }
  v18 = sub_1AA0(v13);
  *((_QWORD *)v7 + 7) = v18;
  if ( !v18 )
  {
LABEL_20:
    sub_2600(v7);
    return 0LL;
  }
LABEL_8:
  if ( a3 )
  {
    v14 = *(_QWORD **)(a1 + 16);
    if ( v14 )
    {
      if ( a2 <= 0x270F )
      {
        v15 = 0LL;
        while ( 1 )
        {
          ++v4;
          v16 = (_QWORD *)v15;
          v15 = sub_4820(v14, v4, 1LL);
          if ( !v15 )
            break;
          if ( v16 )
          {
            *v16 = v15;
            v14 = (_QWORD *)*v14;
            *(_QWORD *)(v15 + 8) = v16;
            if ( !v14 )
              goto LABEL_17;
          }
          else
          {
            v14 = (_QWORD *)*v14;
            *((_QWORD *)v7 + 2) = v15;
            if ( !v14 )
              goto LABEL_17;
          }
          if ( v4 == 10000 )
            goto LABEL_20;
        }
      }
      goto LABEL_20;
    }
    v15 = 0LL;
LABEL_17:
    v17 = *((_QWORD *)v7 + 2);
    if ( v17 )
      *(_QWORD *)(v17 + 8) = v15;
  }
  return v7;
}
