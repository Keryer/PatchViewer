_OWORD *__fastcall sub_4820(__int64 a1, int a2)
{
  _OWORD *v3; // rax
  _OWORD *v4; // r12
  int v5; // eax
  __int64 v6; // xmm0_8
  void *v7; // rdi
  int v8; // eax
  __int64 v9; // rax
  void *v10; // rdi
  _QWORD *v11; // rbx
  __int64 v12; // rax
  _QWORD *v13; // rbp
  __int64 v14; // rdx
  __int64 v16; // rax

  if ( !a1 )
    return 0LL;
  v3 = off_8010(0x40uLL);
  v4 = v3;
  if ( !v3 )
    return 0LL;
  *v3 = 0LL;
  v3[1] = 0LL;
  v3[2] = 0LL;
  v3[3] = 0LL;
  v5 = *(_DWORD *)(a1 + 24);
  v6 = *(_QWORD *)(a1 + 48);
  v7 = *(void **)(a1 + 32);
  BYTE1(v5) &= ~1u;
  *((_DWORD *)v4 + 6) = v5;
  v8 = *(_DWORD *)(a1 + 40);
  *((_QWORD *)v4 + 6) = v6;
  *((_DWORD *)v4 + 10) = v8;
  if ( v7 )
  {
    v9 = sub_1AA0(v7);
    *((_QWORD *)v4 + 4) = v9;
    if ( !v9 )
      goto LABEL_18;
  }
  v10 = *(void **)(a1 + 56);
  if ( !v10 )
    goto LABEL_8;
  if ( (*(_BYTE *)(a1 + 25) & 2) != 0 )
  {
    *((_QWORD *)v4 + 7) = v10;
    goto LABEL_8;
  }
  v16 = sub_1AA0(v10);
  *((_QWORD *)v4 + 7) = v16;
  if ( !v16 )
  {
LABEL_18:
    sub_2600(v4);
    return 0LL;
  }
LABEL_8:
  if ( !a2 )
    return v4;
  v11 = *(_QWORD **)(a1 + 16);
  v12 = 0LL;
  if ( v11 )
  {
    while ( 1 )
    {
      v13 = (_QWORD *)v12;
      v12 = sub_4820(v11, 1LL);
      if ( !v12 )
        goto LABEL_18;
      if ( v13 )
      {
        *v13 = v12;
        v11 = (_QWORD *)*v11;
        *(_QWORD *)(v12 + 8) = v13;
        if ( !v11 )
          break;
      }
      else
      {
        v11 = (_QWORD *)*v11;
        *((_QWORD *)v4 + 2) = v12;
        if ( !v11 )
          break;
      }
    }
  }
  v14 = *((_QWORD *)v4 + 2);
  if ( v14 )
  {
    *(_QWORD *)(v14 + 8) = v12;
    return v4;
  }
  return v4;
}
