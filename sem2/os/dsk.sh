#! /bin/bash

# Author : Marek Szymanski ( s193229@student.pg.edu.pl )
# Created On : 04.05.2023
# Last Modified By : Marek Szymanski ( s193229@student.pg.edu.pl )
# Last Modified On : 12.05.2023
# Version : 0.07
#
# Description : komentarz z opisem działania
#
#
# Licensed under GPL (see /usr/share/common-licenses/GPL for more details
# or contact # the Free Software Foundation for a copy)


WERSJA="0.07"
AKTUALIZACJA="12.05.2023"
TMP="/tmp"
KATALOG="$HOME/dsk_md5"
mkdir -p ~/dsk_md5


WYNIK_POROWNANIA_PROSTY=""


porownaj_2pliki() {
    PLIK_1=$1
    PLIK_2=$2

    SUMA_1=$(md5sum "$PLIK_1" | cut -d " " -f 1)
    SUMA_2=$(md5sum "$PLIK_2" | cut -d " " -f 1)

    echo "$SUMA_1"
    echo "$SUMA_2"

    if [ "$SUMA_1" = "$SUMA_2" ];then
        WYNIK_POROWNANIA_PROSTY="1"
    else
        WYNIK_POROWNANIA_PROSTY="0"
    fi
}

porownaj_plik_i_sume() {
    WYNIK_POROWNANIA_Z_SUMA=$(md5sum -c "$1")

    echo "$WYNIK_POROWNANIA_Z_SUMA"

    #if grep "OK" "$WYNIK_POROWNANIA_Z_SUMA" ;then
    if [[ "$WYNIK_POROWNANIA_Z_SUMA" == *"OK"* ]];then
        WYNIK_POROWNANIA_Z_SUMA="1"
        echo "ok"
    else
        WYNIK_POROWNANIA_Z_SUMA="0"
    fi
}

