         ;���ö�ջ�κ�ջָ�� 
         ;cs = 0x00000
         mov ax,cs      
         mov ss,ax
         mov sp,0x7c00
      
         ;����GDT���ڵ��߼��ε�ַ 
         mov ax,[cs:gdt_base+0x7c00]        ;��16λ 
         mov dx,[cs:gdt_base+0x7c00+0x02]   ;��16λ 
         mov bx,16        
         div bx                             ;������߼��ε�ַ 
         mov ds,ax                          ;��DSָ��ö��Խ��в�������ַ�� 
         mov bx,dx                          ;������ʼƫ�Ƶ�ַ 
      
         ;����0#�����������ǿ������������Ǵ�������Ҫ��
         mov dword [bx+0x00],0x00
         mov dword [bx+0x04],0x00  

         ;����#1������������ģʽ�µĴ����������
         mov dword [bx+0x08],0x7c0001ff     
         mov dword [bx+0x0c],0x00409800     

         ;����#2������������ģʽ�µ����ݶ����������ı�ģʽ�µ���ʾ�������� 
         mov dword [bx+0x10],0x8000ffff     
         mov dword [bx+0x14],0x0040920b     

         ;����#3������������ģʽ�µĶ�ջ��������
         mov dword [bx+0x18],0x00007a00
         mov dword [bx+0x1c],0x00409600

         ;��ʼ����������Ĵ���GDTR
         mov word [cs: gdt_size+0x7c00],31  ;��������Ľ��ޣ����ֽ�����һ��   
                                             
         lgdt [cs: gdt_size+0x7c00]         ;GDTR ��16bitΪ���ޣ���32λΪ��ַ 
      
         in al,0x92                         ;����оƬ�ڵĶ˿� 
         or al,0000_0010B
         out 0x92,al                        ;��A20

         cli                                ;����ģʽ���жϻ�����δ������Ӧ 
                                            ;��ֹ�ж� 
         mov eax,cr0
         or eax,1
         mov cr0,eax                        ;����PEλ
      
         ;�Ѿ����뱣��ģʽ0x0008������Ϊ��ѡ���� EIP��flush����ʼ 
         jmp dword 0x0008:flush             ;16λ��������ѡ���ӣ�32λƫ��
         ;Զת�ƻ��Զ�����CS,�˴��Զ���0x0008�ŵ�CS��,����ˮ�߲����л������� 
         [bits 32] 

    flush:
         mov cx,00000000000_10_000B         ;�������ݶ�ѡ����(0x10)
         mov ds,cx

         mov cx,00000000000_11_000B         ;���ض�ջ��ѡ����
         mov ss,cx
         mov esp,0x7c00
 
 ;=============================================================================; 
         
         mov edi,1                          ;�׳��� 
         mov eax,1
         xor edx,edx
	 xor ebx,ebx
	 xor ecx,ecx
   mult:
         ;��32λ��˷���EBX:ECX��
	 push edx
	 mul edi
	 mov ecx,eax
	 mov ebx,edx
	 ;��32λ�������32λ�ŵ�EDX:EAX��
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

         mov di,1                      ;�����������			    
   divi:
         mov ecx,10                     ;���ó��� 
         push eax                       ;����AX��32λ�ĵ�16λ 
         mov eax,edx
         xor edx,edx                     ;��DX��չ��DX:AX
         div ecx
         mov ebx,eax                     ;�����16λ�������
         pop eax                        ;�ָ���16λ��������16λ��������� 
         div ecx
         mov cl,dl                     ;��������������cx 
         mov edx,ebx                     ;�ָ���16λ����,��AX�������������� 
                                     ;DX:AX�����һ�ֵı����� 
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

         mov cx,13                          ;���λ�� 
         mov bx,8
  showNum:
         pop ax
         mov [ds:bx],ax
         add bx,2
         loop showNum
       
      
  ghalt:     
         hlt                                ;�Ѿ���ֹ�жϣ������ᱻ����   
;-------------------------------------------------------------------------------
     
         gdt_size         dw 0
         gdt_base         dd 0x00007e00     ;GDT�������ַ 
                             
         times 510-($-$$) db 0
                          db 0x55,0xaa