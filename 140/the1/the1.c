#include <stdio.h>

void task1_assembly(void);
void task2_planes(void);
int helper(int , int, int [], int, int);
int helper2(int, int, int [], int, int);

int main() {
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        task1_assembly();
    } else if (choice == 2) {
        task2_planes();
    }

    return 0;
}

void task1_assembly() {
    int registers[8] = {0}, num, instructions[20][3], i = 0;
    char operators[20];
    
    scanf("%d", &num);

    while (i < num) {
        scanf(" %c", &operators[i]);
        switch (operators[i]) {
            case 'A':
                scanf(" %d %d", &instructions[i][0], &instructions[i][1]);

                break;
            case 'C':
                scanf(" %d %d", &instructions[i][0], &instructions[i][1]);

                break;
            case 'D':
                scanf(" %d", &instructions[i][0]);

                break;
            case 'I':
                scanf(" %d", &instructions[i][0]);

                break;
            case 'J':
                scanf(" %d %d %d", &instructions[i][0], &instructions[i][1], &instructions[i][2]);

                break;
            case 'S':
                scanf(" %d %d", &instructions[i][0], &instructions[i][1]);

                break;
        }
        i++;
    }

    for (i=0; i<num; i++) {
        switch(operators[i]) {
            case 'A':
                registers[instructions[i][0] - 1] += registers[instructions[i][1] - 1];

                break;
            case 'C':
                registers[instructions[i][0] - 1] = registers[instructions[i][1] - 1];

                break;
            case 'D':
                registers[instructions[i][0] - 1]--;

                break;
            case 'I':
                registers[instructions[i][0] - 1]++;

                break;
            case 'J':
                if (registers[instructions[i][0] - 1] > registers[instructions[i][1] - 1]) {
                    i = instructions[i][2] - 2;
                }

                break;
            case 'S':
                registers[instructions[i][0] - 1] = instructions[i][1];

                break;
        }
    }

    for (i=0; i<8; i++) printf("R%d: %d\n", i+1, registers[i]);
}

int helper(int land_length, int land_width, int plane_capacities[], int num_of_planes, int i) {
    if (i >= num_of_planes) return 0;

    if (land_length < plane_capacities[i] || land_width < plane_capacities[i]) return helper(land_length, land_width, plane_capacities, num_of_planes, i+1);

    if (land_length % plane_capacities[i] == 0) {
        if (land_width % plane_capacities[i] == 0) return (land_length / plane_capacities[i]) * (land_width / plane_capacities[i]);
        else return (land_length / plane_capacities[i]) + helper(land_length, land_width - plane_capacities[i], plane_capacities, num_of_planes, i);
    } else {
        if (land_width % plane_capacities[i] == 0) return (land_width / plane_capacities[i]) + helper(land_length - plane_capacities[i], land_width, plane_capacities, num_of_planes, i);
        else {
            int num1, num2, num3, min;
            num1 = 1 + helper(land_length - plane_capacities[i], plane_capacities[i], plane_capacities, num_of_planes, i) + helper(land_length, land_width - plane_capacities[i], plane_capacities, num_of_planes, i);
            num2 = 1 + helper(land_length - plane_capacities[i], land_width, plane_capacities, num_of_planes, i) + helper(plane_capacities[i], land_width - plane_capacities[i], plane_capacities, num_of_planes, i);
            num3 = helper(land_length, land_width, plane_capacities, num_of_planes, i+1);
            min = num1 > num2 ? num2 : num1;
            if (min < num3) return min;
            else return num3; 
        }
    }
}

int calculate_planes(int land_length, int land_width, int plane_capacities[], int num_of_planes) {
    return helper(land_length, land_width, plane_capacities, num_of_planes, 0);
}

void task2_planes() {
    int length, width, num_of_planes, plane_capacities[5];

    scanf("%d %d", &length, &width);

    scanf(" %d", &num_of_planes);

    for (int i=0; i<num_of_planes; i++) scanf(" %d", &plane_capacities[i]);

    printf("%d planes\n", calculate_planes(length, width, plane_capacities, num_of_planes));
}