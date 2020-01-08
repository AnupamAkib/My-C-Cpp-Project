#include<stdio.h>
#include<string.h>

int main(){
    int total_runs=0, over_runs=0, wickets_fall=0, total_over, total_over_counter, ball_counter, no_ball_flag=0;
    char individual_runs[5]; // an char array for taking ball by ball runs
    float run_rate;

    printf("CRICKET SCORE CALCULATOR PROJECT for Structured Programming Course\n");
    printf("------------------------------------------------------------------\n");
    printf("Made by MIR ANUPAM HOSSAIN AKIB\nID: 191-35-2640 (Section B)\n");
    printf("==================================================================\n");
    printf("| Help: Enter total over first and then input ball by ball runs (ex: 1, 2, 4, 6). if it is wide ball input WD or wd,\n| for no ball NB or nb, for wicket W or w, for no ball and runs (1nb, 2nb, 4nb), for wide and runs (1wd, 2wd)\n\n");
    printf("==================================================================\n");

    printf("Enter Total Over that will be played:\n");
    scanf("%d", &total_over);
    //run a nested loop to get over and ball that is bowled
    for(total_over_counter=0; total_over_counter<total_over; total_over_counter++){
        for(ball_counter=1; ball_counter<=6; ball_counter++){
            printf("Ball %d.%d: ", total_over_counter, ball_counter);
            scanf("%s", individual_runs);
            //lets check if the run is 1, 2, 4, 6 or something else
            if(strcmp(individual_runs, "0")==0){
                over_runs=over_runs+0;
                no_ball_flag=0; //no_ball_flag is 0. it means the bowl is not a no ball
            }
            else if(strcmp(individual_runs, "1")==0){
                //1 run is scored found
                over_runs++;
                no_ball_flag=0;
            }
            else if(strcmp(individual_runs, "2")==0){
                //double run is taken by batsman
                over_runs=over_runs+2;
                no_ball_flag=0;
            }
            else if(strcmp(individual_runs, "3")==0){
                over_runs=over_runs+3;
                no_ball_flag=0;
            }
            else if(strcmp(individual_runs, "4")==0){
                //batsman hits a four and its not a no ball.
                over_runs=over_runs+4;
                no_ball_flag=0;
            }
            else if(strcmp(individual_runs, "5")==0){
                over_runs=over_runs+5;
                no_ball_flag=0;
            }
            else if(strcmp(individual_runs, "6")==0){
                //batsman hits a six and its not a no ball.
                over_runs=over_runs+6;
                no_ball_flag=0;
            }
            else if(strcmp(individual_runs, "7")==0){
                //if 7 run is scored anyway
                over_runs=over_runs+7;
                no_ball_flag=0;
            }
            else if(strcmp(individual_runs, "wd")==0 || strcmp(individual_runs, "WD")==0){
                //bowler bowled a wide ball, so add an extra run without adding any bowl! this is how we will deal with wide or no ball.
                over_runs++;
                ball_counter--;
                if(no_ball_flag==1){
                    printf("(FREE HIT) "); //check if the previous ball was wide or not. if previous would no ball, free hit will still be there for batsman
                }
            }
            else if(strcmp(individual_runs, "nb")==0 || strcmp(individual_runs, "NB")==0){
                //bowler bowled a no ball. batsman will get a free hit in the next ball.
                no_ball_flag=1;
                printf("(FREE HIT) ");
                over_runs++;
                ball_counter--;
            }
            else if(strcmp(individual_runs, "w")==0 || strcmp(individual_runs, "W")==0){
                //a batsman is out.
                //time to check if it was a free hit ball! batsman will not out if previous ball was a no ball.
                if(no_ball_flag==0){
                    wickets_fall++;
                }
                else{
                    no_ball_flag=0;
                }
            }


            else if(strcmp(individual_runs, "1nb")==0 || strcmp(individual_runs, "1NB")==0){
                //no ball but 1 run taken by batsman as well
                no_ball_flag=1;
                printf("(FREE HIT) "); //will get a free hit
                over_runs=over_runs+2;
                ball_counter--;
            }
            else if(strcmp(individual_runs, "2nb")==0 || strcmp(individual_runs, "2NB")==0){
                //no ball but 2 run taken by batsman as well
                no_ball_flag=1;
                printf("(FREE HIT) "); //will get a free hit
                over_runs=over_runs+3;
                ball_counter--;
            }
            else if(strcmp(individual_runs, "3nb")==0 || strcmp(individual_runs, "3NB")==0){
                no_ball_flag=1;
                printf("(FREE HIT) ");
                over_runs=over_runs+4;
                ball_counter--;
            }
            else if(strcmp(individual_runs, "4nb")==0 || strcmp(individual_runs, "4NB")==0){
                no_ball_flag=1;
                printf("(FREE HIT) ");
                over_runs=over_runs+5;
                ball_counter--;
            }
            else if(strcmp(individual_runs, "6nb")==0 || strcmp(individual_runs, "6NB")==0){
                no_ball_flag=1;
                printf("(FREE HIT) ");
                over_runs=over_runs+7;
                ball_counter--;
            }
            else if(strcmp(individual_runs, "1wd")==0 || strcmp(individual_runs, "1WD")==0){
                //wide bowl but batsman taken 1 run
                over_runs=over_runs+2;
                ball_counter--;
                if(no_ball_flag==1){
                    printf("(FREE HIT) "); //checking if it was a free hit delivery
                }
            }
            else if(strcmp(individual_runs, "2wd")==0 || strcmp(individual_runs, "2WD")==0){
                //wide bowl but batsman taken 2 run
                over_runs=over_runs+3;
                ball_counter--;
                if(no_ball_flag==1){
                    printf("(FREE HIT) "); //checking if it was a free hit delivery
                }
            }
            else if(strcmp(individual_runs, "4wd")==0 || strcmp(individual_runs, "4WD")==0){
                //4 and wide. so 5 will be added
                over_runs=over_runs+5;
                ball_counter--;
                if(no_ball_flag==1){
                    printf("(FREE HIT) ");
                }
            }



            //check if an over is completed, six valid ball bowled.
            if(ball_counter==6){
                total_runs=total_runs+over_runs;
                run_rate=total_runs/(total_over_counter+1.0);
                //print total runs, run rate and last over runs
                printf("\nAfter over %d,\n Total Runs: %d/%d\n Current Run Rate: %.2f\n Last Over: %d runs\n\n", total_over_counter+1, total_runs, wickets_fall, run_rate, over_runs);
                over_runs=0;
            }
            if(wickets_fall==10){ //check if 10 wickets (maximum wickets) are fallen.
                break; //nested loop will be broken if all wickets are fallen
            }

        }
        if(wickets_fall==10){
            printf("ALL WICKETS!\n"); //printing this msg before breaking the loop
            if(ball_counter!=6){ //when all wickets down before ending an over, it will execute
                printf("\nAfter over %d.%d,\n Total Runs: %d/%d\n Last Over: %d runs\n\n", total_over_counter, ball_counter, total_runs, wickets_fall, over_runs);
            }
            break;
        }
    }
    //set the target for the other team;
    printf("___________________________\n");
    printf("TARGET: %d runs in %d overs\n", total_runs+1, total_over);
    printf("---------------------------\n");



    return 0;
}













