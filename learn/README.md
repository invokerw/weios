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
