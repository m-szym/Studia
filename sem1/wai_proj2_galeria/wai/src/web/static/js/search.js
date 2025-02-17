function insert_img(image_rec)
{
    //var img_tag_text = '<img href="' + image_rec['thl-src'] + '" />';
    document.getElementById("search_results").insertAdjacentHTML("beforeend", image_rec);
}


function start_search()
{
    document.getElementById("search_results").remove();
    document.getElementById("search_res").insertAdjacentHTML("beforeend", '<div id="search_results"></div>')

    var phrase = document.getElementById('query').value;
    var url = '/search?q=' + phrase;
    fetch(url).then(res => res.json()).then(data => data.forEach(e=>insert_img(e)))
}



async function update()
{
    var res = await start_search();
    res.forEach(insert_img(element));
}
