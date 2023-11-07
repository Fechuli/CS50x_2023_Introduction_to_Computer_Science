# [Finance]()

This is the last exercise and the one that gave me the most pain along with speller.

If we divide it well though, it becomes easier than expected. 
Initially I didn't quite understand what I had to do. 
I opened the files and everything was already filled in.
Then I realized the app.py file that will be the heart of our finance operation.

## What is the goal?

To make a web page that contains frontend and backend.
By backend I mean a system for Login, Logout, Registration and use of the database.
A functional website concerning finance.
But where to start?
It would seem more logical to start with app.py but the winning strategy in my opinion is to make all the html files first and then focus on the logic.

## But with what criteria do I create the html pages?

There are two methods:

- Read the app.py file and figure out how it is divided

In this case we should look at the functions in the python file and make an html file for each function.
Consider, though, that we have to exclude those already present that will actually give us the cue to make all the others later.
So surely we know that we will need Index.html, buy.html, history.html, quote,html and sell.html.
Inside Quote there is a trap. In fact, we need an additional HTML file called quoted.html.

- Copy the structure from the example provided by Harvard

According to me, the most effective method is the one that provides you with a solid and functional structure of what you are going to do. You just need to inspect the page or view the source to have a fairly good code in front of you to draw from. This way, you have the certainty of which HTML files to use and create.

<br>

Okay, now we have our files, and we can focus on the backend.

To be honest, understanding how the program was supposed to work was a bit strange and quite tedious. But once you grasp the first function, the others become progressively easier. When you have to replicate a mechanism, everything is always a bit mysterious and difficult. I find it much better to create something from scratch that I've thought of on my own. In any case, let's not get lost in chatter and understand how this file works.

## APP.PY

There are several imports, I'll explain them when the time is right.
The constant db has been previously configured to give us access to our database `finance.db`.

I don't want to explain to you what all the functions are for. It wouldn't make sense because the mechanism is clear. Instead, I'd like to give you some hints that helped me find the solution.

First of all, documentation is crucial; the [Flask SQL](ttps://flask.palletsprojects.com/en/3.0.x/tutorial/database/) and [Flask Routing](ttps://flask.palletsprojects.com/en/3.0.x/quickstart/#routing) pages were very helpful.

Of course, ChatGPT can give you a hand, but it doesn't seem to perform at its best with this type of app. Therefore, I recommend checking check50 logs regularly. Even if you know everything is wrong, do a check. It may give you a hint about the next move.

With that said, my page is not 100% identical to the one made by the CS50 team, but I'm quite satisfied with the result.
