.686
.model flat

includelib libcmt.lib

extern __read : PROC
extern __write : PROC
extern _ExitProcess@4 : PROC
extern _puts : PROC

public _main

.data
	; wczytywanie liczby dziesi�tnej z klawiatury � po
	; wprowadzeniu cyfr nale�y nacisn�� klawisz Enter
	; liczba po konwersji na posta� binarn� zostaje wpisana
	; do rejestru EAX
	; deklaracja tablicy do przechowywania wprowadzanych cyfr
	; (w obszarze danych)
	;obszar db 12 dup (?)
	dziesiec dd 10 ; mno�nik

	;znaki db 12 dup (?)
	dekoder db '0123456789ABCDEF'
	base_in dd 10d
	base_out dd 10d

.code

;wyswietl EAX jako liczbe dziesietna
wyswietl_EAX_dec PROC
	pusha
	mov esi, 10 ; indeks w tablicy 'znaki'
	mov ebx, 10 ; dzielnik r�wny 10
	sub esp, 12
	mov edi, esp

	konwersja:
	mov edx, 0 ; zerowanie starszej cz�ci dzielnej
	div ebx ; dzielenie przez 10, reszta w EDX,
			; iloraz w EAX
	add dl, 30H ; zamiana reszty z dzielenia na kod
				; ASCII
	mov [edi] [esi], dl; zapisanie cyfry w kodzie ASCII
	dec esi ; zmniejszenie indeksu
	cmp eax, 0 ; sprawdzenie czy iloraz = 0
	jne konwersja ; skok, gdy iloraz niezerowy

	; wype�nienie pozosta�ych bajt�w spacjami i wpisanie
	; znak�w nowego wiersza
	wypeln:
	or esi, esi
	jz wyswietl ; skok, gdy ESI = 0
	mov byte PTR [edi] [esi], 20H ; kod spacji
	dec esi ; zmniejszenie indeksu
	jmp wypeln

	wyswietl:
	mov byte PTR [edi] [0], 0AH ; kod nowego wiersza
	mov byte PTR [edi] [11], 0AH ; kod nowego wiersza
	; wy�wietlenie cyfr na ekranie
	push dword PTR 12 ; liczba wy�wietlanych znak�w
	push dword PTR edi ; adres wy�w. obszaru
	push dword PTR 1; numer urz�dzenia (ekran ma numer 1)
	call __write ; wy�wietlenie liczby na ekranie

	add esp, 12 ; usuni�cie parametr�w ze stosu
	add esp, 12

	popa
	ret
wyswietl_EAX_dec ENDP

;wczytaj liczbe dziesietna z klawiatury do EAX
wczytaj_do_EAX_dec PROC
	push ebx
	push ecx
	sub esp, 12
	mov edi, esp

	;max ilo�� znak�w wczytywanej liczby
	push dword PTR 12
	push dword PTR [esi] ; adres obszaru pami�ci
	push dword PTR 0; numer urz�dzenia (0 dla klawiatury)
	call __read ; odczytywanie znak�w z klawiatury
				; (dwa znaki podkre�lenia przed read)
	add esp, 12 ; usuni�cie parametr�w ze stosu
				; bie��ca warto�� przekszta�canej liczby przechowywana jest
				; w rejestrze EAX
	; przyjmujemy 0 jako warto�� pocz�tkow�
	mov eax, 0
	mov ebx, [esi] ; adres obszaru ze znakami
	pobieraj_znaki:
	mov cl, [ebx] ; pobranie kolejnej cyfry w kodzie
				  ; ASCII
	inc ebx ; zwi�kszenie indeksu
	cmp cl,10 ; sprawdzenie czy naci�ni�to Enter
	je byl_enter ; skok, gdy naci�ni�to Enter
	sub cl, 30H ; zamiana kodu ASCII na warto�� cyfry
	movzx ecx, cl ; przechowanie warto�ci cyfry w
	; rejestrze ECX
	; mno�enie wcze�niej obliczonej warto�ci razy 10
	mul dword PTR dziesiec
	add eax, ecx ; dodanie ostatnio odczytanej cyfry
	jmp pobieraj_znaki ; skok na pocz�tek p�tli
	byl_enter:
	; warto�� binarna wprowadzonej liczby znajduje si� teraz w
	;rejestrze EAX
	add esp, 12
	pop ecx
	pop ebx
	ret