zapisz_sume() {
    PLIK_DO_ZSUMOWANIA=$1
    NAZWA=${PLIK_DO_ZSUMOWANIA##*/}
    NAZWA=${NAZWA%.*}
    echo "$NAZWA"

    md5sum "$PLIK_DO_ZSUMOWANIA" > "$KATALOG/$NAZWA.md5"
}

porownaj_2_katalogi() {
    KATALOG_1=$1
    KATALOG_2=$2

    #N=${KATALOG_1##*/}
    #echo "$N"

    rm "$TMP/2dir.md5"
    md5deep -r "$KATALOG_1" > "$TMP/2dir.md5"
      
    WYNIK_POROWNANIA_KATALOGOW=$(md5deep -r -x "$TMP/2dir.md5" "$KATALOG_2")
    if [ "$WYNIK_POROWNANIA_KATALOGOW" ];then
        #N=${KATALOG_1##*/}
        #echo "$N"
        #WYNIK_POROWNANIA_KATALOGOW=$(echo "$WYNIK_POROWNANIA_KATALOGOW" | sed "s/.*\("$N"\)/\1/g")
        WYNIK_POROWNANIA_KATALOGOW_BOOL="0"
    else
        WYNIK_POROWNANIA_KATALOGOW_BOOL="1"
    fi
}



while getopts hvp:ds:z: OPT; do
    case $OPT in
        h) 
            echo "---Pomoc---"
            echo "aby skorzystać ze skryptu w wersji graficznej nie wpisuj żadnych opcji"
            echo "Opcje uruchomienia:"
            echo "opcja -h -> pomoc"
            echo "opcja -v -> informacje o wersji"
            echo "opcja -z [plik] -> bezpośrednio zapisuje sumę kontrolną dla wybranego pliku"
            echo "opcja -s [plik z sumą md5] -> porównuje plik z sumą kontrolną zapisaną w wybranym pliku md5"
            echo "opcja -d -> bezpośrednio porównuje sumy md5 dla 2 plików podanych przez podwójne uruchomienie opcji -p [plik]"
            echo "UWAGA: bez uprzedniego, dwukrotnego użycia opcji -p [plik] opcja -d nie zadziała"
            echo "opcja -p -> pozwala podać plik do użycia w opcji -d"
            echo "UWAGA: aby podać 2 pliki należy wywołać 2 razy"
            echo "UWAGA: przechowuje TYLKO 2 plik, kolejne wywołania będą cyklicznie nadpisywać wybrane pliki"
            echo "na razie inne opcje nie są dostępne"
            exit 1
            ;;
        v) 
            echo "Wersja: $WERSJA"
            echo "Ostatnia aktualizacja: $AKTUALIZACJA"
            exit 1
            ;;
        p)
            if [ "$tPLIK_1" ] && [ "$tPLIK_2" ];then
                #tPLIK_2=""
                tPLIK_1=$OPTARG
                #echo "dwa zaj - p1 - $tPLIK_1"
            elif [ "$tPLIK_1" ];then
                tPLIK_2=$OPTARG
                #echo "drugie - $tPLIK_2"
            else
                tPLIK_1=$OPTARG
                #echo "pierwsze - $tPLIK_1"
            fi
            #echo "tp1 - $tPLIK_1"
            #echo "tp2 - $tPLIK_2"
            ;;
        d)
            if [ -f "$tPLIK_1" ] && [ -f "$tPLIK_2" ];then
                echo "$tPLIK_1"
                echo "$tPLIK_2"
                porownaj_2pliki "$tPLIK_1" "$tPLIK_2"
                echo "$WYNIK_POROWNANIA_PROSTY"
                exit 1;
            else
                echo "Nie podano dwóch poprawnych plików"
                exit 0
            fi
        
            ;;

        s)
            tPLIK=$OPTARG
            if [ -f "$tPLIK" ];then
                if [[ "$tPLIK" == *".md5" ]];then
                    porownaj_plik_i_sume "$tPLIK"
                    echo "$WYNIK_POROWNANIA_Z_SUMA"
                    exit 1
                else 
                    echo "Wybrany plik nie jest poprawnym plikiem z sumą md5."
                    exit 0
                fi
            else
                echo "Nie wybrano poprawnego pliku."
                echo "Wybrano katalog / nie podano zadnego pliku"
                exit 0
            fi
            
            ;;   
        z)
            tPLIK=$OPTARG
            echo "tp - $tPLIK optarg - $OPTARG"
            if [ -f "$tPLIK" ];then
                zapisz_sume "$tPLIK"
                exit 1
            else
                echo "Nie wybrano poprawnego pliku."
                echo "Wybrano katalog / nie podano zadnego pliku"
                exit 0
            fi
            exit 1;
            ;;   
        *) 
            echo "nie ma takiej opcji"
            exit 1
            ;;
    esac
done


INPUT=$(zenity --list --column="Nr" --column="Opcja" 1 "Porownywanie 2 plikow" 2 "Zapisywanie sumy kontrolnej" 3 "Porównanie pliku z sumą" 4 "Porównanie zawartości 2 katalogów" 8 "Wyjscie" --height 300 --width 400)

