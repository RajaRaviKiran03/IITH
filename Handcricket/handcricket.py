#HAND CRICKET

import random


from toss import match
match()

random_int = open("C:/Users/gutti/Onedrive/Desktop/Second Semester/web.txt", mode = "r")#random_int opens the file 'web.txt'
a = random_int.readlines()# a reads the lines in the file web.txt
b = list(a) #variable b is used to change the list of strings to a list of integers

for i in range(0,len(b)):
    b[i] = int(b[i])

 
#t is a variable used to take an input from the player for toss.
    
while True: 
  try:
    t = int(input("Enter the number for toss : "))
    break
  except Exception as e:
    print(e)

'''
THE USER HAS TO TAKE AN INTEGER INPUT

AND THE INTEGERS SHOULD BE IN BETWEEN 1 AND 10(Both included)

'''

while  t > 10 or t < 1:
    print("please enter a number in 1-10")
    t = int(input("Enter the number for toss : "))

#toss_choice is used to choose the toss

toss_choice = input("odd / even :")


while toss_choice != "odd" and  toss_choice != "even" : 
    print("please choose odd or even")
    toss_choice = input("odd / even : ")


#Computer_toss takes a randon input
computer_toss = random.choice(b)

#Here the total of the toss inputs is being done.

toss_total = t + computer_toss

#A list is defined so that the computer can choose

Choice = ["bat","bowl"]

#two e
toss_choose = ""
computer_choose = ""

def toss(t):
      
    #The user gives his input here
    
    computer_toss = random.choice(b)
    
    #The computer chooses it's input randomly from 1-10
    
    print("computer choice is ",computer_toss)
    
    Choice = ["bat","bowl"]
    
    toss_total = t + computer_toss
    
    if toss_choice == "even":
      print("Even is the call...")
      if toss_total%2 == 0:
        print("And even it is")
        print("You won the toss")
        global toss_choose
        toss_choose = input("Do you want to bat / bowl  : ")
        print("Player chose to ",toss_choose," first")
        while toss_choose != "bat" and toss_choose != "bowl":
          print("Please enter 'bat' or 'bowl' ")
          toss_choose = input("Do you want to bat / bowl  : ")
          print("Player chose to ",toss_choose," first")
        
      else:
        print("And Odd it is")
        global computer_choose
        computer_choose = random.choice(Choice)
        print("Computer chose to ",computer_choose," first")
        if computer_choose == "bowl":
          print("you bat first")
        else:
          print("you bowl first")
    
    else:
      if toss_total % 2 != 0:
        print(toss_choice," is the call...")
        print("And odd its is")
        toss_choose = input("do you want to bat / bowl  : ")
        while toss_choose != "bat" and toss_choose != "bowl":
          print("Please enter 'bat' or 'bowl' ")
          toss_choose = input("do you want to bat / bowl  : ")
          print("Player chose to", toss_choose," first")

      else:
        print("You lost the toss")
        computer_choose = random.choice(Choice)
        print("Computer chose to ",computer_choose," first")
        if computer_choose == "bowl":
          print("you bat first")
        else:
          print("you bowl first")



toss(t)
# 4 different variables are defined 
score = 0
user_input = 0
computer_score = 0

#Computer takes a random input
computer_input = random.choice(b)

 
 

if ((toss_choose == "bat") or (computer_choose == "bowl")):
 
  while user_input != computer_input:
    try:
      user_input =  int(input("Enter your number:"))  #The player starts batting
      
    except Exception as e:
        print("Please enter a number from 1-10(1 and 10 included)")
        continue
    if user_input > 10 or user_input < 1 :       
        print("Please enter a number from 1-10(1 and 10 included)")
        continue
    else:
        computer_input = random.choice(b)
        print("Computer's choice is ",computer_input)     #The input of the computer is given
        if user_input != computer_input :
          score += user_input
          print("your present score is ",score)     #The present score of the player is given

  else:
      print("You got out :( ") #The player had gotten out
      print("Your score =",score)
      print("Computer target =", score + 1)  #The target to the computer is given
 
      print("Now second innings starts")   #Second innings begins
      print("Try to guess computer choice :)")
 
 
  user_input = 0
 
#Computer takes the input 
  computer_input = random.choice(b)
 
 
  while score  >= computer_score :
    while user_input != computer_input :  #The computer starts batting  
      try:
        user_input = int(input("Enter your number:"))     #The player starts bowling
      except:
        print("Please enter a number from 1-10(1 and 10 included)")
        continue

      '''
      THE USER HAS TO TAKE AN INTEGER INPUT

      AND THE INTEGERS SHOULD BE IN BETWEEN 1 AND 10(Both included)

      '''

      if user_input > 10 or user_input < 1 :       
        print("Please enter a number from 1-10(1 and 10 included)")
        continue
          

        
      else:
          computer_input = random.choice(b)   #Computer chooses it's input
          print("Computer's choice is ",computer_input)
          if user_input != computer_input : #When the user and computer inputs are different 
             computer_score += computer_input
             print("computer present score is ",computer_score) # Here the present score of computer is given 

        
          if score < computer_score : 
            break    
          else :
            print("computer  needs ",score - computer_score + 1 ,"runs to win the match")
 
    else :
      print("Yayy!, Computer got out !") #Computer got out here , since both the inputs match      
      if computer_score == score :
        print("THE MATCH GOT TIED!")
      else :
 
        print("Computer lost by", score-computer_score," runs")
        print("PLAYER WON THE MATCH!")
      break
  else :
    print("Computer won the match!") #Computer won the match

    summary = ["PLAYER SCORE" , "COMPUTER SCORE"]
    runs = [score,computer_score]
    result = dict(zip(summary,runs))
    print("SUMMARY",result)
 

computer_score =0
 
if ((toss_choose == "bowl") or (computer_choose == "bat")): #If the user bowls first or the computer bats first
  while user_input != computer_input:
    try:
        
      user_input = int(input("Enter your number: ")) #Player chooses his number
    except Exception as e:
      print("Please enter a number from 1-10(1 and 10 included)")
      continue
    '''
      THE USER HAS TO TAKE AN INTEGER INPUT
      AND THE INTEGERS SHOULD BE IN BETWEEN 1 AND 10(Both included)

    '''
    if user_input > 10 or user_input < 1 :       
        print("Please enter a number from 1-10(1 and 10 included)")
        continue

    else:
        computer_input = random.choice(b)  #Computer chooses it's number
        print("Computer's choice is ",computer_input) #The choice of computer is given
        if computer_input != user_input : 
          computer_score += computer_input
          print("Prsent score of the computer score is", computer_score) #The computer's present score is given
      
  
  else:
      print("Yayy!, Computer got out! ") #The computer got out
      print("Computer's score =",computer_score)
      print("Your target =", computer_score + 1) #Target to the user is given
      print("Now second innings starts")
      print("You shall bat now. Play well!")
 

 
#The second innings start
  user_input = 0
 
 
  computer_input = random.choice(b)
 
  user_score = 0
 
  while computer_score >= user_score:
    while user_input != computer_input:
      try:
        
        user_input = int(input("Enter your number: "))
        
      except Exception as e:
        print("Please enter a number from 1-10(1 and 10 included)")
        continue

      '''
      THE USER HAS TO TAKE AN INTEGER INPUT

      AND THE INTEGERS SHOULD BE IN BETWEEN 1 AND 10(Both included)

      '''

      if user_input > 10 or user_input < 1 :       
        print("Please enter a number from 1-10(1 and 10 included)")
        continue     
        
        
      else:
        computer_input = random.choice(b)                #The computer chooses it's number
        print("Computer's choice is ",computer_input)
        if user_input != computer_input:     
          user_score += user_input
          print("your current score is ", user_score)     #The player's present score is given
      
        if computer_score < user_score:
          break
 
        else:
          print("You  need ", abs(computer_score -user_score)+1," to win the match") 
 
    else:
      print("You got out :(") 
      if computer_score == user_score:  #Match is tied
        print("THE MATCH GOT TIED!")  
      else:
        print("You've lost by ",computer_score - user_score," runs")  #The player lost the match
      break
 
  else: 
    print("CONGRATS,PLAYER WON THE MATCH!!!")      #The player won the match

    summary = ["PLAYER SCORE" , "COMPUTER SCORE"]
    runs = [user_score,computer_score]
    result= dict(zip(summary,runs))
    print("SUMMARY",result)

    
