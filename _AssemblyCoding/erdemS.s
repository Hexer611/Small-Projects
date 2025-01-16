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


global maxofthree, floaterdem, maxofthreefif
section .text
maxofthreeiii:
        mov     rax, rcx        ; Load the first argument into rax
        cmp     rax, rdx        ; Compare rax (first argument) and rsi (second argument)
        cmovl   rax, rdx        ; If rax < rsi, move rsi into rax
        cmp     rax, r8        ; Compare rax (current max) and rdx (third argument)
        cmovl   rax, r8        ; If rax < rdx, move rdx into rax
        ret                     ; Return with the maximum value in rax

maxofthreefif:
        cvtsi2ss xmm1, rdx         ; Manually copy integer second argument from rdx to xmm1
        minss    xmm0, xmm1        ; Compare rax (first argument) and rsi (second argument)
        minss    xmm0, xmm2        ; If rax < rsi, move rsi into rax
        ret

floaterdem:
    ;mov rax, 1     ; Move the first argument into RAX (return register)
    ;mov eax, 
    ;cvtsi2ss xmm0, eax
    ret
