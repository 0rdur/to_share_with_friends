#include <stdio.h>

//i moved all variables here so that they are treated as global. other wise the func cannot read them. idk why..
 char ch, a='1', b='2', c='3', d='4', e='5', f='6', g='7', h='8', i='9';
    int s,l,t;



// here i added the board printing func so that we can call it anytime we need(before turns,draw,win,lose)
  void board()
    { 
 printf ("\nBoard: \n");
                int r;
                for (r=1; r<=3; r++) {



                    if ( r==1 ) {
                        printf ("\n %c | %c | %c \n", a, b, c);
                        printf ("----------\n"); }

                    else if ( r==2 ) {
                        printf (" %c | %c | %c \n", d, e, f);
                        printf ("----------\n"); }

                    else if ( r==3 ) {
                        printf (" %c | %c | %c \n", g, h, i);
                         }
                }


         
    }
//func ends
void main()
{
   
    printf ("Who'll start first, Human or Bot?\n1. Human\n2. Bot\nEnter choice (1-2): ");
    scanf ("%d", &s);

    printf ("\nChoose Difficulty:\n1. Easy\n2. Medium\n3. Hard\nEnter Choice (1-3): ");
    scanf ("%d", &l);
    printf ("\n");

    for (t=1; t<=10; t++) { //i made it 10 cuz the draw condition is if(t>9) but in for(t<=9) it can never be 9. and the board doesnt get displayed

                 board(); //called the made functions, i also called it to display results
                           

                    printf ("\n#TURN: %d\n", t);


                    int u=0;

                    if (( s==1 && t%2!=0) || (s==2 && t%2==0)) {
                        u=1; }

                    if ( u==1 ) {

                            printf ("\nPlayer, enter a position (1-9): ");
                            scanf (" %c", &ch);

                            if (ch=='1' && a=='1')
                                a= 'X';
                            else if ( ch=='2' && b=='2' )
                                b= 'X';
                            else if ( ch=='3' && c=='3' )
                                c= 'X';
                            else if ( ch=='4' && d=='4' )
                                d= 'X';
                            else if ( ch=='5' && e=='5' )
                                e= 'X';
                            else if ( ch=='6' && f=='6' )
                                f= 'X';
                            else if ( ch=='7' && g=='7')
                                g= 'X';
                            else if ( ch=='8' && h=='8')
                                h= 'X';
                            else if ( ch=='9' && i=='9')
                                i= 'X';
                            else {

                                printf ("\nInvalid Position\n");

                                t--;

                            }
                    }




                    else {


                        printf ("\nBot's turn..\n");

                        if ( l==1 ) {
                            if ( a=='1' )
                                a= 'O';
                            else if ( b=='2' )
                                b= 'O';
                            else if ( c=='3' )
                                c= 'O';
                            else if ( d=='4' )
                                d= 'O';
                            else if ( e=='5' )
                                e= 'O';
                            else if ( f=='6' )
                                f= 'O';
                            else if ( g=='7' )
                                g= 'O';
                            else if ( h=='8' )
                                h= 'O';
                            else if ( i=='9' )
                                i= 'O';

                        }
                        else if ( l==2 ) {

                            if ( (( a=='X' && c=='X' ) || ( e=='X' && h=='X' )) && b=='2' )
                                b= 'O';
                            else if ((( d=='X' && f=='X' ) || ( b=='X' && h=='X')) && e=='5' )
                                e= 'O';
                            else if (( ( g=='X' && i=='X' ) || ( b=='X' && e=='X')) && h=='8' )
                                h= 'O';
                            else if ((( a=='X' && b=='X') || ( f=='X' && i=='X')) && c=='3' )
                                c= 'O';
                            else if ((( d=='X' && e=='X') || ( c=='X' && i=='X')) && f=='6' )
                                f= 'O';
                            else if ((( g=='X' && h=='X') || ( c=='X' && f=='X')) && i=='9' )
                                i= 'O';
                            else if ((( b=='X' && c=='X') || ( d=='X' && g=='X')) && a=='1' )
                                a= 'O';
                            else if ((( e=='X' && f=='X') || ( a=='X' && g=='X')) && d=='4' )
                                d= 'O';
                            else if ((( a=='X' && d=='X') || ( h=='X' && i=='X')) && g=='7' )
                                g= 'O';
                            else {

                                if (e == '5')       e = 'O';

                                else if (a == '1')  a = 'O';

                                else if (b == '2')  b = 'O';

                                else if (c == '3')  c = 'O';

                                else if (d == '4')  d = 'O';

                                else if (f == '6')  f = 'O';

                                else if (g == '7')  g = 'O';

                                else if (h == '8')  h = 'O';

                                else if (i == '9')  i = 'O';
                            }
                        }

                        else if ( l==3 ) {

                          //here i added this block to make it so that the bot tries to win. its simply blocking code block just the X's replaced with O
                            if ((( a=='O' && c=='O' ) || ( e=='O' && h=='O' )) && b=='2' )
                                b= 'O';
                            else if ((( d=='O' && f=='O' ) || ( b=='O' && h=='O') || ( c=='O' && g=='O' ) || ( a=='O' && i=='O' ))
                                      && e=='5' )
                                e= 'O';
                            else if ((( g=='O' && i=='O' ) || ( b=='O' && e=='O')) && h=='8' )
                                h= 'O';
                            else if ((( a=='O' && b=='O') || ( f=='O' && i=='O') || ( e=='O' && g=='O' ))&& c=='3' )
                                c= 'O';
                            else if ((( d=='O' && e=='O') || ( c=='O' && i=='O')) && f=='6' )
                                f= 'O';
                            else if ((( g=='O' && h=='O') || ( c=='O' && f=='O') || ( e=='O' && a=='O' )) && i=='9' )
                                i= 'O';
                            else if ((( b=='O' && c=='O') || ( d=='O' && g=='O') || ( e=='O' && i=='O' )) && a=='1' )
                                a= 'O';
                            else if ((( e=='O' && f=='O') || ( a=='O' && g=='O')) && d=='4' )
                                d= 'O';
                            else if ((( a=='O' && d=='O') || ( h=='O' && i=='O') || ( e=='O' && c=='O' )) && g=='7' )
                                g= 'O';
                             //winning block ends here

                            else if ((( a=='X' && c=='X' ) || ( e=='X' && h=='X' )) && b=='2' )
                                b= 'O';
                            else if ((( d=='X' && f=='X' ) || ( b=='X' && h=='X') || ( c=='X' && g=='X' ) || ( a=='X' && i=='X' ))
                                      && e=='5' )
                                e= 'O';
                            else if ((( g=='X' && i=='X' ) || ( b=='X' && e=='X')) && h=='8' )
                                h= 'O';
                            else if ((( a=='X' && b=='X') || ( f=='X' && i=='X') || ( e=='X' && g=='X' ))&& c=='3' )
                                c= 'O';
                            else if ((( d=='X' && e=='X') || ( c=='X' && i=='X')) && f=='6' )
                                f= 'O';
                            else if ((( g=='X' && h=='X') || ( c=='X' && f=='X') || ( e=='X' && a=='X' )) && i=='9' )
                                i= 'O';
                            else if ((( b=='X' && c=='X') || ( d=='X' && g=='X') || ( e=='X' && i=='X' )) && a=='1' )
                                a= 'O';
                            else if ((( e=='X' && f=='X') || ( a=='X' && g=='X')) && d=='4' )
                                d= 'O';
                            else if ((( a=='X' && d=='X') || ( h=='X' && i=='X') || ( e=='X' && c=='X' )) && g=='7' )
                                g= 'O';
                            else {

                                if (e == '5')       e = 'O';

                                else if (a == '1')  a = 'O';

                                else if (b == '2')  b = 'O';

                                else if (c == '3')  c = 'O';

                                else if (d == '4')  d = 'O';

                                else if (f == '6')  f = 'O';

                                else if (g == '7')  g = 'O';

                                else if (h == '8')  h = 'O';

                                else if (i == '9')  i = 'O';
                            }

                        }


                    }
                    if ( ( a=='X' && b=='X' && c=='X' ) || ( d=='X' && e=='X' && f=='X' ) || ( g=='X' && h=='X' && i=='X' ) || ( a=='X' && e=='X' && i=='X' )
                            || ( c=='X' && e=='X' && g=='X' ) || ( a=='X' && d=='X' && g=='X' ) || ( b=='X' && e=='X' && h=='X' ) || ( c=='X' && f=='X' && i=='X' ) ) {


                            printf ("\nPlayer has won!\n");
                            board();
                            break; }

                    else if ( ( a=='O' && b=='O' && c=='O' ) || ( d=='O' && e=='O' && f=='O' ) || ( g=='O' && h=='O' && i=='O' ) || ( a=='O' && e=='O' && i=='O' )
                            || ( c=='O' && e=='O' && g=='O' ) || ( a=='O' && d=='O' && g=='O' ) || ( b=='O' && e=='O' && h=='O' ) || ( c=='O' && f=='O' && i=='O' )) {

                            printf ("\nBot has won!\n");
                            board();
                            break; }

                    else if ( t>9 ){

                            printf ("\nIt's a draw!\n ");
                            board();
                            break; }




    }

}
