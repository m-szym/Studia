.686
.model flat

public _roznica
public _iteracja
public _l_proc
public _godzina

extern _GetSystemInfo@4:PROC
extern _malloc:PROC
extern _GetSystemTime@4:PROC

.data
	dekoder db "0102030405060708"
			db "0910111213141516"
			db "1718192021222324"

.code

_roznica PROC
	push ebp
	mov ebp, esp

	mov eax, [ebp+8]
	mov eax, [eax]

	mov ecx, [ebp+12]
	mov ecx, [ecx]
	mov ecx, [ecx]

	sub eax, ecx
	
	pop ebp
	ret
_roznica ENDP

_iteracja PROC
	push ebp
	mov ebp, esp

	mov al, [ebp+8]
	sal al, 1

	jc zakoncz
	inc al

	push eax
	call _iteracja
	add esp, 4

	pop ebp
	ret

	zakoncz:
	rcr al, 1
	pop ebp
	ret
_iteracja ENDP

_htest PROC
	mov ebx, 00000001h

	mov eax, ebx
	shr eax, 7
	cmp eax, 0
	jne nie
	clc
	ret
	nie:
	stc
	ret
_htest ENDP

_l_proc PROC
	push ebp
	mov ebp, esp

	sub esp, 36

	push esp
	call _GetSystemInfo@4

	mov eax, dword ptr [ebp-16]	;???

	add esp, 9*4
	pop ebp
	ret
_l_proc ENDP

_godzina PROC
	push ebp
	mov ebp, esp

	sub esp, 16

	push esp
	call _GetSystemTime@4

	mov ax, word ptr [esp+8]
	mov cx, word ptr dekoder[2*eax]
	mov edx, dword ptr [ebp+8]
	mov word ptr [edx], cx


	add esp, 16

	pop ebp
	ret
_godzina ENDP

_test PROC
	push ebp
	mov ebp, esp

	mov ebx, [ebp+8]
	;and ebx, 7fffffh
	mov eax, 1
	shl eax, 23
	add ebx, eax
	finit 
	push ebx
fld dword ptr [esp]
add esp, 4

	pop ebp
	ret
_test ENDP

END