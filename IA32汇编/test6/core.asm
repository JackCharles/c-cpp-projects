         ;代码清单13-2
         ;文件名：c13_core.asm
         ;文件说明：保护模式微型核心程序 
         ;创建日期：2011-10-26 12:11

         ;以下常量定义选择子。内核的大部分内容都应当固定，不占用汇编地址
         core_code_seg_sel     equ  0x38    ;内核代码段选择子7
         core_data_seg_sel     equ  0x30    ;内核数据段选择子6 
         sys_routine_seg_sel   equ  0x28    ;系统公共例程代码段的选择子5 
         video_ram_seg_sel     equ  0x20    ;视频显示缓冲区的段选择子4
         core_stack_seg_sel    equ  0x18    ;内核堆栈段选择子3
         mem_0_4_gb_seg_sel    equ  0x08    ;整个0-4GB内存的段的选择子1

;-------------------------------------------------------------------------------
         ;以下是系统核心的头部，用于加载核心程序 
         core_length      dd core_end       ;核心程序总长度#00

         sys_routine_seg  dd section.sys_routine.start
                                            ;系统公用例程段位置#04

         core_data_seg    dd section.core_data.start
                                            ;核心数据段位置#08

         core_code_seg    dd section.core_code.start
                                            ;核心代码段位置#0c


         core_entry       dd start          ;核心代码段入口点#10
                          dw core_code_seg_sel ;6字节32位段内偏移+16位段选择子

;===============================================================================
         [bits 32]
;===============================================================================
SECTION sys_routine vstart=0                ;系统公共例程代码段 
;-------------------------------------------------------------------------------
         ;字符串显示例程
put_string:                                 ;显示0终止的字符串并移动光标 
                                            ;输入：DS:EBX=串地址
         push ecx
  .getc:
         mov cl,[ebx]
         or cl,cl
         jz .exit
         call put_char
         inc ebx
         jmp .getc

  .exit:
         pop ecx
         retf                               ;段间返回

;-------------------------------------------------------------------------------
put_char:                                   ;在当前光标处显示一个字符,并推进
                                            ;光标。仅用于段内调用 
                                            ;输入：CL=字符ASCII码 
         pushad

         ;以下取当前光标位置
         mov dx,0x3d4
         mov al,0x0e
         out dx,al
         inc dx                             ;0x3d5
         in al,dx                           ;高字
         mov ah,al

         dec dx                             ;0x3d4
         mov al,0x0f
         out dx,al
         inc dx                             ;0x3d5
         in al,dx                           ;低字
         mov bx,ax                          ;BX=代表光标位置的16位数

         cmp cl,0x0d                        ;回车符？
         jnz .put_0a
         mov ax,bx
         mov bl,80
         div bl
         mul bl
         mov bx,ax
         jmp .set_cursor

  .put_0a:
         cmp cl,0x0a                        ;换行符？
         jnz .put_other
         add bx,80
         jmp .roll_screen

  .put_other:                               ;正常显示字符
         push es
         mov eax,video_ram_seg_sel          ;0xb8000段的选择子
         mov es,eax
         shl bx,1
         mov [es:bx],cl
         pop es

         ;以下将光标位置推进一个字符
         shr bx,1
         inc bx

  .roll_screen:
         cmp bx,2000                        ;光标超出屏幕？滚屏
         jl .set_cursor

         push ds
         push es
         mov eax,video_ram_seg_sel
         mov ds,eax
         mov es,eax
         cld
         mov esi,0xa0                       ;小心！32位模式下movsb/w/d 
         mov edi,0x00                       ;使用的是esi/edi/ecx 
         mov ecx,1920
         rep movsd
         mov bx,3840                        ;清除屏幕最底一行
         mov ecx,80                         ;32位程序应该使用ECX
  .cls:
         mov word[es:bx],0x0720
         add bx,2
         loop .cls

         pop es
         pop ds

         mov bx,1920

  .set_cursor:
         mov dx,0x3d4
         mov al,0x0e
         out dx,al
         inc dx                             ;0x3d5
         mov al,bh
         out dx,al
         dec dx                             ;0x3d4
         mov al,0x0f
         out dx,al
         inc dx                             ;0x3d5
         mov al,bl
         out dx,al

         popad
         ret                                

