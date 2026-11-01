#include <stdio.h> 
#include <string.h> 
#include <stdbool.h> 

struct Process { 
    int pid; 
    char name[10]; 
    int at;    
    int bt;    
    int rt;    
    int pr;    
    int ct;    
    int tat;   
    int wt;   
}; 

int main() { 
    printf("ayushmaan goyal | Section C | Roll no. 19\n "); 
    int n, choice; 
    printf("Enter number of processes: "); 
    scanf("%d", &n); 

    struct Process p[n]; 
    printf("Choose:\n"); 
    printf("1. Non-Preemptive Priority\n"); 
    printf("2. Preemptive Priority\n"); 
    printf("Enter choice: "); 
    scanf("%d", &choice); 

    for (int i = 0; i < n; i++) { 
        p[i].pid = i + 1; 
        printf("Enter Process Name for P%d: ", i + 1); 
        scanf("%s", p[i].name); 
        printf("Enter Arrival Time of %s: ", p[i].name); 
        scanf("%d", &p[i].at); 
        printf("Enter Burst Time of %s: ", p[i].name); 
        scanf("%d", &p[i].bt); 
        printf("Enter Priority of %s (lower number = higher priority): ", p[i].name); 
        scanf("%d", &p[i].pr); 
        p[i].rt = p[i].bt; 
    } 

    float total_wt = 0, total_tat = 0; 
    int completed = 0, time = 0; 
    char gantt[500] = ""; 

    if (choice == 1) { 
        // Non-Preemptive Priority  
        bool done[n]; 
        memset(done, 0, sizeof(done)); 

        while (completed < n) { 
            int idx = -1, highest_pr = 1e9; 
            for (int i = 0; i < n; i++) { 
                if (!done[i] && p[i].at <= time && p[i].pr < highest_pr) { 
                    highest_pr = p[i].pr; 
                    idx = i; 
                } 
            } 
            if (idx == -1) { 
                time++; 
                continue; 
            } 
            strcat(gantt, "| "); 
            strcat(gantt, p[idx].name); 
            strcat(gantt, " "); 

            time += p[idx].bt; 
            p[idx].ct = time; 
            p[idx].tat = p[idx].ct - p[idx].at; 
            p[idx].wt = p[idx].tat - p[idx].bt; 

            total_wt += p[idx].wt; 
            total_tat += p[idx].tat; 
            done[idx] = true; 
            completed++; 
        } 
    } 
    else if (choice == 2) { 
        // Preemptive Priority  
        int last = -1; 
        while (completed < n) { 
            int idx = -1, highest_pr = 1e9; 
            for (int i = 0; i < n; i++) { 
                if (p[i].at <= time && p[i].rt > 0 && p[i].pr < highest_pr) { 
                    highest_pr = p[i].pr; 
                    idx = i; 
                } 
            } 
            if (idx == -1) { 
                time++; 
                continue; 
            } 
            if (last != idx) { 
                strcat(gantt, "| "); 
                strcat(gantt, p[idx].name); 
                strcat(gantt, " "); 
                last = idx; 
            } 
            p[idx].rt--; 
            time++; 
            if (p[idx].rt == 0) { 
                p[idx].ct = time; 
                p[idx].tat = p[idx].ct - p[idx].at; 
                p[idx].wt = p[idx].tat - p[idx].bt; 
                total_wt += p[idx].wt; 
                total_tat += p[idx].tat; 
                completed++; 
            } 
        } 
    } 

    printf("\nGantt Chart:\n%s|\n", gantt); 
    printf("\n%-10s %-15s %-15s %-15s %-15s %-15s %-15s\n", 
           "Process", "Arrival Time", "Burst Time", "Priority", "Completion", "Turnaround", "Waiting"); 
    for (int i = 0; i < n; i++) { 
        printf("%-10s %-15d %-15d %-15d %-15d %-15d %-15d\n", 
               p[i].name, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt); 
    } 

    printf("\nAverage Waiting Time: %.2f", total_wt / n); 
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n); 

    return 0; 
}
