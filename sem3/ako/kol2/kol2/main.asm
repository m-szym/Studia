.686
.model flat

;includelib libcmt.lib

extern __write : PROC
extern _ExitProcess@4 : PROC

public _main

.data


.code

formaty PROC
	clc
	mov esi, 80000001h		; format 23<->-8
	mov edi, 80000000h		; format 24<->-7

	; pierwsze porównanie 
	bt edi, 31
	jc edi_gt

	; drugie porównanie (czeœæ wspólna)
	mov eax, edi
	shl eax, 1
	cmp esi, eax
	jg esi_gt

	edi_gt:
	clc

	esi_gt:
	stc

	ret
formaty ENDP


_main PROC
		je dalej
ppp:	and eax, 0fh
		mov [edx+ebx], dl
		inc ecx
		loop ppp
dalej:


	push 0
	call _ExitProcess@4
_main ENDP
END