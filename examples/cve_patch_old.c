__int64 __fastcall sub_140012A40(__int64 a1, unsigned int *a2, unsigned int a3)
{
  unsigned int v4; // edi
  unsigned int v5; // esi
  unsigned int v6; // eax
  __int64 v7; // rbx
  void *v8; // r14
  int v9; // [rsp+20h] [rbp-38h] BYREF
  char v10[32]; // [rsp+28h] [rbp-30h] BYREF

  v9 = 0;
  if ( !a2 )
    return 3221225485LL;
  if ( a3 < 0x10 )
    return 3221225485LL;
  v4 = *a2;
  v5 = a2[1];
  v6 = a2[2];
  v7 = qword_140089000;
  if ( !qword_140089000 )
    return 3221225473LL;
  switch ( v4 )
  {
    case 1u:
      sub_140004100(a1, 1LL);
      break;
    case 2u:
      sub_140004220(a1, v5);
      break;
    case 5u:
      v9 = sub_140004500(v7, v5);
      break;
    default:
      goto loc_140012B10;
  }
  if ( v6 == 0x100 )
  {
    v8 = (void *)sub_140005100(v5 + 16);
    if ( !v8 )
      goto loc_140012B10;
    sub_140005120(v8, a2 + 4, v5);
    sub_140005300(a1, v8, v5);
  }
  else
  {
    sub_140005480(a1, v6, &v9);
  }
  sub_140005900(v10, 32LL);
  return 0LL;

loc_140012B10:
  sub_140005F00(a1, (unsigned int)dword_140089120);
  return 3221225473LL;
}
