class Solution:
    def subarrayBitwiseORs(self, arr: List[int]) -> int:
    
        global_unique = set()
        current_ors = set()
        for num in arr:
       
            current_ors = {prev_or | num for prev_or in current_ors} | {num}
            global_unique.update(current_ors)
        
        return len(global_unique)
 
