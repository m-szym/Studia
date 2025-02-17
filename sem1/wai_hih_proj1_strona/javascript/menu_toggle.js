//  pokazywanie i ukrywanie menu w wersji mobilnej
//  WYMAGANIA PROJEKTOWE:
//      - modyfikacja wyglądu strony

function toggle_menu () {
    var nav = document.getElementById("navi");
    if (nav.style.display == "none")
        nav.style.display = "block"
    else
        nav.style.display = "none"
}