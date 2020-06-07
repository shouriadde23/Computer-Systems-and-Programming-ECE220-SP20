#include <stdlib.h>
#include <stdio.h>

/* 
 * Your code is included as part of this file.
 */
#include "prog5.h"

void print_sol() {
    for(int i = 0; i < 4 ; ++i) {
        printf("%s ", solutions[i]);
    }
    printf("\n");
}



//Runs some unit tests for each function
//Indicates pass or fail 
//Input argument should indicate set_seed (0), start_game (1) or make_guess (2)
int main (int argc, char *argv[] ){

  if (argc == 1){

    printf("Need test No, 0 for set_seed, 1 for start_game, 2 for make_guess\n");
    return 0;
  }
  int command;
  int score = 0;
  sscanf(argv[1],"%d",&command);
  //Test set seed
  if (command == 0){
    printf("*****Testing set_seed:\n");
    int ret = set_seed("what?");
    int ret2 = set_seed("12321");
    if(ret==0 && ret2==1){
      printf("*****set_seed return value: PASS\n");
      score = score+10;
    }else{
      printf("*****set_seed return value: FAIL\n");
    }
    //Check if random number generation correct
    set_seed("12325");
    int test = rand();
    if (test == 18534142){
      printf("*****set_seed call srand: PASS\n");
      score = score+10;
    }else{
      printf("*****set_seed call srand: FAIL\n");
    }
    printf("%d\n",score);
    return score;
  }

  //Test start game
  if (command == 1){
    printf("*****Testing start_game:\n");
    set_seed("12325"); 
    char* ans[] = {"Lando", "C-3PO", "R2-D2", "Padme"};
    start_game();

    if(guess_number == 1 && max_score == -1){
      printf("*****start_game initialization: PASS\n");
      score = score+5;
    } else {
      printf("*****start_game initialization: FAILED\n");
    }

    unsigned flag = 0;
    for (int i = 0; i < 4; i++) { 
      int result = strcmp(ans[i], solutions[i]);
      flag |= result;
      if(result){ 
        printf("index: %d golden: %s yours: %s\n", i, ans[i], solutions[i]);
      }
    }
    if(!flag){
      printf("*****start_game output: PASS\n");
      score = score+15;
    } else {
      printf("*****start_game ouput: FAIL\n");
    }
    printf("%d\n",score);
    return score;

  }

  //Test Make guess
  //Test return value     
  //Test two different guesses
  if (command == 2){
    printf("*****Testing make_guess output:\n");
    srand(12325);

    start_game();
    int ret = make_guess("blahblah");
    if (ret==0){
      printf("*****make_guess return value: PASS\n");
      score +=5;
    }else{ 
      printf("*****make_guess return value: FAIL \n");
    }

    ret = make_guess("Lando C-3PO Vader R2-D2");
    if (ret== 1 && max_score == 2100){
      printf("*****make_guess test1-1: PASS\n");
      score +=6;
    }else{ 
      printf("*****make_guess test1-1: FAIL \n");
    }
    ret = make_guess("Lando C-3PO R2-D2 Padme");

    if (ret== 2 && max_score == 4000){
      printf("*****make_guess test1-2: PASS\n");
      score +=6;
    }else{
      printf("*****make_guess test1-2: FAIL \n");
    }


    srand(12388);
    start_game();

    ret = make_guess("Lando R2-D2 C-3PO");
    if (ret == 0){
      printf("*****make_guess test2-1: PASS\n");
      score +=5;
    }else{
      printf("*****make_guess test2-1: FAIL \n");
    }

    ret = make_guess("Dooku Dooku Vader Jabba");
    if (ret == 1 && max_score == 400){
      printf("*****make_guess test2-2: PASS\n");
      score +=6;
    }else{
      printf("*****make_guess test2-2: FAIL \n");
    }


    ret = make_guess("Dooku Dooku Dooku Dooku");
    if (ret == 1 && max_score == 2000){
      printf("*****make_guess test3-1: PASS\n");
      score +=6;
    }else{
      printf("*****make_guess test3-1: FAIL \n");
    }

    ret = make_guess("Vader Jabba Dooku Dooku");
    if (ret == 2 && max_score == 4000){
      printf("*****make_guess test3-2: PASS\n");
      score +=6;
    }else{
      printf("*****make_guess test3-2: FAIL \n");  
    }
    printf("%d\n",score);    
    return score;


  }
  return 0;
}

