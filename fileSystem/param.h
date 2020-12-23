#define MAX_INODE_NUMBER 32 * 32       // 最大索引数组块的数量
#define BLOCK_NUMBER_IN_INODE 6        // 每个索引数组包含的数据块个数
#define MAX_NAME_LENGTH 121            // 文件/目录名最大长度
#define MAX_BLOCK_NUMBER 4 * 1024      // 最大数据块数量
#define BLOCK_MAP_LENGTH 121           // 数据块位图大小
#define INODE_MAP_LENGTH 32            // 索引节点块位图大小
#define MAGIC_NUMBER 0x18110426        // 文件系统幻数
#define FILE_SIZE 6 * 1024             // 文件大小
#define ROOT_INODE 0                      // 根inode地址
#define ROOT_BLOCK 66                     // 根数据块地址
#define INODE_DIV ( DEVICE_BLOCK_SIZE / sizeof(inode) )  // 每个磁盘块可容纳inode数量
#define DATA_DIV ( DEVICE_BLOCK_SIZE / sizeof(dirent) )  // 每个磁盘块可容纳inode数量
#define INODE_SIZE sizeof(inode)        //inode大小
#define DIRENT_SIZE sizeof(dirent)      //dirent大小

// ----- 类型常量 -------
#define UNUSED_TYPE 0                  // 未使用过
#define DIR_TYPE 1                     // 文件夹类型
#define FILE_TYPE 2                    // 文件类型
#define NEED_ASC 1                     // 需要自增
#define NO_NEED_ASC 0                  // 需要自增
#define VALID 1                        // 文件/目录有效
#define INVALID 0                      // 文件/目录无效