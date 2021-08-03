####  此脚本应该在command目录下执行

if [[ ! -d "../lib" || ! -d "../build" ]];then
   echo "dependent dir don\`t exist!"
   cwd=$(pwd)
   cwd=${cwd##*/}
   cwd=${cwd%/}
   if [[ $cwd != "command" ]];then
      echo -e "you\`d better in command dir\n"
   fi
   exit
fi

AS=nasm
CC=/usr/local/i386elfgcc/bin/i386-elf-gcc
LD=/usr/local/i386elfgcc/bin/i386-elf-ld
AR=/usr/local/i386elfgcc/bin/i386-elf-ar
AS_FLAGS="-f elf"


BIN="prog_arg"

CFLAGS="-Wall -c -fno-builtin -W -Wstrict-prototypes \
      -Wmissing-prototypes -Wsystem-headers"
LIBS="-I ../lib/ -I ../lib/kernel/ -I ../lib/user/ -I \
      ../kernel/ -I ../device/ -I ../thread/ -I \
      ../userprog/ -I ../fs/ -I ../shell/"
OBJS="../build/string.o ../build/syscall.o \
      ../build/stdio.o ../build/assert.o ../build/start.o"

${AS} ${AS_FLAGS} ./start.S -o ../build/start.o
${AR} rcs ../build/simple_crt.a $OBJS

$CC $CFLAGS $LIBS -o ../build/$BIN".o" $BIN".c"
$LD ../build/$BIN".o" ../build/simple_crt.a -o ../build/$BIN

BIN="cat"
$CC $CFLAGS $LIBS -o ../build/$BIN".o" $BIN".c"
$LD ../build/$BIN".o" ../build/simple_crt.a -o ../build/$BIN