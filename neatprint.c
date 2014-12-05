/*
	Problem : NeatPrint

	Description :		
		
		We define the "neatness" factor, NF, of a paragraph as follows. 
		NF is the sum of  the cubes of the number of spaces at the end of 
		each line in the paragraph, except the last. The lower the sum, 
		the neater the paragraph is considered to be

		Write a program which, given a list of words in a paragraph, 
		prints them as neatly as possible, using a given line length, L.


	Solution:
		Given a list of words in the order they appear in the paragraph
		and their length, we first:

		Calculate the extra spaces of each line given the maximum length of the line:
			Extras[i][j] = the extra spaces using words i to j on a line
							where i and j are indexes of words 

		Calcualte the "neatness" factor, NF, for each word places on a line:
			NF[i][j] =  the neatness factor of words from i to j in a single line

		Finally we calculate the lowest neatness factor:
			c[j] = 0 if j = 0
				   min c[i-1] + NF[i][j] if j > 0
			c[j] = the lowest total neatness factor arranging words from 1 to j.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxString  500
#define maxLength 100
#define INF 9999999

void printSolution (int[], int);
int getNumLines (int[], int);
void getNeatnessFactor();


FILE *in, *out;
char words[maxLength][maxString];
int L, numWords = 0;
int wordLength[maxString];

int main()
{
	
	in =  fopen("input.txt", "r");
	out = fopen("output.txt", "w");
	if(in == NULL || out == NULL){
		printf("error reading files\n");
	}

	int i = 0;

	fscanf(in, "%d", &L);

	while (fscanf(in,"%s", words[i]) > 0)
	{

		wordLength[i] = strlen(words[numWords]);		
		numWords++; 
		i++;
	}
	int cubeCap[numWords];
	int pos[numWords];
	int min;

	getNeatnessFactor();	

	fclose(in);
	fclose(out);	
	return 0;
}

void getNeatnessFactor ()
{	     
 
    int i, j, k, n;
 	// extras[i][k] will have number of extra spaces if words from i 
    // to k are put in a single line       
    int extras[numWords+1][numWords+1];     

    // NF[i][j] will have cost of a line which has words from 
    // i to j
    int NF[numWords+1][numWords+1];
     

    // c[n] will have total cost of optimal arrangement of words 
    // from 1 to n    
    int c[numWords+1];
 
    // p[] is used to print the solution.  
    int p[numWords+1];
 
    
    c[0] = 0;
    for (i = 1; i <= numWords; i++)
    {
        extras[i][i] = L - wordLength[i-1]; 
        c[i] = INF;
        for (j = i, k = i+1; j <= numWords; j++, k++)
        {

        	if(k<=numWords)
        	{
            	extras[i][k] = extras[i][k-1] - wordLength[k-1] - 1;  
        	}
        	if (extras[i][j] < 0)
        	{
                NF[i][j] = INF;
        	}
            else if (j == numWords && extras[i][j] >= 0)
            {
                NF[i][j] = 0;
            }
            else
            {
                NF[i][j] = extras[i][j]*extras[i][j]*extras[i][j];                
            }                         
        }
        for (n = 1; n <= i; n++)
        {
            if (c[n-1] != INF && NF[n][i] != INF && (c[n-1] + NF[n][i] < c[i]))
            {
                c[i] = c[n-1] + NF[n][i];
                p[i] = n;                                                        
            }         
        } 

    }


    int min = c[numWords];
    fprintf(out,"%d %d\n",getNumLines(p, numWords), min);  
    printSolution(p, numWords);    
}


int getNumLines (int p[], int n)
{
    int k, i, j;
    if (p[n] == 1)
        k = 1;
    else
        k = getNumLines (p, p[n]-1) + 1;      
    return k;
}


void printSolution (int p[], int n)
{
    int k, i, j, count;
    if (p[n] > 1) printSolution (p, p[n]-1);
    
    for(i = p[n]; i<=n; i++)
    {
    	fprintf(out,"%s ", words[i-1]);
    }
    fprintf(out,"\n");        
    return;
}
