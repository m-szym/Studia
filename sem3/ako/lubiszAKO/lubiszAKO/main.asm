; Przyk³ad wywo³ywania funkcji MessageBoxA i MessageBoxW
.686
.model flat
includelib libcmt.lib

extern _ExitProcess@4 : PROC
extern _MessageBoxA@16 : PROC


public _main

.data
tytul db 'Proste pytanie',0
tekst db 'Czy lubisz AKO ?',0

.code

_main PROC
	_pytanie:
	push 24h ;odzaj ikony
	push OFFSET tytul  ; tytu³
	push OFFSET tekst  ; tekst
	push 0  ; rodzaj przycisków
	
	call _MessageBoxA@16

	cmp eax, 6
	jne _pytanie


	push 0  ; kod powrotu programu
	call _ExitProcess@4
_main ENDP
END