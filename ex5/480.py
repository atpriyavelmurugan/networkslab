import heapq
from collections import defaultdict

class Solution:
    def medianSlidingWindow(self, nums, k):

        small = []   # max heap (store negative values)
        large = []   # min heap

        delayed = defaultdict(int)

        small_size = 0
        large_size = 0

        ans = []


        def prune_small():
            while small and delayed[-small[0]]:
                delayed[-small[0]] -= 1
                heapq.heappop(small)


        def prune_large():
            while large and delayed[large[0]]:
                delayed[large[0]] -= 1
                heapq.heappop(large)


        def balance():
            nonlocal small_size, large_size

            if small_size > large_size + 1:
                x = -heapq.heappop(small)

                heapq.heappush(large, x)

                small_size -= 1
                large_size += 1

                prune_small()


            elif small_size < large_size:
                x = heapq.heappop(large)

                heapq.heappush(small, -x)

                large_size -= 1
                small_size += 1

                prune_large()



        def add(x):
            nonlocal small_size, large_size

            if not small or x <= -small[0]:
                heapq.heappush(small, -x)
                small_size += 1
            else:
                heapq.heappush(large, x)
                large_size += 1

            balance()



        def remove(x):
            nonlocal small_size, large_size

            delayed[x] += 1

            if x <= -small[0]:
                small_size -= 1

                if x == -small[0]:
                    prune_small()

            else:
                large_size -= 1

                if large and x == large[0]:
                    prune_large()

            balance()



        def getMedian():

            if k % 2 == 1:
                return float(-small[0])

            else:
                return (-small[0] + large[0]) / 2.0



        for i, x in enumerate(nums):

            add(x)


            if i >= k:
                remove(nums[i-k])


            if i >= k-1:

                prune_small()
                prune_large()

                ans.append(getMedian())


        return ans
