int findComplement(int num) {
    int mask = 1;
    while (mask < num) {
        mask = (mask * 2) + 1;
    }
    return mask - num; 
}
