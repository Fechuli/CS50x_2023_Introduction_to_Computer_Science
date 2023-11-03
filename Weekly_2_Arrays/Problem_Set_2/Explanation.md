# [Readability](https://github.com/Fechuli/CS50x_2023_Introduction_to_Computer_Science/blob/main/Weekly_2_Arrays/Problem_Set_2/readability.c)

This program aims to evaluate the readability index (whatever that means). 

We create a text variable that will enclose the user's input.
The program counts the number of letters in the text. This count is based solely on the uppercase and lowercase letters of the alphabet.
The amount of letters is stored in the count_l variable, which, for the absent-minded, means count letters.

Same process for words and periods or phrases. The period is a little trickier. If for words we have to increment count_w whenever we find a space, for the period we have to consider periods, exclamation points and question marks.

The 'index calculation is given to us. It's a little formula that will take the variables and work them down to an integer da 0 a 16+.


# [Caesar](https://github.com/Fechuli/CS50x_2023_Introduction_to_Computer_Science/blob/main/Weekly_2_Arrays/Problem_Set_2/caesar.c)


Caesar's cipher is often present during cs50. We will find it several times. The exercise in question merely incorporates this cryptosystem. It is quite trivial. It moves all the letters according to a number that will be entered by the user. To understand:
if the 'user chooses 1 the letter A will become B, if he chooses 2 C and so on.

So the program starts with a check of the input. It checks whether an argument has been provided and whether the argument consists only of digits (using the only_digits function). If the input is invalid, the program prints an error message and terminates.

the rotate function takes as input a character [c] and a key [key]. It first checks whether the character is alphabetic with the isalpha function. If yes, it determines whether it is uppercase or lowercase with isupper. Based on that, it calculates the new cipher character by shifting the character ensuring that it remains in the alphabet. 


