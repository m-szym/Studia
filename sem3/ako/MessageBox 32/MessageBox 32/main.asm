.686
.model flat

includelib libcmt.lib	;tak te¿ mo¿na

extern _ExitProcess@4 : PROC
extern __write : PROC ; (dwa znaki podkreœlenia)
extern _MessageBoxA@16 : PROC

public _main

.data
	tekst db 10, 'Nazywam sie . . . ' , 10
			db 'Moj pierwszy 32-bitowy program '
			db 'asemblerowy dziala juz poprawnie!', 10

	naglowek db "Komunikat", 0
	tresc db 'Witaj!', 0

.code

_main PROC
	mov ecx, 85 ; liczba znaków wyœwietlanego tekstu
	; wywo³anie funkcji ”write” z biblioteki jêzyka C
	push ecx ; liczba znaków wyœwietlanego tekstu
	push dword PTR OFFSET tekst ; po³o¿enie obszaru
	; ze znakami
	push dword PTR 1 ; uchwyt urz¹dzenia wyjœciowego
	call __write ; wyœwietlenie znaków
	; (dwa znaki podkreœlenia _ )
	add esp, 12 ; usuniêcie parametrów ze stosu

	push 6 ; parameter uType
	push OFFSET naglowek ; adres ci¹gu znaków stanowi¹cych nag³ówek komunikatu
	push OFFSET tresc ; adres ci¹gu znaków stanowi¹cych treœæ komunikatu
	push 0 ; uchwyt
	call _MessageBoxA@16 ; skok do podprogramu systemowego MessageBox
	; w przypadku ³añcuchów w Unicode call _MessageBoxW@16


	; zakoñczenie wykonywania programu
	push dword PTR 0 ; kod powrotu programu
	call _ExitProcess@4
_main ENDP

END