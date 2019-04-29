功能：快速编译自定义php扩展，把cm.sh放在php源码ext/[你的拓展]/下

使用：命令行输入  ./cm.sh

cm.sh

echo "------compile php module------"
echo "------created by Shark ------"
echo "------if prompts 'permisition denied'------"
echo "------chmod +x cm.sh will solve------"

sudo phpize
./configure
make
make install