wczytaj_do_EAX_dec ENDP

;wyswietl EAX jako liczbe szesnastkowa
wyswietl_EAX_hex PROC
	; wy�wietlanie zawarto�ci rejestru EAX
	; w postaci liczby szesnastkowej
	pusha ; przechowanie rejestr�w
	; rezerwacja 12 bajt�w na stosie (poprzez zmniejszenie
	; rejestru ESP) przeznaczonych na tymczasowe przechowanie
	; cyfr szesnastkowych wy�wietlanej liczby
	sub esp, 12
	mov edi, esp ; adres zarezerwowanego obszaru
				 ; pami�ci
	; przygotowanie konwersji
	mov ecx, 8 ; liczba obieg�w p�tli konwersji
	mov esi, 1 ; indeks pocz�tkowy u�ywany przy
			   ; zapisie cyfr

	; p�tla konwersji
	ptl3hex:
	; przesuni�cie cykliczne (obr�t) rejestru EAX o 4 bity w lewo
	; w szczeg�lno�ci, w pierwszym obiegu p�tli bity nr 31 - 28
	; rejestru EAX zostan� przesuni�te na pozycje 3 - 0
	rol eax, 4
	; wyodr�bnienie 4 najm�odszych bit�w i odczytanie z tablicy
	; 'dekoder' odpowiadaj�cej im cyfry w zapisie szesnastkowym
	mov ebx, eax ; kopiowanie EAX do EBX
	and ebx, 0000000FH ; zerowanie bit�w 31 - 4 rej.EBX
	mov dl, dekoder[ebx] ; pobranie cyfry z tablicy
	; przes�anie cyfry do obszaru roboczego
	mov [edi][esi], dl
	inc esi ;inkrementacja modyfikatora
	loop ptl3hex ; sterowanie p�tl�
	; wpisanie znaku nowego wiersza przed i po cyfrach

	mov esi, 1
	zera:
	mov ecx, 0
	mov cl, byte PTR [edi][esi]
	cmp byte PTR [edi][esi], "0"
	jne dalej
	mov byte PTR [edi][esi], " "
	inc esi
	jmp zera
	dalej:

	mov byte PTR [edi][0], 10
	mov byte PTR [edi][9], 10
	; wy�wietlenie przygotowanych cyfr
	push 10 ; 8 cyfr + 2 znaki nowego wiersza
	push edi ; adres obszaru roboczego
	push 1 ; nr urz�dzenia (tu: ekran)
	call __write ; wy�wietlenie
	; usuni�cie ze stosu 24 bajt�w, w tym 12 bajt�w zapisanych
	; przez 3 rozkazy push przed rozkazem call
	; i 12 bajt�w zarezerwowanych na pocz�tku podprogramu
	add esp, 24
	popa ; odtworzenie rejestr�w
	ret ; powr�t z podprogramu
wyswietl_EAX_hex ENDP

