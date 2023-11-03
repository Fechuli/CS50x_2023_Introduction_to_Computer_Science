# [Hello](https://github.com/Fechuli/CS50x_2023_Introduction_to_Computer_Science/blob/main/Weekly_1_C/Problem_Set_1/hello.c)

The first exercise as in any new programming language is clearly Hello World. 
Nothing complicated, we use the printf function to make a string appear in the console. 

# [Mario-More](https://github.com/Fechuli/CS50x_2023_Introduction_to_Computer_Science/blob/main/Weekly_1_C/Problem_Set_1/mario.c)

This is the second version of the exercise.
I already had some background with C so I felt I could solve it right away.

The exercise requires making the classic Super Mario block staircase. You will remember it for the first ever Mario level, just before reaching the final flag.
The difficulty with this second version is that a ladder and its mirrored version are required. 

In any case, to begin with, we realize three variables of integer type.
One related to spaces, one to blocks, and the last for height.

After that we ask the user for the height of our scale.
It must be no lower than one nor higher than 8 blocks. 

Okay now let's get to the tricky part.

We make a for loop that repeats for the height the user has chosen.
Inside it we graft three for loops one below the other.
The first thing we want written are the spaces. they will repeat for the height chosen by the user-the variable i that we are using for the first for loop.
After that the blocks that simply mirror the variable i.
At this point we put in two blanks regardless.
And finally the mirrored scale, we don't have to worry about the spaces anymore.

# [Credit](https://github.com/Fechuli/CS50x_2023_Introduction_to_Computer_Science/blob/main/Weekly_1_C/Problem_Set_1/credit.c)

Okay we are already starting to make things complicated.

The Credit exercise is to have the program figure out what type of credit card we are using based on the digits we enter at the 'beginning of the program.
To our rescue comes Luhn's algorithm, which does nothing more than validate the credit card number.

If the number has passed Luhn's algorithm we move on to the interesting part. 
Basically here we have a game of ifs that take into account all the possibilities that the exercise requires of us.
