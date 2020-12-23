#include "string.h"
#include "ls.h"
#include "mkdir.h"
#include "touch.h"
#include "cp.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

//最大参数数量
#define MAXARGS 10
#define MAX_COMMAND_LENGTH 100
#define PATTERN_LENGTH 13
/**
* 打印出错信息
* @param errorMessage 错误信息
*/
void errorPrint(char* errorMessage);

/**
* 带有判断错误情况的fork函数
* @return 返回创建的子进程pid
*/
int myFork();

/**
* 读取指令
* @param buf 指令字符串
* @param bufSize 指令最大长度
* @return 成功读取返回0
*/
int getcmd(char *buf, int bufSize);

/**
* 判断字符是否为空
* @param c 字符
* @return 空字符返回1
*/
int isBlank(char c);

/**
* 解析命令
* @param cmd 从命令行读取的命令
* @param argv 解析出的参数
* @param argc 参数个数
*/
void AnalyseCmd(char *cmd,char* argv[],int* argc);

/**
* 执行命令
* @param argc 参数个数
* @param argv 解析出的参数
*/
void RunCmd(int argc,char* argv[]);