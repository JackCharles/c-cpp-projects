;===============================================================================
SECTION header vstart=0                     ;定义用户程序头部段 
    program_length  dd program_end          ;程序总长度[0x00];dd32bit
    
    ;用户程序入口点
    code_entry      dw start                ;偏移地址[0x04]
                    dd section.code.start   ;段地址[0x06] 
    
    realloc_tbl_len dw (header_end-realloc_begin)/4
                                            ;段重定位表项个数[0x0a]
    
    realloc_begin:
    ;段重定位表           
    code_segment    dd section.code.start   ;[0x0c]
    data_segment    dd section.data.start   ;[0x14]
    stack_segment   dd section.stack.start  ;[0x1c]
    
header_end:                
    
;===============================================================================
SECTION code align=16 vstart=0           ;定义代码段（16字节对齐
new_int_0x70:
      push ax
      push bx
      push cx
      push dx
      push es
      
      xor ax,ax 
      ;读取星期 
      mov al,0x06
      out 0x70,al ;CMOS RAM 0x06偏移
      in al,0x71
      push ax
      
      ;读取秒
      mov al,0x00
      out 0x70,al
      in al,0x71                       
      push ax
      
      ;读入分 
      mov al,0x02
      out 0x70,al
      in al,0x71               
      push ax

      ;读入时 
      mov al,0x04
      out 0x70,al
      in al,0x71                     
      push ax
           
      ;读取日
      mov al,0x07
      out 0x70,al
      in al,0x71
      push ax 

      ;读取月
      mov al,0x08
      out 0x70,al
      in al,0x71
      push ax 
          
      ;读取年
      mov al,0x09
      out 0x70,al
      in al,0x71
      push ax
;=============================================================================; 
      mov al,0x0c                        ;寄存器C的索引
      out 0x70,al
      in al,0x71                         ;读一下RTC的寄存器C，否则只发生一次中断
      
      mov ax,0xb800
      mov es,ax
      
      ;下面显示"Now,the time is :20" 
      mov bx,12*160 + 16*2
      push si
      push cx
      mov si,time_msg
      mov cx,(data_end-time_msg)
ShowMsg:
      mov al,[si]
      mov [es:bx],al
      inc si
      add bx,2
      loop ShowMsg 
      pop cx 
      pop si
      
;=============================================================================; 
      pop ax
      call bcd_to_ascii
      mov [es:bx],ah
      mov [es:bx+2],al                   ;显示两位年份 
      mov byte [es:bx+4],'-'              ;显示分隔符'-' 

      pop ax
      call bcd_to_ascii
      mov [es:bx+6],ah
      mov [es:bx+8],al                   ;显示两位月份
      mov byte [es:bx+10],'-'                  ;显示分隔符'-'

      pop ax
      call bcd_to_ascii
      mov [es:bx+12],ah
      mov [es:bx+14],al                  ;显示两位日期
;=============================================================================;    
      pop ax
      call bcd_to_ascii
      mov [es:bx+18],ah
      mov [es:bx+20],al                   ;显示两位小时   
      mov byte [es:bx+22],':'                  ;显示分隔符':'
      not byte[es:bx+23]
      
      pop ax     
      call bcd_to_ascii
      mov [es:bx+24],ah
      mov [es:bx+26],al                   ;显示两位分钟
      mov byte [es:bx+28],':'                  ;显示分隔符':'
      not byte[es:bx+29]
      
      pop ax
      call bcd_to_ascii
      mov [es:bx+30],ah
      mov [es:bx+32],al                   ;显示两位秒
;=============================================================================;      
      pop ax                              ;显示星期 
      mov ah,9
      mul ah
      add ax,week_msg
      add bx,36                          ;显存偏移 
      push si
      mov si,ax
      push cx
      mov cx,9                            ;每个单词规范化为9个字符 
ShowWeek:
      mov al,[si]
      mov ah,0x0a 
      mov [es:bx],ax
      inc si
      add bx,2
      loop ShowWeek
      pop cx
      pop si
;=============================================================================;
       
      mov al,0x20                        ;中断结束命令EOI 
      out 0xa0,al                        ;向从片发送 
      out 0x20,al                        ;向主片发送 

      pop es
      pop dx
      pop cx
      pop bx
      pop ax

      iret

;-------------------------------------------------------------------------------
bcd_to_ascii:                            ;BCD码转ASCII
                                         ;输入：AL=bcd码
                                         ;输出：AX=ascii
      mov ah,al                          ;分拆成两个数字 
      and al,0x0f                        ;仅保留低4位（个位） 
      add al,0x30                        ;转换成ASCII(+'0') 

      shr ah,4                           ;逻辑右移4位(十位数在高四位上),覆盖掉原来低四位（个位数） 
      and ah,0x0f                        ;高四位清零 
      add ah,0x30

      ret

;-------------------------------------------------------------------------------
start:
      mov ax,[stack_segment]
      mov ss,ax                          ;设置堆栈段段寄存器
      mov sp,ss_pointer				     ;set stack point [sp]
      mov ax,[data_segment]
      mov ds,ax                          ;set ds
      
      mov bx,init_msg                    ;显示初始信息 init_msg:'starting...',0x0d,0x0a,0
      call put_string

      mov bx,inst_msg                    ;显示安装信息 
      call put_string
      
      mov al,0x70						 ;从片中断号从0x70开始,且第一个引脚就是实时时钟中断
      mov bl,4							 ;一个中断向量占4字节
      mul bl                             ;计算0x70号中断在IVT(中断向量表)中的偏移
      mov bx,ax                          ;0x0000:bx对应物理地址,存的就是0x70号中断的入口地址

      cli                                ;防止改动期间发生新的0x70号中断(关中断)

      push es							 ;backup es
      mov ax,0x0000
      mov es,ax					
      mov word [es:bx],new_int_0x70      ;设置0x70号中断的 中断处理程序 偏移地址。
                                          
      mov word [es:bx+2],cs              ;设置0x70号中断的 中断处理程序 段(基)地址
      pop es
      ;中断向量表设置完成
	  
	  ;下面设置RTC工作状态
      mov al,0x0b                        ;RTC寄存器B
      out 0x70,al			
	  
      mov al,0x12                        ;设置寄存器{禁止周期性中断，关闹钟中断，开放更 
      out 0x71,al                        ;新结束后中断，BCD码，24小时制(0x12=0001 0010B)}
	  ;读入RTC中断
      mov al,0x0c
      out 0x70,al
      in al,0x71                         ;读RTC寄存器C，复位未决的中断状态（C寄存器清零）
	  
     ;修改从片中断屏蔽寄存器，位0为0，使之接受RTC中断(默认不接受)
      in al,0xa1                         ;读8259从片的IMR寄存器 0xa1 IMR端口
      and al,0xfe                        ;清除bit 0(此位连接RTC)
      out 0xa1,al                        ;写回此寄存器 

      sti                                ;重新开放中断 IF=1 

	  ;-----------------------------------------
      mov bx,done_msg                    ;显示安装完成信息 
      call put_string

      mov bx,tips_msg                    ;显示提示信息
      call put_string

 .idle:
      hlt                                ;使CPU进入低功耗状态，直到用中断唤醒 
      jmp .idle

;-------------------------------------------------------------------------------
put_string:                              ;显示串(0结尾)。
                                         ;输入：DS:BX=串地址
         mov cl,[bx]                     ;bx=init_msg 首地址
         or cl,cl                        ;cl=0 ? //测试是否到字符串尾部
         jz .exit                        ;是的，返回主程序 
         call put_char		
         inc bx                          ;下一个字符 
         jmp put_string

   .exit:
         ret

;-------------------------------------------------------------------------------
put_char:                                ;显示一个字符
                                         ;输入：字符放在cl中
         push ax
         push bx
         push cx
         push dx
         push ds
         push es						 ;寄存器备份

         ;以下取当前光标位置			 ;详见P142介绍
         mov dx,0x3d4                    ;显卡索引存储器端口,显卡Reg很多，通过索引寄存器间接访问
         mov al,0x0e
         out dx,al						 ;向0x3d4端口发送索引0x0e(指定显卡中14号寄存器)
         mov dx,0x3d5					 ;从0x3d5端口读取数据
         in al,dx                        ;高8位（in操作目的操作数必须是AX或AL） 
         mov ah,al

         mov dx,0x3d4
         mov al,0x0f					 ;指定显卡中15号寄存器（14 h8,15 l8）
         out dx,al
         mov dx,0x3d5
         in al,dx                        ;低8位 
         mov bx,ax                       ;BX=代表光标位置的16位数

         cmp cl,0x0d                     ;回车符？
         jnz .put_0a                     ;不是。看看是不是换行等字符
		 ;以下计算回车目标位置(行首)
         mov ax,bx                       ;当前光标位置做被除数
         mov bl,80                       
         div bl							 ;除以80得到行号al中（商）
         mul bl							 ;alx80就是当前行首的位置(存在AX中)
         mov bx,ax						 ;送入BX保存
         jmp .set_cursor

 .put_0a:
         cmp cl,0x0a                     ;换行符？
         jnz .put_other                  ;不是，那就正常显示字符 
		 ;以下换行
         add bx,80						 ;光标位置+80跳到下一行该位置
         jmp .roll_screen

 .put_other:                             ;正常显示字符
         mov ax,0xb800
         mov es,ax
         shl bx,1                        ;光标位置乘以2就是当前待显示字符的显存偏移
         mov [es:bx],cl                  ;使用默认颜色,每次通过x2计算偏移，颜色位置总会空出来

         ;以下将光标位置推进一个字符
         shr bx,1                        ;复原光标位置
         add bx,1				

 .roll_screen:
         cmp bx,2000                     ;光标超出屏幕？滚屏
         jl .set_cursor
		 ;以下>=2000字符，开始滚屏
         mov ax,0xb800
         mov ds,ax
         mov es,ax
         cld                             ;方向标志位DF清0指令,为了movsw正向移动（l->h）
		 ;以下的核心是将显存内容，从0xb800:160地址开始以后的1920*2个字节往前移动160个字节
		 ;（即将下面24行内容都往上移动一行）
         mov si,0xa0                     ;指定移动的源数据位于显存偏移160位置
         mov di,0x00					 ;指定移动的目的地址位显存偏移0位置
         mov cx,1920					 ;移动次数1920
         rep movsw						 ;每次移动一个字，重复1920次
         mov bx,3840                     ;清除屏幕最底一行;bx指向25行第一个字符处,从此处开始清空字符
         mov cx,80                       ;设置循环次数
 .cls:
         mov word[es:bx],0x0720          ;空白字符填充
         add bx,2
         loop .cls

         mov bx,1920					 ;光标重新置回25行行首
	
         ;以上bx只是逻辑光标，下面真实设置光标
 .set_cursor:
         mov dx,0x3d4					 ;0x3d4索引
         mov al,0x0e
         out dx,al
         mov dx,0x3d5                    ;0x3d5读写
         mov al,bh
         out dx,al                       ;写入高8位
		 
         mov dx,0x3d4
         mov al,0x0f
         out dx,al
         mov dx,0x3d5
         mov al,bl
         out dx,al                       ;写入低8位

         pop es
         pop ds
         pop dx
         pop cx
         pop bx
         pop ax

         ret

;===============================================================================
SECTION data align=16 vstart=0

    init_msg       db 'Starting...',0x0d,0x0a,0 ;0x0d = 回车,0x0a = 换行 
												;(回车就是回到行首,换行是换到下一行,来源于老式打字机)
    inst_msg       db 'Installing a new interrupt 70H...',0
    
    done_msg       db 'Done.',0x0d,0x0a,0

    tips_msg       db 'Clock is now working.',0
    
    week_msg       db 'Sunday   Monday   Tuesday  WednesdayThursday Friday   Saturday ' 
    
    time_msg       db 'Now,the time is: 20'
data_end:
                   
;===============================================================================
SECTION stack align=16 vstart=0
           
                 resb 256
ss_pointer:
 
;===============================================================================
SECTION program_trail
program_end: