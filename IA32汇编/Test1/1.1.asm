jmp near start

string: 
      db 'zhongjie21141122:'        ;SUM(ASCII)=862 

start:                              ;�����Դ��ַ 
      mov ax,0xb800
      mov es,ax 
	  
      mov ax,0x07c0                 ; �������ݻ�ַ 
      mov ds,ax                     ;data segement
;------------------------------------------------------------------------------;      
      mov cx,(start-string)
      mov si,string
      xor di,di
ShowStr:
      mov al,[si]                   ;������ɫ���� 
      mov ah,0x0f
      mov [es:di],ax
      inc si
      add di,2
      loop ShowStr
;------------------------------------------------------------------------------;                
      mov cx,8
      xor ax,ax
      xor bh,bh
      mov si,string                  
adda:
      mov byte bl,[si]              ;��ȡһ���ֽ� 
      add ax,bx 
      inc si
      loop adda                     ;��ӽ����ax�� 
;------------------------------------------------------------------------------;
      mov cx,3			            ;��3��
      mov bx,10
divi:
      xor dx,dx
      div bx
      add dl,'0'		          	;+48�����ASCII��
      mov dh,0x0c                   ;ǳ�� 
      push dx 
      loop divi 
;------------------------------------------------------------------------------;      
      mov si,(start-string+1)*2	    ;�Դ�ƫ��
      mov cx,3						
 show:
      pop ax		                ;��ջ
      mov word [es:si],ax	        ;�����Դ�
      add si,2
      loop show
;------------------------------------------------------------------------------;      
      jmp near $ 
      
times 510-($-$$) db 0
dw 0xaa55