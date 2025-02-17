.686
.model flat
	public _liczba_przeciwna

.code

_liczba_przeciwna PROC
	push ebp ; zapisanie zawartoœci EBP na stosie
	mov ebp,esp ; kopiowanie zawartoœci ESP do EBP
	push ebx ; przechowanie zawartoœci rejestru EBX
	; wpisanie do rejestru EBX adresu zmiennej zdefiniowanej
	; w kodzie w jêzyku C
	mov ebx, [ebp+8]
	mov eax, [ebx] ; odczytanie wartoœci zmiennej
	neg eax ; zanegowanie wartoœci
	mov [ebx], eax ; odes³anie wyniku do zmiennej
	; uwaga: trzy powy¿sze rozkazy mo¿na zast¹piæ jednym rozkazem
	; w postaci: inc dword PTR [ebx]
	pop ebx
	pop ebp
	ret
_liczba_przeciwna ENDP

END