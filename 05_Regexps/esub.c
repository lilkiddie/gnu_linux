#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_GROUPS 10
#define MAX_REFS 100
#define MAX_ERROR_MSG 256

typedef struct {
    int group_num;
    size_t pos;
} subst_ref;

int parse_substitution(const char *subst, subst_ref refs[], int *ref_count, 
                       int max_groups) {
    *ref_count = 0;
    size_t pos = 0;
    
    for (size_t i = 0; subst[i] != '\0'; i++) {
        if (subst[i] == '\\' && subst[i+1] != '\0') {
            if (subst[i+1] >= '1' && subst[i+1] <= '9') {
                int group = subst[i+1] - '0';
                if (group >= max_groups) {
                    fprintf(stderr, "Error: reference to non-existent group \\%d\n", group);
                    return -1;
                }
                if (*ref_count >= MAX_REFS) {
                    fprintf(stderr, "Error: too many references\n");
                    return -1;
                }
                refs[*ref_count].group_num = group;
                refs[*ref_count].pos = pos;
                (*ref_count)++;
                i++;
            } else if (subst[i+1] == '\\') {
                i++;
            }
        }
        pos++;
    }
    return 0;
}

int count_groups(const char *pattern) {
    int count = 1;
    int escape = 0;
    
    for (size_t i = 0; pattern[i] != '\0'; i++) {
        if (escape) {
            escape = 0;
            continue;
        }
        if (pattern[i] == '\\') {
            escape = 1;
            continue;
        }
        if (pattern[i] == '(') {
            count++;
            if (count > 9) return 9;
        }
    }
    return count;
}

void build_result(const char *str, const char *subst, 
                  regmatch_t *groups, subst_ref *refs, int ref_count,
                  char *result, size_t result_size) {
    size_t result_pos = 0;
    size_t subst_pos = 0;
    
    size_t prefix_len = groups[0].rm_so;
    if (prefix_len > 0) {
        memcpy(result + result_pos, str, prefix_len);
        result_pos += prefix_len;
    }
    
    for (size_t i = 0; subst[i] != '\0' && result_pos < result_size - 1; i++) {
        if (subst[i] == '\\' && subst[i+1] != '\0') {
            if (subst[i+1] >= '1' && subst[i+1] <= '9') {
                int group = subst[i+1] - '0';
                if (groups[group].rm_so != -1) {
                    size_t len = groups[group].rm_eo - groups[group].rm_so;
                    if (result_pos + len < result_size - 1) {
                        memcpy(result + result_pos, 
                               str + groups[group].rm_so, len);
                        result_pos += len;
                    }
                }
                i++;
            } else if (subst[i+1] == '\\') {
                result[result_pos++] = '\\';
                i++;
            } else {
                result[result_pos++] = subst[i];
            }
        } else {
            result[result_pos++] = subst[i];
        }
    }
    
    const char *suffix = str + groups[0].rm_eo;
    size_t suffix_len = strlen(suffix);
    if (result_pos + suffix_len < result_size - 1) {
        memcpy(result + result_pos, suffix, suffix_len);
        result_pos += suffix_len;
    }
    
    result[result_pos] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s regexp substitution string\n", argv[0]);
        return 1;
    }
    
    const char *pattern = argv[1];
    const char *substitution = argv[2];
    const char *string = argv[3];
    
    regex_t regex;
    int ret;
    char error_msg[MAX_ERROR_MSG];
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "Regex compilation failed: %s\n", error_msg);
        return 1;
    }
    
    int max_groups = count_groups(pattern);
    
    subst_ref refs[MAX_REFS];
    int ref_count;
    if (parse_substitution(substitution, refs, &ref_count, max_groups) != 0) {
        regfree(&regex);
        return 1;
    }
    
    regmatch_t groups[MAX_GROUPS];
    ret = regexec(&regex, string, MAX_GROUPS, groups, 0);
    
    if (ret == 0) {
        char result[4096];
        build_result(string, substitution, groups, refs, ref_count, 
                     result, sizeof(result));
        printf("%s\n", result);
    } else if (ret == REG_NOMATCH) {
        printf("%s\n", string);
    } else {
        regerror(ret, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "Regex match failed: %s\n", error_msg);
        regfree(&regex);
        return 1;
    }
    
    regfree(&regex);
    return 0;
}
