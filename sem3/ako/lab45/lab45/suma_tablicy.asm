public suma_tablicy
.code
suma_tablicy PROC
	push rdi

	mov rax, 0
	mov rdi, 0

	petla:
	add rax, [rcx + 8*rdi]
	inc rdi
	cmp rdi, rdx
	jl petla

	pop rdi
	ret
suma_tablicy ENDP
END