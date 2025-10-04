#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VECTORS 26 // For vectors A-Z
Vector2D vectors[MAX_VECTORS];
int vector_defined[MAX_VECTORS] = {0}; // 0 if not defined, 1 if defined

int get_vector_index(char name) {
    if (name >= 'A' && name <= 'Z') {
        return name - 'A';
    }
    return -1; // Invalid name
}

void printVector(const char *name_str, Vector2D v) {
    printf("%s = (%.2f, %.2f)\n", name_str, v.x, v.y);
}

void display_help() {
    printf("Available commands:\n");
    printf("  create <name> <x> <y>     - Create a vector (e.g., create A 1.0 2.0)\n");
    printf("  add <name1> <name2> <res> - Add two vectors (e.g., add A B C)\n");
    printf("  sub <name1> <name2> <res> - Subtract two vectors (e.g., sub A B C)\n");
    printf("  scale <name> <scalar> <res> - Scale a vector (e.g., scale A 2.5 B)\n");
    printf("  norm <name>               - Print the norm (length) of a vector (e.g., norm A)\n");
    printf("  dot <name1> <name2>       - Print the dot product of two vectors (e.g., dot A B)\n");
    printf("  angle <name1> <name2>     - Print the angle between two vectors (e.g., angle A B)\n");
    printf("  normalize <name> <res>    - Normalize a vector (e.g., normalize A B)\n");
    printf("  print <name>              - Print a vector (e.g., print A)\n");
    printf("  list                      - List all defined vectors\n");
    printf("  cross <name1> <name2>     - Print the 2D cross product (e.g., cross A B)\n");
    printf("  project <a> <b> <res>   - Project vector a onto b (e.g., project A B C)\n");
    printf("  rotate <name> <deg> <res> - Rotate a vector by degrees (e.g., rotate A 90 B)\n");
    printf("  distance <name1> <name2>  - Print the distance between two vectors (e.g., distance A B)\n");
    printf("  help                      - Display this help message\n");
    printf("  exit                      - Exit the program\n");
}

