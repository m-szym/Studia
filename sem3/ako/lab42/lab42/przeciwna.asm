.686
.model flat
	public _liczba_przeciwna

.code

_liczba_przeciwna PROC
	push ebp ; zapisanie zawarto�ci EBP na stosie
	mov ebp,esp ; kopiowanie zawarto�ci ESP do EBP
	push ebx ; przechowanie zawarto�ci rejestru EBX
	; wpisanie do rejestru EBX adresu zmiennej zdefiniowanej
	; w kodzie w j�zyku C
	mov ebx, [ebp+8]
	mov eax, [ebx] ; odczytanie warto�ci zmiennej
	neg eax ; zanegowanie warto�ci
	mov [ebx], eax ; odes�anie wyniku do zmiennej
	; uwaga: trzy powy�sze rozkazy mo�na zast�pi� jednym rozkazem
	; w postaci: inc dword PTR [ebx]
	pop ebx
	pop ebp
	ret
_liczba_przeciwna ENDP

END