;===========================================================================
read_hard_disk_0:                           ;从硬盘读取一个逻辑扇区
                                            ;EAX=逻辑扇区号
                                            ;DS:EBX=目标缓冲区地址
                                            ;返回：EBX=EBX+512
         push eax 
         push ecx
         push edx
      
         push eax
         
         mov dx,0x1f2
         mov al,1
         out dx,al                          ;读取的扇区数

         inc dx                             ;0x1f3
         pop eax
         out dx,al                          ;LBA地址7~0

         inc dx                             ;0x1f4
         mov cl,8
         shr eax,cl
         out dx,al                          ;LBA地址15~8

         inc dx                             ;0x1f5
         shr eax,cl
         out dx,al                          ;LBA地址23~16

         inc dx                             ;0x1f6
         shr eax,cl
         or al,0xe0                         ;第一硬盘  LBA地址27~24
         out dx,al

         inc dx                             ;0x1f7
         mov al,0x20                        ;读命令
         out dx,al

  .waits:
         in al,dx
         and al,0x88
         cmp al,0x08
         jnz .waits                         ;不忙，且硬盘已准备好数据传输 

         mov ecx,256                        ;总共要读取的字数
         mov dx,0x1f0
  .readw:
         in ax,dx
         mov [ebx],ax
         add ebx,2
         loop .readw

         pop edx
         pop ecx
         pop eax
      
         retf                               ;段间返回 

;================================================================================
;详见P244
put_hex_dword:                              ;在当前光标处以十六进制形式显示
                                            ;一个双字并推进光标 
                                            ;输入：EDX=要转换并显示的数字
                                            ;输出：无
         pushad                             ;PUSHAD指令压入32位寄存器，使他们按照EDI,ESI,EBP,ESP,EBX,EDX,ECX,最后是EAX的顺序出现在堆栈中。
         push ds
      
         mov ax,core_data_seg_sel           ;切换到核心数据段 
         mov ds,ax
      
         mov ebx,bin_hex                    ;指向核心数据段内的转换表
         mov ecx,8                          ;32/4 每次处理4位
  .xlt:    
         rol edx,4                          ;循环左移4次
         mov eax,edx
         and eax,0x0000000f                 ;从高到底每次只保留4位，al中
         xlat                               ;处理器查表指令，ebx为表入口，al表索引，返回查询值到al
      
         push ecx
         mov cl,al                           
         call put_char
         pop ecx
       
         loop .xlt
      
         pop ds
         popad
         retf
      
;-------------------------------------------------------------------------------
allocate_memory:                            ;分配内存
                                            ;输入：ECX=希望分配的字节数
                                            ;输出：ECX=起始线性地址 
         push ds
         push eax
         push ebx
      
         mov eax,core_data_seg_sel          ;切换到数据段
         mov ds,eax
      
         mov eax,[ram_alloc]                ;初始为0x00100000
         add eax,ecx                        ;计算下一次分配时的起始地址
      
         ;这里应当有检测可用内存数量的指令
          
         mov ecx,[ram_alloc]                ;返回分配的起始地址

         mov ebx,eax
         and ebx,0xfffffffc
         add ebx,4                          ;强制对齐 
         test eax,0x00000003                ;下次分配的起始地址最好是4字节对齐
         cmovnz eax,ebx                     ;如果没有对齐，则强制对齐
		 ;以上为强制4B对齐
         mov [ram_alloc],eax                ;记录下次分配内存的起始地址
                                            ;cmovcc指令可以避免控制转移 
         pop ebx
         pop eax
         pop ds

         retf

