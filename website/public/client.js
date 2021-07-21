console.log('Client-side code running');

// HTML text element
const mp = {
    0 : "NONE",
    1 : "LOW",
    2 : "MID",
    3 : "HIGH",
};

// Tailwindcss class for HTML element
const arr = [
    "bg-gray-400",
    "bg-green-400",
    "bg-yellow-400",
    "bg-red-400"
];

let count = 0;

// Selecting the HTML elements in focus(i.e will be changed in future)
const laneOne = document.getElementById('lane-one');
const laneTwo = document.getElementById('lane-two');

// Check for new data every second
setInterval(() => {
    // url (PUBLIC) 
    let url = "https://api.thingspeak.com/channels/1418746/feeds/last.json";

    var value;

    // API call async function
    fetch(url).then(function(response) {
        response.text().then(function(text) {
            value = JSON.parse(text);
            
            // console.log(value);
            
            // Removing the pervious HTML element's class
            for(let i = 0; i < arr.length; i++){
                if (laneOne.classList.contains(arr[i])) {
                    laneOne.classList.remove(arr[i]);
                };
            }
            for(let i = 0; i < arr.length; i++){
                if (laneTwo.classList.contains(arr[i])) {
                    laneTwo.classList.remove(arr[i]);
                };
            }
            
            // value['field1'], value['field2']
            // Adding class and changing HTML element data
            laneOne.classList.add(arr[value['field1']]);
            laneTwo.classList.add(arr[value['field2']]);
            laneOne.innerHTML = mp[value['field1']];
            laneTwo.innerHTML = mp[value['field2']];
        });
    });


    // DEBUGGING CODE
    // switch (count%3) {
    //     case 0:
    //         laneOne.classList.add(arr[count%3]);
    //         laneTwo.classList.add(arr[count%3]);
    //         laneOne.innerHTML = mp[count%3];
    //         laneTwo.innerHTML = mp[count%3];
    //         break;
    //     case 1:
    //         laneOne.classList.add(arr[count%3]);
    //         laneTwo.classList.add(arr[count%3]);
    //         laneOne.innerHTML = mp[count%3];
    //         laneTwo.innerHTML = mp[count%3];
    //         break;
    //     case 2:
    //         laneOne.classList.add(arr[count%3]);
    //         laneTwo.classList.add(arr[count%3]);
    //         laneOne.innerHTML = mp[count%3];
    //         laneTwo.innerHTML = mp[count%3];
    //         break;
    //     default:
    //         break;
    // }
    // count++;
}, 1000);