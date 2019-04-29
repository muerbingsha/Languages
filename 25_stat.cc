#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h> 
 
using namespace std; 
 
int main () {
    struct stat fs;
 
    int ret;
 
    ret = stat("./Makefile", &fs);
    if (ret != 0) {
          perror ("Failed ^_^");
    } else {
        //! 文件的大小，字节为单位
        cout << "size of the file in bytes: " << fs.st_size << endl;
 
        cout << "time of creation: " << ctime (&fs.st_ctime) << endl;
        cout << "time of last modification: " << ctime (&fs.st_mtime) << endl;
        cout << "time of last access: " << ctime (&fs.st_atime) << endl;
        
        cout << "id of user: " << fs.st_uid << endl;
        cout << "id of group: "<< fs.st_gid << endl;
        cout << "id of device containing file: "<< fs.st_dev << endl;
        cout << "id of device: " << fs.st_rdev << endl;
        cout << "protection: " << fs.st_mode << endl;
        cout << "blocksize for filesystem: " << fs.st_blksize << endl;
        cout << "number of inode: " << fs.st_ino << endl;
        cout << "number of inode: " << fs.st_ino << endl;
        cout << "number of hard links: " << fs.st_nlink << endl;
        cout << "number of blocks allocated: " << fs.st_blocks << endl;
    }
    return 0;
}


/* 显示文件信息
int stat(const char *filename, struct stat *buf);
struct stat {
    dev_t       st_dev;     // ID of device containing file -文件所在设备的ID
    ino_t       st_ino;     // inode number -inode节点号
    mode_t      st_mode;    // protection -保护模式?
    nlink_t     st_nlink;   // number of hard links -链向此文件的连接数(硬连接)
    uid_t       st_uid;     // user ID of owner -user id
    gid_t       st_gid;     // group ID of owner - group id
    dev_t       st_rdev;    // device ID (if special file) -设备号，针对设备文件
    off_t       st_size;    // total size, in bytes -文件大小，字节为单位
    blksize_t   st_blksize; // blocksize for filesystem I/O -系统块的大小
    blkcnt_t    st_blocks;  // number of blocks allocated -文件所占块数
 
    time_t      st_atime;   // time of last access -最近存取时间
    time_t      st_mtime;   // time of last modification -最近修改时间
    time_t      st_ctime;   // time of last status change - 创建时间
};
*/
