#!/bin/bash


TEKST_0="Wybierz opcję wpisując jej numer"
TEKST_0O1="Nazwa pliku:"
TEKST_0O2="Katalog:"
TEKST_0O3="Tryb:"
TEKST_0O4="Tylko wykonywalne:"
TEKST_0O5="Prawa dostępu:"
TEKST_0O6="Zawartość pliku"
TEKST_0O7="> Szukaj"
TEKST_0O8="> Koniec"

TEKST_O1="$TEKST_0O1 $NAZWA"
TEKST_O2="$TEKST_0O2 $KATALOG"
TEKST_O3="$TEKST_0O3 $TRYB"
TEKST_O4="$TEKST_0O4 $WYKONYWALNE"
TEKST_O5="$TEKST_0O5 $PRAWA"

INPUT=`zenity --list --column="Nr" --column="Opcja" --width=250 --height=400 1 "$TEKST_O1" 2 "$TEKST_O2" 3 "$TEKST_O3" 4 "$TEKST_O4" 5 "$TEKST_O5" 6 "$TEKST_0O6" 7 "$TEKST_0O7" 8 "$TEKST_0O8" 9 "> Aktualizuj podgląd"`

until [ "$INPUT" = "8" -o "$?" = "1" -o "$?" = "0" ];do
    if [ "$INPUT" = "1" ];then
        NAZWA=`zenity --entry --title "Nazwa pliku" --text "Podaj nazwę pliku (wielkość liter ma znaczenie):"`
        if [ "$NAZWA" ];then
            PNAZWA="-name $NAZWA"
        else
            PNAZWA=""
        fi
    elif [ "$INPUT" = "2" ];then
        KATALOG=`zenity --entry --title "Katalog docelowy" --text "Podaj docelowy katalog:"`
        if [ "$KATALOG" ];then
            PKATALOG=$KATALOG
        else
            PKATALOG=""
        fi
    elif [ "$INPUT" = "3" ];then   
        TRYB=`zenity --entry --title "Tryb wyszukiwania" --text "Wpisz 'katalogi' / 'k' aby wyszukwać tylko katalogi lub 'pliki' / 'p' aby wyszukać tylko pliki"`
        if [ "$TRYB" ];then
            if [ "$TRYB" = "katalogi" -o "$TRYB" = "k" ];then
                PTRYB="-type d" 
            elif [ "$TRYB" = "pliki" -o "$TRYB" = "p" ];then
                PTRYB="-type f" 
            else
                zenity --error --text "Błędny tryb \"$TRYB\""
                
                PTRYB=""
            fi
        fi
    elif [ "$INPUT" = "4" ];then   
        zenity --question --title "Tylko wykonywalne" --text "Wyszukać tylko pliki wykonywalne / katalogi, które można przeglądać (wg. uprawnień tego uzytkownika) ?"
        WYK="$?"
        if [ "$WYK" = "0" ];then
            PWYK="-executable"
        else
            PWYK=""
        fi
    elif [ "$INPUT" = "5" ];then   
        PRAWA=`zenity --entry --title "Prawa dostępu" --text "Wpisz prawa zestaw praw dostępu dla wyszukiwanych plików / folderów. Uzyj 'u=' dla tego uzytkownika, 'g=' dla grupy lub 'o=' dla pozostałych"`
        if [ "$PRAWA" ];then
            PPRAWA="-perm -$PRAWA"
        else
            PPRAWA=""
        fi
    elif [ "$INPUT" = "6" ];then   
        echo "6"
    elif [ "$INPUT" = "7" ];then  
        if [ -n "$(find $PKATALOG $PNAZWA $PTRYB $PWYK $PPRAWA)" ];then
            find $PKATALOG $PNAZWA $PTRYB $PWYK $PPRAWA | zenity --text-info --title "Znalezione pliki"
        else
            zenity --error --text "Nic nie znaleziono"
            zenity --list --column "Opcja:" --column "Wartość" "$TEKST_0O1" "$NAZWA" "$TEKST_0O2" "$KATALOG" "$TEKST_0O3" "$TRYB" "$TEKST_0O4" "$WYK" "$TEKST_0O5" "$PRAWA"
        fi

    elif [ "$INPUT" = "9" ];then
        TEKST_O1="$TEKST_0O1 $NAZWA"
        TEKST_O2="$TEKST_0O2 $KATALOG"
        TEKST_O3="$TEKST_0O3 $TRYB"
        if [ "$WYK" ];then        
            TEKST_O4="$TEKST_0O4 tak"
        else
            TEKST_O4="$TEKST_0O4 nie"
        fi
        TEKST_O5="$TEKST_0O5 $PRAWA"
    else
        zenity --warning --text "Nieznane polecienie $INPUT"
    fi


    INPUT=`zenity --list --column="Nr" --column="Opcja" --width=250 --height=400 1 "$TEKST_O1" 2 "$TEKST_O2" 3 "$TEKST_O3" 4 "$TEKST_O4" 5 "$TEKST_O5" 6 "$TEKST_0O6" 7 "$TEKST_0O7" 8 "$TEKST_0O8" 9 "> Aktualizuj podgląd" `
done


