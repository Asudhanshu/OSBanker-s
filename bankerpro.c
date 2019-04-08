#include<stdio.h>
#include<stdbool.h>
int P = 5;
int R = 4;

// Function to find the Requirement of each process
void processRequirement(int Requirement[P][R], int max[P][R],int allot[P][R])
{
    // Calculating Requirement of each P
    for (int i = 0 ; i < P ; i++)
        for (int j = 0 ; j < R ; j++)
            Requirement[i][j] = max[i][j] - allot[i][j];
}
// Function to find the system is in safe state or not
bool checksafeornot(int processes[], int avail[], int max[][R],int allot[][R])
{
    int Requirement[P][R];

    // Function to calculate Requirement matrix
    processRequirement(Requirement, max, allot);

    // Mark all processes as infinish
    bool finish[P];
    for (int i = 0; i < P; i++)
  {
       finish[i]= 0;
  }
    // To store safe sequence
    int safeSequence[P];
    // Make a copy of available resources
    int work[R];
    for (int i = 0; i < R ; i++)
        work[i] = avail[i];
    // While all processes are not finished
    // or system is not in safe state.
    int count = 0;
    while (count < P)
    {
        /* Find a process which is not finish and
        whose Requirements can be satisfied with current
         work[] resources.*/
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0)
            {
                // Check if for all resources of
                // current P Requirement is less
                // than work
                int j;
                for (j = 0; j < R; j++)
                    if (Requirement[p][j] > work[j])
                        break;

                // If all Requirements of p were satisfied.
                if (j == R)
                {
                    // Add the allocated resources of
                    // current P to the available/work
                    // resources i.e.free the resources
                    for (int k = 0 ; k < R ; k++)
                        work[k] += allot[p][k];

                    // Add this process to safe sequence.
                    safeSequence[count++] = p;

                    // Mark this p as finished
                    finish[p] = 1;

                    found = true;
                }
            }
        }

        // If we could not find a next process in safe
        // sequence.
        if (found == false)
        {
            printf("System is not in safe state");
            return false;
        }
    }
    printf("System is in safe state.\nSafe sequence is: ");
    for (int i = 0; i < P ; i++)
        printf("%d ",safeSequence[i]," ");

    return true;
}
int main()
{
    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {1,5,2,0};
    int max[][4] = {{0,0,1,2},{1,7,5,0},{2,3,5,6},{0,6,5,2},{0,6,5,6}};
    int allot[][4] = {{0,0,1,2},{1,0,0,0},{1,3,5,4},{0,6,3,2},{0,0,1,4}};
    checksafeornot(processes, avail, max, allot);

    return 0;
}
