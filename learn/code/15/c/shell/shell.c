#include "shell.h"
#include "stdint.h"
#include "fs.h"
#include "file.h"
#include "syscall.h"
#include "stdio.h"
#include "global.h"
#include "assert.h"
#include "string.h"
#include "buildin_cmd.h"

#define MAX_ARG_NR 16	   // 加上命令名外,最多支持15个参数

// 存储输入的命令
static char cmd_line[MAX_PATH_LEN] = {0};
char final_path[MAX_PATH_LEN] = {0};      // 用于写路径时的缓冲
// 用来记录当前目录,是当前目录的缓存, 每次执行 cd 命令时会更新此内容
char cwd_cache[MAX_PATH_LEN] = {0};

// 输出提示符
void print_prompt(void) {
    printf("[wei@weios %s]$ ", cwd_cache);
}

// 从键盘缓冲区中最多读入 count 个字节到 buf。
static void readline(char* buf, int32_t count) {
    assert(buf != NULL && count > 0);
    char* pos = buf;
    while (read(stdin_no, pos, 1) != -1 && (pos - buf) < count) { // 在不出错情况下, 直到找到回车符才返回
        switch (*pos) {
            // 找到回车或换行符后认为键入的命令结束,直接返回
            case '\n':
            case '\r':
                *pos = 0;	   // 添加 cmd_line 的终止字符0
                putchar('\n');
                return;
            case '\b':
                if (cmd_line[0] != '\b') {		// 阻止删除非本次输入的信息
                    --pos;	   // 退回到缓冲区 cmd_line 中上一个字符
                    putchar('\b');
                }
                break;
                // ctrl+l 清屏
            case 'l' - 'a':
                *pos = 0;
                clear();
                print_prompt();
                printf("%s", buf);
                break;
                // ctrl+u 清掉输入
            case 'u' - 'a':
                while (buf != pos) {
                    putchar('\b');
                    *(pos--) = 0;
                }
                break;
            default:
                putchar(*pos);
                pos++;
        }
    }
    printf("readline: can`t find enter_key in the cmd_line, max num of char is 128\n");
}

// 分析字符串 cmd_str 中以 token 为分隔符的单词, 将各单词的指针存入 argv 数组
static int32_t cmd_parse(char* cmd_str, char** argv, char token) {
    assert(cmd_str != NULL);
    int32_t arg_idx = 0;
    while(arg_idx < MAX_ARG_NR) {
        argv[arg_idx] = NULL;
        arg_idx++;
    }
    char* next = cmd_str;
    int32_t argc = 0;
    // 外层循环处理整个命令行
    while(*next) {
        // 去除命令字或参数之间的空格
        while(*next == token) {
            next++;
        }
        // 处理最后一个参数后接空格的情况,如 "ls dir2 "
        if (*next == 0) {
            break;
        }
        argv[argc] = next;

        // 内层循环处理命令行中的每个命令字及参数
        while (*next && *next != token) {	  // 在字符串结束前找单词分隔符
            next++;
        }

        // 如果未结束(是 token 字符), 使 token 变成0
        if (*next) {
            *next++ = 0;	// 将 token 字符替换为字符串结束符 0,做为一个单词的结束, 并将字符指针 next 指向下一个字符
        }

        if (argc > MAX_ARG_NR) {
            return -1;
        }
        argc++;
    }
    return argc;
}

char* argv[MAX_ARG_NR];    // argv 必须为全局变量，为了以后 exec 的程序可访问参数
int32_t argc = -1;

// 简单的shell
void my_shell(void) {
    cwd_cache[0] = '/';
    while (1) {
        print_prompt();
        memset(final_path, 0, MAX_PATH_LEN);
        memset(cmd_line, 0, MAX_PATH_LEN);
        readline(cmd_line, MAX_PATH_LEN);
        if (cmd_line[0] == 0) {	 // 若只键入了一个回车
            continue;
        }
        argc = -1;
        argc = cmd_parse(cmd_line, argv, ' ');
        if (argc == -1) {
            printf("num of arguments exceed %d\n", MAX_ARG_NR);
            continue;
        }
        if (!strcmp("ls", argv[0])) {
            buildin_ls(argc, argv);
        } else if (!strcmp("cd", argv[0])) {
            if (buildin_cd(argc, argv) != NULL) {
                memset(cwd_cache, 0, MAX_PATH_LEN);
                strcpy(cwd_cache, final_path);
            }
        } else if (!strcmp("pwd", argv[0])) {
            buildin_pwd(argc, argv);
        } else if (!strcmp("ps", argv[0])) {
            buildin_ps(argc, argv);
        } else if (!strcmp("clear", argv[0])) {
            buildin_clear(argc, argv);
        } else if (!strcmp("mkdir", argv[0])){
            buildin_mkdir(argc, argv);
        } else if (!strcmp("rmdir", argv[0])){
            buildin_rmdir(argc, argv);
        } else if (!strcmp("rm", argv[0])) {
            buildin_rm(argc, argv);
        } else {
            printf("external command\n");
        }
    }
    panic("my_shell: should not be here");
}