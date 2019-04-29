# mmap

## 修改文件
系统调用mmap可以将文件映射至内存(进程空间)，如此可以把对文件的操作转为对内存的操作，以此避免更多的lseek()、read()、write()等系统调用，这点对于大文件或者频繁访问的文件尤其有用，提高了I/O效率
+ mmap_modify_file.c
+ mmap_modify_file.txt

## 进程通信

#### 不相关
+ mmap_IPC_A.c
+ mmap_IPC_B.c
+ mmap_IPC.txt

#### 父子进程
+ mmap_IPC_parent.c
