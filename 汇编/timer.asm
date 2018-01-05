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
       COUNT  DB        0           ;定时器中断次数
         TMP  DW        55AAH
.CODE
      START:
              MOV       AX,@DATA
              MOV       DS,AX

              MOV       AX,0
              MOV       ES,AX
              ;保存老的中断向量
              PUSH      ES:[1CH*4+2]                    ;INT 08 调用了 INT 1CH,所以可以这样 
              PUSH      ES:[1CH*4]
              ;设置新的中断向量
              CLI
              MOV       WORD PTR ES:[1CH*4+2],SEG NEWINT1C
              MOV       WORD PTR ES:[1CH*4],OFFSET NEWINT1C
              STI

       DISP:  MOV       AL,COUNT
              DISPHEXAL
              MOV       CX,0        ;开始延迟程序
      DELAY:  XCHG      AX,TMP
              XCHG      AX,TMP
              LOOP      DELAY       ;结束延迟程序
              CMP       COUNT,100   ;判断是否计数结束
              JB        DISP        ;没有转开始接收
          
              ;改回老的中断向量
       OVER:  CLI
              POP       ES:[1CH*4]
              POP       ES:[1CH*4+2]
              STI
              ;主程序结束
              MOV       AX,4C00H
              INT       21H

              ;中断处理子程序，使count加1
    NEWINT1C  PROC      NEAR
              PUSH      AX
              PUSH      DS          ;由于int8修改了DS
              MOV       AX,@DATA
              MOV       DS,AX
              INC       COUNT
              POP       DS
              POP       AX
              IRET
    NEWINT1C  ENDP

              END       START

