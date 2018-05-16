         ;代码清单13-3
         ;文件名：c13.asm
         ;文件说明：用户程序 
         ;创建日期：2011-10-30 15:19   
         
;===============================================================================
SECTION header vstart=0

         program_length   dd program_end          ;程序总长度#0x00
         
         head_len         dd header_end           ;程序头部的长度#0x04，重定位后存储头部段选择子

         stack_seg        dd 0                    ;用于接收堆栈段选择子#0x08,重定位后存储堆栈段选择子
         stack_len        dd 1                    ;程序建议的堆栈大小#0x0c
                                                  ;以4KB为单位
                                                  
         prgentry         dd start                ;程序入口#0x10 
         code_seg         dd section.code.start   ;代码段位置#0x14，重定位后存储代码段选择子
         code_len         dd code_end             ;代码段长度#0x18

         data_seg         dd section.data.start   ;数据段位置#0x1c，重定位后存储数据段选择子
         data_len         dd data_end             ;数据段长度#0x20
             
;-------------------------------------------------------------------------------
         ;符号地址检索表
         salt_items       dd (header_end-salt)/256 ;#0x24
         
         salt:                                     ;#0x28
         PrintString      db  '@PrintString'       ;重定位后开始6字节存储的是偏移(4B)和公共例程段选择子(2B)
                     times 256-($-PrintString) db 0
                     
         TerminateProgram db  '@TerminateProgram'
                     times 256-($-TerminateProgram) db 0
                     
         ReadDiskData     db  '@ReadDiskData'
                     times 256-($-ReadDiskData) db 0
                 
header_end:

;===============================================================================
SECTION data vstart=0    
         message	 db 0x0d,0x0a,0x0d,0x0a,'  1+2+3+...+1999+2000= ',0
	 buffer times 20 db 0
data_end:

;===============================================================================
      [bits 32]
;===============================================================================
SECTION code vstart=0
start:
         mov eax,ds
         mov fs,eax               ;fs<-头部选择子
     
         mov eax,[stack_seg]
         mov ss,eax               ;ss<-栈段
         mov esp,0
     
         mov eax,[data_seg]
         mov ds,eax               ;ds<-数据段
;================================================================================    

         mov ecx,2000
         xor eax,eax
addi:	
	 add eax,ecx
	 loop addi
		 
	 mov ecx,7
         mov esi,10
		 
divi:	 
	 xor edx,edx
	 div esi
	 add edx,'0'
	 mov [buffer+ecx-1],dl
	 loop divi
		 
         mov ebx,message
         call far [fs:PrintString]          ;32位call far[addr]是从addr处取出一个32位偏移和16位段选择子
     
         mov ebx,buffer 
         call far [fs:PrintString]           
     
         jmp far [fs:TerminateProgram]       ;将控制权返回到系统 
      
code_end:

;===============================================================================
SECTION trail
;-------------------------------------------------------------------------------
program_end: