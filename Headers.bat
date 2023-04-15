clang -H -isystem d:/Source/NCUCodeMerge/arm926/host-cross/arm-wrs-linux-gnueabi/sysroot/usr/include -ID:/Source/NCUCodeMerge/Track2_NCU_CODE/src/include -ferror-limit=9999 %1 2> %1.errors
grep "^\.\+ " %1.errors | grep -v arm926 | grep -v Qt | grep -v Clang > %1.headers
