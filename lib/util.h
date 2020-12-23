#ifndef H_FILE2
#define H_FILE2
#include "diskStructure.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "disk.h"
#endif

/**
 * 超级块写入磁盘
 * @param super_block 需要写入的超级块
 */
void writeSpBlockInfo(sp_block *super_block);

/**
 * inode块写入磁盘
 * @param inode_block 需要写入的inode块
 * @param inumber 第inumber块
 */
void writeInodeInfo(inode *inode_block,int inumber);

/**
 * dirent块写入磁盘
 * @param dirent_block 需要写入的dirent块
 * @param dnumber 第dnumber块
 */
void writeDirentInfo(dirent *dirent_block,int dnumber);

/**
 * 读取超级块
 * @param super_block 读取数据存放到该超级块
 */
void readSpBlockInfo(sp_block * super_block);

/**
 * 磁盘块数据读出到inode
 * @param inode_block 读取数据存放到该inode块
 * @param inumber 第inumber块
 */
void readInodeInfo(inode *inode_block,int inumber);


/**
 * 磁盘块数据读出到dirent
 * @param dirent_block 读取数据存放到该dirent块
 * @param dnumber 第dnumber块
 */
void readDirentInfo(dirent *dirent_block,int dnumber);

/**
 * 读出第几磁盘块
 * @param block_buf 读取数据存放到该buf
 * @param blokc_number 第blokc_number块
 */
void readBlokcInfo(char *block_buf,int blokc_number);


/**
 * 写入第几磁盘块
 * @param block_buf 将该buf的数据写入磁盘块
 * @param blokc_number 第blokc_number块
 */
void writeBlokcInfo(char *block_buf,int blokc_number);

/**
 * 获取可用的磁盘块
 */
int getAvailableDataBlock();

/**
 * 获取可用的inode块
 */
int getAvailabeInodeBlock();