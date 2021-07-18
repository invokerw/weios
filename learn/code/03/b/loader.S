%include "boot.inc"
SECTION LOADER vstart=LOADER_BASE_ADDR

    ; 输出背景色绿色，前景色红色，并且跳动的字符串
    mov byte [gs:0x20],'2'
    mov byte [gs:0x21],0xA4     ; A表示绿色背景闪烁，4表示前景色为红色

    mov byte [gs:0x22],' '
    mov byte [gs:0x23],0xA4

    mov byte [gs:0x24],'L'
    mov byte [gs:0x25],0xA4

    mov byte [gs:0x26],'O'
    mov byte [gs:0x27],0xA4

    mov byte [gs:0x28],'A'
    mov byte [gs:0x29],0xA4

    mov byte [gs:0x2A],'D'
    mov byte [gs:0x2B],0xA4

    mov byte [gs:0x2C],'E'
    mov byte [gs:0x2D],0xA4

    mov byte [gs:0x2E],'R'
    mov byte [gs:0x2F],0xA4

    mov byte [gs:0x30],' '
    mov byte [gs:0x31],0xA4

    jmp $		       ; 通过死循环使程序悬停在此