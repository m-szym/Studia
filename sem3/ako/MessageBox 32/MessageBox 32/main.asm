.686
.model flat

includelib libcmt.lib	;tak te� mo�na

extern _ExitProcess@4 : PROC
extern __write : PROC ; (dwa znaki podkre�lenia)
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
	mov ecx, 85 ; liczba znak�w wy�wietlanego tekstu
	; wywo�anie funkcji �write� z biblioteki j�zyka C
	push ecx ; liczba znak�w wy�wietlanego tekstu
	push dword PTR OFFSET tekst ; po�o�enie obszaru
	; ze znakami
	push dword PTR 1 ; uchwyt urz�dzenia wyj�ciowego
	call __write ; wy�wietlenie znak�w
	; (dwa znaki podkre�lenia _ )
	add esp, 12 ; usuni�cie parametr�w ze stosu

	push 6 ; parameter uType
	push OFFSET naglowek ; adres ci�gu znak�w stanowi�cych nag��wek komunikatu
	push OFFSET tresc ; adres ci�gu znak�w stanowi�cych tre�� komunikatu
	push 0 ; uchwyt
	call _MessageBoxA@16 ; skok do podprogramu systemowego MessageBox
	; w przypadku �a�cuch�w w Unicode call _MessageBoxW@16


	; zako�czenie wykonywania programu
	push dword PTR 0 ; kod powrotu programu
	call _ExitProcess@4
_main ENDP

END