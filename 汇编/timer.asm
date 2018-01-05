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
       COUNT  DB        0           ;��ʱ���жϴ���
         TMP  DW        55AAH
.CODE
      START:
              MOV       AX,@DATA
              MOV       DS,AX

              MOV       AX,0
              MOV       ES,AX
              ;�����ϵ��ж�����
              PUSH      ES:[1CH*4+2]                    ;INT 08 ������ INT 1CH,���Կ������� 
              PUSH      ES:[1CH*4]
              ;�����µ��ж�����
              CLI
              MOV       WORD PTR ES:[1CH*4+2],SEG NEWINT1C
              MOV       WORD PTR ES:[1CH*4],OFFSET NEWINT1C
              STI

       DISP:  MOV       AL,COUNT
              DISPHEXAL
              MOV       CX,0        ;��ʼ�ӳٳ���
      DELAY:  XCHG      AX,TMP
              XCHG      AX,TMP
              LOOP      DELAY       ;�����ӳٳ���
              CMP       COUNT,100   ;�ж��Ƿ��������
              JB        DISP        ;û��ת��ʼ����
          
              ;�Ļ��ϵ��ж�����
       OVER:  CLI
              POP       ES:[1CH*4]
              POP       ES:[1CH*4+2]
              STI
              ;���������
              MOV       AX,4C00H
              INT       21H

              ;�жϴ����ӳ���ʹcount��1
    NEWINT1C  PROC      NEAR
              PUSH      AX
              PUSH      DS          ;����int8�޸���DS
              MOV       AX,@DATA
              MOV       DS,AX
              INC       COUNT
              POP       DS
              POP       AX
              IRET
    NEWINT1C  ENDP

              END       START

