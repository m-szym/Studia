//  pseudo-komentarz - dodawanie, zapisywanie, wyświetlanie i wczytywanie z pamięci lokalnej
//  przechowuje tylko 1 komentarz
//  WYMAGANIA PROJEKTOWE: 
//      - localStorage
//      - tworzenie i dodawanie węzła 
//      - modyfikacja treści strony

function add_comment () {
    if (username && comment_text) {
        var new_comment = new Object();
        new_comment["username"] = document.getElementById("username").value;
        new_comment["comment_text"] = document.getElementById("comment_text").value;

        print_comment(new_comment);
        save_comment(new_comment);
    }
}

function print_comment (comment) {
    var new_comment = document.createElement("div");

    const new_comment_header = document.createElement("h4");
    new_comment_header.append(comment["username"]);

    const new_comment_text = document.createElement("p");
    new_comment_text.append(comment["comment_text"]);

    new_comment.append(new_comment_header, new_comment_text);
    new_comment.classList.add("grid-item");

    document.getElementById("comment_section").appendChild(new_comment);
} 

function save_comment (comment_to_save) {
    stringified_comment_to_save = JSON.stringify(comment_to_save);
    localStorage.setItem("saved_comment", stringified_comment_to_save);
}

function show_saved_comment () {
    if (saved_comment = localStorage.getItem("saved_comment")) {
        parsed_saved_comment = JSON.parse(saved_comment);
        print_comment(parsed_saved_comment);
    }   
}