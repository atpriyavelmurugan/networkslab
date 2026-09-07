class Solution:
    def maxSlidingWindow(self, nums: list[int], k: int) -> list[int]:
        res = []
 
        dq = deque()  
        
        for i, num in enumerate(nums):
            
            if dq and dq[0] < i - k + 1:
                dq.popleft()
                
            
            while dq and nums[dq[-1]] < num:
                dq.pop()
                
            
            dq.append(i)
            
     
            if i >= k - 1:
                res.append(nums[dq[0]])
                
        return res
