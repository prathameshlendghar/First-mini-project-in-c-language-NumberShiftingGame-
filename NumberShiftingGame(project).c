#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//==============================COLOUR CODES COPPIED FROM INTERNET==========================================//
void red () {
  printf("\033[1;31m");                     
}
void yellow() {
  printf("\033[1;32m");
}
void cyan(){
    printf("\033[0;36m");
}
void reset () {
  printf("\033[0m");
}

// #define ANSI_COLOR_GREEN "\x1b[32m"
// #define ANSI_COLOR_RED "\x1b[31m"

//ALSO CAN BE DONE ^^ THIS WAY

//====================================GLOBAL SCOPE VARIABLES AND ARRAYS====================================//
char NameOfUser[20]="";                                         //NAME OF USER FROM MAIN FUNCTION TO STORE HERE BECAUSE IT IS USED IN DISPLAYING
int win[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};            //WINNING SITUTION ARRAY SHOULD LOOK LIKE THIS
int randomarr[16]={};                                           // HERE ELEMENTS ARE PUT BY FUNCTION DEFINED BELOW 

//======================================FILLING DEFAULT ELEMENTS(1-15)IN ARRAY ==================================//

void randomArrDefault(int randomarr[]){
  for(int i=0;i<16;i++){
    if(i<15)
      randomarr[i]=i+1;
    else
      randomarr[i]=0;                      //THIS FUNCTION IS MADE TO FILL ELEMENT IN ARRAY IN SIQUENTIAL WAY
    //printf("%d ",randomarr[i]);          //BECAUSE WE NEED TO RESET POSITION OF ELEMENTS AND ZERO EACH TIME PLAY AGAIN IS CALL
  }
}
//=================================RANDOM SHUFFLING OF AN ARRAY======================================//
void randoma(int randomarr[]){
  for(int i=0;i<=100;i++){
    srand(time(0));
    int randIndex1 = rand()%15;
    int randIndex2 = rand()%15;                                             //HERE IT IS USING TIME FUNCTION TO GENERATE RANDOM NUMBER(GET TO KNOW FROM GOOGLE)
    int temp;                                                               //%15 IS DONE TO TAKE OUT RANDOM INDEX LESS THAN 15 ONLY
    temp=randomarr[randIndex1];
    randomarr[randIndex1]=randomarr[randIndex2];
    randomarr[randIndex2]=temp;
  }
}

//==============================PRINTS THE ARRAY IN THE FORM OF MATRIX BY SHOWING 0 AS AN EMPTY SPACE=======================================//

void printingMatrix(int arr[]){
  yellow();
    printf("---------------------\n");
    for(int i=0;i<4;i++){
      for(int j=i*4;j<(i+1)*4;j++){
        if(j==i*4)
          printf("|");
        if(arr[j]==0)
          printf("%3s%+1s"," "," |");
        else
          printf("%3d%+1s",arr[j]," |");
      }
      printf("\n");
    }
    printf("---------------------\n\n");
    reset();
}

//=====================================================================//

//this function takes the input and check whether it is valid key to press or not AND ALSO PERFORMS CORRESPONDING ACTIONS

char inputChecked(int k){ 
  char inp;
  int row,column;
  column=k%4;
  row=k/4;
  printf("Enter the valid direction input:- ");
  scanf("%c",&inp);
  getchar();
  switch (inp){
    case '8':                                                   //to move number upward not space
      if(row>=0 && row<3){
          randomarr[k]=randomarr[k+4];
          randomarr[k+4]=0;
        }else{
          printf("Empty block is not present in upside of any number\n\n");
          inputChecked(k);
        }
        winningCheck(compair(randomarr,win));   
      break;
    case '4':                                                           // to move number left
      if(column>=0 && column<3){
          randomarr[k]=randomarr[k+1];
          randomarr[k+1]=0;
        }else{
          printf("Empty block is not present in left of any number\n");
          inputChecked(k);
        }
        winningCheck(compair(randomarr,win));   
        break;
    case '2':                                                          // to move number downward
      if(row<=3 && row>0){
          randomarr[k]=randomarr[k-4];
          randomarr[k-4]=0;
        }else{
          printf("Empty block is not present in downside of any number\n");
          inputChecked(k);
        }
        winningCheck(compair(randomarr,win));   
      
      break;
    case '6':                                                         // to move number right
      if(column>0 && column<=4){
          randomarr[k]=randomarr[k-1];
          randomarr[k-1]=0;
        }else{
          printf("Empty block is not present in right of any number\n");
          inputChecked(k);
        }
        winningCheck(compair(randomarr,win));   
        break;
      
    case 'e':                                                         // if end condition occurs
      cyan();
      printf("Thanks for playng %s \n\n",NameOfUser);
      reset();
      exit(0);
    default:
      getchar();
      inputChecked(k);
  }
}


