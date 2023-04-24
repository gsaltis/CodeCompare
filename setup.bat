@echo off
doskey m=make -j 8 -f Makefile.Release $T make -j 4 -f Makefile.Debug
doskey mr=color $T cls $T make -j 8 -f Makefile.Release
doskey md=make -j 8 -f Makefile.Debug
doskey mc=make cleanall
doskey mq=qmake
doskey co=release\CodeCompare $*
doskey co2=release\CodeCompare -1 D:\Source\NCUCodeMerge\Track2_NCU_Code\src -2 D:\Source\NCUCodeMerge\Track3_NCU_Code\G3\src $*
doskey cod=gdb debug\CodeCompare $*
title CodeCompare
