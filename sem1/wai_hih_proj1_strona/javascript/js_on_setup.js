//  zmiana stylów i widzialności elementów interaktywnych, aby nie były one widoczne przy wyłączonym JS
//  WYMAGANIA PROJEKTOWE:
//      - ukrywanie nie działających elementów interaktywnych przy wyłączonym JS
//      - modyfikacja wyglądu strony

function startup () {
    document.getElementById("header").classList.add('sticky-header');
    if (document.getElementById("add_comment_form")) {
      document.getElementById("add_comment_form").style.display = "block";
      show_saved_comment();
    }
    screenTest(media);
}

const media = window.matchMedia('(max-width: 800px)');

function screenTest(query) {
  if (query.matches) {
    document.getElementById("navi").style.display = 'none';
    document.getElementById("icon1").style.display = 'flex';
    document.getElementById("icon2").style.display = 'flex';
  } else {
    document.getElementById("navi").style.display = 'block';
    document.getElementById("icon1").style.display = 'none';
    document.getElementById("icon2").style.display = 'flex';
  }
}

media.addEventListener('change', screenTest);