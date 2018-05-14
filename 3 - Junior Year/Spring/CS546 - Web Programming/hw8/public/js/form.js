(function () {
    console.log("FORM.JS IN THE HOUSE");
    var staticForm = document.getElementById("palindrome-form");
    var errorMessage = document.getElementById("error");

    if (staticForm) {
        var textElement = document.getElementById("palindrome-text");
        var resultList = document.getElementById("results");
        
        staticForm.addEventListener("submit", function (event) {
            event.preventDefault();

            try {
                resultList.classList.add("hidden"); //hide the list while we update it
                errorMessage.classList.add("hidden");
                var text = String(textElement.value).toLowerCase();

                if (text.length == 0) {
                    errorMessage.innerHTML = "Given string was empty."
                    errorMessage.classList.remove("hidden");

                } else {
                    textElement.value = "";
                    //remove non alphanumeric characters
                    text = text.replace(/[^a-z0-9]/g, '');

                    var reverseText = text.split("").reverse().join("");

                    console.log(text + " == " + reverseText);


                    var li = document.createElement("li");
                    li.appendChild(document.createTextNode(text));
                    
                    if (text == reverseText) {
                        //we have a palindrome!
                        li.setAttribute("class", "is-palindrome");
                    } else {
                        //not a palindrome
                        li.setAttribute("class", "not-palindrome");
                    }

                    resultList.appendChild(li);
                    
                }
                resultList.classList.remove("hidden");
            } catch (e) {
                errorMessage.innerHTML = e;
                errorMessage.classList.remove("hidden");
                resultList.classList.remove("hidden");
            }

            return false; //to prevent the real submit from going through
        });


    } else {
        console.log("Couldn't find staticForm.");
    }

})();