              ;ʹ�Ĵ���R��1��ģ80
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
         BUF  DB        80 DUP(0)   ;������80���ֽ�
       COUNT  DW        0           ;��ʱ���жϴ���
      OLDSEG  DW        0
      OLDOFF  DW        0           ;�ϵ�int09��ƫ�Ƶ�ַ
      ISFULL  DB        0           ;���̻���������־
.CODE
      START:  MOV       AX,@DATA
              MOV       DS,AX

              IN        AL,21H
              PUSH      AX
              AND       AL,0FDH     ;���ü����ж�����
              OUT       21H,AL

              MOV       AX,0
              MOV       ES,AX
              ;�����ϵ��ж�����
              PUSH      ES:[26H]    ;�ϵ�int09�Ķε�ַ
              PUSH      ES:[24H]    ;�ϵ�int09��ƫ�Ƶ�ַ
              ;�����µ��ж�����
              CLI
              MOV       WORD PTR ES:[26H],SEG NEWINT09
              MOV       WORD PTR ES:[24H],OFFSET NEWINT09
              STI

              MOV       SI,0        ;��ֵ����λ��
              MOV       DI,0        ;����ʾ�ַ�λ��

        KBD:  MOV       AL,1
              CMP       ISFULL,AL
              JNZ       DISP        ;���������򲻽������룬ת����ʾ
              JMP       OVER

       DISP:  CMP       SI,DI       ;�жϻ������Ƿ��
              JZ        KBD
              MOV       AL,[DI]     ;����ʾ����-��DL  es=DS
              CMP       AL,01H      ;��ESC�˳�����
              JZ        OVER        ;��ת����

              DISPHEXAL                     ;�������������ʾ
              INCREG    DI
              JMP       KBD

              ;�Ļ��ϵ��ж�����
       OVER:  CLI
              POP       ES:[24H]
              POP       ES:[26H]
              STI

              POP       AX
              OUT       21H,AL      ;�ָ��ϵ�IMR

              ;���������
              MOV       AX,4C00H
              INT       21H


              ;�����жϴ����ӳ��򣬶�ȡɨ���벢��Ӧ���źţ�ɨ�����ͻ�����
    NEWINT09  PROC      NEAR
              STI
              PUSH      AX

              IN        AL,61H
              AND       AL,7FH
              OUT       61H,AL      ;PB7=0��λ
              NOP

              IN        AL,60H      ;��ȡ����ɨ����
              PUSH      AX          ;����ɨ����

              ;����Ӧ���źţ�����û����γ��򣡵�������������
              IN        AL,61H
              OR        AL,80H
              OUT       61H,AL      ;PB7=1˲ʱ��1
              NOP

              MOV       AX,SI
              INCREG    AX
  CHECKFULL:  CMP       AX,DI
              JZ        FULL        ;���������򲻽������룬ת��ISFULL
              POP       AX
              MOV       [SI],AL     ;������Ѽ�ֵ���뻺����
              INCREG    SI          ;����ָ��+1
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


