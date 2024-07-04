.code

extrn mechanic2ret: QWORD
mechanic2hk proc
    mov eax, [ rax + 20 ]
    jmp mechanic2ret
mechanic2hk endp
end