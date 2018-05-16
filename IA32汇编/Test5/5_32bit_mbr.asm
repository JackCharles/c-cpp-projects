         ;设置堆栈段和栈指针 
         ;cs = 0x00000
         mov ax,cs      
         mov ss,ax
         mov sp,0x7c00
      
         ;计算GDT所在的逻辑段地址 
         mov ax,[cs:gdt_base+0x7c00]        ;低16位 
         mov dx,[cs:gdt_base+0x7c00+0x02]   ;高16位 
         mov bx,16        
         div bx                             ;换算成逻辑段地址 
         mov ds,ax                          ;令DS指向该段以进行操作（基址） 
         mov bx,dx                          ;段内起始偏移地址 
      
         ;创建0#描述符，它是空描述符，这是处理器的要求
         mov dword [bx+0x00],0x00
         mov dword [bx+0x04],0x00  

         ;创建#1描述符，保护模式下的代码段描述符
         mov dword [bx+0x08],0x7c0001ff     
         mov dword [bx+0x0c],0x00409800     

         ;创建#2描述符，保护模式下的数据段描述符（文本模式下的显示缓冲区） 
         mov dword [bx+0x10],0x8000ffff     
         mov dword [bx+0x14],0x0040920b     

         ;创建#3描述符，保护模式下的堆栈段描述符
         mov dword [bx+0x18],0x00007a00
         mov dword [bx+0x1c],0x00409600

         ;初始化描述符表寄存器GDTR
         mov word [cs: gdt_size+0x7c00],31  ;描述符表的界限（总字节数减一）   
                                             
         lgdt [cs: gdt_size+0x7c00]         ;GDTR 低16bit为界限，高32位为基址 
      
         in al,0x92                         ;南桥芯片内的端口 
         or al,0000_0010B
         out 0x92,al                        ;打开A20

         cli                                ;保护模式下中断机制尚未建立，应 
                                            ;禁止中断 
         mov eax,cr0
         or eax,1
         mov cr0,eax                        ;设置PE位
      
         ;已经进入保护模式0x0008将解释为段选择子 EIP从flush处开始 
         jmp dword 0x0008:flush             ;16位的描述符选择子：32位偏移
         ;远转移会自动重置CS,此处自动将0x0008放到CS中,清流水线并串行化处理器 
         [bits 32] 

    flush:
         mov cx,00000000000_10_000B         ;加载数据段选择子(0x10)
         mov ds,cx

         mov cx,00000000000_11_000B         ;加载堆栈段选择子
         mov ss,cx
         mov esp,0x7c00
 
 ;=============================================================================; 
         
         mov edi,1                          ;阶乘数 
         mov eax,1
         xor edx,edx
	 xor ebx,ebx
	 xor ecx,ecx
   mult:
         ;低32位相乘放在EBX:ECX中
	 push edx
	 mul edi
	 mov ecx,eax
	 mov ebx,edx
	 ;高32位相乘左移32位放到EDX:EAX中
	 pop eax
	 mul edi
	 mov edx,eax
	 xor eax,eax
	 ;EDX:EAX + EBX:ECX -> EDX:EAX
	 add eax,ecx
	 adc edx,ebx
		 
	 inc edi
	 cmp edi,15
         jle mult
         
 ;=============================================================================;        

         mov di,1                      ;控制相除次数			    
   divi:
         mov ecx,10                     ;设置除数 
         push eax                       ;保存AX，32位的低16位 
         mov eax,edx
         xor edx,edx                     ;把DX扩展到DX:AX
         div ecx
         mov ebx,eax                     ;保存高16位相除的商
         pop eax                        ;恢复低16位，不动高16位相除的余数 
         div ecx
         mov cl,dl                     ;保存真正余数到cx 
         mov edx,ebx                     ;恢复高16位的商,与AX组成整个结果的商 
                                     ;DX:AX组成下一轮的被除数 
         add cl,'0'
         mov ch,0x0a
         push cx
         inc di
         cmp di,13
         jle divi
         
         xor bx,bx
  showMsg:
         mov word [ds:bx+0],0x0f31          ;1 
         mov word [ds:bx+2],0x0f35          ;5
         mov word [ds:bx+4],0x0f21          ;!
         mov word [ds:bx+6],0x0f3d          ;=

         mov cx,13                          ;结果位数 
         mov bx,8
  showNum:
         pop ax
         mov [ds:bx],ax
         add bx,2
         loop showNum
       
      
  ghalt:     
         hlt                                ;已经禁止中断，将不会被唤醒   
;-------------------------------------------------------------------------------
     
         gdt_size         dw 0
         gdt_base         dd 0x00007e00     ;GDT的物理地址 
                             
         times 510-($-$$) db 0
                          db 0x55,0xaa