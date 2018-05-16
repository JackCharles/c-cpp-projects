jmp near start

string: 
      db 'zhongjie21141122:'        ;SUM(ASCII)=862 

start:                              ;设置显存基址 
      mov ax,0xb800
      mov es,ax 
	  
      mov ax,0x07c0                 ; 设置数据基址 
      mov ds,ax                     ;data segement
;------------------------------------------------------------------------------;      
      mov cx,(start-string)
      mov si,string
      xor di,di
ShowStr:
      mov al,[si]                   ;设置颜色亮白 
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
      mov byte bl,[si]              ;读取一个字节 
      add ax,bx 
      inc si
      loop adda                     ;相加结果在ax中 
;------------------------------------------------------------------------------;
      mov cx,3			            ;除3次
      mov bx,10
divi:
      xor dx,dx
      div bx
      add dl,'0'		          	;+48获得其ASCII码
      mov dh,0x0c                   ;浅红 
      push dx 
      loop divi 
;------------------------------------------------------------------------------;      
      mov si,(start-string+1)*2	    ;显存偏移
      mov cx,3						
 show:
      pop ax		                ;弹栈
      mov word [es:si],ax	        ;送入显存
      add si,2
      loop show
;------------------------------------------------------------------------------;      
      jmp near $ 
      
times 510-($-$$) db 0
dw 0xaa55