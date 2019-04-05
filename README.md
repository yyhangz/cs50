# **Yuhang's solutions to HarvardX CS50**
## Disclaimer
This repository was created on 1st April 2019, only after my submission of solutions to pset4.  
The dates of upload of all solutions up till and inclusive of pset4 are not reflective of the actual dates of completion.   
Instead, refer to table below for the detailed dates of completion of those problems.

|PSET|NAME         |DATE SUBMITTED|
|:--:|:-----------:|:------------:|
|1   |hello.c      |06-03-2019    |
|1   |/less/mario.c|07-03-2019    |
|1   |/more/mario.c|07-03-2019    |
|1   |cash.c       |09-03-2019    |
|1   |credit.c     |09-03-2019    |
|2   |caesar.c     |10-03-2019    |
|2   |vigenere.c   |10-03-2019    |
|2   |crack.c      |12-03-2019    |
|3   |whodunit.c   |14-03-2019    |
|3   |less/resize.c|17-03-2019    |
|3   |more/resize.c|18-03-2019    |
|3   |recover.c    |18-03-2019    |
|4   |hashtable    |23-03-2019    |
|4   |trie         |30-03-2019    |


## My CS50 journey
Prior to CS50, I already had some (albeit rudimentary) understanding of coding and programming: I learnt robotics and basic C in school. While it made my transition to CS50 more fluid, it was nonetheless a novel challenge for me. 

Personally, I enjoyed the lectures the most. It is hands-down the best series of lectures I have ever sat through. The content was well-organized and informative: the information delineated was sufficient for me to grasp the ideas and concepts readily, yet succinct in a way that invoked curiousity about the subjects. The lecture itself was insightful and inspiring to say the least, and I have #MADZREZPECTZ for Mr. David Malan and the whole CS50 team for making it such an enjoyable course. Props to the team!

## Memos about (some of) my solutions
1. **pset1/hello.c**
  * hello.c was my "rite of passage" that kicked off my CS50 journey, so I kinda overdid it as I was too zealous.  
  Was amazed by the whole "calling a function" thing and couldn't wait to try implementing it so I did it here.
  
2. **pset2/crack**
  * My solution to crack rubbed me the wrong way because I had to nest 5 loops (meaning to say I used multiple loops within loops).   

  * Learnt later on that there is an alternative solution of recursing a function in order to run through all the possible permutations, so I might visit this again sometime in the future.
  
3. **pset3/resize/more**
  * Resize more introduced me to the beloved SEGMENTATION FAULT, an error received when accessing memory that shouldn't be accessed. Because of the vagueness of SEGMENTATION FAULT, I was forced to be comfortable using a debugger to find the fault in my code in order to rectify it.
  
4. **pset5/homepage**
  * While pset5 only specified that html and css had to be used, I went ahead and included some JS scripts to add some flair to my webpage (and also because I don't particularly enjoy design work as much... So I procrastinated on that by working on my scripts whoops).  

  * But what really inspired me to make this memo though, was complimentlink.html. This was my first experience coding with a language other than C, and I immediately felt the difference when I did complimentlink.html. The variance in functions of the different languages, was in retrospect, something I should have paid more heed to; a function that opened a text file and read its contents was as simple as "fopen" and "fread" in C, yet caused me hours of confusion and suffering in JS as I tried to unweave the abomination of a "function" I initially scrapped together.

  * Side note: If I could, I would like to revisit and improve the script in complimentlink.html yet again. Right now, while most of the script is fairly automated and modular, like the expansion/revision of the compliments library, there is still a thorn in my flesh regarding this script. The variable for the library length has to be manually updated in the script whenever the library changes in length, so I hope to be able to take away that by using (probably) regex or by any other other means.