int main() {
    char line[256];
    char cmd[50];
    char name1_char, name2_char, res_char;
    float x, y, scalar;
    int idx1, idx2, res_idx;

    printf("Vector 2D REPL. Type 'help' for commands, 'exit' to quit.\n");

    while (1) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) {
            break; // EOF
        }

        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        if (sscanf(line, "%s", cmd) == 1) {
            if (strcmp(cmd, "exit") == 0) {
                break;
            } else if (strcmp(cmd, "help") == 0) {
                display_help();
            } else if (strcmp(cmd, "create") == 0) {
                if (sscanf(line, "%*s %c %f %f", &name1_char, &x, &y) == 3) {
                    idx1 = get_vector_index(toupper(name1_char));
                    if (idx1 != -1) {
                        vectors[idx1] = createVector(x, y);
                        vector_defined[idx1] = 1;
                        printVector((char[]){toupper(name1_char), '\0'}, vectors[idx1]);
                    } else {
                        printf("Error: Invalid vector name. Use A-Z.\n");
                    }
                } else {
                    printf("Usage: create <name> <x> <y>\n");
                }
            } else if (strcmp(cmd, "add") == 0) {
                if (sscanf(line, "%*s %c %c %c", &name1_char, &name2_char, &res_char) == 3) {
                    idx1 = get_vector_index(toupper(name1_char));
                    idx2 = get_vector_index(toupper(name2_char));
                    res_idx = get_vector_index(toupper(res_char));
                    if (idx1 != -1 && idx2 != -1 && res_idx != -1 && vector_defined[idx1] && vector_defined[idx2]) {
                        vectors[res_idx] = additionVector(vectors[idx1], vectors[idx2]);
                        vector_defined[res_idx] = 1;
                        printVector((char[]){toupper(res_char), '\0'}, vectors[res_idx]);
                    } else {
                        printf("Error: Invalid vector name or undefined vector(s).\n");
                    }
                } else {
                    printf("Usage: add <name1> <name2> <result_name>\n");
                }
            } else if (strcmp(cmd, "sub") == 0) {
                if (sscanf(line, "%*s %c %c %c", &name1_char, &name2_char, &res_char) == 3) {
                    idx1 = get_vector_index(toupper(name1_char));
                    idx2 = get_vector_index(toupper(name2_char));
                    res_idx = get_vector_index(toupper(res_char));
                    if (idx1 != -1 && idx2 != -1 && res_idx != -1 && vector_defined[idx1] && vector_defined[idx2]) {
                        vectors[res_idx] = subtractVector(vectors[idx1], vectors[idx2]);
                        vector_defined[res_idx] = 1;
                        printVector((char[]){toupper(res_char), '\0'}, vectors[res_idx]);
                    } else {
                        printf("Error: Invalid vector name or undefined vector(s).\n");
                    }
                } else {
                    printf("Usage: sub <name1> <name2> <result_name>\n");
                }
            } else if (strcmp(cmd, "scale") == 0) {
                if (sscanf(line, "%*s %c %f %c", &name1_char, &scalar, &res_char) == 3) {
                    idx1 = get_vector_index(toupper(name1_char));
                    res_idx = get_vector_index(toupper(res_char));
                    if (idx1 != -1 && res_idx != -1 && vector_defined[idx1]) {
                        vectors[res_idx] = scaleVector(vectors[idx1], scalar);
                        vector_defined[res_idx] = 1;
                        printVector((char[]){toupper(res_char), '\0'}, vectors[res_idx]);
                    } else {
                        printf("Error: Invalid vector name or undefined vector.\n");
                    }
                } else {
                    printf("Usage: scale <name> <scalar> <result_name>\n");
                }
            } else if (strcmp(cmd, "norm") == 0) {
                if (sscanf(line, "%*s %c", &name1_char) == 1) {
                    idx1 = get_vector_index(toupper(name1_char));
                    if (idx1 != -1 && vector_defined[idx1]) {
                        printf("|%c| = %.2f\n", toupper(name1_char), normVector(vectors[idx1]));
                    } else {
                        printf("Error: Invalid vector name or undefined vector.\n");
                    }
                } else {
                    printf("Usage: norm <name>\n");
                }
            } else if (strcmp(cmd, "dot") == 0) {
                if (sscanf(line, "%*s %c %c", &name1_char, &name2_char) == 2) {
                    idx1 = get_vector_index(toupper(name1_char));
                    idx2 = get_vector_index(toupper(name2_char));
                    if (idx1 != -1 && idx2 != -1 && vector_defined[idx1] && vector_defined[idx2]) {
                        printf("%c . %c = %.2f\n", toupper(name1_char), toupper(name2_char), dotProduct(vectors[idx1], vectors[idx2]));
                    } else {
                        printf("Error: Invalid vector name or undefined vector(s).\n");
                    }
                } else {
                    printf("Usage: dot <name1> <name2>\n");
                }
            } else if (strcmp(cmd, "angle") == 0) {
                if (sscanf(line, "%*s %c %c", &name1_char, &name2_char) == 2) {
                    idx1 = get_vector_index(toupper(name1_char));
                    idx2 = get_vector_index(toupper(name2_char));
                    if (idx1 != -1 && idx2 != -1 && vector_defined[idx1] && vector_defined[idx2]) {
                        printf("Angle between %c and %c: %.2f degrees\n", toupper(name1_char), toupper(name2_char), angleBetwen(vectors[idx1], vectors[idx2]));
                    } else {
                        printf("Error: Invalid vector name or undefined vector(s).\n");
                    }
                } else {
                    printf("Usage: angle <name1> <name2>\n");
                }
            } else if (strcmp(cmd, "normalize") == 0) {
                if (sscanf(line, "%*s %c %c", &name1_char, &res_char) == 2) {
                    idx1 = get_vector_index(toupper(name1_char));
                    res_idx = get_vector_index(toupper(res_char));
                    if (idx1 != -1 && res_idx != -1 && vector_defined[idx1]) {
                        vectors[res_idx] = normalizeVector(vectors[idx1]);
                        vector_defined[res_idx] = 1;
                        printVector((char[]){toupper(res_char), '\0'}, vectors[res_idx]);
                    } else {
                        printf("Error: Invalid vector name or undefined vector.\n");
                    }
                } else {
                    printf("Usage: normalize <name> <result_name>\n");
                }
            } else if (strcmp(cmd, "print") == 0) {
                if (sscanf(line, "%*s %c", &name1_char) == 1) {
                    idx1 = get_vector_index(toupper(name1_char));
                    if (idx1 != -1 && vector_defined[idx1]) {
                        printVector((char[]){toupper(name1_char), '\0'}, vectors[idx1]);
                    } else {
                        printf("Error: Invalid vector name or undefined vector.\n");
                    }
                } else {
                    printf("Usage: print <name>\n");
                }
            } else if (strcmp(cmd, "list") == 0) {
                printf("Defined vectors:\n");
                int found = 0;
                for (int i = 0; i < MAX_VECTORS; ++i) {
                    if (vector_defined[i]) {
                        printVector((char[]){(char)('A' + i), '\0'}, vectors[i]);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("  No vectors defined.\n");
                }
            } else if (strcmp(cmd, "cross") == 0) {
                if (sscanf(line, "%*s %c %c", &name1_char, &name2_char) == 2) {
                    idx1 = get_vector_index(toupper(name1_char));
                    idx2 = get_vector_index(toupper(name2_char));
                    if (idx1 != -1 && idx2 != -1 && vector_defined[idx1] && vector_defined[idx2]) {
                        printf("%c x %c = %.2f\n", toupper(name1_char), toupper(name2_char), crossProduct2D(vectors[idx1], vectors[idx2]));
                    } else {
                        printf("Error: Invalid vector name or undefined vector(s).\n");
                    }
                } else {
                    printf("Usage: cross <name1> <name2>\n");
                }
            } else if (strcmp(cmd, "project") == 0) {
                if (sscanf(line, "%*s %c %c %c", &name1_char, &name2_char, &res_char) == 3) {
                    idx1 = get_vector_index(toupper(name1_char)); // vector to project
                    idx2 = get_vector_index(toupper(name2_char)); // vector to project onto
                    res_idx = get_vector_index(toupper(res_char));
                    if (idx1 != -1 && idx2 != -1 && res_idx != -1 && vector_defined[idx1] && vector_defined[idx2]) {
                        vectors[res_idx] = projectVector(vectors[idx1], vectors[idx2]);
                        vector_defined[res_idx] = 1;
                        printVector((char[]){toupper(res_char), '\0'}, vectors[res_idx]);
                    } else {
                        printf("Error: Invalid vector name or undefined vector(s).\n");
                    }
                } else {
                    printf("Usage: project <vec_to_project> <vec_to_project_on> <result_name>\n");
                }
            } else if (strcmp(cmd, "rotate") == 0) {
                if (sscanf(line, "%*s %c %f %c", &name1_char, &scalar, &res_char) == 3) { // using scalar for angle
                    idx1 = get_vector_index(toupper(name1_char));
                    res_idx = get_vector_index(toupper(res_char));
                    if (idx1 != -1 && res_idx != -1 && vector_defined[idx1]) {
                        vectors[res_idx] = rotateVector(vectors[idx1], scalar);
                        vector_defined[res_idx] = 1;
                        printVector((char[]){toupper(res_char), '\0'}, vectors[res_idx]);
                    } else {
                        printf("Error: Invalid vector name or undefined vector.\n");
                    }
                } else {
                    printf("Usage: rotate <name> <degrees> <result_name>\n");
                }
            } else if (strcmp(cmd, "distance") == 0) {
                if (sscanf(line, "%*s %c %c", &name1_char, &name2_char) == 2) {
                    idx1 = get_vector_index(toupper(name1_char));
                    idx2 = get_vector_index(toupper(name2_char));
                    if (idx1 != -1 && idx2 != -1 && vector_defined[idx1] && vector_defined[idx2]) {
                        printf("Distance between %c and %c: %.2f\n", toupper(name1_char), toupper(name2_char), distanceVector(vectors[idx1], vectors[idx2]));
                    } else {
                        printf("Error: Invalid vector name or undefined vector(s).\n");
                    }
                } else {
                    printf("Usage: distance <name1> <name2>\n");
                }
            }
            else {
                printf("Unknown command: %s. Type 'help' for commands.\n", cmd);
            }
        }
    }

    return 0;
}