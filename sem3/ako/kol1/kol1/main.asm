.686
.model flat
includelib libcmt.lib

extern _ExitProcess@4 : PROC
extern __read : PROC

public _main

.data
	stale dw 2, 1
	napis dw 10 dup(3), 2
	tekst db 7 dup(9)
	ww	  dq 1
	kon db 15
	qxy dw 254, 255, 256
	wq db 11,22,33,44

	linie dd 421, 422, 423
		  dd 442, 444, 427, 432

	obszar dw 2 dup (?)
	rej db 1, 126 dup (0), 0ffh

	bigE dq 0aabbccddh
	dest dd 20 dup(0deadbeefh) 
	bufor db 20 dup(0)
.code

rol1024 PROC
	mov eax, dword ptr rej[124]
	shl eax, 1
	mov dword ptr rej[124], eax
	mov eax, 0
	adc eax, 0
	push eax

	clc
	mov eax, 0
	mov ecx, 31
	ptl:
	mov eax, dword ptr rej[4*ecx-4]
	shl eax, 1
	mov dword ptr rej[4*ecx-4], eax
	mov eax, dword ptr rej[4*ecx]
	adc eax, 0
	mov dword ptr rej[4*ecx], eax
	loop ptl

	mov eax, dword ptr rej[0]
	pop ecx
	add eax, ecx
	mov dword ptr rej[0], eax

	ret
rol1024 ENDP

dziel_minus2 PROC
	sar eax, 1
	pushf
	neg eax
	popf
	ret
dziel_minus2 ENDP

min_dwa PROC
	mov ebx, 0
	mov ecx, 0

	ptl:
	call dziel_minus2
	adc ebx, 0
	ror ebx, 1
	inc cl
	cmp eax, 0
	jne ptl

	mov eax, ebx
	rol eax, cl
	;ror eax, 1

	ret 
min_dwa ENDP

dodaj PROC
	mov ebx, [esp]
	add [esp], dword ptr 12
	mov dx, 0
	mov dh, [ebx+9]
	sub dh, [ebx+7]
	ret
dodaj ENDP

_main PROC
	mov eax, 0
	push dword ptr 12
	push dword ptr offset bufor
push dword ptr 0
	call __read
add esp, 12
mov dl, bufor[-1]


	mov eax, dword ptr offset dest
	mov [eax+76], dword ptr -1

	call dodaj
	dd 01020304h
	dd 01010101h
	dd 02020202h
	


	mov esi, 0
	mov ax, 1
	mov dx, -1
	;cmp ax, dx
	sub ax, dx
	ja ptc	
	mov esi, 15
	ptc:



	mov eax, 0
	mov ebx, offset bigE
	mov ax, word ptr [ebx+2]
	;rol ax, 8
	shl eax, 16
	mov ax, word ptr [ebx]
	ror ax, 8
	

	;mov eax, 9
	;call min_dwa
	;
	;mov eax, dword ptr rej
	;mov eax, dword ptr rej[124]
	;call rol1024
	;mov eax, 0
	;mov eax, dword ptr rej
	;
	;mov edi, 0
	;mov al, 123
	;movzx edi, al

	push 7
	push OFFSET tekst
	push 0
	call __read
	add esp, 12

	mov eax, 2000000000d
	mov ecx, 2000000000d
	mul ecx

	mov eax, 0aabbccddh
	push eax

et0: push et0
	ret
et:	lea dword PTR eax, [et]
	mov dword ptr [obszar], eax

	push 16
	push -16
	rol word ptr [esp+3], 4

	mov ecx, 0
	mov ebx, 0
	mov edi, 0

	mov cx, napis -1
	sub tekst, ch
	mov edi, 1
	mov tekst[4*edi], ch
	mov ebx, dword ptr tekst+1

	xor eax, eax
	sub eax, 0ffffffffh

	mov ebx, -2
	neg ebx
	or ebx, 80000000h

	mov ebx, 11111111h
	mov eax, 22222222h
	sub esp, 8
	mov [esp+4], ebx
	mov [esp], eax

	mov ax, 1
	add ax, 0ffffh

	mov eax, dword ptr qxy+1
	mov ebx, offset wq
	mov al, byte ptr [ebx]
	shl eax, 8
	mov al, [ebx+1]

	mov eax, 63d
	mov ebx, eax
	shl eax, 1
	shl ebx, 3
	add eax, ebx

	mov esi, (OFFSET linie) + 4
	mov ebx,4
	mov edx, [ebx] [esi]


	push 0
	call _ExitProcess@4
_main ENDP
END