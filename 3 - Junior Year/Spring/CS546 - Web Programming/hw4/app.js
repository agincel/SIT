/*
    Adam Gincel
    app.js
    Lab 4

    I pledge my honor that I have abided by the Stevens Honor System.
*/


const todoItems = require("./todo");
const connection = require("./mongoConnection");

let firstTaskID = "";
let secondTaskID = "";

//1. Create First Task and log it
let addFirstPost = todoItems.createTask("Ponder Dinosaurs", "Has Anyone Really Been Far Even as Decided to Use Even Go Want to do Look More Like?");

let addSecondPost = addFirstPost.then((createdTask) => {
    console.log("1. Create first task and log it.");
    firstTaskID = createdTask._id;
    console.log(createdTask);

    //2. Create second task
    console.log("\n\n\n2. Create second task.");
    return todoItems.createTask("Play Pokemon with Twitch TV", "Should we revive Helix?");
});

//3. query all tasks and log them
let printingAllPosts = addSecondPost.then((createdTask) => {
    secondTaskID = createdTask._id;
    console.log("\n\n\n3. Query all tasks and log them:");

    return todoItems.getAllTasks().then((allPosts) => {
           console.log(allPosts); //not working yet
    });
});


//4. remove the first task
let removingFirstPost = printingAllPosts.then(() => { //remove first task
    console.log("\n\n\n4. remove the first task");


    return todoItems.removeTask(firstTaskID);
});



//5. query all tasks and log them
let printingAllPostsAgain = removingFirstPost.then(() => {
    console.log("\n\n\n5. query all tasks and log them:");
    return todoItems.getAllTasks().then((allPosts) => {
        console.log(allPosts)
    });
});

//6. Complete the remaining task
let completingSecondTask = printingAllPostsAgain.then(() => {
    console.log("\n\n\n6. complete the remaining task");
    return todoItems.completeTask(secondTaskID);
});

//7. query and log the remaining task

let lastTask = completingSecondTask.then(() => {
    console.log("\n\n\n7. Query and log the remaining task")
    return todoItems.getTask(secondTaskID).then((task) => {
        console.log(task);
        return todoItems.removeTask(secondTaskID); //remove the second task, to not leave it behind in the database
    });
});

//close the db
lastTask.catch().then(() => {
    return connection();
}).then((db) => {
    return db.close();
});





/*

let sashasFirstPost = addSasha.then((sasha) => {
    console.log("Sasha the dog has been added, now she will blog!");
    console.log(sasha);

    return posts.addPost("A Review of Bleu d'Auvergne", "It was 2014 when I was born, and it was 2014 when I received my first taste of Bleu d'Auvergne. I dined upon the delicacy at the home of my grand-papa, known as The Cheese Man for the great varieties of cheese he kept in his abode. I still do not know if the Bleu d'Auvergne was what ignited my love of cheese, or if it was the strange diet of my papa whom kept away from the starches and sugars and replaced them with cheeses and legumes. But truly, I will never forget the strange world of the first taste of Bleu d'Auvergne, to this day the greatest cheese I have ever tasted. It paired very nicely with the cheeseburger I stole from my papa's four year old cousin. No one believed him. It was the perfect crime.", sasha._id);
});

let updatingSashasFirstPost = sashasFirstPost.then((post) => {
    return posts.updatePost(post._id, "For Love of Bleu d'Auvergne", post.body, post.poster.id);
});

let removeTheFirstPostAfterUpdate = updatingSashasFirstPost.then((updatedPost) => {
    console.log("Now, the post is:");
    console.log(updatedPost);
    console.log("That's all, folks!");

    return posts.removePost(updatedPost._id);
});

let otherThingToDo = updatingSashasFirstPost.then((updatedPost) => {
    // ..
})

removeTheFirstPostAfterUpdate.catch().then(() => {
    return connection();
}).then((db) => {
    return db.close();
});
*/