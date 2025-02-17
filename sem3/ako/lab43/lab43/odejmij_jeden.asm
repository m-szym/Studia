.686
.model flat

	public _odejmij_jeden
.code

_odejmij_jeden PROC
	push ebp	; zapisanie zawartoœci EBP na stosie
	mov ebp,esp ; kopiowanie zawartoœci ESP do EBP
	push ebx	; przechowanie zawartoœci rejestru EBX

	; wpisanie do rejestru EBX adresu zmiennej zdefiniowanej
	; w kodzie w jêzyku C, zawieraj¹cej adres zmiennej docelowej
	mov ebx, [ebp+8]
	mov edx, [ebx]	; wpisanie do EDX adresu zmiennej docelowej
	mov eax, [edx]	; wpisanie do EAX wartoœci zmiennej docelowej
	dec eax		; zmniejszenie wartoœci o 1
	mov [edx], eax ; odes³anie wyniku do zmiennej
	pop ebx
	pop ebp
	ret
_odejmij_jeden ENDP

END