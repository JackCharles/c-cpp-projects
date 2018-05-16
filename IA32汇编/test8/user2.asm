         ;�����嵥13-3
         ;�ļ�����c13.asm
         ;�ļ�˵�����û����� 
         ;�������ڣ�2011-10-30 15:19   
         
;===============================================================================
SECTION header vstart=0

         program_length   dd program_end          ;�����ܳ���#0x00
         
         head_len         dd header_end           ;����ͷ���ĳ���#0x04���ض�λ��洢ͷ����ѡ����

         stack_seg        dd 0                    ;���ڽ��ն�ջ��ѡ����#0x08,�ض�λ��洢��ջ��ѡ����
         stack_len        dd 1                    ;������Ķ�ջ��С#0x0c
                                                  ;��4KBΪ��λ
                                                  
         prgentry         dd start                ;�������#0x10 
         code_seg         dd section.code.start   ;�����λ��#0x14���ض�λ��洢�����ѡ����
         code_len         dd code_end             ;����γ���#0x18

         data_seg         dd section.data.start   ;���ݶ�λ��#0x1c���ض�λ��洢���ݶ�ѡ����
         data_len         dd data_end             ;���ݶγ���#0x20
             
;-------------------------------------------------------------------------------
         ;���ŵ�ַ������
         salt_items       dd (header_end-salt)/256 ;#0x24
         
         salt:                                     ;#0x28
         PrintString      db  '@PrintString'       ;�ض�λ��ʼ6�ֽڴ洢����ƫ��(4B)�͹������̶�ѡ����(2B)
                     times 256-($-PrintString) db 0
                     
         TerminateProgram db  '@TerminateProgram'
                     times 256-($-TerminateProgram) db 0
                     
         ReadDiskData     db  '@ReadDiskData'
                     times 256-($-ReadDiskData) db 0
                 
header_end:

;===============================================================================
SECTION data vstart=0    
         message	 db 0x0d,0x0a,0x0d,0x0a,'  15!= ',0
	 buffer times 20 db 0
data_end:

;===============================================================================
      [bits 32]
;===============================================================================
SECTION code vstart=0
start:
         mov eax,ds
         mov fs,eax               ;fs<-ͷ��ѡ����
     
         mov eax,[stack_seg]
         mov ss,eax               ;ss<-ջ��
         mov esp,0
     
         mov eax,[data_seg]
         mov ds,eax               ;ds<-���ݶ�
;================================================================================        
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

         mov edi,12                      ;�����������			    
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
         mov byte [buffer+edi],cl
         dec edi
         cmp edi,0
         jge divi
         
         mov ebx,message
         call far [fs:PrintString]          ;32λcall far[addr]�Ǵ�addr��ȡ��һ��32λƫ�ƺ�16λ��ѡ����
     
         mov ebx,buffer 
         call far [fs:PrintString]           
     
         call far [fs:TerminateProgram]       ;������Ȩ���ص�ϵͳ 
      
code_end:

;===============================================================================
SECTION trail
;-------------------------------------------------------------------------------
program_end: