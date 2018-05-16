;计算1+2+3+...+10000

jmp near start

;data segement
string: 
       db '1+2+3+...+9999+10000='
number:
       times 10 db 0

;code segement   
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
       mov si,(number-string+1)*2    ;显存偏移
       mov cx,8						
 show:
       pop ax     		     ;弹栈 
       mov word [es:si],ax	     ;送入显存
       add si,2
       loop show
;-------------------------------------------------------------------------;       
       jmp near $
       times 510-($-$$) db 0
       dw 0xaa55
       
;-------------------------------------------------------------------------;
;关于32位除法公式推导: X/N=int (H/N)*2^16 + [rem(H/N)*2^16+L]/N
;其中int(H/N)代表商，rem(H/N)代表余数,X被拆分为高16位H和低16位L 
;X=H*65536+L 
;X/N=(H*65536+L)/N 
;   =[(AN+B)/N]*65536+L/N    其中H/N=A......B 
;   =[A+B/N]*65536+L/N
;   =A*65536+B/N*65536+L/N 
;   =A*2^16+(B*2^16+L)/N     其中A=int(H/N), B=rem(H/N) 