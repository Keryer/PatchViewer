__int64 __fastcall sub_2C80(__int64 a1, char *a2)
{
  void *v3; // r13
  size_t v4; // r12
  __int64 result; // rax
  void *v6; // rdi
  __int64 v7; // [rsp+0h] [rbp-30h]

  if ( !a1 )
    return 0LL;
  if ( (*(_DWORD *)(a1 + 24) & 0x110) != 0x10 )
    return 0LL;
  v3 = *(void **)(a1 + 32);
  if ( !a2 || !v3 )
    return 0LL;
  v4 = strlen(a2);
  if ( v4 <= strlen((const char *)v3) )
  {
    memcpy(v3, a2, v4 + 1);
    return *(_QWORD *)(a1 + 32);
  }
  result = sub_1AC0(a2);
  if ( !result )
    return 0LL;
  v6 = *(void **)(a1 + 32);
  if ( v6 )
  {
    v7 = result;
    off_8018(v6);
    result = v7;
  }
  *(_QWORD *)(a1 + 32) = result;
  return result;
}
