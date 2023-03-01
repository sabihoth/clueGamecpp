# ECE309FinalProject-SCGD

Hello! Professor or TA, the game we chose to impliment is **Clue**, originally named **Cluedo**.
We have a makefile that includes 3 commands that will, build, run and clean the code

    >make all
    >make run
    >make clean

This will use the *inputVector.txt* file as "user input" to run a game against 4 CPU characters to completiton. If you want to run a test without using CPU characters or *inputVector.txt* file please eithier ~~remove the text included or~~ remove the whole file from the project. This will not cause any errors and will instead alow you to input your own values. 

Shown below was the README throughout the semester that I created to explain to my team how to use Git, Github and makefile. We used Discord for communication and would be happy to share logs of communication if requested. 

Enjoy!

![clue game](cluepic.png)




Hello! I have since added a Makefile, if you have never used these before you can just treat the code
as a black box as it works as is. To make the project please type

    >make all
    
This creates the .o files. you then to run the code type. I also added make run that simply runs the clueGame.o file

    >./clueGame
    >make run 
    
    
    
This runs the game and works as is
PLEASE BEFORE PUSHING CODE CLEAN DIRECTORY OF .o FILES WE DO NOT WANT A BUNCH OF THEM WITH DIFFERENT STUFF.
I have since added a gitignore which I should have done in the beginning but I'm dumb

    >make clean
    
^^^^^^ Run this cmd before pushing

Hello! to start working on my you might have to first add your SSH key

Follow these instructions below using your favorite terminal

https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account

If you have already added your SSH key to your account then you will just need to clone 
this project into a folder. I strongly recommend making a new folder 

    >mkdir ECE309Project
    
The next step is to change into this file and clone (using git) this repository

If you click on the green "Code" icon at the top right of this page and then copy the link
you can then enter the following command

    >git clone https://github.ncsu.edu/YOURNAME/ECE309FinalProject-SCGD.git
    
You now have the code cloned!
The next step is to get into this directory using 

    >cd ECE309FinalProject-SCGD

You can now start editing files as needed! When you're ready to start submitting (Committing )
The files you can use the following commands

    >git pull 
    
This gets you the latest most up-to date files
    
    >git add myFile.cpp
    >git commit -m "My comment Here"
    > git push 
    
These next 3 commands add the file to be pushed, adds a comment for the commit and then pushes the 
code to the repo
    
    
Some other useful git commands
    
    >git diff
    >git status
    >git log
    
    
 NOTE: I strongly recommend using VS-Code as it includes a terminal so using git is very easy and integrated. You're also 
 able to see all of the different commits from users
    
