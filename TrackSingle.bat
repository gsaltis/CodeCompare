cls
set NCUINCLUDE=D:\Source\NCUCodeMerge\Track2_NCU_Code\src\include\
set NCUBASE=D:\Source\NCUCodeMerge\Track2_NCU_Code\src
set TRACK=Track2
set ARGS=-c -std=c90 -Dlinux -Wno-macro-redefined -Wno-return-type -Wno-implicit-function-declaration -nostdinc -isystem stdincludes -I %NCUINCLUDE% -Xclang -ast-dump=json -ferror-limit=9999


set DIR=%1
set FILE=%2
tr --delete '\r' <  %NCUBASE%\%DIR%\%FILE% > BuildDir\%TRACK%\%DIR%\%FILE%
clang  %ARGS% BuildDir\%TRACK%\%DIR%\%FILE% > BuildDir\%TRACK%\%DIR%\%FILE%.json 2> BuildDir\%TRACK%\%DIR%\%FILE%.errors


set NCUINCLUDE=D:\Source\NCUCodeMerge\Track3_NCU_Code\G3\src\include\
set NCUBASE=D:\Source\NCUCodeMerge\Track3_NCU_Code\G3\src
set TRACK=Track3

tr --delete '\r' <  %NCUBASE%\%DIR%\%FILE% > BuildDir\%TRACK%\%DIR%\%FILE%
clang  %ARGS% BuildDir\%TRACK%\%DIR%\%FILE% > BuildDir\%TRACK%\%DIR%\%FILE%.json 2> BuildDir\%TRACK%\%DIR%\%FILE%.errors