;wczytaj liczbe szesnastkowa z klawiatury do EAX
wczytaj_do_EAX_hex PROC
	; wczytywanie liczby szesnastkowej z klawiatury � liczba po
	; konwersji na posta� binarn� zostaje wpisana do rejestru EAX
	; po wprowadzeniu ostatniej cyfry nale�y nacisn�� klawisz
	; Enter

	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp

	; rezerwacja 12 bajt�w na stosie przeznaczonych na tymczasowe
	; przechowanie cyfr szesnastkowych wy�wietlanej liczby
	sub esp, 12 ; rezerwacja poprzez zmniejszenie ESP
	mov esi, esp ; adres zarezerwowanego obszaru pami�ci
	push dword PTR 10 ; max ilo�� znak�w wczytyw. liczby
	push esi ; adres obszaru pami�ci
	push dword PTR 0; numer urz�dzenia (0 dla klawiatury)
	call __read ; odczytywanie znak�w z klawiatury
	; (dwa znaki podkre�lenia przed read)
	add esp, 12 ; usuni�cie parametr�w ze stosu
	mov eax, 0 ; dotychczas uzyskany wynik

	pocz_konw:
	mov dl, [esi] ; pobranie kolejnego bajtu
	inc esi ; inkrementacja indeksu
	cmp dl, 10 ; sprawdzenie czy naci�ni�to Enter
	je gotowe  ; skok do ko�ca podprogramu

	; sprawdzenie czy wprowadzony znak jest cyfr� 0, 1, 2 , ..., 9
	cmp dl, '0'
	jb pocz_konw ; inny znak jest ignorowany
	cmp dl, '9'
	ja sprawdzaj_dalej
	sub dl, '0' ; zamiana kodu ASCII na warto�� cyfry
	dopisz:
	shl eax, 4 ; przesuni�cie logiczne w lewo o 4 bity
	or al, dl ; dopisanie utworzonego kodu 4-bitowego
	; na 4 ostatnie bity rejestru EAX
	jmp pocz_konw ; skok na pocz�tek p�tli konwersji

	; sprawdzenie czy wprowadzony znak jest cyfr� A, B, ..., F
	sprawdzaj_dalej:
	cmp dl, 'A'
	jb pocz_konw ; inny znak jest ignorowany
	cmp dl, 'F'
	ja sprawdzaj_dalej2
	sub dl, 'A' - 10 ; wyznaczenie kodu binarnego
	jmp dopisz
	; sprawdzenie czy wprowadzony znak jest cyfr� a, b, ..., f

	sprawdzaj_dalej2:
	cmp dl, 'a'
	jb pocz_konw ; inny znak jest ignorowany
	cmp dl, 'f'
	ja pocz_konw ; inny znak jest ignorowany
	sub dl, 'a' - 10
	jmp dopisz
	gotowe:

	; zwolnienie zarezerwowanego obszaru pami�ci
	add esp, 12
	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	ret
wczytaj_do_EAX_hex ENDP


wyswietl_EAX_Nary PROC
	pusha
	mov esi, 20 ; indeks w teoretycznej tablicy 'znaki' (obszarze stosu)
	mov ebx, base_out ; dzielnik r�wny ebx
	sub esp, 22 ; rezerwacja 22 (LF + 20 znak�w + LF) bajt�w na stosie
	mov edi, esi ; ebp liczy gdzie kolejny przerywnik
	mov ebp, esi
	sub ebp, ecx

	konwersja_N:
	mov edx, 0 ; zerowanie starszej cz�ci dzielnej
	div ebx ; dzielenie przez 12, reszta w EDX,
			; iloraz w EAX

	cmp dl, 9d
	ja zamiana_N
	add dl, 30H ; zamiana reszty z dzielenia na kod
				; ASCII
	jmp wpisanie_N

	zamiana_N:
	add dl, 37H ; zamiana reszty z dzielenia na kod
				; ASCII

	
	wpisanie_N:
	; odst�py co ecx znak�w
	cmp esi, ebp
	jne dale
	mov byte PTR [edi] [esi], '.' ; kod przerywnika
	sub ebp, ecx
	sub ebp, 1
	dec esi
	jmp wpisanie_N
	dale:
	; koniec odst�p�w
	mov [edi] [esi], dl; zapisanie cyfry w kodzie ASCII
	dec esi ; zmniejszenie indeksu
	cmp eax, 0 ; sprawdzenie czy iloraz = 0
	jne konwersja_N ; skok, gdy iloraz niezerowy

	; wype�nienie pozosta�ych bajt�w spacjami i wpisanie
	; znak�w nowego wiersza
	wypeln_N:
	or esi, esi
	jz wyswietl_N ; skok, gdy ESI = 0
	mov byte PTR [edi] [esi], 2AH ; kod spacji
	dec esi ; zmniejszenie indeksu
	jmp wypeln_N

	wyswietl_N:
	mov byte PTR [edi] [0], 0AH ; kod nowego wiersza
	mov byte PTR [edi] [21], 0AH ; kod nowego wiersza
	; wy�wietlenie cyfr na ekranie
	push dword PTR 22 ; liczba wy�wietlanych znak�w
	push dword PTR edi ; adres wy�w. obszaru
	push dword PTR 1; numer urz�dzenia (ekran ma numer 1)
	call __write ; wy�wietlenie liczby na ekranie

	add esp, 12 ; usuni�cie parametr�w ze stosu
	add esp, 22 ; zwolnienie pami�ci przechowuj�cej tekstow� posta� liczby

	popa
	ret
