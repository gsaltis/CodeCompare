@echo off
doskey m=make -j 8 -f Makefile.Release $T make -j 4 -f Makefile.Debug
doskey mr=make -j 8 -f Makefile.Release
doskey md=make -j 8 -f Makefile.Debug
doskey mc=make cleanall
doskey mq=qmake
doskey co=release\CodeCompare $*
doskey cod=debug\CodeCompare $*
title CodeCompare
