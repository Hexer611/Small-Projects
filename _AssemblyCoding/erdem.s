;ld.exe uses .a static libraries
;nasm and golink is not compatible if using .lib files but .dll files are fine
;
; rax return value register
; rcx is first argument
; rdx is second argument
; r8 is third argument
; r9 is fourth argument
; After the first three they are stored in stack
; Interesting stuff :D


; Parameter type	                        fifth and higher	fourth	third	second	leftmost
; floating-point	                        stack	                XMM3	XMM2	XMM1	XMM0
; integer	                                stack	                R9      R8	RDX	RCX
; Aggregates (8, 16, 32, or 64 bits) and __m64	stack	                R9	R8	RDX	RCX
; Other aggregates, as pointers	                stack	                R9	R8	RDX	RCX
; __m128, as a pointer	                        stack	                R9	R8	RDX	RCX

global erdem_strlen, erdem_strcpy, erdem_strcmp
section .text

erdem_strlen:
    mov rax, 0                  ; init rax as 0, not sure if necessary
erdem_loop:
    movzx rdx, byte [rcx]       ; load first char from the pointer, hopefully it exists
    cmp rdx, 0                  ; compare if the char we read is the end of the string
    je .returnfunc               ; je means the previous comparison is equal i hope. jg is greater, jl is less??
    inc rcx                     ; if we didn't find the last char we increase the pointer to next char
    inc rax                     ; if we didn't find the last char we increase the rax value by one which is the char count
    jmp erdem_loop              ; go back to counting characters :D
.returnfunc:                    ; finish him
    ret

erdem_strcpy:
    mov rdi, rcx
    mov rsi, rdx
erdem_strcpy_main:
    mov al, [rsi]
    mov byte [rdi], al
    cmp al, 0                  ; compare if the char we read is the end of the string
    je .ret_strcpy

    inc rdi
    inc rsi
    jmp erdem_strcpy_main
.ret_strcpy:                          ; finish him
    ret

erdem_strcmp:
    mov rdi, rcx
    mov rsi, rdx
erdem_strcmp_main:
    mov al, [rsi]
    mov bl, [rdi]
    cmp al, bl                  ; compare if the char we read is the end of the string
    ja .ret_strcmp_g
    jb .ret_strcmp_l
    cmp al, 0                  ; compare if the char we read is the end of the string
    je .ret_strcmp_e

    inc rdi
    inc rsi
    jmp erdem_strcmp_main
.ret_strcmp_g:                          ; finish him
    mov rax, -1
    ret
.ret_strcmp_l:                          ; finish him
    mov rax, 1
    ret
.ret_strcmp_e:                          ; finish him
    mov rax, 0
    ret
