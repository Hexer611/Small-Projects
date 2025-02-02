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

global erdem_strlen, erdem_strcpy, erdem_strcmp, erdem_open, erdem_read, erdem_write, erdem_strdup
section .text

erdem_strlen:
    mov rax, 0                  ; init rax as 0, not sure if necessary
erdem_loop:
    movzx rdx, byte [rdi]       ; load first char from the pointer, hopefully it exists
    cmp rdx, 0                  ; compare if the char we read is the end of the string
    je .returnfunc              ; je means the previous comparison is equal i hope. jg is greater, jl is less??
    inc rdi                     ; if we didn't find the last char we increase the pointer to next char
    inc rax                     ; if we didn't find the last char we increase the rax value by one which is the char count
    jmp erdem_loop              ; go back to counting characters :D
.returnfunc:                    ; finish him
    ret

erdem_strcpy:
    mov al, [rsi]
    mov byte [rdi], al
    test al, al                  ; compare if the char we read is the end of the string
    je .ret_strcpy

    inc rsi
    inc rdi
    jmp erdem_strcpy
.ret_strcpy:                          ; finish him
    ret

erdem_strcmp:
    mov al, [rsi]
    mov bl, [rdi]
    cmp al, bl                  ; compare if the char we read is the end of the string
    ja .ret_strcmp_g
    jb .ret_strcmp_l
    cmp al, 0                  ; compare if the char we read is the end of the string
    je .ret_strcmp_e

    inc rdi
    inc rsi
    jmp erdem_strcmp
.ret_strcmp_g:                          ; finish him
    movzx rax, al
    neg rax
    ret
.ret_strcmp_l:                          ; finish him
    movzx rax, bl
    ret
.ret_strcmp_e:                          ; finish him
    mov rax, 0
    ret

erdem_open:
    mov rax, 2
    ;mov rdi, name
    ;mov rsi, flags
    ;mov rdx, mode
    syscall
    ret

erdem_read:
    mov rax, 0
    ;mov rdi, uint fd
    ;mov rsi, char* buffer
    ;mov rdx, size_t count
    syscall
    ret

erdem_write:
    mov rax, 1
    ;mov rdi, uint fd
    ;mov rsi, const char* buffer
    ;mov rdx, size_t count
    syscall
    ret

erdem_strdup:
    mov r12, rdi
    mov rax, 0                  
strdup_loop:
    movzx rdx, byte [rdi]       
    cmp rdx, 0                  
    je .returnstrdup            
    inc rdi                     
    inc rax                     
    jmp strdup_loop           
.returnstrdup:                  
    inc rax
    mov rdi, 0
    mov rsi, rax
    mov rdx, 3
    mov r10, 34
    mov r8, -1
    mov r9, 0
    mov rax, 9
    syscall

    mov rsi, rax

.conts:
    mov r8b, [r12]
    mov byte [rsi], r8b

    test r8b, r8b                  ; compare if the char we read is the end of the string
    je .ret_strdup_strcpy

    inc rsi
    inc r12
    
    jmp .conts
.ret_strdup_strcpy:                          ; finish him
    mov rdi, r11
    mov rax, rax
    ret