//==============================THIS FUNCTION COMPAIRS WINNIG ARRAY AND RANDOM ARRAY =======================================//

int compair(int arr[],int arr1[]){
  int count=0;
  int i;
  for(i=0;i<16;i++){
    if(arr[i]==arr1[i]){
      count++;
    }
  }
  if(count==i-1)
    return 1;
  else
    return 0;
}

//=================IT IS CHECK EACH TIME THE INPUT IS GIVEN FROM USER AND PRINT MSS TO CONTINUE OR END GAME====//

void winningCheck(int check){
  char playAgain;
  if(check==1){
        printf("you won!!!\n");
        printf("Want to play again? ('y'-> yes) / ('e'->end)\n");
        //scanf("%c",&red);
        scanf("%c",&playAgain);
        getchar();
        
        if(playAgain=='y'){
          randomArrDefault(randomarr);
          randoma(randomarr);
          playing();
        }
        else if(playAgain=='e'){
          cyan();
          printf("Thanks for playng %s\n",NameOfUser);
          reset();
          exit(0);
        }
        else
          printf("wrong inp");
          exit(0);

      }
}

//========================================================================//

void playing(){
  int chances=5;
  int k,i;
  int randtemp;
  char playAgain;
  
  for(i=chances;i>=0;i--){
    if(i>0){
      system("clear");
      printf("Your chances left are %d\n",i);
      printingMatrix(randomarr);

      for(k=0;k<16;k++){                                              ///this finds the current position of 0 in the matrix
        if(randomarr[k]==0){
          break;
        }
      }
      inputChecked(k);
    }  
    else {
      system("clear");                                              //THIS ELSE IS FOR AFTER LAST CHANCE DECLARE RESULT BY PRINTING MATRIX WITH IT
      printingMatrix(randomarr);
      winningCheck(compair(randomarr,win));
      if(compair(randomarr,win)==0){
        printf("You loose!!\n");
        printf("Want to play again? ('y'-> yes) / ('e'->end)\n");
        scanf("%c",&playAgain);
        getchar();
        
        if(playAgain=='y'){
          randomArrDefault(randomarr);
          randoma(randomarr);
          playing();
        }
        else if(playAgain=='e'){
          cyan();
          printf("Thanks for playng %s\n",NameOfUser);
          reset();
          exit(0);
        }
        else
          printf("wrong input");
          exit(0);
      } 
    }
  }
}


//============================TO DISPLAY INSTRUCTION ON FIRST PAGE===================================================//

void displayInstruction(char Name[]){
    system("clear");
    cyan();
    printf("%+40s","MATRIX PUZZLE\n");
    red();
    printf("%+40s","Rules of Game\n");
    printf("1. You Can move only one step at a time By using arrow key.\n");
    reset();
    printf("See the numpad on keyboard carefully, 8 has up arrow key 2 has down arrow key and so on for 4 and 6\n");
    printf("%+8s","");
    printf("%-11s","Move up ");
    printf("%-20s",": By 8 on numpad ");
    printf("\n");
    printf("%+8s","");
    printf("%-11s","Move Down ");
    printf("%-20s",": By 2 on numpad ");
    printf("\n");
    printf("%+8s","");
    printf("%-11s","Move Left ");
    printf("%-20s",": By 4 on numpad");
    printf("\n");
    printf("%+8s","");
    printf("%-11s","Move Right ");
    printf("%-20s",": By 6 on numpad");
    printf("\n");

    red();
    printf("2. You Can move number at an empty position only.\n");
    printf("3. For each valid move : your total number of move will decrease by 1.\n");
    printf("3. winning situation : your 4*4 matrix should have elements arranged in 1-15 order.\n\n");

    reset();
    printf("%+2s","");
    printf("%-11s","WINNING SITUATION \n");
    
    printingMatrix(win);
    
    red();
    printf("5.If You want to exit you can press e .\n");
    
}


//===========================================================================================//
int main(){

    printf("Enter your name:- ");
    scanf("%s",&NameOfUser);
    displayInstruction(NameOfUser);
    reset();
    printf("Press Enter key to start the Game ");
    getchar();
    getchar();
    randomArrDefault(randomarr);
    randoma(randomarr);
    playing();
    reset();
}
//=============================================================================================//