wyswietl_EAX_Nary ENDP

wczytaj_do_EAX_N PROC
	push ebx
	push ecx
	sub esp, 12
	mov edi, esp

	;max ilo�� znak�w wczytywanej liczby
	push dword PTR 12
	push dword PTR [esi] ; adres obszaru pami�ci
	push dword PTR 0; numer urz�dzenia (0 dla klawiatury)
	call __read ; odczytywanie znak�w z klawiatury
				; (dwa znaki podkre�lenia przed read)
	add esp, 12 ; usuni�cie parametr�w ze stosu
				; bie��ca warto�� przekszta�canej liczby przechowywana jest
				; w rejestrze EAX
	; przyjmujemy 0 jako warto�� pocz�tkow�
	mov eax, 0
	mov ebx, [esi] ; adres obszaru ze znakami
	pobieraj_znakiN:
	mov cl, [ebx] ; pobranie kolejnej cyfry w kodzie
				  ; ASCII
	inc ebx ; zwi�kszenie indeksu
	cmp cl, 10 ; sprawdzenie czy naci�ni�to Enter
	je byl_enter ; skok, gdy naci�ni�to Enter

	; sprawdzenie czy wprowadzony znak jest cyfr� 0, 1, 2 , ..., 9
	cmp cl, '0'
	jb pobieraj_znakiN ; inny znak jest ignorowany
	cmp cl, '9'
	ja sprawdzaj_dalejN
	sub cl, '0' ; zamiana kodu ASCII na warto�� cyfry
	jmp dodajN

	; sprawdzenie czy wprowadzony znak jest cyfr� A, B, ..., F
	sprawdzaj_dalejN:
	cmp cl, 'A'
	jb  pobieraj_znakiN; inny znak jest ignorowany
	cmp cl, 'Z'
	ja sprawdzaj_dalejN2
	sub cl, 'A' - 10 ; wyznaczenie kodu binarnego
	jmp dodajN
	; sprawdzenie czy wprowadzony znak jest cyfr� a, b, ..., f

	sprawdzaj_dalejN2:
	cmp cl, 'a'
	jb pobieraj_znakiN ; inny znak jest ignorowany
	cmp cl, 'z'
	ja pobieraj_znakiN ; inny znak jest ignorowany
	sub cl, 'a' - 10
	jmp dodajN

	dodajN:
	movzx ecx, cl ; przechowanie warto�ci cyfry w
	; rejestrze ECX
	; mno�enie wcze�niej obliczonej warto�ci razy 10
	mul dword PTR base_in
	add eax, ecx ; dodanie ostatnio odczytanej cyfry
	jmp pobieraj_znakiN ; skok na pocz�tek p�tli
	byl_enter:
	; warto�� binarna wprowadzonej liczby znajduje si� teraz w
	; rejestrze EAX
	add esp, 12
	pop ecx
	pop ebx
	ret
wczytaj_do_EAX_N ENDP

; funkcja, kt�ra ma argumenty w kodzie, a nie jak cz�owiek na stosie / w rejestrach
; tylko 1 argument - dword
fun PROC
	mov ebp, [esp]	; esp jest za ostatnia warto�ci� ip - w miejscu w kodzie gdzie zaczynaj� si� parametry
	mov eax, [ebp]	; pod ebp pierwszy parametr - wpisujemy do eax
	add ebp, 4		; przesuwamy ebp o 4 bajty - na kolejny parametr lub poza parametry => adres powrotu
	push ebp		; zapisujemy na stosie adres powrotu
	ret				; powr�t z fun
fun ENDP

