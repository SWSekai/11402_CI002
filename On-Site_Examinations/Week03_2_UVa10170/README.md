# UVa 10170 - The Hotel with Infinite Rooms

## 1. Problem Information

- **Platform:** UVa
- **Problem ID:** 10170
- **Problem Title:** The Hotel with Infinite Rooms
- **Problem Link:** https://onlinejudge.org/external/101/10170.html
- **Source Code (Fail):** N/A
- **Source Code (Correct/Accepted):** [UVa10170.cpp](./UVa10170.cpp)

## 2. Problem Statement in My Own Words

Given two integers `S` and `D`:

- `S` is the number of people staying on the first day.
- The number of people increases by 1 each day: `S`, `S + 1`, `S + 2`, and so on.
- `D` is the target cumulative number of people counted from day 1.

The task is to find the number of people staying on the first day when the cumulative total becomes greater than or equal to `D`.

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts

- The most direct approach is to simulate day by day and keep adding people until the total reaches `D`.
- That idea is easy to understand, but it may take too many iterations when `D` is large.

### Final Strategy

- I treat the answer as the smallest integer `N` such that `N >= S`.
- The sum from `S` to `N` can be computed with the arithmetic series formula:

```text
sum = (S + N) * (N - S + 1) / 2
```

- We need the smallest `N` such that this sum is greater than or equal to `D`.
- Since the sum increases monotonically as `N` increases, binary search can find the answer efficiently.

### Edge Cases Considered

- If `S >= D`, the target is already reached on the first day, so the answer is `S`.
- The arithmetic series values can be large, so `long long` is required.
- The multiplication order matters, so the code splits cases by parity to reduce overflow risk in intermediate steps.

## 4. Pseudocode

```text
START
1. Read S and D until EOF
2. If S >= D, output S
3. Binary search N in [S, 2 * 10^9]
4. For each mid, compute whether sum from S to mid is >= D
5. If yes, keep searching left half for smaller valid N
6. If no, search right half
7. Output the smallest valid N
END
```

## 5. Fail Code vs Correct Code

### Fail Code

```cpp
// No preserved fail version for this problem.
```

**Why it failed:**

- No earlier rejected version was kept in the repository.
- This README focuses on explaining the accepted approach instead.

### Correct Code

```cpp
#include<iostream>

using namespace std;

class Infinite_room {
public:
    static long long get_room_group_size(long long initial_member, long long target_room_num) {

        if (initial_member >= target_room_num) return initial_member;

        long long low = initial_member;
        long long high = 2000000000LL;
        long long answer = 0;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (is_reach_target_room(initial_member, mid, target_room_num)) {
                answer = mid;
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        return answer;
    }

private:
    static bool is_reach_target_room(long long initial_member, long long current_room_member, long long target_room_num) {
        long long total_day = 0;

        if ((initial_member + current_room_member) % 2 == 0) {
            total_day = ((initial_member + current_room_member) / 2) * (current_room_member - initial_member + 1);
            return total_day >= target_room_num;
        }
        else {
            total_day = (initial_member + current_room_member) * ((current_room_member - initial_member + 1) / 2);
            return total_day >= target_room_num;
        }
    }
};

int main() {
    long long initial_member;
    long long target_room;

    while (cin >> initial_member >> target_room) {
        cout << Infinite_room::get_room_group_size(initial_member, target_room) << endl;
    }
}
```

**Why it works:**

- It turns the problem into finding the smallest valid value with binary search, which is more efficient than day-by-day simulation.
- Each check uses the arithmetic series formula, so it can quickly decide whether the current `mid` already reaches the target.

## 6. Difference and Reflection

### Key Differences

| Item | Fail Code | Correct Code |
|---|---|---|
| Logic | No preserved fail version | Use binary search with arithmetic series sum |
| Edge Cases | Unknown | Handles `S >= D` directly |
| Output Handling | Unknown | Reads until EOF and prints one answer per case |
| Other | Unknown | Uses `long long` and safer multiplication split |

### Reflection

- The key idea is not simulation, but recognizing that the cumulative sum is monotonic and can be searched with binary search.
- Even with a simple formula, implementation details still matter because intermediate multiplication can overflow.
- For similar problems in the future, I should check early whether they can be converted into "find the smallest valid value" with binary search.
