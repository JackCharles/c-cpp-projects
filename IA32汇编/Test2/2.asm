;����1+2+3+...+10000=?

jmp near start
string: 
       db '1+2+3+...+9999+10000='
number:
       db 0,0,0,0,0,0,0,0,0,0
start:
       mov ax,0xb800
       mov es,ax
       mov ax,0x07c0
       mov ds,ax
;--------------------------------------------------------------------------;       
       mov si,string
       mov cx,(number-string)
       xor di,di                      
       mov ah,0x0f
ShowStr:
       mov al,[si]
       mov [es:di],ax
       add di,2
       inc si
       loop ShowStr
;--------------------------------------------------------------------------;       
       mov cx,1
       xor ax,ax
       xor dx,dx
adda:
       add ax,cx                     ;adc ��add�⻹Ҫ���Ͻ�λCF
       adc dx,0                      ;�൱��DX:AX 32λ��ϼĴ��� 
       inc cx
       cmp cx,10000                  ;�Ƚ�cx,10000�Ĵ�С�����д��ZF,SF
       jle adda                      ;<=,ZF=1 and SF(����,����Ϊ1)!=OF(���)
;--------------------------------------------------------------------------;                         
       mov bx,0x00
       mov ss,bx                     ;����һ��ջ 
       mov sp,bx
                                     ;32λ��������� 
       mov di,1                      ;�����������			    
divi:
       mov cx,10                     ;���ó��� 
       push ax                       ;����AX��32λ�ĵ�16λ 
       mov ax,dx
       xor dx,dx                     ;��DX��չ��DX:AX
       div cx
       mov bx,ax                     ;�����16λ�������
       pop ax                        ;�ָ���16λ��������16λ��������� 
       div cx
       mov cx,dx                     ;��������������cx 
       mov dx,bx                     ;�ָ���16λ����,��AX������������
                                     ;DX:AX�����һ�ֵı����� 
       add cl,'0'
       mov ch,0x0a
       push cx
       inc di
       cmp di,8
       jle divi
;-------------------------------------------------------------------------;      
       mov si,(number-string+1)*2    ;�Դ�ƫ��
       mov cx,8						
 show:
       pop ax     		     ;��ջ 
       mov word [es:si],ax	     ;�����Դ�
       add si,2
       loop show
;-------------------------------------------------------------------------;       
       jmp near $
       times 510-($-$$) db 0
       dw 0xaa55
