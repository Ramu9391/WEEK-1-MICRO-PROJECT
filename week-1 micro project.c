#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50

typedef struct {
    int id;
    char pName[20];
    int priority;
    int BT;
} Process;

int count = 0;

/* ---------- Utility Function ---------- */
void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

/* ---------- Add Process ---------- */
void Add(Process table[]) {
    if (count >= SIZE) {
        printf("Process table is full\n");
        return;
    }

    printf("Enter process-%d details\n", count + 1);
    printf("Enter PID: ");
    scanf("%d", &table[count].id);
    printf("Enter Process Name: ");
    scanf("%s", table[count].pName);
    printf("Enter Priority: ");
    scanf("%d", &table[count].priority);
    printf("Enter Burst Time: ");
    scanf("%d", &table[count].BT);

    count++;
}

/* ---------- Display ---------- */
void Display(Process table[]) {
    int i;
    if (count == 0) {
        printf("No processes to display\n");
        return;
    }

    printf("\nPID\tName\tPriority\tBT\n");
    for (i = 0; i < count; i++) {
        printf("%d\t%s\t%d\t\t%d\n",
               table[i].id,
               table[i].pName,
               table[i].priority,
               table[i].BT);
    }
}

/* ---------- Bubble Sort by Priority ---------- */
void BubbleSortByPriority(Process table[]) {
    int i, j, comparisons = 0, swaps = 0;
    clock_t start = clock();

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            comparisons++;
            if (table[j].priority > table[j + 1].priority) {
                swap(&table[j], &table[j + 1]);
                swaps++;
            }
        }
    }

    clock_t end = clock();
    printf("Bubble Sort (Priority) Done\n");
    printf("Comparisons: %d\nSwaps: %d\nTime: %lf seconds\n",
           comparisons, swaps, (double)(end - start) / CLOCKS_PER_SEC);
}

/* ---------- Insertion Sort by PID ---------- */
void InsertionSortByPid(Process table[]) {
    int i, j, comparisons = 0, swaps = 0;
    Process key;
    clock_t start = clock();

    for (i = 1; i < count; i++) {
        key = table[i];
        j = i - 1;

        while (j >= 0 && table[j].id > key.id) {
            comparisons++;
            table[j + 1] = table[j];
            swaps++;
            j--;
        }
        table[j + 1] = key;
    }

    clock_t end = clock();
    printf("Insertion Sort (PID) Done\n");
    printf("Comparisons: %d\nShifts: %d\nTime: %lf seconds\n",
           comparisons, swaps, (double)(end - start) / CLOCKS_PER_SEC);
}

/* ---------- Shell Sort by Burst Time ---------- */
void ShellSortByBT(Process table[]) {
    int gap, i, j, comparisons = 0, swaps = 0;
    Process temp;
    clock_t start = clock();

    for (gap = count / 2; gap > 0; gap /= 2) {
        for (i = gap; i < count; i++) {
            temp = table[i];
            for (j = i; j >= gap && table[j - gap].BT > temp.BT; j -= gap) {
                comparisons++;
                table[j] = table[j - gap];
                swaps++;
            }
            table[j] = temp;
        }
    }

    clock_t end = clock();
    printf("Shell Sort (Burst Time) Done\n");
    printf("Comparisons: %d\nShifts: %d\nTime: %lf seconds\n",
           comparisons, swaps, (double)(end - start) / CLOCKS_PER_SEC);
}

/* ---------- Linear Search by PID ---------- */
void LinearSearchByPid(Process table[]) {
    int key, i, comparisons = 0;
    clock_t start = clock();

    printf("Enter PID to search: ");
    scanf("%d", &key);

    for (i = 0; i < count; i++) {
        comparisons++;
        if (table[i].id == key) {
            clock_t end = clock();
            printf("Process Found at position %d\n", i + 1);
            printf("Comparisons: %d\nTime: %lf seconds\n",
                   comparisons, (double)(end - start) / CLOCKS_PER_SEC);
            return;
        }
    }

    clock_t end = clock();
    printf("Process Not Found\n");
    printf("Comparisons: %d\nTime: %lf seconds\n",
           comparisons, (double)(end - start) / CLOCKS_PER_SEC);
}

/* ---------- Binary Search by PID ---------- */
void BinarySearchByPid(Process table[]) {
    int key, low = 0, high = count - 1, mid, comparisons = 0;
    clock_t start = clock();

    printf("NOTE: Ensure list is sorted by PID before binary search\n");
    printf("Enter PID to search: ");
    scanf("%d", &key);

    while (low <= high) {
        mid = (low + high) / 2;
        comparisons++;

        if (table[mid].id == key) {
            clock_t end = clock();
            printf("Process Found at position %d\n", mid + 1);
            printf("Comparisons: %d\nTime: %lf seconds\n",
                   comparisons, (double)(end - start) / CLOCKS_PER_SEC);
            return;
        } else if (table[mid].id < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    clock_t end = clock();
    printf("Process Not Found\n");
    printf("Comparisons: %d\nTime: %lf seconds\n",
           comparisons, (double)(end - start) / CLOCKS_PER_SEC);
}

/* ---------- Main ---------- */
int main() {
    Process table[SIZE];
    int choice;

    while (1) {
        printf("\n1.Add Process\n2.Display\n3.Bubble Sort by Priority\n");
        printf("4.Insertion Sort by PID\n5.Shell Sort by BT\n");
        printf("6.Linear Search by PID\n7.Binary Search by PID\n8.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: Add(table); break;
            case 2: Display(table); break;
            case 3: BubbleSortByPriority(table); break;
            case 4: InsertionSortByPid(table); break;
            case 5: ShellSortByBT(table); break;
            case 6: LinearSearchByPid(table); break;
            case 7: BinarySearchByPid(table); break;
            case 8: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}

