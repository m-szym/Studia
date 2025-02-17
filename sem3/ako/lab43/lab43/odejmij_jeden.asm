.686
.model flat

	public _odejmij_jeden
.code

_odejmij_jeden PROC
	push ebp	; zapisanie zawarto�ci EBP na stosie
	mov ebp,esp ; kopiowanie zawarto�ci ESP do EBP
	push ebx	; przechowanie zawarto�ci rejestru EBX

	; wpisanie do rejestru EBX adresu zmiennej zdefiniowanej
	; w kodzie w j�zyku C, zawieraj�cej adres zmiennej docelowej
	mov ebx, [ebp+8]
	mov edx, [ebx]	; wpisanie do EDX adresu zmiennej docelowej
	mov eax, [edx]	; wpisanie do EAX warto�ci zmiennej docelowej
	dec eax		; zmniejszenie warto�ci o 1
	mov [edx], eax ; odes�anie wyniku do zmiennej
	pop ebx
	pop ebp
	ret
_odejmij_jeden ENDP

END