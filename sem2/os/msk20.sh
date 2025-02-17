#!/bin/bash


TEKST_0="Wybierz opcję wpisując jej numer"
TEKST_0O1="1. Nazwa pliku:"
TEKST_0O2="2. Katalog:"
TEKST_0O3="3. Tryb:"
TEKST_0O4="4. Tylko wykonywalne:"
TEKST_0O5="5. Prawa dostępu:"
TEKST_0O6="6. Zawartość pliku"
TEKST_0O7="7. > Szukaj"
TEKST_0O8="8. > Koniec"

TEKST_O1="$TEKST_0O1 $NAZWA"
TEKST_O2="$TEKST_0O2 $KATALOG"
TEKST_O3="$TEKST_0O3 $TRYB"
TEKST_O4="$TEKST_0O4 $WYKONYWALNE"
TEKST_O5="$TEKST_0O5 $PRAWA"

echo "$TEKST_0"
echo "$TEKST_O1"
echo "$TEKST_O2"
echo "$TEKST_O3"
echo "$TEKST_O4"
echo "$TEKST_O5"
echo "$TEKST_0O6"
echo "$TEKST_0O7"
echo "$TEKST_0O8"

read INPUT

until [ "$INPUT" = "8" ];do
    if [ "$INPUT" = "1" ];then
        echo "Podaj nazwę pliku (wielkość liter ma znaczenie) :"
        read NAZWA
        if [ "$NAZWA" ];then
            PNAZWA="-name $NAZWA"
        else
            PNAZWA=""
        fi
    elif [ "$INPUT" = "2" ];then
        echo "Podaj docelowy katalog:"
        read KATALOG
        if [ "$KATALOG" ];then
            PKATALOG=$KATALOG
        else
            PKATALOG=""
        fi
    elif [ "$INPUT" = "3" ];then   
        echo "Podaj tryb wyszukiwania"
        echo "Wpisz 'katalogi' lub 'k' aby wyszukwać tylko katalogi,"
        echo " 'pliki' lub 'p' aby wyszukać tylko pliki"
        echo "albo naciśnij ENTER, aby pozostać przy wyszukiwaniu plików I katalogów"
        read TRYB
        if [ "$TRYB" ];then
            if [ "$TRYB" = "katalogi" -o "$TRYB" = "k" ];then
                PTRYB="-type d" 
            elif [ "$TRYB" = "pliki" -o "$TRYB" = "p" ];then
                PTRYB="-type f" 
            else
                echo "Błędny tryb \"$TRYB\""
                PTRYB=""
            fi
        fi
    elif [ "$INPUT" = "4" ];then   
        echo "Wpisz 'tak' aby wyszukać tylko pliki wykonywalne i katalogi które można przeszukać"
        echo "(według uprawnień dla tego użytwkonika)"
        read WYKONYWALNE
        if [ "$WYKONYWALNE" = "tak" ];then
            PWYKONYWALNE="-executable"
        else
            PWYKONYWALNE=""
        fi
    elif [ "$INPUT" = "5" ];then   
        echo "Wpisz prawa zestaw praw dostępu dla wyszukiwanych plików / folderów:"
        echo "uzyj 'u=' dla tego uzytkownika, 'g=' dla grupy lub 'o=' dla pozostałych"
        echo "uzyj 'rwx' itp."
        read PRAWA
        if [ "$PRAWA" ];then
            PPRAWA="-perm -$PRAWA"
        else
            PPRAWA=""
        fi
    elif [ "$INPUT" = "6" ];then   
        echo "6"
    elif [ "$INPUT" = "7" ];then  
        if [ -n "$(find $PKATALOG $PNAZWA $PTRYB $PWYKONYWALNE $PPRAWA)" ];then
            find $PKATALOG $PNAZWA $PTRYB $PWYKONYWALNE $PPRAWA
        else
            echo "Nic nie znaleziono dla zapytania "
            if [ "$KATALOG" ];then
                echo "Katalog: $KATALOG"
            fi
            if [ "$NAZWA" ];then
                echo "Nazwa: $NAZWA"
            fi
            if [ "$TRYB" ];then
                echo "Tryb: $TRYB"
            fi
            if [ "$WYKONYWALNE" ];then
                echo "Tylko wykonywalne: $WYKONYWALNE"
            fi
            if [ "$PRAWA" ];then
                echo "Prawa dostępu: $PRAWA"
            fi
         fi

    elif [ "$INPUT" = "wid" ];then
        TEKST_O1="$TEKST_0O1 $NAZWA"
        TEKST_O2="$TEKST_0O2 $KATALOG"
        TEKST_O3="$TEKST_0O3 $TRYB"
        TEKST_O4="$TEKST_0O4 $WYKONYWALNE"
        TEKST_O5="$TEKST_0O5 $PRAWA"
    else
        echo "Nieznane polecienie $INPUT"
    fi
    
    echo ""
    echo "$TEKST_0"
    echo "$TEKST_O1"
    echo "$TEKST_O2"
    echo "$TEKST_O3"
    echo "$TEKST_O4"
    echo "$TEKST_O5"
    echo "$TEKST_0O6"
    echo "$TEKST_0O7"
    echo "$TEKST_0O8"
    echo ""
    echo "Podaj kolejną opcję:"
    echo ""
    read INPUT

done