;-------------------------------------------------------------------------------
set_up_gdt_descriptor:                      ;在GDT内安装一个新的描述符
                                            ;输入：EDX:EAX=描述符 
                                            ;输出：CX=描述符的选择子
         push eax
         push ebx
         push edx
      
         push ds
         push es
      
         mov ebx,core_data_seg_sel          ;切换到核心数据段
         mov ds,ebx

         sgdt [pgdt]                        ;读取GDTR到内存pgdt处,pgdt核心数据段定义的6字节

         mov ebx,mem_0_4_gb_seg_sel
         mov es,ebx                         ;es 0-4GB的段

         movzx ebx,word [pgdt]              ;GDT界限 无符号扩展并传送
         inc bx                             ;GDT界限+1就是GDT总字节数，也是下一个描述符偏移p236 
         add ebx,[pgdt+2]                   ;下一个描述符的物理地址,偏移+基址 
      
         mov [es:ebx],eax                   ;装载新的GDT
         mov [es:ebx+4],edx
      
         add word [pgdt],8                  ;增加一个描述符的大小 size+=8  
      
         lgdt [pgdt]                        ;对GDT的更改生效 
       
         mov ax,[pgdt]                      ;得到GDT界限值
         xor dx,dx
         mov bx,8
         div bx                             ;除以8，去掉余数
         mov cx,ax                          
         shl cx,3                           ;将索引号移到正确位置,刚开始3位不是索引 

         pop es
         pop ds

         pop edx】
		 
         pop ebx
         pop eax
      
         retf 
;-------------------------------------------------------------------------------
make_seg_descriptor:                        ;构造描述符
                                            ;输入：EAX=线性基地址
                                            ;      EBX=段界限
                                            ;      ECX=属性。各属性位都在原始
                                            ;          位置，无关的位清零 
                                            ;返回：EDX:EAX=描述符
         mov edx,eax
         shl eax,16
         or ax,bx                           ;描述符前32位(EAX)构造完毕

         and edx,0xffff0000                 ;清除基地址中无关的位
         rol edx,8
         bswap edx                          ;装配基址的31~24和23~16  (80486+)

         xor bx,bx
         or edx,ebx                         ;装配段界限的高4位

         or edx,ecx                         ;装配属性

         retf

;===============================================================================
SECTION core_data vstart=0                  ;系统核心的数据段
;-------------------------------------------------------------------------------
         pgdt             dw  0             ;用于设置和修改GDT 
                          dd  0

         ram_alloc        dd  0x00100000    ;下次分配内存时的起始地址

         ;符号地址检索表
         salt:
         salt_1           db  '@PrintString'
                     times 256-($-salt_1) db 0
                          dd  put_string         ;函数入口
                          dw  sys_routine_seg_sel;段选择子

         salt_2           db  '@ReadDiskData'
                     times 256-($-salt_2) db 0
                          dd  read_hard_disk_0
                          dw  sys_routine_seg_sel

         salt_3           db  '@PrintDwordAsHexString'
                     times 256-($-salt_3) db 0
                          dd  put_hex_dword
                          dw  sys_routine_seg_sel

         salt_4           db  '@TerminateProgram'
                     times 256-($-salt_4) db 0
                          dd  return_point
                          dw  core_code_seg_sel

         salt_item_len   equ $-salt_4
         salt_items      equ ($-salt)/salt_item_len;函数个数

         message_1        db  '  If you seen this message,that means we '
                          db  'are now in protect mode,and the system '
                          db  'core is loaded,and the video display '
                          db  'routine works perfectly.',0x0d,0x0a,0

         message_5        db  '  Loading user program...',0
         
         do_status        db  'Done.',0x0d,0x0a,0
         
         message_6        db  0x0d,0x0a,0x0d,0x0a,0x0d,0x0a
                          db  '  User program terminated,control returned.',0

         bin_hex          db '0123456789ABCDEF'
                                            ;put_hex_dword子过程用的查找表 
         core_buf   times 2048 db 0         ;内核用的缓冲区

         esp_pointer      dd 0              ;内核用来临时保存自己的栈指针     
         
		 ;CPU信息
         cpu_brnd0        db 0x0d,0x0a,'  ',0
         cpu_brand  times 52 db 0
         cpu_brnd1        db 0x0d,0x0a,0x0d,0x0a,0