dziel PROC
	; dzielenie eax przez ebx i wyswietlenie wyniku jako liczby dziesietnej
	; 3 miejsca po przecinku
	; wynik dzielenia mo�e by� wi�kszy ni� 10, wi�c wy�wietlamy go z pomoc� wy�wietl_EAX_dec
	;	lekko zmodyfikowanego - bez LF na ko�cu
	; cz�� u�amkow� wy�wietlamy r�cznie dziel�c 3 razy pisemnie
	;	dzielimy, mno�ymy reszt� przez 10, wpisujemy do pami�ci wynik i dzielimy ponownie
	; cz�� u�amkow� wy�wietlamy przez puts znak po znaku
	mov ecx, 0
	sub esp, 5
	mov edi, esp
	mov byte PTR [edi], ','
	mov byte PTR [edi+4], 0Ah
	mov eax, 211d
	mov ebx, 22d
	div bl
	mov ch, ah
	mov ah, 0
	call wyswietl_EAX_dec
	mov ah, ch
	movzx ecx, ah
	mov ax, cx
	mul byte ptr dziesiec
	div bl
	add al, 30h
	mov byte PTR [edi+1], al
	movzx ecx, ah
	mov ax, cx
	mul byte ptr dziesiec
	div bl
	add al, 30h
	mov byte PTR [edi+2], al
	movzx ecx, ah
	mov ax, cx
	mul byte ptr dziesiec
	div bl
	add al, 30h
	mov byte PTR [edi+3], al

	push dword PTR 5
	push dword PTR edi
	push dword PTR 1
	call __write

	add esp, 12
	add esp, 5
	ret
dziel ENDP

; wyswietl EAX_dec z pomoc� _puts
wyswietl_EAX_dec2 PROC
	pusha
	mov esi, 10 ; indeks w tablicy 'znaki'
	mov ebx, 10 ; dzielnik r�wny 10
	;sub esp, 12
	mov edi, esp

	dkonwersja:
	mov edx, 0 ; zerowanie starszej cz�ci dzielnej
	div ebx ; dzielenie przez 10, reszta w EDX,
			; iloraz w EAX
	add dl, 30H ; zamiana reszty z dzielenia na kod
				; ASCII
	mov [edi] [esi], dl; zapisanie cyfry w kodzie ASCII
	dec esi ; zmniejszenie indeksu
	cmp eax, 0 ; sprawdzenie czy iloraz = 0
	jne dkonwersja ; skok, gdy iloraz niezerowy

	; wype�nienie pozosta�ych bajt�w spacjami i wpisanie
	; znak�w nowego wiersza
	dwypeln:
	or esi, esi
	jz dwyswietl ; skok, gdy ESI = 0
	mov byte PTR [edi] [esi], 20H ; kod spacji
	dec esi ; zmniejszenie indeksu
	jmp dwypeln

	dwyswietl:
	mov byte PTR [edi] [0], 0AH ; kod nowego wiersza
	mov byte PTR [edi] [11], 0 ; kod nowego wiersza
	; wy�wietlenie cyfr na ekranie
	;push dword PTR 12 ; liczba wy�wietlanych znak�w
	push dword PTR edi ; adres wy�w. obszaru
	;push dword PTR 1; numer urz�dzenia (ekran ma numer 1)
	;call __write ; wy�wietlenie liczby na ekranie
	call _puts
	pop eax
	;add esp, 12 ; usuni�cie parametr�w ze stosu
	;add esp, 12

	popa
	ret
wyswietl_EAX_dec2 ENDP

_main PROC
	;mov eax, 26d				; testowanie og�lne 
	;call wyswietl_EAX_hex
	;call wczytaj_do_EAX_hex
	;call wyswietl_EAX_dec
	;call wyswietl_EAX_Nary
	mov ecx, 2

	whi:						; p�tla while do testowania
	call wczytaj_do_EAX_N		; exit po wpisaniu 0
	cmp eax, 0
	je dont
	call wyswietl_EAX_dec
	call wyswietl_EAX_Nary
	jmp whi
	dont:

	;call dziel					; dzielenie

	;call fun					; for fun()
	;dd 10h						; tak nie dawa� argument�w do funkcji
								; ale jest
	
	push 0
	call _ExitProcess@4
_main ENDP
END