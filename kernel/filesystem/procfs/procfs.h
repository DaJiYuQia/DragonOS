#pragma once

#include <filesystem/VFS/VFS.h>
#include <common/lockref.h>
#include <common/spinlock.h>
#include <common/stdlib.h>
#include <common/stdio.h>
#include <common/string.h>
#include <process/process.h>
// #include <stdio.h>

/**
 * @brief 初始化procfs
 *
 */
void procfs_init();

/**
 * @brief proc文件系统的超级块信息结构体
 *
 */
struct procfs_sb_info_t
{
    struct lockref lockref; //该lockref包含自旋锁以及引用计数
};
typedef struct procfs_sb_info_t procfs_sb_info_t;

/**
 * @brief procfs文件系统的结点私有信息
 *
 */
struct procfs_inode_info_t
{
    pid_t pid;       //进程号
    unsigned int fd; //文件描述符
};

/**
 * @brief 私有信息结构
 *
 */
struct proc_data {
  	int release_buffer;
  	int readlen;
  	char *rbuffer;
  	int writelen;
  	int maxwritelen;
  	char *wbuffer;
  	void (*on_close) (struct vfs_index_node_t *, struct vfs_file_t *);
};

/**
 * @brief 检查文件名是否合法
 *
 * @param name 文件名
 * @param namelen 文件名长度
 * @param reserved 保留字段
 * @return int 合法：0， 其他：错误码
 */
int check_name_available(const char *name, int namelen, int8_t reserved)
{
    if (namelen > 255 || namelen <= 0)
        return -ENAMETOOLONG;
    // 首个字符不能是空格或者'.'
    if (name[0] == 0x20 || name[0] == '.')
        return -EINVAL;

    return 0;
};

/**
 * @brief 创建进程对应文件夹
 *
 * @param pid 进程号
 * @return int64_t 错误码
 */
int64_t mk_proc_dir(long pid)
{
    int retval = 0;
    
    //创建文件夹
    char *path = "/proc/";
    const char *temp = ltoa(pid);
    strcat(path, temp);
    vfs_mkdir(path, 0, false);

    //创建各相关文件

    
    //获取进程pcb
    struct process_control_block *tsk = process_get_pcb(pid);

    return retval;
}

/**
 * @brief 检查读取并将数据从内核拷贝到用户
 * 
 * @param to: 要读取的用户空间缓冲区
 * @param count: 要读取的最大字节数
 * @param position: 缓冲区中的当前位置
 * @param from: 要读取的缓冲区
 * @param available: 缓冲区的大小
 * 
 * @return long 读取字节数
 */
long simple_procfs_read(void *to, int64_t count, long *position, const void *from, int64_t available);