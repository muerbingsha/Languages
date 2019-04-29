1) compile .so

gcc testa.c testb.c testc.c -fPIC -shared -o libtest.so



2)compile test.c
gcc test.c -L. -ltest -o test

//-L.
在当前文件夹查找
