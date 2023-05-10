set ARMINCLUDE=d:/Source/NCUCodeMerge/arm926/host-cross/arm-wrs-linux-gnueabi/sysroot/usr/include/
set NCUINCLUDE=D:/Source/NCUCodeMerge/Track2_NCU_Code/src/include/
set NCUBASE=D:/Source/NCUCodeMerge/Track2_NCU_Code/src

clang -c -std=c90 -Wno-macro-redefined -Wno-return-type -Wno-implicit-function-declaration -nostdinc -isystem stdincludes -I %NCUINCLUDE% -Xclang -ast-dump=json -ferror-limit=9999 %NCUBASE%/%1/%2 > BuildDir/%2.json 2> BuildDir/%2.errors
