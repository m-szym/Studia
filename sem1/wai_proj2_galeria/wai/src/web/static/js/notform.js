chosen_images = [];

function add_or_del (img_id)
{
    if(chosen_images.includes(img_id))
    {
        for( var i = 0; i < chosen_images.length; i++)
        {  
            if ( chosen_images[i] === img_id) 
            { 
                chosen_images.splice(i, 1); 
                i--;
            }
        }
    }
    else
    {
        chosen_images.push(img_id);
    }
}

function send_post (chosen_images)
{
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "session_remember", true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify(chosen_images));
}
