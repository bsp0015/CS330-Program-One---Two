# CS330-Program-One---Two
This is a program that demonstrates movement behaviors and path following for my AI and Game Development Course.
The code in main.cpp is for both a Dynamic movement behavior assignment as well as a path following assignment. PA1 code is commented out at the bottom of the code; however. 

Note: After this assignment I learend about vectors which could have simplified the amount of functions and variables needed

Date completed - 2/24/22 & 2/01/22

## Assignment #1
Programming Assignment 1:  Dynamic Movement 
 
### Objective 
 
Your primary objective is to implement and test the dynamic movement update and three dynamic 
movement behaviors, Seek, Flee, and Arrive.  Your secondary (optional) objective is to learn how to 
plot your movement trajectories. 
 
### Requirements 
 
Implement the dynamic version of the Newton-Euler-1 movement update algorithm and the dynamic 
Seek, Flee, and Arrive movement behaviors.  These are all described in Chapter 3 of the Millington 
textbook and Lecture 6.  Also implement a Continue movement behavior, which does not alter a 
character’s movement at all, but simply uses the initial values.  The Continue behavior is not in the 
textbook, but it is in my R implementation.  For this assignment, the Continue character’s initial 
velocity and rotation will all be 0, so the Continue character should not move at all. 
 
Your program should output each character’s trajectory as a text file (.txt).  The output file should 
have one record per character per timestep, including a record for the initial conditions (time = 0).  
For example, for a scenario with 4 characters that runs for 50 timesteps, there should 204 records in 
the output file, in the following order.  (This list shows proper order, but not proper format for the 
output file.) character 1, timestep 0 
character 2, timestep 0 
character 3, timestep 0 
character 4, timestep 0 
character 1, timestep 1 
character 2, timestep 1 
character 3, timestep 1 
character 4, timestep 1 
... 
character 1, timestep 50 
character 2, timestep 50 
character 3, timestep 50 
character 4, timestep 50 
 
Each record should have the following 10 fields, in the order listed, and separated by commas: 
1. simulation time 
2. character id (numeric) 
3. position x (meters) 
4. position z (meters) 
5. velocity x (meters per second) 
6. velocity z (meters per second) 
7. linear acceleration x (meters per second per second) 
8. linear acceleration z (meters per second per second) 
9. orientation (radians)  
10. steering behavior code (1=Continue, 6=Seek, 7=Flee, 8=Arrive) 
11. collision status (TRUE if collided, FALSE if not collided; always FALSE for Program 1) 
 
Run your program for 50 simulated seconds with a timestep duration of 0.5 using Newton-Euler-1 
integration, i.e., 100 timesteps after initialization.  Your scenario should have four characters with 
the initial conditions in the following table.  The movement target of the Flee, Seek, and Arrive 
characters is the Continue character. 
 
 
| Character number | 1 | 2 | 3 | 4 | 
| --- | --- | ---| --- | --- |
| Character id | 2601 | 2602 | 2603 | 2604 |
| Steering behavior | Continue | Flee | Seek | Arrive | 
| Initial position | 0, 0 | -30, -50 | -50, 40 | 50, 75 | 
| Initial velocity | 0, 0 | 2, 7 | 0, 8 | -9, 4 |
| Initial orientation |0 | π / 4 | 3π / 2 | π |
| Max velocity | 0 | 8 | 8 | 10 |
| Max acceleration | 0 | 1.5 | 2 | 2 |
| Target | 0 | 1 | 1 | 1 |
| Arrival radius | 0 | 0 | 0 | 4 |
| Slowing radius | 0 | 0 | 0 | 32 |
| Time to target | 0 | 0 | 0 | 1 |

Replicate, as closely as possible, the character movement trajectories shown in the preceding image.  
You are not required to implement a trajectory plotting program yourself; I will provide three 
different plotting programs

<br>

## Assignment #2
Programming Assignment 2:  Path Following 
 
### Objective 
 
Your objective is to implement and test the dynamic Follow path behavior. 
 
### Requirements 
 
Implement and test the dynamic Follow path behavior using the “chase the rabbit” algorithm, as 
presented in the textbook (section 3.3.12) and the slides (Lecture 8), and as implemented in my 
example R code.  Note that implementing the Follow path behavior will require also implementing 
several supporting geometry functions, as described in Lecture 8 and also implemented in my 
example R code in program CS 330, Dynamic movement, 1 Support v8.r. 
 
Your implementation of Follow path should be added to your code for Program 1.  The Follow path 
behavior depends on and reuses the dynamic Seek behavior, movement update, and other 
functionality you implemented in Program 1. 
 
Your program should output each character’s trajectory as a text file (.txt).  The output file should 
have one record per character per timestep, including a record for the initial conditions (time = 0).  
The format of the output text file is the same as Program 1. 
 
Run your program for 125 simulated seconds with a time step duration of 0.5 using Newton-Euler-1 
integration.  Your scenario should have one character with these initial conditions: 
 
| Character number | 1 |
| --- | --- |
| Character id | 2701 |
| Steering behavior | Follow path |
| Initial position | 20, 95 |
| Initial velocity | 0, 0 |
| Initial orientation | 0 |
| Max velocity | 4 |
| Max acceleration | 2 |
| Path to follow | 1 |
| Path offset | 0.04 |
 
The path your character should follow has eight vertices.  From start to end, they are: 

(0, 90) (-20, 65), (20, 40), (-40, 15), (40, -10), (-60, -35), (60, -60), (0, -85) 
  
Replicate, as closely as possible, the character movement trajectory shown in the preceding image.  
You are not required to implement a trajectory plotting program yourself; I will provide three 
different plotting programs 

