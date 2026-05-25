class SeatManager {
    priority_queue<int, vector<int>, greater<int>> unreserve_seats;
    int nextSeat;
public:
    SeatManager(int n) {
        nextSeat = 1;
    }
    
    int reserve() {
        if(unreserve_seats.empty()) return nextSeat++;
        else {
            int seat = unreserve_seats.top();
            unreserve_seats.pop();

            return seat;
        }
    }
    
    void unreserve(int seatNumber) {
        unreserve_seats.push(seatNumber);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */