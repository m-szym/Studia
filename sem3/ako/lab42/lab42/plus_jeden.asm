.686
.model flat
	public _plus_jeden

.code

_plus_jeden PROC
	push ebp ; zapisanie zawarto�ci EBP na stosie
	mov ebp,esp ; kopiowanie zawarto�ci ESP do EBP
	push ebx ; przechowanie zawarto�ci rejestru EBX
	; wpisanie do rejestru EBX adresu zmiennej zdefiniowanej
	; w kodzie w j�zyku C
	mov ebx, [ebp+8]
	mov eax, [ebx] ; odczytanie warto�ci zmiennej
	inc eax ; dodanie 1
	mov [ebx], eax ; odes�anie wyniku do zmiennej
	; uwaga: trzy powy�sze rozkazy mo�na zast�pi� jednym rozkazem
	; w postaci: inc dword PTR [ebx]
	pop ebx
	pop ebp
	ret
_plus_jeden ENDP

END