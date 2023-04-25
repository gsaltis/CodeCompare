@echo off
doskey m=make -j 8 -f Makefile.Release $T make -j 4 -f Makefile.Debug
doskey mr=color $T cls $T make -j 8 -f Makefile.Release
doskey md=make -j 8 -f Makefile.Debug
doskey mc=make cleanall
doskey mq=qmake
doskey co=release\CodeCompare $*
doskey co2=release\CodeCompare -1 C:\users\greg.saltis\\Source\NCUCodeMerge\Track2_NCU_Code-master\src -2 C:\users\greg.saltis\Source\NCUCodeMerge\Track3_NCU_Code-master\G3\src $*
doskey co1=release\CodeCompare -1 C:\users\greg.saltis\\Source\NCUCodeMerge\Track2_NCU_Code-master\src
doskey cod=gdb debug\CodeCompare $*
title CodeCompare
