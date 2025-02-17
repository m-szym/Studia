.686
.model flat

extern _ExitProcess@4 : PROC
extern __write : PROC ; (dwa znaki podkre�lenia)

public _main

.data
	tekst db 10, 'Nazywam si', 169, ' . . . ' , 10
			db 'M', 0A2h, 'j pierwszy 32-bitowy program '
			db 'asemblerowy dziala juz poprawnie!', 10

	pqr dw 257, 129, 65

.code

_minus_dwojkowy PROC
	; w eax liczba w kodzie U2
	mov edx, 0 ; wyzerowanie bufora wyj�ciowego
	mov ecx, 0 ; wyzerowanie pomocniczego licznika bufora wyj�.
	ppp:
	or eax, eax ; czy dzielna jest ju� zerem?
	jz gotowe ; je�li tak � zrekonstruuj bufor
	call dziel
	adc edx, 0 ; dodaj CF do bufora ko�owego
	add ecx, 1 ; zwi�ksz pomocniczy licznik bufora ko�owego	
	ror edx, 1 ; zr�b miejsce na kolejny bit przesuwaj�c bufor
	jmp ppp
	gotowe:
	rol edx, cl ; odtw�rz
	mov eax, edx ; wpisz wynik
	ret

_minus_dwojkowy ENDP
dziel PROC
	;neg eax
	shr eax, 1 ; podziel dzieln�
	neg eax	; zmie� znak wyniku
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

	mov ecx, 85 ; liczba znak�w wy�wietlanego tekstu

	; wywo�anie funkcji �write� z biblioteki j�zyka C
	push ecx ; liczba znak�w wy�wietlanego tekstu
	push dword PTR OFFSET tekst ; po�o�enie obszaru
								; ze znakami
	push dword PTR 1 ; uchwyt urz�dzenia wyj�ciowego
	call __write ; wy�wietlenie znak�w
				; (dwa znaki podkre�lenia _ )

	add esp, 12 ; usuni�cie parametr�w ze stosu

	mov eax, 11223344h
	mov ax, 2
	mov eax, 11223344h
	mov ah, 2

	; zako�czenie wykonywania programu
	push dword PTR 0 ; kod powrotu programu
	call _ExitProcess@4
_main ENDP

END