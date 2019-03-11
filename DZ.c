/*
* "name": "Михаил", 
* "surname": "Ивваниадзе", 
* "group": "АПО-12" 
* "task":
Submit a solution for A- (Variant 5)
Задача A-5. Форматирование строк с тегом div
Time limit: 14 s
Memory limit:   64 M
Реализуйте функцию 
char** div_format(char **s) { 
    ... 
} 

и программу, использующую эту функцию для форматирования текстовой разметки состоящей из <div>, </div> и ASCII строк. 
Правильное форматирование подразумевает расстановку 4х пробелов согласно вложенности. То есть в исходном тексте необходимо 
игнорировать все "ведущие" и "закрывающие" пробелы, и форматировать вывод строк простановкой нового соответствующего количества 
пробелов. В случае некорректной последовательности тэгов, выведите в поток вывода [error]. 

ВАЖНО! Программа в любом случае должна возвращать 0. Не пишите return -1, exit(1) и т.п. Даже если обнаружилась какая-то ошибка, 
все равно необходимо вернуть 0! (и напечатать [error] в stdout).

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Определение типа тега 
int check_div(char *str, size_t p){
    char *s =(char*)malloc(sizeof(char)*(7));
    strncpy(s,str+p,5);
    s[5] = '\0';
    if (!strcmp(s,"<div>")){
        free(s);
        return 1;
    }
    strncpy(s,str+p,6);
    s[6] = '\0';
    if (!strcmp(s,"</div>")){
        free(s);
        return 2;
    }
    free (s);
    return 0;
}

char** div_format (char** s){
    int count = 0;
    size_t i = 0;
    size_t len_size = 100;
    char** result =(char**)malloc(sizeof (char*)*len_size);
    if (!result)
        return result;
    size_t size_len = 128;
    size_t size_result = 0;
    size_t len_str = 0;
    result[size_result] =(char*)malloc(sizeof (char)*size_len);
    if (!result[size_result]){
        free (result);
        return result;
    }
    int flag = 0;
    if (check_div(s[i],0) != 1){
        free(result[size_result]);
        free(result);
        printf("%s\n", "error");
        return result;
    }
    while (s[i] != NULL){
        size_t j = 0;
        while (s[i][j] != '\0' && s[i][j]!='\n'){
            if (s[i][j] == '<'){
                switch(check_div(s[i],j)){
                case 1 :
                    j += 5;
                    count++;
                    if (flag == 1){
                        size_result++;
                        if (size_result == len_size){
                            char** tmp = (char**)realloc(result,len_size*2);
                            if (!tmp){
                                for (size_t k = 0; k < len_size; k++){
                                    free (result[k]);
                                }
                                free(result);
                                return result;
                            }
                            for (size_t k = 0; k < len_size; k++){
                                free (result[k]);
                            }
                            free(result);
                            len_size *= 2;
                            result = tmp;
                        }
                        len_str = 0;
                        result[size_result] = (char*)malloc(sizeof(char)*size_len);
                        if (!result[size_result]){
                            for (size_t k = 0; k < size_result; k++){
                                free (result[k]);
                            }
                            free(result);
                            return result;
                        }
                        for(int m = 0;m < count ; m++){
                            result[size_result][len_str] = '\t';
                            len_str++;
                        }
                        strncpy(result[size_result]+count-1,"<div>",5);
                        result[size_result][len_str+5] = 0;
                        size_result++;
                        if (size_result == len_size){
                            char** tmp = (char**)realloc(result,len_size*2);
                            if (!tmp){
                                for (size_t k = 0; k < len_size; k++){
                                    free (result[k]);
                                }
                                free(result);
                                return result;
                            }
                            for (size_t k = 0; k < size_result; k++){
                                free (result[k]);
                            }
                            free(result);
                            len_size *= 2;
                            result = tmp;
                        }
                        result[size_result] = (char*)malloc(sizeof(char)*size_len);
                        if (!result[size_result]){
                            for (size_t k = 0; k < size_result; k++){
                                free (result[k]);
                            }
                            free(result);
                            return result;
                        }
                        len_str = 0;
                        for(int m = 0;m < count ; m++){
                            result[size_result][len_str] = '\t';
                            len_str++;
                        }
                        result[size_result][len_str] = 0;
                        flag = 0;
                        break;
                    }
                    else {
                        strncpy(result[size_result]+count-1,"<div>",5);
                        result[size_result][len_str+5] = 0;
                        size_result++;
                        if (size_result == len_size){
                            char** tmp = (char**)realloc(result,len_size*2);
                            if (!tmp){
                                for (size_t k = 0; k < len_size; k++){
                                    free (result[k]);
                                }
                                free(result);
                                return result;
                            }
                            for (size_t k = 0; k < len_size; k++){
                                free (result[k]);
                            }
                            free(result);
                            len_size *= 2;
                            result = tmp;
                        }
                        result[size_result] =(char*)malloc(sizeof(char)*size_len);
                        if (!result[size_result]){
                            for (size_t k = 0; k < size_result; k++){
                                free (result[k]);
                            }
                            free(result);
                            return result;
                        }
                        len_str = 0;
                        for(int m = 0;m < count ; m++){
                            result[size_result][len_str] = '\t';
                            len_str++;
                        }
                        result[size_result][len_str] = 0;
                        flag = 0;
                        break;
                    }
                case 2:
                    j += 6;
                    count--;
                    if (flag == 1){
                        if (count < 0){
                            for (size_t k = 0; k < size_result; k++){
                                free (result[k]);
                            }
                            free(result);
                            printf ("%s\n","error");
                            return result;
                        }
                        size_result++;
                        if (size_result == len_size){
                            char** tmp =(char**)realloc(result,len_size*2);
                            if (!tmp){
                                for (size_t k = 0; k < len_size; k++){
                                    free (result[k]);
                                }
                                free(result);
                                return result;
                            }
                            for (size_t k = 0; k < size_result; k++){
                                free (result[k]);
                            }
                            free(result);
                            len_size *= 2;
                            result = tmp;
                        }
                        len_str = 0;
                        result[size_result] =(char*)malloc(sizeof(char)*size_len);
                        if (!result[size_result]){
                            for (size_t k = 0; k < size_result; k++){
                                free (result[k]);
                            }
                            free(result);
                            return result;
                        }
                        for(int m = 0;m < count ; m++){
                            result[size_result][len_str] = '\t';
                            len_str++;
                        }
                        strncpy(result[size_result]+count,"</div>",6);
                        result[size_result][len_str+6] = 0;
                        size_result++;
                        if (size_result == len_size){
                            char** tmp = (char**)realloc(result,len_size*2);
                            if (!tmp){
                                for (size_t k = 0; k < len_size; k++){
                                    free (result[k]);
                                }
                                free(result);
                                return result;
                            }
                            for (size_t k = 0; k < len_size; k++){
                                free (result[k]);
                            }
                            free(result);
                            len_size *= 2;
                            result = tmp;
                        }
                        result[size_result] = (char*)malloc(sizeof (char)*size_len);
                        if (!result[size_result]){
                            for (size_t k = 0; k < size_result; k++){
                                free (result[k]);
                            }
                            free(result);
                            return result;
                        }
                        len_str = 0;
                        for(int m = 0;m < count ; m++){
                            result[size_result][len_str] = '\t';
                            len_str++;
                        }
                        result[size_result][len_str] = 0;
                        flag = 0;
                        break;
                    }
                    else {
                        strncpy(result[size_result]+count,"</div>",6);
                        result[size_result][len_str+6] = 0;
                        size_result++;
                        if (size_result == len_size){
                            char** tmp = (char**)realloc(result,len_size*2);
                            if (!tmp){
                                for (size_t k = 0; k < len_size; k++){
                                    free (result[k]);
                                }
                                free(result);
                                return result;
                            }
                            for (size_t k = 0; k < len_size; k++){
                                free (result[k]);
                            }
                            free(result);
                            len_size *= 2;
                            result = tmp;
                        }
                        result[size_result] = (char*)malloc(sizeof (char)*size_len);
                        if (!result[size_result]){
                            for (size_t k = 0; k < size_result; k++){
                                free (result[k]);
                            }
                            free(result);
                            return result;
                        }
                        len_str = 0;
                        for(int m = 0;m < count ; m++){
                            result[size_result][len_str] = '\t';
                            len_str++;
                        }
                        result[size_result][len_str] = 0;
                        flag = 0;
                        break;
                    }
                case 0:
                    flag = 1;
                    result[size_result][len_str] = s[i][j];
                    len_str++;
                    j++;
                    break;
                }
            }
            else {
                flag = 1;
                result[size_result][len_str] = s[i][j];
                len_str++;
                j++;
            }
        }
        i++;
    }
    if (count == 0){
        return result;
    }
    else{
        for (size_t k = 0; k < size_result; k++){
            free (result[k]);
        }
        free(result);
        printf("%s\n", "error");
        return result;
    }
}

int CheckEmpry (char * str){
    size_t k = 0;
    while (str[k]!= 0){
        if (str[k]!='\t' && str[k]!= ' ')
            return 1;
        k++;
    }
    return 0;
}

int main(){
    size_t len_size = 100;
    char** s =(char**)malloc(sizeof(char*)*len_size);
    if (!s)
        return 0;
    size_t str_len_size = 0;
    size_t string_size = 128;
    s[str_len_size] = (char*)malloc(sizeof (char)*string_size);
    if (!s[str_len_size])
        return 0;
    int getline_result =getline(&s[str_len_size],&string_size,stdin);
    if (getline_result == -1){
        free(s[str_len_size]);
        free(s);
        return 0;
    }
    while (getline_result != -1){
        str_len_size++;
        if (str_len_size == len_size){
            char **tmp = (char**)realloc(s,len_size*2);
            if (!tmp){
                for (size_t k = 0; k < str_len_size; k++){
                    free (s[k]);
                }
                free(s);
                return 0;
            }
            for (size_t i = 0; i < len_size; i++){
                free (s[i]);
            }
            free(s);
            len_size *= 2;
            s = tmp;
        }
        s[str_len_size] = (char*)malloc(sizeof (char)*string_size);
        if (!s[str_len_size]){
            for (size_t k = 0; k < str_len_size - 1; k++)
                free(s[k]);
            free(s);
            return 0;
        }
        getline_result = getline(&s[str_len_size],& string_size,stdin);
    }
    char** result = div_format(s);
    if (result != NULL){
        size_t i = 0;
        while (result[i]!= NULL){
            if (CheckEmpry(result[i])) {
                for (size_t j = 0, k = 0; result[i][j] != 0; j++){
                    if(result[i][j] == ' ')
                        k++;
                    if (k != 1)
                        printf("%c", result[i][j]);
                    else
                        k++;
                }
                printf ("\n");
            }
            free(result[i]);
            i++;
        }
        free (result);
    }
    for (size_t i = 0; i < str_len_size; i++){
        free (s[i]);
    }
    free(s);
    return 0;
}
