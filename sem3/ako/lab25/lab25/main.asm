.686
.model flat

includelib libcmt.lib

extern _ExitProcess@4 : PROC
extern __write : PROC ; (dwa znaki podkreœlenia)
extern __read : PROC ; (dwa znaki podkreœlenia)
extern _MessageBoxA@16 : PROC

public _main


.data
	tekst_pocz db 10, 'Proszê napisaæ jakiœ tekst '
				db 'i nacisnac Enter', 10
	koniec_t db ?
	magazyn db 80 dup (?)
	nowa_linia db 10
	liczba_znakow dd ?
	tytul db 'Wczytany komunikat', 0


.code

_main PROC
	; wyœwietlenie tekstu informacyjnego

	; liczba znaków tekstu
	mov ecx,(OFFSET koniec_t) - (OFFSET tekst_pocz)
	push ecx
	push OFFSET tekst_pocz ; adres tekstu
	push 1 ; nr urz¹dzenia (tu: ekran - nr 1)
	call __write ; wyœwietlenie tekstu pocz¹tkowego

	add esp, 12 ; usuniecie parametrów ze stosu


	; czytanie wiersza z klawiatury

	push 80 ; maksymalna liczba znaków
	push OFFSET magazyn
	push 0 ; nr urz¹dzenia (tu: klawiatura - nr 0)
	call __read ; czytanie znaków z klawiatury

	add esp, 12 ; usuniecie parametrów ze stosu


	; kody ASCII napisanego tekstu zosta³y wprowadzone
	; do obszaru 'magazyn'
	; funkcja read wpisuje do rejestru EAX liczbê
	; wprowadzonych znaków

	mov liczba_znakow, eax

	; rejestr ECX pe³ni rolê licznika obiegów pêtli
	mov ecx, eax
	mov ebx, 0 ; indeks pocz¹tkowy

	ptl: mov dl, magazyn[ebx] ; pobranie kolejnego znaku
	;tu by³o

	;polskie znaki
	pl_a:
	cmp dl, 0a5h
	jnz pl_c
	mov magazyn[ebx], 0a5h
	jmp dalej

	pl_c:
	cmp dl, 86h
	jnz pl_e
	mov magazyn[ebx], 0c6h
	jmp dalej

	pl_e:
	cmp dl, 0a9h
	jnz pl_l
	mov magazyn[ebx], 0cah
	jmp dalej

	pl_l:
	cmp dl, 88h
	jnz pl_n
	mov magazyn[ebx], 0a3h
	jmp dalej

	pl_n:
	cmp dl, 0e4h
	jnz pl_o
	mov magazyn[ebx], 0d1h
	jmp dalej

	pl_o:
	cmp dl, 0a2h
	jnz pl_s
	mov magazyn[ebx], 0d3h
	jmp dalej

	pl_s:
	cmp dl, 98h
	jnz pl_zi
	mov magazyn[ebx], 08ch
	jmp dalej

	pl_zi:
	cmp dl, 0abh
	jnz pl_z
	mov magazyn[ebx], 08fh
	jmp dalej

	pl_z:
	cmp dl, 0beh
	jnz latin
	mov magazyn[ebx], 0afh
	jmp dalej

	;angielskie znaki
	latin:
	cmp dl, 'a'
	jb dalej ; skok, gdy znak nie wymaga zamiany
	cmp dl, 'z'
	ja dalej ; skok, gdy znak nie wymaga zamiany

	sub dl, 20H ; zamiana na wielkie litery
	; odes³anie znaku do pamiêci
	mov magazyn[ebx], dl

	
	dalej: inc ebx ; inkrementacja indeksu
	;loop ptl ; sterowanie pêtl¹
	dec ecx
	jnz ptl


	; wyœwietlenie przekszta³conego tekstu
	;push liczba_znakow
	;push OFFSET magazyn
	;push 1
	;call __write ; wyœwietlenie przekszta³conego tekstu

	;add esp, 12 ; usuniecie parametrów ze stosu

	mov magazyn[ebx + 1], 0
	push 0
	push OFFSET tytul
	push OFFSET magazyn
	push 0
	call _MessageBoxA@16

	push 0
	call _ExitProcess@4 ; zakoñczenie programu
_main ENDP
END