;===============================================================================
SECTION core_code vstart=0
;-------------------------------------------------------------------------------
load_relocate_program:                      ;加载并重定位用户程序
                                            ;输入：ESI=起始逻辑扇区号
                                            ;返回：AX=指向用户程序头部的选择子 
         push ebx
         push ecx
         push edx
         push esi
         push edi
      
         push ds
         push es
      
         mov eax,core_data_seg_sel
         mov ds,eax                         ;切换DS到内核数据段
       
         mov eax,esi                        ;读取程序头部数据 
         mov ebx,core_buf                        
         call sys_routine_seg_sel:read_hard_disk_0 ;先读取一个扇区存到内核缓冲区

         ;以下判断整个程序有多大
         mov eax,[core_buf]                 ;程序尺寸，用户程序头部4字节
         mov ebx,eax
         and ebx,0xfffffe00                 ;使之512字节对齐（能被512整除的数， 
         add ebx,512                        ;低9位都为0 
         test eax,0x000001ff                ;程序的大小正好是512的倍数吗? 
         cmovnz eax,ebx                     ;不是。使用凑整的结果 
      
         mov ecx,eax                        ;实际需要申请的内存数量
         call sys_routine_seg_sel:allocate_memory
         mov ebx,ecx                        ;ebx -> 申请到的内存首地址
         push ebx                           ;保存该首地址-----用户程序真正加载到此处
         xor edx,edx
         mov ecx,512
         div ecx
         mov ecx,eax                        ;总扇区数 
      
         mov eax,mem_0_4_gb_seg_sel         ;切换DS到0-4GB的段
         mov ds,eax

         mov eax,esi                        ;起始扇区号 
  .b1:
         call sys_routine_seg_sel:read_hard_disk_0
         inc eax
         loop .b1                           ;循环读，直到读完整个用户程序

         ;建立用户程序头部段描述符
         pop edi                            ;恢复程序装载的首地址 
         mov eax,edi                        ;程序头部起始线性地址
         mov ebx,[edi+0x04]                 ;用户程序头部长度
         dec ebx                            ;段界限（长度-1） 
         mov ecx,0x00409200                 ;字节粒度的数据段描述符
         call sys_routine_seg_sel:make_seg_descriptor
         call sys_routine_seg_sel:set_up_gdt_descriptor
         mov [edi+0x04],cx                  ;把选择子写回0x04偏移处

         ;建立程序代码段描述符
         mov eax,edi
         add eax,[edi+0x14]                 ;代码起始线性地址
         mov ebx,[edi+0x18]                 ;段长度
         dec ebx                            ;段界限
         mov ecx,0x00409800                 ;字节粒度的代码段描述符
         call sys_routine_seg_sel:make_seg_descriptor
         call sys_routine_seg_sel:set_up_gdt_descriptor
         mov [edi+0x14],cx

         ;建立程序数据段描述符
         mov eax,edi
         add eax,[edi+0x1c]                 ;数据段起始线性地址
         mov ebx,[edi+0x20]                 ;段长度
         dec ebx                            ;段界限
         mov ecx,0x00409200                 ;字节粒度的数据段描述符
         call sys_routine_seg_sel:make_seg_descriptor
         call sys_routine_seg_sel:set_up_gdt_descriptor
         mov [edi+0x1c],cx

         ;建立程序堆栈段描述符
         mov ecx,[edi+0x0c]                 ;4KB的倍率，获取建议堆栈大小 
         mov ebx,0x000fffff
         sub ebx,ecx                        ;得到段界限0xfffff-倍率（此处1倍4KB）
		                                    ;相当于0xffff ffff - 0x1000(B为单位)
         mov eax,4096                        
         mul dword [edi+0x0c]               ;倍率乘以4K得到需要栈的大小         
         mov ecx,eax                        ;准备为堆栈分配内存 
         call sys_routine_seg_sel:allocate_memory
         add eax,ecx                        ;得到堆栈的高端物理地址(低端基址+段界限) 
         mov ecx,0x00c09600                 ;4KB粒度的堆栈段描述符
         call sys_routine_seg_sel:make_seg_descriptor
         call sys_routine_seg_sel:set_up_gdt_descriptor
         mov [edi+0x08],cx

         ;重定位SALT（符号地址检索表）内核根据用户程序SALT的符号名回填入口地址
         mov eax,[edi+0x04]
         mov es,eax                         ;es -> 用户程序头部;定位到用户程序头部读取U-SALT
		 
         mov eax,core_data_seg_sel          ;定位到内核数据段读取C-SALT
         mov ds,eax
      
         cld
		
		;以下将用户SALT信息压栈
         mov ecx,[es:0x24]                  ;用户程序的SALT条目数,循环次数
         mov edi,0x28                       ;用户程序内的SALT位于头部内0x28处
  .b2: 
         push ecx
         push edi
		
		;内循环(与C-SALT的每一个条目比较)开始比较
         mov ecx,salt_items                 ;读取C-SALT个数
         mov esi,salt                       ;获取C-SALT地址
  .b3:
         push edi
         push esi
         push ecx                           ;寄存器备份
		
         mov ecx,64                         ;检索表中，每条目至多的比较次数256/4 
         repe cmpsd                         ;每次比较4字节 repe(repz)相等(ZF=0)则重复
		 ;比较源(C-SALT)[DS:ESI],目标[ES:EDI]
         jnz .b4                            ;不匹配(ZF!=0)则跳转.b4
		 	                                ;若匹配,上面cmpsd比较过程中EDI,ESI已经自动加到256处(字符串尾部)
		 mov eax,[esi]                      ;esi=256,eax保存其后4字节函数入口偏移地址 
		 mov [es:edi-256],eax               ;将对应U-SALT头部4字节改写成函数入口偏移地址(edi-256回到头部)
         mov ax,[esi+4]                     ;ax保存最后2字节的段选择子(256+4 ~ 262字节)
         mov [es:edi-252],ax                ;将段选择子保存到头部5、6字节中(256-252=4,下一字节从5字节开始)
  .b4:
      
         pop ecx							;恢复
         pop esi
         add esi,salt_item_len              ;指向内核下一个SALT表项
         pop edi                            ;从头比较 
         loop .b3
         ;内循环比较结束
	  
	  
         pop edi
         add edi,256                       	;指向用户下一个SALT表项
         pop ecx
         loop .b2
		;外循环结束，所有比较结束
         mov ax,[es:0x04]                   ;返回用户头部选择子，上面重定位过程中已经把头部选择子写入0x04偏移中

         pop es                             ;恢复到调用此过程前的es段 
         pop ds                             ;恢复到调用此过程前的ds段
      
         pop edi
         pop esi
         pop edx
         pop ecx
         pop ebx
      
         ret
      
