.686
.model flat

extern _ExitProcess@4 : PROC
extern __write : PROC ; (dwa znaki podkreœlenia)

public _main

.data
	srow db 00h, 00h, 80h, 00h
	nrows db 15*4 dup (0)
	lf db 10d
	maska dd 1110b


.code

row PROC
	mov eax, 0
	mov ecx, 0
	mov edi, 0

	petla:
	mov eax, [ebx]
	shr eax, cl
	shl eax, 1
	and eax, [maska]

	op1:
	cmp al, 00001110b
	jnz op2
	add ecx, 1
	btr [edx], ecx
	sub ecx, 1
	jmp kolejny

	op2:
	cmp al, 00001100b
	jnz op3
	add ecx, 1
	btr [edx], ecx
	sub ecx, 1
	jmp kolejny

	op3:
	cmp al, 00001010b
	jnz op4
	add ecx, 1
	btr [edx], ecx
	sub ecx, 1
	jmp kolejny

	op4:
	cmp al, 00001000b
	jnz op5
	add ecx, 1
	btc [edx], ecx
	sub ecx, 1
	jmp kolejny

	op5:
	cmp al, 00000110b
	jnz op6
	add ecx, 1
	btc [edx], ecx
	sub ecx, 1
	jmp kolejny

	op6:
	cmp al, 00000100b
	jnz op7
	add ecx, 1
	btc [edx], ecx
	sub ecx, 1
	jmp kolejny

	op7:
	cmp al, 00000010b
	jnz op8
	add ecx, 1
	btc [edx], ecx
	sub ecx, 1
	jmp kolejny

	op8:
	cmp al, 00000000b
	jnz kolejny
	add ecx, 1
	btr [edx], ecx
	sub ecx, 1
	jmp kolejny

	kolejny:
	add ecx, 1
	cmp ecx, 29
	jb petla

	ret
row ENDP
	

_main PROC
	mov eax, dword ptr [srow]
	mov dword ptr [nrows], eax
	mov ebx, OFFSET [nrows]
	mov edx, OFFSET [nrows + 4]
	mov esi, 0



	mov ecx, 0
	mov ecx, -1
	mov cx, 22
	skok:
	sub cx, 11
	je et2
	call skok
	et2:
	mov ecx, [esp]
	neg ecx
	lea ecx, [ecx+et2+1]

	;ptl
	call row
	;add ebx, 4
	;add edx, 4
	;add esi, 1
	;cmp esi, 15
	;jb pl


	push dword PTR 0 ; kod powrotu programu
	call _ExitProcess@4
_main ENDP

END

  