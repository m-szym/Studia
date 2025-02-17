.686
.model flat

extern _ExitProcess@4 : PROC
extern __write : PROC ; (dwa znaki podkreœlenia)

public _main

.data
	tekst db 10, 'Nazywam si', 169, ' . . . ' , 10
			db 'M', 0A2h, 'j pierwszy 32-bitowy program '
			db 'asemblerowy dziala juz poprawnie!', 10

	pqr dw 257, 129, 65

.code

_minus_dwojkowy PROC
	; w eax liczba w kodzie U2
	mov edx, 0 ; wyzerowanie bufora wyjœciowego
	mov ecx, 0 ; wyzerowanie pomocniczego licznika bufora wyjœ.
	ppp:
	or eax, eax ; czy dzielna jest ju¿ zerem?
	jz gotowe ; jeœli tak – zrekonstruuj bufor
	call dziel
	adc edx, 0 ; dodaj CF do bufora ko³owego
	add ecx, 1 ; zwiêksz pomocniczy licznik bufora ko³owego	
	ror edx, 1 ; zrób miejsce na kolejny bit przesuwaj¹c bufor
	jmp ppp
	gotowe:
	rol edx, cl ; odtwórz
	mov eax, edx ; wpisz wynik
	ret

_minus_dwojkowy ENDP
dziel PROC
	;neg eax
	shr eax, 1 ; podziel dzieln¹
	neg eax	; zmieñ znak wyniku
	koniec:
	ret
dziel ENDP

_main PROC
	mov eax, 0
	push esp
	ret


	mov eax, 0
	mov ax, 0ffh
	shl al, 6
	shr al, 6

	mov ecx, 85 ; liczba znaków wyœwietlanego tekstu

	; wywo³anie funkcji ”write” z biblioteki jêzyka C
	push ecx ; liczba znaków wyœwietlanego tekstu
	push dword PTR OFFSET tekst ; po³o¿enie obszaru
								; ze znakami
	push dword PTR 1 ; uchwyt urz¹dzenia wyjœciowego
	call __write ; wyœwietlenie znaków
				; (dwa znaki podkreœlenia _ )

	add esp, 12 ; usuniêcie parametrów ze stosu

	mov eax, 11223344h
	mov ax, 2
	mov eax, 11223344h
	mov ah, 2

	; zakoñczenie wykonywania programu
	push dword PTR 0 ; kod powrotu programu
	call _ExitProcess@4
_main ENDP

END