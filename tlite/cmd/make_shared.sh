#! /bin/sh

TMP_DIR=/tmp/tlite$$
CMD_DIR=$PWD
mkdir $TMP_DIR
cd $TMP_DIR
ar -x $CMD_DIR/../lib/i586-sl3-linux/libtLite.a
rm *hx*.o
rm vxlitebs.o
rm DAFRevertexingModule.o
rm tliPattern.o
rm tliPartTab.o
g++ -shared *.o -o $CMD_DIR/libtLite.so
