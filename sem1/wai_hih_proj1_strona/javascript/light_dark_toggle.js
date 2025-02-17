//  prosta zmiana wyglądu strony przez zmianę zmiennych css
//  WYMAGANIA PROJEKTOWE:
//      - sessionStorage
//      - modyfikacja wyglądu strony

var root = document.querySelector(':root');

if (sessionStorage.getItem('light_dark_mode') == null)
    sessionStorage.setItem('light_dark_mode', 'light');
else
    set_style();


function change_style () {
    if (sessionStorage.getItem('light_dark_mode') == 'light')
        sessionStorage.setItem('light_dark_mode', 'dark');
    else if (sessionStorage.getItem('light_dark_mode') == 'dark')
        sessionStorage.setItem('light_dark_mode', 'light');
    set_style();
}

function set_style () {
    if (sessionStorage.getItem('light_dark_mode')) {
        if (sessionStorage.getItem('light_dark_mode') == 'dark') {
            root.style.setProperty('--main-bg-color', 'black');
            root.style.setProperty('--typeface-color', 'white');
            root.style.setProperty('--stronger-typeface-color', 'white');
        }
        else if (sessionStorage.getItem('light_dark_mode') == 'light' ){
            root.style.setProperty('--main-bg-color', 'white');
            root.style.setProperty('--typeface-color', 'black');
            root.style.setProperty('--stronger-typeface-color', 'black');
        }
    }
}
    