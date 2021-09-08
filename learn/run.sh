

DIR="/usr/local/Cellar/bochs/"

VERSION="2.7"
if [ -d "${DIR}${VERSION}" ]; then
    echo "find bochs 2.7"
else
    echo "err: can't find bochs"
    exit 1
fi

export BXSHARE=${DIR}${VERSION}/share/bochs
export BOCHS_WORK=.


# hd10M.img
# 直接声明到 img 好像不行 - -
bochs -f bochs.disk