;-------------------------------------------------------------------------------
start:
         mov ecx,core_data_seg_sel           ;使ds指向核心数据段 
         mov ds,ecx

         mov ebx,message_1
         call sys_routine_seg_sel:put_string
                                         
         ;显示处理器品牌信息 
         mov eax,0x80000002
         cpuid
         mov [cpu_brand + 0x00],eax
         mov [cpu_brand + 0x04],ebx
         mov [cpu_brand + 0x08],ecx
         mov [cpu_brand + 0x0c],edx
      
         mov eax,0x80000003
         cpuid
         mov [cpu_brand + 0x10],eax
         mov [cpu_brand + 0x14],ebx
         mov [cpu_brand + 0x18],ecx
         mov [cpu_brand + 0x1c],edx

         mov eax,0x80000004
         cpuid
         mov [cpu_brand + 0x20],eax
         mov [cpu_brand + 0x24],ebx
         mov [cpu_brand + 0x28],ecx
         mov [cpu_brand + 0x2c],edx

         mov ebx,cpu_brnd0
         call sys_routine_seg_sel:put_string
         mov ebx,cpu_brand
         call sys_routine_seg_sel:put_string
         mov ebx,cpu_brnd1
         call sys_routine_seg_sel:put_string

         mov ebx,message_5
         call sys_routine_seg_sel:put_string
         mov esi,50                          ;用户程序位于逻辑50扇区 
         call load_relocate_program
      
         mov ebx,do_status
         call sys_routine_seg_sel:put_string
      
         mov [esp_pointer],esp               ;临时保存堆栈指针
       
         mov ds,ax                           ;AX程序重定位返回的头部选择子
      
         jmp far [0x10]                      ;控制权交给用户程序（入口点）
                                             ;相当于DS:0x10,0x10处是用户程序入口点

return_point:                                ;用户程序返回点
         mov eax,core_data_seg_sel           ;使ds指向核心数据段
         mov ds,eax

         mov eax,core_stack_seg_sel          ;切换回内核自己的堆栈
         mov ss,eax 
         mov esp,[esp_pointer]

         mov ebx,message_6
         call sys_routine_seg_sel:put_string

         ;这里可以放置清除用户程序各种描述符的指令
         ;也可以加载并启动其它程序
       
         hlt
            
;===============================================================================
SECTION core_trail
;-------------------------------------------------------------------------------
core_end: