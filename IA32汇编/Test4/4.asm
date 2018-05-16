;===============================================================================
SECTION header vstart=0                     ;�����û�����ͷ���� 
    program_length  dd program_end          ;�����ܳ���[0x00];dd32bit
    
    ;�û�������ڵ�
    code_entry      dw start                ;ƫ�Ƶ�ַ[0x04]
                    dd section.code.start   ;�ε�ַ[0x06] 
    
    realloc_tbl_len dw (header_end-realloc_begin)/4
                                            ;���ض�λ�������[0x0a]
    
    realloc_begin:
    ;���ض�λ��           
    code_segment    dd section.code.start   ;[0x0c]
    data_segment    dd section.data.start   ;[0x14]
    stack_segment   dd section.stack.start  ;[0x1c]
    
header_end:                
    
;===============================================================================
SECTION code align=16 vstart=0           ;�������Σ�16�ֽڶ���
new_int_0x70:
      push ax
      push bx
      push cx
      push dx
      push es
      
      xor ax,ax 
      ;��ȡ���� 
      mov al,0x06
      out 0x70,al ;CMOS RAM 0x06ƫ��
      in al,0x71
      push ax
      
      ;��ȡ��
      mov al,0x00
      out 0x70,al
      in al,0x71                       
      push ax
      
      ;����� 
      mov al,0x02
      out 0x70,al
      in al,0x71               
      push ax

      ;����ʱ 
      mov al,0x04
      out 0x70,al
      in al,0x71                     
      push ax
           
      ;��ȡ��
      mov al,0x07
      out 0x70,al
      in al,0x71
      push ax 

      ;��ȡ��
      mov al,0x08
      out 0x70,al
      in al,0x71
      push ax 
          
      ;��ȡ��
      mov al,0x09
      out 0x70,al
      in al,0x71
      push ax
;=============================================================================; 
      mov al,0x0c                        ;�Ĵ���C������
      out 0x70,al
      in al,0x71                         ;��һ��RTC�ļĴ���C������ֻ����һ���ж�
      
      mov ax,0xb800
      mov es,ax
      
      ;������ʾ"Now,the time is :20" 
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
      mov [es:bx+2],al                   ;��ʾ��λ��� 
      mov byte [es:bx+4],'-'              ;��ʾ�ָ���'-' 

      pop ax
      call bcd_to_ascii
      mov [es:bx+6],ah
      mov [es:bx+8],al                   ;��ʾ��λ�·�
      mov byte [es:bx+10],'-'                  ;��ʾ�ָ���'-'

      pop ax
      call bcd_to_ascii
      mov [es:bx+12],ah
      mov [es:bx+14],al                  ;��ʾ��λ����
;=============================================================================;    
      pop ax
      call bcd_to_ascii
      mov [es:bx+18],ah
      mov [es:bx+20],al                   ;��ʾ��λСʱ   
      mov byte [es:bx+22],':'                  ;��ʾ�ָ���':'
      not byte[es:bx+23]
      
      pop ax     
      call bcd_to_ascii
      mov [es:bx+24],ah
      mov [es:bx+26],al                   ;��ʾ��λ����
      mov byte [es:bx+28],':'                  ;��ʾ�ָ���':'
      not byte[es:bx+29]
      
      pop ax
      call bcd_to_ascii
      mov [es:bx+30],ah
      mov [es:bx+32],al                   ;��ʾ��λ��
;=============================================================================;      
      pop ax                              ;��ʾ���� 
      mov ah,9
      mul ah
      add ax,week_msg
      add bx,36                          ;�Դ�ƫ�� 
      push si
      mov si,ax
      push cx
      mov cx,9                            ;ÿ�����ʹ淶��Ϊ9���ַ� 
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
       
      mov al,0x20                        ;�жϽ�������EOI 
      out 0xa0,al                        ;���Ƭ���� 
      out 0x20,al                        ;����Ƭ���� 

      pop es
      pop dx
      pop cx
      pop bx
      pop ax

      iret

;-------------------------------------------------------------------------------
bcd_to_ascii:                            ;BCD��תASCII
                                         ;���룺AL=bcd��
                                         ;�����AX=ascii
      mov ah,al                          ;�ֲ���������� 
      and al,0x0f                        ;��������4λ����λ�� 
      add al,0x30                        ;ת����ASCII(+'0') 

      shr ah,4                           ;�߼�����4λ(ʮλ���ڸ���λ��),���ǵ�ԭ������λ����λ���� 
      and ah,0x0f                        ;����λ���� 
      add ah,0x30

      ret

;-------------------------------------------------------------------------------
start:
      mov ax,[stack_segment]
      mov ss,ax                          ;���ö�ջ�ζμĴ���
      mov sp,ss_pointer				     ;set stack point [sp]
      mov ax,[data_segment]
      mov ds,ax                          ;set ds
      
      mov bx,init_msg                    ;��ʾ��ʼ��Ϣ init_msg:'starting...',0x0d,0x0a,0
      call put_string

      mov bx,inst_msg                    ;��ʾ��װ��Ϣ 
      call put_string
      
      mov al,0x70						 ;��Ƭ�жϺŴ�0x70��ʼ,�ҵ�һ�����ž���ʵʱʱ���ж�
      mov bl,4							 ;һ���ж�����ռ4�ֽ�
      mul bl                             ;����0x70���ж���IVT(�ж�������)�е�ƫ��
      mov bx,ax                          ;0x0000:bx��Ӧ�����ַ,��ľ���0x70���жϵ���ڵ�ַ

      cli                                ;��ֹ�Ķ��ڼ䷢���µ�0x70���ж�(���ж�)

      push es							 ;backup es
      mov ax,0x0000
      mov es,ax					
      mov word [es:bx],new_int_0x70      ;����0x70���жϵ� �жϴ������ ƫ�Ƶ�ַ��
                                          
      mov word [es:bx+2],cs              ;����0x70���жϵ� �жϴ������ ��(��)��ַ
      pop es
      ;�ж��������������
	  
	  ;��������RTC����״̬
      mov al,0x0b                        ;RTC�Ĵ���B
      out 0x70,al			
	  
      mov al,0x12                        ;���üĴ���{��ֹ�������жϣ��������жϣ����Ÿ� 
      out 0x71,al                        ;�½������жϣ�BCD�룬24Сʱ��(0x12=0001 0010B)}
	  ;����RTC�ж�
      mov al,0x0c
      out 0x70,al
      in al,0x71                         ;��RTC�Ĵ���C����λδ�����ж�״̬��C�Ĵ������㣩
	  
     ;�޸Ĵ�Ƭ�ж����μĴ�����λ0Ϊ0��ʹ֮����RTC�ж�(Ĭ�ϲ�����)
      in al,0xa1                         ;��8259��Ƭ��IMR�Ĵ��� 0xa1 IMR�˿�
      and al,0xfe                        ;���bit 0(��λ����RTC)
      out 0xa1,al                        ;д�ش˼Ĵ��� 

      sti                                ;���¿����ж� IF=1 

	  ;-----------------------------------------
      mov bx,done_msg                    ;��ʾ��װ�����Ϣ 
      call put_string

      mov bx,tips_msg                    ;��ʾ��ʾ��Ϣ
      call put_string

 .idle:
      hlt                                ;ʹCPU����͹���״̬��ֱ�����жϻ��� 
      jmp .idle

;-------------------------------------------------------------------------------
put_string:                              ;��ʾ��(0��β)��
                                         ;���룺DS:BX=����ַ
         mov cl,[bx]                     ;bx=init_msg �׵�ַ
         or cl,cl                        ;cl=0 ? //�����Ƿ��ַ���β��
         jz .exit                        ;�ǵģ����������� 
         call put_char		
         inc bx                          ;��һ���ַ� 
         jmp put_string

   .exit:
         ret

;-------------------------------------------------------------------------------
put_char:                                ;��ʾһ���ַ�
                                         ;���룺�ַ�����cl��
         push ax
         push bx
         push cx
         push dx
         push ds
         push es						 ;�Ĵ�������

         ;����ȡ��ǰ���λ��			 ;���P142����
         mov dx,0x3d4                    ;�Կ������洢���˿�,�Կ�Reg�ܶ࣬ͨ�������Ĵ�����ӷ���
         mov al,0x0e
         out dx,al						 ;��0x3d4�˿ڷ�������0x0e(ָ���Կ���14�żĴ���)
         mov dx,0x3d5					 ;��0x3d5�˿ڶ�ȡ����
         in al,dx                        ;��8λ��in����Ŀ�Ĳ�����������AX��AL�� 
         mov ah,al

         mov dx,0x3d4
         mov al,0x0f					 ;ָ���Կ���15�żĴ�����14 h8,15 l8��
         out dx,al
         mov dx,0x3d5
         in al,dx                        ;��8λ 
         mov bx,ax                       ;BX=������λ�õ�16λ��

         cmp cl,0x0d                     ;�س�����
         jnz .put_0a                     ;���ǡ������ǲ��ǻ��е��ַ�
		 ;���¼���س�Ŀ��λ��(����)
         mov ax,bx                       ;��ǰ���λ����������
         mov bl,80                       
         div bl							 ;����80�õ��к�al�У��̣�
         mul bl							 ;alx80���ǵ�ǰ���׵�λ��(����AX��)
         mov bx,ax						 ;����BX����
         jmp .set_cursor

 .put_0a:
         cmp cl,0x0a                     ;���з���
         jnz .put_other                  ;���ǣ��Ǿ�������ʾ�ַ� 
		 ;���»���
         add bx,80						 ;���λ��+80������һ�и�λ��
         jmp .roll_screen

 .put_other:                             ;������ʾ�ַ�
         mov ax,0xb800
         mov es,ax
         shl bx,1                        ;���λ�ó���2���ǵ�ǰ����ʾ�ַ����Դ�ƫ��
         mov [es:bx],cl                  ;ʹ��Ĭ����ɫ,ÿ��ͨ��x2����ƫ�ƣ���ɫλ���ܻ�ճ���

         ;���½����λ���ƽ�һ���ַ�
         shr bx,1                        ;��ԭ���λ��
         add bx,1				

 .roll_screen:
         cmp bx,2000                     ;��곬����Ļ������
         jl .set_cursor
		 ;����>=2000�ַ�����ʼ����
         mov ax,0xb800
         mov ds,ax
         mov es,ax
         cld                             ;�����־λDF��0ָ��,Ϊ��movsw�����ƶ���l->h��
		 ;���µĺ����ǽ��Դ����ݣ���0xb800:160��ַ��ʼ�Ժ��1920*2���ֽ���ǰ�ƶ�160���ֽ�
		 ;����������24�����ݶ������ƶ�һ�У�
         mov si,0xa0                     ;ָ���ƶ���Դ����λ���Դ�ƫ��160λ��
         mov di,0x00					 ;ָ���ƶ���Ŀ�ĵ�ַλ�Դ�ƫ��0λ��
         mov cx,1920					 ;�ƶ�����1920
         rep movsw						 ;ÿ���ƶ�һ���֣��ظ�1920��
         mov bx,3840                     ;�����Ļ���һ��;bxָ��25�е�һ���ַ���,�Ӵ˴���ʼ����ַ�
         mov cx,80                       ;����ѭ������
 .cls:
         mov word[es:bx],0x0720          ;�հ��ַ����
         add bx,2
         loop .cls

         mov bx,1920					 ;��������û�25������
	
         ;����bxֻ���߼���꣬������ʵ���ù��
 .set_cursor:
         mov dx,0x3d4					 ;0x3d4����
         mov al,0x0e
         out dx,al
         mov dx,0x3d5                    ;0x3d5��д
         mov al,bh
         out dx,al                       ;д���8λ
		 
         mov dx,0x3d4
         mov al,0x0f
         out dx,al
         mov dx,0x3d5
         mov al,bl
         out dx,al                       ;д���8λ

         pop es
         pop ds
         pop dx
         pop cx
         pop bx
         pop ax

         ret

;===============================================================================
SECTION data align=16 vstart=0

    init_msg       db 'Starting...',0x0d,0x0a,0 ;0x0d = �س�,0x0a = ���� 
												;(�س����ǻص�����,�����ǻ�����һ��,��Դ����ʽ���ֻ�)
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