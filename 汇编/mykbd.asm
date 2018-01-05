              ;使寄存器R加1，模80
      INCREG  MACRO     R
              LOCAL     NORMAL
              INC       R
              CMP       R ,80
              JNZ       NORMAL
              MOV       R,0
     NORMAL:  NOP
              ENDM

    DISPHALF  MACRO
              LOCAL     DIGIT,DPC
              CMP       DL,9
              JBE       DIGIT
              ADD       DL,'A'-10
              JMP       DPC
      DIGIT:  ADD       DL,'0'
        DPC:  MOV       AH,2
              INT       21H
              ENDM

   DISPHEXAL  MACRO
              ROR       AL,4
              MOV       DL,AL
              AND       DL,0FH
              PUSH      AX
              DISPHALF
              POP       AX
              ROR       AL,4
              MOV       DL,AL
              AND       DL,0FH
              DISPHALF
              MOV       DL,' '
              MOV       AH,2
              INT       21H
              MOV       DL,' '
              MOV       AH,2
              INT       21H
              ENDM

.MODEL        SMALL
.STACK
.DATA
         BUF  DB        80 DUP(0)   ;缓冲区80个字节
       COUNT  DW        0           ;定时器中断次数
      OLDSEG  DW        0
      OLDOFF  DW        0           ;老的int09的偏移地址
      ISFULL  DB        0           ;键盘缓冲区满标志
.CODE
      START:  MOV       AX,@DATA
              MOV       DS,AX

              IN        AL,21H
              PUSH      AX
              AND       AL,0FDH     ;设置键盘中断允许
              OUT       21H,AL

              MOV       AX,0
              MOV       ES,AX
              ;保存老的中断向量
              PUSH      ES:[26H]    ;老的int09的段地址
              PUSH      ES:[24H]    ;老的int09的偏移地址
              ;设置新的中断向量
              CLI
              MOV       WORD PTR ES:[26H],SEG NEWINT09
              MOV       WORD PTR ES:[24H],OFFSET NEWINT09
              STI

              MOV       SI,0        ;键值存入位置
              MOV       DI,0        ;待显示字符位置

        KBD:  MOV       AL,1
              CMP       ISFULL,AL
              JNZ       DISP        ;缓冲区满则不接受输入，转到显示
              JMP       OVER

       DISP:  CMP       SI,DI       ;判断缓冲区是否空
              JZ        KBD
              MOV       AL,[DI]     ;待显示数据-〉DL  es=DS
              CMP       AL,01H      ;是ESC退出键吗？
              JZ        OVER        ;是转结束

              DISPHEXAL                     ;不空则把数据显示
              INCREG    DI
              JMP       KBD

              ;改回老的中断向量
       OVER:  CLI
              POP       ES:[24H]
              POP       ES:[26H]
              STI

              POP       AX
              OUT       21H,AL      ;恢复老的IMR

              ;主程序结束
              MOV       AX,4C00H
              INT       21H


              ;键盘中断处理子程序，读取扫描码并发应答信号，扫描码送缓冲区
    NEWINT09  PROC      NEAR
              STI
              PUSH      AX

              IN        AL,61H
              AND       AL,7FH
              OUT       61H,AL      ;PB7=0复位
              NOP

              IN        AL,60H      ;读取键盘扫描码
              PUSH      AX          ;保存扫描码

              ;发送应答信号，可以没有这段程序！但处理起来慢。
              IN        AL,61H
              OR        AL,80H
              OUT       61H,AL      ;PB7=1瞬时置1
              NOP

              MOV       AX,SI
              INCREG    AX
  CHECKFULL:  CMP       AX,DI
              JZ        FULL        ;缓冲区满则不接受输入，转到ISFULL
              POP       AX
              MOV       [SI],AL     ;不是则把键值送入缓冲区
              INCREG    SI          ;接收指针+1
              JMP       EXIT
       FULL:  POP       AX
              MOV       AL,1
              MOV       ISFULL,AL

       EXIT:  MOV       AL,20H
              OUT       20H,AL
              POP       AX
              IRET
    NEWINT09  ENDP

              END       START


