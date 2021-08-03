

DIR="/usr/local/Cellar/bochs/"

VERSION_1="2.6.11"
VERSION_2="2.6.9_2"

if [ -d "${DIR}${VERSION_1}" ]; then
    echo "bochs version ${VERSION_1}"
    export BXSHARE=${DIR}${VERSION_1}/share/bochs
    export BOCHS_WORK=/Users/fei.wei/pro/weios/learn/
elif [ -d "${DIR}${VERSION_2}" ]; then
    echo "bochs version ${VERSION_2}"
    export BXSHARE=${DIR}${VERSION_2}/share/bochs
    export BOCHS_WORK=/Users/weifei/Desktop/weios/learn/
else
    echo "err: can't find bochs"
    exit 1
fi


# hd10M.img
# 直接声明到 img 好像不行 - -
bochs -f bochs.disk
