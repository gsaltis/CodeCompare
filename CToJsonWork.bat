set ARMINCLUDE=c:/Users/greg.saltis/Source/arm926/host-cross/arm-wrs-linux-gnueabi/sysroot/usr/include/
set NCUINCLUDE=c:/Users/greg.saltis/Source/NCUCodeMerge/Track2_NCU_Code-master/src/include/
set NCUBASE=C:/users/greg.saltis/Source/NCUCodeMerge/Track2_NCU_Code-master/src

clang -H -isystem %ARMINCLUDE% -Xclang -ast-dump=json -I%NCUINCLUDE% -ferror-limit=9999 %NCUBASE%/%1/%2 > %2.json 2> %2.errors
