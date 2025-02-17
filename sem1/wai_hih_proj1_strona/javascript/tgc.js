//  ! nie używane - inline script !
//  obsługa zewnętrznego pluginu tagcloud 
//  WYMAGANIA PROJEKTOWE:
//      -  gotowy obcy przykład użycia JQuery


$.fn.tagcloud.defaults = {
    size: {start: 14, end: 18, unit: 'pt'},
    color: {start: '#cde', end: '#f52'}
  };

$(function () {
    $('#tagcloud a').tagcloud();
  });
        