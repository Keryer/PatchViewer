__int64 __fastcall sub_2C80(__int64 a1, char *a2)
{
  char *v3; // r13
  size_t v4; // r12
  size_t v5; // rax
  __int64 result; // rax
  void *v7; // rdi
  __int64 v8; // [rsp+0h] [rbp-30h]

  if ( !a1 )
    return 0LL;
  if ( (*(_DWORD *)(a1 + 24) & 0x110) != 0x10 )
    return 0LL;
  v3 = *(char **)(a1 + 32);
  if ( !a2 || !v3 )
    return 0LL;
  v4 = strlen(a2);
  v5 = strlen(v3);
  if ( v4 <= v5 )
  {
    if ( v3 > &a2[v4] || a2 > &v3[v5] )
    {
      memcpy(v3, a2, v4 + 1);
      return *(_QWORD *)(a1 + 32);
    }
    return 0LL;
  }
  result = sub_1AC0(a2);
  if ( !result )
    return 0LL;
  v7 = *(void **)(a1 + 32);
  if ( v7 )
  {
    v8 = result;
    off_8018(v7);
    result = v8;
  }
  *(_QWORD *)(a1 + 32) = result;
  return result;
}
