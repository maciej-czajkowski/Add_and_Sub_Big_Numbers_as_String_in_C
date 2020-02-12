#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int validate(const char *number);

int sign(const char *number);

int compare(const char *number1, const char *number2);

int subtract(const char *number1, const char *number2, char **result);

int add(const char *number1, const char *number2, char **result);

int add2(const char *number1, const char *number2, char *result, int size);

int subtract2(const char *number1, const char *number2, char *result, int size);

int main()
{

    char *first_array, *second_array;
    char *result_array, *result_array2;

    int c;

    first_array = (char *) malloc(201 * sizeof(char));
    if (first_array == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }


    second_array = (char *) malloc(201 * sizeof(char));
    if (second_array == NULL)
    {
        printf("Failed to allocate memory");
        free(first_array);
        return 8;
    }

    printf("Podaj pierwsza liczbe:");
    scanf("%200s", first_array);

    // czyszczenie buffora
    while ((c = getchar()) != '\n' && c != EOF);


    printf("Podaj druga liczbe: ");
    scanf("%200s", second_array);

    // czyszczenie buffora
    while ((c = getchar()) != '\n' && c != EOF);

//    char result[100];
//    subtract2(first_array, second_array, result, 100);


//    printf("\n\nvalidacja1 = %d", validate(first_array));
//    printf("\ncomapre = %d\n", compare(first_array, second_array));
//
//    printf("wynik add %d\n", add(first_array, second_array, &result_array));

    int sum = add(first_array, second_array, &result_array);

    if ( sum == 2 )
    {
        printf("Incorrect input");
        free(first_array);
        free(second_array);
        return 1;
    }
    if (sum == 3)
    {
        printf("Failed to allocate memory");
        free(first_array);
        free(second_array);
        return 8;
    }
    int sub = subtract(first_array, second_array, &result_array2);
    if ( sub == 2 )
    {
        printf("Incorrect input");
        free(first_array);
        free(second_array);
        free(result_array);
        return 1;
    }
    if (sub == 3)
    {
        free(result_array);
        free(first_array);
        free(second_array);
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Sum\n%s\nSubtraction\n%s\n", result_array, result_array2);

    free(result_array);
    free(result_array2);
    free(first_array);

    free(second_array);
    return 0;
}

int validate(const char *number)
{
    if (number == NULL)
    {
        return -1;
    }

    int i = 0;
    int size = strlen(number);
    if (size == 0)  // sam terminator
    {
        return 2;
    } else if (size == 1)  // 1 znak -> musi byc cyfra
    {
        if (isdigit(*number) == 0)
        {
            return 2;
        } else
        {
            return 0;
        }
    } else // powyzej jednego znaku
    {
        if (*number == '-')
        {
            i++;
            if (size == 2) // wyjatek dla ciagu 2 znakow np "-1"
            {
                if (isdigit(*(number + i)) > 0 && *(number + i) != '0')
                {
                    return 0;
                } else
                {
                    return 2;
                }
            }
        }


        if (*(number + i) == '0' && *(number + i + 1) == '\0')  // sprawdzania samego 0
        {
            return 0;
        } else if (*(number + i) == '0' && *(number + i + 1) != '\0')  // odrzucenie dublowania zera z przodu np 003
        {
            return 2;
        } else
        {
            while (i < size)
            {
                if (isdigit(*(number + i)) == 0) // sprawdzanie czy reszta znakow jest cyframi
                {
                    return 2;
                }
                i++;
            }
            return 0;
        }

    }

}

int compare(const char *number1, const char *number2)
{
    if (number1 == NULL || number2 == NULL)
    {
        return 2;
    }

    if (validate(number1) != 0 || validate(number2) != 0)
    {
        return 3;
    }

    int size1 = strlen(number1);
    int size2 = strlen(number2);

    // obie dodatnie
    // obie ujemna
    // pierwsza + / druga -
    // pierwsza - / druga +

    if (*number1 != '-' && *number2 != '-') // obie +
    {
        if (size1 > size2)
        {
            return 1;
        } else if (size2 > size1)
        {
            return -1;
        }
        if (size1 == size2)
        {
            int i = 0;
            while (*(number1 + i) == *(number2 + i))
            {
                i++;
                if (i == size1)
                {
                    return 0;
                }
            }
            if (*(number1 + i) > *(number2 + i))
            {
                return 1;
            } else
            {
                return -1;
            }
        }
    } else if (*number1 == '-' && *number2 == '-') // obie ujemne
    {
        if (size1 > size2)
        {
            return -1;
        } else if (size2 > size1)
        {
            return 1;
        }
        if (size1 == size2)
        {
            int i = 1;
            while (*(number1 + i) == *(number2 + i))
            {
                i++;
                if (i == size1)
                {
                    return 0;
                }
            }
            if (*(number1 + i) > *(number2 + i))
            {
                return -1;
            } else
            {
                return 1;
            }
        }
    } else if (*number1 == '-' && *number2 != '-')
    {
        return -1;
    } else
    {
        return 1;
    }


    return 8;
}

int subtract(const char *number1, const char *number2, char **result)
{
    if (number1 == NULL || number2 == NULL || result == NULL)
    {
        return 1;
    }

    if (validate(number1) != 0 || validate(number2) != 0)
    {
        return 2;
    }


    int size = 0;
    // alokacja pamieci na result
    if (strlen(number1) > strlen(number2))
    {
        *result = (char *) malloc((strlen(number1) + 3) * sizeof(char));
        size = (strlen(number1) + 2);
        if (*result == NULL)
        {
            return 3;
        }
    } else
    {
        *result = (char *) malloc((strlen(number2) + 3) * sizeof(char));
        size = (strlen(number2) + 2);
        if (*result == NULL)
        {
            return 3;
        }
    }

    int sign1 = sign(number1);
    int sign2 = sign(number2);
//    printf("\nsign1 = %d\tsing2 =%d\n", sign1, sign2);
    if (sign1 == 1 && sign2 == 1)   // 1000 - 950  /   950 - 1000 = - (1000 - 950)   / 125 - 256 = -( 256 - 125) / 256 - 125
    {
        if (strlen(number1) > strlen(number2))
        {
            subtract2(number1, number2, *result, size);
        } else if (strlen(number1) < strlen(number2))
        {
            *((*result)) = '-';
            subtract2(number2, number1, *result + 1, size - 1);
        } else
        {
            if (compare(number1, number2) == 1)
            {
                subtract2(number1, number2, *result, size);

            } else if(compare(number1, number2) == -1)
            {
                *((*result)) = '-';
                subtract2(number2, number1, *result + 1, size - 1);
            }
            else
            {
                *((*result)) = '0';
                *((*result) + 1) = '\0';
            }
        }
    } else if (sign1 == -1 && sign2 == -1)  // -100 - - 100 -300 - -100 = -300 + 100 = - (300 -100) //- 100 - -300 = -100 + 300 = - (100 -
        // 300)
    {
        if (compare(number1+1, number2+1) == 1)  // pierwsza wieksza
        {
            *((*result)) = '-';
            subtract2(number1+1, number2+1, *result+1, size-1);
        }
        else if (compare(number1+1, number2+1) == -1)
        {
            subtract2(number2+1, number1+1, *result, size);
        }
        else
        {
            *((*result)) = '0';
            *((*result) + 1) = '\0';
        }
    } else if (sign1 == 1 && sign2 == -1)  //  pierwsza + / druga - //  356 - -256
    {
        add2(number1, number2+1, *result, size-1);
    } else if (sign1 == -1 && sign2 == 1) // pierwsza / - druga + // -2658 - 300 = - (2658 + 300)  // -1 - 9999 = - (1 + 9999)
    {
        *((*result)) = '-';
        add2(number2, number1+1, *result+1, size-2);
    }

    return 0;
}

int add(const char *number1, const char *number2, char **result)
{
    if (number1 == NULL || number2 == NULL || result == NULL)
    {
        return 1;
    }

    if (validate(number1) != 0 || validate(number2) != 0)
    {
        return 2;
    }


    int size = 0;
    // alokacja pamieci na result
    if (strlen(number1) > strlen(number2))
    {
        *result = (char *) malloc((strlen(number1) + 2) * sizeof(char));
        size = (strlen(number1) + 2);
        if (*result == NULL)
        {
            return 3;
        }
    } else
    {
        *result = (char *) malloc((strlen(number2) + 2) * sizeof(char));
        size = (strlen(number2) + 2);
        if (*result == NULL)
        {
            return 3;
        }
    }

    int sign1 = sign(number1);
    int sign2 = sign(number2);
//    printf("\nsign1 = %d\tsing2 =%d\n", sign1, sign2);
    if (sign1 == 1 && sign2 == 1)
    {
        add2(number1, number2, *result, size);
    } else if (sign1 == -1 && sign2 == -1)
    {
        add2(number1 + 1, number2 + 1, *result + 1, size - 1);
        *((*result)) = '-';
    } else if (sign1 == 1 && sign2 == -1)  //  pierwsza + / druga -
    {
        if (strlen(number1) > strlen(number2) - 1) // 1564894654   + (-54656)  = 1564894654 - 54656
        {
            subtract2(number1, number2 + 1, *result, size);
        } else if (strlen(number1) < strlen(number2) - 1) //  123 + (- 65856) = -(65856 - 123)
        {
            *((*result)) = '-';
            subtract2(number2 + 1, number1, *result + 1, size - 1);
        } else// 123 + (-456) = - (456 -123)  lub 456 + (-123) = 456 - 123
        {
            if (compare(number1, number2 + 1) == -1)
            {
                *((*result)) = '-';
                subtract2(number2 + 1, number1, *result + 1, size - 1);
            } else if (compare(number1, number2 + 1) == 1)
            {
                subtract2(number1, number2 + 1, *result, size);
            } else
            {
                *((*result)) = '0';
                *((*result) + 1) = '\0';
            }
        }
    } else if (sign1 == -1 && sign2 == 1) // pierwsza / - druga +
    {
        if (strlen(number1) - 1 > strlen(number2)) // -123456 + 123 = - ( 123456 - 123)
        {
            *((*result)) = '-';
            subtract2(number1 + 1, number2, *result + 1, size - 1);
        } else if (strlen(number1) - 1 < strlen(number2)) //  -123 + 25689 = 25689 - 123
        {
            subtract2(number2, number1 + 1, *result, size - 1);
        } else// -123 + 256 = 256 - 123 lub -256 + 123 = -(256-123)
        {
            if (compare(number1 + 1, number2) == -1)
            {
                subtract2(number2, number1 + 1, *result, size);
            } else if (compare(number1 + 1, number2) == 1)
            {
                *((*result)) = '-';
                subtract2(number1 + 1, number2, *result + 1, size - 1);
            } else
            {
                *((*result)) = '0';
                *((*result) + 1) = '\0';
            }
        }
    }

    return 0;
}

int sign(const char *number)
{
    if (number == NULL)
    {
        return -2;
    }

    if (*number == '-')
    {
        return -1;
    } else
    {
        return 1;
    }

}

int add2(const char *number1, const char *number2, char *result, int size)
{

    int first_counter = strlen(number1) - 1;
    int second_counter = strlen(number2) - 1;
    int result_counter = 0;
    int adder = 0;
    int temp1, temp2;
    if (number1 == NULL || number2 == NULL || result == NULL || size <= 0)
    {
        return 1;
    }


    if (first_counter >= second_counter)
    {
        result_counter = 0;

        while (first_counter >= 0)
        {


            if (second_counter < 0 && first_counter >= 0)
            {


                for (int i = first_counter; i >= 0; i--)
                {

                    temp1 = *(number1 + first_counter) - '0';

                    if (temp1 + adder >= 10)
                    {
                        *(result + result_counter) = (temp1 - 10 + adder) + '0';


                    } else
                    {
                        *(result + result_counter) = (temp1 + adder) + '0';
                        adder = 0;
                    }

                    result_counter++;
                    first_counter--;

                }
            } else
            {
                temp1 = *(number1 + first_counter) - '0';
                temp2 = *(number2 + second_counter) - '0';

                if (temp1 + temp2 + adder >= 10)
                {
                    *(result + result_counter) = ((temp1 + temp2) - 10 + adder) + '0';

                    adder = 1;
                } else
                {
                    *(result + result_counter) = (temp1 + temp2) + adder + '0';

                    adder = 0;
                }
                first_counter--;
                second_counter--;


                result_counter++;

            }
            if (adder == 1 && first_counter == -1)
            {
                *(result + result_counter) = '1';
                adder = 0;
                result_counter++;
            }
            if (result_counter == size)
            {
                break;
            }

        }
    }

    if (first_counter < second_counter)
    {
        result_counter = 0;

        while (second_counter >= 0)
        {


            if (first_counter < 0 && second_counter >= 0)
            {


                for (int i = second_counter; i >= 0; i--)
                {
                    temp2 = *(number2 + second_counter) - '0';
                    if (temp2 + adder >= 10)
                    {
                        *(result + result_counter) = (temp2 - 10 + adder) + '0';


                    } else
                    {
                        *(result + result_counter) = (temp2 + adder) + '0';
                        adder = 0;
                    }

                    result_counter++;
                    second_counter--;
                }
            } else
            {
                temp1 = *(number1 + first_counter) - '0';
                temp2 = *(number2 + second_counter) - '0';

                if (temp1 + temp2 + adder >= 10)
                {
                    *(result + result_counter) = ((temp1 + temp2) - 10 + adder) + '0';

                    adder = 1;
                } else
                {
                    *(result + result_counter) = (temp1 + temp2) + adder + '0';

                    adder = 0;
                }
                first_counter--;
                second_counter--;


                result_counter++;

            }
            if (adder == 1 && second_counter == -1)
            {
                *(result + result_counter) = '1';
                adder = 0;
                result_counter++;
            }
            if (result_counter == size)
            {
                break;
            }
        }

    }


    *(result + result_counter) = '\0';
    char temp;
//    printf("wynik przed zamiana: \n%s\n", result);
    for (int i = 0; i < ((result_counter - 1) / 2 + 1); i++)
    {
        temp = *(result + i);
        *(result + i) = *(result + result_counter - i - 1);
        *(result + result_counter - i - 1) = temp;
    }
//    printf("wynik po zamiana: \n%s\n", result);

    return 0;
}

int subtract2(const char *number1, const char *number2, char *result, int size)
{
    int first_counter = strlen(number1) - 1;
    int second_counter = strlen(number2) - 1;
    int result_counter = 0;

    int temp1, temp2;
    int sub = 0;


    if (number1 == NULL || number2 == NULL || result == NULL || size <= 0)
    {
        return 1;
    }
    if (first_counter >= second_counter)  // usunoelm rowne
    {
        result_counter = 0;

        while (first_counter >= 0)
        {
            if (second_counter < 0) // do zrobienia
            {


                for (int i = first_counter; i >= 0; i--)
                {

                    temp1 = *(number1 + first_counter) - '0';
                    if (temp1 - sub < 0)
                    {
                        *(result + result_counter) = temp1 + 10 - sub + '0';
                        sub = 1;
                    } else
                    {
                        *(result + result_counter) = temp1 - sub + '0';
                        sub = 0;
                    }
                    first_counter--;
                    result_counter++;

                }
            } else
            {
                temp1 = *(number1 + first_counter) - '0';
                temp2 = *(number2 + second_counter) - '0';
                if (temp1 - temp2 - sub < 0)
                {
                    *(result + result_counter) = temp1 + 10 - sub - temp2 + '0';
                    sub = 1;
                } else
                {
                    *(result + result_counter) = temp1 - sub - temp2 + '0';
                    sub = 0;
                }
                first_counter--;
                second_counter--;
                result_counter++;

            }

        }

    } else
    {
        return 1; // zla kolejnosc
    }
    *(result + result_counter) = '\0';
    char temp;
//    printf("\nwynik \n%s\n\n", result);


    for (int i = 0; i < ((result_counter - 1) / 2 + 1); i++)
    {
        temp = *(result + i);
        *(result + i) = *(result + result_counter - i - 1);
        *(result + result_counter - i - 1) = temp;
    }
//    printf("\npo zamianie kolejnosci \n%s\n\n", result);
    int zero_deleter = 0;
    while (*(result + zero_deleter) == '0')
    {
        zero_deleter++;
    }
    int k = 0;
    for (int i = zero_deleter; i < (int) strlen(result) + 1; i++)
    {
        *(result + k) = *(result + i);
        k++;
        if (*(result + i) == '\0')
        {
            break;
        }
    }

//    printf("\npo usunieciu zer\n%s\n\n", result);

    return 0;
}
