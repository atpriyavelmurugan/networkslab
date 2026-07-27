char* addBinary(char* a, char* b) {
 
    static char result[10005]; 
    
    int i = strlen(a) - 1;
    int j = strlen(b) - 1;
    int carry = 0;
    int k = 10004; 
    result[k] = '\0'; 
    k--;
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        
        result[k--] = (sum % 2) + '0';
        carry = sum / 2;
    }
    return &result[k + 1];
}

