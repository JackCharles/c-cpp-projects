;user.asm:
;===============================================================================
SECTION header vstart=0                     ;定义用户程序头部段
    program_length  dd program_end          ;程序总长度[0x00]0-4

    ;用户程序入口点
    code_entry      dw start                ;偏移地址[0x04]4-6
                    dd section.code.start   ;段地址[0x06]6-a

    realloc_tbl_len dw (header_end-code_segment)/4;段重定位表项个数[0x0a]

    ;段重定位表
    code_segment  dd section.code.start ;[0x0c]
    data_segment  dd section.data.start

    header_end:

;===============================================================================
SECTION data align=16 vstart=0
string: 
       db '1+2+3+...+9999+10000='

end_data:    
;===============================================================================       
       
SECTION code align=16 vstart=0
start:
       mov ax,0xb800
       mov es,ax
       mov ax,[data_segment]
       mov ds,ax
;--------------------------------------------------------------------------;       
       mov si,string
       mov cx,(end_data-string)
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
       add ax,cx                     ;adc 除add外还要加上进位CF
       adc dx,0                      ;相当于DX:AX 32位组合寄存器 
       inc cx
       cmp cx,10000                  ;比较cx,10000的大小，结果写入ZF,SF等 
       jle adda                      ;<=,ZF=1 and SF(符号,负数为1)!=OF(溢出)
;--------------------------------------------------------------------------;                         
       mov bx,0x00
       mov ss,bx                     ;定义一个栈 
       mov sp,bx
                                     ;32位防溢出除法 
       mov di,1                      ;控制相除次数			    
divi:
       mov cx,10                     ;设置除数 
       push ax                       ;保存AX，32位的低16位 
       mov ax,dx
       xor dx,dx                     ;把DX扩展到DX:AX
       div cx
       mov bx,ax                     ;保存高16位相除的商
       pop ax                        ;恢复低16位，不动高16位相除的余数 
       div cx
       mov cx,dx                     ;保存真正余数到cx 
       mov dx,bx                     ;恢复高16位的商,与AX组成整个结果的商 
                                     ;DX:AX组成下一轮的被除数 
       add cl,'0'
       mov ch,0x0a
       push cx
       inc di
       cmp di,8
       jle divi
;-------------------------------------------------------------------------;      
       mov si,(end_data-string+1)*2    ;显存偏移
       mov cx,8						
 show:
       pop ax     		     ;弹栈 
       mov word [es:si],ax	     ;送入显存
       add si,2
       loop show
;-------------------------------------------------------------------------;       
       jmp near $
code_end:
;=========================================================================;
SECTION trail align=16
program_end:
