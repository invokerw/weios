## 参考
https://github.com/seaswalker/tiny-os.git

https://github.com/wfatestaynight/os-elephant

https://github.com/cfenollosa/os-tutorial

mac 交叉编译 linux gcc
https://github.com/cfenollosa/os-tutorial/tree/master/11-kernel-crosscompiler

http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

## 章节 code
- 02 实现一个有输出的 mbr，输出使用实模式下中断
- 03
    1. a 实现一个有输出的 mbr，输出使用写入显存。实现简单mbr实例程序，打印"1 MBR"字符串后进入死循环
       采用的是直接修改显存的方式实现，区别于之前BIOS中断方式实现
       以后都采用修改显存的方式实现打印
    2. b 实现 mbr 调用读取加载硬盘中的程序 loader(简单输出字符)。本程序实现基本MBR程序
       从磁盘的第二个扇区（磁盘扇区从0开始，跳过第一个扇区）读取1个扇区的内容
       到内存的0x900位置
       然后从该内存地址执行loader的功能
       loader 实现字符串打印 "2 LOADER"
- 04 实现从 mbr 到 loader，由 loader 实现进入保护模式
- 05 
    1. a 三种检测内存的方法
    2. b 启动内存分页机制(二级页表)
    3. c loader 加载 c 语言内核
- 06
    1. a 内核实现 put_char
    2. b 内核实现 put_int put_str(调用 put_char)
- 07
    1. a 内核初始化 8259A，实现时钟中断处理
    2. b 优化代码, 中断处理函数在 c 代码中运行 
    3. c 内核初始化 PIT8253 控制时钟中断频率
- 08
    1. a 内核实现 开关中断、panic assert、string、bitmap, 使用 Makefile
    2. b 内核使用 bitmap 进行基础内存管理
- 09 
    1. a 内核实现线程(并直接运行这个线程), 添加链表
    2. b 通过中断实现简单多线程调度
    
- 10 
    1. a 内核实现互斥锁(包含线程调度)、用锁实现终端输出
    2. b 键盘输入显示
    3. b_test 使用环形缓冲区生产者与消费者在不同线程取键盘数据

- 11 
    1. a 创建 TSS
    2. b 实现用户进程
- 12 
    1. a 添加系统调用(参数寄存器传递) get_pid printf。
       (注意 print.S:122-123 .roll_screen 中 替换为了 0xc00b8000，否则用户进程会报 page fault)
    2. a_stack_syscall 实现用栈从中断中传递
    2. b 完善内存堆管理, 提供 malloc、free 系统调用

- 13 需要 hd50M_slave.img 分区
    1. a 读取硬盘基本信息，读取写入数据，加入 idle 线程，实现 time_sleep
- 14
    1. a 创建超级快、i 节点、目录项，创建文件系统，挂载分区
    2. b 实现进程文件描述符、文件操作相关的基础函数（inode 操作，文件相关，目录相关，路径解析，文件检索)、
        创建文件、文件的打开与关闭
    3. c 实现文件写入，读取文件，文件读写指针定位，文件删除，创建目录，遍历目录(打开、关闭、读取)，删除目录
        设置与显示任务的工作目录，获取文件属性
- 15
    1. a 实现 fork 系统调用
    2. b put char, clear screen 系统调用，shell 雏形
    3. c 完善 shell 实现 cd ls pwd ps clear mkdir rmdir rm 等系统调用以及 shell 命令
    4. d 实现 exec，shell 支持外部命令，加载硬盘上的用户程序，用户进程支持参数
    5. e 完善进程退出。实现 wait 和 exit，cat
    6. f 实现管道函数，shell 中可以使用管道
    
## 注意 
1. 一定要对内存进行初始化！！！！
2. 14 章包括之前的 ide.c 需要对 name 进行 memeset。否则有可能出现莫名其妙的问题
   ```
   memset(hd->prim_parts[p_no].name, 0, 8);
   memset(hd->logic_parts[l_no].name, 0, 8);
   memset(hd->name, 0, 8);
   ```

       

        