until [ "$?" = "1" ] || [ "$INPUT" = "8" ];do
    if [ "$INPUT" = "1" ];then

        PLIK1=$(zenity --file-selection)
        #echo "$PLIK1"
        #CS1=$(md5sum "$PLIK1" | cut -d " " -f 1)
        #echo "$CS1"
        #md5sum "$PLIK1" > "$KATALOG/plik1.md5"
        #echo "$CS1"
        #cat "$KATALOG/plik1.md5"


        PLIK2=$(zenity --file-selection)
        #echo "$PLIK2"
        #CS2=$(md5sum "$PLIK2" | cut -d " " -f 1)
        #echo "$CS2"


        porownaj_2pliki "$PLIK1" "$PLIK2"

        if [ "$WYNIK_POROWNANIA_PROSTY" ];then
            if [ "$WYNIK_POROWNANIA_PROSTY" = "1" ];then
                zenity --info --title "Wynik porównania" --text "Sumy kontrolne md5 zgodne. Pliki mają taką samą zawartość."  
            elif [ "$WYNIK_POROWNANIA_PROSTY" = "0" ];then
                zenity --info --title "Wynik porównania" --text "Sumy kontrolne nie są zgodne. Pliki mają różną zawartość."   
            fi        

   
            #zenity --info --title "Wynik porównania" --text "$WYNIK_POROWNANIA_PROSTY"
        fi

    elif [ "$INPUT" = "2" ];then
        
        NOWY_PLIK=$(zenity --file-selection)
        zapisz_sume "$NOWY_PLIK"
        zenity --info --title "Zapisywanie sumy kontrolnej" --text "Suma kontrolna dla $NOWY_PLIK została zapisana. Zapisane sumy znajdują się w $KATALOG"


    elif [ "$INPUT" = "3" ];then
        WYBRANY_PLIK=""
        WYBRANY_PLIK=$(zenity --file-selection --filename="$KATALOG/")
        echo "$WYBRANY_PLIK"
        if [ "$WYBRANY_PLIK" ];then
            porownaj_plik_i_sume "$WYBRANY_PLIK"

            if [ "$WYNIK_POROWNANIA_Z_SUMA" = "1" ];then
                zenity --info --title "Wynik porównania z zapisaną sumą" --text "Sumy kontrolne md5 są zgodne. Wybrany plik ma taką samą zawartość jak plik dla którego zapisano oryginalną sumę."
            else
                zenity --info --title "Wynik porównania z zapisaną sumą" --text "Sumy kontrolne md5 nie są zgodne. Wybrany plik rózni się zawartością od pliku, dla którego obliczono oryginlanie zapisaną sumę kontrolną. Jeśli jest to ten sam plik oznacza to, ze jego zawartość uległa zmianie od momentu zapisania sumy kontrolnej"
            fi
        fi

    elif [ "$INPUT" = "4" ];then
        KATALOG_1=$(zenity --file-selection --directory)
        KATALOG_2=$(zenity --file-selection --directory)

        if [ "$KATALOG_1" ] && [  "$KATALOG_2" ];then
            porownaj_2_katalogi "$KATALOG_1" "$KATALOG_2"
            #echo "$WYNIK_POROWNANIA_KATALOGOW"

            
            if [ "$WYNIK_POROWNANIA_KATALOGOW_BOOL" = "1" ];then
                #echo "$KATALOG_1 $KATALOG_2 - $WYNIK_POROWNANIA_KATALOGOW_BOOL - $WYNIK_POROWNANIA_KATALOGOW"
                zenity --info --title "Wynik porównania" --text "Sumy kontrolne md5 zgodne. Katalogi mają taką samą zawartość."  
            elif [ "$WYNIK_POROWNANIA_KATALOGOW_BOOL" = "0" ];then
                zenity --info --title "Wynik porównania" --text "Sumy kontrolne nie są zgodne. Katalogi mają różną zawartość. Różnice w zawartości znaleziono w plikach: \n $WYNIK_POROWNANIA_KATALOGOW"   
            fi     

            WYNIK_POROWNANIA_KATALOGOW=""
            WYNIK_POROWNANIA_KATALOGOW_BOOL=""


        
        fi    
    fi




    INPUT=$(zenity --list --column="Nr" --column="Opcja" 1 "Porownywanie 2 plikow" 2 "Zapisywanie sumy kontrolnej" 3 "Porównanie z zapisaną sumą" 4 "Porówywanie zawartości 2 katalogów" 8 "Wyjscie" --height 300 --width 400)
    #INPUT=$(zenity --list --column="Nr" --column="Opcja" 1 "Porownywanie 2 plikow" 8 "Wyjscie")

done

